/*************************************************************************************************************


@file:  QH_atd.h
@autor: Marc Weber
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


#ifndef QH_ATD_H
  #define QH_ATD_H


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* atdInit() configures the analog to digital converters (ATD) for the gyroscope, temperature, air pressure */
/* and battery voltage evaluation; 10 bit conversion resolution; this function must be called before any    */
/* other atd...() function                                                                                  */
/*----------------------------------------------------------------------------------------------------------*/
  void atdInit(void);

/*----------------------------------------------------------------------------------------------------------*/
/* atdCalibrate() calculates the zero level offset of the gyroscopes (roll, pitch and yaw); this function   */
/* should be called before the first call of atdGetValues()                                                 */
/* CAUTION: to get right offset values, the copter must be in rest                                          */
/*----------------------------------------------------------------------------------------------------------*/
  void atdCalibrate(void);

/*----------------------------------------------------------------------------------------------------------*/
/* atdGetValues() gets the actual values of all analog inputs (raw and physical value for gyroscopes,       */
/* temperature, air pressure and battery voltage) and writes them to the CopterState structure              */
/*----------------------------------------------------------------------------------------------------------*/
  void atdGetValues(void);


/*----------------------------------------------------------------------------------------------------------*/
/* atdCalcPhysicalValues() Calculates the physical Values from the attached sensors       */
/*----------------------------------------------------------------------------------------------------------*/
  void atdCalculatePhysicalValues(CopterState* copterState);


/************************************************************************************************************/


#endif