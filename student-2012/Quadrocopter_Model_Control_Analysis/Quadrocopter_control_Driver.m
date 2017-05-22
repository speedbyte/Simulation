% This M-File is a driver to start the simulation of Quadrocopter_control
clc
clear all
addpath ..\Analyse_Quadrocopter_modell
%% Parameter
run 'quadrocopter_param'

theta_filt_old = double(0); % last angle phi filtered
phi_filt_old   = double(0);   % last angle theta filtered
phi_filt       = double(0);
theta_filt     = double(0);

%setup sampletime
T = [0];

% setup inputs
U1 = [0];
U2 = [0];
U3 = [0];
U4 = [0];%[90.2];
   
%U2_3 = [0 1 0;0 -1 0];
%   - A table of input values versus time for all
%    |                             input ports UT = [T, U1, ... Un]
%    |                             where T = [t1, ..., tm]'
%UT = [T' U1'  U2_3'];
UT = [T' U1' U2' U3' U4' ];


% States at begin of simulation
phi0      =  0.15; % rad 
r_phi0     =  0;    % rad/s
theta0    =  0.15; % rad 
r_theta0   =  0;    % rad/s
r_psi0     =  0;    % rad 

%% run Simulation
sim('Quadrocopter_control', [0 10], simset(),UT  );   %[phi(roll), theta(pitch),rpsi(yaw rate), T(thrust)]


rmpath ..\Analyse_Quadrocopter_modell
