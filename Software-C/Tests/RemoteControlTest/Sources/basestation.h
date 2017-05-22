/*************************************************************************************************************


@file:  basestation.h
@autor: Marc Weber
@date:  Datum: 19.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to communicate with the base station</h2>


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


#ifndef BASESTATION_H
  #define BASESTATION_H


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* basestation() checks for a received message sent by the base station and reacts correspondingly; this    */
/* function must be executed every 100 ms                                                                   */
/*----------------------------------------------------------------------------------------------------------*/
  void basestation(void);


/************************************************************************************************************/


#endif