/*****************************************************************************************

@file:  QH_gps.c
@autor: Max Pejs
@date:  Datum: 17.04.2011

Copyright (C) 2011 University of Applied Sciences Esslingen

$Id:$
$Rev:$
<h2>Functions to init the GPS receiver, receive and process GPS NMEA 0183 data strings</h2>

CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be 
            called before!
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
#include "QH_gps_app.h"
#include "QH_gps_os_interface.h"

#include "QH_pll.h"
#include "derivative.h"

/* Forward declarations *****************************************************************/

#define SCI_NUM 1		// serial port number

#define SETPORT2(a,b,c) a##b##c
#define SETPORT(a,b,c) SETPORT2(a,b,c)

#define SCIxBD	SETPORT(SCI,SCI_NUM,BD)
#define SCIxSR1_RDRF SETPORT(SCI,SCI_NUM,SR1_RDRF)
#define SCIxSR1_TDRE SETPORT(SCI,SCI_NUM,SR1_TDRE)
#define SCIxCR1 SETPORT(SCI,SCI_NUM,CR1)
#define SCIxCR2 SETPORT(SCI,SCI_NUM,CR2)
#define SCIxDRL SETPORT(SCI,SCI_NUM,DRL)
#define VectorNumber_Vscix SETPORT(VectorNumber_V, sci, SCI_NUM)


/* Functions ****************************************************************************/
//----------------------------------------------------------------------------------------
void gpsInit(void)
{
  SCIxCR1 = 0x04; /* bit 7: LOOPS, no looping, normal */
                  /* bit 6: SCISWAI, SCI enabled in wait mode */
                  /* bit 5: RSRC, not appliable with LOOPS = 0 */
                  /* bit 4: M, one start bit, eight data bits, one stop bit */
                  /* bit 3: WAKE, wake by idle */
                  /* bit 2: ILT, short idle time */
                  /* bit 1: PE, no parity */
                  /* bit 0: PT, parity type (not applicable with PE = 0) */
                      
  SCIxCR2 = 0x2C; /* bit 7: TIE, no transmit interrupts on transmit data register empty (TDRE) */
                  /* bit 6: TCIE, no transmit interrupts on transmission complete (TC) */
                  /* bit 5: RIE, receive interrupts on receive data register full (RDRF) */
                  /* bit 4: ILIE, no interrupts on idle */
                  /* bit 3: TE, enable transmitter */
                  /* bit 2: RE, enable receiver */
                  /* bit 1: RWU, no receiver wakeup */
                  /* bit 0: SBK, no send break */
  syncBaudRate();
}

//----------------------------------------------------------------------------------------
void sendMsgPoll(uint8 * message)
{
	uint8 buffPos = 0;
	uint8 len;
	
	len = (uint8)strlen((const int8*)message);

	while( len > 0 )
	{
		if (SCIxSR1_TDRE)
		{
			SCIxDRL = message[buffPos];       // send message byte
			len--;
			buffPos++;
		 }
	 }
}

//----------------------------------------------------------------------------------------
void setControllerBaudRate(uint16 baudrate)
{
    /* calculate divisor with which a baud rate of 9600 baud (default value) is achieved*/
    /* divisor = BUSCLK / (16 * baud rate) */
    /* CAUTION: must use 32 bit calculation (16 bit calculation -> overflow) */
	uint32 divisor = pllGetBusclk() / ((int32)baudrate << 4);
	SCI1BD  = ((uint16) divisor) & 0x1FFF;
}

/**---------------------------------------------------------------------------------------
* gpsTxRxIsr() is the ISR for the receive data register full and transmit data register 
* empty interrupt. The ISR for transmit data is not	implemented. The receive ISR is 
* called, when one byte was received.
*---------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vscix void gpsTxRxIsr(void)
{
  // RX - receive data -------------------------------------------------------------------------------------*/
  if (SCIxSR1_RDRF)				// check, if the write buffer is empty and it is an
                                         // interrupt due to receive data register full
  { 
    processNMEAbyte(SCIxDRL);     // process received byte; clear interrupt flag 
  }
  // TX - transmit data ------------------------------------------------------------------------------------
  // currently not in use
}