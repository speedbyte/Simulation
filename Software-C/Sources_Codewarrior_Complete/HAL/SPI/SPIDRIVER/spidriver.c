
#include "spidriver.h"
				




#pragma CODE_SEG NON_BANKED
void interrupt 19 ISR_SPI0(void)
{
#pragma CODE_SEG DEFAULT

  // receive interrupt
  if(SPI0SR & 0x80)
  { 
   //recDataSPI0 = SPI0DR; // clears RDRF

  }

  // transmit interrupt
  if(SPI0SR & 0x20)
  {
    //SPI0DR = sendDataSPI0;   // clears TDRE
  }
}

void initSPI0Master(unsigned char bauddiv, unsigned char cpol, unsigned char cpha)
{
  DDRS |= 0x60; // set SCK,MOSI on PORT S as Output
  DDRS ^= 0x10; // set MISO on PORT S as Input
  SPI0BR = bauddiv; // set SPI Rate

  // enable Interrupts, SPI, Master mode, select clock polarity/phase
  //SPI0CR1 = 0xF0 | (cpol ? 0x04 : 0) | (cpha ? 0x02 : 0);
  SPI0CR1 = 0x50 | (cpol ? 0x04 : 0) | (cpha ? 0x02 : 0); //<== interrupts disabled
  
  SPI0CR2 = 0; // as default
}

void initSPI0Slave(unsigned char cpol, unsigned char cpha)
{
  DDRS ^= 0xE0; // set SS, SCK,MOSI on PORT S as Input
  DDRS |= 0x10; // set MISO on PORT S as Output

  // enable Interrupts, SPI, select clock polarity/phase
  //SPI0CR1 = 0xE0 | (cpol ? 0x04 : 0) | (cpha ? 0x02 : 0);
  SPI0CR1 = 0x40 | (cpol ? 0x04 : 0) | (cpha ? 0x02 : 0); //<== interrupts disabled
  
  SPI0CR2 = 0; // as default
}

void writeSPI0(unsigned char abyte)
{
  while((SPI0SR & 0x20) == 0) ; // wait for transmitter available

  SPI0DR = abyte;               // start transfer (write data)

  //while((SPI0SR & 0x80) == 0) ; // wait until transfer finished
}