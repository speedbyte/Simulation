clc
run quadrocopter_param
% States at begin of simulation
phi0      =  0.15; % rad 
r_phi0     =  0;    % rad/s
theta0    =  0.15; % rad 
r_theta0   =  0;    % rad/s
r_psi0     =  0.1;    % rad/s 


sys = dlinmod('discrete_control_angle_from_acc');

ss(sys.a, sys.b, sys.c, sys.d, Ts);

eig(sys.a)
% ans =
% 
%    1.0000          
%   -0.0050          
%   -0.0048          
%    0.9821 + 0.0960i
%    0.9821 - 0.0960i
%    0.9819 + 0.0932i
%    0.9819 - 0.0932i
%    0.9913 + 0.0000i
%    0.9913 - 0.0000i
%    0.8996          
%    0.8996          
%   -0.0055          
%    0.9778 + 0.1013i
%    0.9778 - 0.1013i
%    0.9500      
              

zgrid('new'),pzmap(ss(sys.a,sys.b,sys.c,sys.d,Ts));