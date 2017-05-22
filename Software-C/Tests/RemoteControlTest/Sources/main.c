/*************************************************************************************************************


@file:  main.c
@autor: Marc Weber
@date:  Datum: 19.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Quadrocopter flight control software</h2>


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


#include <hidef.h>            /* common defines and macros */
#include "derivative.h"       /* derivative-specific definitions */

#include "basestation.h"
#include "copter.h"
#include "flightcontrol.h"
#include "QH_accelerometer.h" 
#include "QH_atd.h"
#include "QH_beeper.h"
#include "QH_brushless.h"
#include "QH_led.h"
#include "QH_pll.h"
#include "QH_remote.h"
#include "QH_timer.h"
#include "QH_xbee.h"
#include "sensorfilter.h"

#include "typedef.h"
#include "xgate.h"


/* Defines **************************************************************************************************/


#define ROUTE_INTERRUPT(vec_adr, cfdata)                \
  INT_CFADDR= (vec_adr) & 0xF0;                         \
  INT_CFDATA_ARR[((vec_adr) & 0x0F) >> 1]= (cfdata)

#define SOFTWARETRIGGER0_VEC  0x72              /* vector address = 2 * channel id */


/* XGATE ****************************************************************************************************/


#pragma DATA_SEG SHARED_DATA
volatile int shared_counter;                    /* volatile because both cores are accessing it. */
#pragma DATA_SEG DEFAULT

static void SetupXGATE(void)
{
  /* initialize the XGATE vector block and set the XGVBR register to its start address */
  XGVBR= (unsigned int)(void*__far)(XGATE_VectorTable - XGATE_VECTOR_OFFSET);

  /* switch software trigger 0 interrupt to XGATE */
  ROUTE_INTERRUPT(SOFTWARETRIGGER0_VEC, 0x81);  /* RQST=1 and PRIO=1 */

  /* enable XGATE mode and interrupts */
  XGMCTL= 0xFBC1;                               /* XGE | XGFRZ | XGIE */

  /* force execution of software trigger 0 handler */
  XGSWT= 0x0101;
}


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* main() is the main function of the quadrocopter software                                                 */
/*----------------------------------------------------------------------------------------------------------*/
void main(void)
{
  uint32 count = 0;                             /* counter for debug purposes */
  
  CRGINT = 0x64;
  
  SetupXGATE();
  
  /* hardware initialization */
  pllInit();
  timerInit();
  accelInit();
  atdInit();
  beeperInit();
  brushlessInit();
  ledInit();
  remoteInit();
  xbeeInit();
  
  /* copterRestoreConfig(); */                  /* load stored configuration */
  /* CAUTION: the EEPROM is erased during the programming process but the 'Verify Erase' command still */
  /* signals that there is some data stored in the EEPROM, therefore only zeros would be restored */
  
  EnableInterrupts;
    
  /* wait a second a calibrate sensors */
  /* CAUTION: the calibration process assumes, that the copter stands on a plain ground and is in rest, so */
  /* this has to be ensured when the copter is switched on */
  while (!timerIsFlagSet(TIMER_FLAG_1000MS));
  accelCalibrate();
  atdCalibrate();
  
    
  for(;;)
  {
    /* functions, called every 10 milliseconds */
    if (timerIsFlagSet(TIMER_FLAG_5MS))
    {
      (void)ledOn(GREEN_LED);
      count++;
      
      copterActualizeState();                   /* actualize real-time image */
      myFilter(copterGetStatePtr());
      //sensorFilter(copterGetConfigPtr(),copterGetStatePtr());
      
      if (copterGetStatePtr()->remoteConnected) /* check, if there is a valid signal from the remote */
      {
        flightControl();
        copterSetRpms();
      }
      (void)ledOff(GREEN_LED);
    }
    
    /* functions, called every 100 milliseconds */
    if (timerIsFlagSet(TIMER_FLAG_100MS))
    {
      basestation();
    }
    
    /* functions, called every 1000 milliseconds */
    if (timerIsFlagSet(TIMER_FLAG_1000MS))
    {
      copterOnBoardDiagnosis();
    }
    
    _FEED_COP();                                /* feeds the dog */
  }                                             /* loop forever */
  /* please make sure that you never leave main */
}