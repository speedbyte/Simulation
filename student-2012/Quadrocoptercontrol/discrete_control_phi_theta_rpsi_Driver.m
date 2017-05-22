clc
run quadrocopter_param
% States at begin of simulation
phi0      =  0.15; % rad 
r_phi0     =  0;    % rad/s
theta0    =  0.15; % rad 
r_theta0   =  0;    % rad/s
r_psi0     =  0.01;    % rad/s 


sys = dlinmod('discrete_control_phi_theta_rpsi');

ss(sys.a, sys.b, sys.c, sys.d, Ts);

eig(sys.a)

% ans =
% 
%    1.0000          
%   -0.0051          
%   -0.0048          
%    0.9912          
%    0.9912          
%    0.9819 + 0.0960i
%    0.9819 - 0.0960i
%    0.9818 + 0.0933i
%    0.9818 - 0.0933i
%   -0.0055          
%    0.9500          
%    0.9778 + 0.1013i
%    0.9778 - 0.1013i

zgrid('new'),pzmap(ss(sys.a,sys.b,sys.c,sys.d,Ts));