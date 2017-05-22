/*************************************************************************************************************


@file:  QH_brushless.c
@autor: Marc Weber
@date:  Datum: 19.04.2010

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


/* Includes *************************************************************************************************/


#include "derivative.h"
#include "QH_brushless.h"
#include "typedef.h"


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* brushlessInit() configures the IIC bus to work with the brushless controllers; 200kHz IIC clock; this    */
/* function must be called before any other brushless...() function                                         */
/*----------------------------------------------------------------------------------------------------------*/
void brushlessInit(void)
{
  IIC0_IBFD = 0x85; /* 200kHz IIC clock at 24MHz bus clock; the value of this register is chosen according */
                    /* to the microcontroller datasheet, see section 9.3.2 */
                    
  IIC0_IBCR = 0x80; /* enable IIC module, disable interrupts */
  IIC0_IBSR = 0x12; /* clear status flags */
}

/*----------------------------------------------------------------------------------------------------------*/
/* brushlessSetRpm() sets a new rounds per minute (RPM) setpoint for one brushless controller               */
/*   - motorAddress:  the motor of which the setpoint is changed; please use the appropriate defines        */
/*   - setpoint:      the new setpoint for the motor (PWM duty cycle of the 3-phase control)                */
/*   return value:    0:  if the parameter "motorAddress" is in the range between one and four              */
/*                    1:  if the parameter "motorAddress" is greater than three (no such brushless          */
/*                        controller available)                                                             */
/*----------------------------------------------------------------------------------------------------------*/
uint8 brushlessSetRpm(uint8 motorAddress, uint8 setpoint)
{
  if (motorAddress <= 3)
  {
    while (IIC0_IBSR_IBB);                    /* wait until bus is free */
    IIC0_IBCR_TXAK  = 0;
    IIC0_IBCR_TX_RX = 1;                      /* transmit data */
    IIC0_IBCR_MS_SL = 1;                      /* switch to master mode */
    
    IIC0_IBDR = (0x52 + (motorAddress * 2));  /* send address of brushless controller */
    while (!IIC0_IBSR_IBIF);                  /* wait until byte is sent */
    IIC0_IBSR_IBIF = 1;                       /* clear transmission complete flag*/
    
    IIC0_IBDR = setpoint;                     /* send setpoint */
    while (!IIC0_IBSR_IBIF);                  /* wait until byte is sent */
    IIC0_IBSR_IBIF = 1;                       /* clear transmission complete flag */
    
    IIC0_IBCR_MS_SL = 0;                      /* switch to slave mode */
    IIC0_IBCR_TX_RX = 0;                      /* receive data */
    
    return 0;
  }
  return 1;
}