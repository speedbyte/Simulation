/*************************************************************************************************************


@file:  QH_timer.c
@autor: Dionysios Satikidis, Marc Weber, inspired by Prof. Dr.-Ing. Werner Zimmermann
@date:  Datum: 19.04.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to control the Enhanced Capture Timer (ECT) and the Real Time Interrupt (RTI)</h2>


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
#include "QH_timer.h"
#include "typedef.h"


/* Variables ************************************************************************************************/


static uint8 ectChannelFlags[NR_OF_CHANNELS] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
static uint8 ectOutputToggleFlags[NR_OF_CHANNELS] = {0x01, 0x04, 0x10, 0x40, 0x01, 0x04, 0x10, 0x40};
static void (*ectClbkFunctions[NR_OF_CHANNELS])(void);

static void (*rtiClbkFunction)(void) = NULL;


/* Functions (Enhanced Capture Timer - ECT) *****************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* ectInit() configures the ECT to use the precision timer; an ECT clock of 1MHz is selected and the main   */
/* timer is started; additionally the timer channels are configured to work as input capture or output      */
/* compare; this function must be called before any other ect...() function                                 */
/*   - outputCompare: a mask defining which channel is an output compare; a 1 configures the corresponding  */
/*                    channel as output compare; bit 0 stands for timer channel 0 (IOC0) etc.               */
/*----------------------------------------------------------------------------------------------------------*/
void ectInit(uint8 outputCompare)
{
  TIOS = TIOS | outputCompare;  /* configure the single timer channels to work as input capture (0) or */
                                /* output compare (1); after reset all channels work as input capture */
  PTPSR = 0x17;                 /* set precision prescaler to 24 to get 1MHz ect clock frequency */
  TSCR1 = 0x88;                 /* main timer enable (start); use precision timer */
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectSetCallback() links a callback function to a timer interrupt; if the timer elapses and the interrupt  */
/* is enabled (use ectInterruptInit(), ectInterruptEnable() and ectInterruptClearFlag()) the given function */
/* will be executed; it is only possible to link one callback function to an interrupt (second use of       */
/* ectSetCallback() will overwrite the first assignment)                                                    */
/*   - channel:       the timer channel to which the callback function is attached; please use the          */
/*                    appropriate defines                                                                   */
/*   - clbkFunction:  a function pointer to the callback function which is attached to the timer interrupt; */
/*                    it must have a signature like void functionName(void)                                 */
/*   return value:    FALSE (0):  if the parameter "channel" is in the range between zero and seven         */
/*                    TRUE (1):   if the parameter "channel" is greater than seven (no such channel         */
/*                                available)                                                                */
/*----------------------------------------------------------------------------------------------------------*/
bool ectSetCallback(uint8 channel, void clbkFunction(void))
{   
   if (clbkFunction && (channel < NR_OF_CHANNELS))
   {
     ectClbkFunctions[channel] = clbkFunction;
     return FALSE;  
   }
   return TRUE;  
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectToggleMode() configures the output of a timer channel to work in toggle mode (switching port value    */
/* with each interrupt) or to be disconnected from the timer                                                */
/*   - channel:     the timer channel which is switched to toggle mode; please use the appropriate defines  */
/*   - enable:      TRUE (!= 0):  enables output toggle                                                     */
/*                  FALSE (0):    disconnect timer from output pin logic                                    */
/*   return value:  FALSE (0):    if the parameter "channel" is in the range between zero and seven         */
/*                  TRUE (1):     if the parameter "channel" is greater than seven (no such channel         */
/*                                available)                                                                */
/*----------------------------------------------------------------------------------------------------------*/
bool ectToggleMode(uint8 channel, bool enable)
{
  if (channel <= IOC3)
  {
    if (enable)
    {
      TCTL2 = TCTL2 | ectOutputToggleFlags[channel];        /* enable output toggle */
    }
    else
    {
      TCTL2 = TCTL2 & ~ectOutputToggleFlags[channel];       /* disconnect timer from output pin logic */
    }
    TCTL2 = TCTL2 & ~(ectOutputToggleFlags[channel] << 1);  /* ensure desired output action */
  }
  else if (channel <= IOC7)
  {
    if (enable)
    {
      TCTL1 = TCTL1 | ectOutputToggleFlags[channel];        /* enable output toggle */
    }
    else
    {
      TCTL1 = TCTL1 & ~ectOutputToggleFlags[channel];       /* disconnect timer from output pin logic */
    }
    TCTL1 = TCTL1 & ~(ectOutputToggleFlags[channel] << 1);  /* ensure desired output action */
  }
  else
  {
    return TRUE;
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectSetTimerCompare() increases the value of the timer compare register of the corresponding channel; if  */
/* the timer channel is in output compare mode, an interrupt will be raised when the timer count matches    */
/* the value in this register                                                                               */
/*   - channel:     the timer channel of which the timer compare register value is increased                */
/*   - deltaTicks:  the number of ticks which are added to the corresponding timer compare register; the    */
/*                  number of ticks is equal to microseconds because of 1MHz ECT clock                      */
/*   return value:  FALSE (0):  if the parameter "channel" is in the range between zero and seven           */
/*                  TRUE (1):   if the parameter "channel" is greater than seven (no such channel           */
/*                                available)                                                                */
/*----------------------------------------------------------------------------------------------------------*/
bool ectSetTimerCompare(uint8 channel, uint16 deltaTicks)
{
  switch (channel)
  {
    case IOC0:
      TC0 = TC0 + deltaTicks;
      break;
    case IOC1:
      TC1 = TC1 + deltaTicks;
      break;
    case IOC2:
      TC2 = TC2 + deltaTicks;
      break;
    case IOC3:
      TC3 = TC3 + deltaTicks;
      break;
    case IOC4:
      TC4 = TC4 + deltaTicks;
      break;
    case IOC5:
      TC5 = TC5 + deltaTicks;
      break;
    case IOC6:
      TC6 = TC6 + deltaTicks;
      break;
    case IOC7:
      TC7 = TC7 + deltaTicks;
      break;
    default:
      return TRUE;
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectInterruptEnable() enables or disables the output compare interrupt of a timer channel                 */
/*   - channel:     the timer channel of which the interrupt is enabled; please use the appropriate defines */
/*   - enable:      TRUE (!= 0):  enables the interrupt                                                     */
/*                  FALSE (0):    disables the interrupt                                                    */
/*   return value:  FALSE (0):  if the parameter "channel" is in the range between zero and seven           */
/*                  TRUE (1):   if the parameter "channel" is greater than seven (no such channel available)*/
/*----------------------------------------------------------------------------------------------------------*/
bool ectInterruptEnable(uint8 channel, bool enable)
{
  if (channel < NR_OF_CHANNELS)
  {
    if (enable)
    {
      TIE = TIE | ectChannelFlags[channel];   /* enable timer interrupt for corresponding timer channel */
    }
    else
    {
      TIE = TIE & ~ectChannelFlags[channel];  /* disable timer interrupt for corresponding timer channel */
    }
    return FALSE;
  }
  return TRUE;
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectInterruptClearFlag() clears the interrupt flag of a timer channel, so that a new interrupt can be     */
/* generated                                                                                                */
/*   - channel:     the timer channel of which the interrupt flag is cleared; please use the appropriate    */
/*                  defines                                                                                 */
/*   return value:  FALSE (0):  if the parameter "channel" is in the range between zero and seven           */
/*                  TRUE (1):   if the parameter "channel" is greater than seven (no such channel available)*/
/*----------------------------------------------------------------------------------------------------------*/
bool ectInterruptClearFlag(uint8 channel)
{
  if (channel < NR_OF_CHANNELS)
  {
	  TFLG1 = TFLG1 | ectChannelFlags[channel]; /* reset interrupt flag for corresponding timer channel */
	  return FALSE;
  }
  return TRUE;
}


/* Interrupt Service Routines - ISR (Enhanced Capture Timer - ECT) ******************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* ectIsr0() is the ISR for timer channel 0; if the timer channel is in output compare mode, it will be     */
/* called, when the timer counter matches the value defined in the register TC0; the associated callback    */
/* function (set by ectSetCallback()) is called internally                                                  */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch0 void ectIsr0(void)
{
  if (ectClbkFunctions[IOC0])         /* check if there is an associated callback function; if yes, call it */
  {
    ectClbkFunctions[IOC0]();
  }
  (void) ectInterruptClearFlag(IOC0); /* clear interrupt flag */
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectIsr1() is the ISR for timer channel 1; if the timer channel is in output compare mode, it will be     */
/* called, when the timer counter matches the value defined in the register TC0; the associated callback    */
/* function (set by ectSetCallback()) is called internally                                                  */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch1 void ectIsr1(void)
{
  if (ectClbkFunctions[IOC1])         /* check if there is an associated callback function; if yes, call it */
  {
    ectClbkFunctions[IOC1]();
  }
  (void) ectInterruptClearFlag(IOC1); /* clear interrupt flag */
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectIsr2() is the ISR for timer channel 2; if the timer channel is in output compare mode, it will be     */
/* called, when the timer counter matches the value defined in the register TC0; the associated callback    */
/* function (set by ectSetCallback()) is called internally                                                  */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch2 void ectIsr2(void)
{
  if (ectClbkFunctions[IOC2])         /* check if there is an associated callback function; if yes, call it */
  {
    ectClbkFunctions[IOC2]();
  }
  (void) ectInterruptClearFlag(IOC2); /* clear interrupt flag */
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectIsr3() is the ISR for timer channel 3; if the timer channel is in output compare mode, it will be     */
/* called, when the timer counter matches the value defined in the register TC0; the associated callback    */
/* function (set by ectSetCallback()) is called internally                                                  */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch3 void ectIsr3(void)
{
  if (ectClbkFunctions[IOC3])         /* check if there is an associated callback function; if yes, call it */
  {
    ectClbkFunctions[IOC3]();
  }
  (void) ectInterruptClearFlag(IOC3); /* clear interrupt flag */
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectIsr4() is the ISR for timer channel 4; if the timer channel is in output compare mode, it will be     */
/* called, when the timer counter matches the value defined in the register TC0; the associated callback    */
/* function (set by ectSetCallback()) is called internally                                                  */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch4 void ectIsr4(void)
{
  if (ectClbkFunctions[IOC4])         /* check if there is an associated callback function; if yes, call it */
  {
    ectClbkFunctions[IOC4]();
  }
  (void) ectInterruptClearFlag(IOC4); /* clear interrupt flag */
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectIsr5() is the ISR for timer channel 5; if the timer channel is in output compare mode, it will be     */
/* called, when the timer counter matches the value defined in the register TC0; the associated callback    */
/* function (set by ectSetCallback()) is called internally                                                  */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch5 void ectIsr5(void)
{
  if (ectClbkFunctions[IOC5])         /* check if there is an associated callback function; if yes, call it */
  {
    ectClbkFunctions[IOC5]();
  }
  (void) ectInterruptClearFlag(IOC5); /* clear interrupt flag */
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectIsr6() is the ISR for timer channel 6; if the timer channel is in output compare mode, it will be     */
/* called, when the timer counter matches the value defined in the register TC0; the associated callback    */
/* function (set by ectSetCallback()) is called internally                                                  */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch6 void ectIsr6(void)
{
  if (ectClbkFunctions[IOC6])         /* check if there is an associated callback function; if yes, call it */
  {
    ectClbkFunctions[IOC6]();
  }
  (void) ectInterruptClearFlag(IOC6); /* clear interrupt flag */
}

/*----------------------------------------------------------------------------------------------------------*/
/* ectIsr7() is the ISR for timer channel 7; if the timer channel is in output compare mode, it will be     */
/* called, when the timer counter matches the value defined in the register TC0; the associated callback    */
/* function (set by ectSetCallback()) is called internally                                                  */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtimch7 void ectIsr7(void)
{
  if (ectClbkFunctions[IOC7])         /* check if there is an associated callback function; if yes, call it */
  {
    ectClbkFunctions[IOC7]();
  }
  (void) ectInterruptClearFlag(IOC7); /* clear interrupt flag */
}


/* Functions (Real Time Interrupt - RTI) ********************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* rtiSetCallback() links a callback function to the RTI; if the RTI is raised, the given function will be  */
/* executed                                                                                                 */
/*   - clbkFunction:  a function pointer to the callback function which is attached to the RTI interrupt;   */
/*                    it must have a signature like void functionName(void)                                 */
/*----------------------------------------------------------------------------------------------------------*/
void rtiSetCallback(void clbkFunction(void))
{
   rtiClbkFunction = clbkFunction;
}

/*----------------------------------------------------------------------------------------------------------*/
/* rtiInit() configures the RTI; the interrupt period is ((x + 1) * 2^(y + 9)) / OSCCLK; this function must */
/* be called before any other rti...() function                                                             */
/*   - x: please see the calculation formula above; x is limited to the range between zero and seven        */
/*   - y: please see the calculation formula above; y is limited to the range between zero and 15           */
/*----------------------------------------------------------------------------------------------------------*/
void rtiInit(uint8 x, uint8 y)
{
  RTICTL = ((x & 0x07) << 4) | (y & 0x0F);
}

/*----------------------------------------------------------------------------------------------------------*/
/* rtiEnable() enables or disables the RTI                                                                  */
/*   - enable:  TRUE (!= 0), enables the interrupt                                                          */
/*              FALSE (0), disables the interrupt                                                           */
/*----------------------------------------------------------------------------------------------------------*/
void rtiEnable(bool enable)
{
  if (enable)
  {
	  CRGINT = CRGINT | 0x80;   /* enable RTI */
  }
  else
  {
    CRGINT = CRGINT & ~0x80;  /* disable RTI */
  }
}

/*----------------------------------------------------------------------------------------------------------*/
/* rtiClearFlag() clears the interrupt flag of the RTI, so that a new interrupt can be generated            */
/*----------------------------------------------------------------------------------------------------------*/
void rtiClearFlag(void)
{
  CRGFLG = CRGFLG | 0x80; /* clear interrupt flag */
}


/* Interrupt Service Routines - ISR (Real Time Interrupt - RTI) *********************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* rtiIsr() is the ISR for the RTI; it is called, when the RTI is raised                                    */
/*----------------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vrti void rtiIsr(void)
{
  if (rtiClbkFunction)  /* check if there is an associated callback function; if yes, call it */
  {
    rtiClbkFunction();
  }
  rtiClearFlag();       /* clear interrupt flag */
}