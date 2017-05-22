/*************************************************************************************************************


@file:  QH_xbee.c
@autor: Marc Weber
@date:  Datum: 16.05.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to communicate with the base station over the XBee modules</h2>


CAUTION: - Serial Communication Interface 1 (SCI1) is used. Don't use SCI1 outside of this file!
         - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be called before!
         - Timer channel 2 (IOC2) is internally used to observe the message timeout. A timer frequency of
           1 MHz is assumed. Therefore timerInit() must be called before! Don't use timer channel 2 outside
           of this file!


--------------------------------------------------------------------------------------------------------------

 _
|
| Hochschule Esslingen
| University of Applied Sciencs
|_

Graduate School
Automotive Systems Master - Software Based Automotive Systems

Project Quadrocopter

Joachim Schwab, Sreekanth Sundaresh, Nina Vetlugina, Marc Weber 
Summer Term 2010


*************************************************************************************************************/


/* Includes *************************************************************************************************/


#include "derivative.h"
#include "QH_pll.h"
#include "QH_xbee.h"
#include <string.h>
#include "typedef.h"


/* Variables ************************************************************************************************/


static uint8 rxMsg[256];          /* currently incoming message */
static uint8 rxMsgLen = 0;        /* length of the currently incoming message */

static uint8 rxMsgBuffer[256];    /* received message */
static uint8 rxMsgBufferLen = 0;  /* length of the received message */
static bool rxNewMsg = FALSE;     /* flag, indicating if a new message is available in the buffer */


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* xbeeInit() configures the Serial Communication Interface 1 (SCI1) to work with the XBee module;          */
/* additionally timer channel 2 is configured to work as output compare; this function must be called       */
/* before any other xbee...() function                                                                      */
/*----------------------------------------------------------------------------------------------------------*/
void xbeeInit(void)
{
  /* calculate divisor with which a baud rate of 9600 baud (standard value) is achieved */
  /* divisor = BUSCLK / (16 * baud rate) */
  /* CAUTION: must use 9600L (32 bit calculation) instead of 9600 (16 bit calculation -> overflow) only */
  uint32 divisor = pllGetBusclk() / (9600L << 4);
    
  DDRH_DDRH5 = 0;     /* port H, pin 5 is input; used for clear to send (~CTS) signal; ~CTS is set to '1' */
                      /* by the XBee module, if the transmit buffer (DI Buffer) is nearly full (17 of 202 */
                      /* bytes left) */
  
  /* no infrared (bit 15 to 13); adjustment of the baud rate (bit 12 to 0); see divisor calculation above */
  SCI1BD  = ((uint16) divisor) & 0x1FFF;
  
  SCI1CR1 = 0x04;     /* bit  value  meaning */
                      /* 7    0      LOOPS, no looping, normal */
                      /* 6    0      SCISWAI, SCI enabled in wait mode */
                      /* 5    0      RSRC, not appliable with LOOPS = 0 */
                      /* 4    0      M, one start bit, eight data bits, one stop bit */
                      /* 3    0      WAKE, wake by idle */
                      /* 2    1      ILT, short idle time */
                      /* 1    0      PE, no parity */
                      /* 0    0      PT, parity type (not applicable with PE = 0) */
                      
  SCI1CR2 = 0x2C;     /* bit  value  meaning */
                      /* 7    0      TIE, no transmit interrupts on transmit data register empty (TDRE) */
                      /* 6    0      TCIE, no transmit interrupts on transmission complete (TC) */
                      /* 5    1      RIE, receive interrupts on receive data register full (RDRF) */
                      /* 4    0      ILIE, no interrupts on idle */
                      /* 3    1      TE, enable transmitter */
                      /* 2    1      RE, enable receiver */
                      /* 1    0      RWU, no receiver wakeup */
                      /* 0    0      SBK, no send break */
  
  TIOS_IOS2 = 1;      /* timer channel 2 works as output compare */
}

/*----------------------------------------------------------------------------------------------------------*/
/* xbeeCalcCrc16() returns the CRC16 checksum of the given data block                                       */
/*   - data:        a pointer to the beginning of the data block                                            */
/*   - n:           the number of bytes, used for CRC calculation                                           */
/*   return value:  the CRC16 checksum of the data block                                                    */
/*----------------------------------------------------------------------------------------------------------*/
uint16 xbeeCalcCrc16(uint8* data, uint8 n)
{
  uint16 crc = 0;
  uint8 buffer = 0; 
  uint8 i = 0;
  uint8 j = 0;
  
  for (i = 0; i < n; i++)                 /* loop for each data byte */
  {
    buffer = data[i];
    for (j = 0; j < 8; j++)               /* loop for each bit in one data byte */
    {
      if (((crc ^ buffer) & 1) != 0)
      {
        crc = (crc >> 1) ^ CRC16_POLYNOM;
      }
      else
      {
        crc = crc >> 1;
      }
      buffer = buffer >> 1;
    }
  }
  return crc;
}

/*----------------------------------------------------------------------------------------------------------*/
/* xbeeSendMsg() sends out a message (sequence of bytes) to the XBee module via SCI; a message consists of  */
/* an one byte ID, one byte data length, zero to 252 data bytes and two bytes CRC; for details, please see  */
/* 'Xbee_Communication.docx'                                                                                */
/*   - msg:         a pointer to the message, sent to the XBee module                                       */
/*   return value:  0:  if the transmission to the XBee module was successful                               */
/*                  1:  if the receive buffer of the XBee module is full                                    */
/*----------------------------------------------------------------------------------------------------------*/
uint8 xbeeSendMsg(XbeeMsg* msg)
{
  uint8* buffer = (uint8*) msg;               /* cast to a pointer, which points to one byte of data */
  uint8 msgLen = 2 + msg->dataLen;            /* message length (without CRC); max: 254 */
  uint8 i = 0;
  
  uint16 crc = xbeeCalcCrc16(buffer, msgLen); /* calculate the CRC16 checksum of the message */
  
  for (i = 0; i < (msgLen + 2); i++)          /* loop for each byte in the message (incl. CRC) */
  {
    if (PTH_PTH5 == 1)                        /* check if XBee module is clear to receive data */
    {
      return 1;                               /* XBee receive buffer full, abort transmission */
    }
    
    while(!SCI1SR1_TDRE);                     /* wait unil send register is empty */
    
    if (i < msgLen)                           /* check, if a message byte (not CRC) is to be sent */
    {
      SCI1DRL = buffer[i];                    /* send message byte */
    }
    else
    {
      SCI1DRL = ((uint8*) &crc)[i - msgLen];  /* send CRC */
    }
  }
  
  return 0;                                   /* transmission successful */
}

/*----------------------------------------------------------------------------------------------------------*/
/* xbeeCheckForMsg() writes back a received message, if there is a new one available in the buffer          */
/*   - msg:         a pointer to the struct to which the received message is written                        */
/*   return value:  0:  a received message was written to 'msg'                                             */
/*                  1:  there was no new message available in the buffer                                    */
/*----------------------------------------------------------------------------------------------------------*/
uint8 xbeeCheckForMsg(XbeeMsg* msg)
{
  if (rxNewMsg)                                       /* check, if a new message is available in the buffer */
  {
    (void) memcpy(msg, rxMsgBuffer, rxMsgBufferLen);  /* copy the received message to the specified memory */
    rxNewMsg = FALSE;                                 /* reset flag */
    return 0;
  }
  else
  {
    return 1;
  }
}


/* Interrupt Service Routines - ISR *************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* xbeeTimeoutIsr() is the ISR for timer channel 2; it is called if a message timeout occurs (no further    */
/* byte was received within 2ms); additionally it is called by xbeeRxIsr(), when a message reception is     */
/* complete; it resets the message length counter, so that a new message can be received                    */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch2 void xbeeTimeoutIsr(void)
{
  rxMsgLen = 0;     /* reset message length counter */
  TIE_C2I = 0;      /* disable interrupts for timer channel 2 */
  TFLG1_C2F = 1;    /* clear interrupt flag */
}

/*----------------------------------------------------------------------------------------------------------*/
/* xbeeRxIsr() is the ISR for the receive data register full interrupt; it is called, when the RDRF         */
/* interrupt is raised, that means when one byte was received; a message is built up internally; if a       */
/* message reception is complete, the message is copied to the buffer (rxMsgBuffer)                         */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vsci1 void xbeeRxIsr(void)
{
  if (SCI1SR1_RDRF == 1)                                    /* check, if it was an interrupt due to receive */
                                                            /* data register full */
  {
    rxMsg[rxMsgLen] = SCI1DRL;                              /* store received byte; clear interrupt flag */
    TC2 = TCNT + 2;                                         /* set message time out; next byte must be */
                                                            /* received within the next 2ms, if not, the */
                                                            /* timer expires and the previous received */
                                                            /* bytes are ignored */
    
    if (rxMsgLen == 0)                                      /* check, if it was the first byte (ID) */
    {
      TIE_C2I = 1;                                          /* enable interrupts for timer channel 2; start */
                                                            /* timeout observation  */
    }
    else if (rxMsgLen == 1)                                 /* check, if it was the data length byte */
    {
      rxMsgBufferLen = rxMsg[rxMsgLen] + 2;                 /* calculate message length (without CRC) */
    }
    else if (rxMsgLen == rxMsgBufferLen + 1)                /* check, if it was the last byte of a message */
                                                            /* (second CRC byte) */
    {
      /* check, if the received CRC matches the calculated CRC */
      if (*((uint16*) &rxMsg[rxMsgBufferLen]) == xbeeCalcCrc16(rxMsg, rxMsgBufferLen))
      {
        (void) memcpy(rxMsgBuffer, rxMsg, rxMsgBufferLen);  /* copy message (without CRC) into the buffer */
        rxNewMsg = TRUE;                                    /* set flag, new message in buffer available */
      }
      
      xbeeTimeoutIsr();                                     /* message complete; ready for new message */
    }
    
    rxMsgLen++;                                             /* increase message length counter */
  }
}