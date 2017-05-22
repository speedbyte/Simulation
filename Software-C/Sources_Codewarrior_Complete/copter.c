/*************************************************************************************************************


@file:  copter.c
@autor: Marc Weber
@date:  Datum: 19.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to handle the real-time image of the quadrocopter</h2>


CAUTION: - To work properly, all used components of the Hardware Abstraction Layer (HAL) must be initialized,
           (see Includes section)


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
#include "QH_accelerometer.h"
#include "QH_atd.h"
#include "QH_beeper.h"
#include "QH_brushless.h"
#include "QH_eeprom.h"
#include "QH_led.h"
#include "QH_remote.h"


/* Variables ************************************************************************************************/


static CopterConfig configRam = {2500, 5000, 500, 2500, 5000, 500, 400, 500, 70, 5, 95, 5, 95, 9, 9, 16, 166,
                                 10000, 750, 250, 250};
                                 
static CopterState state = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0};
static CopterState mystate = {0, 0, 0, 0, 0, 0, 0,505, 0, 0, 0,505, 0, 0, 0,505, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0,0,0,0,0, 0,0,0,0,0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0};


/* EEPROM Variables *****************************************************************************************/


#pragma DATA_SEG EE_DATA
static CopterConfig configEeprom; 
#pragma DATA_SEG DEFAULT


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* copterRestoreConfig() restores the quadrocopter configuration (CopterConfig) stored in the EEPROM memory */
/*----------------------------------------------------------------------------------------------------------*/
void copterRestoreConfig(void)
{
  /* check, if there is a configuration stored in the EEPROM memory; if yes, restore it (copy to RAM) */
  if (!eepromIsErased((void*)&configEeprom))
  {
    (void) eepromRead((void*)&configRam, (void*)&configEeprom, sizeof(CopterConfig));
  }
}

/*----------------------------------------------------------------------------------------------------------*/
/* copterSaveActualConfig() saves the actual configuration (RAM) in the EEPROM memory; present data will be */
/* overwritten                                                                                              */
/*----------------------------------------------------------------------------------------------------------*/
void copterSaveActualConfig(void)
{
  (void) eepromWrite((void*)&configRam, (void*)&configEeprom, sizeof(CopterConfig));
}

/*----------------------------------------------------------------------------------------------------------*/
/* copterGetConfigPtr() returns a pointer to the quadrocopter configuration (RAM)                           */
/*   return value:  a pointer to the configuration parameters                                               */
/*----------------------------------------------------------------------------------------------------------*/
CopterConfig* copterGetConfigPtr(void)
{
  return &configRam;
}

/*----------------------------------------------------------------------------------------------------------*/
/* copterGetStatePtr() returns a pointer to the real-time image (status information) of the quadrocopter    */
/*   return value:  a pointer to the real-time image                                                        */
/*----------------------------------------------------------------------------------------------------------*/
CopterState* copterGetStatePtr(void)
{
  return &state;
}

CopterState* mycopterGetStatePtr(void)
{
  return &mystate;
}

/*----------------------------------------------------------------------------------------------------------*/
/* copterActualizeState() actualizes the real-time image of the quadrocopter system by evaluating all       */
/* sensors and the remote control                                                                           */
/*----------------------------------------------------------------------------------------------------------*/
void copterActualizeState(void)
{
  accelGetValues();
  atdGetValues();
  remoteGetValues();
  
  if (state.remoteMotorsOn)
  {
  /* calculate desired physical values out of the remote raw values */
    (void) calcPhysicalValuesFromRemote(&state);

  }
  else
  {
    state.remotePitch = 0;
    state.remoteRoll = 0;
    state.remoteForce = 0;
    state.remoteYaw = 0;
  }
}

/*----------------------------------------------------------------------------------------------------------*/
/* copterSetRpms() sets the RPM setpoints for all four motors                                               */
/*----------------------------------------------------------------------------------------------------------*/
void copterSetRpms(void)
{
  (void) brushlessSetRpm(MOTOR_FRONT, state.setpointFront);
  (void) brushlessSetRpm(MOTOR_REAR, state.setpointRear);
  (void) brushlessSetRpm(MOTOR_RIGHT, state.setpointRight);
  (void) brushlessSetRpm(MOTOR_LEFT, state.setpointLeft);
}

/*----------------------------------------------------------------------------------------------------------*/
/* copterOnBoardDiagnosis() generates diagnostic and alarm signals                                          */
/*----------------------------------------------------------------------------------------------------------*/
void copterOnBoardDiagnosis(void)
{
  static bool beeperState = FALSE;
  static beeperFreq=2000;
  /* alive LED */
  //(void) ledToggle(GREEN_LED);
  
  /* no remote connection */
  if (state.remoteConnected)  /* check, if the remote control is connected */
  {
    (void) ledOff(RED_LED);
  }
  else
  {
    (void) ledOn(RED_LED);
  }
  
  /* low battery warning */
  /* Modification, Dio, 12.11.2010*****************************************************************************/
                    // Changed from (state.battery <= 105) to (state.battery <= 110)
  /* **********************************************************************************************************/
  if (state.battery <= 110)   /* check, if battery voltage is equal or below 10.5V */
  {
    if(FALSE==beeperState){
      beeperOn(beeperFreq);
      beeperState=TRUE;
    }else{
      beeperOff();
      beeperState=FALSE; 
    }
  }
  else
  {
    beeperOff();
  }
}