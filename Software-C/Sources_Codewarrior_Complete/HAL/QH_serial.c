/*
 * QH_Serial.c
 *
 *  Created on: 21.12.2010
 *      Author: Dionysios Satikidis, W. Zimmermann
 */

#include "QH_serial.h"
#include "derivative.h"
#include "QH_pll.h"

//***** Serial Interface (UART) ***********************************************
//Note: If you use interfaceNr=0 (SCI0), the debugger does not work anymore,
//      because the debugger uses this interface for its own communication,
//      when debugging the Dragon12 hardware board
void SciInit(uint8 interfaceNr, uint32 baudRate)
{ 
  uint32 busclk  = pllGetBusclk();
  uint16 divisor = (uint16)(busclk/(baudRate<<4)) & 0x1FFF;	// divisor=MCLK/(16*baudRate), assume MCLK=BUSCLK=24MHz

/* bit value meaning in SCIxCR1
    7   0    LOOPS, no looping, normal
    6   0    WOMS, normal high/low outputs
    5   0    RSRC, not appliable with LOOPS=0
    4   0    M, 1 start, 8 data, 1 stop
    3   0    WAKE, wake by idle (not applicable)
    2   0    ILT, short idle time (not applicable)
    1   0    PE, no parity
    0   0    PT, parity type (not applicable with PE=0) */
/* bit value meaning in SCIxCR2
    7   0    TIE, no transmit interrupts on TDRE
    6   0    TCIE, no transmit interrupts on TC
    5   0    RIE, no receive interrupts on RDRF
    4   0    ILIE, no interrupts on idle
    3   1    TE, enable transmitter
    2   1    RE, enable receiver
    1   0    RWU, no receiver wakeup
    0   0    SBK, no send break */
  switch (interfaceNr)
  {   case 1:   SCI1BD  = divisor;
                SCI1CR1 = 0x04;
                SCI1CR2 = 0x0C;
      case 0:
      default:
                SCI0BD  = divisor;
                SCI0CR1 = 0x04;
                SCI0CR2 = 0x0C;
  }
}

#ifndef SCI0CR2_SCTIE_MASK
#define SCI0CR2_SCTIE_MASK 128
#endif
#ifndef SCI1CR2_SCTIE_MASK
#define SCI1CR2_SCTIE_MASK 128
#endif

void SciEnableInterrupts(uint8 interfaceNr, bool receiveInterrupt, bool transmitInterrupt)
{   if (interfaceNr==1)
    {   if (receiveInterrupt)
            SCI1CR2 = SCI1CR2 |  SCI1CR2_RIE_MASK;
        else
            SCI1CR2 = SCI1CR2 & ~SCI1CR2_RIE_MASK;
        if (transmitInterrupt)
            SCI1CR2 = SCI1CR2 |  SCI1CR2_SCTIE_MASK;
        else
            SCI1CR2 = SCI1CR2 & ~SCI1CR2_SCTIE_MASK;;
    } else
    {   if (receiveInterrupt)
            SCI0CR2 = SCI0CR2 |  SCI0CR2_RIE_MASK;
        else
            SCI0CR2 = SCI0CR2 & ~SCI0CR2_RIE_MASK;
        if (transmitInterrupt)
            SCI0CR2 = SCI0CR2 |  SCI0CR2_SCTIE_MASK;
        else
            SCI0CR2 = SCI0CR2 & ~SCI0CR2_SCTIE_MASK;
    }
}

// Checks if new input is ready, TRUE if new input is ready
// Input: none
// Output: TRUE if a call to InChar will return right away with data
//         FALSE if a call to InChar will wait for input
bool SciInStatus(uint8 interfaceNr)
{    if (interfaceNr==1)
        return (SCI1SR1 & SCI1SR1_RDRF_MASK);
     else
        return (SCI0SR1 & SCI0SR1_RDRF_MASK);
}

// Checks if output data buffer is empty, TRUE if empty
// Input: none
// Output: TRUE if a call to OutChar will output and return right away
//         FALSE if a call to OutChar will wait for output to be ready
bool SciOutStatus(uint8 interfaceNr)
{    if (interfaceNr==1)
     {  return (SCI1SR1 & SCI1SR1_TDRE_MASK);
     } else
     {  return (SCI0SR1 & SCI0SR1_TDRE_MASK);
     }
}

// Wait for new serial port input, busy-waiting synchronization
uint8 SciGetc(uint8 interfaceNr)
{   while(!SciInStatus(interfaceNr));   //Busy wait, till data is available
    if (interfaceNr==1)
        return SCI1DRL;
    else
        return SCI0DRL;
}

// Wait for buffer to be empty, output 8-bit to serial port
// busy-waiting synchronization
// Input: 8-bit data to be transferred
// Output: none
void SciPutc(uint8 interfaceNr, uint8 data)
{   while(!SciOutStatus(interfaceNr));	//Busy wait, till send register is empty
    if (interfaceNr==1)
        SCI1DRL = data;
    else
        SCI0DRL = data;
}

// Output String (NULL termination), busy-waiting synchronization
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void SciPuts(uint8 interfaceNr, char *p)
{   while(*p)
    {   SciPutc(interfaceNr, *p);
        p++;
    }
}
/*
#pragma INLINE
void TERMIO_PutChar(char *c)            //Glue function to make stdio functions putc(), puts(), printf() work
{   SciPutc(STDOUT, (uint8) c);         //Serial interface must be initialized by SciInit() before
}

#pragma INLINE
char TERMIO_GetChar(void)               //Glue function to make stdio functions getc(), gets(), scanf() work
{   return SciGetc(STDIN);              //Serial interface must be initialized by SciInit() before
}


#ifndef USER_SCI_ISR
void (*UserSci0CallbackFcn)(void) = NULL;
void (*UserSci1CallbackFcn)(void) = NULL;

void SciRegisterCallback(uint8 interfaceNr, void userSciCallback(void))
{  if (interfaceNr==1)
        UserSci1CallbackFcn = userSciCallback;
   else
        UserSci0CallbackFcn = userSciCallback;
}

#ifndef _HCS12_SERIALMON                //Reserved for serial monitor operation
interrupt 20 void sci0ISR (void)
{   if (UserSci0CallbackFcn)
        UserSci0CallbackFcn();
}
#endif

interrupt 21 void sci1ISR (void)
{   if (UserSci1CallbackFcn)
        UserSci1CallbackFcn();
}
#endif //USER_SCI_ISR
*/