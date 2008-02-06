/* constants */
#define EAH_GENERIC 0

#define EAH_OPTIMIZATION_SSE         3
#define EAH_OPTIMIZATION_ALTIVEC     2

#define EAH_SINCOS_ROUND_FLOOR       EAH_GENERIC
#define EAH_SINCOS_ROUND_MODF        1
#define EAH_SINCOS_ROUND_PLUS2       2
#define EAH_SINCOS_ROUND_INT4        4
#define EAH_SINCOS_ROUND_INT8        8

#define EAH_SINCOS_VARIANT_LAL       EAH_GENERIC
#define EAH_SINCOS_VARIANT_LINEAR    9

#define EAH_HOTLOOP_VARIANT_LAL      EAH_GENERIC
#define EAH_HOTLOOP_VARIANT_AUTOVECT 1
#define EAH_HOTLOOP_VARIANT_ALTIVEC  2
#define EAH_HOTLOOP_VARIANT_SSE      3
#define EAH_HOTLOOP_VARIANT_x87      EAH_GENERIC

#define EAH_HOUGH_PREFETCH_NONE      EAH_GENERIC
#define EAH_HOUGH_PREFETCH_DIRECT    1
#define EAH_HOUGH_PREFETCH_C         2

#define EAH_HOUGH_ASS_NONE           EAH_GENERIC
#define EAH_HOUGH_ASS_X87            7
/* #define EAH_HOUGH_BATCHSIZELD 0 /* not using it yet */

#ifndef EAH_OPTIMIZATION
#define EAH_OPTIMIZATION EAH_GENERIC
#endif

#if   EAH_OPTIMIZATION == 1 /* fastest portable code */
#define EAH_SINCOS_VARIANT  EAH_SINCOS_VARIANT_LINEAR
#define EAH_SINCOS_ROUND    EAH_SINCOS_ROUND_PLUS2
#define EAH_HOTLOOP_VARIANT EAH_HOTLOOP_VARIANT_LAL
#define EAH_HOTLOOP_RECIPROCAL /* might give it a try - on old CPUs this might give a little speedup */
#define EAH_HOUGH_PREFETCH  EAH_HOUGH_PREFETCH_NONE
#define EAH_HOUGH_ASS       EAH_HOUGH_ASS_NONE

#elif EAH_OPTIMIZATION == 2 /* AltiVec Code (currently not working) */
#define EAH_SINCOS_VARIANT  EAH_SINCOS_VARIANT_LINEAR
#define EAH_SINCOS_ROUND    EAH_SINCOS_ROUND_FLOOR
#define EAH_HOTLOOP_VARIANT EAH_HOTLOOP_VARIANT_LAL /* should be ALTIVEC, but doesn't work yet */
#define EAH_HOUGH_PREFETCH  EAH_HOUGH_PREFETCH_NONE /* should be somethig similar to ASS, but isn't there yet */
#define EAH_HOUGH_ASS       EAH_HOUGH_ASS_NONE

#elif EAH_OPTIMIZATION == 3 /* SSE code, contains assembler */
#define EAH_SINCOS_VARIANT  EAH_SINCOS_VARIANT_LINEAR
#define EAH_SINCOS_ROUND    EAH_SINCOS_ROUND_PLUS2
#define EAH_HOTLOOP_VARIANT EAH_HOTLOOP_VARIANT_SSE
#define EAH_HOUGH_PREFETCH  EAH_HOUGH_PREFETCH_DIRECT
#define EAH_HOUGH_ASS       EAH_HOUGH_ASS_X87

#elif EAH_OPTIMIZATION == 4 /* contains x87 assembler, but no SSE instructions */
#define EAH_SINCOS_VARIANT  EAH_SINCOS_VARIANT_LINEAR
#define EAH_SINCOS_ROUND    EAH_SINCOS_ROUND_PLUS2
#define EAH_HOTLOOP_VARIANT EAH_HOTLOOP_VARIANT_x87 
#define EAH_HOUGH_PREFETCH  EAH_HOUGH_PREFETCH_NONE
#define EAH_HOUGH_ASS       EAH_HOUGH_ASS_X87

#endif /* EAH_OPTIMIZATION == */


/* defaults - if they haven't been set special, set them to GENERIC */
#ifndef EAH_SINCOS_VARIANT
#define EAH_SINCOS_VARIANT  EAH_GENERIC
#endif
#ifndef EAH_SINCOS_ROUND
#define EAH_SINCOS_ROUND    EAH_GENERIC
#endif
#ifndef EAH_HOTLOOP_VARIANT
#define EAH_HOTLOOP_VARIANT EAH_GENERIC
#endif
#ifndef EAH_HOUGH_PREFETCH
#define EAH_HOUGH_PREFETCH  EAH_GENERIC
#endif
#ifndef EAH_HOUGH_ASS
#define EAH_HOUGH_ASS       EAH_GENERIC
#endif
