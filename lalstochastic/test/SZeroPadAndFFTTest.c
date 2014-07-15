/*
*  Copyright (C) 2007 Jolien Creighton, John Whelan
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
 * \author UTB Relativity Group; contact john.whelan@ligo.org
 * \file
 * \ingroup ZeroPadAndFFT_c
 *
 * \brief Test suite for <tt>LALSZeroPadAndFFT()</tt>.
 *
 * ### Usage ###
 *
 * \code
 * ./SZeroPadAndFFTTest
 * Options:
 * -h             print usage message
 * -q             quiet: run silently
 * -v             verbose: print extra information
 * -d level       set lalDebugLevel to level
 * -i filename    read time series from file filename
 * -o filename    print frequency series to file filename
 * -n length      input & output series contain length points
 * -m             measure plan
 * \endcode
 *
 * ### Description ###
 *
 * This program tests the routine <tt>LALSZeroPadAndFFT()</tt>, which
 * zero-pads and Fourier transforms a real time series of length \f$N\f$ to
 * produce a complex frequency series of length \f$[M/2]+1\f$.
 *
 * First, it tests that the correct error codes
 * (cf. \ref StochasticCrossCorrelation_h)
 * are generated for the following error conditions (tests in
 * \e italics are not performed if \c LAL_NDEBUG is set, as
 * the corresponding checks in the code are made using the ASSERT macro):
 * <ul>
 * <li> <em>null pointer to output series</em></li>
 * <li> <em>null pointer to input series</em></li>
 * <li> <em>null pointer to parameter structure</em></li>
 * <li> <em>null pointer to FFT plan</em></li>
 * <li> <em>null pointer to data member of window function</em></li>
 * <li> <em>null pointer to data member of output series</em></li>
 * <li> <em>null pointer to data member of input series</em></li>
 * <li> <em>null pointer to data member of data member of input series</em></li>
 * <li> <em>null pointer to data member of data member of output series</em></li>
 * <li> <em>zero length</em></li>
 * <li> <em>negative time spacing</em></li>
 * <li> <em>zero time spacing</em></li>
 * <li> negative heterodyning frequency</li>
 * <li> positive heterodyning frequency</li>
 * <li> length mismatch between input series and window function</li>
 * <li> length mismatch between output series and zero-padded data</li>
 * <li> output series shorter than input series</li>
 * </ul>
 *
 * It then verifies that the correct frequency series
 * is generated for the simple test case
 * \f$\{h[k]=1+k|k=0,\ldots,7\}\f$ with \f$\delta t=0.5\,\textrm{s}\f$
 * and rectangular windowing.
 * [Note: The values are compared to a series generated by Matlab, correcting for the
 * differing sign convention.]
 * For each
 * successful test (both of these valid data and the invalid ones
 * described above), it prints "\c PASS" to standard output; if a
 * test fails, it prints "\c FAIL".
 *
 * If the \c filename arguments are present, it also reads a time
 * series from a file, calls <tt>LALSZeroPadAndFFT()</tt>, and writes the
 * results to the specified output file.
 *
 * ### Uses ###
 *
 * \code
 * LALSZeroPadAndFFT()
 * LALCheckMemoryLeaks()
 * LALSReadTimeSeries()
 * LALCPrintFrequencySeries()
 * LALCCreateVector()
 * LALCDestroyVector()
 * LALSCreateVector()
 * LALSDestroyVector()
 * LALCHARCreateVector()
 * LALCHARDestroyVector()
 * LALCreateForwardRealFFTPlan()
 * LALDestroyRealFFTPlan()
 * XLALUnitAsString()
 * XLALUnitCompare()
 * getopt()
 * printf()
 * fprintf()
 * freopen()
 * fabs()
 * \endcode
 *
 * ### Notes ###
 *
 * <ul>
 * <li> No specific error checking is done on user-specified data.  If
 * \c length is missing, the resulting default will cause a bad
 * data error.</li>
 * <li> The length of the user-provided series must be specified, even
 * though it could in principle be deduced from the input file, because
 * the data sequences must be allocated before the
 * <tt>LALSReadTimeSeries()</tt> function is called.</li>
 * <li> If one \c filename argument, but not both, is present,
 * the user-specified data will be silently ignored.</li>
 * </ul>
 *
 */

/**\name Error Codes */ /*@{*/
#define SZEROPADANDFFTTESTC_ENOM 0	/**< Nominal exit */
#define SZEROPADANDFFTTESTC_EARG 1	/**< Error parsing command-line arguments */
#define SZEROPADANDFFTTESTC_ECHK 2	/**< Error checking failed to catch bad data */
#define SZEROPADANDFFTTESTC_EFLS 3	/**< Incorrect answer for valid data */
#define SZEROPADANDFFTTESTC_EUSE 4	/**< Bad user-entered data */
/*@}*/

/** \cond DONT_DOXYGEN */
#define SZEROPADANDFFTTESTC_MSGENOM "Nominal exit"
#define SZEROPADANDFFTTESTC_MSGEARG "Error parsing command-line arguments"
#define SZEROPADANDFFTTESTC_MSGECHK "Error checking failed to catch bad data"
#define SZEROPADANDFFTTESTC_MSGEFLS "Incorrect answer for valid data"
#define SZEROPADANDFFTTESTC_MSGEUSE "Bad user-entered data"


#include <lal/LALStdlib.h>
#include <lal/Window.h>

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <config.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

#include <lal/StochasticCrossCorrelation.h>
#include <lal/AVFactories.h>
#include <lal/ReadFTSeries.h>
#include <lal/PrintFTSeries.h>
#include <lal/Units.h>

#include "CheckStatus.h"

#define SZEROPADANDFFTTESTC_LENGTH        8
#define SZEROPADANDFFTTESTC_FULLLENGTH (2 * SZEROPADANDFFTTESTC_LENGTH - 1)
#define SZEROPADANDFFTTESTC_EPOCHSEC      1234
#define SZEROPADANDFFTTESTC_EPOCHNS       56789
#define SZEROPADANDFFTTESTC_DELTAT        0.5
#define SZEROPADANDFFTTESTC_DELTAF 1.0/(SZEROPADANDFFTTESTC_FULLLENGTH * SZEROPADANDFFTTESTC_DELTAT)
#if LAL_CUDA_ENABLED
#define SZEROPADANDFFTTESTC_TOL           1e-5
#else
#define SZEROPADANDFFTTESTC_TOL           1e-6
#endif

#define SZEROPADANDFFTTESTC_TRUE     1
#define SZEROPADANDFFTTESTC_FALSE    0

extern char *optarg;
extern int   optind;

BOOLEAN optVerbose = SZEROPADANDFFTTESTC_FALSE;
BOOLEAN optMeasurePlan = SZEROPADANDFFTTESTC_FALSE;
UINT4 optLength    = 0;


CHAR optInputFile[LALNameLength] = "";
CHAR optOutputFile[LALNameLength] = "";
INT4 code;

static void
Usage (const char *program, int exitflag);

static void
ParseOptions (int argc, char *argv[]);

/*
 * ADDED -- JC
 * going to need to modify fields of RealFFTPlan...
 * don't try this at home!
 */
/* Actually, we don't need it -- JTW
struct tagRealFFTPlan
{
  INT4  sign;
  UINT4 size;
  void* junk;
};
*/
int
main( int argc, char *argv[] )
{

   static LALStatus         status;

   UINT4      i;
   REAL8      f;


   const REAL4    testInputDataData[SZEROPADANDFFTTESTC_LENGTH]
                     = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

   COMPLEX8 expectedOutputDataData[SZEROPADANDFFTTESTC_LENGTH]
                     = {crectf(+3.600000000000000e+01, 0.0),
                        crectf(-1.094039137097177e+01, -2.279368601990178e+01),
                        crectf(+3.693524635113721e-01, +9.326003289238411e+00),
                        crectf(-8.090169943749448e-01, -7.918722831227928e+00),
                        crectf(+3.502214272222959e-01, +5.268737078678177e+00),
                        crectf(+5.329070518200751e-15, -5.196152422706625e+00),
                        crectf(+3.090169943749475e-01, +4.306254604896173e+00),
                        crectf(+2.208174802380956e-01, -4.325962305777781e+00)};

   REAL4TimeSeries             goodInput;
   COMPLEX8FrequencySeries     goodOutput;

   int                    result;
   LALUnit                expectedUnit;
   CHAR                   unitString[LALUnitTextSize];

   SZeroPadAndFFTParameters   goodParams;


   goodParams.window = NULL;
   goodParams.fftPlan = NULL;
   goodParams.length = SZEROPADANDFFTTESTC_FULLLENGTH;

   /* build window */
   goodParams.window = XLALCreateRectangularREAL4Window(SZEROPADANDFFTTESTC_LENGTH);
#ifndef LAL_NDEBUG
   SZeroPadAndFFTParameters badParams = goodParams;
#endif

   /* Fill in expected output */

   for (i=0; i<SZEROPADANDFFTTESTC_LENGTH; ++i)
   {
     expectedOutputDataData[i] *= SZEROPADANDFFTTESTC_DELTAT;
   }

   ParseOptions( argc, argv );

   /* TEST INVALID DATA HERE ------------------------------------------- */

   /* define valid parameters */
   goodInput.f0                   = 0.0;
   goodInput.deltaT               = SZEROPADANDFFTTESTC_DELTAT;
   goodInput.epoch.gpsSeconds     = SZEROPADANDFFTTESTC_EPOCHSEC;
   goodInput.epoch.gpsNanoSeconds = SZEROPADANDFFTTESTC_EPOCHNS;
   goodInput.data                 = NULL;
   goodOutput.data                = NULL;

#ifndef LAL_NDEBUG
   REAL4TimeSeries badInput = goodInput;
   COMPLEX8FrequencySeries badOutput = goodOutput;
#endif

   /* construct plan */
   LALCreateForwardRealFFTPlan(&status, &(goodParams.fftPlan),
			       SZEROPADANDFFTTESTC_FULLLENGTH,
			       SZEROPADANDFFTTESTC_FALSE);
   if ( ( code = CheckStatus( &status, 0 , "",
			      SZEROPADANDFFTTESTC_EFLS,
			      SZEROPADANDFFTTESTC_MSGEFLS ) ) )
   {
     return code;
   }
   /* allocate input and output vectors */
   LALSCreateVector(&status, &(goodInput.data), SZEROPADANDFFTTESTC_LENGTH);
   if ( ( code = CheckStatus( &status, 0 , "",
			      SZEROPADANDFFTTESTC_EFLS,
			      SZEROPADANDFFTTESTC_MSGEFLS ) ) )
   {
     return code;
   }
   LALCCreateVector(&status, &(goodOutput.data), SZEROPADANDFFTTESTC_LENGTH);
   if ( ( code = CheckStatus( &status, 0 , "",
			      SZEROPADANDFFTTESTC_EFLS,
			      SZEROPADANDFFTTESTC_MSGEFLS ) ) )
   {
     return code;
   }

#ifndef LAL_NDEBUG
   if ( ! lalNoDebug )
   {
     /* test behavior for null pointer to output series */
     LALSZeroPadAndFFT(&status, NULL, &goodInput, &goodParams);
     if ( ( code = CheckStatus( &status, STOCHASTICCROSSCORRELATIONH_ENULLPTR,
				STOCHASTICCROSSCORRELATIONH_MSGENULLPTR,
				SZEROPADANDFFTTESTC_ECHK,
				SZEROPADANDFFTTESTC_MSGECHK ) ) )
     {
       return code;
     }
     printf("  PASS: null pointer to output series results in error:\n       \"%s\"\n", STOCHASTICCROSSCORRELATIONH_MSGENULLPTR);

     /* test behavior for null pointer to input series */
     LALSZeroPadAndFFT(&status, &goodOutput, NULL, &goodParams);
     if ( ( code = CheckStatus( &status, STOCHASTICCROSSCORRELATIONH_ENULLPTR,
				STOCHASTICCROSSCORRELATIONH_MSGENULLPTR,
				SZEROPADANDFFTTESTC_ECHK,
				SZEROPADANDFFTTESTC_MSGECHK ) ) )
     {
       return code;
     }
     printf("  PASS: null pointer to input series results in error:\n       \"%s\"\n", STOCHASTICCROSSCORRELATIONH_MSGENULLPTR);

     /* test behavior for null pointer to parameter structure */
     LALSZeroPadAndFFT(&status, &goodOutput, &goodInput, NULL);
     if ( ( code = CheckStatus( &status, STOCHASTICCROSSCORRELATIONH_ENULLPTR,
				STOCHASTICCROSSCORRELATIONH_MSGENULLPTR,
				SZEROPADANDFFTTESTC_ECHK,
				SZEROPADANDFFTTESTC_MSGECHK ) ) )
     {
       return code;
     }
     printf("  PASS: null pointer to parameter structure results in error:\n       \"%s\"\n", STOCHASTICCROSSCORRELATIONH_MSGENULLPTR);

     /* test behavior for null pointer to FFT plan */
     badParams.fftPlan = NULL;
     LALSZeroPadAndFFT(&status, &goodOutput, &goodInput, &badParams);
     if ( ( code = CheckStatus( &status, STOCHASTICCROSSCORRELATIONH_ENULLPTR,
				STOCHASTICCROSSCORRELATIONH_MSGENULLPTR,
				SZEROPADANDFFTTESTC_ECHK,
				SZEROPADANDFFTTESTC_MSGECHK ) ) )
     {
       return code;
     }
     printf("  PASS: null pointer to FFT plan results in error:\n       \"%s\"\n", STOCHASTICCROSSCORRELATIONH_MSGENULLPTR);
     badParams.fftPlan = goodParams.fftPlan;

     /* test behavior for null pointer to data member of output series */
     LALSZeroPadAndFFT(&status, &badOutput, &goodInput, &goodParams);
     if ( ( code = CheckStatus( &status, STOCHASTICCROSSCORRELATIONH_ENULLPTR,
				STOCHASTICCROSSCORRELATIONH_MSGENULLPTR,
				SZEROPADANDFFTTESTC_ECHK,
				SZEROPADANDFFTTESTC_MSGECHK ) ) )
     {
       return code;
     }
     printf("  PASS: null pointer to data member of output series results in error:\n       \"%s\"\n", STOCHASTICCROSSCORRELATIONH_MSGENULLPTR);

     /* test behavior for null pointer to data member of input series */
     LALSZeroPadAndFFT(&status, &goodOutput, &badInput, &goodParams);
     if ( ( code = CheckStatus( &status, STOCHASTICCROSSCORRELATIONH_ENULLPTR,
				STOCHASTICCROSSCORRELATIONH_MSGENULLPTR,
				SZEROPADANDFFTTESTC_ECHK,
				SZEROPADANDFFTTESTC_MSGECHK ) ) )
     {
       return code;
     }
     printf("  PASS: null pointer to data member of input series results in error:\n       \"%s\"\n", STOCHASTICCROSSCORRELATIONH_MSGENULLPTR);

     /* test behavior for null pointer to data member of data member of output series */
     LALCCreateVector(&status, &(badOutput.data), SZEROPADANDFFTTESTC_LENGTH);
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }
     COMPLEX8                *cPtr;
     cPtr = badOutput.data->data;
     badOutput.data->data = NULL;
     LALSZeroPadAndFFT(&status, &badOutput, &goodInput, &goodParams);
     if ( ( code = CheckStatus( &status, STOCHASTICCROSSCORRELATIONH_ENULLPTR,
				STOCHASTICCROSSCORRELATIONH_MSGENULLPTR,
				SZEROPADANDFFTTESTC_ECHK,
				SZEROPADANDFFTTESTC_MSGECHK ) ) )
     {
       return code;
     }
     printf("  PASS: null pointer to data member of data member of output series results in error:\n       \"%s\"\n", STOCHASTICCROSSCORRELATIONH_MSGENULLPTR);
     badOutput.data->data = cPtr;
     LALCDestroyVector(&status, &(badOutput.data));
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }

     /* test behavior for null pointer to data member of data member of output series */
     LALSCreateVector(&status, &(badInput.data), SZEROPADANDFFTTESTC_LENGTH);
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }
     REAL4                   *sPtr;
     sPtr = badInput.data->data;
     badInput.data->data = NULL;
     LALSZeroPadAndFFT(&status, &goodOutput, &badInput, &goodParams);
     if ( ( code = CheckStatus( &status, STOCHASTICCROSSCORRELATIONH_ENULLPTR,
				STOCHASTICCROSSCORRELATIONH_MSGENULLPTR,
				SZEROPADANDFFTTESTC_ECHK,
				SZEROPADANDFFTTESTC_MSGECHK ) ) )
     {
       return code;
     }
     printf("  PASS: null pointer to data member of data member of input series results in error:\n       \"%s\"\n", STOCHASTICCROSSCORRELATIONH_MSGENULLPTR);
     badInput.data->data = sPtr;
     LALSDestroyVector(&status, &(badInput.data));
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }

     /* test behavior for zero length */
     goodInput.data->length = goodOutput.data->length = 0;
     /* plan->size = -1; */
     LALSZeroPadAndFFT(&status, &goodOutput, &goodInput, &goodParams);
     if ( ( code = CheckStatus(&status, STOCHASTICCROSSCORRELATIONH_EZEROLEN,
			       STOCHASTICCROSSCORRELATIONH_MSGEZEROLEN,
			       SZEROPADANDFFTTESTC_ECHK,
			       SZEROPADANDFFTTESTC_MSGECHK) ) )
     {
       return code;
     }
     printf("  PASS: zero length results in error:\n       \"%s\"\n",
            STOCHASTICCROSSCORRELATIONH_MSGEZEROLEN);
     /* reassign valid length */
     goodInput.data->length = goodOutput.data->length
       = SZEROPADANDFFTTESTC_LENGTH;
     /* plan->size = SZEROPADANDFFTTESTC_FULLLENGTH; */

     /* test behavior for negative time spacing */
     goodInput.deltaT = -SZEROPADANDFFTTESTC_DELTAT;
     LALSZeroPadAndFFT(&status, &goodOutput, &goodInput, &goodParams);
     if ( ( code = CheckStatus(&status,
			       STOCHASTICCROSSCORRELATIONH_ENONPOSDELTAT,
			       STOCHASTICCROSSCORRELATIONH_MSGENONPOSDELTAT,
			       SZEROPADANDFFTTESTC_ECHK,
			       SZEROPADANDFFTTESTC_MSGECHK) ) )
     {
       return code;
     }
     printf("  PASS: negative time spacing results in error:\n       \"%s\"\n",
            STOCHASTICCROSSCORRELATIONH_MSGENONPOSDELTAT);

     /* test behavior for zero time spacing */
     goodInput.deltaT = 0;
     LALSZeroPadAndFFT(&status, &goodOutput, &goodInput, &goodParams);
     if ( ( code = CheckStatus(&status,
			       STOCHASTICCROSSCORRELATIONH_ENONPOSDELTAT,
			       STOCHASTICCROSSCORRELATIONH_MSGENONPOSDELTAT,
			       SZEROPADANDFFTTESTC_ECHK,
			       SZEROPADANDFFTTESTC_MSGECHK) ) )
     {
       return code;
     }
     printf("  PASS: zero time spacing results in error:\n       \"%s\"\n",
            STOCHASTICCROSSCORRELATIONH_MSGENONPOSDELTAT);
     /* reassign valid time spacing */
     goodInput.deltaT = SZEROPADANDFFTTESTC_DELTAT;

   } /* if ( ! lalNoDebug ) */
#endif /* NDEBUG */

   /* test behavior for negative heterodyning frequency */
   goodInput.f0 = -100.0;
   LALSZeroPadAndFFT(&status, &goodOutput, &goodInput, &goodParams);
   if ( ( code = CheckStatus(&status,
			     STOCHASTICCROSSCORRELATIONH_ENONZEROHETERO,
			     STOCHASTICCROSSCORRELATIONH_MSGENONZEROHETERO,
			     SZEROPADANDFFTTESTC_ECHK,
			     SZEROPADANDFFTTESTC_MSGECHK) ) )
   {
     return code;
   }
   printf("  PASS: negative heterodyning frequency results in error:\n       \"%s\"\n",
            STOCHASTICCROSSCORRELATIONH_MSGENONZEROHETERO);
   /* test behavior for positive heterodyning frequency */
   goodInput.f0 = 100.0;
   LALSZeroPadAndFFT(&status, &goodOutput, &goodInput, &goodParams);
   if ( ( code = CheckStatus(&status,
			     STOCHASTICCROSSCORRELATIONH_ENONZEROHETERO,
			     STOCHASTICCROSSCORRELATIONH_MSGENONZEROHETERO,
			     SZEROPADANDFFTTESTC_ECHK,
			     SZEROPADANDFFTTESTC_MSGECHK) ) )
   {
     return code;
   }
   printf("  PASS: positive heterodyning frequency results in error:\n       \"%s\"\n",
          STOCHASTICCROSSCORRELATIONH_MSGENONZEROHETERO);
   goodInput.f0 = 0.0;

   /* test behavior for length mismatch between input series and output series */
   goodOutput.data->length = SZEROPADANDFFTTESTC_LENGTH + 1;
   LALSZeroPadAndFFT(&status, &goodOutput, &goodInput, &goodParams);
   if ( ( code = CheckStatus(&status,
			     STOCHASTICCROSSCORRELATIONH_EMMLEN,
			     STOCHASTICCROSSCORRELATIONH_MSGEMMLEN,
			     SZEROPADANDFFTTESTC_ECHK,
			     SZEROPADANDFFTTESTC_MSGECHK) ) )
   {
     return code;
   }
   printf("  PASS: length mismatch between input series and output series results in error:\n       \"%s\"\n",
          STOCHASTICCROSSCORRELATIONH_MSGEMMLEN);
   goodOutput.data->length = SZEROPADANDFFTTESTC_LENGTH;

   /* TEST VALID DATA HERE --------------------------------------------- */

   /* fill input time-series parameters */
   strncpy(goodInput.name,"Dummy test data",LALNameLength);
   goodInput.sampleUnits  = lalDimensionlessUnit;
   goodInput.sampleUnits.unitNumerator[LALUnitIndexADCCount] = 1;

     /* fill input time-series data */
   for (i=0; i<SZEROPADANDFFTTESTC_LENGTH; ++i)
   {
     goodInput.data->data[i] = testInputDataData[i];
   }

   /* zero-pad and FFT */
   LALSZeroPadAndFFT(&status, &goodOutput, &goodInput, &goodParams);
   if ( ( code = CheckStatus( &status, 0 , "",
			      SZEROPADANDFFTTESTC_EFLS,
			      SZEROPADANDFFTTESTC_MSGEFLS) ) )
   {
     return code;
   }

   /* check output f0 */
   if (optVerbose)
   {
     printf("f0=%g, should be 0\n", goodOutput.f0);
   }
   if (goodOutput.f0)
   {
     printf("  FAIL: Valid data test\n");
     if (optVerbose)
     {
       printf("Exiting with error: %s\n", SZEROPADANDFFTTESTC_MSGEFLS);
     }
     return SZEROPADANDFFTTESTC_EFLS;
   }

   /* check output deltaF */
   if (optVerbose)
   {
     printf("deltaF=%g, should be %g\n", goodOutput.deltaF,
            SZEROPADANDFFTTESTC_DELTAF);
   }
   if ( fabs(goodOutput.deltaF-SZEROPADANDFFTTESTC_DELTAF)
        / SZEROPADANDFFTTESTC_DELTAF > SZEROPADANDFFTTESTC_TOL )
   {
     printf("  FAIL: Valid data test\n");
     if (optVerbose)
     {
       printf("Exiting with error: %s\n", SZEROPADANDFFTTESTC_MSGEFLS);
     }
     return SZEROPADANDFFTTESTC_EFLS;
   }

   /* check output epoch */
   if (optVerbose)
   {
     printf("epoch=%d seconds, %d nanoseconds; should be %d seconds, %d nanoseconds\n",
            goodOutput.epoch.gpsSeconds, goodOutput.epoch.gpsNanoSeconds,
            SZEROPADANDFFTTESTC_EPOCHSEC, SZEROPADANDFFTTESTC_EPOCHNS);
   }
   if ( goodOutput.epoch.gpsSeconds != SZEROPADANDFFTTESTC_EPOCHSEC
        || goodOutput.epoch.gpsNanoSeconds != SZEROPADANDFFTTESTC_EPOCHNS )
   {
     printf("  FAIL: Valid data test\n");
     if (optVerbose)
     {
       printf("Exiting with error: %s\n", SZEROPADANDFFTTESTC_MSGEFLS);
     }
     return SZEROPADANDFFTTESTC_EFLS;
   }

   /* check output units */
   expectedUnit = lalDimensionlessUnit;
   expectedUnit.unitNumerator[LALUnitIndexADCCount] = 1;
   expectedUnit.unitNumerator[LALUnitIndexSecond] = 1;
   result = XLALUnitCompare(&expectedUnit, &(goodOutput.sampleUnits));
   if (optVerbose)
   {
     if ( XLALUnitAsString( unitString, LALUnitTextSize, &(goodOutput.sampleUnits)) == NULL ) {
       return SZEROPADANDFFTTESTC_EFLS;
     }
     printf( "Units are \"%s\", ", unitString );
     if ( XLALUnitAsString( unitString, LALUnitTextSize, &expectedUnit) == NULL ) {
       return SZEROPADANDFFTTESTC_EFLS;
     }
     printf( "should be \"%s\"\n", unitString );
   }

   if (result != 0)
   {
     printf("  FAIL: Valid data test #1\n");
     if (optVerbose)
     {
       printf("Exiting with error: %s\n",
              SZEROPADANDFFTTESTC_MSGEFLS);
     }
     return SZEROPADANDFFTTESTC_EFLS;
   }

   /* check output values */
   if (optVerbose)
   {
     printf("hBarTilde(0)=%g + %g i, should be %g\n",
            crealf(goodOutput.data->data[0]), cimagf(goodOutput.data->data[0]),
            crealf(expectedOutputDataData[0]));
   }
   if ( fabs(crealf(goodOutput.data->data[0]) - crealf(expectedOutputDataData[0]))
        /* / expectedOutputDataData[0].re */> SZEROPADANDFFTTESTC_TOL
        || fabs(cimagf(goodOutput.data->data[0])) > SZEROPADANDFFTTESTC_TOL )
   {
     printf("  FAIL: Valid data test\n");
     if (optVerbose)
       {
         printf("Exiting with error: %s\n", SZEROPADANDFFTTESTC_MSGEFLS);
       }
     return SZEROPADANDFFTTESTC_EFLS;
   }

   for (i=1; i<SZEROPADANDFFTTESTC_LENGTH; ++i)
   {
     f = i * SZEROPADANDFFTTESTC_DELTAF;
     if (optVerbose)
     {
       printf("hBarTilde(%f Hz)=%g + %g i, should be %g + %g i\n",
              f, crealf(goodOutput.data->data[i]), cimagf(goodOutput.data->data[i]),
              crealf(expectedOutputDataData[i]), cimagf(expectedOutputDataData[i]));
     }
     if (fabs(crealf(goodOutput.data->data[i]) - crealf(expectedOutputDataData[i]))
         /* / expectedOutputDataData[0].re */> SZEROPADANDFFTTESTC_TOL
         || fabs(cimagf(goodOutput.data->data[i]) - cimagf(expectedOutputDataData[i]))
         /* / expectedOutputDataData[0].re */> SZEROPADANDFFTTESTC_TOL)
     {
       printf("  FAIL: Valid data test\n");
       if (optVerbose)
       {
         printf("Exiting with error: %s\n", SZEROPADANDFFTTESTC_MSGEFLS);
       }
       return SZEROPADANDFFTTESTC_EFLS;
     }
   }

    /* write results to output file
   LALSPrintTimeSeries(&input, "zeropadgoodInput.dat");
   LALCPrintFrequencySeries(&output, "zeropadgoodOutput.dat");*/

   /* clean up valid data */
   LALSDestroyVector(&status, &goodInput.data);
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
   {
     return code;
   }
   LALCDestroyVector(&status, &goodOutput.data);
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
   {
     return code;
   }
   LALDestroyRealFFTPlan(&status, &(goodParams.fftPlan));
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
   {
     return code;
   }
   XLALDestroyREAL4Window(goodParams.window);

   LALCheckMemoryLeaks();

   printf("PASS: all tests\n");

   /**************** Process User-Entered Data, If Any **************/

   /* ::TODO:: Fix this with length and window type to be specified */

   if (optInputFile[0] && optOutputFile[0]){
     /* construct plan*/
     LALCreateForwardRealFFTPlan(&status, &(goodParams.fftPlan), 2*optLength - 1,
				   optMeasurePlan);
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }

     goodInput.data  = NULL;
     goodOutput.data = NULL;

     LALSCreateVector(&status, &goodInput.data, optLength);
     if ( ( code = CheckStatus( &status, 0 , "",
				SZEROPADANDFFTTESTC_EUSE,
				SZEROPADANDFFTTESTC_MSGEUSE) ) )
     {
       return code;
     }
     LALCCreateVector(&status, &goodOutput.data, optLength);
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }

     /* Read input file */
     LALSReadTimeSeries(&status, &goodInput, optInputFile);
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }

     /* calculate zero-pad and FFT */
     LALSZeroPadAndFFT(&status, &goodOutput, &goodInput, &goodParams);
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }

     LALCPrintFrequencySeries(&goodOutput, optOutputFile);

     printf("===== FFT of Zero-Padded User-Specified Data Written to File %s =====\n", optOutputFile);

     /* clean up valid data */
     LALSDestroyVector(&status, &goodInput.data);
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }
     LALCDestroyVector(&status, &goodOutput.data);
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }
     LALDestroyRealFFTPlan(&status, &(goodParams.fftPlan));
     if ( ( code = CheckStatus(&status, 0 , "",
			       SZEROPADANDFFTTESTC_EFLS,
			       SZEROPADANDFFTTESTC_MSGEFLS) ) )
     {
       return code;
     }
     LALCheckMemoryLeaks();
   }
   return SZEROPADANDFFTTESTC_ENOM;
}

/*------------------------------------------------------------------------*/

/*
 * Usage ()
 *
 * Prints a usage message for program program and exits with code exitcode.
 *
 */
static void
Usage (const char *program, int exitcode)
{
  fprintf (stderr, "Usage: %s [options]\n", program);
  fprintf (stderr, "Options:\n");
  fprintf (stderr, "  -h             print this message\n");
  fprintf (stderr, "  -q             quiet: run silently\n");
  fprintf (stderr, "  -v             verbose: print extra information\n");
  fprintf (stderr, "  -d level       set lalDebugLevel to level\n");
  fprintf (stderr, "  -i filename    read time series from file filename\n");
  fprintf (stderr, "  -o filename    print frequency series to file filename\n");
  fprintf (stderr, "  -n length      input & output series contain length points\n");
  fprintf (stderr, "  -m             measure plan\n");
  exit (exitcode);
}


/*
 * ParseOptions ()
 *
 * Parses the argc - 1 option strings in argv[].
 *
 */
static void
ParseOptions (int argc, char *argv[])
{
  FILE *fp;

  while (1)
  {
    int c = -1;

    c = getopt (argc, argv, "hqvd:i:o:n:m");
    if (c == -1)
    {
      break;
    }

    switch (c)
    {
      case 'i': /* specify input file */
        strncpy (optInputFile, optarg, LALNameLength);
        break;

      case 'o': /* specify output file */
        strncpy (optOutputFile, optarg, LALNameLength);
        break;

      case 'n': /* specify number of points in series */
        optLength = atoi (optarg);
        break;

      case 'm': /* specify whether or not to measure plan */
        optMeasurePlan = SZEROPADANDFFTTESTC_TRUE;
        break;

      case 'd': /* set debug level */
        break;

      case 'v': /* optVerbose */
        optVerbose = SZEROPADANDFFTTESTC_TRUE;
        break;

      case 'q': /* quiet: run silently (ignore error messages) */
        fp = freopen ("/dev/null", "w", stderr);
        if (fp == NULL)
        {
          fprintf(stderr, "Error: Unable to open /dev/null\n");
          exit(1);
        }
        fp = freopen ("/dev/null", "w", stdout);
        if (fp == NULL)
        {
          fprintf(stderr, "Error: Unable to open /dev/null\n");
          exit(1);
        }
        break;

      case 'h':
        Usage (argv[0], 0);
        break;


      default:
        Usage (argv[0], 1);
    }

  }

  if (optind < argc)
  {
    Usage (argv[0], 1);
  }

  return;
}

/** \endcond */
