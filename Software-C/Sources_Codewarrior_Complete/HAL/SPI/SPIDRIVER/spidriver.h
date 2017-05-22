
#ifndef _SPI_H
#define _SPI_H

#include <hidef.h>      /* common defines and macros */
#include <mc9s12dp512.h>     /* derivative information */


void initSPI0Master(unsigned char bauddiv, unsigned char cpol, unsigned char cpha);

void initSPI0Slave(unsigned char cpol, unsigned char cpha);

void writeSPI0(unsigned char abyte);																 




































#endif // _SPI_H