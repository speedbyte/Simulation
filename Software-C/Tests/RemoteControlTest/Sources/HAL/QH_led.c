/*************************************************************************************************************


@file:  QH_led.c
@autor: Marc Weber, inspired by Dionysios Satikidis
@date:  Datum: 17.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to control the LEDs</h2>


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
#include "QH_led.h"
#include "typedef.h"


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* ledInit() configures the hardware so that the LEDs can be used; this function must be called before any  */
/* other led...() function                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
void ledInit(void)
{
  DDRA 	= DDRA | 0x03;  /* configure PA0 and PA1 as output */
  PORTA = PORTA & 0xFC; /* switch both LEDs off */
}

/*----------------------------------------------------------------------------------------------------------*/
/* ledOn() turns one or both LED(s) on, dependent on the parameter                                          */
/*   - led:         specifies the LED(s) turned on (use GREEN_LED, RED_LED or BOTH_LEDS)                    */
/*   return value:  0:  if the parameter "led" is in the range between one and three                        */
/*                  1:  if the parameter "led" is zero or greater than three                                */
/*----------------------------------------------------------------------------------------------------------*/
uint8 ledOn(uint8 led)
{
  if ((led <= 3) && (led >= 1))
  {
    PORTA = PORTA | led;
    return 0;
  }
  else
  {
    return 1;
  }
}

/*----------------------------------------------------------------------------------------------------------*/
/* ledOff() turns one or both LED(s) off, dependent on the parameter                                        */
/*   - led:         specifies the LED(s) turned off (use GREEN_LED, RED_LED or BOTH_LEDS)                   */
/*   return value:  0:  if the parameter "led" is in the range between one and three                        */
/*                  1:  if the parameter "led" is zero or greater than three                                */
/*----------------------------------------------------------------------------------------------------------*/
uint8 ledOff(uint8 led)
{
  if ((led <= 3) && (led >= 1))
  {
    PORTA = PORTA & ~led;
    return 0;
  }
  else
  {
    return 1;
  }
}

/*----------------------------------------------------------------------------------------------------------*/
/* ledToggle() toggles one or both LED(s), dependent on the parameter                                       */
/*   - led:         specifies the LED(s) toggled (use GREEN_LED, RED_LED or BOTH_LEDS)                      */
/*   return value:  0:  if the parameter "led" is in the range between one and three                        */
/*                  1:  if the parameter "led" is zero or greater than three                                */
/*----------------------------------------------------------------------------------------------------------*/
uint8 ledToggle(uint8 led)
{
  if ((led <= 3) && (led >= 1))
  {
    PORTA = PORTA ^ led;
    return 0;
  }
  else
  {
    return 1;
  }
}