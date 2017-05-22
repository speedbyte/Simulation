/*************************************************************************************************************


@file:  QH_eeprom.c
@autor: Marc Weber
@date:  Datum: 20.05.2010

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


#ifndef QH_EEPROM_H
  #define QH_EEPROM_H


/* Includes *************************************************************************************************/


  #include "typedef.h"


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* eepromWrite() updates the EEPROM memory by erasing and programming; RAM data with the specified length   */
/* is written to the EEPROM                                                                                 */
/*   - ramAdr:    the starting address of the RAM data which is copied to the EEPROM (source); this can be  */
/*                a variable, an array or a struct                                                          */
/*   - eepromAdr: the starting address of the EEPROM sector to which the RAM data is written (destination)  */
/*   - n:         the number of bytes to copy                                                               */
/*----------------------------------------------------------------------------------------------------------*/
  void eepromWrite(void* ramAdr, void* eepromAdr, uint16 n);

/*----------------------------------------------------------------------------------------------------------*/
/* eepromRead() writes the EEPROM content to the specified address, e.g. a RAM variable, array or struct    */
/*   - ramAdr:    the starting address of the RAM area to which the EEPROM content is written (destination);*/
/*                this can be a variable, an array or a struct                                              */
/*   - eepromAdr: the starting address of the EEPROM data which is copied (source)                          */
/*   - n:         the number of bytes to copy                                                               */
/*----------------------------------------------------------------------------------------------------------*/
  void eepromRead(void* ramAdr, void* eepromAdr, uint16 n);

/*----------------------------------------------------------------------------------------------------------*/
/* eepromIsErased() checks, if the entire EEPROM is in erased state                                         */
/*  - eepromAdr:  an address in the EEPROM memory (only needed for a dummy write, no data will be changed)  */
/*  return value: TRUE (1):   if the complete EEPROM is erased                                              */
/*                FALSE (0):  if some data is stored in the EEPROM                                          */
/*----------------------------------------------------------------------------------------------------------*/
  bool eepromIsErased(void* eepromAdr);


/************************************************************************************************************/


#endif