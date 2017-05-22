clear all
format long


% Parameterfile for Quadrocopter model
Ts = 0.001;
g = 9.81;

% Parameters and dimensions
% Electronics box
elec.m = 0.25;
elec.r = 63*10^-3;
elec.d = [0, 0, 19.125*10^-3];

% Battery pack + landing skids
bat.m = 0.3;
bat.l = 143.5*10^-3;
bat.w = 45.5*10^-3;
bat.h = 23*10^-3;
bat.d = [0, 0, 23.5*10^-3];

% Boom
boom.m = 0.09;
boom.l = 166*10^-3;
boom.r = 11.5*10^-3;
boom.d = [140*10^-3, 0, 17*10^-3];

% Motor
mot.m = 0.1;
mot.h = 31.5*10^-3;
mot.r = 14.2*10^-3;
mot.d = [202.5*10^-3, 0, 42*10^-3];

% Rotor
rot.m = 0.01;
rot.h = 10*10^-3;
rot.r = 127*10^-3;
rot.d = [202.5*10^-3, 0, 63*10^-3];
% Rotational moment of inertia
rot.w = rot.h;
rot.l = 2*rot.r;

% Complete mass
m = elec.m+bat.m+boom.m+mot.m+rot.m;


% Determination of inertia
% Electronics box
elec.I_x = 83/320*elec.m*elec.r^2+elec.m*elec.d(3)^2;
elec.I_y = 83/320*elec.m*elec.r^2+elec.m*elec.d(3)^2;
elec.I_z = 2/5*elec.m*elec.r^2;

% Battery pack + landing skids
bat.I_x = 1/12*bat.m*(bat.h^2+bat.l^2)+bat.m*bat.d(3)^2;
bat.I_y = 1/12*bat.m*(bat.h^2+bat.w^2)+bat.m*bat.d(3)^2;
bat.I_z = 1/12*bat.m*(bat.w^2+bat.l^2);

% Booms
boom.I_1x = 1/2*boom.m*boom.r^2+boom.m*boom.d(3)^2;
boom.I_1y = 1/16*boom.m*(4*boom.r^2+4/3*boom.l^2)+boom.m*...
                                            (boom.d(1)^2+boom.d(3)^2);
boom.I_1z = 1/16*boom.m*(4*boom.r^2+4/3*boom.l^2)+boom.m*boom.d(1)^2;
% Due to symmetry I_boom1x = I_boom2y = I_boom3x = I_boom4y!

% Motors
mot.I_1x = 1/16*mot.m*(4*mot.r^2+4/3*mot.h^2)+mot.m*mot.d(3)^2;
mot.I_1y = 1/16*mot.m*(4*mot.r^2+4/3*mot.h^2)+mot.m*...
                                            (mot.d(1)^2+mot.d(3)^2);
mot.I_1z = 1/2*mot.m*mot.r^2+mot.m*mot.d(1)^2;
% Due to symmetry I_mot1x = I_mot2y = I_mot3x = I_mot4y!

% Rotors
rot.I_1x = 1/16*rot.m*(4*rot.r^2+4/3*rot.h^2)+rot.m*rot.d(3)^2;
rot.I_1y = 1/16*rot.m*(4*rot.r^2+4/3*rot.h^2)+rot.m*...
                                            (rot.d(1)^2+rot.d(3)^2);
rot.I_1z = 1/2*rot.m*rot.r^2+rot.m*rot.d(1)^2;
% Due to symmetry I_mot1x = I_mot2y = I_mot3x = I_mot4y!
% additional rotational moment of inertia of rotors
rot.J_z = 1/12*rot.m*(rot.w^2+rot.l^2);

% Total body moment of inertia! ("2*" because of symmetry)
I_x = elec.I_x+bat.I_x+2*boom.I_1x+2*boom.I_1y+2*mot.I_1x+2*mot.I_1y+...
                            2*rot.I_1x+2*rot.I_1y;
I_y = elec.I_y+bat.I_y+2*boom.I_1x+2*boom.I_1y+2*mot.I_1x+2*mot.I_1y+...
                            2*rot.I_1x+2*rot.I_1y;
I_z = elec.I_z+bat.I_z+4*boom.I_1z+4*mot.I_1x+4*rot.I_1x;

% To save computational time, these factors are already calculated in the
% m-file.
f1 = (I_y-I_z)/I_x;
f2 = rot.J_z/I_x;
f3 = (I_z-I_x)/I_y;
f4 = rot.J_z/I_y;
f5 = (I_x-I_y)/I_z;



% Rpm - Thrust curve
rpm = [1988 2544 2940 3566 4033 4500 5033 5233];
speed = rpm.*2*pi/60;
thrust = [0.58 1 1.33 2 2.54 3.33 4.08 4.54];

disp('Parameters for quadrocopter model loaded!')