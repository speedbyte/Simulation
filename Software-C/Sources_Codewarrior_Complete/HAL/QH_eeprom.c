/*************************************************************************************************************


@file:  QH_eeprom.c
@autor: Marc Weber
@date:  Datum: 19.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to control the non-volatile memory (NVM) - EEPROM</h2>


CAUTION: EEPROM variables has to be defined in the EE_DATA segment (use #pragma DATA_SEG EE_DATA and
         afterwards #pragma DATA_SEG DEFAULT); therefore the linker configuration file was changed; see
         Project.prm


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
#include "QH_eeprom.h"
#include <string.h>
#include "typedef.h"


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* eepromSetClock() configures the EEPROM clock divider so that the EEPROM clock has a frequency of 200kHz  */
/* (maximum allowed frequency)                                                                              */
/*----------------------------------------------------------------------------------------------------------*/
void eepromSetClock(void)
{
  if (!ECLKDIV_EDIVLD)
  {
    ECLKDIV = 0x14;     /* 4MHz (oscillator frequency) / 20 to get 200kHz */
  }
}

/*----------------------------------------------------------------------------------------------------------*/
/* eepromWrite() updates the EEPROM memory by erasing and programming; RAM data with the specified length   */
/* is written to the EEPROM                                                                                 */
/*   - ramAdr:    the starting address of the RAM data which is copied to the EEPROM (source); this can be  */
/*                a variable, an array or a struct                                                          */
/*   - eepromAdr: the starting address of the EEPROM sector to which the RAM data is written (destination)  */
/*   - n:         the number of bytes to copy                                                               */
/*----------------------------------------------------------------------------------------------------------*/
void eepromWrite(void* ramAdr, void* eepromAdr, uint16 n) 
{
  uint16* ram = (uint16*) ramAdr;       /* cast to a pointer which points to two byte of data */
  uint16* eeprom = (uint16*) eepromAdr; /* cast to a pointer which points to two byte of data */
  
  uint16 i = 0;
  
  eepromSetClock();                     /* set EEPROM clock to approx. 200kHz (maximum) */
  while (!ESTAT_CBEIF);                 /* wait until buffer is ready to accept new command */
  ESTAT = ESTAT | 0x30;                 /* clear access violation and error flag */
  
  for (i = 0; i <= (n / 4); i++)        /* loop over used EEPROM sectors (four bytes per sector) */
  {
    *eeprom = *ram;                     /* write data (the first two bytes of a sector) */
    ECMD = 0x60;                        /* command: erase and program sector */
                                        /* CAUTION: an EEPROM sector must be erased before new data is */
                                        /*          programmed */
    ESTAT_CBEIF = 1;                    /* execute command */
    
    while(!ESTAT_CBEIF);                /* wait until buffer is ready to accept new command */
    *(++eeprom) = *(++ram);             /* write the second two bytes of the EEPROM sector */
    ECMD = 0x20;                        /* command: program; sector is already erased by the first command */
                                        /* -> 0x60; see above */
    ESTAT_CBEIF = 1;                    /* execute command */
    while(!ESTAT_CBEIF);                /* wait until buffer is ready to accept new command */
    ram++;                              /* pointer to the next two bytes to copy into EEPROM */
    eeprom++;                           /* pointer to the next EEPROM sector */
  }
  while(!ESTAT_CCIF);                   /* wait until all commands are completed */
}

/*----------------------------------------------------------------------------------------------------------*/
/* eepromRead() writes the EEPROM content to the specified address, e.g. a RAM variable, array or struct    */
/*   - ramAdr:    the starting address of the RAM area to which the EEPROM content is written (destination);*/
/*                this can be a variable, an array or a struct                                              */
/*   - eepromAdr: the starting address of the EEPROM data which is copied (source)                          */
/*   - n:         the number of bytes to copy                                                               */
/*----------------------------------------------------------------------------------------------------------*/
void eepromRead(void* ramAdr, void* eepromAdr, uint16 n)
{
  (void) memcpy(ramAdr, eepromAdr, n);
}

/*----------------------------------------------------------------------------------------------------------*/
/* eepromIsErased() checks, if the entire EEPROM is in erased state                                         */
/*  - eepromAdr:  an address in the EEPROM memory (only needed for a dummy write, no data will be changed)  */
/*  return value: TRUE (1):   if the complete EEPROM is erased                                              */
/*                FALSE (0):  if some data is stored in the EEPROM                                          */
/*----------------------------------------------------------------------------------------------------------*/
bool eepromIsErased(void* eepromAdr)
{
  uint16* eeprom = (uint16*) eepromAdr; /* cast to a pointer which points to two byte of data */

  eepromSetClock();                     /* set EEPROM clock to approx. 200kHz (maximum) */
  while (!ESTAT_CBEIF);                 /* wait until buffer is ready to accept new command */
  ESTAT = ESTAT | 0x30;                 /* clear access violation and error flag */
  
  *eeprom = 0xFFFF;                     /* dummy write to EEPROM; address and data will be ignored */
  ECMD = 0x05;                          /* command: verify erase */
  ESTAT_CBEIF = 1;                      /* execute command */
  while(!ESTAT_CCIF);                   /* wait until all commands are completed */
  
  return ESTAT_BLANK;                   /* check flag indicating a blank EEPROM */
}