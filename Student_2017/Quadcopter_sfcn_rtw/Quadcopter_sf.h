/*
 * Quadcopter_sf.h
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
#ifndef RTW_HEADER_Quadcopter_sf_h_
#define RTW_HEADER_Quadcopter_sf_h_
#include <string.h>
#include <stddef.h>
#ifndef Quadcopter_sf_COMMON_INCLUDES_
# define Quadcopter_sf_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME                Quadcopter_sf
#define S_FUNCTION_LEVEL               2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if !defined(MATLAB_MEX_FILE)
#include "rt_matrx.h"
#endif

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
#endif                                 /* Quadcopter_sf_COMMON_INCLUDES_ */

#include "Quadcopter_sf_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T *PhiCorrection;               /* '<Root>/Phi Correction' */
  real_T *wt;                          /* '<Root>/Theta Correction' */
  real_T *PsiCorrection;               /* '<Root>/Psi Correction' */
  real_T *AltitudeCorrection;          /* '<Root>/Altitude Correction' */
} ExternalUPtrs_Quadcopter_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T *mc1;                         /* '<Root>/mc1' */
  real_T *mc2;                         /* '<Root>/mc2' */
  real_T *mc3;                         /* '<Root>/mc3' */
  real_T *mc4;                         /* '<Root>/mc4' */
} ExtY_Quadcopter_T;

/* Parameters (auto storage) */
struct P_Quadcopter_T_ {
  struct_WFOsM4eVlFHz7wRPvf9IDH quadModel;/* Variable: quadModel
                                           * Referenced by: '<S1>/Quad Model Type Logical'
                                           */
};

extern P_Quadcopter_T Quadcopter_DefaultP;

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
 * hilite_system('Quadcopter_Simulation/Quadcopter Control Mixing')    - opens subsystem Quadcopter_Simulation/Quadcopter Control Mixing
 * hilite_system('Quadcopter_Simulation/Quadcopter Control Mixing/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Quadcopter_Simulation'
 * '<S1>'   : 'Quadcopter_Simulation/Quadcopter Control Mixing'
 * '<S2>'   : 'Quadcopter_Simulation/Quadcopter Control Mixing/+ Config Control Mixing'
 * '<S3>'   : 'Quadcopter_Simulation/Quadcopter Control Mixing/X Config Control Mixing'
 */
#endif                                 /* RTW_HEADER_Quadcopter_sf_h_ */
