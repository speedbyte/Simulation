/*************************************************************************************************************


@file:    sensorfilter.c
@author:  Sreekanth Sundaresh
@date:    20.05.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.


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
#include "sensorfilter.h"
#include "typedef.h"


/* Function Prototypes **************************************************************************************/


int16 Compl_Filter(int16 Acc_in, int16 Gyro_in, int16 Filt_old, int16 LPF, int16 HPF, int16 Ts);


/* Functions ************************************************************************************************/


void sensorFilter(void)
{
  CopterConfig* copterConfig = copterGetConfigPtr();
  CopterState* copterState = copterGetStatePtr();
  
  int16 lpR = copterConfig->lpR;
  int16 hpR = copterConfig->hpR;
  int16 lpP = copterConfig->lpP;
  int16 hpP = copterConfig->hpP;
  
  int16 accX = copterState->accX;
  int16 accY = copterState->accY;
  int16 angVelR = copterState->angVelR;
  int16 angVelP = copterState->angVelP;
  
  /* get the new filtered output value for the roll angle */
  copterState->angR = Compl_Filter(-accY, angVelR, copterState->angR, lpR, hpR, SENSOR_FILTER_SAMPLE_TIME);

  /* get the new filtered output value for the pitch angle */
  copterState->angP = Compl_Filter(accX, angVelP, copterState->angP, lpP, hpP, SENSOR_FILTER_SAMPLE_TIME);
}

/*----------------------------------------------------------------------------------------------------------*/
/* User-defined Function:Compl_Filter
 *    In this function, Calculation of the Filter output is done. 
 *    
 *    Filtering action is done by the following formula
 *
 *    |---------------------------------------------------------------|
 *    |Filt_out = HPF * ((Gyro_in * Ts) + Filt_old) + LPF * (Acc_in/g)|
 *    |---------------------------------------------------------------| 
 *
 *    This is done with the following discretization
 *                                     _                                                _                         _              _ 
 *    (10000 *Filt_out) = (100 * HPF) |  (100*Gyro_in) * (100 * Ts)+ (10000 * Filt_old)  |     100 * (100 * LPF) |  (10 * Acc_in) |
 *                                    |                                                  |  +                    |  ------------- |
 *                                    |_                                                _|                       |_  (10 * g)    _|
 *                         ----------------------------------------------------------------          
 *                                                   100                                                                
 *
 *    \param     int16 Acc_in     Accelerometer input for the filter
 *    \param     int16 Gyro_in    Gyro input for the filter      
 *    \param     int16 LPF        Low Pass filter factor
 *    \param     int16 HPF        High Pass filter factor
 *    \param     int16 Ts         Inherited Sample time from the Simulink
 *    \return    int16 Filt_out   Filter output
 */
int16 Compl_Filter(int16 Acc_in, int16 Gyro_in, int16 Filt_old, int16 LPF, int16 HPF, int16 Ts)
{
  static uint32 countMax = 0;
  static uint32 countMin = 0;
  
  /* temp1 is the angle component with High-pass filter with the resolution of 0.0001 */
  /* HPF inverse resolution is 100, Gyro_in inverse resolution is 100 */
  /* Ts inverse resolution is 100, Filt_old inverse resolution is 10000 */
  /* So in order to get the inverse resolution of 10000 for temp 1, resolution compensation of */
  /* "division" by 100 is needed */
  /* Inv Res(temp1) = Inv Res(HPF) * Inv Res(Sum) * x */
  /* x = Resolution compensation factor */
  /* 10000 = 100 * 10000 * x */
  /* x = 1/100 */

  int32 temp1 = (HPF * ((((int32)Gyro_in * Ts) / 10) + Filt_old)) / 100;

  /* temp2 is the angle component with Low-pass filter with the resolution of 0.0001 */
  /* LPF inverse resolution is 100, Acc_in inverse resolution is 10,ACC_GRAVITY inverse resolution is 10 */
  /* So in order to get the inverse resolution of 10000 for temp 2, resolution compensation of */
  /* "multiplication" by 100 is needed */
  /* Inv Res(temp2) = Inv Res(LPF) * (Inv Res(Acc_in)/Inv Res(ACC_GRAVITY)) * x */
  /* x = Resolution compensation factor */
  /* 10000 = 100 * (10/10) * x */
  /* x = 100 */

  int32 temp2 = ((((int32)LPF * 100) * Acc_in) / ACC_GRAVITY);

  if ((temp1 + temp2) > MAX_INT16)
  {
    countMax++;
    return MAX_INT16;
  }
  else if ((temp1 + temp2) < MIN_INT16)
  {
    countMin++;
    return MIN_INT16;
  }
  else
    return (int16)(temp1 + temp2);
}