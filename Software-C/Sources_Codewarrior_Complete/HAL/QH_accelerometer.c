/*************************************************************************************************************


@file:  QH_accelerometer.c
@autor: Marc Weber
@date:  Datum: 17.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to control the accelerometer over Serial Peripheral Interface 0 (SPI0)</h2>


CAUTION: - To work probably, a bus clock of 24MHz is required. Therefore pllInit() must be called before!


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


#include "copter.h"
#include "derivative.h"
#include "QH_accelerometer.h"
#include "typedef.h"


/* Variables ************************************************************************************************/


/* byte sequence to configure the accelerometer (multi byte writing) */
static uint8 configSequence[4] = {0x40 | CTRL_REG_ADR, CTRL_REG1, CTRL_REG2, CTRL_REG3};

/* byte sequence to read the acceleration values out of the accelerometer (multi byte reading) */
static uint8 accelRequest[7] = {0xC0 | ACCEL_REG_ADR, DUMMY, DUMMY, DUMMY, DUMMY, DUMMY, DUMMY};

/* array used to save the acceleration values */
static uint8 sensorData[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* calibration variables */
static int16 accXOffset = 0;
static int16 accYOffset = 0;
static int16 accZOffset = 0;
static int16 sensorSensitivityY = 343; //1020;//mittelwert 357;
static int16 sensorSensitivityX = 354; //1047;
static int16 sensorSensitivityZ = 355; //1058;
                                                           
/* arcsin Kennfeld*/
float Kennfeld[21][2] = { {10000, 10000 },{2.2942,0.9450 },{1.6667,0.4060 },{1.4003,0.2048 },
                          {1.25,0.1065 },{1.1547,0.0538 },{1.0911,0.0249 },{1.0483,0.0098 },
                          {1.0206,0.0028 },{1.005,0.0003 },{1,0 },{1.005,-0.0003 }, {1.0206,-0.0028 },
                          {1.0483,-0.0098 },{1.0911,-0.0249 },{1.1547,-0.0538 },{1.25,-0.1065 },{1.4003,-0.2048 },
                          {1.6667,-0.4060 },{2.2942,-0.9450 },{10000,-10000 }};
float ArcSin[21] = {-1.5708, -1.1198, -0.9273, -0.7754, -0.6435, -0.5236, -0.4115, -0.3047, -0.2014, -0.1002, 0,
                    0.1002, 0.2014, 0.3047, 0.4115, 0.5236, 0.6435, 0.7754, 0.9273, 1.1198,1.5708};
  

/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* accelSendReceive() sends out a specified number of bytes over the SPI interface; the read values are     */
/* written back                                                                                             */
/*   - out: a pointer to the array containing the data bytes to send out; the minimal array size is         */
/*          specified by parameter 'n'                                                                      */
/*   - in:  a pointer to the array to which the received data bytes are written; the minimal array size is  */
/*          specified by parameter 'n'                                                                      */
/*   - n:   the number of bytes to send out / read back                                                     */
/*----------------------------------------------------------------------------------------------------------*/
void accelSendReceive(uint8* out, uint8* in, uint16 n)
{
  uint16 i = 0;
  PTS_PTS7 = 0;             /* manually set the ~SS (also ~CS) to low (start communication) */
  
  /* send out / read back 'n' bytes */
  for (i = 0; i < n; i++)
  {
    while (!SPI0SR_SPTEF);  /* wait until data register is free */
    SPI0DR = out[i];        /* write byte to data register (send it) */
    while(!SPI0SR_SPIF);    /* wait for data in data register */
    if (in == NULL)         /* check if data is written back or not */
    {
      (void) SPI0DR;        /* read the data register to clear */
    }
    else
    {
      in[i] = SPI0DR;       /* write back received byte */
    }
  }
  
  PTS_PTS7 = 1;             /* manually set the ~SS (also ~CS) to high (communication finished)*/
}

/*----------------------------------------------------------------------------------------------------------*/
/* accelInit() configures the SPI interface of the microcontroller, so that it can be used to communicate   */
/* with the accelerometer; additionally the accelerometer itself is configured; this function must be       */
/* called before any other accel...() function                                                              */
/*----------------------------------------------------------------------------------------------------------*/
void accelInit(void)
{
  
  DDRH = DDRH & 0xEF; /* port H, pin 4 is an input, used for data ready signalisation by the accelerometer */
  
  DDRS_DDRS7 = 1;     /* port S, pin 7 is an output, used for ~SS signal */
  PTS_PTS7 = 1;       /* port S, pin 7 is logical high; accelerometer interface deactive */

  
  SPI0BR  = 0x00;     /* SPI baud rate configuration: baud rate = BUSCLK / ((x + 1) * 2^(y + 1)); */
                      /* configured for 12Mhz (at 24Mhz BUSCLK) */
                      /* bit 6 to 4: x value (see formula above) */
                      /* bit 2 to 0: y value (see formula above) */
                      
  SPI0CR1 = 0x5C;     /* bit 7:      disabled SPI interrupt */
                      /* bit 6:      enalbe SPI */
                      /* bit 5:      disable SPI transmit interrupt */
                      /* bit 4:      SPI in master mode */
                      /* bit 3:      in idle state SCK is high */
                      /* bit 2:      sampling of data at even edges (2nd, 4th etc.) */
                      /* bit 1:      ~SS not controlled by the SPI controller (is done manually because of */
                      /*             multi-byte read and write operations */
                      /* bit 0:      data is transferred most significant bit first */
                      
  SPI0CR2 = 0x00;     /* bit 4:      ~SS port pin is not used by SPI controller directly */
                      /* bit 3:      disable output buffer */
                      /* bit 1:      SPI clock operates normally in wait mode */
                      /* bit 0:      no combind MISO/MOSI pin; 4-wire SPI */
  
  (void) SPI0SR;      /* read the status register to clear */
  (void) SPI0DR;      /* read the data register to clear */
  
  /* configure the accelerometer over SPI */
  accelSendReceive(configSequence, NULL, 4);
}

/*----------------------------------------------------------------------------------------------------------*/
/* accelCalibrate() calculates the zero level offset of the accelerometer (X-, Y- and Z-axis); this         */
/* function should be called before the first call of accelGetValues()                                      */
/* CAUTION: to get right offset values, the copter must stand on a plain ground                             */
/*----------------------------------------------------------------------------------------------------------*/
void accelCalibrate(void)
{

  accelSendReceive(accelRequest, sensorData, 7);  /* read the actual acceleration values */
  
  /* calculate the offset value for the X-, Y- and Z-axis; each raw value of the accelerometer is composed  */
  /* of two received bytes; see also chapter 5.2 in the datasheet of the accelerometer (LIS3LV02DQ) */
  accYOffset = -23;//(sensorData[2] << 8) + sensorData[1];//-23
  accXOffset = -5;//(sensorData[4] << 8) + sensorData[3];//-6
  accZOffset = ((sensorData[6] << 8) + sensorData[5]) - sensorSensitivityZ;
  
  /* CAUTION - FURTHER IMPROVEMENT: use the self test functionality of the accelerometer */
}

/*----------------------------------------------------------------------------------------------------------*/
/* accelGetValues() gets the actual values of the accelerometer (raw and physical value for X-, Y- and      */
/* Z-axis) and writes them to the CopterState structure                                                     */
/*----------------------------------------------------------------------------------------------------------*/
void accelGetValues(void)
{
  /* get pointer to the CopterState structure (real-time database) */
 CopterState* copterState = copterGetStatePtr();

  /* while (!PTH_PTH4); */                        /* wait for data ready signal */
  /* CAUTION: the wait command causes a processor freeze after a while, therefore it is commented out */
  
  accelSendReceive(accelRequest, sensorData, 7);  /* read the actual acceleration values */
  
  /* calculate the raw acceleration values; each value is composed of two received bytes; see also chapter  */
  /* 5.2 in the datasheet of the accelerometer (LIS3LV02DQ) */
  copterState->accYRaw = (int16)((sensorData[2] << 8) + sensorData[1]);
  copterState->accXRaw = (int16)((sensorData[4] << 8) + sensorData[3]);         
  copterState->accZRaw = (int16)((sensorData[6] << 8) + sensorData[5]);
  
  (void) accelCalcPhysicalValues(copterState);
}

float f_arcsin(float x) {
 int h;
 float m;
 
 h = (int)((x+1)*10);   // float to Index transformation
 
 if(h<0)return -1.5708;    // -pi/2 Max Angle
 if(h>=20)return 1.5708;  // +pi/2  Max Angle
 
 m = ((ArcSin[h+1]-ArcSin[h])/0.1); 
 
 
 // Interpolate value
 return (x-(float)(h*0.1-1))*m+ArcSin[h]; //Kennfeld[h][0]*x+Kennfeld[h][1]; 
}

void accelCalcPhysicalValues(CopterState* copterState) {

  /* calculate the physical acceleration values in [(10 * m)/(s^2)], as needed by the control algorithm */
  /* 24.10 und invertiere y*/
  copterState->accY =  (int16)(((((int32)(copterState->accYRaw)-(int32)(accYOffset)) * G) / sensorSensitivityY) / 10);
  copterState->accX = -(int16)(((((int32)(copterState->accXRaw)-(int32)(accXOffset)) * G) / sensorSensitivityX) / 10);
  copterState->accZ = -(int16)((((int32)(copterState->accZRaw) * G) / sensorSensitivityZ) / 10);

  // [ 1000*rad ]                                           commended for simulation
  copterState->angP = -(f_arcsin((float)(copterState->accXRaw-accXOffset)/sensorSensitivityX));
  copterState->angR = -(f_arcsin((float)(copterState->accYRaw-accYOffset)/sensorSensitivityY));
}