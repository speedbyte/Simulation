/*************************************************************************************************************


@file:  QH_remote.c
@autor: Marc Weber
@date:  Datum: 28.04.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to receive the remote control PPM signal, therefor timer channel 0 (IOC0) is used</h2>


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


#include "derivative.h"
#include "QH_remote.h"
#include "QH_timer.h"
#include <string.h>
#include "typedef.h"


/* Variables ************************************************************************************************/


static uint8 signalID = 0;
static uint8 signals[8];        /* array for the actual remote control signal values (0 to 255 per channel) */
static bool signalsOK = FALSE;  /* flag which indicates if new signal data is available */


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* remoteInit() configures the timer channel 0 (IOC0) to receive the remote control PPM signal; in an       */
/* interrupt service routine, the signal values are transferred to the                                      */
/* CAUTION: the timer is disabled for a short time to configure the delay behavior                          */
/*----------------------------------------------------------------------------------------------------------*/
void remoteInit(void)
{
  TIOS_IOS0   = 0;    /* timer channel 0 acts as input compare */
  
  /* input capture on falling edges (starting pulse detection) */
  TCTL4_EDG0A = 1;
  TCTL4_EDG0B = 1;
  
  /* raise an interrupt after two input captures; the first value is stored in TC0H, the last one in TC0 */
  ICOVW_NOVW0 = 1;
  ICSYS_TFMOD = 1;
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
/* remoteGetSignals() writes the remote control values to the given destination                             */
/*   - remoteSignals: a pointer to the array (eight elements) to which the remote control values are        */
/*                    written                                                                               */
/*   return value:    FALSE(0): if new remote control values are written                                    */
/*                    TRUE (1): if no new remote control values are available                               */
/*----------------------------------------------------------------------------------------------------------*/
bool remoteGetSignals(uint8* remoteSignals)
{
  if (signalsOK)
  {
    (void) memcpy(remoteSignals, signals, 8);
    signalsOK = FALSE;
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}

/*----------------------------------------------------------------------------------------------------------*/
/* remoteIsr() is the ISR for IOC0; it is called, when two events (input captures) occurred in IOC0         */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch0 void remoteIsr(void)
{
  uint16 pulseWidth = TC0 - TC0H;             /* calculate the number of ticks between the two events */
                                              /* (normally the pulse wdith) */
  
  if ((pulseWidth < TIMER_05MS) || (pulseWidth > TIMER_15MS) || (signalID > 7))
  {
    signalID++;
  }
  //{
  //  TCTL4_EDG0A = 0;                          /* there was an error; don't transfer remote commands; */
  //                                            /* continue with starting pulse detection (input capture */
  //                                            /* only on falling edges */
  //}
  //else if (pulseWidth > TIMER_4MS)            /* check, if it was the starting pulse (wdith > 4ms) */
  //{
  //  if (!TCTL4_EDG0A)                         /* check, if only falling edges cause an input capture */
  //                                            /* (starting pulse detection) */
  //  {
  //    TCTL4_EDG0A = 1;                        /* input capture on rising and falling edges (normal mode; */
  //                                            /* starting pulse detected; pulse width measurement) */
  //  }
  //  else
  //  {
  //    signalsOK = TRUE;                       /* complete frame received; transfer remote control signals */
  //  }
  //  signalID = 0;                             /* next signal is signal zero (new frame) */
  //}
  //else if (TCTL4_EDG0A)
  //{
  //  /* calculate the signal value between 0 and 255 */
  //  signals[signalID] = (uint8)((pulseWidth - TIMER_07MS) * (256 / TIMER_1MS));
  //   
  //  signalID++;                               /* signal successfully received; continue with next signal */
  //}
  TFLG1_C0F = 1;                              /* clear interrupt flag */
}