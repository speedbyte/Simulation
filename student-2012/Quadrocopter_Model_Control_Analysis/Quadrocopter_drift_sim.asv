
% This File is used to simulate the Quadrocoptermodell to generate a drift,
% not seen or not correctly seen bei sensor elements.

help Quadrocopter_drift_sim

clear all, clc

run quadrocopter_param
run quadrocopter_sim
run quadrocopter_testcases

%% Setup simulation
%setup sampletime
T = [0];

% setup inputs
U1 = [5];
   
%U2_3 = [0 1 0;0 -1 0];
%   - A table of input values versus time for all
%    |                             input ports UT = [T, U1, ... Un]
%    |                             where T = [t1, ..., tm]'
%UT = [T' U1'  U2_3'];
UT = [T' U1'];

%% Simulate
sys = linmod('Quadrocopter_driftsim');
%[y, T, X] = lsim(ss(sys.a, sys.b, sys.c, sys.d), U, T, X0);
% ss(sys.a, sys.b, sys.c, sys.d)
options = simset('maxstep',0.001);
[T, X, Y] = sim('Quadrocopter_driftsim',[0,30],options, UT);
%sys.StateName

%% Show results
figure(1)
%ShowState = 11;
ShowOutput = 7;
plot(T',Y(:,ShowOutput)', T',Y(:,8)')
title(sys.OutputName(ShowOutput));
legend('Position  in Z','Stellgröße');
xlabel('time/s');
ylabel('Position z in[m]');

figure(2)
% T', Y(:,10)',
plot( T', Y(:,1)','g', T', Y(:,11)','r',T', Y(:,9)','b')
title('drift in x-direction');
%'Drift in y-direction',
legend('accel. sensor in x-direction','acceleration in x-direction','position x-direction');
xlabel('time/s');
ylabel('[m] e.g. [m/s²]');

