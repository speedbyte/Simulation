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

/* Defines ***********************************************************************************/
#define I_Angles (0)
#define P_Angles (2)  //3
#define D_Angles (0)
#define N_Angles (0)

#define I_Rates (0.25) //0.25
#define P_Rates (40)   //40
#define D_Rates (0)
#define N_Rates (0)

/*

#define I_Angles (0)
#define P_Angles (1.1)
//float P_Angles = 0;
#define D_Angles (0)
#define N_Angles (0)

#define I_Rates (0.25)
//float I_Rates = 0;
#define P_Rates (2.0)
//float P_Rates = 0;
#define D_Rates (0)
#define N_Rates (0)
*/

/* Variables ************************************************************************************************/


/* variables for the control algorithm - global because of debug purposes */
//static int16 errR;
//static int16 errP;
//static int16 errY;
//static int16 pidR;
//static int16 pidP;
//static int16 pidY;
//static int32 U1;
//static int32 U2;
//static int32 U3;
//static int32 U4;
//static int16 prop1F;
//static int16 prop2F;
//static int16 prop3F;
//static int16 prop4F;

   //                  0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250
   uint8 yM1[THRUST2SETPOINT_DATAPOINTS] = {0, 27, 53, 78, 104, 129, 154, 179, 200, 225, 250};
   uint8 yM2[THRUST2SETPOINT_DATAPOINTS] = {0, 25, 50, 75, 99, 124, 147, 178, 201, 225, 250};
   uint8 yM3[THRUST2SETPOINT_DATAPOINTS] = {0, 28, 52, 77, 103, 128, 153, 170, 188, 225, 250};
   uint8 yM4[THRUST2SETPOINT_DATAPOINTS] = {0, 25, 50, 75, 100, 125, 153, 178, 203, 225, 250};
   uint8 yMx[THRUST2SETPOINT_DATAPOINTS] = {0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250};


/* Function Prototypes **************************************************************************************/


float PID(float P, float I, float D, float N, float ek, float* ek_1, float *IState, float *FiltState, float Ts);
int16 limitToInt16(int32 value);
int32 limitToInt32(int32 value);
uint8 thrustToSetpoint(int16 x, int16 battery, uint8 *yout);
void Controll(CopterState* copterState, CopterConfig* copterConfig);


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
    Controll(copterState, copterConfig);
  }
  else
  {
    /* Reset all variables if motors are off */
    copterState->e_r_Yaw_1            = 0;
    copterState->r_Yaw_I_State        = 0;
    copterState->r_Yaw_Filter_State   = 0;
    copterState->e_r_Roll_1           = 0;
    copterState->r_Roll_I_State       = 0;
    copterState->r_Roll_Filter_State  = 0;
    copterState->e_r_Pitch_1          = 0;
    copterState->r_Pitch_I_State      = 0;
    copterState->r_Pitch_Filter_State = 0;
  
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


void Controll(CopterState* copterState, CopterConfig* copterConfig) 
{
   
   // Motorvalues for the next sampletime
   static uint8 M1_limited = 0;
   static uint8 M2_limited = 0;
   static uint8 M3_limited = 0;
   static uint8 M4_limited = 0;
   
   float M1, M2, M3, M4;
   
   float e_Pitch, e_Roll, m_Roll, m_Pitch;
   float e_r_Pitch, e_r_Roll, e_r_Yaw, m_r_Pitch, m_r_Roll, m_r_Yaw;
   
   static float Ts = 0.005; // Sample time      // static 4 test
    
    // Set outputs to Values calculated last sample time
   copterState->setpointFront = M1_limited;
   copterState->setpointLeft  = M2_limited;
   copterState->setpointRear  = M3_limited;
   copterState->setpointRight = M4_limited;
   
   //% calculate error values for the controlled angles
   //% Pitch error 
   e_Pitch = (float)(copterState->remotePitch)/100 - (float)(copterState->Pitch_filt);//->angP)/1000;
   //% Roll error
   e_Roll = (float)(copterState->remoteRoll)/100 - (float)(copterState->Roll_filt);//->angR)/1000;
   //% calculate controller output for the angles (I State & FilterState are not necessary cause only p is used
   m_Roll  = PID(P_Angles,I_Angles,D_Angles,N_Angles,e_Roll,&(copterState->e_Roll_1),
                 &(copterState->Roll_I_State), &(copterState->Roll_Filter_State), Ts);
   m_Pitch = PID(P_Angles,I_Angles,D_Angles,N_Angles,e_Pitch,&(copterState->e_Pitch_1),
                 &(copterState->Pitch_I_State),&(copterState->Pitch_Filter_State),Ts);
      
   //% Yaw Rate error
   e_r_Yaw = (float)(copterState->remoteYaw)/100 - (float)(copterState->angVelY)/100;
   //% Pitch Rate error
   e_r_Pitch = m_Pitch - (float)(copterState->angVelP)/100;
   //% Roll Rate error
   e_r_Roll = m_Roll - (float)(copterState->angVelR)/100;
   //% calculate  controller output for rates
   m_r_Yaw   = PID (P_Rates, I_Rates, D_Rates,N_Rates,e_r_Yaw, &(copterState->e_r_Yaw_1), 
                &(copterState->r_Yaw_I_State), &(copterState->r_Yaw_Filter_State),Ts);
   m_r_Roll  = PID (P_Rates, I_Rates, D_Rates,N_Rates,e_r_Roll, &(copterState->e_r_Roll_1), 
                &(copterState->r_Roll_I_State), &(copterState->r_Roll_Filter_State),Ts);
   m_r_Pitch = PID (P_Rates, I_Rates, D_Rates,N_Rates,e_r_Pitch, &(copterState->e_r_Pitch_1),
                &(copterState->r_Pitch_I_State), &(copterState->r_Pitch_Filter_State),Ts);
   
    //Calculate new setpoints of all motors
    M1 = (float)(copterState->remoteForceRaw)-m_r_Pitch+m_r_Yaw;
    M2 = (float)(copterState->remoteForceRaw)+m_r_Roll-m_r_Yaw;
    M3 = (float)(copterState->remoteForceRaw)+m_r_Pitch+m_r_Yaw;
    M4 = (float)(copterState->remoteForceRaw)-m_r_Roll-m_r_Yaw;
    
    // saturate setpoint of motor1 to 0 if less and 255 if above
    if(M1 < 10){
      M1_limited = 10;
    }else if(M1 > 255){
      M1_limited = 255; 
    }else{
         M1_limited=(uint8)(M1);//thrustToSetpoint(M1, 120, yM1);
    }
    
    // saturate setpoint of motor2 to 0 if less and 255 if above
    if(M2 < 10){
      M2_limited = 10;
    }else if(M2 > 255){
      M2_limited = 255; 
    }else{
         M2_limited=(uint8)(M2);//thrustToSetpoint(M2, 120, yM2);
    }

    // saturate setpoint of motor3 to 0 if less and 255 if above
    if(M3 < 10){
      M3_limited = 10;
    }else if(M3 > 255){
      M3_limited = 255; 
    }else{
         M3_limited=(uint8)(M3);//thrustToSetpoint(M3, 120, yM3);
    }
    
    // saturate setpoint of motor4 to 0 if less and 255 if above
    if(M4 < 10){
      M4_limited = 10;
    }else if(M4 > 255){
      M4_limited = 255; 
    }else{                 
         M4_limited=(uint8)(M4);//thrustToSetpoint(M4, 120, yM4);
    }
    
    
}

/*----------------------------------------------------------------------------------------------------------*/
/* User-defined Function:PID
 *    In this function, Calculation of the controller output is done. 
 *    \param     float P             Gain Factor of P-controller      
 *    \param     float I             Gain Factor of I-controller      
 *    \param     float D             Gain Factor of D-controller      
 *    \param     float N             Filter Factor for D-part
 *    \param     float ek            Error of aktive sample time 
 *    \param     float *ek_1         Pointer to error of last sample time
 *    \param     float *IState       Pointer to integral state of I-part
 *    \param     float *FilterState  Pointer to integral state of the filter 
 *    \return    float Ts            Used sample time
 */
float PID(float P, float I, float D, float N, float ek, float* ek_1, float *IState, float *FiltState, float Ts)
{
  /* Calculate the output with the resolution compensation for P-part, I-part & D-part 
   * appropriately 
   */
   float ret = 0;      // return value
   float yd = 0;       // result of derivative
   
    
        if (I != 0) {
            //% calculate new itegral value
            (*IState) = ek * Ts * I + (*IState);
        }
        else {
          
            (*IState) = 0;
        }

        if (D != 0){
            //% calculate new derivative value
            yd = (ek - (*ek_1))/Ts * D;

            //% Filter the derivative  value
            (*FiltState) = yd;//Ts * (yd - N * (*FiltState))+ (*FiltState) ;
        }
        else{
            (*FiltState) = 0;
        }

        //% Add all values 
        ret = (P * ek + (*IState) + *(FiltState));
    //% save error for next sample time
   *ek_1 = ek;
   
   return ret;
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
uint8 thrustToSetpoint(int16 x, int16 battery, uint8* yout)
{
  static uint8 n = THRUST2SETPOINT_DATAPOINTS;
  static int16 xin[THRUST2SETPOINT_DATAPOINTS] = {0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250};
    
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