function y = fcn(u)
%#eml
persistent e_r_Roll_1 e_Roll_1 r_Roll_I_State r_Roll_Filter_State 
persistent e_r_Pitch_1 e_Pitch_1 r_Pitch_I_State r_Pitch_Filter_State 
persistent e_r_Yaw_1 r_Yaw_I_State r_Yaw_Filter_State
persistent M1_limited M2_limited M3_limited M4_limited 
%  first time initialization
if isempty(M1_limited) 
    M1_limited=uint8(0);
    M2_limited=uint8(0);
    M3_limited=uint8(0);
    M4_limited=uint8(0);
    e_r_Roll_1 = int16(0);
    e_Roll_1 = int16(0);
    r_Roll_I_State = int16(0);
    r_Roll_Filter_State = int16(0); 
    e_r_Pitch_1 = int16(0);
    e_Pitch_1 = int16(0);
    r_Pitch_I_State = int16(0); 
    r_Pitch_Filter_State = int16(0); 
    e_r_Yaw_1 = int16(0); 
    r_Yaw_I_State = int16(0); 
    r_Yaw_Filter_State = int16(0);
end
IRoll = int16(0);
FiltRoll = int16(0);
IPitch = int16(0);
FiltPitch = int16(0);
Ts = 10; % 1000 sec
G = 9810; % 1000 m/sec²
maxPitchAngle = pi/4*1000;
maxRollAngle  = pi/4*1000;
maxYawRate = 200*1000;
sensorSensitivityX = 340;
sensorSensitivityY = 340;
sensorSensitivityZ = 340;
copterState.gyroPOffset = 505;
copterState.gyroROffset = 505;
copterState.gyroYOffset = 505;
copterState.YawRateI_State = 0;
copterState.YawRateD_Filter = 0;
copterState.PitchRateI_State = 0;
copterState.PitchRateD_Filter = 0;
copterState.RollRateI_State = 0;
copterState.RollRateD_Filter = 0;
% copy inputs to variables with easy to know names
copterState.angVelRRaw =  u(3);
copterState.accYRaw = u(2);
copterState.angVelPRaw = u(4);
copterState.accXRaw = u(1);
copterState.accZRaw = 0; %not available
copterState.angVelYRaw = u(5);
copterState.remoteForceRaw = u(9);
copterState.remotePitchRaw = u(7);
copterState.remoteRollRaw = u(6);
copterState.remoteYawRaw = u(8);
copterState.accY = int16(0);
copterState.accX = int16(0);
copterState.accZ = int16(0);
copterState.angP = int16(0);
copterState.angR = int16(0);
copterState.angVelP = int16(0);
copterState.angVelR = int16(0);
copterState.angVelY = int16(0);
copterState.remotePitch = int16(0);
copterState.remoteRoll = int16(0);
copterState.remoteForce = int16(0);
copterState.remoteYaw = int16(0);

% Convert Data like in the copter
% Accelerometer
%%%%%%%%%%%%%%%%%
  %/* calculate the physical acceleration values in [(10 * m)/(s^2)], as needed by the control algorithm */
  copterState.accY = div_fp(div_fp(mult_fp(copterState.accYRaw, G, 1000), sensorSensitivityY, 1000), 100000,1000);
  copterState.accX = div_fp(div_fp(mult_fp(copterState.accXRaw, G, 1000), sensorSensitivityX, 1000), 100000,1000);
  copterState.accZ = div_fp(div_fp(mult_fp(copterState.accZRaw, G, 1000), sensorSensitivityZ, 1000), 100000,1000);
  %copterState.accX = -int16(((int32(copterState.accXRaw) * G) / sensorSensitivityX) / 100);
  %copterState.accZ = -int16(((int32(copterState.accZRaw) * G) / sensorSensitivityZ) / 100);
  %// [ 10000*rad ]
  copterState.angP = -div_fp(copterState.accXRaw*1000,340*1000,1000);
  copterState.angR = -div_fp(copterState.accYRaw*1000,340*1000,1000);
  
  % Gyroscopes
  %%%%%%%%%%%%%%
   copterState.angVelP     = -mult_fp(div_fp(((copterState.angVelPRaw-copterState.gyroPOffset)*1000),1055000, 1000),990000,1000);
   copterState.angVelR     = -mult_fp(div_fp(((copterState.angVelRRaw-copterState.gyroROffset)*1000),1055000, 1000),990000,1000);
   copterState.angVelY     = -mult_fp(div_fp(((copterState.angVelYRaw-copterState.gyroYOffset)*1000),1055000, 1000),990000,1000);
   %copterState.angVelR     = int16((int32(copterState.angVelRRaw-copterState.gyroROffset) * 1000)/1055*990);
   %copterState.angVelY     = -int16((int32(copterState.angVelYRaw-copterState.gyroYOffset) * 1000)/1055*990);
   
   % Remote
   %%%%%%%%%%%%%
  copterState.remotePitch    = div_fp(mult_fp(maxPitchAngle,(copterState.remotePitchRaw-128)*1000,1000),128000,1000);
  copterState.remoteRoll     = div_fp(mult_fp(maxRollAngle,(copterState.remoteRollRaw-128)*1000,1000),128000,1000);
  copterState.remoteForce    = int16(copterState.remoteForceRaw); 
  copterState.remoteYaw      = div_fp(mult_fp(maxYawRate,(copterState.remoteYawRaw-128)*1000,1000),128000,1000);

% Set outputs to Values calculated last sample time
y = double([M1_limited;M2_limited;M3_limited;M4_limited]);
   
   % calculate error values for the controlled angles
   % Pitch error 
   e_Pitch = copterState.remotePitch - copterState.angP;
   % Roll error
   e_Roll = copterState.remoteRoll - copterState.angR;
   % calculate controller output for the angles (I State & FilterState are not necessary cause only p is used
   [m_Roll, IRoll, FiltRoll] = PID(200,0,0,0,e_Roll,e_Roll_1,IRoll, FiltRoll, Ts, 1000);
   [m_Pitch, IPitch, FiltPitch] = PID(200,0,0,0,e_Pitch,e_Pitch_1,IPitch,FiltPitch,Ts, 1000);
      
   % Yaw Rate error
   e_r_Yaw = copterState.remoteYaw - copterState.angVelY;
   % Pitch Rate error
   e_r_Pitch = m_Pitch - copterState.angVelP;
   % Roll Rate error
   e_r_Roll = m_Roll - copterState.angVelR;
   % calculate  controller output for rates
   [m_r_Yaw,r_Yaw_I_State, r_Yaw_Filter_State] = PID (110, ...
       500, 0,0,e_r_Yaw, e_r_Yaw_1, r_Yaw_I_State, r_Yaw_Filter_State,Ts, 100);
   [m_r_Roll,r_Roll_I_State, r_Roll_Filter_State] = PID (110, ...
       500, 0,0,e_r_Roll, e_r_Roll_1, r_Roll_I_State, r_Roll_Filter_State,Ts, 100);
   [m_r_Pitch,r_Pitch_I_State, r_Pitch_Filter_State] = PID (110, ...
       500, 0,0,e_r_Pitch, e_r_Pitch_1, r_Pitch_I_State, r_Pitch_Filter_State,Ts, 100);
   
   % save error for next sample time
   e_Roll_1 = e_Roll;
   e_Pitch_1 = e_Pitch;
   e_r_Roll_1 = e_r_Roll;
   e_r_Pitch_1 = e_r_Pitch;
   e_r_Yaw_1 = e_r_Yaw;
 
   %//Calculate new setpoints of all motors
    M1 = (copterState.remoteForce(-m_r_Pitch+m_r_Yaw)/1000);
    M2 = (copterState.remoteForce(+m_r_Roll-m_r_Yaw)/1000);
    M3 = (copterState.remoteForce(+m_r_Pitch+m_r_Yaw)/1000);
    M4 = (copterState.remoteForce(-m_r_Roll-m_r_Yaw)/1000);
    
    %// saturate setpoint of motor1 to 0 if less and 255 if above
    if M1 < 0
      M1_limited = uint8(0);
    else
        if M1 > 255
            M1_limited = uint8(255); 
        else
            M1_limited=uint8(M1);
        end
    end
    
    %// saturate setpoint of motor2 to 0 if less and 255 if above
    if M2 < 0
      M2_limited = uint8(0);
    else
        if M2 > 255
          M2_limited = uint8(255); 
        else
          M2_limited=uint8(M2);
        end
    end

    %// saturate setpoint of motor3 to 0 if less and 255 if above
  if M3 < 0
      M3_limited = uint8(0);
  else
      if M3 > 255
        M3_limited = uint8(255); 
      else
         M3_limited=uint8(M3);
      end
  end
    
    %// saturate setpoint of motor4 to 0 if less and 255 if above
    if M4 < 0
      M4_limited = uint8(0);
    else
        if M4 > 255
           M4_limited = uint8(255); 
        else
           M4_limited=uint8(M4);
        end
    end

% This function calculates the next Value of the ideal PID controller
function [ret, I_State, Filt_State] = PID (P, I, D, N, ek, ek_1, I_State, Filt_State, Ts, fp_factor)

if P ~= 0 
% calculate new itegral value
I_State = ek * Ts * I/fp_factor + I_State;

% calculate new derivative Value
yd = (ek - ek_1)/Ts * D;

% Filter the derivative  Value
Filt_State = Ts * (yd -N*Filt_State)+ Filt_State ;

% Add all values and multiply P gain to all
ret = P * (ek + I_State + Filt_State)/fp_factor;

else
    ret = 0;
end


function ret16 = mult_fp (A, B, factor)
    ret32 = int32(A) * int32(B)/factor;
    if ret32 > 2^15-1
        ret16 = int16(2^15-1);
    else
        if ret32 < -2^15+1
            ret16 = int16(-2^15+1);
        else
            ret16 = int16(ret32);
        end
    end
% end of mult_fp    

function ret16 = div_fp(A, B, factor)
if B == 0
    display('divide by ZERO !!!!')
    ret16 = 2^16-1;
else
    ret32 = int32(A)*factor/int32(B);
     if ret32 > 2^15-1
        ret16 = int16(2^15-1);
    else
        if ret32 < -2^15+1
            ret16 = int16(-2^15+1);
        else
            ret16 = int16(ret32);
        end
    end
end
% end of div_fp

