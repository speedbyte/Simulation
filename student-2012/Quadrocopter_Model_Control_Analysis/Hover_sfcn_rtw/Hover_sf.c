/*
 * Hover_sf.c
 *
 * Real-Time Workshop code generation for Simulink model "Hover_sf.mdl".
 *
 * Model version              : 1.351
 * Real-Time Workshop version : 7.5  (R2010a)  25-Jan-2010
 * C source code generated on : Thu Apr 21 15:37:39 2011
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
#include "Hover_sf.h"
#include "Hover_sf_private.h"
#include "simstruc.h"
#include "fixedpoint.h"

/* Named constants for Stateflow: '<Root>/Hover Mode Enable' */
#define Hover_IN_Hovering              (1U)
#define Hover_IN_NotHovering           (2U)
#define Hover_IN_WaitForBodyCtrl       (3U)
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

extern void *Hover_malloc(SimStruct *S);

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
  "memory allocation error in RTW generated S-Function";

/* Initial conditions for root system: '<Root>' */
#define MDL_INITIALIZE_CONDITIONS

static void mdlInitializeConditions(SimStruct *S)
{
  /* InitializeConditions for Stateflow: '<Root>/Hover Mode Enable' */
  ((uint8_T *)ssGetDWork(S, 4))[0] = 0U;
  ((uint8_T *)ssGetDWork(S, 5))[0] = 0U;
  ((BlockIO_Hover *) ssGetLocalBlockIO(S))->Control = 0.0;
  ((real_T *)ssGetDWork(S, 1))[0] = 0.0;
  ((real_T *)ssGetDWork(S, 2))[0] = 0.0;
  ((real_T *)ssGetDWork(S, 3))[0] = 0.0;
}

/* Enable for root system: '<Root>' */
#define RTW_GENERATED_ENABLE

static void mdlEnable(SimStruct *S)
{
  /* Enable for Stateflow: '<Root>/Hover Mode Enable' */
  ((real_T *)ssGetDWork(S, 1))[0] = ssGetTaskTime(S,0);
  ((real_T *)ssGetDWork(S, 3))[0] = ((real_T *)ssGetDWork(S, 1))[0];
}

/* Disable for root system: '<Root>' */
#define RTW_GENERATED_DISABLE

static void mdlDisable(SimStruct *S)
{
  /* Disable for Stateflow: '<Root>/Hover Mode Enable' */
  ((real_T *)ssGetDWork(S, 1))[0] = ssGetTaskTime(S,0);
  ((real_T *)ssGetDWork(S, 2))[0] = ((real_T *)ssGetDWork(S, 1))[0] - ((real_T *)
    ssGetDWork(S, 3))[0];
  ((real_T *)ssGetDWork(S, 3))[0] = ((real_T *)ssGetDWork(S, 1))[0];
  ((real_T *)ssGetDWork(S, 0))[0] = ((real_T *)ssGetDWork(S, 0))[0] + ((real_T *)
    ssGetDWork(S, 2))[0];
}

/* Start for root system: '<Root>' */
#define MDL_START

static void mdlStart(SimStruct *S)
{
  /* instance underlying S-Function data */
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#  if defined(MATLAB_MEX_FILE)

  /* non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

#  endif

  Hover_malloc(S);
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
  /* Stateflow: '<Root>/Hover Mode Enable' incorporates:
   *  Inport: '<Root>/phiSet'
   *  Inport: '<Root>/r_psiSet'
   *  Inport: '<Root>/thetaSet'
   */
  ((real_T *)ssGetDWork(S, 1))[0] = ssGetTaskTime(S,0);
  ((real_T *)ssGetDWork(S, 2))[0] = ((real_T *)ssGetDWork(S, 1))[0] - ((real_T *)
    ssGetDWork(S, 3))[0];
  ((real_T *)ssGetDWork(S, 3))[0] = ((real_T *)ssGetDWork(S, 1))[0];
  ((real_T *)ssGetDWork(S, 0))[0] = ((real_T *)ssGetDWork(S, 0))[0] + ((real_T *)
    ssGetDWork(S, 2))[0];

  /* Gateway: Hover Mode Enable */
  /* During: Hover Mode Enable */
  if (((uint8_T *)ssGetDWork(S, 4))[0] == 0) {
    /* Entry: Hover Mode Enable */
    ((uint8_T *)ssGetDWork(S, 4))[0] = 1U;

    /* Transition: '<S1>:4' */
    /* Entry 'NotHovering': '<S1>:2' */
    ((uint8_T *)ssGetDWork(S, 5))[0] = Hover_IN_NotHovering;
    ((BlockIO_Hover *) ssGetLocalBlockIO(S))->Control = 0.0;
  } else {
    switch (((uint8_T *)ssGetDWork(S, 5))[0]) {
     case Hover_IN_Hovering:
      /* During 'Hovering': '<S1>:3' */
      if (((*(((const real_T **)ssGetInputPortSignalPtrs(S, 0))[0])) <= -0.1) ||
          ((*(((const real_T **)ssGetInputPortSignalPtrs(S, 0))[0])) >= 0.1) ||
          (((*(((const real_T **)ssGetInputPortSignalPtrs(S, 1))[0])) <= -0.1) ||
           ((*(((const real_T **)ssGetInputPortSignalPtrs(S, 1))[0])) >= 0.1)) ||
          (((*(((const real_T **)ssGetInputPortSignalPtrs(S, 2))[0])) <= -0.1) ||
           ((*(((const real_T **)ssGetInputPortSignalPtrs(S, 2))[0])) >= 0.1)))
      {
        /* Transition: '<S1>:116' */
        /* Exit 'Hovering': '<S1>:3' */
        /* Entry 'NotHovering': '<S1>:2' */
        ((uint8_T *)ssGetDWork(S, 5))[0] = Hover_IN_NotHovering;
        ((BlockIO_Hover *) ssGetLocalBlockIO(S))->Control = 0.0;
      }
      break;

     case Hover_IN_NotHovering:
      /* During 'NotHovering': '<S1>:2' */
      if (((*(((const real_T **)ssGetInputPortSignalPtrs(S, 1))[0])) > -0.1) &&
          ((*(((const real_T **)ssGetInputPortSignalPtrs(S, 1))[0])) < 0.1) &&
          (((*(((const real_T **)ssGetInputPortSignalPtrs(S, 0))[0])) > -0.1) &&
           ((*(((const real_T **)ssGetInputPortSignalPtrs(S, 0))[0])) < 0.1)) &&
          (((*(((const real_T **)ssGetInputPortSignalPtrs(S, 2))[0])) > -0.1) &&
           ((*(((const real_T **)ssGetInputPortSignalPtrs(S, 2))[0])) < 0.1))) {
        /* Transition: '<S1>:12' */
        /* Exit 'NotHovering': '<S1>:2' */
        /* Entry 'WaitForBodyCtrl': '<S1>:115' */
        ((uint8_T *)ssGetDWork(S, 5))[0] = Hover_IN_WaitForBodyCtrl;
        ((real_T *)ssGetDWork(S, 0))[0] = 0.0;
        ((BlockIO_Hover *) ssGetLocalBlockIO(S))->Control = 0.0;
      }
      break;

     case Hover_IN_WaitForBodyCtrl:
      /* During 'WaitForBodyCtrl': '<S1>:115' */
      if ((ssGetTaskTime(S,0) - ((real_T *)ssGetDWork(S, 3))[0]) + ((real_T *)
           ssGetDWork(S, 0))[0] >= 1.0) {
        /* Transition: '<S1>:117' */
        /* Exit 'WaitForBodyCtrl': '<S1>:115' */
        /* Entry 'Hovering': '<S1>:3' */
        ((uint8_T *)ssGetDWork(S, 5))[0] = Hover_IN_Hovering;
        ((BlockIO_Hover *) ssGetLocalBlockIO(S))->Control = 1.0;
      } else {
        if (((*(((const real_T **)ssGetInputPortSignalPtrs(S, 0))[0])) <= -0.1) ||
            ((*(((const real_T **)ssGetInputPortSignalPtrs(S, 0))[0])) >= 0.1) ||
            (((*(((const real_T **)ssGetInputPortSignalPtrs(S, 1))[0])) <= -0.1)
             || ((*(((const real_T **)ssGetInputPortSignalPtrs(S, 1))[0])) >=
                 0.1)) || (((*(((const real_T **)ssGetInputPortSignalPtrs(S, 2))
                               [0])) <= -0.1) || ((*(((const real_T **)
                 ssGetInputPortSignalPtrs(S, 2))[0])) >= 0.1))) {
          /* Transition: '<S1>:13' */
          /* Exit 'WaitForBodyCtrl': '<S1>:115' */
          /* Entry 'NotHovering': '<S1>:2' */
          ((uint8_T *)ssGetDWork(S, 5))[0] = Hover_IN_NotHovering;
          ((BlockIO_Hover *) ssGetLocalBlockIO(S))->Control = 0.0;
        }
      }
      break;

     default:
      /* Transition: '<S1>:4' */
      /* Entry 'NotHovering': '<S1>:2' */
      ((uint8_T *)ssGetDWork(S, 5))[0] = Hover_IN_NotHovering;
      ((BlockIO_Hover *) ssGetLocalBlockIO(S))->Control = 0.0;
      break;
    }
  }

  /* Outport: '<Root>/Control' */
  ((real_T *)ssGetOutputPortSignal(S, 0))[0] = ((BlockIO_Hover *)
    ssGetLocalBlockIO(S))->Control;

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE

static void mdlUpdate(SimStruct *S, int_T tid)
{
  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
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
#  include "Hover_mid.h"
#endif

/* Function to initialize sizes. */
static void mdlInitializeSizes(SimStruct *S)
{
  ssSetNumSampleTimes(S, 1);           /* Number of sample times */
  ssSetNumContStates(S, 0);            /* Number of continuous states */
  ssSetNumNonsampledZCs(S, 0);         /* Number of nonsampled ZCs */
  ssSetZCCacheNeedsReset(S, 0);
  ssSetDerivCacheNeedsReset(S, 0);

  /* Number of output ports */
  if (!ssSetNumOutputPorts(S, 1))
    return;

  /* outport number: 0 */
  if (!ssSetOutputPortVectorDimension(S, 0, 1))
    return;
  ssSetOutputPortBusMode(S, 0, SL_NON_BUS_MODE);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 0, 0.0);
  ssSetOutputPortOffsetTime(S, 0, 1.0);
  ssSetOutputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);

  /* Number of input ports */
  if (!ssSetNumInputPorts(S, 3))
    return;

  /* inport number: 0 */
  {
    if (!ssSetInputPortVectorDimension(S, 0, 1))
      return;
    ssSetInputPortBusMode(S, 0, SL_NON_BUS_MODE);
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 0, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortSampleTime(S, 0, 0.0);
    ssSetInputPortOffsetTime(S, 0, 1.0);
    ssSetInputPortOverWritable(S, 0, 0);
    ssSetInputPortOptimOpts(S, 0, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 1 */
  {
    if (!ssSetInputPortVectorDimension(S, 1, 1))
      return;
    ssSetInputPortBusMode(S, 1, SL_NON_BUS_MODE);
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 1, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortSampleTime(S, 1, 0.0);
    ssSetInputPortOffsetTime(S, 1, 1.0);
    ssSetInputPortOverWritable(S, 1, 0);
    ssSetInputPortOptimOpts(S, 1, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 2 */
  {
    if (!ssSetInputPortVectorDimension(S, 2, 1))
      return;
    ssSetInputPortBusMode(S, 2, SL_NON_BUS_MODE);
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 2, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 2, 1);
    ssSetInputPortSampleTime(S, 2, 0.0);
    ssSetInputPortOffsetTime(S, 2, 1.0);
    ssSetInputPortOverWritable(S, 2, 0);
    ssSetInputPortOptimOpts(S, 2, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  ssSetRTWGeneratedSFcn(S, 1);         /* RTW generated S-function */

  /* DWork */
  if (!ssSetNumDWork(S, 6)) {
    return;
  }

  /* '<Root>/Hover Mode Enable': DWORK3 */
  ssSetDWorkName(S, 0, "DWORK0");
  ssSetDWorkWidth(S, 0, 1);

  /* '<Root>/Hover Mode Enable': DWORK4 */
  ssSetDWorkName(S, 1, "DWORK1");
  ssSetDWorkWidth(S, 1, 1);

  /* '<Root>/Hover Mode Enable': DWORK5 */
  ssSetDWorkName(S, 2, "DWORK2");
  ssSetDWorkWidth(S, 2, 1);

  /* '<Root>/Hover Mode Enable': DWORK6 */
  ssSetDWorkName(S, 3, "DWORK3");
  ssSetDWorkWidth(S, 3, 1);

  /* '<Root>/Hover Mode Enable': DWORK1 */
  ssSetDWorkName(S, 4, "DWORK4");
  ssSetDWorkWidth(S, 4, 1);
  ssSetDWorkDataType(S, 4, SS_UINT8);

  /* '<Root>/Hover Mode Enable': DWORK2 */
  ssSetDWorkName(S, 5, "DWORK5");
  ssSetDWorkWidth(S, 5, 1);
  ssSetDWorkDataType(S, 5, SS_UINT8);

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

  /* task offsets */
  ssSetOffsetTime(S, 0, 1.0);
}

#if defined(MATLAB_MEX_FILE)
# include "fixedpoint.c"
# include "simulink.c"
#else
# undef S_FUNCTION_NAME
# define S_FUNCTION_NAME               Hover_sf
# include "cg_sfun.h"
#endif                                 /* defined(MATLAB_MEX_FILE) */
