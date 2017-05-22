/*************************************************************************************************************


@file:  QH_xbee.h
@autor: Marc Weber
@date:  Datum: 16.05.2010

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


#ifndef QH_XBEE_H
  #define QH_XBEE_H


/* Includes *************************************************************************************************/


  #include "typedef.h"
  
  
/* Defines **************************************************************************************************/


  #define CRC16_POLYNOM   0xA001
  
  
/* Typedefs *************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* XbeeMsg corresponds to a message, used for communication with the base station; for details, please see  */
/* 'XBee_Communication.docx'                                                                                */
/*----------------------------------------------------------------------------------------------------------*/
  typedef struct
  {
    uint8 id;         /* message ID */
    uint8 dataLen;    /* data length */
    uint8 data[252];  /* data field */
    
  } XbeeMsg;


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* xbeeInit() configures the Serial Communication Interface 1 (SCI1) to work with the XBee module;          */
/* additionally timer channel 2 is configured to work as output compare; this function must be called       */
/* before any other xbee...() function                                                                      */
/*----------------------------------------------------------------------------------------------------------*/
  void xbeeInit(void);

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
  uint8 xbeeSendMsg(XbeeMsg* msg);

/*----------------------------------------------------------------------------------------------------------*/
/* xbeeCheckForMsg() writes back a received message, if there is a new one available in the buffer          */
/*   - msg:         a pointer to the struct to which the received message is written                        */
/*   return value:  0:  a received message was written to 'msg'                                             */
/*                  1:  there was no new message available in the buffer                                    */
/*----------------------------------------------------------------------------------------------------------*/
  uint8 xbeeCheckForMsg(XbeeMsg* msg);


/************************************************************************************************************/


#endif