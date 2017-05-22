/*************************************************************************************************************


@file:  QH_beeper.h
@autor: Marc Weber
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


#ifndef QH_BEEPER_H
  #define QH_BEEPER_H


/* Includes *************************************************************************************************/


  #include "typedef.h"


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* beeperInit() configures the hardware so that the beeper can be used; uses timer channel 1 (IOC1); this   */
/* function must be called before any other beeper...() function                                            */
/*----------------------------------------------------------------------------------------------------------*/
  void beeperInit(void);
  
/*----------------------------------------------------------------------------------------------------------*/
/* beeperOn() turns the beeper on                                                                           */
/*   - freq:  specifies the beep frequency in Hz; value range: 50Hz to 10KHz, every frequency below 50Hz is */
/*            set to 50Hz, every frequency above 10KHz is set to 10KHz                                      */
/*----------------------------------------------------------------------------------------------------------*/
  void beeperOn(uint16 freq);
  
/*----------------------------------------------------------------------------------------------------------*/
/* beeperOff() turns the beeper off                                                                         */
/*----------------------------------------------------------------------------------------------------------*/
  void beeperOff(void);


/************************************************************************************************************/


#endif