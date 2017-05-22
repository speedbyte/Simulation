%
%param fileNamePrfx: Prefix of file
%
%param fileID: The id of file
%
%param x_err_stimuli: [Step_Time Step_After]
%
%param y_err_stimuli: [Step_Time Step_Time] 
%
%param rate_psi_err_stimuli: [Step_Time Step_Time]
%
%
%opt_sensor_rec 
%[Opt_Var_Trans Opt_Var_ST_Trans Opt_Limit_Trans Opt_Ori_SG_Trans Opt_Var_Rot Opt_Var_ST_Rot Opt_Limit_Rot Opt_Ori_SG_Rot Opt_Delay_Global Opt_ST_Global]
%       1               2               3               4              5            6               7             8             9               10
%
%
%
%
function [fileName]=STEP_TEST_FCN( fileNamePrfx, fileID, theta_stimuli, phi_stimuli, psi_stimuli, simTime)

% Initializations
% ===============

%Paths to the objects
Step_theta_path = 'System_Design_Quadrocopter/Quadrocopter/Remote Control/Step_Stimuli/Step_theta';
Step_phi_path = 'System_Design_Quadrocopter/Quadrocopter/Remote Control/Step_Stimuli/Step_phi';
Step_psi_path = 'System_Design_Quadrocopter/Quadrocopter/Remote Control/Step_Stimuli/Step_psi';
To_File_path = 'System_Design_Quadrocopter/Quadrocopter/To File';
Simulation_path = 'System_Design_Quadrocopter';

% Backup original values
% ======================
% Params of Step Table Block
%     Time: [1x1 struct]
%     After: [1x1 struct]

filename_rec_orig=get_param(To_File_path,'File name');

Step_theta_Time_orig=get_param(Step_theta_path,'Time');
Step_theta_After_orig=get_param(Step_theta_path,'After');

Step_phi_Time_orig=get_param(Step_phi_path,'Time');
Step_phi_After_orig=get_param(Step_phi_path,'After');

Step_psi_Time_orig=get_param(Step_psi_path,'Time');
Step_psi_After_orig=get_param(Step_psi_path,'After');

filename_rec=strcat(fileNamePrfx, numStrCat(fileID),'.mat');

fileName=filename_rec;
%Set file name
set_param(To_File_path,'File name',filename_rec);

%Set stimuli
set_param(Step_theta_path, 'Time', strcat('[',num2str(theta_stimuli(1)),']'));
set_param(Step_theta_path, 'After', strcat('[',num2str(theta_stimuli(2)),']'));

set_param(Step_phi_path, 'Time', strcat('[',num2str(phi_stimuli(1)),']'));
set_param(Step_phi_path, 'After', strcat('[',num2str(phi_stimuli(2)),']'));

set_param(Step_psi_path, 'Time', strcat('[',num2str(psi_stimuli(1)),']'));
set_param(Step_psi_path, 'After', strcat('[',num2str(psi_stimuli(2)),']'));
%----------------------Optical System--------------------------------------

%Execute Simulation
sim(Simulation_path, simTime);

%Restore parameters
set_param(Step_theta_path,'Time', Step_theta_Time_orig);
set_param(Step_theta_path,'After', Step_theta_After_orig);

set_param(Step_phi_path,'Time', Step_phi_Time_orig);
set_param(Step_phi_path,'After', Step_phi_After_orig);

set_param(Step_psi_path,'Time', Step_psi_Time_orig);
set_param(Step_psi_path,'After', Step_psi_After_orig);

set_param(To_File_path,'File name', filename_rec_orig);
end