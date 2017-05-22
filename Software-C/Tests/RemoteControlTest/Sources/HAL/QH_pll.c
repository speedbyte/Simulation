/*************************************************************************************************************


@file:  QH_pll.c
@autor: Marc Weber, inspired by Dionysios Satikidis
@date:  Datum: 17.06.2010

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


/* Includes *************************************************************************************************/


#include "derivative.h"
#include "QH_pll.h"


/* Constants ************************************************************************************************/


static const uint32 OSCCLK =  4000000;  /* oscillator clock */
static const uint32 BUSCLK = 24000000;  /* bus clock */


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* pllInit() configures the internal PLL to generate 24MHz bus clock, using a 4MHz oscillator; this         */
/* function must be called before any other pll...() function                                               */
/*----------------------------------------------------------------------------------------------------------*/
void pllInit(void)
{   
  CLKSEL_PLLSEL = 0;			  /* disconnect CPU clock from PLL */
  PLLCTL = 0xF1;			      /* turn on PLL and clock monitor */
  
  SYNR  = 5;		            /* SYNR and REFDV setting for 24MHz SYSCLK = MCLK, using a 4Mhz quartz */
  REFDV = 0;
  
  while (CRGFLG_LOCK != 1); /* wait untill PLL has locked */
  CLKSEL_PLLSEL = 1;        /* connect CPU clock to PLL clock */
}

/*----------------------------------------------------------------------------------------------------------*/
/* pllGetOscclk() returns the frequency of the oscillator (quartz) in [Hz]                                  */
/*   return value:  the oscillator frequency in [Hz]                                                        */
/*----------------------------------------------------------------------------------------------------------*/
uint32 pllGetOscclk(void)
{
  return OSCCLK;
}

/*----------------------------------------------------------------------------------------------------------*/
/* pllGetBusclk() returns the output frequency of the PLL (bus clock) in [Hz]                               */
/*   return value:  the bus frequency in [Hz]                                                               */
/*----------------------------------------------------------------------------------------------------------*/
uint32 pllGetBusclk(void)
{
  return BUSCLK;
}