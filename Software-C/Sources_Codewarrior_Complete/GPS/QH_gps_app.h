/*****************************************************************************************

@file:  QH_gps_app.h
@autor: Max Pejs
@date:  Datum: 17.04.2011

Copyright (C) 2011 University of Applied Sciences Esslingen

$Id:$
$Rev:$

<h2>Functions to init GPS modul, receive GPS data from modul and parse the data</h2>


CAUTION: -	To work probably, a bus clock of 24MHz is required. Therefore pllInit() 
		must be called before!
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

#ifndef QH_GPS_APP_H
  #define QH_GPS_APP_H

/* Includes *****************************************************************************/
#include "typedef.h"
#include "QH_gps_os_interface.h"
#include "string.h"

/* Defines ******************************************************************************/
#define RX_MESSAGE_BUFFER_SIZE		81
#define TX_MESSAGE_BUFFER_SIZE		81
#define RMC_DATA_UPDATE_FIX		    1		// number of fixes on which NMEA 0183 RMC 
											                // should be outputed. 1 means every 200 ms.
										                	// 5 means every second (at 5 fixes per second)
#define DEFAULT_BAUD_RATE			    9600	// default baud rate
#define RMC_FIELD_MIN_LEN			    12		// (!) DON'T CHANGE 
#define SPEED_FACTOR_KNOTS_TO_MS	51444	// 51444*10^-5 Factor for converting speed 
											                  // from knots into m/s
#define PRECISION_SPEED_FACTOR		100000
#define PRECISION_GPS				      1000000

/* typedefs *****************************************************************************/

/**---------------------------------------------------------------------------------------
* The RMCmsg struct contains every data of the NMEA0183 RMC format. For more details, 
* please see 'GPSdevice_Communication.docx'
*---------------------------------------------------------------------------------------*/
typedef struct
{
	uint8  Hour;
	uint8  Minute;					
	uint8  Second;					
	uint8  DataValid;			    // A - Data valid, V - data not valid
	int32  Latitude;			    // latitude
	int32  Longitude;			    // longitude
	uint16 Ground_speed_ms;			// speed over ground (m/s) * 10^-2
	uint16 Ground_course;			// course over ground in degrees * 10^-2
	uint8  Day;						// date
	uint8  Month;				  
	uint16 Year;				  
	int32  MagVar;				    // magnetic variation, East(+)/West(-) in degrees
}RMCmsg;

/**---------------------------------------------------------------------------------------
* The struct contains current geografic position. Latitude and Longitude. 
*---------------------------------------------------------------------------------------*/
typedef struct
{
	int32  Latitude;			 // latitude
	int32  Longitude;			 // longitude
}GeograficPosition;

/**---------------------------------------------------------------------------------------
* The struct contains time data.
*---------------------------------------------------------------------------------------*/
typedef struct
{
	uint8  Hour;					// Time
	uint8  Minute;					
	uint8  Second;
}GPSTime;

/**---------------------------------------------------------------------------------------
* The struct contains date data.
*---------------------------------------------------------------------------------------*/
typedef struct
{
	uint8  Day;						// date
	uint8  Month;				  
	uint16 Year;
}GPSDate;

/**---------------------------------------------------------------------------------------
* The NP_state enum  represents states of the NMEA state machine.
*---------------------------------------------------------------------------------------*/
typedef enum 
{
	NP_SOS = 0,					// wait for "Start Of Sequence"
	NP_GET_DATA,				// get NMEA data string
	NP_CHK_1,					// get first checksum char
	NP_CHK_2,					// get second checksum char
}states;
		

/* Functions ****************************************************************************/
/**---------------------------------------------------------------------------------------
*	Initialize the serial port SCI2 and synchronize the baud rate
*	CAUTION: Call gpsInit() only after the GPS-Device was connected. Call before enabling
* interrupts
----------------------------------------------------------------------------------------*/
void gpsInit(void);

/**---------------------------------------------------------------------------------------
*	Function stores whole RMC struct into parameter m
*	param:		m			pointer to struct where data schould be copy to
*	return:		status		true if	data were copied succesfully
*							false if the data could not be accessed
*---------------------------------------------------------------------------------------*/
bool getRMCdata(RMCmsg * m);

/**---------------------------------------------------------------------------------------
*	Function stores the gps data (latitude and longitude) into parameter m 
*	param:			
*		m					pointer to struct where data schould be copy to
*	return value:	
*		status				0 if data were copied succesfully but they are invalid
*							1 if data were copied succesfully
*							-1 if the data could not be accessed
*							false if data were not updated,because memory couldn't be 
*							accessed
*---------------------------------------------------------------------------------------*/
int8 getCurrentGeogrPos(GeograficPosition * m);

/**---------------------------------------------------------------------------------------
*	Function stores whole RMC struct into parameter m and checks if the time was updated.
*	The old time (since last call) must be stored in the struct *m
*	param:		m			pointer to struct where data schould be copy to
*	return:		status		true if	data were copied succesfully
*							false if the data could not be accessed
*---------------------------------------------------------------------------------------*/
bool getCurrentTime(GPSTime * m);

/**---------------------------------------------------------------------------------------
*	Function stores whole RMC struct into parameter m
*	param:		m			pointer to struct where data schould be copy to
*	return:		status		true if	data were copied succesfully
*							false if the data could not be accessed
*---------------------------------------------------------------------------------------*/
bool getCurrentDate(GPSDate * m);

//****************************** JUST FOR TESTING ****************************************
/**---------------------------------------------------------------------------------------
*	This function represent a state machine for data receiving. This function is listed
*	in interface because of testing.
*	CAUTION! DON'T MAKE ANY CALL OF THIS FUNCTION. IT CAN LEAD TO WRONG WORK. THIS
*	FUNCTION WILL BE CALLED BY INTERRUPT.
*	
*	parameters:
*		recvByte		a received NMEA-String character
*---------------------------------------------------------------------------------------*/
void processNMEAbyte(char recvByte);

/**---------------------------------------------------------------------------------------
*	Synchronize iteratively the baud rates of the µController an the GPS-receiver. This
*	function is listed in interface because of testing.
*	CAUTION! DON'T MAKE ANY CALL OF THIS FUNCTION. IT CAN LEAD TO WRONG WORK OR CRASH
*	OF QUADROCOPTER. THIS FUNCTION WILL BE CALLED AUTOMATICALLY IN  THE FUNCTION
*	gpsInit, SEE ABOVE.
*---------------------------------------------------------------------------------------*/
void syncBaudRate(void);

#endif	//	QH_GPS_APP_H