/*************************************************************************************************************


@file:    flightcontrol.h
@author:  Sreekanth Sundaresh
@date:    05.06.2010

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


#ifndef FLIGHTCONTROL_H
  #define FLIGHTCONTROL_H
  
  
/* Defines **************************************************************************************************/


  #define THRUST2SETPOINT_DATAPOINTS    3
  
  #define FLIGHT_CONTROL_SAMPLE_TIME   10
  
  
/* Functions ************************************************************************************************/


  void flightControl(void);


/************************************************************************************************************/


#endif