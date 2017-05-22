clear all;
clc;
close all;
run quadrocopter_param
System = linmod('complete_param');
StateSpace = ss(System.a, System.b, System.c, System.d);

n = order(StateSpace)                       %Ordnung des Systems
rank(ctrb(StateSpace))                      %Prüfung der Steuerbarkeit
rank(obsv(StateSpace))                      %Prüfung der Beobachtbarkeit

% step(StateSpace)
eig(System.a)
% figure
% pzmap(StateSpace);

%[K_ret,prec,message] = place(System.a, System.b, [-18 -7.01 -7 -10 -10.01]);
%[K_ret,prec,message] = place(System.a, System.b, [-40 -20 -21 -40 -41]);
%[K_ret,prec,message] = place(System.a, System.b, [-9 -3 -3.001 -5 -5.001]);
[K_ret,prec,message] = place(System.a, System.b, [-3 -1 -1.001 -2 -2.001])

% [K_ret,prec,message] = place(System.a, System.b, [-4 -1 -1.1 -2.1 -2.05])

A_CL = System.a - System.b * K_ret;
C_CL = System.c - System.d * K_ret;
Sys_ClosedLoop = ss(A_CL, System.b, C_CL, System.d);
eig(Sys_ClosedLoop)
figure
step(Sys_ClosedLoop)

KV = -(System.c * A_CL^-1 * System.b)^-1; %Orginal!!!
KV = KV' %Original!!!
% KV = -inv(System.c * inv(System.a - System.b * K_ret) * System.b)

% Reglerauslegungs test

S_CL = linmod('Controller');
SS_ClosedLoop = ss(S_CL.a, S_CL.b, S_CL.c, S_CL.d);
eig(SS_ClosedLoop)
% figure 
% step(SS_ClosedLoop)


return



% % Discretisation
% disp('discret')
% Ts = 0.01;
% SystemD = dlinmod('complete_param', Ts);
% StateSpaceD = ss(SystemD.a, SystemD.b, SystemD.c, SystemD.d);
% eig(StateSpaceD)
% K_retD = place(SystemD.a, SystemD.b, [-2 -0.25 -0.5 -1.5 -1.2])
% 
% n = order(StateSpaceD)
% rank(ctrb(StateSpaceD))                      %Prüfung der Steuerbarkeit
% rank(obsv(StateSpaceD))                      %Prüfung der Beobachtbarkeit 
