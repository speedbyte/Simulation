/*************************************************************************************************************


@file:  basestation.c
@autor: Marc Weber
@date:  Datum: 19.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to communicate with the base station</h2>


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
#include "flightcontrol.h"
#include "QH_xbee.h"
#include <string.h>


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* basestation() checks for a received message sent by the base station and reacts correspondingly; this    */
/* function must be executed every 100 ms                                                                   */
/*----------------------------------------------------------------------------------------------------------*/
void basestation(void)
{
/* copterState modiefied some dataexchange will not ork properly */
  static uint8 statusMsgPeriod = 0;
  static uint8 executionCounter = 0;
  
  static XbeeMsg rxMsg;
  static XbeeMsg txMsg;
  
  CopterConfig* copterConfig = copterGetConfigPtr();
  CopterState* copterState = copterGetStatePtr();
  
  executionCounter++;
  
  /* check, if a new message was received */
  if (xbeeCheckForMsg(&rxMsg) == 0)
  {
    /* check which message was received */
    switch (rxMsg.id)
    {
      /* Parameter Request message */
      case 0x10:
      {
        /* send Parameter Response message */
        txMsg.id = 0x11;
        txMsg.dataLen = sizeof(CopterConfig);
        (void) memcpy(txMsg.data, copterConfig, txMsg.dataLen);
        (void) xbeeSendMsg(&txMsg);
        break;
      }
      /* Parameter Update message */
      case 0x12:
      {
        /* only actualize configuration parameters, if the quadrocopter is currently grounded */
        if (!copterState->remoteMotorsOn)
        {
          /* copy received configuration parameters to the RAM */
          (void) memcpy(copterConfig, rxMsg.data, rxMsg.dataLen);
          
          /* save configuration parameters in the EEPROM */
          copterSaveActualConfig();
        }
        
        /* send Parameter Response message */
        txMsg.id = 0x11;
        txMsg.dataLen = sizeof(CopterConfig);
        (void) memcpy(txMsg.data, copterConfig, txMsg.dataLen);
        (void) xbeeSendMsg(&txMsg);
        break;
      }
      /* Status Request message */
      case 0x20:
      {
        /* send Status Response message */
        txMsg.id = 0x21;
        txMsg.dataLen = sizeof(CopterState);
        (void) memcpy(txMsg.data, copterState, txMsg.dataLen);
        
        if (rxMsg.data[0] < 0xFF)
        {
          /* periodic Status Response message configuration */
          statusMsgPeriod = rxMsg.data[0];
          executionCounter = 0;
        }
        else
        {
          /* single Status Response message */
          statusMsgPeriod = 0;
        }
        
        (void) xbeeSendMsg(&txMsg);
        break;
      }
      case 0x30: 
      {
        txMsg.id = 0x31;
        txMsg.dataLen = 4;
        
        
        copterState = mycopterGetStatePtr();
        
        // accelerometer 
        copterState->accXRaw = rxMsg.data[0]*256 + rxMsg.data[1];        // -2048 .. 2047 
        copterState->accYRaw = rxMsg.data[2]*256 + rxMsg.data[3];        // -2048 .. 2047 
    
        // ATD; gyroscopes, temperature, air pressure and battery voltage 
        copterState->angVelRRaw = rxMsg.data[4]*256 + rxMsg.data[5];     // 0 .. 1024 
        copterState->angVelPRaw = rxMsg.data[6]*256 + rxMsg.data[7];     // 0 .. 1024 
        copterState->angVelYRaw = rxMsg.data[8]*256 + rxMsg.data[9];     // 0 .. 1024 
    
        copterState->remoteRollRaw   = rxMsg.data[10];  // 0 .. 255
        copterState->remotePitchRaw  = rxMsg.data[11]; // 0 .. 255 
        copterState->remoteYawRaw    = rxMsg.data[12];   // 0 .. 255 
        copterState->remoteForceRaw  = rxMsg.data[13]; // 0 .. 255 
    
        (void) accelCalcPhysicalValues(copterState);
        (void) atdCalculatePhysicalValues(copterState);
        (void) calcPhysicalValuesFromRemote(copterState);
       
        // compute controll algorithm
        (void) Controll(copterState, copterConfig);
       
        txMsg.data[0] = copterState->setpointFront;
        txMsg.data[1] = copterState->setpointLeft;  
        txMsg.data[2] = copterState->setpointRear;  
        txMsg.data[3] = copterState->setpointRight;
        
        (void) xbeeSendMsg(&txMsg);    
        break;
      }        
      default:
      {
        /* no valid message */
      }
    }
  }
  
  /* check, if a status response message is to send periodically */
  if ((statusMsgPeriod > 0) && (statusMsgPeriod == executionCounter))
  {
    txMsg.id = 0x21;
    txMsg.dataLen = sizeof(CopterState);
    (void) memcpy(txMsg.data, copterState, txMsg.dataLen);
    (void) xbeeSendMsg(&txMsg);
    executionCounter = 0;
  }
}