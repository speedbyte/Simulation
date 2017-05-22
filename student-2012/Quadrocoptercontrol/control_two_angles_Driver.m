clc
run quadrocopter_param
% States at begin of simulation
phi0      =  0.15; % rad 
r_phi0     =  0;    % rad/s
theta0    =  0.15; % rad 
r_theta0   =  0;    % rad/s
r_psi0     =  0.01;    % rad/s 


sys = linmod('control_two_angles');

ss(sys.a, sys.b, sys.c, sys.d);

eig(sys.a)
