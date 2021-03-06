/*
*  Copyright (C) 2007 Jolien Creighton, Tania Regimbau
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


/**
 * \author Tania Regimbau, Sukanta Bose, Jeff Noel
 * \defgroup StochasticMC_h Header StochasticMC.h
 * \ingroup lalstochastic_general
 *
 * \brief Routine used by the stochastic DSO to do software injection.
 *
 * ### Synopsis ###
 *
 * \code
 * #include <lal/StochasticMC.h>
 * \endcode
 *
 * @{
 */

#ifndef _STOCHASTICMC_H
#define _STOCHASTICMC_H

#include <lal/LALStdlib.h>
#include <lal/DetectorSite.h>
#include <lal/Units.h>
#include <lal/Calibration.h>
#include <lal/SimulateSB.h>

#ifdef  __cplusplus
extern "C" {
#endif

/**\name Error Codes */ /*@{*/
#define STOCHASTICMCH_ENULLP        1	/**< Null pointer */
#define STOCHASTICMCH_ENULLLEN      2	/**< Negative or zero length for data member of time series */
#define STOCHASTICMCH_ENULLSEG      3	/**< Negative or zero number of segment */
#define STOCHASTICMCH_ENULLSRATE    4	/**< Negative or zero sampling rate */
#define STOCHASTICMCH_ENEGFMIN      5	/**< negative start frequency */
#define STOCHASTICMCH_EMMEPOCH      6	/**< Mismatch in epochs */
#define STOCHASTICMCH_EMMUNITS      7	/**< Mismatch in units */
/*@}*/

/** \cond DONT_DOXYGEN */
#define STOCHASTICMCH_MSGENULLP       "Null pointer"
#define STOCHASTICMCH_MSGENULLLEN     "Negative or zero length for data member of time series"
#define STOCHASTICMCH_MSGENULLSEG      "Negative or zero number of segment"
#define STOCHASTICMCH_MSGENULLSRATE    "Negative or zero sampling rate"
#define STOCHASTICMCH_MSGENEGFMIN      "negative start frequency"
#define STOCHASTICMCH_MSGEMMEPOCH      "Mismatch in epochs"
#define STOCHASTICMCH_MSGEMMUNITS      "Mismatch in units"
/** \endcond */

  typedef struct tagStochasticMCInput {
    CalibrationFunctions         calfuncs1;
    CalibrationFunctions         calfuncs2 ;
    CalibrationUpdateParams      calfacts1;
    CalibrationUpdateParams      calfacts2 ;
  } StochasticMCInput;

  typedef struct tagStochasticMCSInput {
      CHAR *ifo1;
      CHAR *ifo2;
      CHAR *catalog1;
      CHAR *catalog2;
  } StochasticMCSInput;

  typedef struct tagStochasticMCParams {
    UINT4 lengthseg;
    UINT4 numseg;
    REAL8 sRate;
    INT4  starttime;
    INT4  seed;
    REAL8 fRef;
    REAL8 f0;
    REAL8 omegaRef;
    REAL8 alpha;
    INT4 site1;
    INT4 site2;

  } StochasticMCParams;



 void
 LALStochasticMCDso( LALStatus                  *status,
		  SSSimStochBGOutput         *output,
		  StochasticMCInput          *input,
		  StochasticMCParams         *params );

 void LALStochasticMCDsoSplice (LALStatus *status,
     SSSimStochBGOutput *MCoutput,
     StochasticMCInput  *MCinput,
     StochasticMCParams *MCparams);

/** @} */

#ifdef  __cplusplus
}
#endif

#endif /* _STOCHASTICMC_H */
