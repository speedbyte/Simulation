/*****************************************************************************************

@file:  simu_data_sources.h
@autor: Max Pejs
@date:  Datum: 02.06.2011

Copyright (C) 2011 University of Applied Sciences Esslingen

$Id:$
$Rev:$

<h2> some dummy data for gps receiver test </h2>

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
#ifndef DATA_SOURCES_H
  #define DATA_SOURCES_H
#include "../typedef.h"

// NMEA string for checksum calculation only!!! (chars between '$' and '*' only)
static char * NMEA_string_checksum_calc_1 = "GPRMC,162614,A,5230.5900,N,01322.3900,E,10.0,90.0,131006,1.2,E,A";	// checksum 0x13
static char * NMEA_string_checksum_calc_2 = "GPRMC,162614,A,4830.3900,N,01627.9900,E,10.0,20.0,131006,1.2,E,A";	// checksum 0x1F
static char * NMEA_string_checksum_calc_3 = "GPRMC,157890,V,0000.0000,S,12347.9879,W,11.7,31.1,010611,2.5,E,A";	// checksum 0x09

// NMEA strings for state machine testing 
static char * NMEA_string_state_machine_1 = "$GPRMC,162614,A,5230.5900,N,01322.3900,E,10.0,90.0,131006,1.2,E,A*13";
static char * NMEA_string_state_machine_2 = "$GPRMC,162614,A,4830.3900,N,01627.9900,E,10.0,20.0,131006,1.2,E,A*1F";
// string with wrong checksum
static char * NMEA_string_state_machine_3 = "$GPRMC,954123,E,4878.4578,W,01627.9890,E,11.2,23.5,136007,1.2,E,A*1F";
// string with empty fields data and time fields
static char * NMEA_string_state_machine_4 = "$GPRMC,,E,4878.4578,W,01627.9890,E,11.2,23.5,,1.2,E,A*04";

#endif // DATA_SOURCES_H
  
