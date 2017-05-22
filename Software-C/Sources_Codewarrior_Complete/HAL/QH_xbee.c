/*************************************************************************************************************


@file:  QH_xbee.c
@autor: Marc Weber, Dionysios Satikidis
@date:  Datum: 19.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to communicate with the base station over the XBee modules using Serial Communication
    Interface 1 (SCI1)</h2>


CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be called before!
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

/* Defines ************************************************************************************************/
#define BAUD_RATE 115200

/* Variables ************************************************************************************************/


/* double buffering for incomming XBee messages (0 to 252 byte user data) */
static uint8 rxMsgBuffer1[256];
static uint8 rxMsgBuffer2[256];
static uint8* rxReadPtr = rxMsgBuffer1;
static uint8* rxWritePtr = rxMsgBuffer2;

static uint8 txMsgBuffer[256];      /* transmit buffer */
static uint8 txMsgByteNo = 0;       /* number of the next byte to send */

static uint8 rxMsgByteNo = 0;       /* number of the next incomming byte of a message */
static bool rxReadPtrInUse = FALSE; /* flag, indicating if the read pointer/buffer is currently used */
static bool rxMsgInQueue = FALSE;   /* flag, indicating if a new message is available in the write buffer */
static bool rxNewMsg = FALSE;       /* flag, indicating if a new message is available in the read buffer */


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
  /* CAUTION: must use 32 bit calculation (16 bit calculation -> overflow) */
  uint32 divisor = pllGetBusclk() / ((int32)BAUD_RATE << 4);
    
  DDRH_DDRH5 = 0; /* port H, pin 5 is input; used for clear to send (~CTS) signal; ~CTS is set to '1' */
                  /* by the XBee module, if the transmit buffer (DI Buffer) is nearly full (17 of 202 */
                  /* bytes left) */
  
  /* no infrared (bit 15 to 13); adjustment of the baud rate (bit 12 to 0); see divisor calculation above */
  SCI1BD  = ((uint16) divisor) & 0x1FFF;
  
  SCI1CR1 = 0x04; /* bit 7: LOOPS, no looping, normal */
                  /* bit 6: SCISWAI, SCI enabled in wait mode */
                  /* bit 5: RSRC, not appliable with LOOPS = 0 */
                  /* bit 4: M, one start bit, eight data bits, one stop bit */
                  /* bit 3: WAKE, wake by idle */
                  /* bit 2: ILT, short idle time */
                  /* bit 1: PE, no parity */
                  /* bit 0: PT, parity type (not applicable with PE = 0) */
                      
  SCI1CR2 = 0x2C; /* bit 7: TIE, no transmit interrupts on transmit data register empty (TDRE) */
                  /* bit 6: TCIE, no transmit interrupts on transmission complete (TC) */
                  /* bit 5: RIE, receive interrupts on receive data register full (RDRF) */
                  /* bit 4: ILIE, no interrupts on idle */
                  /* bit 3: TE, enable transmitter */
                  /* bit 2: RE, enable receiver */
                  /* bit 1: RWU, no receiver wakeup */
                  /* bit 0: SBK, no send break */
  
  TIOS_IOS2 = 1;  /* timer channel 2 works as output compare */
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
/*   return value:  0:  if the transmission to the XBee module was statred (this does not mean, that the    */
/*                      message was sent successfully)                                                      */
/*                  1:  if the receive buffer of the XBee module is full or the transmit buffer is not      */
/*                      empty                                                                               */
/*----------------------------------------------------------------------------------------------------------*/
uint8 xbeeSendMsg(XbeeMsg* msg)
{
  uint8 msgLen = 2 + msg->dataLen;                    /* message length (without CRC); max: 254 */
  
  if (SCI1SR1_TDRE && !SCI1CR2_TIE && !PTH_PTH5)
  {
    uint16 crc = xbeeCalcCrc16((uint8*)msg, msgLen);  /* calculate the CRC16 checksum of the message */
    (void) memcpy(txMsgBuffer, msg, msgLen);
    (void) memcpy(&txMsgBuffer[msgLen], &crc, 2);
    
    SCI1DRL = txMsgBuffer[0];                         /* send message byte */
    
    SCI1CR2_TIE = 1;
    return 0;
  }
  return 1;
}

/*----------------------------------------------------------------------------------------------------------*/
/* xbeeCheckForMsg() writes back a received message, if there is a new one available in the read buffer     */
/*   - msg:         a pointer to the struct to which the received message is written                        */
/*   return value:  0:  a received message was written to 'msg'                                             */
/*                  1:  there was no new message available in the buffer                                    */
/*----------------------------------------------------------------------------------------------------------*/
uint8 xbeeCheckForMsg(XbeeMsg* msg)
{
  if (rxNewMsg)                                             /* check, if a new message is available */
  {
    rxReadPtrInUse = TRUE;                                  /* lock read pointer while copying */
    (void) memcpy(msg, rxReadPtr, (*(rxReadPtr + 1)) + 2);  /* copy the received message */
    rxReadPtrInUse = FALSE;
    rxNewMsg = FALSE;                                       /* reset flag */
    return 0;
  }
  else
  {
    return 1;
  }
}

/*----------------------------------------------------------------------------------------------------------*/
/* xbeeCompleteRx() tries to exchange the read and write buffer pointers; if the read pointer is currently  */
/* used, a new timeout is defined after which this function is called again (see xbeeTimeoutIsr())          */
/*----------------------------------------------------------------------------------------------------------*/
void xbeeCompleteRx(void)
{
  if (rxReadPtrInUse)         /* check, if the read pointer is currently in use */
  {
    SCI1CR2_RIE = 0;          /* disable SCI receive interrupt while buffers are not exchanged */
    rxMsgInQueue = TRUE;
    TC2 = TCNT + 2000;        /* next try to get access to the read pointer in 2ms */
    TIE_C2I = 1;              /* enable interrupts for timer channel 2 */
  }
  else
  {
    /* exchange read and write pointers */
    uint8* temp = rxWritePtr;
    rxWritePtr = rxReadPtr;
    rxReadPtr = temp;
    
    rxNewMsg = TRUE;          /* set flag, new message in buffer available */
    rxMsgInQueue = FALSE;
    rxMsgByteNo = 0;          /* reset message byte counter */
    SCI1CR2_RIE = 1;          /* enable SCI receive interrupt; ready for new message */
  }
}


/* Interrupt Service Routines - ISRs ************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* xbeeTimeoutIsr() is the ISR for timer channel 2; it is called if a message timeout occurs (no further    */
/* byte was received within 3ms); additionally it is called by xbeeTxRxIsr(), when a message reception is   */
/* complete; it tries to exchange the read and write pointer/buffer, so that a new message can be received  */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch2 void xbeeTimeoutIsr(void)
{
  if (rxMsgInQueue)   /* check, if there is a new message available in the write buffer */  
  {
    xbeeCompleteRx();
  }
  else
  {
    TIE_C2I = 0;      /* disable interrupts for timer channel 2 */
    rxMsgByteNo = 0;  /* reset message byte counter */
  }
  TFLG1_C2F = 1;      /* clear interrupt flag */
}

/*----------------------------------------------------------------------------------------------------------*/
/* xbeeTxRxIsr() is the ISR for the receive data register full and the transmit data register empty         */
/* interrupt; it is called, when one byte was received or one byte was transmitted; at receiving bytes, a   */
/* message is built up internally; if a message reception is complete, the message is copied to the buffer  */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vsci1 void xbeeTxRxIsr(void)
{

  /* RX - receive data -------------------------------------------------------------------------------------*/
  
  static uint8 rxMsgLen = 255;                  /* length of the currently incoming message */
  
  if (SCI1SR1_RDRF && !rxMsgInQueue)            /* check, if the write buffer is empty and it is an */
                                                /* interrupt due to receive data register full */
  {
    TIE_C2I = 0;                                /* disable interrupts for timer channel 2 */
    
    rxWritePtr[rxMsgByteNo] = SCI1DRL;          /* store received byte; clear interrupt flag */
    
    
    if (rxMsgByteNo == rxMsgLen)                /* check, if it was the last byte of a message */
    {
      /* check, if the received CRC matches the calculated CRC */
      if (*((uint16*) &rxWritePtr[rxMsgLen - 1]) == xbeeCalcCrc16(rxWritePtr, rxMsgLen - 1))
      {
        xbeeCompleteRx();                       /* message complete; ready for new message */
      }
      else
      {
        rxMsgByteNo = 0;                        /* reset message byte counter */
      }
    }
    else
    {
      if (rxMsgByteNo == 1)                     /* check, if it was the data length byte */
      {
        rxMsgLen = rxWritePtr[rxMsgByteNo] + 3; /* calculate message length (with CRC) */
      }
      rxMsgByteNo++;                            /* increase message length counter */
      
      TC2 = TCNT + 3000;                        /* set message time out; next byte must be received within */
                                                /* the next 3ms, if not, the timer expires and the previous */
                                                /* received bytes are ignored */
      TIE_C2I = 1;                              /* enable interrupts for timer channel 2 */
    }
  }
  
  /* TX - transmit data ------------------------------------------------------------------------------------*/
  
  if (SCI1SR1_TDRE && SCI1CR2_TIE)              /* check, if the transmit register is empty and a message */
                                                /* is currently sent */
  {
    if ((txMsgByteNo == (txMsgBuffer[1] + 3)) || PTH_PTH5)
    {
      txMsgByteNo = 0;                          /* message completely sent or XBee receive buffer full */
      SCI1CR2_TIE = 0;
    }
    else
    {
      txMsgByteNo++;
      SCI1DRL = txMsgBuffer[txMsgByteNo];       /* send message byte */
    }
  }     
}