/*****************************************************************************************

@file:  QH_gps_app.c
@autor: Max Pejs
@date:  Datum: 17.04.2011

Copyright (C) 2011 University of Applied Sciences Esslingen

$Id:$
$Rev:$
<h2> the application layer of the gps driver, contains OS independent functions to init
the GPS receiver and process GPS NMEA 0183 data strings </h2>

CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be 
            called before!
------------------------------------------------------------------------------------------
 _
|
| Hochschule Esslingen
| University of Applied Sciences
|_

Subject:	Student research project
Faculty:	Information Technology
Speciality:	Technical Informatics

Project Quadrocopter
*****************************************************************************************/

/* Includes *****************************************************************************/
#include <stdio.h>
#include "QH_gps_app.h"
#include "QH_gps_util.h"
#include "QH_gps_os_interface.h"

/* Forward declarations *****************************************************************/
//void syncBaudRate(void);

/* Statics ******************************************************************************/
static uint8 calc_checksum = 0;				// calculated checksum
static uint8 recv_checksum = 0;				// received checksum
static uint8 wIndex = 0;				// write index for rxMsgBuffer
static uint8 rxMsgBuffer[RX_MESSAGE_BUFFER_SIZE];	// receive buffer
static uint8 txMsgBuffer[TX_MESSAGE_BUFFER_SIZE];	// send buffer

static bool RMC_struct_access_free = TRUE;		// semaphore for synchronisation
static states actState = NP_SOS;			// current state of the state machine

// an array with all possible baud rates
static uint16 aBaudrates[] = { 4800, 9600, 14400, 19200, 38400, 57600, 0 };	

static bool last_msg_processed = TRUE;	
static RMCmsg gpsRMCdata;						// contains gps data from NMEA RMC string

/* Functions ****************************************************************************/

/**---------------------------------------------------------------------------------------
*	For more informations see file QH_gps_app.h 	
*---------------------------------------------------------------------------------------*/
bool getRMCdata(RMCmsg * m)
{
	if(RMC_struct_access_free)
	{
		RMC_struct_access_free = FALSE;		// label, the struct is in use
		(void)memcpy( &(*m), &gpsRMCdata, sizeof(RMCmsg) );
		RMC_struct_access_free = TRUE;		// label, the struct access is free
		return TRUE;
	}
	return FALSE;
}

/**---------------------------------------------------------------------------------------
*	For more informations see file QH_gps_app.h 	
*---------------------------------------------------------------------------------------*/
int8 getCurrentGeogrPos(GeograficPosition * m)
{
	int8 ret = -1;
	if( RMC_struct_access_free )
	{
		RMC_struct_access_free = FALSE;
		if('A' == gpsRMCdata.DataValid) // RMC data are valid
		{
			ret = 1;
		}else
		{
			ret = 0;
		}
		m->Latitude = gpsRMCdata.Latitude;
		m->Longitude = gpsRMCdata.Longitude;
		RMC_struct_access_free = TRUE;
	}
	return ret;
}

/**---------------------------------------------------------------------------------------
*	For more informations see file QH_gps_app.h 	
*---------------------------------------------------------------------------------------*/
bool getCurrentTime(GPSTime * m)
{
	if(RMC_struct_access_free)
	{
		RMC_struct_access_free = FALSE;
		m->Hour = gpsRMCdata.Hour;
		m->Minute = gpsRMCdata.Minute;
		m->Second = gpsRMCdata.Second;
		RMC_struct_access_free = TRUE;
		return TRUE;
	}
	return FALSE;
}

/**---------------------------------------------------------------------------------------
*	For more informations see file QH_gps_app.h 	
*---------------------------------------------------------------------------------------*/
bool getCurrentDate(GPSDate * m)
{
	if(RMC_struct_access_free)
	{
		RMC_struct_access_free = FALSE;
		m->Day = gpsRMCdata.Day;
		m->Month = gpsRMCdata.Month;
		m->Year = gpsRMCdata.Year;
		RMC_struct_access_free = TRUE;
		return TRUE;
	}
	return FALSE;
}

/**---------------------------------------------------------------------------------------
* 	this finction calculates a CRC chekcsum of txMsgBuffer, converts the checksum to
* 	ASCII and terminates a this with a zero.
*---------------------------------------------------------------------------------------*/
void completeTxMsg(void)
{
	uint8 len;
	uint8 crc;

	crc = calcCRC8(txMsgBuffer+1);	    // calc crc without '$'
	len = (uint8)strlen((const char*)txMsgBuffer);
	txMsgBuffer[len++] = '*';		        // end of sequence
	txMsgBuffer[len++] = nibbleToAscii((crc>>4)&0x0F);	// first nibble from crc
	txMsgBuffer[len++] = nibbleToAscii(crc&0x0F);		// second nibble from crc
	txMsgBuffer[len++] = 13;	  	      // end of message
	txMsgBuffer[len++] = 10;
	txMsgBuffer[len] = 0;			          // terminate string
}

/**---------------------------------------------------------------------------------------
* function to send a gps baudrate via polling operation to gps receiver
*	param:
*		uint16 baudrate		the baud rate to be set
*---------------------------------------------------------------------------------------*/
void setGPSBaudRate(uint16 baudrate)
{
	(void)sprintf( (char*)txMsgBuffer, "$PMTK251,%i", baudrate);
	completeTxMsg();
	sendMsgPoll(txMsgBuffer);
}

/**---------------------------------------------------------------------------------------
* function to send a gps output frequency via polling operation to gps receiver. The
* frequency in stored in RMC_DATA_UPDATE_FREQ (see header file).
*---------------------------------------------------------------------------------------*/
void setGPSOutputFreq()
{
	uint8 rmcDataFreq = RMC_DATA_UPDATE_FIX;

	if( (rmcDataFreq < 1) || (rmcDataFreq > 5) )// only values between 1 and 5 are allowed
	{
		rmcDataFreq = 5;
	}
	(void)sprintf( (char*)txMsgBuffer, "$PMTK314,0,%i,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0",rmcDataFreq);
	completeTxMsg();
	sendMsgPoll(txMsgBuffer);
}

/**---------------------------------------------------------------------------------------
*	The Function locate the next data field of the NMEA data string											
*	parameters:																								
*		pData				pointer to the NMEA data string													
*		pField				string pointer to the field data
*		fieldSize			size of pField (destination buffer)												
*		nSearchPosition		pointer to integer. Start to search the next
*							field from this position
*	return value:																							
*		TRUE				the next data field was found successful										
*		FALSE				the next data field couldn't be found, data
*							field is empty or end of string is reached.	
*---------------------------------------------------------------------------------------*/
bool getNextField(uint8 *pData, uint8 *pField, uint8 fieldSize, uint8 * nSearchPosition)
{
     uint8 i = 0;
     uint8 l = 0;
     uint8 cDelimiter = ',';
	 pField[fieldSize-1] = 0;
	// check parameters
	if( NULL == pData || NULL == pField || 
	                            NULL == nSearchPosition || fieldSize < RMC_FIELD_MIN_LEN )
	{return FALSE;}
	i = *nSearchPosition;

	// check for end of message
	if( pData[i] == 0 )
	{return FALSE;}	// end of the nmea message
	// check if field is empty
	if( pData[i] == cDelimiter )
	{
		// data field is empty
		pField[0] = 0;
		*nSearchPosition = ++i; // set position on the next char
		return FALSE;	// failed, field is empty
	}
	// copy chars from pData to pField
	while( (cDelimiter != pData[i]) && (0 != pData[i])  && ('*' != pData[i]) )
	{
		pField[l++] = pData[i++];
		// check if field is too big to fit on passed parameter.
		if(l >= fieldSize)
		{	// in this case cut returned field to max length. Should never happen :)
			l = fieldSize-1;
		}
	}
	*nSearchPosition = ++i; // set position on the next char
	pField[l] = 0;	// terminate destination string
	return TRUE;	// success!
}

/**---------------------------------------------------------------------------------------
* This function processes an RMC message. The received NMEA data are stored in 
* rxMsgBuffer. The data	fields will read from the data string one by one and 
* processed. The fields are separated by the ","	
*---------------------------------------------------------------------------------------*/
void processRMCmessage(void)
{  
	uint8 Search_position = 0;
	uint8 pBuff[RMC_FIELD_MIN_LEN];
	uint8 temp[10];
	if( RMC_struct_access_free )
	{
		RMC_struct_access_free = FALSE;
		last_msg_processed = FALSE;
		
		// skip NMEA packet type (GPRMC) and comma
		Search_position = 6;
		// aternative solution for skipping packet type but arithmetically wasteful
		//if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position));
		
		// time
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{
			temp[0] = pBuff[0];
			temp[1] = pBuff[1];
			temp[2] = '\0';
			gpsRMCdata.Hour = myAtouint8(temp);
			
			temp[0] = pBuff[2];
			temp[1] = pBuff[3];
			gpsRMCdata.Minute = myAtouint8(temp);

			temp[0] = pBuff[4];
			temp[1] = pBuff[5];
			gpsRMCdata.Second = myAtouint8(temp);
		}

		// Data validation
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{gpsRMCdata.DataValid = pBuff[0];}
		else
		{gpsRMCdata.DataValid = 'V';}

		// GPS Position latitude
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{
			gpsRMCdata.Latitude = convMinToDeg(&pBuff[2]);
			pBuff[2] = 0;
			gpsRMCdata.Latitude += myAtouint8(pBuff)*PRECISION_GPS;
		}
		// GPS Position latitude indicator (North or South)
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{
			if( 'S' == pBuff[0] )
			{gpsRMCdata.Latitude = -gpsRMCdata.Latitude;}
		}
		
		// GPS Position longitude 
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{
			gpsRMCdata.Longitude = convMinToDeg(&pBuff[3]);
			pBuff[3] = 0;
			gpsRMCdata.Longitude  += myAtouint8(pBuff)*PRECISION_GPS;
		}
		
		// GPS Position longitude indicator (West or East)
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{
			if( 'W' == pBuff[0] )
			{gpsRMCdata.Longitude = -gpsRMCdata.Longitude;}
		}
		
		//Speed over ground
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{
			gpsRMCdata.Ground_speed_ms = (uint16)( (myAtofasint32(pBuff) * 
				SPEED_FACTOR_KNOTS_TO_MS) / 10000000); 
		}
		
		//Course over ground
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{
			gpsRMCdata.Ground_course = (uint16)(myAtofasint32(pBuff)/100);
		}     
		
		//Date
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{
			temp[0] = pBuff[0];
			temp[1] = pBuff[1];
			temp[2] = 0;
			gpsRMCdata.Day = myAtouint8(temp);
			
			temp[0] = pBuff[2];
			temp[1] = pBuff[3];
			gpsRMCdata.Month = myAtouint8(temp);

			temp[0] = pBuff[4];
			temp[1] = pBuff[5];
			gpsRMCdata.Year = myAtouint8(temp) + 2000;
		}
// this fields are don't needed
 /*
		//Magnetic variation in degrees
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{
			gpsRMCdata.MagVar = myAtofasint32(pBuff);
		}
		
		//Variation sense E=east or W=west (Not shown)
		if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &Search_position))
		{
			if( 'W' == pBuff[0] )
			{gpsRMCdata.MagVar = -gpsRMCdata.MagVar;}
		}
        */
		RMC_struct_access_free = TRUE;
		last_msg_processed = TRUE;	// gps data were updated
	}
	else
	{
		last_msg_processed = FALSE;	// couldn't update gps data
	}
}

/**---------------------------------------------------------------------------------------
*	Function to process a received message stored in rxMsgBuffer
*---------------------------------------------------------------------------------------*/
void process_message(void)
{
	uint8 pBuff[RMC_FIELD_MIN_LEN];
	uint8 pos = 0;

	// process RMC data
	if(getNextField(rxMsgBuffer, pBuff, RMC_FIELD_MIN_LEN, &pos))
	{
		if( 0 == strcmp((char *)pBuff, "GPRMC") )
		{
			processRMCmessage();
		}
		
		if( 0 == strcmp((char *)pBuff, "PMTK") )	// response message from GPS device
		{
			
		}
	}
}

//----------------------------------------------------------------------------------------
void processNMEAbyte(char recvByte)
{
	switch(actState)
	{
	//*** wait for "Start Of Sequence" ***
		case NP_SOS:
				if( !last_msg_processed )	// if las message wasn't processed
				{
					process_message();	// try once again
				}
				if('$' == recvByte)
				{
					calc_checksum = 0;			// reset checksum
					wIndex = 0;					// reset index
					actState = NP_GET_DATA;		// goto next state (receive NMEA data)
				}
				break;

	//*** Recieve data ( data fields between '$' and '*' )***
		case NP_GET_DATA:
				if( '*' != recvByte )
				{
					rxMsgBuffer[wIndex++] = recvByte;
				}
				else
				{
					rxMsgBuffer[wIndex] = 0;	// terminate string
					wIndex = 0;
					actState = NP_CHK_1;		// goto next state (receive first checksum byte)
				}
				break;

	//*** wait for first checksum byte ***
		case NP_CHK_1:
				recv_checksum = (asciiToNibble(recvByte))<<4;
				actState = NP_CHK_2;		// goto next state (receive second checksum byte)
				break;

	//*** wait for second checksum byte ***
		case NP_CHK_2:
				recv_checksum |= (asciiToNibble(recvByte));
				calc_checksum = calcCRC8(rxMsgBuffer);	// calculate checksum of received message

				if(recv_checksum == calc_checksum)	// check if checksum is correct
				{
					process_message();	// if checksum is correct, process message
				}
				actState = NP_SOS;
				break;
		default : actState = NP_SOS;
	}

	// In case of overflow
	if (wIndex >= RX_MESSAGE_BUFFER_SIZE)
	{
		wIndex = 0;
		actState = NP_SOS;
	}
}

//----------------------------------------------------------------------------------------
void syncBaudRate(void)
{
  uint8 cnt;
  // synchronize baud rate
  for( cnt = 0; 0 != aBaudrates[cnt];  cnt++)
  {
	  setControllerBaudRate(aBaudrates[cnt]);
  	setGPSBaudRate(DEFAULT_BAUD_RATE);
  	setGPSOutputFreq();
  }
  // now set the controller baudrate to default
  setControllerBaudRate(DEFAULT_BAUD_RATE);
  // and set the NMEA output
  setGPSOutputFreq();
}
