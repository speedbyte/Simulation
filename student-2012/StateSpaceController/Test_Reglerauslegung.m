clear all;
clc;
close all;
run quadrocopter_param
System = linmod('dynamics_reduced');
StateSpace = ss(System.a, System.b, System.c, System.d);
rank(ctrb(StateSpace))                      %Prüfung der Steuerbarkeit
rank(obsv(StateSpace))                      %Prüfung der Beobachtbarkeit

eig(StateSpace)                             % Eigenwerte
pzmap(StateSpace)                           % Pole Zero Map

K_ret = place(System.a, System.b, [-18 -10 -9 -5 -7]);


A_CL = System.a - System.b * K_ret;
C_CL = System.c - System.d * K_ret;
System_ClosedLoop = ss(A_CL, System.b, C_CL, System.d);
eig(System_ClosedLoop)

return

KV = -(System.c * A_CL^-1 * System.b)^-1;
KV = KV';


% Berechnung folgt!!
 KvPsi = 0.08;
 KvTheta = 0.4;
 KvPhi = 0.5;

% t_sim = 0:0.001:50;
% 
% % Psi - Theta - Phi
% simPara = ones(3, length(t_sim))*128;
% 
% System_neu = linmod('NODELAY_ReglerinclStrecke_const');
% StateSpace_neu = ss(System_neu.a, System_neu.b, System_neu.c, System_neu.d);
% [Ausgaenge, Zeit] = lsim(StateSpace_neu, simPara, t_sim);
% grid on
% hold on
% plot(Zeit, Ausgaenge);
% xlabel('time [s]');