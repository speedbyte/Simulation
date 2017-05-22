clc
run quadrocopter_param
% States at begin of simulation
phi0      =  0.15; % rad 
r_phi0     =  0;    % rad/s
theta0    =  0.15; % rad 
r_theta0   =  0;    % rad/s
r_psi0     =  0.01;    % rad/s 


sys = linmod('control_two_angles_and_yawrate');

ss(sys.a, sys.b, sys.c, sys.d);

eig(sys.a)

% ans =
% 
%         0          
%   -2.1222 + 9.6623i
%   -2.1222 - 9.6623i
%   -2.1213 + 9.3891i
%   -2.1213 - 9.3891i
%   -0.8839          
%   -0.8857          
%   -2.5641 +10.2128i
%   -2.5641 -10.2128i
%   -5.1282 