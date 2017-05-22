
#include <mc9s12dp512.h>     /* derivative information */
#include "adc.h"                /* ADC_Init, ADC_Read */
#include "spidriver.h"


#pragma LINK_INFO DERIVATIVE "mc9s12dp512"

void main(void)
{
  unsigned long int i;
  int j;
  const unsigned long delay = 40000;
  unsigned char sendData;
																 
  // activate and start spi0 in master mode
  initSPI0Master( 1, 0, 0); // baudrate selection register = 0x01, polarity = 0, phase = 1    
  ADC_Init();

  // enable global interrupts
  asm cli;
									 
  while(1)
  {										 	
	  // determine LED bit pattern
    for(j=0, sendData=0x00; j<(ADC_Data & 0x3FF); j += 0x3FF/8) 
    {										       
      // assemble LED bit pattern
      sendData = sendData<<1 | 0x01;
    }										 		
												   
		// write data to spi0
		writeSPI0( sendData );

    for (i=0; i < delay; i++)
    {
		 
    }
  }
}