/*************************************************************************************************************


@file:  sfun_Sensor_Filter_discrete.c
@author: Sreekanth Sundaresh
@date:  20.05.2010

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
#define S_FUNCTION_NAME  sfun_Sensor_Filter_discrete
#define S_FUNCTION_LEVEL 2
#define NUMINPORTS 4
#define NUMOUTPORTS 2
#define NUMPARAMS 0


/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include "copter.h"
#include "typedef.h"
#include "sensorfilter.h"

static CopterConfig copterConfig = {2500, 5000, 500, 2500, 5000, 500, 400, 500, 70, 5, 95, 5, 95, 9, 9, 16, 166,
                                    10000, 750, 250, 250};
                                 
static CopterState copterState = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0};

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
    
    /* Declare input & output interfaces*/

	int16_T *acc_x_B  = (int16_T *)ssGetInputPortSignal(S,0);
    int16_T *acc_y_B  = (int16_T *)ssGetInputPortSignal(S,1);
    int16_T *anv_phi_B  = (int16_T *)ssGetInputPortSignal(S,2);
    int16_T *anv_theta_B  = (int16_T *)ssGetInputPortSignal(S,3);

	int16_T *phi_filt = (int16_T *)ssGetOutputPortRealSignal(S,0);
    int16_T *theta_filt = (int16_T *)ssGetOutputPortRealSignal(S,1);
    
	/* Read the input port signals into appropriate copterState variables*/
    copterState.accX  = *acc_x_B;
    copterState.accY  = *acc_y_B;
    copterState.angVelR  = *anv_phi_B;
    copterState.angVelP  = *anv_theta_B;

	/* Call the routine & sensorFilter() */ 
	sensorFilter();

	/* Write the appropriate copterState variables into input port signals */
	*phi_filt = copterState.angR;
	*theta_filt = copterState.angP;

    
  
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
/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
