/*****************************************************************************************

@file:  QH_gps_simu.c
@autor: Max Pejs
@date:  Datum: 01.06.2011

Copyright (C) 2011 University of Applied Sciences Esslingen

$Id:$
$Rev:$
<h2> dummy functions for simulation </h2>

------------------------------------------------------------------------------------------
 _
|
| Hochschule Esslingen
| University of Applied Sciencs
|_

Subject:	Student research project
Faculty:	Information Technology
Speciality:	Technical Informatics

Project Quadrocopter
*****************************************************************************************/

/* Includes *****************************************************************************/
#include <stdio.h>
#include "../QH_gps_app.h"
#include "../QH_gps_os_interface.h"


/* Functions ****************************************************************************/
/**---------------------------------------------------------------------------------------
*	simulates an gps initialization function
*---------------------------------------------------------------------------------------*/
void gpsInit(void)
{
	// dummy
	printf("init GPS\n");
	printf("start synchronizing baud rates \n\n");
	syncBaudRate();
}

/**---------------------------------------------------------------------------------------
*	simulates sending a message to gps receiver over serial port
*---------------------------------------------------------------------------------------*/
void sendMsgPoll(uint8 * message)
{
	printf("sending message to GPS receiver in polling operation.\nMessage text: %s", message);
}

/**---------------------------------------------------------------------------------------
*	simulates a setting the µController baud rate
*---------------------------------------------------------------------------------------*/
void setControllerBaudRate(uint16 baudrate)
{
	printf("\nsetting QH-Controller baud rate to: %i\n", baudrate);
}



void RMC_generator(int course, int speed, GeograficPosition lastPos)
{

}