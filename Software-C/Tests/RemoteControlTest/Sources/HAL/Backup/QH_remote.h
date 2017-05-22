/*************************************************************************************************************


@file:  QH_remote.h
@autor: Marc Weber
@date:  Datum: 28.04.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to receive the remote control PPM signal, therefor timer channel 0 (IOC0) is used</h2>


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


#ifndef QH_REMOTE_H
  #define QH_REMOTE_H


/* Includes *************************************************************************************************/


  #include "typedef.h"


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* remoteInit() configures the timer channel 0 (IOC0) to receive the remote control PPM signal; in an       */
/* interrupt service routine, the signal values are transferred to the                                      */
/* CAUTION: the timer is disabled for a short time to configure the delay behavior                          */
/*----------------------------------------------------------------------------------------------------------*/
  void remoteInit(void);

/*----------------------------------------------------------------------------------------------------------*/
/* remoteGetSignals() writes the remote control values to the given destination                             */
/*   - remoteSignals: a pointer to the array (eight elements) to which the remote control values are        */
/*                    written                                                                               */
/*   return value:    FALSE(0): if new remote control values are written                                    */
/*                    TRUE (1): if no new remote control values are available                               */
/*----------------------------------------------------------------------------------------------------------*/
  bool remoteGetSignals(uint8* remoteSignals);


/************************************************************************************************************/


#endif