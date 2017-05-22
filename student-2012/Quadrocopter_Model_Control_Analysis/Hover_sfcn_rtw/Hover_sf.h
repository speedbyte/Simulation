/*
 * Hover_sf.h
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
#ifndef RTW_HEADER_Hover_sf_h_
#define RTW_HEADER_Hover_sf_h_
#ifndef Hover_sf_COMMON_INCLUDES_
# define Hover_sf_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#define S_FUNCTION_NAME                Hover_sf
#define S_FUNCTION_LEVEL               2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_nonfinite.h"
#if !defined(RTW_SFUNCTION_DEFINES)
#define RTW_SFUNCTION_DEFINES

typedef struct {
  void *blockIO;
  void *defaultParam;
  void *nonContDerivSig;
} LocalS;

#define ssSetLocalBlockIO(S, io)       ((LocalS *)ssGetUserData(S))->blockIO = ((void *)(io))
#define ssGetLocalBlockIO(S)           ((LocalS *)ssGetUserData(S))->blockIO
#define ssSetLocalDefaultParam(S, paramVector) ((LocalS *)ssGetUserData(S))->defaultParam = (paramVector)
#define ssGetLocalDefaultParam(S)      ((LocalS *)ssGetUserData(S))->defaultParam
#define ssSetLocalNonContDerivSig(S, pSig) ((LocalS *)ssGetUserData(S))->nonContDerivSig = (pSig)
#define ssGetLocalNonContDerivSig(S)   ((LocalS *)ssGetUserData(S))->nonContDerivSig
#endif
#endif                                 /* Hover_sf_COMMON_INCLUDES_ */

#include "Hover_sf_types.h"

/* Block signals (auto storage) */
typedef struct {
  real_T Control;                      /* '<Root>/Hover Mode Enable' */
} BlockIO_Hover;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T *phiSet;                      /* '<Root>/phiSet' */
  real_T *thetaSet;                    /* '<Root>/thetaSet' */
  real_T *r_psiSet;                    /* '<Root>/r_psiSet' */
} ExternalUPtrs_Hover;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T *Control;                     /* '<Root>/Control' */
} ExternalOutputs_Hover;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('System_Design_Quadrocopter/Control/PID_Control_IMU_and_Optical/Hover Mode Enable')    - opens subsystem System_Design_Quadrocopter/Control/PID_Control_IMU_and_Optical/Hover Mode Enable
 * hilite_system('System_Design_Quadrocopter/Control/PID_Control_IMU_and_Optical/Hover Mode Enable/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : System_Design_Quadrocopter/Control/PID_Control_IMU_and_Optical
 * '<S1>'   : System_Design_Quadrocopter/Control/PID_Control_IMU_and_Optical/Hover Mode Enable
 */
#endif                                 /* RTW_HEADER_Hover_sf_h_ */
