#ifdef __GNUC__
#define UNUSED __attribute__ ((unused))
#else
#define UNUSED
#endif

#ifndef _LALSIM_RINGDOWN_MMRDNS_H
#define _LALSIM_RINGDOWN_MMRDNS_H


/* ************************************************************  */
/*
 * Copyright (C) 2016 Lionel London
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with with program; see the file COPYING. If not, write to the
 *  Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 */

 #if defined(__cplusplus)
 extern "C" {
 #elif 0
 } /* so that editors will match preceding brace */
 #endif

/* Include the desired Libs */
#include <stdbool.h>
#include <math.h>
#include <complex.h>
/* LAL specific libs  */

#include <lal/Date.h>
#include <lal/FrequencySeries.h>
#include <lal/Units.h>

#include <lal/LALDatatypes.h>
#include <lal/LALStdlib.h>
#include <lal/LALSimInspiral.h>
#include <lal/LALSimIMR.h>
#include <lal/LALConfig.h>
#include <lal/LALConstants.h>

#include <lal/LALConstants.h>
#include <lal/LALStdio.h>
#include <lal/LALSimSphHarmSeries.h>
#include <lal/LALStdlib.h>
#include <lal/LALSimInspiral.h>

#include <lal/TimeSeries.h>
#include <lal/FrequencySeries.h>

/* ---------------------------------------- */
/* General model methods and parameters     */
/* ---------------------------------------- */

/* Gnerate Time domain ringdown waveform  */
UNUSED int XLALSimRingdownMMRDNSTD(
        UNUSED REAL8TimeSeries **hplus,        /**< OUTPUT h_+ vector */
        UNUSED REAL8TimeSeries **hcross,       /**< OUTPUT h_x vector */
        UNUSED REAL8 phiRef,                   /**< orbital phase at reference pt. */
        UNUSED REAL8 inclination,              /**< inclination angle */
        UNUSED REAL8 deltaT,                   /**< sampling interval (s) */
        UNUSED REAL8 m1,                       /**< mass of companion 1 (kg) */
        UNUSED REAL8 m2,                       /**< mass of companion 2 (kg) */
        UNUSED REAL8 r,                        /**< distance of source (m) */
        UNUSED const LALSimInspiralTestGRParam *extraParams /**< linked list containing the extra testing GR parameters */
        );

/* XLALSimRingdownSingleModeTD: Time domain waveformgenerator for single QNM without angular dependence (i.e. this function generates multipole moments only ). In  */
UNUSED int XLALSimRingdownGenerateSingleModeTD(
  UNUSED COMPLEX16TimeSeries **hk,        /**< OUTPUT vector for QNM time series */
  UNUSED const LIGOTimeGPS T0,            /**< Start time  */
  UNUSED REAL8 deltaT,                    /**< sampling interval (s) */
  UNUSED REAL8 Nsamples,                  /**< Number of time domain samples */
  UNUSED complex double Ak,               /**< COMPLEX QNM Strain Amplitude */
  UNUSED complex double CWk               /**< COMPLEX QNM Frequency */
);

/* XLALSimRingdownMMRDNSFD: Frequency domain waveformgenerator for all QNM with angular dependence */
int XLALSimRingdownMMRDNSFD(
        COMPLEX16FrequencySeries **hptilde,          /**< OUTPUT FD h_+ polarization */
        COMPLEX16FrequencySeries **hctilde,          /**< OUTPUT FD h_x polarization */
        const REAL8 deltaF,                          /**< Frequency resolution (Hz) */
        const REAL8 fStart,                          /**< Start GW frequency (Hz) */
        const REAL8 fEnd,                            /**< Highest GW frequency (Hz) */
        REAL8 Mf,                                    /**< Final BH Mass (solar mass) */
        REAL8 jf,                                    /**< Final BH dimensionaless spin */
        REAL8 eta,                                   /**< Symmetric mass ratio of two companions */
        REAL8 iota,                                  /**< inclination angle (in rad) */
        REAL8 phi,                                   /**< azimuthal angle (in rad) */
        REAL8 r,                                     /**< distance of source (m) */
        LALSimInspiralTestGRParam *nonGRparams       /**< testing GR parameters */
);

/* XLALSimRingdownGenerateSingleModeFD: Frequency domain waveformgenerator for single QNM with angular dependence */
int XLALSimRingdownGenerateSingleModeFD(
      COMPLEX16FrequencySeries **hptilde_lmn,      /**< OUTPUT FD h_+ polarization */
      COMPLEX16FrequencySeries **hctilde_lmn,      /**< OUTPUT FD h_x polarization */
      const REAL8 deltaF,                          /**< Frequency resolution (Hz) */
      const REAL8 fStart,                          /**< Start GW frequency (Hz) */
      const REAL8 fEnd,                            /**< Highest GW frequency (Hz) */
      REAL8 Mf,                                    /**< Final BH Mass (solar mass) */
      REAL8 jf,                                    /**< Final BH dimensionaless spin */
      REAL8 eta,                                   /**< Symmetric mass ratio of two companions */
      REAL8 iota,                                  /**< inclination angle */
      REAL8 phi,                                   /**< azimuthal angle */
      UINT4 l,                                     /**< Polar eigenvalue */
      UINT4 m,                                     /**< Azimuthal eigenvalue */
      UINT4 n,                                     /**< Overtone Number */
      REAL8 r,                                     /**< distance of source (m) */
      REAL8 dfreq,                                 /**< relative shift in the real frequency parameter */
      REAL8 dtau                                   /**< relative shift in the damping time parameter */
);

/* Convert NR Code Time to Physical Units */
//UNUSED static double XLALNRtoPhysTime( UNUSED double NRtime  );

/* ************************************************************  */
#endif	/* of #ifndef _LALSIM_RINGDOWN_MMRDNS_H */
