/*
 * controller_data.c
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

/* Block parameters (auto storage) */
Parameters_controller controller_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Unit Delay1'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Gain13'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Unit Delay2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Quantizer5'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Unit Delay'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Gain15'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Quantizer6'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Quantizer7'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Gain'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Gain14'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Quantizer8'
                                        */
  0.01,                                /* Computed Parameter: DiscreteTimeIntegrator_gainval
                                        * Referenced by: '<S1>/Discrete-Time Integrator'
                                        */
  0.15,                                /* Expression: phi0
                                        * Referenced by: '<S1>/Discrete-Time Integrator'
                                        */
  0.01,                                /* Computed Parameter: DiscreteTimeIntegrator1_gainval
                                        * Referenced by: '<S1>/Discrete-Time Integrator1'
                                        */
  0.15,                                /* Expression: theta0
                                        * Referenced by: '<S1>/Discrete-Time Integrator1'
                                        */
  0.00938349,                          /* Expression: 0.00938349
                                        * Referenced by: '<S1>/Gain21'
                                        */
  41.0,                                /* Expression: 41
                                        * Referenced by: '<S1>/Gain1'
                                        */
  34.9,                                /* Expression: 34.9
                                        * Referenced by: '<S1>/Gain11'
                                        */
  0.00938349,                          /* Expression: 0.00938349
                                        * Referenced by: '<S1>/Gain26'
                                        */
  41.0,                                /* Expression: 41
                                        * Referenced by: '<S1>/Gain16'
                                        */
  0.028852941,                         /* Expression: 0.028852941
                                        * Referenced by: '<S1>/Gain23'
                                        */
  1.0193679918450560E-001,             /* Expression: 1/g
                                        * Referenced by: '<S1>/Gain24'
                                        */
  10.0,                                /* Expression: 10
                                        * Referenced by: '<S1>/Gain18'
                                        */
  34.9,                                /* Expression: 34.9
                                        * Referenced by: '<S1>/Gain2'
                                        */
  0.00938349,                          /* Expression: 0.00938349
                                        * Referenced by: '<S1>/Gain28'
                                        */
  0.028852941,                         /* Expression: 0.028852941
                                        * Referenced by: '<S1>/Gain31'
                                        */
  1.0193679918450560E-001,             /* Expression: 1/g
                                        * Referenced by: '<S1>/Gain32'
                                        */
  10.0,                                /* Expression: 10
                                        * Referenced by: '<S1>/Gain29'
                                        */
  41.0                                 /* Expression: 41
                                        * Referenced by: '<S1>/Gain6'
                                        */
};
