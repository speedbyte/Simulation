% This m-file will simulate the control and model for a given testcase.

% Load parameters of the model
quadrocopter_param;

% Choose the correct testcase
% ------------------------------------------------------
% Possible values 1: Height
%                 2: Roll angle        
%                 3: Step Roll angle
%                 4: Step Pitch angle
%                 5: Step Yaw velocity
%                 6: Everything
% ------------------------------------------------------
testcase = 5;
quadrocopter_testcases;


% Start the Simulation
% simout = sim('Copter_System','StopTime',num2str(desheight.time(end)),...
%              'SaveState','on','StateSaveName','xout','SaveFormat','array',...
%              'LimitDataPoints','off');,
tend = desheight.time(end);
%sim('Copter_System');

% Analysis of testcase
%quadrocopter_analysis;