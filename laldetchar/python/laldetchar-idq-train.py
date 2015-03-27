# Copyright (C) 2013 Lindy Blackburn, Reed Essick and Ruslan Vaulin
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
# Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

import time
import sys
import os
import traceback
import logging

import numpy

import ConfigParser
from optparse import OptionParser

import subprocess

from glue.ligolw import ligolw
from glue.ligolw import utils as ligolw_utils
from glue.ligolw import lsctables
from glue.ligolw import table

#from laldetchar.idq import idq
from laldetchar.idq import reed
from laldetchar.idq import event
from laldetchar.idq import auxmvc_utils

from pylal import frutils

from laldetchar import git_version

#===================================================================================================

__author__ = \
    'Lindy Blackburn (<lindy.blackburn@ligo.org>), Reed Essick (<reed.essick@ligo.org>), Ruslan Vaulin (<ruslan.vaulin@ligo.org>)'
__version__ = git_version.id
__date__ = git_version.date

description = \
    """This program performs periodic training of the classifiers used in iDQ pipeline. Some intensive training jobs are submitted to cluster using condor. """

#===================================================================================================

parser = OptionParser(version='Name: %%prog\n%s'
                      % git_version.verbose_msg, usage='%prog [options]'
                      , description=description)
parser.add_option('-c', '--config', default='idq.ini', type='string', help='configuration file')

parser.add_option('-s', '--gps-start', dest="gpsstart", default=False, type='int', help='a GPS start time for the analysis. If default, gpsstart is calculated from the current time.')
parser.add_option('-e', '--gps-stop', dest="gpsstop", default=False, type='int', help='a GPS stop time for the analysis. If default, gpsstop is calculated from the current time.')
parser.add_option('-b', '--lookback', default='0', type='string', help="Number of seconds to look back and get data for training. Default is zero.\
	Can be either positive integer or 'infinity'. In the latter case, the lookback will be incremented at every stride and all data after --gps-start will be used in every training.")

parser.add_option('-l', '--log-file', default='idq_train.log', type='string', help='log file')

parser.add_option('-f','--force',default=False, action='store_true', help="forces classifiers to be trained, \
	and if errors are recovered it passes them along. Intended for use when we must have a trained classifier or else we should raise an error. \
	This may produce an infinite loop if the condor dags get lost (for mla classifiers). Use with caution.")

parser.add_option("", "--no-robot-cert", default=False, action="store_true", help="does not set up robot certificate. This can cause jobs to fail because of expired certificates")

parser.add_option("", "--ignore-science-segments", default=False, action="store_true", help="ignores science segments and trains over all available data within range")

parser.add_option("", "--sngl_chan-xml", default=False, action="store_true", help="convert single channel trg files to xml tables")

(opts, args) = parser.parse_args()

if opts.lookback != "infinity":
    opts.lookback = int(opts.lookback)

cwd = os.getcwd()

#===================================================================================================
### setup logger to record processes
logger = reed.setup_logger('idq_logger', opts.log_file, sys.stdout, format='%(asctime)s %(message)s')

sys.stdout = reed.LogFile(logger)
sys.stderr = reed.LogFile(logger)

#===================================================================================================
### read global configuration file

config = ConfigParser.SafeConfigParser()
config.read(opts.config)

#mainidqdir = config.get('general', 'idqdir') ### get the main directory where idq pipeline is going to be running.

ifo = config.get('general', 'ifo')

usertag = config.get('general', 'usertag')
if usertag:
    usertag = "_%s"%usertag

#========================
# which classifiers
#========================
classifiers = sorted(set(config.get('general', 'classifiers').split()))
if not classifiers:
    raise ValueError("no classifiers in general section of %s"%opts.config_file)

### ensure we have a section for each classifier and fill out dictionary of options
classifiersD, mla, ovl = reed.config_to_classifiersD( config )

if mla:
    ### reading parameters from config file needed for mla
    auxmvc_coinc_window = config.getfloat('build_auxmvc_vectors','time-window')
    auxmc_gw_signif_thr = config.getfloat('build_auxmvc_vectors','signif-threshold')
    auxmvc_selected_channels = config.get('general','selected-channels')
    auxmvc_unsafe_channels = config.get('general','unsafe-channels')

#min_samples = config.getint('train', 'min_samples') ### minimum number of samples a training set should have
#min_svm_samples = config.getint('idq_train', 'min_svm_samples')
#min_ovl_samples = config.getint('ovl_train', 'min_num_glitches')

dag_classifiers = []
blk_classifiers = []
for classifier in classifiers:
    if classifier in reed.train_with_dag:
        dag_classifiers.append( classifier )
    else:
        blk_classifiers.append( classifier )

#========================
# realtime
#========================
realtimedir = config.get('general', 'realtimedir')

padding = config.getfloat('realtime', 'padding')

#========================
# train
#========================
traindir = config.get('general', 'traindir')
if ovl: ### need snglchandir
   snglchndir = config.get('general', 'snglchndir') 

stride = config.getint('train', 'stride')
delay = config.getint('train', 'delay')

train_script = config.get('condor', 'train')

train_cache = dict( (classifier, reed.Cachefile(reed.cache(traindir, classifier, tag='_train%s'%usertag))) for classifier in classifiers )

build_auxmvc_vectors = mla and (not os.path.exists(realtimedir)) ### if realtimedir does not exist, we cannot rely on patfiles from the realtime job
                                                                 ### we need to build our own auxmvc_vectors

#========================
# data discovery
#========================
if not opts.ignore_science_segments:
    ### load settings for accessing dmt segment files
#    dmt_segments_location = config.get('get_science_segments', 'xmlurl')
    dq_name = config.get('get_science_segments', 'include')
#    dq_name = config.get('get_science_segments', 'include').split(':')[1]
    segdb_url = config.get('get_science_segments', 'segdb')

### set up content handler for xml files
lsctables.use_in(ligolw.LIGOLWContentHandler)

### define the gravitational wave channel/what is a glitch
gwchannel = config.get('general', 'gwchannel')
gwthreshold = config.getfloat('general', 'gw_kwsignif_thr')

### kleineWelle config
GWkwconfigpath = config.get('data_discovery', 'GWkwconfig')
GWkwconfig = reed.loadkwconfig(GWkwconfigpath)
GWkwbasename = GWkwconfig['basename']
GWgdsdir = config.get('data_discovery', 'GWgdsdir')

GWkwtrgdir = "%s/%s"%(GWgdsdir, GWkwbasename)

AUXkwconfigpath = config.get('data_discovery', 'AUXkwconfig')
AUXkwconfig = reed.loadkwconfig(AUXkwconfigpath)
AUXkwbasename = AUXkwconfig['basename']
AUXgdsdir = config.get('data_discovery', 'AUXgdsdir')

AUXkwtrgdir = "%s/%s"%(AUXgdsdir, AUXkwbasename)

identical_trgfile = (GWgdsdir == AUXgdsdir) and (GWkwbasename == AUXkwbasename) ### used to avoid re-loading the same file for both GW and AUX triggers

#==================================================
### set up ROBOT certificates
### IF ligolw_segment_query FAILS, THIS IS A LIKELY CAUSE
if opts.no_robot_cert:
    logger.warning("Warning: running without a robot certificate. Your personal certificate may expire and this job may fail")
else:
    ### unset ligo-proxy just in case
    if os.environ.has_key("X509_USER_PROXY"):
        del os.environ['X509_USER_PROXY']

    ### get cert and key from ini file
    robot_cert = config.get('ldg_certificate', 'robot_certificate')
    robot_key = config.get('ldg_certificate', 'robot_key')

    ### set cert and key
    os.environ['X509_USER_CERT'] = robot_cert
    os.environ['X509_USER_KEY'] = robot_key

#=================================================
### data storage during training jobs

### create condorlogs directory if needed
condorlogs = config.get('train', 'condorlogs')
if not os.path.exists(condorlogs):
    os.makedirs(condorlogs)

#==================================================
### current time and boundaries

t = int(reed.nowgps())

gpsstop = opts.gpsstop
if not gpsstop: ### stop time of this analysis
    logger.info('computing gpsstop from current time')
    gpsstop = t ### We do not require boundaries to be integer multiples of stride

gpsstart = opts.gpsstart
if not gpsstart:
    logger.info('computing gpsstart from gpsstop')
    gpsstart = gpsstop - stride

#===================================================================================================
#
# LOOP
#
#===================================================================================================
logger.info('Begin: training')

n_train = 0 ### this is used to track the "original starting place" via incrementation within the persistent loop

### wait until all jobs are finished
wait = gpsstart + stride + delay - t
if wait > 0:
    logger.info('----------------------------------------------------')
    logger.info('waiting %.1f seconds to reach gpsstart+stride+delay=%d' % (wait, gpsstart+stride+delay))
    time.sleep(wait)

global_start = gpsstart 

### iterate over all ranges
while gpsstart < gpsstop:

    logger.info('----------------------------------------------------')

    wait = gpsstart + stride + delay - t
    if wait > 0:
        logger.info('waiting %.1f seconds to reach gpsstart+stride+delay=%d' %(wait, gpstart+stride+delay))
        time.sleep(wait)

    launch_gps_time = reed.nowgps()

    ### increment lookback time if it is set to infinity
    ### this forces the job to pick up all data since opts.gps_start
    if opts.lookback == 'infinity':
        lookback = gpsstart - global_start
    else:
        lookback = opts.lookback

    logger.info('processing data in [%d, %d]' % (gpsstart - lookback , gpsstart + stride))

    ### directory into which we write data
    output_dir = "%s/%d_%d/"%(traindir, gpsstart, gpsstart + stride)
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    #=============================================
    # veto segments (external to idq)
    #=============================================
    ### NOTHING implemented for vetosegs
    ### these are only used by ovl
    vetosegs = False

    #=============================================
    # science segments
    #=============================================
    if opts.ignore_science_segments:
        logger.info('analyzing data regardless of science segments')
        seg_file = None
        if ovl:
            ovlsegs = False ### required for OVL input

    else:
        logger.info('Begin: querrying science segments')

        try: 
           ### this returns a string
            seg_xml_file = reed.segment_query(config, gpsstart - lookback , gpsstart + stride, url=segdb_url)

            ### load xml document
            xmldoc = ligolw_utils.load_fileobj(seg_xml_file, contenthandler=ligolw.LIGOLWContentHandler)[0]

            ### science segments xml filename
            seg_file = reed.segxml(output_dir, "_%s"%dq_name, gpsstart - lookback , lookback+stride)

            logger.info('writing science segments to file : '+seg_file)
            ligolw_utils.write_filename(xmldoc, seg_file, gz=seg_file.endswith(".gz"))

        except Exception as e:
            traceback.print_exc()
            logger.info('ERROR: segment generation failed. Skipping this training period.')

            if opts.force: ### we are require successful training or else we want errors
                logger.info(traceback.print_exc())
                raise e
            else: ### we don't care if any particular training job fails
                gpsstart += stride
                continue

        if ovl:
            if build_auxmvc_vectors or (not os.path.exists(realtimedir)): ### mla will use science segments, so we need to write those for ovl
                                                                         ### if realtimedir doesn't exits, we need to use queried scisegs
                try:
                    (scisegs, coveredseg) = reed.extract_dq_segments(seg_file, dq_name) ### read in segments from xml file

                    ### write segments to ascii list
                    sciseg_path = reed.segascii(output_dir, "_%s"%dq_name, gpsstart-lookback, lookback+stride)
                    logger.info('writing science segments to file : '+sciseg_path)
                    f = open(sciseg_path, 'w')
                    for line in scisegs:
                        print >> f, line[0], line[1]
                    f.close()
                    ovlsegs = sciseg_path

                except Exception as e:
                    traceback.print_exc()
                    logger.warning('WARNING: conversion from xml to ASCII segment file failed.')
    
                    if opts.force:
                        logger.info(traceback.print_exc())
                        raise e
                    else:
                        gpsstart += stride 
                        continue 

            ### if we aren't building auxmvc vectors, we re-use pat files from realtime job
            ### this requires us to redefine the 'science-segments' as the intersection of scisegs with realtime segs
            ### we call this intersection "idq_segs"
            else: ### we're re-using pat files!
                try:
                    ### determine segments from realtime filenames
                    realtime_segs = reed.get_idq_segments(realtimedir, gpsstart - lookback, gpsstart + stride, suffix='.pat')

                    ### read in science segments
                    (scisegs, coveredseg) = reed.extract_dq_segments(seg_file, dq_name)

                    ### take the intersection of these segments
                    idq_segs = event.andsegments([scisegs, realtime_segs])

                    ### write segment file
                    idqseg_path = reed.idqsegascii(output_dir, '_%s'%dq_name, gpsstart - lookback, lookback+stride)
                    f = open(idqseg_path, 'w')
                    for seg in idq_segs:
                        print >> f, seg[0], seg[1]
                    f.close()

                    ovlsegs = idqseg_path

                except Exception as e:
                    traceback.print_exc()
                    logger.info('WARNING: failed to generate iDQ segments from realtime output.')

                    if opts.force:
                        raise e
                    else:
                        gpsstart += stride
                        continue

            logger.info('Done.')

    #===============================================================================================
    # preparing auxmvc training samples
    #===============================================================================================
    if mla:
        logger.info('preparing training auxmvc samples')

        if not build_auxmvc_vectors: ### we cat together pat files instead of building vectors from scratch
            ### output file for training samples
            pat = reed.pat(output_dir, ifo, "mla", gpsstart-lookback, lookback+stride)

            ### run job that prepares training samples
            (ptas_exit_status, _) = reed.execute_prepare_training_auxmvc_samples(output_dir, realtimedir, config, gpsstart - lookback, gpsstart + stride, pat, dq_segments=seg_file, dq_segments_name=dq_name )
            os.chdir(current_dir) ### go back to starting directory

        if build_auxmvc_vectors or ptas_exit_status!=0: ### we need to build vectors
            if build_auxmvc_vectors: ### no realtime directory...
                logger.warning('WARNING: building auxmvc vectors, this should be necessary only at the very first training cycle')
            else:
                logger.warning('WARNING: patfile generation failed for some reason. Attempt to build auxmvc vectors from scratch')

                ### launch job that builds auxmvc_vectors
                (ptas_exit_status, _) = reed.execute_build_auxmvc_vectors( config, ptas_execute_dir, AUXkwtrgdir, gwchannel, pat, gpsstart - lookback, gpsstart + stride, channels=auxmvc_selected_channels, unsafe_channels=auxmvc_unsafe_channels, dq_segments=seg_file, dq_segments_name=dq_name )
                os.chdir(current_dir) ### go back to starting directory
 
        # check if process has been executed correctly
        if ptas_exit_status != 0: ### check that process executed correctly
            logger.warning('WARNING: Preparing training auxmvc samples failed')
            if opts.force:
                raise StandardError, "auxmvc samples required for successful training"
            else:
                logger.warning('WARNING: skipping re-training the MLA classifiers')
        else:
            ### figure out training set size
            ### load auxmvc vector samples
            auxmvc_samples = auxmvc_utils.ReadMVSCTriggers([pat], Classified=False)

            ### get numbers of samples
            N_clean = len(auxmvc_samples[numpy.nonzero(auxmvc_samples['i']==0)[0], :])
            N_glitch = len(auxmvc_samples[numpy.nonzero(auxmvc_samples['i']==1)[0], :])

            del auxmvc_samples

    logger.info('Done: preparing training auxmvc samples')

    #===============================================================================================
    # launch training jobs
    #===============================================================================================
    dags = {} ### dictionary that holds the dags submitted for each classifier

    #=============================================
    # training with a dag
    #=============================================
    for classifier in dag_classifiers: ### these are trained with a dag
        classD = classifiersD[classifier]
        flavor = classD['flavor']

        if flavor in reed.mla_flavors and ptas_exit_status:
            logger.warning("WARNING: mla training samples could not be built. skipping %s training"%classifier)
            continue

        if opts.force or ((N_clean >= classD['min_num_cln']) and (N_glitch >= classD['min_num_gch'])):

            logger.info('submitting %s training dag'%classifier)

            train_dir = "%s/%s/"%(output_dir, classifier)
            if not os.path.exists(train_dir):
                os.makedirs(train_dir)
      
            ### submit training job
            (submit_dag_exit_status, dag_file) = reed.dag_train(flavor, pat,  train_cache[classifier].name, config, train_dir, cwd)

            if submit_dag_exit_status:
                logger.warning("WARNING: was not able to submit %s training dag"%classifier)
                dags[dag_file] = "submit failed"
                if opts.force:
                    raise StandardError, "submission of %s training dag failed"%classifier
            else:
                dags[dag_file] = "incomplete"
                logger.info('dag file %s/%s'%(train_dir, dag_file))

        elif (N_clean > classD['min_num_cln']):
            logger.warning("WARNING: not enough glitches in training set. skipping %s training"%classifier)
        elif (N_glitch >= classD['min_num_gch']):
            logger.warning("WARNING: not enough cleans in training set. skipping %s training"%classifier)
        else:
            logger.warning("WARNING: neither enough cleans nor enough glitches in training set. skipping %s training"%classifier)
            
    #=============================================
    # sngl_chan collection
    #=============================================
    ### OVL reads triggers from single channel summary files. these are not produced in low latency, so we build them now
    ### Currently, OVL is the only method that doesn't train with a dag, so we can put this here and not slow down the other methods' training
    ### HOWEVER, this is fragile and may break in the future.
    ### a possible work around is to define yet another group of flavors to distinguish "blk_train" from "sngchn_train"
    if ovl:
        logger.info('generating single-channel summary files')
    
        new_dirs = reed.collect_sngl_chan_kw( gpsstart, gpsstart + stride, GWkwconfigpath, width=stride, source_dir=GWkwtrgdir, output_dir=snglchndir )
        if not identical_trgfile:
            new_dirs += reed.collect_sngl_chan_kw( gpsstart, gpsstart+stride, AUXkwconfigpath, width=stride, source_dir=AUXkwtrgdir, output_dir=snglchndir )

    #=============================================
    # training on submit node
    #=============================================
    for classifier in blk_classifiers: ### these are trained via routines on the head node
                                       ### right now, this is just OVL, so we're safe putting sngl_chan routine ahead of this 
        classD = classifiersD[classifier]
        flavor = classD['flavor']

        train_dir = "%s/%s/"%(output_dir, classifier)
        if not os.path.exists(train_dir):
            os.makedirs(train_dir)

        logger.info('launching %s training job'%classifier)
        exit_status, _ = reed.blk_train(flavor, config, classifiersD[classifier], gpsstart-lookback, gpsstart+stride, ovlsegs=ovlsegs, vetosegs=vetosegs, train_dir=train_dir, cwd=cwd, force=opts.force, cache=train_cache[classifier], min_num_gch=classD['min_num_gch'], min_num_cln=classD['min_num_cln'], padding=padding)

        if exit_status:
            logger.info('WARNING: number glitches in the training set is less than %d'%int(classD['min_num_gch']))
            logger.info('WARNING: Not enough glitches in the training set. Skip %s training.'%classifier)

        logger.info('Done.')

    #===============================================================================================
    # jobs completion checkpoint (for dags)
    #===============================================================================================
    if dags: ### dags is not empty

        logger.info('Begin: checking on dags')

        list_of_dags = sorted(dags.keys())

        ### loop until either all dags are complete or gpsstop+stride time is reached
        incompleted_dags = []

        ### if opts.force, we wait for all jobs to finish
        ### otherwise, we wait for some amount of time before proceeding
        while opts.force or (reed.nowgps() < gpsstop + stride) or (reed.nowgps() < launch_gps_time + stride):

            for dag in list_of_dags: ### check dag status
                dag_status = reed.get_condor_dag_status(dag)
                dags[dag] = dag_status

                if dag_status == 0:
                    logger.info('%s completed' % dag)
                else:
                    incompleted_dags.append(dag)

            list_of_dags = incompleted_dags
            incompleted_dags = []

            if 'incomplete' in dags.values(): ### check if any of the dags are still incomplete
                logger.info('WARNING: Some dags have not been completed.')
                time.sleep(300) ### wait 300 seconds before continue the loop
                                ### 300 is a magic number, although 5 min. should be much shorter than stride
            else: ### no incomplete dags, break the loop
                break

        ### print warnings for dags that failed or are incomplete
        for dag in list_of_dags:
            if dags[dag] != 0:
                if dags[dag] == 'incomplete':
                    logger.warning('WARNING: %s was  not complete' % dag)
                else:
                    logger.warning('WARNING: %s failed with exit status %s'% (dag, str(dags[dag])))
                    if opts.force:
                       raise StandardError, "%s failed with exit status %s"%(dag, str(dags[dag]))

    #===============================================================================================
    # conversion of snglchn files to xml
    #===============================================================================================
    ### we collect the single channel trg files into xml files
    ### this shouldn't be necessary for OVL training and i doubt these files
    ### will be used by anyone else...
    ### FIXME: WE MAY WANT TO REMOVE THIS STEP
    if opts.sngl_chan_xml:
        logger.info('launching conversion from .trg to .xml files')
        for dir in new_dirs:
            current_dir = os.getcwd()
            trg_to_xml_exit_code = reed.submit_command([config.get('condor', 'convertkwtosb'), dir], process_name='convertkwtosb', dir=dir)
            os.chdir(current_dir)
            if trg_to_xml_exit_code != 0:
                logger.info('WARNING: Conversion from single-channel KW trig files to xml failed in '+ dir)

        logger.info('Done.')

    #===============================================================================================

    ### continue onto the next stride
    gpsstart += stride

