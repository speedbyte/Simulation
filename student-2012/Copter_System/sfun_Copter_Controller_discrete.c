

/*************************************************************************************************************


@file:  sfun_Copter_Controller_discrete.c
@author: Sreekanth Sundaresh
@date:  12.05.2010

Copyright (C) 2010 University of Applied Sciences Esslingen

--------------------------------------------------------------------------------------------------------------

 _
|
| Hochschule Esslingen
| University of Applied Sciencs
|_

Graduate School
Automotive Systems Master - Software Based Automotive Systems

Project Quadrocopter

Joachim Schwab, Sreekanth Sundaresh, Nina Vetlugina, Marc Weber 
Summer Term 2010


*************************************************************************************************************/
#define S_FUNCTION_NAME  sfun_Copter_Controller_discrete
#define S_FUNCTION_LEVEL 2
#define NUMINPORTS 7
#define NUMOUTPORTS 5
#define NUMPARAMS 1

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include "copter.h"
#include "flightcontrol.h"
#include "typedef.h"


static CopterConfig copterConfig = {2500, 5000, 500, 2500, 5000, 500, 400, 500, 70, 5, 95, 5, 95, 9, 9, 16, 166,
                                    10000, 750, 250, 250};
                                 
static CopterState copterState = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0};

/*----------------------------------------------------------------------------------------------------------*/
/* copterGetConfigPtr() returns a pointer to the quadrocopter configuration (RAM)                           */
/*   return value:  a pointer to the configuration parameters                                               */
/*----------------------------------------------------------------------------------------------------------*/
CopterConfig* copterGetConfigPtr(void)
{
  return &copterConfig;
}

/*----------------------------------------------------------------------------------------------------------*/
/* copterGetStatePtr() returns a pointer to the real-time image (status information) of the quadrocopter    */
/*   return value:  a pointer to the real-time image                                                        */
/*----------------------------------------------------------------------------------------------------------*/
CopterState* copterGetStatePtr(void)
{
  return &copterState;
}



/* Function: mdlInitializeSizes ===========================================
 * Abstract: Mandatory function
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */

static void mdlInitializeSizes(SimStruct *S)
{
    int_T i;
    
    ssSetNumContStates(S,0);    /* number of continuous states */
    ssSetNumDiscStates(S,0);    /* number of discrete states */
    ssSetNumInputPorts(S,NUMINPORTS);    /* number of input signals */
    ssSetNumOutputPorts(S,NUMOUTPORTS);    /* number of output signals */
    ssSetNumSFcnParams(S,NUMPARAMS);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }
    ssSetNumSampleTimes(S,1);    /* number of sample times */
    ssSetNumRWork(S,0);    /* size of real work array */
    ssSetNumIWork(S,0);    /* size of integer work array */
    ssSetNumPWork(S,0);    /* size of pointer work array */
   
    /* Specify the width of an input & output ports 
     * In our case all the inputs & outputs are scalar.
     * Hence the width of all the input & output ports are 1 */
    
    for (i=0; i<NUMINPORTS; i++)
    { 
        ssSetInputPortWidth(S, i, 1);
        ssSetInputPortDataType(S, i, SS_INT16);
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous(S, i, 1);
        
    }
    
    for (i=0; i<NUMOUTPORTS;i++)
    { 
        ssSetOutputPortWidth(S, i, 1);
        ssSetOutputPortDataType(S, i, SS_INT16);
    }
    
}

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct *S, int16_T port, DTypeId dType)
{
    ssSetInputPortDataType( S, 0, dType);
}
#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, int16_T port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}
#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
    ssSetInputPortDataType( S, 0, SS_DOUBLE);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}

/* Function: mdlInitializeSampleTimes =====================================
 * Abstract: Mandatory function
 *    This function is used to specify the sample time(s) for the
 *    S-function. We must specify the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, 0.01);
    ssSetOffsetTime(S, 0, 0.0);

}


/* Function: mdlOutputs =======================================================
 * Abstract: Mandatory function
 *    In this function, the outputs of the S-function block is
 *    computed.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
	double *p;

    
    /* Declare input & output interfaces*/
    
	int16_T *U1_des  = (int16_T *)ssGetInputPortSignal(S,0);
    int16_T *phi_des  = (int16_T *)ssGetInputPortSignal(S,1);
    int16_T *phi_filt  = (int16_T *)ssGetInputPortSignal(S,2);
    int16_T *theta_des  = (int16_T *)ssGetInputPortSignal(S,3);
    int16_T *theta_filt  = (int16_T *)ssGetInputPortSignal(S,4);
    int16_T *anv_phi_des  = (int16_T *)ssGetInputPortSignal(S,5);
    int16_T *anv_psi  = (int16_T *)ssGetInputPortSignal(S,6);
	
	int16_T *U1_out = (int16_T *)ssGetOutputPortRealSignal(S,0);
	int16_T *anv_prop1 = (int16_T *)ssGetOutputPortRealSignal(S,1);
	int16_T *anv_prop2 = (int16_T *)ssGetOutputPortRealSignal(S,2);
	int16_T *anv_prop3 = (int16_T *)ssGetOutputPortRealSignal(S,3);
	int16_T *anv_prop4 = (int16_T *)ssGetOutputPortRealSignal(S,4);
	
	/* Get the parameter vector */
    p=mxGetPr(ssGetSFcnParam(S,0));
	
	copterState.remoteForce = *U1_des;
	copterState.remoteRoll = *phi_des;
	copterState.angR = *phi_filt;
	copterState.remotePitch = *theta_des;
	copterState.angP = *theta_filt;
	copterState.remoteYaw = *anv_phi_des;
	copterState.angVelY = *anv_psi;

	copterConfig.kpR = (int16)(p[0]*100);
    copterConfig.kiR = (int16)(p[1]*100);
    copterConfig.kdR = (int16)(p[2]*100);
    
    copterConfig.kpP = (int16)(p[3]*100);
    copterConfig.kiP = (int16)(p[4]*100);
    copterConfig.kdP = (int16)(p[5]*100);
    
    copterConfig.kpY = (int16)(p[6]*100);
    copterConfig.kiY = (int16)(p[7]*100);
    copterConfig.kdY = (int16)(p[8]*100);

	/* Call the routine & flightControl() */
	copterState.remoteMotorsOn = TRUE;
	flightControl();
    
    *U1_out = copterState.forceTotal;
    *anv_prop1 = copterState.setpointFront;
	*anv_prop2 = copterState.setpointLeft;
	*anv_prop3 = copterState.setpointRear;
	*anv_prop4 = copterState.setpointRight;
}
    
/* Function: mdlTerminate =====================================================
 * Abstract: Mandatory function
 *    In this function, any actions that are necessary at the termination 
 *    of a simulation should be performed .  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    
}

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif