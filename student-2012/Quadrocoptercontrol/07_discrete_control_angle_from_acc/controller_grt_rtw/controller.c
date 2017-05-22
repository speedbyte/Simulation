/*
 * controller.c
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
 */

#include "controller.h"
#include "controller_private.h"

/* Block signals (auto storage) */
BlockIO_controller controller_B;

/* Block states (auto storage) */
D_Work_controller controller_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_controller controller_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_controller controller_Y;

/* Real-time model */
RT_MODEL_controller controller_M_;
RT_MODEL_controller *controller_M = &controller_M_;

/* Model output function */
static void controller_output(int_T tid)
{
  /* local block i/o variables */
  real_T rtb_Quantizer7;
  real_T rtb_DiscreteTimeIntegrator1;
  real_T rtb_Gain28;

  {
    real_T rtb_Gain21;
    real_T rtb_Sum17;
    real_T rtb_Gain2;

    /* Sum: '<S1>/Sum2' incorporates:
     *  Inport: '<Root>/theta_set'
     *  UnitDelay: '<S1>/Unit Delay1'
     */
    rtb_Quantizer7 = controller_U.theta_set - controller_DWork.UnitDelay1_DSTATE;

    /* Sum: '<S1>/Sum11' incorporates:
     *  Inport: '<Root>/r_psi_set'
     *  UnitDelay: '<S1>/Unit Delay2'
     */
    rtb_Gain21 = controller_U.r_psi_set - controller_DWork.UnitDelay2_DSTATE;

    /* Sum: '<S1>/Sum10' incorporates:
     *  Gain: '<S1>/Gain13'
     *  Inport: '<Root>/thrust'
     */
    rtb_DiscreteTimeIntegrator1 = (controller_P.Gain13_Gain * rtb_Quantizer7 +
      controller_U.thrust) + rtb_Gain21;

    /* Quantizer: '<S1>/Quantizer5' */
    {
      real_T yre;
      yre = controller_P.Quantizer5_Interval * floor(fabs
        ((rtb_DiscreteTimeIntegrator1/(controller_P.Quantizer5_Interval))) + 0.5);
      rtb_DiscreteTimeIntegrator1 = ((rtb_DiscreteTimeIntegrator1 >= 0.0) ? yre :
        -yre);
    }

    /* Outport: '<Root>/M1' */
    controller_Y.M1 = rtb_DiscreteTimeIntegrator1;

    /* Sum: '<S1>/Sum6' incorporates:
     *  Inport: '<Root>/phi_set'
     *  UnitDelay: '<S1>/Unit Delay'
     */
    rtb_DiscreteTimeIntegrator1 = controller_U.phi_set -
      controller_DWork.UnitDelay_DSTATE;

    /* Sum: '<S1>/Sum7' incorporates:
     *  Gain: '<S1>/Gain15'
     *  Inport: '<Root>/thrust'
     */
    rtb_Gain28 = (controller_U.thrust + rtb_DiscreteTimeIntegrator1) +
      controller_P.Gain15_Gain * rtb_Gain21;

    /* Quantizer: '<S1>/Quantizer6' */
    {
      real_T yre;
      yre = controller_P.Quantizer6_Interval * floor(fabs((rtb_Gain28/
        (controller_P.Quantizer6_Interval))) + 0.5);
      rtb_Gain28 = ((rtb_Gain28 >= 0.0) ? yre : -yre);
    }

    /* Outport: '<Root>/M2' */
    controller_Y.M2 = rtb_Gain28;

    /* Sum: '<S1>/Sum8' incorporates:
     *  Inport: '<Root>/thrust'
     */
    rtb_Quantizer7 = (controller_U.thrust + rtb_Quantizer7) + rtb_Gain21;

    /* Quantizer: '<S1>/Quantizer7' */
    {
      real_T yre;
      yre = controller_P.Quantizer7_Interval * floor(fabs((rtb_Quantizer7/
        (controller_P.Quantizer7_Interval))) + 0.5);
      rtb_Quantizer7 = ((rtb_Quantizer7 >= 0.0) ? yre : -yre);
    }

    /* Outport: '<Root>/M3' */
    controller_Y.M3 = rtb_Quantizer7;

    /* Sum: '<S1>/Sum9' incorporates:
     *  Gain: '<S1>/Gain'
     *  Gain: '<S1>/Gain14'
     *  Inport: '<Root>/thrust'
     */
    rtb_Gain28 = (controller_P.Gain_Gain * rtb_DiscreteTimeIntegrator1 +
                  controller_U.thrust) + controller_P.Gain14_Gain * rtb_Gain21;

    /* Quantizer: '<S1>/Quantizer8' */
    {
      real_T yre;
      yre = controller_P.Quantizer8_Interval * floor(fabs((rtb_Gain28/
        (controller_P.Quantizer8_Interval))) + 0.5);
      rtb_Gain28 = ((rtb_Gain28 >= 0.0) ? yre : -yre);
    }

    /* Outport: '<Root>/M4' */
    controller_Y.M4 = rtb_Gain28;

    /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
    rtb_Gain28 = controller_DWork.DiscreteTimeIntegrator_DSTATE;

    /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
    rtb_DiscreteTimeIntegrator1 =
      controller_DWork.DiscreteTimeIntegrator1_DSTATE;

    /* Gain: '<S1>/Gain21' incorporates:
     *  Inport: '<Root>/Gyro_phi'
     */
    rtb_Gain21 = controller_P.Gain21_Gain * controller_U.Gyro_phi;

    /* Gain: '<S1>/Gain16' incorporates:
     *  Gain: '<S1>/Gain26'
     *  Inport: '<Root>/Gyro_psi'
     */
    controller_B.Gain16 = controller_P.Gain26_Gain * controller_U.Gyro_psi *
      controller_P.Gain16_Gain;

    /* Sum: '<S1>/Sum17' incorporates:
     *  Gain: '<S1>/Gain23'
     *  Gain: '<S1>/Gain24'
     *  Inport: '<Root>/acc_ay'
     */
    rtb_Sum17 = controller_P.Gain23_Gain * controller_U.acc_ay *
      controller_P.Gain24_Gain - rtb_Gain28;

    /* Gain: '<S1>/Gain2' */
    rtb_Gain2 = controller_P.Gain2_Gain * rtb_Gain28;

    /* Gain: '<S1>/Gain28' incorporates:
     *  Inport: '<Root>/Gyrp_theta'
     */
    rtb_Gain28 = controller_P.Gain28_Gain * controller_U.Gyrp_theta;

    /* Sum: '<S1>/Sum' incorporates:
     *  Gain: '<S1>/Gain1'
     */
    controller_B.Sum = controller_P.Gain1_Gain * rtb_Gain21 + rtb_Gain2;

    /* Sum: '<S1>/Sum1' incorporates:
     *  Gain: '<S1>/Gain11'
     *  Gain: '<S1>/Gain6'
     */
    controller_B.Sum1 = controller_P.Gain6_Gain * rtb_Gain28 +
      controller_P.Gain11_Gain * rtb_DiscreteTimeIntegrator1;

    /* Sum: '<S1>/Sum18' incorporates:
     *  Gain: '<S1>/Gain18'
     */
    controller_B.Sum18 = controller_P.Gain18_Gain * rtb_Sum17 + rtb_Gain21;

    /* Sum: '<S1>/Sum20' incorporates:
     *  Gain: '<S1>/Gain29'
     *  Gain: '<S1>/Gain31'
     *  Gain: '<S1>/Gain32'
     *  Inport: '<Root>/acc_x'
     *  Sum: '<S1>/Sum19'
     */
    controller_B.Sum20 = (controller_P.Gain31_Gain * controller_U.acc_x *
                          controller_P.Gain32_Gain - rtb_DiscreteTimeIntegrator1)
      * controller_P.Gain29_Gain + rtb_Gain28;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
static void controller_update(int_T tid)
{
  /* Update for UnitDelay: '<S1>/Unit Delay1' */
  controller_DWork.UnitDelay1_DSTATE = controller_B.Sum1;

  /* Update for UnitDelay: '<S1>/Unit Delay2' */
  controller_DWork.UnitDelay2_DSTATE = controller_B.Gain16;

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  controller_DWork.UnitDelay_DSTATE = controller_B.Sum;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  controller_DWork.DiscreteTimeIntegrator_DSTATE =
    controller_P.DiscreteTimeIntegrator_gainval * controller_B.Sum18 +
    controller_DWork.DiscreteTimeIntegrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  controller_DWork.DiscreteTimeIntegrator1_DSTATE =
    controller_P.DiscreteTimeIntegrator1_gainval * controller_B.Sum20 +
    controller_DWork.DiscreteTimeIntegrator1_DSTATE;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++controller_M->Timing.clockTick0))
    ++controller_M->Timing.clockTickH0;
  controller_M->Timing.t[0] = controller_M->Timing.clockTick0 *
    controller_M->Timing.stepSize0 + controller_M->Timing.clockTickH0 *
    controller_M->Timing.stepSize0 * 4294967296.0;

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model initialize function */
void controller_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)controller_M,0,
                sizeof(RT_MODEL_controller));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = controller_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    controller_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    controller_M->Timing.sampleTimes = (&controller_M->Timing.sampleTimesArray[0]);
    controller_M->Timing.offsetTimes = (&controller_M->Timing.offsetTimesArray[0]);

    /* task periods */
    controller_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    controller_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(controller_M, &controller_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = controller_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    controller_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(controller_M, 30.0);
  controller_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    controller_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(controller_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(controller_M->rtwLogInfo, (NULL));
    rtliSetLogT(controller_M->rtwLogInfo, "tout");
    rtliSetLogX(controller_M->rtwLogInfo, "");
    rtliSetLogXFinal(controller_M->rtwLogInfo, "");
    rtliSetSigLog(controller_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(controller_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(controller_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(controller_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(controller_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &controller_Y.M1,
        &controller_Y.M2,
        &controller_Y.M3,
        &controller_Y.M4
      };

      rtliSetLogYSignalPtrs(controller_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        1,
        1,
        1,
        1
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1,
        1,
        1,
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        1,
        1,
        1,
        1
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0,
        0,
        0,
        0
      };

      static int_T* rt_LoggedCurrentSignalDimensions[] = {
        (NULL),
        (NULL),
        (NULL),
        (NULL)
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0,
        0,
        0,
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "",
        "",
        "",
        "" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "controller/M1",
        "controller/M2",
        "controller/M3",
        "controller/M4" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          4,
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

      rtliSetLogYSignalInfo(controller_M->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[1];
      rt_LoggedCurrentSignalDimensions[2] = &rt_LoggedOutputWidths[2];
      rt_LoggedCurrentSignalDimensions[3] = &rt_LoggedOutputWidths[3];
    }

    rtliSetLogY(controller_M->rtwLogInfo, "yout");
  }

  controller_M->solverInfoPtr = (&controller_M->solverInfo);
  controller_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&controller_M->solverInfo, 0.01);
  rtsiSetSolverMode(&controller_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  controller_M->ModelData.blockIO = ((void *) &controller_B);
  (void) memset(((void *) &controller_B),0,
                sizeof(BlockIO_controller));

  /* parameters */
  controller_M->ModelData.defaultParam = ((real_T *) &controller_P);

  /* states (dwork) */
  controller_M->Work.dwork = ((void *) &controller_DWork);
  (void) memset((void *)&controller_DWork, 0,
                sizeof(D_Work_controller));

  /* external inputs */
  controller_M->ModelData.inputs = (((void*) &controller_U));
  (void) memset((void *)&controller_U, 0,
                sizeof(ExternalInputs_controller));

  /* external outputs */
  controller_M->ModelData.outputs = (&controller_Y);
  (void) memset((void *)&controller_Y, 0,
                sizeof(ExternalOutputs_controller));
}

/* Model terminate function */
void controller_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  controller_output(tid);
}

void MdlUpdate(int_T tid)
{
  controller_update(tid);
}

void MdlInitializeSizes(void)
{
  controller_M->Sizes.numContStates = (0);/* Number of continuous states */
  controller_M->Sizes.numY = (4);      /* Number of model outputs */
  controller_M->Sizes.numU = (9);      /* Number of model inputs */
  controller_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  controller_M->Sizes.numSampTimes = (1);/* Number of sample times */
  controller_M->Sizes.numBlocks = (44);/* Number of blocks */
  controller_M->Sizes.numBlockIO = (5);/* Number of block outputs */
  controller_M->Sizes.numBlockPrms = (29);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* InitializeConditions for UnitDelay: '<S1>/Unit Delay1' */
  controller_DWork.UnitDelay1_DSTATE = controller_P.UnitDelay1_X0;

  /* InitializeConditions for UnitDelay: '<S1>/Unit Delay2' */
  controller_DWork.UnitDelay2_DSTATE = controller_P.UnitDelay2_X0;

  /* InitializeConditions for UnitDelay: '<S1>/Unit Delay' */
  controller_DWork.UnitDelay_DSTATE = controller_P.UnitDelay_X0;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  controller_DWork.DiscreteTimeIntegrator_DSTATE =
    controller_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  controller_DWork.DiscreteTimeIntegrator1_DSTATE =
    controller_P.DiscreteTimeIntegrator1_IC;
}

void MdlStart(void)
{
  MdlInitialize();
}

void MdlTerminate(void)
{
  controller_terminate();
}

RT_MODEL_controller *controller(void)
{
  controller_initialize(1);
  return controller_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
