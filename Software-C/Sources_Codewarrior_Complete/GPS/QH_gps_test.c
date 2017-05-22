/*****************************************************************************************

 @file:  QH_gps_test.c
 @autor: Max Pejs
 @date:  Datum: 02.06.2011

 Copyright (C) 2011 University of Applied Sciences Esslingen

 $Id:$
 $Rev:$

 <h2> test functions for gps driver </h2>

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
#include <stdio.h>
#include <math.h>
#include "../QH_gps_app.h"
#include "../QH_gps_navicontrol.h"
#include "../QH_gps_util.h"
#include "../simulation/SIMU_data_sources.h"
#define myPI 3.1415926535897932384626433832795

void testUtilFunc(void);
void testDistCalc(void);
void testStateMachine(void);
void testInit(void);
void testSendmContrToGPS(void);


static uint16 ErrorArr[100];
uint8 GL_ERRORCOUNTER = 0;

void main(void) {
	uint8 i;
	
	printf(" ++++++++++++ STARTING TESTS ++++++++++++\n");
	testUtilFunc();
	testDistCalc();
	testStateMachine();
	testInit();
	testSendmContrToGPS();

	printf("\n\n\n++++++++++++ ERROR REPORT ++++++++++++ \n");
	if( GL_ERRORCOUNTER > 0 )
	{
		printf("Total errors: %i \n\n", GL_ERRORCOUNTER);
		for( i = 0; ErrorArr[i]!=0; ++i)
		{
			printf("Error in the line %i\n", ErrorArr[i]);
		}
	}else
	{
		printf("Congratulations! No errors were found\n\n\n\n");
	}
}

// ***************************************************************************************
void testUtilFunc() {
	uint32 i, UIN32MAX, must, is, difference;
	uint8 testBuff[100];
	bool tmp = FALSE;
//----------
	if (asciiToNibble('0') != 0) {	ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
	if (asciiToNibble('A') != 10) { ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
//----------
	if (nibbleToAscii(15) != 'F') { ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
	if (nibbleToAscii(1) != '1') { ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
//----------
	if (0x13 != calcCRC8((uint8*) NMEA_string_checksum_calc_1)) { ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
	if (0x1F != calcCRC8((uint8*) NMEA_string_checksum_calc_2)) { ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
//----------
	memcpy(testBuff,"42.108\0",7);
	// value 42.108 to 42108
	if (myAtofasint32(testBuff) != 42108) { ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
	memcpy(testBuff,"413.\0",5);
	//	value 413. to 413
	if (myAtofasint32(testBuff) != 413) { ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
//----------
	// check the whole uint32 range. 
	UIN32MAX = (uint32)(pow((double)2,32)-1);
	for(i = 0; i < (UIN32MAX/2); i+=1191)
	{
		is = calcSQRT(i);
		must = (uint32)sqrt((float)i);
		difference = (uint32)abs((double)(is-must));

		// Max allowed difference between the correct and the calculated value is 1
		if ( difference > 1 ) 
		{ 
			ErrorArr[GL_ERRORCOUNTER++] = __LINE__;
		}	
	}
	
	for(i = UIN32MAX; i < (UIN32MAX/2); i-=1191)
	{
		if (calcSQRT(i) != (uint32)sqrt((float)i)) { ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}	//????
	}

//----------
	memcpy(testBuff,"20.4545\0",8);
	if( convMinToDeg(testBuff) != 340908){ ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
	memcpy(testBuff,"30.0000\0",8);
	if( convMinToDeg(testBuff) != 500000){ ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
	memcpy(testBuff,"00.0000\0",8);
	if( convMinToDeg(testBuff) != 0){ ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
	memcpy(testBuff,"59.9999\0",8);
	if( convMinToDeg(testBuff) != 999998){ ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
//----------	
	memcpy(testBuff,"59\0",3);
	if( myAtouint8(testBuff) != 59 ) {ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
	memcpy(testBuff,"255\0",3);
	if( myAtouint8(testBuff) != 255 ) {ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
	memcpy(testBuff,"0000\0",5);
	if( myAtouint8(testBuff) != 0 ) {ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
}

// ***************************************************************************************
void testDistCalc() {
	int32 temp;
	
	// Address: Schwieberdinger Strasse, Stuttgart, Germany
	// distance according to googlemaps 200 meters
	GeograficPosition pos1 = { 48831421, 9160215};
	GeograficPosition pos2 = { 48830462, 9162482};
	
	// Address: highway A8, near Munich
	// distance according to googlemaps 1200 meters
	GeograficPosition pos3 = { 48213649, 11388680};
	GeograficPosition pos4 = { 48207267, 11400933};

	// Address: highway A8, near Munich
	GeograficPosition pos5 = { 48213649, 11388680};
	GeograficPosition pos6 = { 48213649, 11388681};

	// Address: 
	// distance according to googlemaps 
	GeograficPosition pos7 = { 48213649, 11388680};
	GeograficPosition pos8 = { 48213652, 11388681};

	// Address: Jean Lolive, France
	// distance according to googlemaps 7,4 km
	GeograficPosition pos9 = { 48890629, 2399820};
	GeograficPosition pos10= { 48907871, 2493412};
	
	temp = (int32)calcDistance(pos1, pos2) - 200;	
	if( temp < 0 ){temp=-temp;}
	if( temp > 10 ){ErrorArr[GL_ERRORCOUNTER++] = __LINE__; }
	
	temp = (int32)calcDistance(pos3, pos4) - 1200;	
	if( temp < 0 ){temp=-temp;}
	if( temp > 10 ){ErrorArr[GL_ERRORCOUNTER++] = __LINE__; }

	temp = (int32)calcDistance(pos5, pos6) - 0;		
	if( temp < 0 ){temp=-temp;}
	if( temp > 10 ){ErrorArr[GL_ERRORCOUNTER++] = __LINE__; }

	temp = (int32)calcDistance(pos9, pos10) - 7400;	
	if( temp < 0 ){temp=-temp;}
	if( temp > 10 ){ErrorArr[GL_ERRORCOUNTER++] = __LINE__; }
}

// ***************************************************************************************
void testStateMachine() {
	uint8 ERRORCOUNTER = 0;
	GPSDate myDate;
	GeograficPosition myPos;
	uint32 i;

	// TEST #1
	// receive nmea string
	for (i = 0; i < strlen(NMEA_string_state_machine_1); ++i) {
		processNMEAbyte(NMEA_string_state_machine_1[i]);
	}

	// read gps data
	getCurrentGeogrPos(&myPos);
	if( (myPos.Latitude != 52509833) || (myPos.Longitude != 13373167) )	{ ErrorArr[GL_ERRORCOUNTER++] = __LINE__;	}
	getCurrentDate(&myDate);
	if ((myDate.Day != 13) || (myDate.Month != 10) || (myDate.Year != 2006)) { ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}

	// TEST  #2
	// receive next nmea string
	for (i = 0; i < strlen(NMEA_string_state_machine_1); ++i) {
		processNMEAbyte(NMEA_string_state_machine_2[i]);
	}

	// read gps data
	getCurrentGeogrPos(&myPos);
	if( (myPos.Latitude != 48506500) || (myPos.Longitude != 16466500) )	{ ErrorArr[GL_ERRORCOUNTER++] = __LINE__;}
}

// ***************************************************************************************
void testInit(void) {
	gpsInit();
}

// ***************************************************************************************
void testSendmContrToGPS(void) {
	uint8 crc = 0x2B;
	uint8 crc_1 = nibbleToAscii((crc>>4)&0x0F);	// first nibble from crc
	uint8 crc_2 = nibbleToAscii(crc&0x0F);
	if( crc_1 != '2' ){ErrorArr[GL_ERRORCOUNTER++] = __LINE__; }
	if( crc_2 != 'B' ){ErrorArr[GL_ERRORCOUNTER++] = __LINE__; }
}




