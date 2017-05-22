#include <mc9s12dp512.h>        /* derivative information */
#include "spidriver.h"

#pragma LINK_INFO DERIVATIVE "mc9s12dp512"


#define initLED() PTH |= 0x80; DDRH |= 0x80
#define offLED() PTH |= 0x80
#define onLED() PTH &= ~0x80
#define toggleLED() PTH ^= 0x80

void main(void)
{
  unsigned long int i, j;
  const unsigned long delay = 60000;
  unsigned char receivedData = 0, ledPattern = 0, counter = 0;
  
  // activate and start spi0 in slave mode
  initSPI0Slave( 0, 0); // polarity = 0, phase = 0    
	
	initLED();
							
  /* allow all interrupts to take place */
  asm cli;
						
	offLED();					
						
  while(1)
  {
    
    // if one byte was received on spi0
  	if ( SPI0SR & 0x80 )
  	{
  	  receivedData = SPI0DR;
  	  counter = 0;
  	  
  	  // determine LED bit pattern
      for(j=0, ledPattern=0x00; j<(receivedData & 0xFF); j += 0xFF/8) 
      {										       
        // assemble LED bit pattern
        ledPattern = ledPattern<<1 | 0x01;
        counter++;
      }	
   	}

	  toggleLED();
 	
  	for ( i = 0; i < (delay / counter); i++)
  	{
  	  
  	}
  	
  }
}