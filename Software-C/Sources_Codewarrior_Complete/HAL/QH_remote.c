/*************************************************************************************************************


@file:  QH_remote.c
@autor: Marc Weber
@date:  Datum: 17.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to receive the remote control PPM signal</h2>


CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be called before!
         - Timer channel 0 (IOC0) is internally used to measure the pulse width of the signals in the PPM
           frame. A timer frequency of 1MHz is assumed. Therefore timerInit() must be called before! Don't
           use timer channel 0 outside of this file!


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


/* Includes *************************************************************************************************/
#include "copter.h"
#include "derivative.h"
#include "QH_remote.h"
#include "QH_timer.h"
#include "typedef.h"

/* Defines *************************************************************************************************/
#define RC_FAIL_DETECTION_VAL 140  //This value is the lower bound (with tolerance) of unassigned RC channels
#define MAX_ERR_OF_SEQ_SIGNALS 50  //Deprecated: This value defines the maximum error of two sequential signals
                                   //and is used to execute plausibility checks of RC commands in runtime


/* Variables ************************************************************************************************/
static const int32 maxRemoteYaw   = 128;  // max remote value for yaw rate
static const int32 maxRemotePitch = 128;  // max remote value for pitch angle
static const int32 maxRemoteRoll  = 128;  // max remote value for roll angle
static const int32 maxYawRate     = 314/4;  // [100*rad/s] max value for yaw rate
static const int32 maxPitchAngle  = 314/8;  // [100*rad] max value for pitch angle
static const int32 maxRollAngle   = 314/8;  // [100*rad] max value for roll angle


/* double buffering for remote control values (PPM channel 1 to channel 9; 0 to 255 per channel) */
static uint8 signalBuffer1[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8 signalBuffer2[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

static uint16 pulseBuffer[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

static uint8* readPtr = signalBuffer1;
static uint8* writePtr = signalBuffer2;

static bool remoteOk = FALSE; /* flag, indicating if a valid PPM frame was received */

/* Private Functions ****************************************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/* getSafetyChannelsState() returns the state of the safety channels. These channels are not attached to a switch
   and have a constant value which is smaller as RC_FAIL_DETECTION_VAL. If one of these channels are higher as
   RC_FAIL_DETECTION_VAL, it has to be assumed that the RC was switched off.
/* CAUTION: If the safety channels are mapped to a switch in the RC, this function has to be modified. Otherwise
   the function could return always false, so the copter could not be switched on.*/
/*----------------------------------------------------------------------------------------------------------*/
bool getSafetyChannelsState(){
   return (writePtr[4] < RC_FAIL_DETECTION_VAL &&
           writePtr[5] < RC_FAIL_DETECTION_VAL &&
           writePtr[6] < RC_FAIL_DETECTION_VAL &&
           writePtr[7] < RC_FAIL_DETECTION_VAL &&
           writePtr[8] < RC_FAIL_DETECTION_VAL);
}


/* Functions ************************************************************************************************/
 

/*----------------------------------------------------------------------------------------------------------*/
/* remoteInit() configures the timer channel 0 (IOC0) to receive the remote control PPM signal; in an       */
/* interrupt service routine, the signal values are transferred to the                                      */
/* CAUTION: the timer is disabled for a short time to configure the delay behavior                          */
/*----------------------------------------------------------------------------------------------------------*/
void remoteInit(void)
{
  TIOS_IOS0   = 0;    /* timer channel 0 acts as input compare */
  
  /* input capture on rising edges (starting pulse detection) */
  TCTL4_EDG0A = 1;
  TCTL4_EDG0B = 0;
  
  /* raise an interrupt after two input captures; the first value is stored in TC0H, the last one in TC0 */
  ICSYS_BUFEN = 1;
  ICSYS_LATQ  = 0;
  
  /* clear capture and holding register; empty registers required for selected capture mode */
  (void) TC0;
  (void) TC0H;
  
  TSCR1_TEN   = 0;    /* disable timer for delay adjustment */
  
  DLYCT       = 0x7F; /* ignore short impulses up to the length of f(DLYCT) * BUSCLK; see also datasheet */
                      /* chapter 7.3.2.22 */
  
  TSCR1_TEN   = 1;    /* enable timer */
  
  TIE_C0I     = 1;    /* enable interrupt generation for timer channel 0 */
}
 
/*----------------------------------------------------------------------------------------------------------*/
/* remoteGetValues() gets the actual values of the remote control (raw value for the desired force, yaw     */
/* velocity and pitch/roll angle) and writes them to the CopterState structure; also the flags              */
/* indicating if the motors should be on and if the remote connection is ok are set/reset                   */
/*----------------------------------------------------------------------------------------------------------*/
void remoteGetValues(void)
{
  static uint8 safetySwCnt = 0;
  static bool actSafetySwState = FALSE;
  static bool prevSafetySwState = FALSE;
  static bool safetySwPosSlope = FALSE;
  CopterState* copterState;

/* // Deprecated safety switch architecture which works with channel 5
  // Switch debouncer 
  if(pulseBuffer[4] < 1800){ //Check if channel 5 is switched on (negative logic)
                             //Count six times before the value of switch set to high (debouncing)
     if(safetySwCnt < 6){   
       safetySwCnt++;
     }  
     if(safetySwCnt >=6){
       actSafetySwState=TRUE;
     }
  }else{                    //Check if channel 5 is switched off
                            //Count six times down before the value of switch set to low (debouncing)
     if(safetySwCnt > 0){
       safetySwCnt--;
     }  
     if(safetySwCnt < 1){
       actSafetySwState=FALSE;
     }
  } 
  // Slope checker
  if(FALSE==prevSafetySwState && TRUE==actSafetySwState){ //Check if positive slope occured
                                                          //with comparing actual and previous switch value
    safetySwPosSlope=TRUE;
  }else{
    safetySwPosSlope=FALSE;
  }
                                                           //Set previous switch state to the actual state
  prevSafetySwState=actSafetySwState;
*/
   
  /* get pointer to the CopterState structure (real-time database) */
  copterState = copterGetStatePtr();
  
  if(remoteOk && getSafetyChannelsState()){ 
    copterState->remotePitchRaw = readPtr[0]; 
    copterState->remoteRollRaw  = readPtr[1];
    copterState->remoteForceRaw = readPtr[2]; 
    copterState->remoteYawRaw   = readPtr[3];
  }else{
  /*Connection lost -> Stop engines immediately*/
    copterState->remotePitchRaw = 128; 
    copterState->remoteRollRaw  = 128;
    copterState->remoteForceRaw = 0; 
    copterState->remoteYawRaw   = 128;
  }
  if (remoteOk && (copterState->remoteForceRaw <= 5) && (copterState->remoteYawRaw <= 45))
  {
    copterState->remoteMotorsOn = TRUE;     /* turn motors on, if the remote signal is ok and motor start */
                                            /* condition occurred */
  }
  else if (!remoteOk || ((copterState->remoteForceRaw <= 5) && (copterState->remoteYawRaw >= 210)))
  {
    copterState->remoteMotorsOn = FALSE;    /* turn motors off, if the remote signal is lost or motor stop */
                                            /* condition occurred */
  }
  copterState->remoteConnected = remoteOk;
}

void calcPhysicalValuesFromRemote( CopterState* copterState) 
{
  copterState->remotePitch    = (int16)(maxPitchAngle*(int32)(copterState->remotePitchRaw-128)/maxRemotePitch);
  copterState->remoteRoll     = -(int16)(maxRollAngle*(int32)(copterState->remoteRollRaw-128)/maxRemoteRoll);
  copterState->remoteForce    = copterState->remoteForceRaw; 
  copterState->remoteYaw      = (int16)(maxYawRate*(int32)(copterState->remoteYawRaw-128)/maxRemoteYaw);
}

/*----------------------------------------------------------------------------------------------------------
* Calculates the absolute value of the parameter num
*-----------------------------------------------------------------------------------------------------------*/

/* Interrupt Service Routine - ISR **************************************************************************/

 
/*----------------------------------------------------------------------------------------------------------*/
/* remoteIsr() is the ISR for IOC0; it is called, when a rising edge occurred at IOC0 (input captures);     */
/* internally the duration of a pulse (PPM channel) and the corresponding (desired) raw value is calculated */
/* and stored in the buffer                                                                                 */
/* CAUTION: the calculation of the raw value assumes a minimum pulse duration of 1100us (400us high level   */
/*          and 700us low level) and a maximum pulse duration of 1900us (400us high level and 1500us low    */
/*          level) - this holds only for an untrimmed remote control                                        */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch0 void remoteIsr(void)
{
  static uint8 signalID = 0;
  static uint8 errorCount = 0;
  static uint16 pulseWidth = 0;


  pulseWidth = TC0 - TC0H; /* calculate pulse duration in [us] */
  

  /* check, if it was the starting pulse */
  if ((pulseWidth > TIMER_3500US) && (pulseWidth < TIMER_13500US) && (signalID == 9))
  {
     uint8* temp;
     if(getSafetyChannelsState()){
       /* exchange read and write pointers */
       temp = writePtr;
       writePtr = readPtr;
       readPtr = temp;
       
       errorCount = 0;               /* reset error counter */
       signalID = 0;                 /* next signal is signal zero (new frame) */
       remoteOk = TRUE;
       
     }else{
       remoteOk = FALSE;
       (void)beeperOn(2000);
     }
  }
  else if ((pulseWidth > TIMER_900US) && (pulseWidth < TIMER_2100US) && (signalID < 9))
  {
    pulseBuffer[signalID]=pulseWidth;
    /* calculate the signal value between 0 and 255 */
    if (pulseWidth < 1100){
      writePtr[signalID] = 0;
    }else if (pulseWidth > 1900){
      writePtr[signalID] = 255;
    }else{
      writePtr[signalID] = (uint8)(((uint32)(pulseWidth - TIMER_1100US) * 255) / TIMER_800US);
    }
    
    signalID++;                   /* signal successfully received; continue with next signal */
  }
  else{
    errorCount++;                 /* increment error counter */
    signalID = 0;                 /* error; reset signal ID */
    if (errorCount > 8)           /* check, if it is a permanent connection error */
    {
       remoteOk = FALSE;
      (void)beeperOn(2000);
    }
  }
  TFLG1_C0F = 1;                  /* clear interrupt flag */
}
