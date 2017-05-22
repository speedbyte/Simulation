/*************************************************************************************************************


@file:  QH_pll.h
@autor: Marc Weber
@date:  Datum: 19.04.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to control the PLL</h2>


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


#ifndef QH_PLL_H
  #define QH_PLL_H
  
  
/* Includes *************************************************************************************************/


  #include "typedef.h"
  
  
/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* pllInit() configures the internal PLL to generate 24MHz bus clock, using a 4MHz oscillator; this         */
/* function must be called before any other pll...() function                                               */
/*----------------------------------------------------------------------------------------------------------*/
  void pllInit(void);
  
/*----------------------------------------------------------------------------------------------------------*/
/* pllGetOscclk() returns the frequency of the oscillator (quartz) in [Hz]                                  */
/*   return value:  the oscillator frequency in [Hz]                                                        */
/*----------------------------------------------------------------------------------------------------------*/
  uint32 pllGetOscclk(void);
  
/*----------------------------------------------------------------------------------------------------------*/
/* pllGetBusclk() returns the output frequency of the PLL (bus clock) in [Hz]                               */
/*   return value:  the bus frequency in [Hz]                                                               */
/*----------------------------------------------------------------------------------------------------------*/
  uint32 pllGetBusclk(void);
  
  
/************************************************************************************************************/


#endif