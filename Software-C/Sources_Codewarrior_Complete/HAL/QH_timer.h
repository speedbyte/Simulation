/*************************************************************************************************************


@file:  QH_timer.h
@autor: Marc Weber
@date:  Datum: 06.05.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to configure the Enhanced Capture Timer (ECT) and generate a general time base </h2>


CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be called before!
         - Timer channel 0 (IOC0) is internally used to set the timer flags. Don't use this timer channel
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


#ifndef QH_TIMER_H
  #define QH_TIMER_H


/* Includes *************************************************************************************************/


  #include "typedef.h"


/* Defines **************************************************************************************************/


  /* masks for the timer flags */
  #define TIMER_FLAG_5MS      0x01
  #define TIMER_FLAG_10MS     0x02
  #define TIMER_FLAG_20MS     0x04
  #define TIMER_FLAG_50MS     0x08
  #define TIMER_FLAG_100MS    0x10
  #define TIMER_FLAG_200MS    0x20
  #define TIMER_FLAG_500MS    0x40
  #define TIMER_FLAG_1000MS   0x80
  
  /* time constants */
  #define TIMER_800US          800
  #define TIMER_900US          900
  #define TIMER_1100US        1100
  #define TIMER_2100US        2100
  #define TIMER_3500US        3500
  #define TIMER_13500US      13500
  
  
/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* timerInit() configures the ECT to use the precision timer; an ECT clock of 1MHz is selected (assuming    */
/* 24MHz bus clock) and the main timer is started; additionally the timer channel 0 is configured to work   */
/* output compare; with this channel, the timer flags are set (see interrupt service routine); this         */
/* function must be called before any other timer...() function                                             */
/*----------------------------------------------------------------------------------------------------------*/
  void timerInit(void);

/*----------------------------------------------------------------------------------------------------------*/
/* timerIsFlagSet() checks, if the specified timer flag is set; if so, the flag is cleared                  */
/*   - timerFlag:   the mask of the flag which is checked; please use the appropriate defines               */
/*   return value:  TRUE (1):   if the corresponding flag is set                                            */
/*                  FALSE (0):  if the corresponding flag is not set or timerFlag has a wrong value         */
/*----------------------------------------------------------------------------------------------------------*/
  bool timerIsFlagSet(uint8 timerFlag);
  

/************************************************************************************************************/


#endif