% Analysis of the Quadrocoptermodel
% This M-File checks the controllability and observability of the
% Quadrocoptermodel
clear all; clc

%% initialize the workspace to use the modell
run quadrocopter_param
% run quadrocopter_sim
% run quadrocopter_testcases

%% generate the state-space-matrices 
sys=linmod('Test_Copter');
%sys=linmod('Test_Copter_reduced');

%% Calculate eigen-values
display('Eigen-values of the model')
% sys.StateName
eig(sys.a)
StateSys = ss(sys.a,sys.b,sys.c,sys.d);
% pzmap(StateSys);

%% Get count of all states available
display('Count of all States available')
size(sys.a)

%% Calculate controlability
display('Count of controllable states')
rank(ctrb(StateSys))

%% Calculate controlability
display('Count of controllable states')
[ABAR,BBAR,CBAR,T,K] = ctrbf(sys.a,sys.b,sys.c);
sum(K)

%% Calculate observability
display('Count of observable states')
rank(obsv(StateSys))

%% Reduce model to controlable and observable states
display('Statenames of full model')
sys.StateName
% display('full model')
% StateSys
% display('Reduced model')
msys = sminreal(StateSys);
% msys

%% Get count of all states available
display('Count of all reduced States available')
size(msys.a)
display('Statenames of reduced model')
msys.statename