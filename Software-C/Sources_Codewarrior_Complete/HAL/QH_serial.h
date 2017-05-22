/*
 * QH_Serial.h
 *
 *  Created on: 21.12.2010
 *      Author: Dionysios Satikidis, W. Zimmermann
 */

#ifndef QH_SERRIAL_H_
#define QH_SERRIAL_H_


/* Includes ****************************************************************************************/
#include "typedef.h"


//#############################################################################
//! \defgroup SCI ***** Serial Interface (SCI, UART) ***********************************************
//! @{

//Note: If you use interfaceNr=0 (SCI0), the debugger does not work anymore,
//      because the debugger uses this interface for its own communication,
//      when debugging the Dragon12 hardware board

//! Initialize serial interface. Must be called before using any of the other Sci...() functions.
/*! @param interfaceNr  0 for first, 1 for second serial interface (UART)
    @param baudRate     baud rate, e.g. 2400, 4800, 9600, 19200, 38400, 57600, 115200 (min. 184bit/s, max. 1,5Mbit/s)

    Uses 8N1 (8bit characters  , no parity, 1 stop bit).
*/
void SciInit(uint8 interfaceNr, uint32 baudRate);

//! Read a byte from the serial interface (blocking, i.e. waits until the receive buffer is full)
/*! @param interfaceNr  0 for first, 1 for second serial interface (UART)
    @return last byte received
*/
uint8 SciGetc(uint8 interfaceNr);

//! Send a character to the serial interface (blocking, i.e. waits, until the transmit buffer is empty)
/*! @param interfaceNr  0 for first, 1 for second serial interface (UART)
    @param data		character (byte) to send
*/
void SciPutc(uint8 interfaceNr, uint8 data);

//! Check, if a character has been received, i.e. if the receive buffer is full. Call first, if you do not want SciGetc() or SciGets() to block.
/*! @param interfaceNr  0 for first, 1 for second serial interface (UART)
    @return TRUE, if the receive buffer is full
*/
bool SciInStatus(uint8 interfaceNr);

//! Check, if a character can be send, i.e. if the transmit buffer is empty. Call first, if you do not want SciPutc() or SciPuts() to block.
/*! @param interfaceNr  0 for first, 1 for second serial interface (UART)
    @return TRUE, if the transmit buffer is empty
*/
bool SciOutStatus(uint8 interfaceNr);

//! Send a character string (calls SciPutc() repeatedly, until the string has been sent).
/*! @param interfaceNr  0 for first, 1 for second serial interface (UART)
    @param p            pointer to ASCIIZ string
*/
void SciPuts(uint8 interfaceNr, char *p);

#ifndef USER_SCI_ISR
//! Register a callback function, which will be called on character reception or transmission.
/*! @param interfaceNr  	0 for first, 1 for second serial interface (UART)
    @param userSciCallback 	name of the callback function

    First register the callback function, then enable interrupts via SciEnableInterrupts().

    In case, the callback function is used for both receive and transmit events, use SciInStatus() and
    SciOutStatus() to find out, if the interrupt was called by reception or transmission.

    Note: The HAL does implement Interrupt Service Routines (ISR) for the SCI interrupts 20 and 21. So
    the user may use a normal function instead of an ISR. If the user wants to provide his own ISR, he/she
    should insert \#define USER_SCI_ISR before line \#include "HAL.h"
*/
     void SciRegisterCallback(uint8 interfaceNr, void userSciCallback(void));
#endif

//! Enable serial interface receive or transmit interrupts/callback functions
/*! @param interfaceNr  	0 for first, 1 for second serial interface (UART)
    @param receiveInterrupt 	TRUE to trigger an interrupt/callback, when a character has been received
    @param transmitInterrupt	TRUE to trigger an interrupt/callback, when a character has been sent
*/
void SciEnableInterrupts(uint8 interfaceNr, bool receiveInterrupt, bool transmitInterrupt);

#ifdef _HCS12_SERIALMON
//! Standard output - With serial monitor SCI1 is used
   #define STDOUT       1
//! Standard input  - With serial monitor SCI1 is used
   #define STDIN	1
#else
//! Standard output - With simulation, SCI0 is used
   #define STDOUT       0
//! Standard input  - With simulation, SCI0 is used
   #define STDIN	0
#endif

//! @}
#endif /* QH_SERRIAL_H_ */
