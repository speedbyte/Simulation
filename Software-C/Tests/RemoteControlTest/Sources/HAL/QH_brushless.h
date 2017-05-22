/*************************************************************************************************************


@file:  QH_brushless.h
@autor: Marc Weber
@date:  Datum: 17.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to control the brushless controllers over Inter-Integrated Circuit 0 (IIC0)</h2>


CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be called before!


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


#ifndef QH_BRUSHLESS_H
  #define QH_BRUSHLESS_H


/* Includes *************************************************************************************************/


  #include "QH_brushless.h"
  #include "typedef.h"


/* Defines **************************************************************************************************/


  #define MOTOR_FRONT      0
  #define MOTOR_REAR       1
  #define MOTOR_RIGHT      2
  #define MOTOR_LEFT       3
  

/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* brushlessInit() configures the IIC bus to work with the brushless controllers; 200kHz IIC clock; this    */
/* function must be called before any other brushless...() function                                         */
/*----------------------------------------------------------------------------------------------------------*/
  void brushlessInit(void);

/*----------------------------------------------------------------------------------------------------------*/
/* brushlessSetRpm() sets a new rounds per minute (RPM) setpoint for one brushless controller               */
/*   - motorAddress:  the motor of which the setpoint is changed; please use the appropriate defines        */
/*   - setpoint:      the new setpoint for the motor (PWM duty cycle of the 3-phase control)                */
/*   return value:    0:  if the parameter "motorAddress" is in the range between one and four              */
/*                    1:  if the parameter "motorAddress" is greater than three (no such brushless          */
/*                        controller available)                                                             */
/*----------------------------------------------------------------------------------------------------------*/
  uint8 brushlessSetRpm(uint8 motorAddress, uint8 setpoint);


/************************************************************************************************************/


#endif