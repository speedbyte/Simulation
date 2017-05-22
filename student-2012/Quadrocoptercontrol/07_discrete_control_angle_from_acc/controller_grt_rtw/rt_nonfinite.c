/*
 * rt_nonfinite.c
 *
 * Real-Time Workshop code generation for Simulink model "controller.mdl".
 *
 * Model Version              : 1.41
 * Real-Time Workshop version : 7.4  (R2009b)  29-Jun-2009
 * C source code generated on : Sat Oct 23 23:09:29 2010
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 *
 */

/*
 * Abstract:
 *      Real-Time Workshop function to intialize non-finites,
 *      (Inf, NaN and -Inf).
 */
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include "rtGetInf.h"

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
boolean_T rtIsInf(real_T value)
{
  return ((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
boolean_T rtIsInfF(real32_T value)
{
  return(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
boolean_T rtIsNaN(real_T value)
{

#if defined(_MSC_VER) && (_MSC_VER <= 1200)

  /* For MSVC 6.0, use a compiler specific comparison function */
  return _isnan(value)? 1U:0U;

#else

  return((value!=value) ? 1U : 0U);

#endif

}

/* Test if single-precision value is not a number */
boolean_T rtIsNaNF(real32_T value)
{

#if defined(_MSC_VER) && (_MSC_VER <= 1200)

  /* For MSVC 6.0, use a compiler specific comparison function */
  return _isnan((real_T)value)? 1U:0U;

#else

  return((value!=value) ? 1U : 0U);

#endif

}

/* end rt_nonfinite.c */
