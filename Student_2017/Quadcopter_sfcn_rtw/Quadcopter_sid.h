/*
 * Quadcopter_sid.h
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
 *
 * SOURCES: Quadcopter_sf.c
 */

/* statically allocated instance data for model: Quadcopter */
{
  extern P_Quadcopter_T Quadcopter_DefaultP;

  {
    /* Local SimStruct for the generated S-Function */
    static LocalS slS;
    LocalS *lS = &slS;
    ssSetUserData(rts, lS);

    /* model parameters */
    ssSetLocalDefaultParam(rts, (real_T *) &Quadcopter_DefaultP);

    /* model checksums */
    ssSetChecksumVal(rts, 0, 236483849U);
    ssSetChecksumVal(rts, 1, 1483223165U);
    ssSetChecksumVal(rts, 2, 3336949459U);
    ssSetChecksumVal(rts, 3, 578439558U);
  }
}
