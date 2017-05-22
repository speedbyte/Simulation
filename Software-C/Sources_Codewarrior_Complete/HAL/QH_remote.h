/*************************************************************************************************************


@file:  QH_remote.h
@autor: Marc Weber
@date:  Datum: 17.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to receive the remote control PPM signal</h2>


CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be called before!
         - Timer channel 0 (IOC0) is internally used to measure the pulse width of the signals in the PPM
           frame. A timer frequency of 1MHz is assumed. Therefore timerInit() must be called before! Don't
           use timer channel 0 outside of this file!


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


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* remoteInit() configures the timer channel 0 (IOC0) to receive the remote control PPM signal; in an       */
/* interrupt service routine, the signal values are transferred to the                                      */
/* CAUTION: the timer is disabled for a short time to configure the delay behavior                          */
/*----------------------------------------------------------------------------------------------------------*/
  void remoteInit(void);

/*----------------------------------------------------------------------------------------------------------*/
/* remoteGetValues() gets the actual values of the remote control (raw value for the desired force, yaw     */
/* velocity and pitch/roll angle) and writes them to the CopterState structure; also the flags              */
/* indicating if the motors should be on and if the remote connection is ok are set/reset                   */
/*----------------------------------------------------------------------------------------------------------*/
  void remoteGetValues(void);

 void calcPhysicalValuesFromRemote( CopterState* copterState);
/************************************************************************************************************/


#endif