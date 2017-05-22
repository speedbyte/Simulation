/*************************************************************************************************************


@file:  QH_led.h
@autor: Marc Weber
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


#ifndef QH_LED_H
  #define QH_LED_H


/* Includes *************************************************************************************************/


  #include "typedef.h"


/* Defines **************************************************************************************************/


  #define GREEN_LED 0x01
  #define RED_LED   0x02
  #define BOTH_LEDS 0x03


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* ledInit() configures the hardware so that the LEDs can be used; this function must be called before any  */
/* other led...() function                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
  void ledInit(void);

/*----------------------------------------------------------------------------------------------------------*/
/* ledOn() turns one or both LED(s) on, dependent on the parameter                                          */
/*   - led:         specifies the LED(s) turned on (use GREEN_LED, RED_LED or BOTH_LEDS)                    */
/*   return value:  0:  if the parameter "led" is in the range between one and three                        */
/*                  1:  if the parameter "led" is zero or greater than three                                */
/*----------------------------------------------------------------------------------------------------------*/
  uint8 ledOn(uint8 led);

/*----------------------------------------------------------------------------------------------------------*/
/* ledOff() turns one or both LED(s) off, dependent on the parameter                                        */
/*   - led:         specifies the LED(s) turned off (use GREEN_LED, RED_LED or BOTH_LEDS)                   */
/*   return value:  0:  if the parameter "led" is in the range between one and three                        */
/*                  1:  if the parameter "led" is zero or greater than three                                */
/*----------------------------------------------------------------------------------------------------------*/
  uint8 ledOff(uint8 led);

/*----------------------------------------------------------------------------------------------------------*/
/* ledToggle() toggles one or both LED(s), dependent on the parameter                                       */
/*   - led:         specifies the LED(s) toggled (use GREEN_LED, RED_LED or BOTH_LEDS)                      */
/*   return value:  0:  if the parameter "led" is in the range between one and three                        */
/*                  1:  if the parameter "led" is zero or greater than three                                */
/*----------------------------------------------------------------------------------------------------------*/
  uint8 ledToggle(uint8 led);


/************************************************************************************************************/


#endif