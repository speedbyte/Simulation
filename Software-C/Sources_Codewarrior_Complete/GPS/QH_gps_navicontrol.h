/*****************************************************************************************

@file:  QH_gps_navicontrol.h
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
| University of Applied Sciences
|_

Subject:	Student Research Project
Faculty:	Information Technology
			Technical Informatics

Project Quadrocopter

*****************************************************************************************/

#ifndef QH_GPS_NAVICONTROL_H
  #define QH_GPS_NAVICONTROL_H

/* Includes *****************************************************************************/
#include "typedef.h"
#include "QH_gps_app.h"

/* Defines ******************************************************************************/
#define METERS_PER_DEGREE	111307		// 1 degree on equator corresponds to 113307 m

/* Functions ****************************************************************************/
/**---------------------------------------------------------------------------------------
*	Calculates the distance in meters between two geografical positions
----------------------------------------------------------------------------------------*/
uint32 calcDistance( GeograficPosition pos1, GeograficPosition pos2);

#endif	//	QH_GPS_NAVICONTROL_H
