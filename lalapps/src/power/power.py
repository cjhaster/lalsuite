# $Id$
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 51
# Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


#
# =============================================================================
#
#                                   Preamble
#
# =============================================================================
#


"""
Classes needed for the excess power analysis pipeline.
"""


import math
import os
import sys
import time


from glue import segments
from glue import pipeline
from glue.lal import CacheEntry
from pylal.date import LIGOTimeGPS


__author__ = "Duncan Brown <duncan@gravity.phys.uwm.edu>, Kipp Cannon <kipp@gravity.phys.uwm.edu>"
__date__ = "$Date$"[7:-2]
__version__ = "$Revision$"[11:-2]


#
# =============================================================================
#
#                                   Helpers
#
# =============================================================================
#


def get_universe(config_parser):
	return config_parser.get("condor", "universe")


def get_executable(config_parser, name):
	return config_parser.get("condor", name)


def get_out_dir(config_parser):
	return config_parser.get("pipeline", "out_dir")


def get_cache_dir(config_parser):
	return config_parser.get("pipeline", "cache_dir")


def make_dag_directories(config_parser):
	os.mkdir(get_cache_dir(config_parser))
	os.mkdir(get_out_dir(config_parser))


def get_parents_per_binjfind(config_parser):
	return config_parser.getint("pipeline", "parents_per_binjfind")


def get_parents_per_bucluster(config_parser):
	return config_parser.getint("pipeline", "parents_per_bucluster")


def get_parents_per_bucut(config_parser):
	return config_parser.getint("pipeline", "parents_per_bucut")


#
# =============================================================================
#
#                            DAG Node and Job Class
#
# =============================================================================
#


class BurstInjJob(pipeline.CondorDAGJob):
	"""
	A lalapps_binj job used by the power pipeline. The static options
	are read from the [lalapps_binj] section in the ini file. The
	stdout and stderr from the job are directed to the logs directory.
	The job runs in the universe specified in the ini file.  The path
	to the executable is determined from the ini file.
	"""
	def __init__(self, config_parser):
		"""
		config_parser = ConfigParser object
		"""
		pipeline.CondorDAGJob.__init__(self, get_universe(config_parser), get_executable(config_parser, "lalapps_binj"))

		# do this many injections between flow and fhigh inclusively
		self.injection_bands = config_parser.getint("pipeline", "injection_bands")

		self.add_ini_opts(config_parser, "lalapps_binj")

		self.set_stdout_file(os.path.join(get_out_dir(config_parser), "binj-$(macrochannelname)-$(macrogpsstarttime)-$(macrogpsendtime)-$(cluster)-$(process).out"))
		self.set_stderr_file(os.path.join(get_out_dir(config_parser), "binj-$(macrochannelname)-$(macrogpsstarttime)-$(macrogpsendtime)-$(cluster)-$(process).err"))
		self.set_sub_file("lalapps_binj.sub")


class BurstInjNode(pipeline.CondorDAGNode):
	def __init__(self, job):
		pipeline.CondorDAGNode.__init__(self, job)
		self.__usertag = None

	def set_user_tag(self, tag):
		self.__usertag = tag
		self.add_var_opt("user-tag", self.__usertag)

	def get_user_tag(self):
		return self.__usertag

	def set_start(self, start):
		self.add_var_opt("gps-start-time", start)

	def set_end(self, end):
		self.add_var_opt("gps-end-time", end)

	def get_start(self):
		return self.get_opts().get("macrogpsstarttime", None)

	def get_end(self):
		return self.get_opts().get("macrogpsendtime", None)

	def get_output_cache(self):
		"""
		Returns a LAL cache of the output file names.  This must be
		kept synchronized with the name of the output file in
		binj.c.  Note in particular the calculation of the "start"
		and "duration" parts of the name.
		"""
		if not self.get_start() or not self.get_end():
			raise ValueError, "start time or end time has not been set"
		seg = segments.segment(LIGOTimeGPS(self.get_start()), LIGOTimeGPS(self.get_end()))
		if self.__usertag:
			filename = "HL-INJECTIONS_%s-%d-%d.xml" % (self.__usertag, int(self.get_start()), int(self.get_end() - self.get_start()))
		else:
			filename = "HL-INJECTIONS-%d-%d.xml" % (int(self.get_start()), int(self.get_end() - self.get_start()))
		return [CacheEntry("H1,H2,L1", self.__usertag, seg, "file://localhost" + os.path.abspath(filename))]

	def get_output_files(self):
		raise NotImplementedError

	def get_output(self):
		raise NotImplementedError


class PowerJob(pipeline.CondorDAGJob, pipeline.AnalysisJob):
	"""
	A lalapps_power job used by the power pipeline. The static options
	are read from the [lalapps_power] and [lalapps_power_<inst>]
	sections in the ini file. The stdout and stderr from the job are
	directed to the logs directory.  The job runs in the universe
	specified in the ini file. The path to the executable is determined
	from the ini file.
	"""
	def __init__(self, config_parser):
		"""
		config_parser = ConfigParser object
		"""
		pipeline.CondorDAGJob.__init__(self, get_universe(config_parser), get_executable(config_parser, "lalapps_power"))
		pipeline.AnalysisJob.__init__(self, config_parser)
		self.add_condor_cmd("compress_files", "*.xml.gz")

		self.add_ini_opts(config_parser, "lalapps_power")

		self.set_stdout_file(os.path.join(get_out_dir(config_parser), "power-$(macrochannelname)-$(macrogpsstarttime)-$(macrogpsendtime)-$(cluster)-$(process).out"))
		self.set_stderr_file(os.path.join(get_out_dir(config_parser), "power-$(macrochannelname)-$(macrogpsstarttime)-$(macrogpsendtime)-$(cluster)-$(process).err"))
		self.set_sub_file("lalapps_power.sub")

		# pre-evaluate some segmentation parameters
		self.psd_length = float(self.get_opts()["psd-average-points"]) / float(self.get_opts()["resample-rate"])
		self.window_length = float(self.get_opts()["window-length"]) / float(self.get_opts()["resample-rate"])
		self.window_shift = float(self.get_opts()["window-shift"]) / float(self.get_opts()["resample-rate"])
		self.filter_corruption = float(self.get_opts()["filter-corruption"]) / float(self.get_opts()["resample-rate"])
		self.psd_overlap = self.window_length - self.window_shift


class PowerNode(pipeline.AnalysisNode):
	def __init__(self, job):
		pipeline.CondorDAGNode.__init__(self, job)
		pipeline.AnalysisNode.__init__(self)
		self.__usertag = None

	def set_ifo(self, instrument):
		"""
		Load additional options from the per-instrument section in
		the config file.
		"""
		pipeline.AnalysisNode.set_ifo(self, instrument)
		for optvalue in self.job()._AnalysisJob__cp.items("lalapps_power_%s" % instrument):
			self.add_var_arg("--%s %s" % optvalue)

	def set_user_tag(self, tag):
		self.__usertag = tag
		self.add_var_opt("user-tag", self.__usertag)

	def get_user_tag(self):
		return self.__usertag

	def get_output_cache(self):
		"""
		Returns a LAL cache of the output file name.  Calling this
		method also induces the output name to get set, so it must
		be at least once.
		"""
		seg = segments.segment(LIGOTimeGPS(self.get_start()), LIGOTimeGPS(self.get_end()))
		filename = self.get_output()
		# FIXME: condor's documentation claims that it will
		# compress output files written by standard universe jobs.
		# I did what the documentation says, and the files were not
		# compressed.  Why?  Get rid of this post script when this
		# gets figured out.
		self.set_post_script("/usr/bin/gzip -f %s" % os.path.abspath(filename))
		return [CacheEntry(self.get_ifo(), self.__usertag, seg, "file://localhost" + os.path.abspath(filename + ".gz"))]

	def get_output_files(self):
		raise NotImplementedError

	def get_output(self):
		if self._AnalysisNode__output is None:
			if None in (self.get_start(), self.get_end(), self.get_ifo(), self.__usertag):
				raise ValueError, "start time, end time, ifo, or user tag has not been set"
			seg = segments.segment(LIGOTimeGPS(self.get_start()), LIGOTimeGPS(self.get_end()))
			self.set_output("%s-POWER_%s-%d-%d.xml" % (self.get_ifo(), self.__usertag, int(self.get_start()), int(self.get_end()) - int(self.get_start())))
		return self._AnalysisNode__output

	def set_mdccache(self, file):
		"""
		Set the LAL frame cache to to use. The frame cache is
		passed to the job with the --frame-cache argument.  @param
		file: calibration file to use.
		"""
		self.add_var_opt("mdc-cache", file)
		self.add_input_file(file)

	def set_inspinj(self, file):
		"""
		Set the LAL frame cache to to use. The frame cache is
		passed to the job with the --frame-cache argument.  @param
		file: calibration file to use.
		"""
		self.add_var_opt("inspiralinjection-file", file)
		self.add_input_file(file)

	def set_siminj(self, file):
		"""
		Set the LAL frame cache to to use. The frame cache is
		passed to the job with the --frame-cache argument.  @param
		file: calibration file to use.
		"""
		self.add_var_opt("siminjection-file", file)
		self.add_input_file(file)


class LigolwAddNode(pipeline.LigolwAddNode):
	def __init__(self, *args):
		pipeline.LigolwAddNode.__init__(self, *args)
		self.cache = []

	def set_name(self, *args):
		pipeline.LigolwAddNode.set_name(self, *args)
		self.cache_name = os.path.join(self._CondorDAGNode__job.cache_dir, "%s.cache" % self.get_name())
		self.add_var_opt("input-cache", self.cache_name)

	def add_input_cache(self, cache):
		self.cache.extend(cache)

	def add_preserve_cache(self, cache):
		for c in cache:
			self.add_var_arg("--remove-input-except %s" % c.path())

	def get_output_cache(self):
		instruments = []
		for c in self.cache:
			if c.observatory != None:
				instruments.extend([ins for ins in c.observatory.split(",") if ins not in instruments])
		instruments.sort()
		return [CacheEntry(",".join(instruments), None, segments.segmentlist([c.segment for c in self.cache if c.segment != None]).extent(), "file://localhost" + os.path.abspath(self._AnalysisNode__output))]

	def write_input_files(self, *args):
		f = file(self.cache_name, "w")
		for c in self.cache:
			print >>f, str(c)
		pipeline.LigolwAddNode.write_input_files(self, *args)

	def get_output_files(self):
		raise NotImplementedError

	def get_output(self):
		raise NotImplementedError


class BucutJob(pipeline.CondorDAGJob):
	def __init__(self, config_parser):
		pipeline.CondorDAGJob.__init__(self, "vanilla", get_executable(config_parser, "ligolw_bucut"))
		self.set_sub_file("ligolw_bucut.sub")
		self.set_stdout_file(os.path.join(get_out_dir(config_parser), "ligolw_bucut-$(cluster)-$(process).out"))
		self.set_stderr_file(os.path.join(get_out_dir(config_parser), "ligolw_bucut-$(cluster)-$(process).err"))
		self.add_condor_cmd("getenv", "True")
		self.add_ini_opts(config_parser, "ligolw_bucut")


class BucutNode(pipeline.CondorDAGNode):
	def __init__(self, *args):
		pipeline.CondorDAGNode.__init__(self, *args)
		self.cache = []

	def add_input_cache(self, cache):
		self.cache.extend(cache)
		for c in cache:
			filename = c.path()
			pipeline.CondorDAGNode.add_file_arg(self, filename)
			self.add_output_file(filename)

	def add_file_arg(self, filename):
		raise NotImplementedError

	def get_output_cache(self):
		return self.cache

	def get_output_files(self):
		raise NotImplementedError

	def get_output(self):
		raise NotImplementedError


class BuclusterJob(pipeline.CondorDAGJob):
	def __init__(self, config_parser):
		pipeline.CondorDAGJob.__init__(self, "vanilla", get_executable(config_parser, "ligolw_bucluster"))
		self.set_sub_file("ligolw_bucluster.sub")
		self.set_stdout_file(os.path.join(get_out_dir(config_parser), "ligolw_bucluster-$(cluster)-$(process).out"))
		self.set_stderr_file(os.path.join(get_out_dir(config_parser), "ligolw_bucluster-$(cluster)-$(process).err"))
		self.add_condor_cmd("getenv", "True")
		self.add_ini_opts(config_parser, "ligolw_bucluster")


class BuclusterNode(pipeline.CondorDAGNode):
	def __init__(self, *args):
		pipeline.CondorDAGNode.__init__(self, *args)
		self.cache = []

	def set_name(self, *args):
		pipeline.CondorDAGNode.set_name(self, *args)
		self.cache_name = os.path.join(self._CondorDAGNode__job.cache_dir, "%s.cache" % self.get_name())
		self.add_var_opt("input-cache", self.cache_name)

	def add_input_cache(self, cache):
		self.cache.extend(cache)

	def add_file_arg(self, filename):
		raise NotImplementedError

	def write_input_files(self, *args):
		pipeline.CondorDAGNode.write_input_files(self, *args)
		f = file(self.cache_name, "w")
		for c in self.cache:
			print >>f, str(c)

	def get_output_cache(self):
		return self.cache

	def get_output_files(self):
		raise NotImplementedError

	def get_output(self):
		raise NotImplementedError


class BinjfindJob(pipeline.CondorDAGJob):
	def __init__(self, config_parser):
		pipeline.CondorDAGJob.__init__(self, "vanilla", get_executable(config_parser, "ligolw_binjfind"))
		self.set_sub_file("ligolw_binjfind.sub")
		self.set_stdout_file(os.path.join(get_out_dir(config_parser), "ligolw_binjfind-$(cluster)-$(process).out"))
		self.set_stderr_file(os.path.join(get_out_dir(config_parser), "ligolw_binjfind-$(cluster)-$(process).err"))
		self.add_condor_cmd("getenv", "True")
		self.add_ini_opts(config_parser, "ligolw_binjfind")


class BinjfindNode(pipeline.CondorDAGNode):
	def __init__(self, *args):
		pipeline.CondorDAGNode.__init__(self, *args)
		self.cache = []

	def add_input_cache(self, cache):
		self.cache.extend(cache)
		for c in cache:
			filename = c.path()
			pipeline.CondorDAGNode.add_file_arg(self, filename)
			self.add_output_file(filename)

	def add_file_arg(self, filename):
		raise NotImplementedError

	def get_output_cache(self):
		return self.cache

	def get_output_files(self):
		raise NotImplementedError

	def get_output(self):
		raise NotImplementedError


class BurcaJob(pipeline.CondorDAGJob):
	def __init__(self, config_parser):
		pipeline.CondorDAGJob.__init__(self, "vanilla", get_executable(config_parser, "ligolw_burca"))
		self.set_sub_file("ligolw_burca.sub")
		self.set_stdout_file(os.path.join(get_out_dir(config_parser), "ligolw_burca-$(cluster)-$(process).out"))
		self.set_stderr_file(os.path.join(get_out_dir(config_parser), "ligolw_burca-$(cluster)-$(process).err"))
		self.add_condor_cmd("getenv", "True")
		self.add_ini_opts(config_parser, "ligolw_burca")


class BurcaNode(pipeline.CondorDAGNode):
	def __init__(self, *args):
		pipeline.CondorDAGNode.__init__(self, *args)
		self.cache = []

	def add_input_cache(self, cache):
		self.cache.extend(cache)
		for c in cache:
			filename = c.path()
			pipeline.CondorDAGNode.add_file_arg(self, filename)
			self.add_output_file(filename)

	def add_file_arg(self, filename):
		raise NotImplementedError

	def get_output_cache(self):
		return self.cache

	def get_output_files(self):
		raise NotImplementedError

	def get_output(self):
		raise NotImplementedError


#
# =============================================================================
#
#                                DAG Job Types
#
# =============================================================================
#


#
# This is *SUCH* a hack I don't know where to begin.  Please, shoot me.
#


datafindjob = None
binjjob = None
powerjob = None
lladdjob = None
binjfindjob = None
bucutjob = None
buclusterjob = None
burcajob = None


def init_job_types(config_parser, types = ["datafind", "binj", "power", "lladd", "binjfind", "bucluster", "bucut", "burca"]):
	"""
	Construct definitions of the submit files.
	"""
	global datafindjob, binjjob, powerjob, lladdjob, binjfindjob, buclusterjob, llb2mjob, bucutjob, burcajob

	# LSCdataFind
	if "datafind" in types:
		datafindjob = pipeline.LSCDataFindJob(get_cache_dir(config_parser), get_out_dir(config_parser), config_parser)

	# lalapps_binj
	if "binj" in types:
		binjjob = BurstInjJob(config_parser)

	# lalapps_power
	if "power" in types:
		powerjob = PowerJob(config_parser)

	# ligolw_add
	if "lladd" in types:
		lladdjob = pipeline.LigolwAddJob(get_out_dir(config_parser), config_parser)
		lladdjob.cache_dir = get_cache_dir(config_parser)

	# ligolw_binjfind
	if "binjfind" in types:
		binjfindjob = BinjfindJob(config_parser)
		binjfindjob.parents_per_binjfind = get_parents_per_binjfind(config_parser)

	# ligolw_bucut
	if "bucut" in types:
		bucutjob = BucutJob(config_parser)
		bucutjob.parents_per_bucut = get_parents_per_bucut(config_parser)

	# ligolw_bucluster
	if "bucluster" in types:
		buclusterjob = BuclusterJob(config_parser)
		buclusterjob.parents_per_bucluster = get_parents_per_bucluster(config_parser)
		buclusterjob.cache_dir = get_cache_dir(config_parser)

	# ligolw_burca
	if "burca" in types:
		burcajob = BurcaJob(config_parser)


#
# =============================================================================
#
#                                 Segmentation
#
# =============================================================================
#


def psds_from_job_length(powerjob, t):
	"""
	Return the number of PSDs that can fit into a job of length t
	seconds.  In general, the return value is a non-integer.
	"""
	if t < 0.0:
		raise ValueError, t
	return (t - 2 * powerjob.filter_corruption - powerjob.psd_overlap) / (powerjob.psd_length - powerjob.psd_overlap)


def job_length_from_psds(powerjob, psds):
	"""
	From the analysis parameters and a count of PSDs, return the length
	of the job in seconds.
	"""
	if psds < 1:
		raise ValueError, psds
	return psds * (powerjob.psd_length - powerjob.psd_overlap) + powerjob.psd_overlap + 2 * powerjob.filter_corruption


def split_segment(powerjob, segment, psds_per_job):
	"""
	Split the data segment into correctly-overlaping segments.  We try
	to have the numbers of PSDs in each segment be equal to
	psds_per_job, but with a short segment at the end if needed.
	"""
	joblength = job_length_from_psds(powerjob, psds_per_job)
	joboverlap = 2 * powerjob.filter_corruption + powerjob.psd_overlap

	segs = segments.segmentlist()
	t = segment[0]
	while t + joblength <= segment[1]:
		segs.append(segments.segment(t, t + joblength) & segment)
		t += joblength - joboverlap

	extra_psds = int(psds_from_job_length(powerjob, float(segment[1] - t)))
	if extra_psds:
		segs.append(segments.segment(t, t + job_length_from_psds(powerjob, extra_psds)))
	return segs


def segment_ok(powerjob, segment):
	"""
	Return True if the segment can be analyzed using lalapps_power.
	"""
	return psds_from_job_length(powerjob, float(abs(segment))) >= 1.0


#
# =============================================================================
#
#                            Single Node Fragments
#
# =============================================================================
#


datafind_pad = 512


def make_datafind_fragment(dag, instrument, seg):
	node = pipeline.LSCDataFindNode(datafindjob)
	node.set_name("LSCdataFind-%s-%s-%s" % (instrument, int(seg[0]), int(abs(seg))))
	node.set_start(seg[0] - datafind_pad)
	node.set_end(seg[1] + 1)
	# FIXME: argh, shoot me, I need the node to know what instrument
	# it's for, but can't call set_ifo() because that adds a
	# --channel-name command line argument
	node._AnalysisNode__ifo = instrument
	node.set_observatory(instrument[0])
	if node.get_type() == None:
		node.set_type(datafindjob.get_config_file().get("datafind", "type_%s" % instrument))
	node.set_post_script(datafindjob.get_config_file().get("condor", "LSCdataFindcheck") + " --dagman-return $RETURN --stat --gps-start-time %s --gps-end-time %s %s" % (str(seg[0]), str(seg[1]), node.get_output()))
	dag.add_node(node)
	return [node]


def make_lladd_fragment(dag, parents, instrument, seg, tag, preserves = []):
	node = LigolwAddNode(lladdjob)
	node.set_name("lladd_%s_%s_%s_%s" % (instrument, tag, int(seg[0]), int(abs(seg))))
	for parent in parents:
		node.add_parent(parent)
		node.add_input_cache(parent.get_output_cache())
	node.add_preserve_cache(preserves)
	dag.add_node(node)
	# NOTE:  code that calls this generally requires a single node to
	# be returned;  if this behaviour changes, check and fix all
	# calling codes.
	return [node]


def make_power_fragment(dag, parents, instrument, seg, tag, framecache, injargs = {}):
	node = PowerNode(powerjob)
	node.set_name("lalapps_power_%s_%s_%s_%s" % (instrument, tag, int(seg[0]), int(abs(seg))))
	map(node.add_parent, parents)
	node.set_cache(framecache)
	node.set_ifo(instrument)
	node.set_start(seg[0])
	node.set_end(seg[1])
	node.set_user_tag(tag)
	for arg, value in injargs.iteritems():
		# this is a hack, but I can't be bothered
		node.add_var_arg("--%s %s" % (arg, value))
	dag.add_node(node)
	return [node]


def make_binj_fragment(dag, seg, tag, offset, flow, fhigh):
	# determine frequency ratio from number of injections across band
	# (take a bit off to allow fhigh to be picked up despite round-off
	# errors)
	fratio = 0.9999999 * (fhigh / flow) ** (1.0 / binjjob.injection_bands)

	# one injection every time-step / pi seconds, taking
	# injection_bands steps across the frequency range, this is how
	# often the sequence "repeats"
	period = binjjob.injection_bands * float(binjjob.get_opts()["time-step"]) / math.pi

	# adjust start time to be commensurate with injection period
	start = seg[0] - seg[0] % period + period * offset

	node = BurstInjNode(binjjob)
	node.set_start(start)
	node.set_end(seg[1])
	node.set_name("lalapps_binj_%d_%d" % (int(start), int(flow)))
	node.set_user_tag(tag)
	node.add_macro("macroflow", flow)
	node.add_macro("macrofhigh", fhigh)
	node.add_macro("macrofratio", fratio)
	node.add_macro("macroseed", int(time.time() + start))
	dag.add_node(node)
	return [node]


def make_binjfind_fragment(dag, parents, tag):
	parents = list(parents)
	nodes = []
	while parents:
		node = BinjfindNode(binjfindjob)
		node.set_name("ligolw_binjfind_%s_%d" % (tag, len(nodes)))
		for i in xrange(min(binjfindjob.parents_per_binjfind, len(parents))):
			parent = parents.pop()
			node.add_parent(parent)
			node.add_input_cache(parent.get_output_cache())
		node.add_macro("macrocomment", tag)
		dag.add_node(node)
		nodes.append(node)
	return nodes


def make_bucluster_fragment(dag, parents, instrument, seg, tag):
	parents = list(parents)
	nodes = []
	while parents:
		node = BuclusterNode(buclusterjob)
		node.set_name("ligolw_bucluster_%s_%s_%d_%d_%d" % (instrument, tag, int(seg[0]), int(abs(seg)), len(nodes)))
		for i in xrange(min(buclusterjob.parents_per_bucluster, len(parents))):
			parent = parents.pop()
			node.add_parent(parent)
			node.add_input_cache(parent.get_output_cache())
		node.add_macro("macrocomment", tag)
		dag.add_node(node)
		nodes.append(node)
	return nodes


def make_bucut_fragment(dag, parents, tag):
	parents = list(parents)
	nodes = []
	while parents:
		node = BucutNode(bucutjob)
		node.set_name("ligolw_bucut_%s_%d" % (tag, len(nodes)))
		for i in xrange(min(bucutjob.parents_per_bucut, len(parents))):
			parent = parents.pop()
			node.add_parent(parent)
			node.add_input_cache(parent.get_output_cache())
		node.add_macro("macrocomment", tag)
		dag.add_node(node)
		nodes.append(node)
	return nodes


def make_burca_fragment(dag, parents, instrument, seg, tag):
	node = BurcaNode(burcajob)
	node.set_name("ligolw_burca_%s_%s_%d_%d" % (instrument, tag, int(seg[0]), int(abs(seg))))
	for parent in parents:
		node.add_parent(parent)
		node.add_input_cache(parent.get_output_cache())
	node.add_macro("macrocomment", tag)
	dag.add_node(node)
	return [node]


#
# =============================================================================
#
#         DAG Fragment Combining Multiple lalapps_binj With ligolw_add
#
# =============================================================================
#


def make_multibinj_fragment(dag, seg, tag):
	flow = float(powerjob.get_opts()["low-freq-cutoff"])
	fhigh = flow + float(powerjob.get_opts()["bandwidth"])

	nodes = make_binj_fragment(dag, seg, tag, 0.0, flow, fhigh)
	nodes = make_lladd_fragment(dag, nodes, "ALL", seg, tag)
	nodes[0].set_output("HL-%s-%d-%d.xml" % (tag, int(seg[0]), int(abs(seg))))
	return nodes


#
# =============================================================================
#
#             Analyze A Segment Using Multiple lalapps_power Jobs
#
# =============================================================================
#


#
# Without injections
#


def make_power_segment_fragment(dag, datafindnodes, instrument, segment, tag, psds_per_job, verbose = False):
	"""
	Construct a DAG fragment for an entire segment, splitting the
	segment into multiple power jobs.
	"""
	if len(datafindnodes) != 1:
		raise ValueError, "must set exactly one datafind parent per power job, got %d" % len(datafindnodes)
	framecache = datafindnodes[0].get_output()
	seglist = split_segment(powerjob, segment, psds_per_job)
	if verbose:
		print >>sys.stderr, "Segment split: " + str(seglist)
	nodes = []
	for seg in seglist:
		nodes += make_power_fragment(dag, datafindnodes, instrument, seg, tag, framecache)
	return nodes


#
# With injections
#


def make_injection_segment_fragment(dag, datafindnodes, binjnodes, instrument, segment, tag, psds_per_job, verbose = False):
	if len(datafindnodes) != 1:
		raise ValueError, "must set exactly one datafind parent per power job, got %d" % len(datafindnodes)
	framecache = datafindnodes[0].get_output()
	if len(binjnodes) != 1:
		raise ValueError, "must set exactly one binj parent per power job, got %d" % len(binjnodes)
	simfile = binjnodes[0].get_output_cache()[0].path()
	seglist = split_segment(powerjob, segment, psds_per_job)
	if verbose:
		print >>sys.stderr, "Injections split: " + str(seglist)
	nodes = []
	for seg in seglist:
		nodes += make_power_fragment(dag, datafindnodes + binjnodes, instrument, seg, tag, framecache, injargs = {"burstinjection-file": simfile})
	return nodes


#
# =============================================================================
#
#              Combine a group of trigger files with clustering
#
# =============================================================================
#


def make_lladded_bucluster_fragment(dag, parents, segment, tag):
	# make first-pass bucluster jobs (these are no-ops on files that
	# don't contain sngl_burst tables).

	nodes = make_bucluster_fragment(dag, parents, "ALL", segment, tag)

	# make ligolw_add job.

	nodes = make_lladd_fragment(dag, nodes, "ALL", segment, tag)

	# set the output

	nodes[0].set_output("ALL-%s-%s-%s.xml.gz" % (tag, int(segment[0]), int(abs(segment))))

	# add second-pass clustering

	return make_bucluster_fragment(dag, nodes, "ALL", segment, "%s_POSTLLADD" % tag)


#
# =============================================================================
#
#       The Coincidence Fragment:  bucluster + lladd + bucluster + burca
#
# =============================================================================
#


def make_coinc_fragment(dag, parents, segment, tag, time_slides_filename, binjnodes = []):
	# cache for extra files to include in next ligolw_add

	extra_cache = [CacheEntry(None, None, None, "file://localhost" + os.path.abspath(filename)) for filename in [time_slides_filename]]
	for binj in binjnodes:
		extra_cache += binj.get_output_cache()

	# cache for files that should not be deleted in the event that
	# --remove-input is set.  assume all input files are shared between
	# this and other branches of the DAG, and should not be deleted

	preserve_cache = list(extra_cache)
	for node in parents:
		preserve_cache += node.get_output_cache()

	# make ligolw_add job.  assume all input files are shared between
	# this and other branches of the DAG, and should not be deleted in
	# the event that --remove-input is set

	nodes = make_lladd_fragment(dag, parents, "ALL", segment, "%s_PREBURCA" % tag, preserves = preserve_cache)

	# add the extra files to the input cache

	nodes[0].add_input_cache(extra_cache)

	# set the output

	nodes[0].set_output("ALL-%s-%s-%s.xml.gz" % (tag, int(segment[0]), int(abs(segment))))

	# run ligolw_burca

	return make_burca_fragment(dag, nodes, "ALL", segment, tag)

