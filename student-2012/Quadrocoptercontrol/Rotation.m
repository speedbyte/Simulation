function [sys,x0,str,ts] = Rotation(t,x,u,flag)
% Pendel_Animation S-Function zum visualisieren des mobilen, inversen
% Pendels
%
%   Abgeleitet von:
%   Simulink model 'aero_guidance'
%   Copyright 1990-2002 The MathWorks, Inc.
%   J.Hodgson
%   $Revision: 1.10 $  $Date: 2002/04/10 18:40:02 $

switch flag,

  %%%%%%%%%%%%%%%%%%
  % Initialization %
  %%%%%%%%%%%%%%%%%%
  case 0,
     [sys,x0,str,ts]=mdlInitializeSizes();

  %%%%%%%%%%%%%%%
  % Derivatives %
  %%%%%%%%%%%%%%%
  case {1 },
     sys=[];
     
  %%%%%%%%%%
  % Update %
  %%%%%%%%%%
  case 2,
     mdlUpdate(t,x,u)
     sys = [];
 
  %%%%%%%%%%
  % Outputs %
  %%%%%%%%%%
  case 3,
     sys = mdlOutputs(t,x,u);

  %%%%%%%%%%%%%%%%%%%%%%%
  % GetTimeOfNextVarHit %
  %%%%%%%%%%%%%%%%%%%%%%%
%   case 4,
%     sys=mdlGetTimeOfNextVarHit(t,x,u);

  %%%%%%%%%%%%%
  % Terminate %
  %%%%%%%%%%%%%
  case 9,
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
function [sys,x0,str,ts]=mdlInitializeSizes()
%
% Set Sizes Matrix
%
sizes = simsizes;

sizes.NumContStates  = 0;
sizes.NumDiscStates  = 0;
sizes.NumOutputs     = 3;
sizes.NumInputs      = 6;
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
ts  = [-1 0]; % variable sample time



%
%=============================================================================
% mdlUpdate
% Handle discrete state updates, sample time hits, and major time step
% requirements.
%=============================================================================
%
function mdlUpdate(t,x,u)
% end mdlUpdate

%
%=============================================================================
% mdlOutputs
% Return the time of the next hit for this block.  
%=============================================================================
%
function sys = mdlOutputs(t,x,u)
%
%Rotations-Matrix um Input 1 (x)
%
    cphi = cos(u(4));            
    sphi = sin(u(4));
    rot_phi = [  1   0   0; ... % Rotationsmatrix um phi(pitch)
                 0  cphi -sphi; ...
                 0  sphi cphi];
   
%
% Rotations-Matrix um Input 2 (y)
%
 
    ctheta = cos(u(5));            
    stheta = sin(u(5));
    rot_theta = [ctheta    0  stheta; ...  % Rotationsmatrix um theta(roll)
                     0     1    0   ; ...
                 -stheta   0  ctheta];
             
%
% Rotations-Matrix um Input 3 (z)
%
    cpsi = cos(u(6));            
    spsi = sin(u(6));

    rot_psi = [cpsi -spsi 0; ...  % Rotationsmatrix um psi(yaw)
                spsi  cpsi 0; ...
                  0    0   1];
    
    sys = (u(1:3)'*rot_phi*rot_theta*rot_psi)';
%
%=============================================================================
% mdlGetTimeOfNextVarHit
% Return the time of the next hit for this block.  
%=============================================================================
%
% function sys=mdlGetTimeOfNextVarHit(t,x,u,Config)
%    sys = t+Config.update;

% end mdlGetTimeOfNextVarHit


