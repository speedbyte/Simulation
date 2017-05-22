/*************************************************************************************************************


@file:    sensorfilter.h
@author:  Sreekanth Sundaresh
@date:    20.05.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.


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


#ifndef SENSORFILTER_H
  #define SENSORFILTER_H
  
  
/* Defines **************************************************************************************************/


  #define ACC_GRAVITY 98

  #define SENSOR_FILTER_SAMPLE_TIME   10


/* Functions ************************************************************************************************/


  void sensorFilter(void);


/************************************************************************************************************/


#endif