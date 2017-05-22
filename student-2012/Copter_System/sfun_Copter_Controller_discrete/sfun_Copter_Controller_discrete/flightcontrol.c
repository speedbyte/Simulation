/*************************************************************************************************************


@file:    flightcontrol.c
@author:  Sreekanth Sundaresh
@date:    05.06.2010

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
#include "flightcontrol.h"
#include "typedef.h"


/* Variables ************************************************************************************************/


/* variables for the control algorithm - global because of debug purposes */
static int16 errR;
static int16 errP;
static int16 errY;
static int16 pidR;
static int16 pidP;
static int16 pidY;
static int32 U1;
static int32 U2;
static int32 U3;
static int32 U4;
static int16 prop1F;
static int16 prop2F;
static int16 prop3F;
static int16 prop4F;


/* Function Prototypes **************************************************************************************/


int16 pid(int16 Kp, int16 Ki, int16 Kd, int16 err, int16 delta_err, int32 sum, int16 Ts);
int16 limitToInt16(int32 value);
int32 limitToInt32(int32 value);
uint8 thrustToSetpoint(int16 x, int16 battery);


/* Functions ************************************************************************************************/


void flightControl(void)
{
  static int32 sumR = 0;
  static int32 sumP = 0;
  static int32 sumY = 0;
  static int16 prev_errR = 0;
  static int16 prev_errP = 0;
  static int16 prev_errY = 0;
  
  CopterConfig* copterConfig = copterGetConfigPtr();
  CopterState* copterState = copterGetStatePtr();
  
  if (copterState->remoteMotorsOn)
  {
    /* Get the error signals for the PID controllers */    
    errR = copterState->remoteRoll - (copterState->angR / 10);
    sumR = limitToInt32(sumR + (int32)errR);
    errP = copterState->remotePitch - (copterState->angP / 10);
    sumP = limitToInt32(sumP + (int32)errP);
    errY = copterState->remoteYaw - (copterState->angVelY * 10);
    sumY = limitToInt32(sumY + (int32)errY);
    
    /* Call PID functions for roll, pitch and yaw rate control */
    pidR = pid(copterConfig->kpR, copterConfig->kiR, copterConfig->kdR, errR, (errR - prev_errR), sumR, (FLIGHT_CONTROL_SAMPLE_TIME / 10));
    pidP = pid(copterConfig->kpP, copterConfig->kiP, copterConfig->kdP, errP, (errP - prev_errP), sumP, (FLIGHT_CONTROL_SAMPLE_TIME / 10));
    pidY = pid(copterConfig->kpY, copterConfig->kiY, copterConfig->kdY, errY, (errY - prev_errY), sumY, (FLIGHT_CONTROL_SAMPLE_TIME / 10));
    
    prev_errR = errR;
    prev_errP = errP;
    prev_errY = errY;
    
    U1 = (int32)copterState->remoteForce;
    U2 = (int32)pidR * copterConfig->inertiaX;
    U3 = (int32)pidP * copterConfig->inertiaY;
    U4 = (int32)pidY * copterConfig->inertiaZ;
    
    /* Force needed at the propellers in [1000*N] */
    prop1F = limitToInt16((U1 / 4) - (U3 / (2 * copterConfig->lenBoom)) + (U4 / (4 * copterConfig->lenBoom)));
    prop2F = limitToInt16((U1 / 4) + (U2 / (2 * copterConfig->lenBoom)) - (U4 / (4 * copterConfig->lenBoom)));
    prop3F = limitToInt16((U1 / 4) + (U3 / (2 * copterConfig->lenBoom)) + (U4 / (4 * copterConfig->lenBoom)));
    prop4F = limitToInt16((U1 / 4) - (U2 / (2 * copterConfig->lenBoom)) - (U4 / (4 * copterConfig->lenBoom)));
    
    copterState->forceFront = prop1F;
    copterState->forceLeft  = prop2F;
    copterState->forceRear  = prop3F;
    copterState->forceRight = prop4F;
    
    /* Calculate the total propeller force in [1000*N] */
    copterState->forceTotal = limitToInt16(((int32)prop1F + prop2F) + prop3F + prop4F);

    /* Call thrustToSetpoint function to calculate setpoint for the propellers */
    copterState->setpointFront = thrustToSetpoint(prop1F, copterState->battery);
    copterState->setpointLeft  = thrustToSetpoint(prop2F, copterState->battery);
    copterState->setpointRear  = thrustToSetpoint(prop3F, copterState->battery);
    copterState->setpointRight = thrustToSetpoint(prop4F, copterState->battery);
  }
  else
  {
    /* Reset all variables if motors are off */
    sumR = 0;
    sumP = 0;
    sumY = 0;
    prev_errR = 0;
    prev_errP = 0;
    prev_errY = 0;
  
    copterState->forceFront = 0;
    copterState->forceLeft  = 0;
    copterState->forceRear  = 0;
    copterState->forceRight = 0;
    copterState->forceTotal = 0;
    copterState->setpointFront = 0;
    copterState->setpointLeft  = 0;
    copterState->setpointRear  = 0;
    copterState->setpointRight = 0;
  }
}

/*----------------------------------------------------------------------------------------------------------*/
/* User-defined Function:pid
 *    In this function, Calculation of the controller output is done. 
 *    \param     int16 Kp         Gain Factor of P-controller      
 *    \param     int16 Ki         Gain Factor of I-controller      
 *    \param     int16 Kd         Gain Factor of D-controller      
 *    \param     int16 err        Error input for the controller
 *    \param     int16 delta_err  Current error minus previous error
 *    \param     int32 sum        Sum of all errors (for I-part)
 *    \param     int16 Ts         Inherited Sample time from the Simulink
 *    \return    int16 Contr_out  Controller output
 */
int16 pid(int16 Kp, int16 Ki, int16 Kd, int16 err, int16 delta_err, int32 sum, int16 Ts)
{
  /* Calculate the output with the resolution compensation for P-part, I-part & D-part 
   * appropriately 
   */
   int32 p = limitToInt16(((int32)Kp * err) / 100);
   int32 i = limitToInt16((((int32)Ki * (sum/100)) * Ts) / 100);
   int32 d = limitToInt16(((int32)Kd * delta_err) / Ts);
   
   return limitToInt16(p + i + d);
}

/*----------------------------------------------------------------------------------------------------------*/
uint8 limitToUint8(int16 value)
{
  static uint32 countMax8 = 0;
  static uint32 countMin8 = 0;
  
  if (value > MAX_UINT8)
  {
    countMax8++;
    return MAX_UINT8;
  }
  else if (value < MIN_UINT8)
  {
    countMin8++;
    return MIN_UINT8;
  }
  else
    return (uint8)(value);
}

/*----------------------------------------------------------------------------------------------------------*/
int16 limitToInt16(int32 value)
{
  static uint32 countMax16 = 0;
  static uint32 countMin16 = 0;
  
  if (value > MAX_INT16)
  {
    countMax16++;
    return MAX_INT16;
  }
  else if (value < MIN_INT16)
  {
    countMin16++;
    return MIN_INT16;
  }
  else
    return (int16)(value);
}

/*----------------------------------------------------------------------------------------------------------*/
int32 limitToInt32(int32 value)
{
  static uint32 countMax32 = 0;
  static uint32 countMin32 = 0;
  
  if (value > MAX_INT32_2)
  {
    countMax32++;
    return MAX_INT32_2;
  }
  else if (value < MIN_INT32_2)
  {
    countMin32++;
    return MIN_INT32_2;
  }
  else
    return value;
}

/*----------------------------------------------------------------------------------------------------------*/
/* User-defined Function:thrustToSetpoint
 *    In this function, interpolation of the curve is done. 
 *    \param     int16 x         Point for which interpolation to be done
 *    \param     int16 battery   The actual battery voltage [10*V]
 *    \return    int16 y         Interpolated output
 */
uint8 thrustToSetpoint(int16 x, int16 battery)
{
  static uint8 n = THRUST2SETPOINT_DATAPOINTS;
  static int16 xin[THRUST2SETPOINT_DATAPOINTS] = {0, 500, 4500};
  static uint8 yout[THRUST2SETPOINT_DATAPOINTS] = {10, 40, 175};
  
  int16 x1  = 0;
  int16 x2  = 0;
  int16 y1  = 0;
  int16 y2  = 0;
  int16 y   = 0;
  int16 i   = 0;
  int16 cor = 0;

  if (x < xin[0])
  {
    y = yout[0];
  }
  else if (x > xin[n-1])
  {
    y = yout[n-1];
  }
  else
  { 
    for (i = 0; i < n-1; i++)
    {
      if ((x >= xin[i]) && (x <= xin[i+1]))
      {
        x1 = xin[i];
        x2 = xin[i+1];
        y1 = yout[i];
        y2 = yout[i+1];
        y  = limitToInt16(y1 + ((int32)(y2 - y1) * (x - x1)) / (x2 - x1));
        break;
      }
    }
  }
  
  if (battery <= 100)
  {
    cor = 120;
  }
  else if (battery >= 120)
  {
    cor = 100;
  }
  else
  {
    cor = 220 - battery;
  }
  
  /* Maximum values: y = 255; cor = 120 */
  return limitToUint8((y * cor) / 100);
}