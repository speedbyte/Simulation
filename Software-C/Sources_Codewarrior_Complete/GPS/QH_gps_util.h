/*****************************************************************************************

@file:  QH_gps_util.h
@autor: Max Pejs
@date:  Datum: 07.05.2011

Copyright (C) 2011 University of Applied Sciences Esslingen

$Id:$
$Rev:$

<h2> Utility functions </h2>

------------------------------------------------------------------------------------------
 _
|
| Hochschule Esslingen
| University of Applied Sciencs
|_

Subject:	Student Research Project
Faculty:	Information Technology
			Technical Informatics

Project Quadrocopter

*****************************************************************************************/

#ifndef QH_GPS_UTIL_H
  #define QH_GPS_UTIL_H


/* Includes *****************************************************************************/
#include "typedef.h"


/* Functions ****************************************************************************/
/**---------------------------------------------------------------------------------------
*	Calculates the 8 bits checksum from a string
*---------------------------------------------------------------------------------------*/
uint8 calcCRC8( uint8 * data );

/**---------------------------------------------------------------------------------------
*	Converts a nibble to ASCII char
*---------------------------------------------------------------------------------------*/
uint8 nibbleToAscii(uint8 v);

/**---------------------------------------------------------------------------------------
*	Converts an ASCII char to a nibble
*---------------------------------------------------------------------------------------*/
uint8 asciiToNibble(uint8 c);

/**---------------------------------------------------------------------------------------
*	Funtction to convert a minutes to degrees
*	example:	58.4545 minutes / 60 minutes/degree = 974241 (* 10^-6) degree
*---------------------------------------------------------------------------------------*/
int32 convMinToDeg(uint8* p);

/**---------------------------------------------------------------------------------------
*	myAtofasint32 means "array to float as signed integer 32Bit". The float value is 
*	stored as string and will be coverted to 32 bit integer without dot.
*---------------------------------------------------------------------------------------*/
int32 myAtofasint32(uint8* ptr);

/**---------------------------------------------------------------------------------------
*	Function to avoid a lot of typing the casts in the code
*---------------------------------------------------------------------------------------*/
uint8 myAtouint8(uint8* p);

/**---------------------------------------------------------------------------------------
*   calculates a square root of a value. Function uses numerical method Heron-Method
*---------------------------------------------------------------------------------------*/
uint32 calcSQRT(uint32 value);

/**---------------------------------------------------------------------------------------
*   rounds a number the last digit. E.g. 437 will be rounded to 440 and 432 will be 
*	rounded to 430
*---------------------------------------------------------------------------------------*/
uint16 rnd(uint16 value);

#endif	//	QH_GPS_UTIL_H
