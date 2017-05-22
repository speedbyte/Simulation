clc
run quadrocopter_param
% States at begin of simulation
phi0      =  0.15; % rad 
r_phi0     =  0;    % rad/s
theta0    =  0.15; % rad 
r_theta0   =  0;    % rad/s
r_psi0     =  0.1;    % rad/s 


sys = dlinmod('discrete_noise_Quantified');

ss(sys.a, sys.b, sys.c, sys.d, Ts);

eig(sys.a)

% ans =
% 
%    1.0000          
%   -0.0051          
%   -0.0048          
%    0.9820 + 0.0960i
%    0.9820 - 0.0960i
%    0.9818 + 0.0932i
%    0.9818 - 0.0932i
%    0.9912 + 0.0000i
%    0.9912 - 0.0000i
%   -0.0055          
%    0.9778 + 0.1013i
%    0.9778 - 0.1013i
%    0.9500                

zgrid('new'),pzmap(ss(sys.a,sys.b,sys.c,sys.d,Ts));