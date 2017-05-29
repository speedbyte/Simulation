/*
 * Quadcopter_sf_types.h
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
#ifndef RTW_HEADER_Quadcopter_sf_types_h_
#define RTW_HEADER_Quadcopter_sf_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef _DEFINED_TYPEDEF_FOR_struct_WFOsM4eVlFHz7wRPvf9IDH_
#define _DEFINED_TYPEDEF_FOR_struct_WFOsM4eVlFHz7wRPvf9IDH_

typedef struct {
  real_T g;
  real_T d;
  real_T mass;
  real_T ct;
  real_T cq;
  real_T Jx;
  real_T Jy;
  real_T Jz;
  real_T Jm;
  real_T Jb[9];
  real_T Jbinv[9];
  real_T dctcq[12];
  real_T motor_m;
  real_T motor_dm;
  real_T motor_h;
  real_T motor_r;
  real_T ESC_m;
  real_T ESC_a;
  real_T ESC_b;
  real_T ESC_ds;
  real_T HUB_m;
  real_T HUB_r;
  real_T HUB_H;
  real_T arms_m;
  real_T arms_r;
  real_T arms_L;
  real_T arms_da;
  real_T T;
  real_T minThr;
  real_T cr;
  real_T b;
  real_T plusConfig;
} struct_WFOsM4eVlFHz7wRPvf9IDH;

#endif

/* Parameters (auto storage) */
typedef struct P_Quadcopter_T_ P_Quadcopter_T;

#endif                                 /* RTW_HEADER_Quadcopter_sf_types_h_ */
