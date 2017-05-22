/*************************************************************************************************************


@file:  QH_beeper.c
@autor: Marc Weber, inspired by Dionysios Satikidis
@date:  Datum: 06.05.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to control the beeper</h2>


CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be called before!
         - Timer channel 1 (IOC1) is internally used to generate the beep frequency. A timer frequency of
           1MHz is assumed. Therefore timerInit() must be called before! Don't use timer channel 1 outside of
           this file!
           

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
#include "QH_beeper.h"
#include "typedef.h"


/* Variables ************************************************************************************************/


static uint16 deltaTicks = 0;


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* beeperInit() configures the hardware so that the beeper can be used; uses timer channel 1 (IOC1); this   */
/* function must be called before any other beeper...() function                                            */
/*----------------------------------------------------------------------------------------------------------*/
void beeperInit(void)
{
  DDRT     = DDRT | 0x02; /* configure PT1 as output */
  PTT_PTT1 = 0;           /* set output of PT1 to zero */
  
  TIOS_IOS1 = 1;          /* timer channel 1 works as output compare */
}

/*----------------------------------------------------------------------------------------------------------*/
/* beeperOn() turns the beeper on                                                                           */
/*   - freq:  specifies the beep frequency in Hz; value range: 50Hz to 10KHz, every frequency below 50Hz is */
/*            set to 50Hz, every frequency above 10KHz is set to 10KHz                                      */
/*----------------------------------------------------------------------------------------------------------*/
void beeperOn(uint16 freq)
{
  /* frequency limitation */
  uint16 frequency = freq;
  if (frequency < 50)
  {
    frequency = 50;
  }
  else if (frequency > 10000)
  {
    frequency = 10000;
  }
  
  /* get the number of ticks, which is equal to microseconds because of 1MHz ECT clock, between two         */
  /* interrupts; with each interrupt the state of the output pin changes (toggle mode); to get the desired  */
  /* frequency at the output pin, two edges are needed within one period; therefore use double the          */
  /* frequency to calculate the delta ticks (1000000us / (2 * frequency))                                   */
  deltaTicks = (uint16)(500000 / frequency);
  
  /* TC1 = TCNT + 2; */ /* set first timer compare value */
  /* CAUTION: to set the first timer compare value causes clicks when calling bepperOn() several times, */
  /*          therefore it is commented out */
  
  TIE_C1I = 1;          /* enable interrupts for timer channel 1 */    
  TCTL2_OL1 = 1;        /* connect timer channel 1 to output pin logic (toggle mode) */
}

/*----------------------------------------------------------------------------------------------------------*/
/* beeperOff() turns the beeper off                                                                         */
/*----------------------------------------------------------------------------------------------------------*/
void beeperOff(void)
{
  TCTL2_OL1 = 0;  /* disconnect timer channel from output pin logic; interrupt disable not sufficient */
                  /* (beeper beeps at lowest possible frequency) */
  TIE_C1I = 0;    /* disable interrupts for timer channel 1 */
}


/* Interrupt Service Routine - ISR **************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* beeperTimerIsr() is the ISR for timer channel 1; it is called with half of the beep period; due to the   */
/* fact, that the timmer channel 1 is connected to the output pin logic (in toggle mode), the desired beep  */
/* frequency is generated                                                                                   */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch1 void beeperTimerIsr(void)
{
  TC1 = TC1 + deltaTicks; /* set next output compare value (next interrupt in half of the beep period) */
  TFLG1_C1F = 1;          /* clear interrupt flag */
}