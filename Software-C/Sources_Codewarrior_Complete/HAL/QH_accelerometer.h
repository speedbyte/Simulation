/*************************************************************************************************************


@file:  QH_accelerometer.h
@autor: Marc Weber
@date:  Datum: 17.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to control the accelerometer over Serial Peripheral Interface 0 (SPI0)</h2>


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


#ifndef QH_ACCELEROMETER_H
  #define QH_ACCELEROMETER_H


/* Defines **************************************************************************************************/


  #define CTRL_REG_ADR          0x20  /* address of the first control register of the accelerometer */

  #define CTRL_REG1             0xC7//<-40Hz  //0xE7//0xD7<-orginal  /* value of the first control register of the accelerometer */
                                      /* bit 7 to 6: accelerometer on */
                                      /* bit 5 to 4: 160Hz sample frequency of the accelerometer */
                                      /* bit 3:      self test off */
                                      /* bit 2 to 0: enable x, y and z axis */
                                
  #define CTRL_REG2             0xD4//0x54  /* value of the second control register of the accelerometer */
                                      /* bit 7:      plus/minus 6g */
                                      /* bit 6:      output registers not updated until MSB and LSB reading */
                                      /* bit 5:      little endian data representation in the output registers */
                                      /* bit 4:      enable calibration (reboot memory content) */
                                      /* bit 3:      data ready on RDY pad */
                                      /* bit 2:      enable data ready signal generation */
                                      /* bit 1:      4-wire SPI interface */
                                      /* bit 0:      12 bit right justified data alignment in the output registers */
                                
  #define CTRL_REG3             0x00  /* value of the third control register of the accelerometer */
                                      /* bit 7:      internal clock is used */
                                      /* bit 6 to 0: switch off all internal high-pass filter */

  #define ACCEL_REG_ADR         0x28  /* address of the first output register of the accelerometer */

  #define DUMMY                 0xFF  /* byte sent by the master when reading data from the accelerometer */
  
  #define G                      981  /* local gravity constant * 100 -> no floating point */
  
  
/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* accelInit() configures the SPI interface of the microcontroller, so that it can be used to communicate   */
/* with the accelerometer; additionally the accelerometer itself is configured; this function must be       */
/* called before any other accel...() function                                                              */
/*----------------------------------------------------------------------------------------------------------*/
  void accelInit(void);

/*----------------------------------------------------------------------------------------------------------*/
/* accelCalibrate() calculates the zero level offset of the accelerometer (X-, Y- and Z-axis); this         */
/* function should be called before the first call of accelGetValues()                                      */
/* CAUTION: to get right offset values, the copter must stand on a plain ground                             */
/*----------------------------------------------------------------------------------------------------------*/
  void accelCalibrate(void);
  
/*----------------------------------------------------------------------------------------------------------*/
/* accelGetValues() gets the actual values of the accelerometer (raw and physical value for X-, Y- and      */
/* Z-axis) and writes them to the CopterState structure                                                     */
/*----------------------------------------------------------------------------------------------------------*/
  void accelGetValues(void);

/*----------------------------------------------------------------------------------------------------------*/
/* accelCalcPhysicalValues() gets the actual values of the accelerometer (raw and physical value for X-, Y- and      */
/* Z-axis) and writes them to the CopterState structure                                                     */
/*----------------------------------------------------------------------------------------------------------*/
  void accelCalcPhysicalValues(CopterState* copterState);


/************************************************************************************************************/


#endif