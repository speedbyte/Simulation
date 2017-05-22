/*************************************************************************************************************


@file:  copter.c
@autor: Marc Weber
@date:  Datum: 19.06.2010

Copyright (C) 2007 University of Applied Sciences Esslingen

This software is subject to the LGPL license terms.

$Id:$
$Rev:$

<h2>Functions to handle the real-time image of the quadrocopter</h2>


CAUTION: - To work properly, all used components of the Hardware Abstraction Layer (HAL) must be initialized,
           (see Includes section)


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


#ifndef COPTER_H
  #define COPTER_H


/* Includes *************************************************************************************************/


  #include "typedef.h"


/* Typedefs *************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* CopterState holds all status data of the quadrocopter system (real-time image)                           */
/*----------------------------------------------------------------------------------------------------------*/
  typedef struct
  {
    /* accelerometer */
    int16 accXRaw;        /* -2048 .. 2047 */
    int16 accX;           /* [(10*m)/(s^2)] */
    int16 accYRaw;        /* -2048 .. 2047 */
    int16 accY;           /* [(10*m)/(s^2)] */
    int16 accZRaw;        /* -2048 .. 2047 */
    int16 accZ;           /* [(10*m)/(s^2)] */
    
    /* ATD; gyroscopes, temperature, air pressure and battery voltage */
    int16 angVelRRaw;     /* 0 .. 1024 */
    int16 gyroROffset;                    // -------------   modified/injected
    int16 angVelR;        /* [(100*rad)/sec] */
    float angR;           /* [10000*rad] */
    int16 angVelPRaw;     /* 0 .. 1024 */
    int16 gyroPOffset;                    // -------------   modified/injected
    int16 angVelP;        /* [(100*rad)/sec] */
    float angP;           /* [10000*rad] */
    int16 angVelYRaw;     /* 0 .. 1024 */
    int16 gyroYOffset;                    // --------------  modified/injected
    int16 angVelY;        /* [(100*rad)/sec] */
    int16 tempRaw;        /* 0 .. 1024 */
    int16 temp;           /* [°C] */
    int16 airPressureRaw; /* 0 .. 1024 */
    int16 batteryRaw;     /* 0 .. 1024 */
    int16 battery;        /* [10*V] */
    
    /* brushless */
    int16 forceFront;     /* [1000*N] */
    uint8 setpointFront;  /* 0 .. 255 */
    int16 forceRear;      /* [1000*N] */
    uint8 setpointRear;   /* 0 .. 255 */
    int16 forceRight;     /* [1000*N] */
    uint8 setpointRight;  /* 0 .. 255 */
    int16 forceLeft;      /* [1000*N] */
    uint8 setpointLeft;   /* 0 .. 255 */
    int16 forceTotal;     /* [1000*N] */
    
    /* remote */
    bool remoteConnected; /* 0 .. 1 */
    bool remoteMotorsOn;  /* 0 .. 1 */
    uint8 remoteForceRaw; /* 0 .. 255 */
    int16 remoteForce;    /* [1000*N] */
    uint8 remoteYawRaw;   /* 0 .. 255 */
    int16 remoteYaw;      /* [(1000*rad)/sec] */
    uint8 remotePitchRaw; /* 0 .. 255 */
    int16 remotePitch;    /* [1000*rad] */
    uint8 remoteRollRaw;  /* 0 .. 255 */
    int16 remoteRoll;     /* [1000*rad] */
    
    float e_Roll_1,Roll_I_State,Roll_Filter_State;
    float e_Pitch_1,Pitch_I_State,Pitch_Filter_State;
    float e_r_Yaw_1, r_Yaw_I_State, r_Yaw_Filter_State;
    float e_r_Roll_1, r_Roll_I_State, r_Roll_Filter_State;
    float e_r_Pitch_1, r_Pitch_I_State, r_Pitch_Filter_State;
    
    float Roll_filt, Pitch_filt;
    float r_Roll_filt, r_Pitch_filt, r_Yaw_filt;
    
  } CopterState;
  
  extern CopterState mycopterState;

/*----------------------------------------------------------------------------------------------------------*/
/* CopterConfig holds all configuration parameter of the quadrocopter system                                */
/*----------------------------------------------------------------------------------------------------------*/
  typedef struct
  {
    /* PID governor for roll angle */
    int16 kpR;          /* [100/sec^2] */
    int16 kiR;          /* [100/sec^3] */
    int16 kdR;          /* [100/sec] */
    
    /* PID governor for pitch angle */
    int16 kpP;          /* [100/sec^2] */
    int16 kiP;          /* [100/sec^3] */
    int16 kdP;          /* [100/sec] */
    
    /* PID governor for yaw velocity */
    int16 kpY;          /* [100/sec] */
    int16 kiY;          /* [100/sec^2] */
    int16 kdY;          /* [100] */
    
    /* filtering for complementary sensor filter; roll and pitch */
    int16 lpR;          /* [] */
    int16 hpR;          /* [] */
    int16 lpP;          /* [] */
    int16 hpP;          /* [] */
    
    /* physical properties of the quadrocopter */
    int16 inertiaX;     /* [1000*N*m*sec^2] */
    int16 inertiaY;     /* [1000*N*m*sec^2] */
    int16 inertiaZ;     /* [1000*N*m*sec^2] */
    int16 lenBoom;      /* [mm] */
    
    /* maximal desireable values */
    int16 forceMax;     /* [1000*N] */
    int16 angVelYMax;   /* [(1000*rad)/sec] */
    int16 angPMax;      /* [1000*rad] */
    int16 angRMax;      /* [1000*rad] */
    
  } CopterConfig;


/* Functions ************************************************************************************************/


/*----------------------------------------------------------------------------------------------------------*/
/* copterRestoreConfig() restores the quadrocopter configuration (CopterConfig) stored in the EEPROM memory */
/*----------------------------------------------------------------------------------------------------------*/
  void copterRestoreConfig(void);

/*----------------------------------------------------------------------------------------------------------*/
/* copterSaveActualConfig() saves the actual configuration (RAM) in the EEPROM memory; present data will be */
/* overwritten                                                                                              */
/*----------------------------------------------------------------------------------------------------------*/
  void copterSaveActualConfig(void);

/*----------------------------------------------------------------------------------------------------------*/
/* copterGetConfigPtr() returns a pointer to the quadrocopter configuration (RAM)                           */
/*   return value:  a pointer to the configuration parameters                                               */
/*----------------------------------------------------------------------------------------------------------*/
  CopterConfig* copterGetConfigPtr(void);

/*----------------------------------------------------------------------------------------------------------*/
/* copterGetStatePtr() returns a pointer to the real-time image (status information) of the quadrocopter    */
/*   return value:  a pointer to the real-time image                                                        */
/*----------------------------------------------------------------------------------------------------------*/
  CopterState* copterGetStatePtr(void);
   
  CopterState* mycopterGetStatePtr(void);

/*----------------------------------------------------------------------------------------------------------*/
/* copterActualizeState() actualizes the real-time image of the quadrocopter system by evaluating all       */
/* sensors and the remote control                                                                           */
/*----------------------------------------------------------------------------------------------------------*/
  void copterActualizeState(void);

/*----------------------------------------------------------------------------------------------------------*/
/* copterSetRpms() sets the RPM setpoints for all four motors                                               */
/*----------------------------------------------------------------------------------------------------------*/
  void copterSetRpms(void);

/*----------------------------------------------------------------------------------------------------------*/
/* copterOnBoardDiagnosis() generates diagnostic and alarm signals                                          */
/*----------------------------------------------------------------------------------------------------------*/
  void copterOnBoardDiagnosis(void);


/************************************************************************************************************/


#endif