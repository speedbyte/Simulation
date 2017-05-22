% Analysis of the Quadrocoptermodell
% This M-File checks the controllability and observability of the
% Quadrocoptermodell
clear all;

%% initialize the workspace to use the modell
run quadrocopter_param
run quadrocopter_sim
run quadrocopter_testcases

%% generate the state-space-matrices 
%sys=linmod('Test_Copter');
sys=linmod('Test_Copter_reduced');

ss_sys=ss(sys.a,sys.b,sys.c,sys.d);

display('Reduced modell')
[msys,U] = minreal(ss(sys.a,sys.b,sys.c,sys.d));
U,msys
display('press any key'),pause()
sys=msys;

display('Ranks of the modell')
rank(obsv(ss_sys))
rank(ctrb(ss_sys))

display('Berechnung der Eigenwerte')
eing_a=eig(sys.a)

Lt = place(sys.a', sys.c', [-2 -2 -2 -3 -3 -3 -4 -4 -4 -5 -5]);

L = Lt';

Ab=[sys.a zeros(11,11); L*sys.c sys.a-L*sys.c]
Bb= [sys.b; sys.b]
Cb = eye(22,22)
Db = zeros(22, 4)

beobachter = ss(Ab, Bb, Cb, Db);

x0 = [zeros(11, 1); zeros(11, 1)];

initial(beobachter, x0)
% 
% %% Calculate eigen-values
% display('Eigen-values of the modell')
% % sys.StateName
% eig(sys.a)
% pzmap(ss(sys.a,sys.b,sys.c,sys.d));
% display('press any key'),pause()
% 
% %% Get count of all states available
% display('Count of all States available')
% size(sys.a)
% 
% %% Calculate controlability
% display('Count of controllable states')
% [ABAR,BBAR,CBAR,T,K] = ctrbf(sys.a,sys.b,sys.c);
% sum(K)
% 
% %% Calculate observability
% display('Count of observable states')
% [ABAR,BBAR,CBAR,T,K] = obsvf(sys.a,sys.b,sys.c);
% sum(K)
% display('press any key'),pause()
% 
% %% Reduce modell to controlable and observable states
% display('Statenames of full modell')
% sys.StateName
% display('full modell')
% ss(sys.a,sys.b,sys.c,sys.d)
% display('Reduced modell')
% [msys,U] = minreal(ss(sys.a,sys.b,sys.c,sys.d));
% U,msys
% display('press any key'),pause()