/*
 * Hover_sid.h
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
 *
 * SOURCES: Hover_sf.c
 */

/* statically allocated instance data for model: Hover */
{
  {
    /* Local SimStruct for RTW generated S-Function */
    static LocalS slS;
    LocalS *lS = &slS;
    ssSetUserData(rts, lS);

    /* block I/O */
    {
      static BlockIO_Hover sfcnB;
      void *b = (real_T *) &sfcnB;
      ssSetLocalBlockIO(rts, b);
      (void) memset(b, 0,
                    sizeof(BlockIO_Hover));
    }

    /* model checksums */
    ssSetChecksumVal(rts, 0, 3345817364U);
    ssSetChecksumVal(rts, 1, 515488957U);
    ssSetChecksumVal(rts, 2, 3716686703U);
    ssSetChecksumVal(rts, 3, 4064680963U);
  }
}
