/*************************************************************************************************************


@file:  QH_timer.c
@autor: Marc Weber
@date:  Datum: 06.05.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to configure the Enhanced Capture Timer (ECT) and generate a general time base </h2>


CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be called before!
         - Timer channel 7 (IOC7) is internally used to set the timer flags. Don't use this timer channel
           outside of this file!


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
#include "QH_timer.h"
#include "typedef.h"


/* Variables ************************************************************************************************/


static uint16 counter = 0;    /* the counter variable, used to set the timer flags */
static uint8 timerFlags = 0;  /* flags, indicating that a period of time has elapsed; the individual bits */
                              /* are set in the following intervals: */
                              /* bit  interval (milliseconds) */
                              /* 0       5 */
                              /* 1      10 */
                              /* 2      20 */
                              /* 3      50 */
                              /* 4     100 */
                              /* 5     200 */
                              /* 6     500 */
                              /* 7    1000 */


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* timerInit() configures the ECT to use the precision timer; an ECT clock of 1MHz is selected (assuming    */
/* 24MHz bus clock) and the main timer is started; additionally the timer channel 7 is configured to work   */
/* output compare; with this channel, the timer flags are set (see interrupt service routine); this         */
/* function must be called before any other timer...() function                                             */
/*----------------------------------------------------------------------------------------------------------*/
void timerInit(void)
{
  TIOS_IOS7 = 1;                /* timer channel 7 works as output compare */
  
  PTPSR = 0x17;                 /* set precision prescaler to 24 to get 1MHz ECT clock frequency */
  TSCR1 = 0x88;                 /* main timer enable (start); use precision timer */
  
  TC7 = TCNT + 5;                /* set first timer compare value */
  TIE_C7I = 1;                  /* enable interrupts for timer channel 7 */
}

/*----------------------------------------------------------------------------------------------------------*/
/* timerIsFlagSet() checks, if the specified timer flag is set; if so, the flag is cleared                  */
/*   - timerFlag:   the mask of the flag which is checked; please use the appropriate defines               */
/*   return value:  TRUE (1):   if the corresponding flag is set                                            */
/*                  FALSE (0):  if the corresponding flag is not set or timerFlag has a wrong value         */
/*----------------------------------------------------------------------------------------------------------*/
bool timerIsFlagSet(uint8 timerFlag)
{
  if ((timerFlags & timerFlag) == timerFlag)  /* check, if the corresponding flag is set */
  {
    timerFlags = timerFlags & ~timerFlag;     /* reset timer flag */
    return TRUE;
  }
  return FALSE;
}


/* Interrupt Service Routine - ISR **************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* timerIsr() is the ISR for timer channel 7; it is called every five milliseconds to set the timer flags;  */
/* e.g. if the counter has a value of 1000, all flags are set (because 1000 milliseconds is a multiple of   */
/* all flag setting periods, see section Variables)                                                         */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch7 void timerIsr(void)
{
  counter = counter + 5;            /* 5ms elapsed */
    
  if ((counter % 1000) == 0)
  {
    timerFlags = timerFlags | 0xFF; /* set all timer flags */
  }
  else if ((counter % 500) == 0)
  {
    timerFlags = timerFlags | 0x5F; /* set the flags for 500ms, 100ms, 50ms, 20ms, 10ms and 5ms */
  }
  else if ((counter % 200) == 0)
  {
    timerFlags = timerFlags | 0x3F; /* set the flags for 200ms, 100ms, 50ms, 20ms, 10ms and 5ms */
  }
  else if ((counter % 100) == 0)
  {
    timerFlags = timerFlags | 0x1F; /* set the flags for 100ms, 50ms, 20ms, 10ms and 5ms */
  }
  else if ((counter % 50) == 0)
  {
    timerFlags = timerFlags | 0x0B; /* set the flags for 50ms, 10ms and 5ms */
  }
  else if ((counter % 20) == 0)
  {
    timerFlags = timerFlags | 0x07; /* set the flags for 20ms, 10ms and 5ms */
  }
  else if ((counter % 10) == 0)
  {
    timerFlags = timerFlags | 0x03; /* set the flags for 10ms and 5ms */
  } 
  else //if (counter % 5) == 0 
  {
    timerFlags = timerFlags | TIMER_FLAG_5MS; /* set the flag for 5ms */
  }
  
  if (counter == 60000)
  {
    counter = 0;                    /* reset counter to zero (after one minute) to prevent overflow */
  }
  
  TC7 = TC7 + 5000;                 /* set next timer compare value; next interrupt in five milliseconds */
                                    /* (1MHz ECT clock) */
  TFLG1_C7F = 1;                    /* clear interrupt flag */
}