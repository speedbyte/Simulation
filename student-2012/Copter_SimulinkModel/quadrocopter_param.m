clear all


% Parameterfile for Quadrocopter model

Ts = 0.005;      % in s
Ts_Opt = 0.01   % Optical sample rate
g = 9.81;       % in m/s^2
shift = 1000;

% Parameters for Sensor filter
LPF = 0.05;
HPF = 0.95;

% Parameters and dimensions
% Electronics box
% elec.m = 0.25;                  % in kg
elec.m = 0.178;                 % in kg (actual measured value consisting 
                                % sum of values of Base plate, Middle
                                % plate, Upper plate, Fixings, Flight
                                % control & 4*Brushless control
elec.r = 63*10^-3;              % in m
elec.d = [0, 0, 19.125*10^-3];  % in m

% Battery pack + landing skids
bat.m = 0.3;                    % in kg
bat.l = 143.5*10^-3;            % in m
bat.w = 45.5*10^-3;             % in m
bat.h = 23*10^-3;               % in m
bat.d = [0, 0, 23.5*10^-3];     % in m

% Boom
% boom.m = 0.09;                      % in kg
boom.m = 0.021;                     % in kg (actual measured value 
                                    % consisting of sum of values of Arm &
                                    % Fixing
boom.l = 166*10^-3;                 % in m
boom.r = 11.5*10^-3;                % in m
boom.d = [140*10^-3, 0, 17*10^-3];  % in m

% Motor
% mot.m = 0.1;                        % in kg
mot.m = 0.071;                      % in kg (actual measured value
                                    % consisting of sum of values of Motor
                                    % carrier & Motor
mot.h = 31.5*10^-3;                 % in m
mot.r = 14.2*10^-3;                 % in m
mot.d = [202.5*10^-3, 0, 42*10^-3]; % in m

% Rotor
% rot.m = 0.01;                       % in kg
rot.m = 0.007;                      % in kg (actual measured value
                                    % consisting of propeller weight
rot.h = 10*10^-3;                   % in m
rot.r = 127*10^-3;                  % in m
rot.d = [202.5*10^-3, 0, 63*10^-3]; % in m
% Rotational moment of inertia
rot.w = rot.h;      % in m
rot.l = 2*rot.r;    % in m

% Complete mass
m = elec.m+bat.m+boom.m+(4*mot.m)+(4*rot.m);    % in kg


% Determination of inertia
% Electronics box
elec.I_x = 83/320*elec.m*elec.r^2+elec.m*elec.d(3)^2;   % in Nms^2
elec.I_y = 83/320*elec.m*elec.r^2+elec.m*elec.d(3)^2;   % in Nms^2
elec.I_z = 2/5*elec.m*elec.r^2;                         % in Nms^2

% Battery pack + landing skids
bat.I_x = 1/12*bat.m*(bat.h^2+bat.l^2)+bat.m*bat.d(3)^2;    % in Nms^2 X und y sind vertauscht
bat.I_y = 1/12*bat.m*(bat.h^2+bat.w^2)+bat.m*bat.d(3)^2;    % in Nms^2
bat.I_z = 1/12*bat.m*(bat.w^2+bat.l^2);                     % in Nms^2

% Booms
boom.I_1x = 1/2*boom.m*boom.r^2+boom.m*boom.d(3)^2;         % in Nms^2
boom.I_1y = 1/16*boom.m*(4*boom.r^2+4/3*boom.l^2)+boom.m*...
                             (boom.d(1)^2+boom.d(3)^2);     % in Nms^2
boom.I_1z = 1/16*boom.m*(4*boom.r^2+4/3*boom.l^2)+boom.m*boom.d(1)^2;   % in Nms^2
% Due to symmetry I_boom1x = I_boom2y = I_boom3x = I_boom4y!

% Motors
mot.I_1x = 1/16*mot.m*(4*mot.r^2+4/3*mot.h^2)+mot.m*mot.d(3)^2; % in Nms^2
mot.I_1y = 1/16*mot.m*(4*mot.r^2+4/3*mot.h^2)+mot.m*...
                                 (mot.d(1)^2+mot.d(3)^2);       % in Nms^2
mot.I_1z = 1/2*mot.m*mot.r^2+mot.m*mot.d(1)^2;                  % in Nms^2
% Due to symmetry I_mot1x = I_mot2y = I_mot3x = I_mot4y!

% Rotors
rot.I_1x = 1/16*rot.m*(4*rot.r^2+4/3*rot.h^2)+rot.m*rot.d(3)^2; % in Nms^2
rot.I_1y = 1/16*rot.m*(4*rot.r^2+4/3*rot.h^2)+rot.m*...
                                 (rot.d(1)^2+rot.d(3)^2);       % in Nms^2
rot.I_1z = 1/2*rot.m*rot.r^2+rot.m*rot.d(1)^2;                  % in Nms^2
% Due to symmetry I_mot1x = I_mot2y = I_mot3x = I_mot4y!
% additional rotational moment of inertia of rotors
rot.J_z = 1/12*rot.m*(rot.w^2+rot.l^2);                         % in Nms^2

% Total body moment of inertia! ("2*" because of symmetry)
I_x = elec.I_x+bat.I_x+2*boom.I_1x+2*boom.I_1y+2*mot.I_1x+2*mot.I_1y+...
                            2*rot.I_1x+2*rot.I_1y;              % in Nms^2
I_y = elec.I_y+bat.I_y+2*boom.I_1x+2*boom.I_1y+2*mot.I_1x+2*mot.I_1y+...
                            2*rot.I_1x+2*rot.I_1y;              % in Nms^2
I_z = elec.I_z+bat.I_z+4*boom.I_1z+4*mot.I_1z+4*rot.I_1z;       % in Nms^2

% To save computational time, these factors are already calculated in the
% m-file.
f1 = (I_y-I_z)/I_x;
f2 = rot.J_z/I_x;
f3 = (I_z-I_x)/I_y;
f4 = rot.J_z/I_y;
f5 = (I_x-I_y)/I_z;



% Rpm - Thrust curve
rpm = [1988 2544 2940 3566 4033 4500 5033 5233];    % in rpm
dis_rpm = round(rpm.*shift);
speed = rpm.*(2*pi/60);                               % in rad/s
thrust = [0.58 1 1.33 2 2.54 3.33 4.08 4.54];       % in N
dis_thrust = round(thrust.*shift);

% initial States
phi0 = 0;%pi/8;
r_phi0 = 0;%pi/8;/pi/2
theta0 = 0;%pi/8;
r_theta0 = 0;
psi0 = 0;
r_psi0 = 0;

% mass correction
m= m*1.2;

disp('Parameters for quadrocopter model loaded!')