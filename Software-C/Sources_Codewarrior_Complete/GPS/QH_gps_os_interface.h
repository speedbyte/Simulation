/*****************************************************************************************

@file:  QH_gps_os_interface.h
@autor: Max Pejs
@date:  Datum: 31.05.2011

Copyright (C) 2011 University of Applied Sciences Esslingen

$Id:$
$Rev:$

<h2> operating system dependent interface functions </h2>

------------------------------------------------------------------------------------------
 _
|
| Hochschule Esslingen
| University of Applied Sciences
|_

Subject:	Student Research Project
Faculty:	Information Technology
		Technical Informatics

Project Quadrocopter

*****************************************************************************************/

#ifndef QH_GPS_OS_INTERFACE_H
  #define QH_GPS_OS_INTERFACE_H

/* Includes *****************************************************************************/
#include "typedef.h"


/**---------------------------------------------------------------------------------------
*		sends a message over polling operation to gps receiver over serial port
*	param:							
*	    message	the pointer to the message string
*---------------------------------------------------------------------------------------*/
void sendMsgPoll(uint8 * message);

/**---------------------------------------------------------------------------------------
*	Sets the baud rate of the µController
*	param:							
*	    baudrate	set controller to this baud rate
**--------------------------------------------------------------------------------------*/
void setControllerBaudRate(uint16 baudrate);

#endif	//	QH_GPS_OS_INTERFACE_H