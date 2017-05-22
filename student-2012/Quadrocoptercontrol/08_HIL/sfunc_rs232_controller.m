function [sys,x0,str,ts] = Copter_Animation(t,x,u,flag,Config)
% Pendel_Animation S-Function zum visualisieren des mobilen, inversen
% Pendels
%
%   Abgeleitet von:
%   Simulink model 'aero_guidance'
%   Copyright 1990-2002 The MathWorks, Inc.
%   J.Hodgson
%   $Revision: 1.10 $  $Date: 2002/04/10 18:40:02 $
persistent s


switch flag,

  %%%%%%%%%%%%%%%%%%
  % Initialization %
  %%%%%%%%%%%%%%%%%%
  case 0,
     s = serial('COM2','BaudRate', 9600,'Timeout', 1);
     fopen(s);
     [sys,x0,str,ts]=mdlInitializeSizes(Config);
     

  %%%%%%%%%%%%%%%
  % Derivatives %
  %%%%%%%%%%%%%%%
  case {1 },
     sys=[];
     
  %%%%%%%%%%
  % Update %
  %%%%%%%%%%
  case 2,
     sys = [];

  %%%%%%%%%%%
  % Outputs %
  %%%%%%%%%%%   
  case {3 },
     sys=mdlOutputs(t,x,u,s);
  

  %%%%%%%%%%%%%%%%%%%%%%%
  % GetTimeOfNextVarHit %
  %%%%%%%%%%%%%%%%%%%%%%%
  case 4,
    sys=mdlGetTimeOfNextVarHit(t,x,u,Config);

  %%%%%%%%%%%%%
  % Terminate %
  %%%%%%%%%%%%%
  case 9,
     fclose(s);
     clear s
     sys=[];
 
otherwise
  %%%%%%%%%%%%%%%%%%%%
  % Unexpected flags %
  %%%%%%%%%%%%%%%%%%%%

   error(['Unhandled flag = ',num2str(flag)]);

end

% end Pendel_Animation
%
%=============================================================================
% mdlInitializeSizes
% Return the sizes, initial conditions, and sample times for the S-function.
%=============================================================================
%
function [sys,x0,str,ts]=mdlInitializeSizes(Config)
%
% Set Sizes Matrix
%
sizes = simsizes;

sizes.NumContStates  = 0;
sizes.NumDiscStates  = 0;
sizes.NumOutputs     = 4;
sizes.NumInputs      = 9;
sizes.DirFeedthrough = 1;
sizes.NumSampleTimes = 1;   % at least one sample time is needed

sys = simsizes(sizes);

%
% initialise the initial conditions
%
x0  = [];

%
% str is always an empty matrix
%
str = [];

%
% initialise the array of sample times
%
ts  = [0.01 0]; % variable sample time


%
%=============================================================================
% mdlUpdate
% Handle discrete state updates, sample time hits, and major time step
% requirements.
%=============================================================================
%
function mdlUpdate(t,x,u,Config)


%
%=============================================================================
% mdlOutputs
% Handle discrete state updates, sample time hits, and major time step
% requirements.
%=============================================================================
%
function sys = mdlOutputs(t,x,u,s)
i         = 0;
ID        = uint8(48); % 0x30
Length    = uint8(14); % 0x12
ax        = uint8(double2uint8(u(1)));
ay        = uint8(double2uint8(u(2)));
r_phi     = uint8(double2uint8(u(3)));
r_theta   = uint8(double2uint8(u(4)));
r_psi     = uint8(double2uint8(u(5)));
phi_set   = uint8(u(6));
theta_set = uint8(u(7));
r_psi_set = uint8(u(8));
thrust    = uint8(u(9));
sendvect = [ID; Length;ax;ay;r_phi;r_theta;r_psi;phi_set; theta_set; r_psi_set;thrust];
sendvectint8 = uint8(crc16(double(sendvect),16));


%A = myserial(5);
%s = serial('COM2','BaudRate', 9600);
%fopen(s);
pause(0.2);
while i < 3
   fwrite(s, sendvectint8, 'uint8');
   pause(0.2);
   Ret = fread(s, 8, 'uint8');
   if size(Ret) ~= (2+4+2);
      display('Timeout once')
   else
      sys = double(Ret(3:6));
      break;
   end
i= i+1;
end
if size(Ret) ~= (2+4+2)
      display(' !!!!!! --- Total timeout --- !!!!!!')
      sys = [0;0;0;0];
end
%fclose(s);

