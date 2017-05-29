/*
 * Quadcopter_sf.c
 *
 * Code generation for model "Quadcopter_sf".
 *
 * Model version              : 1.19
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Mon May 22 16:48:09 2017
 *
 * Target selection: rtwsfcn.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include <math.h>
#include "Quadcopter_sf.h"
#include "Quadcopter_sf_private.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

extern void *Quadcopter_malloc(SimStruct *S);

#endif

#ifndef __RTW_UTFREE__
#if defined (MATLAB_MEX_FILE)

extern void * utMalloc(size_t);
extern void utFree(void *);

#endif
#endif                                 /* #ifndef __RTW_UTFREE__ */

#if defined(MATLAB_MEX_FILE)
#include "rt_nonfinite.c"
#endif

static const char_T *RT_MEMORY_ALLOCATION_ERROR =
  "memory allocation error in generated S-Function";

/* Start for root system: '<Root>' */
#define MDL_START

static void mdlStart(SimStruct *S)
{
  /* instance underlying S-Function data */
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#  if defined(MATLAB_MEX_FILE)

  /* non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* Check for invalid switching between solver types */
  if (!ssIsVariableStepSolver(S)) {
    ssSetErrorStatus(S, "This Simulink Coder generated "
                     "S-Function cannot be used in a simulation with "
                     "a solver type of fixed-step "
                     "because this S-Function was created from a model with "
                     "solver type of variable-step solver and it has continuous time blocks. "
                     "See the Solver page of the simulation parameters dialog.");
    return;
  }

#  endif

  Quadcopter_malloc(S);
  if (ssGetErrorStatus(S) != (NULL) ) {
    return;
  }

#endif

  {
  }
}

/* Outputs for root system: '<Root>' */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  real_T rtb_Sum2;
  real_T rtb_Sum2_b;
  real_T rtb_Sum4;
  real_T rtb_Sum4_h;
  P_Quadcopter_T *_rtP;
  _rtP = ((P_Quadcopter_T *) ssGetLocalDefaultParam(S));
  if (1) {
    /* Sum: '<S2>/Sum2' incorporates:
     *  Inport: '<Root>/Altitude Correction'
     *  Inport: '<Root>/Psi Correction'
     */
    rtb_Sum2 = *((const real_T **)ssGetInputPortSignalPtrs(S, 3))[0] - *((const
      real_T **)ssGetInputPortSignalPtrs(S, 2))[0];

    /* Sum: '<S3>/Sum2' incorporates:
     *  Inport: '<Root>/Altitude Correction'
     *  Inport: '<Root>/Psi Correction'
     */
    rtb_Sum2_b = *((const real_T **)ssGetInputPortSignalPtrs(S, 3))[0] - *((
      const real_T **)ssGetInputPortSignalPtrs(S, 2))[0];

    /* Switch: '<S1>/Switch' incorporates:
     *  Constant: '<S1>/Quad Model Type Logical'
     */
    if (_rtP->quadModel.plusConfig != 0.0) {
      /* Outport: '<Root>/mc1' incorporates:
       *  Inport: '<Root>/Theta Correction'
       *  Sum: '<S2>/Sum1'
       */
      ((real_T *)ssGetOutputPortSignal(S, 0))[0] = rtb_Sum2 - *((const real_T **)
        ssGetInputPortSignalPtrs(S, 1))[0];
    } else {
      /* Outport: '<Root>/mc1' incorporates:
       *  Inport: '<Root>/Phi Correction'
       *  Inport: '<Root>/Theta Correction'
       *  Sum: '<S3>/Sum1'
       *  Sum: '<S3>/Sum5'
       */
      ((real_T *)ssGetOutputPortSignal(S, 0))[0] = (rtb_Sum2_b - *((const real_T
        **)ssGetInputPortSignalPtrs(S, 0))[0]) - *((const real_T **)
        ssGetInputPortSignalPtrs(S, 1))[0];
    }

    /* End of Switch: '<S1>/Switch' */

    /* Sum: '<S2>/Sum4' incorporates:
     *  Inport: '<Root>/Altitude Correction'
     *  Inport: '<Root>/Psi Correction'
     */
    rtb_Sum4 = *((const real_T **)ssGetInputPortSignalPtrs(S, 2))[0] + *((const
      real_T **)ssGetInputPortSignalPtrs(S, 3))[0];

    /* Sum: '<S3>/Sum4' incorporates:
     *  Inport: '<Root>/Altitude Correction'
     *  Inport: '<Root>/Psi Correction'
     */
    rtb_Sum4_h = *((const real_T **)ssGetInputPortSignalPtrs(S, 2))[0] + *((
      const real_T **)ssGetInputPortSignalPtrs(S, 3))[0];

    /* Switch: '<S1>/Switch' incorporates:
     *  Constant: '<S1>/Quad Model Type Logical'
     *  Switch: '<S1>/Switch'
     */
    if (_rtP->quadModel.plusConfig != 0.0) {
      /* Outport: '<Root>/mc2' incorporates:
       *  Inport: '<Root>/Phi Correction'
       *  Sum: '<S2>/Sum8'
       */
      ((real_T *)ssGetOutputPortSignal(S, 1))[0] = rtb_Sum4 + *((const real_T **)
        ssGetInputPortSignalPtrs(S, 0))[0];

      /* Outport: '<Root>/mc3' incorporates:
       *  Inport: '<Root>/Theta Correction'
       *  Sum: '<S2>/Sum3'
       */
      ((real_T *)ssGetOutputPortSignal(S, 2))[0] = *((const real_T **)
        ssGetInputPortSignalPtrs(S, 1))[0] + rtb_Sum2;

      /* Outport: '<Root>/mc4' incorporates:
       *  Inport: '<Root>/Phi Correction'
       *  Sum: '<S2>/Sum11'
       */
      ((real_T *)ssGetOutputPortSignal(S, 3))[0] = rtb_Sum4 - *((const real_T **)
        ssGetInputPortSignalPtrs(S, 0))[0];
    } else {
      /* Outport: '<Root>/mc2' incorporates:
       *  Inport: '<Root>/Phi Correction'
       *  Inport: '<Root>/Theta Correction'
       *  Sum: '<S3>/Sum'
       *  Sum: '<S3>/Sum3'
       */
      ((real_T *)ssGetOutputPortSignal(S, 1))[0] = (*((const real_T **)
        ssGetInputPortSignalPtrs(S, 0))[0] + rtb_Sum4_h) - *((const real_T **)
        ssGetInputPortSignalPtrs(S, 1))[0];

      /* Outport: '<Root>/mc3' incorporates:
       *  Inport: '<Root>/Phi Correction'
       *  Inport: '<Root>/Theta Correction'
       *  Sum: '<S3>/Sum6'
       *  Sum: '<S3>/Sum8'
       */
      ((real_T *)ssGetOutputPortSignal(S, 2))[0] = (rtb_Sum2_b + *((const real_T
        **)ssGetInputPortSignalPtrs(S, 0))[0]) + *((const real_T **)
        ssGetInputPortSignalPtrs(S, 1))[0];

      /* Outport: '<Root>/mc4' incorporates:
       *  Inport: '<Root>/Phi Correction'
       *  Inport: '<Root>/Theta Correction'
       *  Sum: '<S3>/Sum11'
       *  Sum: '<S3>/Sum7'
       */
      ((real_T *)ssGetOutputPortSignal(S, 3))[0] = (rtb_Sum4_h - *((const real_T
        **)ssGetInputPortSignalPtrs(S, 0))[0]) + *((const real_T **)
        ssGetInputPortSignalPtrs(S, 1))[0];
    }

    /* End of Switch: '<S1>/Switch' */
  }

  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE

static void mdlUpdate(SimStruct *S, int_T tid)
{
  UNUSED_PARAMETER(tid);
}

/* Termination for root system: '<Root>' */
static void mdlTerminate(SimStruct *S)
{

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

  if (ssGetUserData(S) != (NULL) ) {
    rt_FREE(ssGetLocalBlockIO(S));
  }

  rt_FREE(ssGetUserData(S));

#endif

}

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#  include "Quadcopter_mid.h"
#endif

/* Function to initialize sizes. */
static void mdlInitializeSizes(SimStruct *S)
{
  ssSetNumSampleTimes(S, 2);           /* Number of sample times */
  ssSetNumContStates(S, 0);            /* Number of continuous states */
  ssSetNumNonsampledZCs(S, 0);         /* Number of nonsampled ZCs */
  ssSetZCCacheNeedsReset(S, 0);
  ssSetDerivCacheNeedsReset(S, 0);

  /* Number of output ports */
  if (!ssSetNumOutputPorts(S, 4))
    return;

  /* outport number: 0 */
  if (!ssSetOutputPortMatrixDimensions(S, 0, 1, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 0, 0.0);
  ssSetOutputPortOffsetTime(S, 0, 0.0);
  ssSetOutputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);

  /* outport number: 1 */
  if (!ssSetOutputPortMatrixDimensions(S, 1, 1, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 1, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 1, 0.0);
  ssSetOutputPortOffsetTime(S, 1, 0.0);
  ssSetOutputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);

  /* outport number: 2 */
  if (!ssSetOutputPortMatrixDimensions(S, 2, 1, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 2, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 2, 0.0);
  ssSetOutputPortOffsetTime(S, 2, 0.0);
  ssSetOutputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);

  /* outport number: 3 */
  if (!ssSetOutputPortMatrixDimensions(S, 3, 1, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 3, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 3, 0.0);
  ssSetOutputPortOffsetTime(S, 3, 0.0);
  ssSetOutputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);

  /* Number of input ports */
  if (!ssSetNumInputPorts(S, 4))
    return;

  /* inport number: 0 */
  {
    if (!ssSetInputPortMatrixDimensions(S, 0, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 0, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortSampleTime(S, 0, 0.0);
    ssSetInputPortOffsetTime(S, 0, 0.0);
    ssSetInputPortOverWritable(S, 0, 0);
    ssSetInputPortOptimOpts(S, 0, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 1 */
  {
    if (!ssSetInputPortMatrixDimensions(S, 1, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 1, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortSampleTime(S, 1, 0.0);
    ssSetInputPortOffsetTime(S, 1, 0.0);
    ssSetInputPortOverWritable(S, 1, 0);
    ssSetInputPortOptimOpts(S, 1, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 2 */
  {
    if (!ssSetInputPortMatrixDimensions(S, 2, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 2, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 2, 1);
    ssSetInputPortSampleTime(S, 2, 0.0);
    ssSetInputPortOffsetTime(S, 2, 0.0);
    ssSetInputPortOverWritable(S, 2, 0);
    ssSetInputPortOptimOpts(S, 2, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 3 */
  {
    if (!ssSetInputPortMatrixDimensions(S, 3, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 3, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 3, 1);
    ssSetInputPortSampleTime(S, 3, 0.0);
    ssSetInputPortOffsetTime(S, 3, 0.0);
    ssSetInputPortOverWritable(S, 3, 0);
    ssSetInputPortOptimOpts(S, 3, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  ssSetRTWGeneratedSFcn(S, 1);         /* Generated S-function */

  /* Tunable Parameters */
  ssSetNumSFcnParams(S, 0);

  /* Number of expected parameters */
#if defined(MATLAB_MEX_FILE)

  if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {

#if defined(MDL_CHECK_PARAMETERS)

    mdlCheckParameters(S);

#endif                                 /* MDL_CHECK_PARAMETERS */

    if (ssGetErrorStatus(S) != (NULL) ) {
      return;
    }
  } else {
    return;                            /* Parameter mismatch will be reported by Simulink */
  }

#endif                                 /* MATLAB_MEX_FILE */

  /* Options */
  ssSetOptions(S, (SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE |
                   SS_OPTION_PORT_SAMPLE_TIMES_ASSIGNED ));

#if SS_SFCN_FOR_SIM

  {
    ssSupportsMultipleExecInstances(S, true);
    ssHasStateInsideForEachSS(S, false);
  }

#endif

}

/* Function to initialize sample times. */
static void mdlInitializeSampleTimes(SimStruct *S)
{
  /* task periods */
  ssSetSampleTime(S, 0, 0.0);
  ssSetSampleTime(S, 1, 0.0);

  /* task offsets */
  ssSetOffsetTime(S, 0, 0.0);
  ssSetOffsetTime(S, 1, 1.0);
}

#if defined(MATLAB_MEX_FILE)
# include "fixedpoint.c"
# include "simulink.c"
#else
# undef S_FUNCTION_NAME
# define S_FUNCTION_NAME               Quadcopter_sf
# include "cg_sfun.h"
#endif                                 /* defined(MATLAB_MEX_FILE) */
