/*************************************************************************************************************


@file:  QH_atd.c
@autor: Marc Weber, inspired by Dionysios Satikidis
@date:  Datum: 17.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to control the analog to digital converter unit (ATD), used for gyroscope (roll, pitch and yaw),
    temperature, air pressure and battery voltage evaluation</h2>


CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be called before!
         - The controller derivative MC9S12XDT256 has 16 ATD channels, but they belong to two different ATD 
           units; AN0 to AN7 belong to the unit ATD0 (eight channels), while AN8 to AN15 belong to ATD1 (16
           channels but only eight of them are used / connected to pins); AN8 is channel zero of ATD1


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


#include "copter.h"
#include "derivative.h"
#include "QH_atd.h"
#include "typedef.h"
#include "sensorfilter.h"


/* Variables ************************************************************************************************/


/* calibration variables */
static int16 gyroZeroMaxDiff = 335;
static int16 temp25To50Diff = 41;


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* atdInit() configures the analog to digital converters (ATD) for the gyroscope, temperature, air pressure */
/* and battery voltage evaluation; 10 bit conversion resolution; this function must be called before any    */
/* other atd...() function                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
void atdInit(void)
{
  ATD0CTL0 = 0x06;  /* wrap around to AN0 after converting AN6 */
  
  ATD0CTL2 = 0x80;  /* bit 7:       normal ATD functionality */
                    /* bit 6:       normal flag clearing mode */
                    /* bit 5:       ATD continues to run in wait mode */
                    /* bit 4 to 2:  disable external trigger mode */
                    /* bit 1:       disable ATD sequence complete interrupt */
                    /* bit 0:       interrupt flag, writing has no effect */
   
  ATD0CTL3 = 0x38;  /* bit 6 to 3:  conversion sequence length of seven (AN0 to AN6) */
                    /* bit 2:       no FIFO mode */
                    /* bit 1 to 0:  continue conversion during freeze mode (debugging breakpoint) */
                   
  ATD0CTL4 = 0x05;  /* bit 7:       10 bit resolution */
                    /* bit 6 to 5:  second phase of sample time is two ATD clock periods */
                    /* bit 4 to 0:  ATD clock prescaler (PRS); ATD clock = (bus clock / (PRS + 1)) * 0.5 */
  
  ATD0CTL5 = 0x90;  /* bit 7:       right justified data in the result registers */
                    /* bit 6:       unsigned data representation */
                    /* bit 5:       single conversion sequence (started by writing ATD0CTL5) */
                    /* bit 4:       multi-channel sample mode */
                    /* bit 3 to 0:  AN0 is starting channel for the conversion sequence */
  
  ATD1CTL2 = 0x80;  /* see description of ATD0CTL2 */
  
  ATD1CTL3 = 0x08;  /* bit 6 to 3:  conversion sequence length of one (AN8) */
                    /* see description of ATD0CTL3 */
  
  ATD1CTL4 = 0x05;  /* see description of ATD0CTL4 */
  
  ATD1CTL5 = 0x80;  /* bit 7:       right justified data in the result registers */
                    /* bit 6:       unsigned data representation */
                    /* bit 5:       single conversion sequence (started by writing ATD1CTL5) */
                    /* bit 4:       sample single channel */
                    /* bit 3 to 0:  AN8 is the channel to sample */

}

/*----------------------------------------------------------------------------------------------------------*/
/* atdCalibrate() calculates the zero level offset of the gyroscopes (roll, pitch and yaw); this function   */
/* should be called before the first call of atdGetValues()                                                 */
/* CAUTION: to get right offset values, the copter must be in rest                                          */
/*----------------------------------------------------------------------------------------------------------*/
void atdCalibrate(void)
{
  /* get pointer to the CopterState structure (real-time database) */
 CopterState* copterState = copterGetStatePtr();

  ATD0CTL5 = 0x90;                  /* start new conversion sequence; ATD0STAT0_SCF is cleared automatically*/
  while (ATD0STAT0_SCF != 1);       /* wait till conversion sequence is finished */
  
  /* calculate the offset values for the gyroscopes */
  copterState->r_Pitch_filt = copterState->gyroPOffset = ATD0DR0 & 0x03FF;
  copterState->r_Roll_filt = copterState->gyroROffset = ATD0DR1 & 0x03FF;
  copterState->r_Yaw_filt = copterState->gyroYOffset = ATD0DR2 & 0x03FF;
  
  /* CAUTION - FURTHER IMPROVEMENTS: - use the self test functionality of the gyroscopes */
  /*                                 - include temperature in calculation */
}

/*----------------------------------------------------------------------------------------------------------*/
/* atdGetValues() gets the actual values of all analog inputs (raw and physical value for gyroscopes,       */
/* temperature, air pressure and battery voltage) and writes them to the CopterState structure              */
/*----------------------------------------------------------------------------------------------------------*/
void atdGetValues(void)
{
  /* get pointer to the CopterState structure (real-time database) */
 CopterState* copterState = copterGetStatePtr();

  ATD0CTL5 = 0x90;                  /* start new conversion sequence; ATD0STAT0_SCF is cleared automatically*/
  while (ATD0STAT0_SCF != 1);       /* wait till conversion sequence is finished */
  
  ATD1CTL5 = 0x80;                  /* start new conversion sequence; ATD1STAT0_SCF is cleared automatically*/
  while (ATD1STAT0_SCF != 1);       /* wait till conversion sequence is finished */
  
  /* write the 10bit (each value) conversion data to the variables */
  copterState->angVelPRaw     = ATD0DR0 & 0x03FF;
  copterState->angVelRRaw     = ATD0DR1 & 0x03FF;
  copterState->angVelYRaw     = ATD0DR2 & 0x03FF;
  copterState->tempRaw        = ATD0DR5 & 0x03FF;
  copterState->airPressureRaw = ATD0DR6 & 0x03FF;
  copterState->batteryRaw     = ATD1DR0 & 0x03FF;
  
  // Calculating physical values should be called in the an other function ? 
  (void) atdCalculatePhysicalValues(copterState);
}

void atdCalculatePhysicalValues(CopterState* copterState) 
{
 /* calculate physical values out of raw values; yaw rates in [(100 * rad)/sec], temperature in [°C] and */
  /* battery voltage in [10 * V] */
  /* 24.10 korrigiere Auflösung der Gyroskope*/
   copterState->angVelP     = -(int16)(HP_Filter((float)(copterState->angVelPRaw),&(copterState->r_Pitch_filt)) * 0.938349);//* 524) / gyroZeroMaxDiff);
   copterState->angVelR     = (int16)(HP_Filter((float)(copterState->angVelRRaw),&(copterState->r_Roll_filt)) * 0.938349);//* 524) / gyroZeroMaxDiff);
   copterState->angVelY     = -(int16)(HP_Filter((float)(copterState->angVelYRaw),&(copterState->r_Yaw_filt)) * 0.938349);//* 524) / gyroZeroMaxDiff);
   copterState->temp        = (int16)((((copterState->tempRaw - 512) * 25) / temp25To50Diff) + 25);
   copterState->battery     = (int16)(((int32)copterState->batteryRaw * 363) >> 10); 
   
}

