/*************************************************************************************************************


@file:  typedef.h
@autor: Marc Weber, inspired by Dionysios Satikidis and Apostolos Georgiadis
@date:  Datum: 12.04.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Type definitions</h2>


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


#ifndef TYPEDEF_H
  #define TYPEDEF_H


/* Defines **************************************************************************************************/


  #define NULL            ((void *) 0)
  
  #define TRUE                       1
  #define FALSE                      0
  
  #define MAX_UINT8                255
  #define MIN_UINT8                  0
  
  #define MAX_INT16              32767
  #define MIN_INT16             -32768
  
  #define MAX_INT32_2   ( 1073741824L)
  #define MIN_INT32_2   (-1073741824L)


/* Typedefs *************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/*   bool:    data type that can have values TRUE and FALSE                                                 */
/*   uint8:   data type that can have values  0 to 255                                                      */
/*   int8:    data type that can have values -128 to 127                                                    */
/*   uint16:  data type that can have values 0 to 65535                                                     */
/*   int16:   data type that can have values -32768 to +32767                                               */
/*   uint32:  data type that can have values 0 to 4294967296                                                */
/*   int32:   data type that can have values -2147483648 to 2147483647                                      */
/*----------------------------------------------------------------------------------------------------------*/

  typedef unsigned char       bool;
  typedef unsigned char       uint8;
  typedef signed char         int8;
  typedef unsigned short      uint16;
  typedef signed short        int16;
  typedef unsigned int        uint32;
  typedef signed int          int32;


/************************************************************************************************************/


#endif