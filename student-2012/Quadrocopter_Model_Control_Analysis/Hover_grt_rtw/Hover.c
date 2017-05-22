/*
 * Hover.c
 *
 * Real-Time Workshop code generation for Simulink model "Hover.mdl".
 *
 * Model version              : 1.351
 * Real-Time Workshop version : 7.5  (R2010a)  25-Jan-2010
 * C source code generated on : Thu Apr 21 15:42:09 2011
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Hover.h"
#include "Hover_private.h"

/* Named constants for Stateflow: '<Root>/Hover Mode Enable' */
#define Hover_IN_Hovering              (1U)
#define Hover_IN_NotHovering           (2U)
#define Hover_IN_WaitForBodyCtrl       (3U)

/* Block signals (auto storage) */
BlockIO_Hover Hover_B;

/* Block states (auto storage) */
D_Work_Hover Hover_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_Hover Hover_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_Hover Hover_Y;

/* Real-time model */
RT_MODEL_Hover Hover_M_;
RT_MODEL_Hover *Hover_M = &Hover_M_;

/* Model output function */
static void Hover_output(int_T tid)
{
  /* Stateflow: '<Root>/Hover Mode Enable' incorporates:
   *  Inport: '<Root>/phiSet'
   *  Inport: '<Root>/r_psiSet'
   *  Inport: '<Root>/thetaSet'
   */
  Hover_DWork.presentTicks = Hover_M->Timing.clockTick0;
  Hover_DWork.elapsedTicks = Hover_DWork.presentTicks -
    Hover_DWork.previousTicks;
  Hover_DWork.previousTicks = Hover_DWork.presentTicks;
  if ((uint32_T)Hover_DWork.temporalCounter_i1 + Hover_DWork.elapsedTicks <= 7U)
  {
    Hover_DWork.temporalCounter_i1 = (uint8_T)((uint32_T)
      Hover_DWork.temporalCounter_i1 + Hover_DWork.elapsedTicks);
  } else {
    Hover_DWork.temporalCounter_i1 = 7U;
  }

  /* Gateway: Hover Mode Enable */
  /* During: Hover Mode Enable */
  if (Hover_DWork.is_active_c3_Hover == 0) {
    /* Entry: Hover Mode Enable */
    Hover_DWork.is_active_c3_Hover = 1U;

    /* Transition: '<S1>:4' */
    /* Entry 'NotHovering': '<S1>:2' */
    Hover_DWork.is_c3_Hover = Hover_IN_NotHovering;
    Hover_B.Control = 0.0;
  } else {
    switch (Hover_DWork.is_c3_Hover) {
     case Hover_IN_Hovering:
      /* During 'Hovering': '<S1>:3' */
      if ((Hover_U.phiSet <= -0.1) || (Hover_U.phiSet >= 0.1) ||
          ((Hover_U.thetaSet <= -0.1) || (Hover_U.thetaSet >= 0.1)) ||
          ((Hover_U.r_psiSet <= -0.1) || (Hover_U.r_psiSet >= 0.1))) {
        /* Transition: '<S1>:116' */
        /* Exit 'Hovering': '<S1>:3' */
        /* Entry 'NotHovering': '<S1>:2' */
        Hover_DWork.is_c3_Hover = Hover_IN_NotHovering;
        Hover_B.Control = 0.0;
      }
      break;

     case Hover_IN_NotHovering:
      /* During 'NotHovering': '<S1>:2' */
      if ((Hover_U.thetaSet > -0.1) && (Hover_U.thetaSet < 0.1) &&
          ((Hover_U.phiSet > -0.1) && (Hover_U.phiSet < 0.1)) &&
          ((Hover_U.r_psiSet > -0.1) && (Hover_U.r_psiSet < 0.1))) {
        /* Transition: '<S1>:12' */
        /* Exit 'NotHovering': '<S1>:2' */
        /* Entry 'WaitForBodyCtrl': '<S1>:115' */
        Hover_DWork.is_c3_Hover = Hover_IN_WaitForBodyCtrl;
        Hover_DWork.temporalCounter_i1 = 0U;
        Hover_B.Control = 0.0;
      }
      break;

     case Hover_IN_WaitForBodyCtrl:
      /* During 'WaitForBodyCtrl': '<S1>:115' */
      if ((uint32_T)Hover_DWork.temporalCounter_i1 >= 5U) {
        /* Transition: '<S1>:117' */
        /* Exit 'WaitForBodyCtrl': '<S1>:115' */
        /* Entry 'Hovering': '<S1>:3' */
        Hover_DWork.is_c3_Hover = Hover_IN_Hovering;
        Hover_B.Control = 1.0;
      } else {
        if ((Hover_U.phiSet <= -0.1) || (Hover_U.phiSet >= 0.1) ||
            ((Hover_U.thetaSet <= -0.1) || (Hover_U.thetaSet >= 0.1)) ||
            ((Hover_U.r_psiSet <= -0.1) || (Hover_U.r_psiSet >= 0.1))) {
          /* Transition: '<S1>:13' */
          /* Exit 'WaitForBodyCtrl': '<S1>:115' */
          /* Entry 'NotHovering': '<S1>:2' */
          Hover_DWork.is_c3_Hover = Hover_IN_NotHovering;
          Hover_B.Control = 0.0;
        }
      }
      break;

     default:
      /* Transition: '<S1>:4' */
      /* Entry 'NotHovering': '<S1>:2' */
      Hover_DWork.is_c3_Hover = Hover_IN_NotHovering;
      Hover_B.Control = 0.0;
      break;
    }
  }

  /* Outport: '<Root>/Control' */
  Hover_Y.Control = Hover_B.Control;

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
static void Hover_update(int_T tid)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Hover_M->Timing.clockTick0)) {
    ++Hover_M->Timing.clockTickH0;
  }

  Hover_M->Timing.t[0] = Hover_M->Timing.clockTick0 * Hover_M->Timing.stepSize0
    + Hover_M->Timing.clockTickH0 * Hover_M->Timing.stepSize0 * 4294967296.0;

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model initialize function */
void Hover_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Hover_M, 0,
                sizeof(RT_MODEL_Hover));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Hover_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Hover_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Hover_M->Timing.sampleTimes = (&Hover_M->Timing.sampleTimesArray[0]);
    Hover_M->Timing.offsetTimes = (&Hover_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Hover_M->Timing.sampleTimes[0] = (0.2);

    /* task offsets */
    Hover_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Hover_M, &Hover_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Hover_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Hover_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Hover_M, -1);
  Hover_M->Timing.stepSize0 = 0.2;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    Hover_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Hover_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Hover_M->rtwLogInfo, (NULL));
    rtliSetLogT(Hover_M->rtwLogInfo, "tout");
    rtliSetLogX(Hover_M->rtwLogInfo, "");
    rtliSetLogXFinal(Hover_M->rtwLogInfo, "");
    rtliSetSigLog(Hover_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Hover_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Hover_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(Hover_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Hover_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &Hover_Y.Control
      };

      rtliSetLogYSignalPtrs(Hover_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        1
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        1
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0
      };

      static int_T* rt_LoggedCurrentSignalDimensions[] = {
        (NULL)
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "Control" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "Hover/Control" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          1,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (NULL),

          { rt_LoggedOutputLabels },
          (NULL),
          (NULL),
          (NULL),

          { rt_LoggedOutputBlockNames },

          { (NULL) },
          (NULL),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo(Hover_M->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
    }

    rtliSetLogY(Hover_M->rtwLogInfo, "yout");
  }

  Hover_M->solverInfoPtr = (&Hover_M->solverInfo);
  Hover_M->Timing.stepSize = (0.2);
  rtsiSetFixedStepSize(&Hover_M->solverInfo, 0.2);
  rtsiSetSolverMode(&Hover_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Hover_M->ModelData.blockIO = ((void *) &Hover_B);
  (void) memset(((void *) &Hover_B), 0,
                sizeof(BlockIO_Hover));

  /* states (dwork) */
  Hover_M->Work.dwork = ((void *) &Hover_DWork);
  (void) memset((void *)&Hover_DWork, 0,
                sizeof(D_Work_Hover));

  /* external inputs */
  Hover_M->ModelData.inputs = (((void*)&Hover_U));
  (void) memset((void *)&Hover_U, 0,
                sizeof(ExternalInputs_Hover));

  /* external outputs */
  Hover_M->ModelData.outputs = (&Hover_Y);
  Hover_Y.Control = 0.0;
}

/* Model terminate function */
void Hover_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Hover_output(tid);
}

void MdlUpdate(int_T tid)
{
  Hover_update(tid);
}

void MdlInitializeSizes(void)
{
  Hover_M->Sizes.numContStates = (0);  /* Number of continuous states */
  Hover_M->Sizes.numY = (1);           /* Number of model outputs */
  Hover_M->Sizes.numU = (3);           /* Number of model inputs */
  Hover_M->Sizes.sysDirFeedThru = (1); /* The model is direct feedthrough */
  Hover_M->Sizes.numSampTimes = (1);   /* Number of sample times */
  Hover_M->Sizes.numBlocks = (3);      /* Number of blocks */
  Hover_M->Sizes.numBlockIO = (1);     /* Number of block outputs */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* InitializeConditions for Stateflow: '<Root>/Hover Mode Enable' */
  Hover_DWork.is_active_c3_Hover = 0U;
  Hover_DWork.is_c3_Hover = 0U;
  Hover_B.Control = 0.0;
  Hover_DWork.presentTicks = 0U;
  Hover_DWork.elapsedTicks = 0U;
  Hover_DWork.previousTicks = 0U;
}

void MdlStart(void)
{
  MdlInitialize();

  /* Enable for Stateflow: '<Root>/Hover Mode Enable' */
  Hover_DWork.presentTicks = Hover_M->Timing.clockTick0;
  Hover_DWork.previousTicks = Hover_DWork.presentTicks;
}

void MdlTerminate(void)
{
  Hover_terminate();
}

RT_MODEL_Hover *Hover(void)
{
  Hover_initialize(1);
  return Hover_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
