clear all;
clc;
close all;
System = linmod('simpleprocess_control_step');
StateSpace = ss(System.a, System.b, System.c, System.d);
rank(ctrb(StateSpace))                      %Pr�fung der Steuerbarkeit
rank(obsv(StateSpace))                      %Pr�fung der Beobachtbarkeit

% step(StateSpace)
eig(StateSpace)
% figure
% pzmap(StateSpace);
% ORIG [-10 -9 -8 -7 -6 -0.5 -0.6 -0.7 -0.8 -0.9]
K_ret = place(System.a, System.b, [-2 -4 -3]);

A_CL = System.a - System.b * K_ret;
C_CL = System.c - System.d * K_ret;
Sys_CL = ss(A_CL, System.b, C_CL, System.d);
eig(Sys_CL)

KV = -(System.c * A_CL^-1 * System.b)^-1;
KV = KV';
Kv = 1;
Kr1 = K_ret(2);
Kr2 = K_ret(3);
Kr3 = K_ret(1);

System_CL = linmod('simpleprocess_controller_step');
StateSpace_CL = ss(System_CL.a, System_CL.b, System_CL.c, System_CL.d);

eig(StateSpace_CL)
% process
step(StateSpace)

figure
% c_L without Kv
step(StateSpace_CL)

figure
% c_L with Kv
Kv = 24;
System_CL = linmod('simpleprocess_controller_step');
StateSpace_CL = ss(System_CL.a, System_CL.b, System_CL.c, System_CL.d);
step(StateSpace_CL)
