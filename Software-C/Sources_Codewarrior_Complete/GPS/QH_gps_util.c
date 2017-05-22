/*****************************************************************************************

@file:  QH_gps_util.c
@autor: Max Pejs
@date:  Datum: 07.05.2011

Copyright (C) 2011 University of Applied Sciences Esslingen

$Id:$
$Rev:$

<h2>Functions for automatic navigation and distance calculation</h2>

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
/* Includes *****************************************************************************/
#include <stdlib.h> 
#include "typedef.h"
#include "QH_gps_navicontrol.h"
#include "QH_gps_util.h"

/* Functions ****************************************************************************/
uint8 calcCRC8( uint8 * data )
{ 
  uint8 i = 0;
  uint8 XOR = 0;
  int32 iLen = strlen((const int8*)data);
  for (i = 0; i < iLen; i++)             /* loop for each data byte */
  {
    XOR^=data[i];
  }
  return XOR;
}

/*--------------------------------------------------------------------------------------*/
uint8 nibbleToAscii(uint8 v)
{
	uint8 ret;
	if (v > 9)
	{
		ret = (v + 'A') - 10;
	}
	else
	{
		ret = v + '0';
	}
	return ret;
}

/*--------------------------------------------------------------------------------------*/
uint8 asciiToNibble(uint8 c)
{
	uint8 v;
	if (c > '9')
	{
		v = (c  + 10) - 'A';
	}
	else
	{
		v = c - '0';
	}
	return v;
}

/*---------------------------------------------------------------------------------------*/
int32 myAtofasint32(uint8* ptr)
{ 
  int32 result = 0;
  uint8 cnt = 0;
  int8 * end = 0;
  
  while( 0 != ptr[cnt] )
  {
     if('.' == ptr[cnt] ) // when the dot was found
     {
        break;
     }
     cnt++;
  }
  while( 0 != ptr[cnt] )
  {
    ptr[cnt] = ptr[cnt+1];
    cnt++;
  }
  // convert string to long(32 bit), don't use atoi(...), on HCS12 it works for max 
  // 16 bit values
  return (int32)strtol((const int8*) ptr, &end, 10);
}

/*--------------------------------------------------------------------------------------*/
int32 convMinToDeg(uint8* p) 
{
  int32 position = myAtofasint32(p);
  uint8 digit = 0;
  
  position = position * 100;
  position = (int32)(position/6);
  digit = (uint8)(position%10);
 
  if(digit > 5)
  {
    position += 10 - digit;
  }
  else
  {
    position -= digit;
  }
  
  position = (int32)(position/10);
	return position;
}

/*--------------------------------------------------------------------------------------*/
uint8 myAtouint8(uint8* p)
{
	return (uint8)atoi((const int8*)p);
}

/*--------------------------------------------------------------------------------------*/
uint8 getSqrtPrecision(uint32 value)
{
	if( value > 1000000000 )
		return 18;
	if( value >	100000000 )
		return 17;
	if( value >	10000000 )
		return 15;
	if( value >	1000000 )
		return 13;
	if( value >	100000 )
		return 11;
	if( value >	10000 )
		return 10;
	if( value >	1000 )
		return 8;
	if( value >	100 )
		return 6;
	if( value >	10 )
		return 3;

	return 2;
}

/*--------------------------------------------------------------------------------------*/
uint32 calcSQRT(uint32 value)
{
	uint32 calcVal = value/2;
	uint32 i = 0;
	uint8 n;
	
	if(value <= 0) {return 0;}
	n = getSqrtPrecision(value);
	for(i = 0; i<n; ++i)
	{
		calcVal = ((calcVal + (value/calcVal)) / 2 );
	}
	return calcVal;
}

/*--------------------------------------------------------------------------------------*/
uint16 rnd(uint16 value)
{
	uint8 digit;

	digit = value % 10;
	if(digit > 5)
	{
		value = value + (10-digit);
	}
	else
	{
		value = value - digit;
	}
	return value;
}