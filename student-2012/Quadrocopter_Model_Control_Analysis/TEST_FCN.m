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
function [fileName]=TEST_FCN( fileNamePrfx, fileID, x_err_stimuli, y_err_stimuli, z_err_stimuli, rate_psi_err_stimuli, opt_sensor_rec, simTime, selectOC)

% Initializations
% ===============

%Paths to the objects
Step_v_x_E_error_path = 'System_Design_Quadrocopter/Quadrocopter/Environmetal influences/Step_v_x_E_error';
Step_v_y_E_error_path = 'System_Design_Quadrocopter/Quadrocopter/Environmetal influences/Step_v_y_E_error';
Step_v_z_E_error_path = 'System_Design_Quadrocopter/Quadrocopter/Environmetal influences/Step_v_z_E_error';
Step_r_psi_E_error_path = 'System_Design_Quadrocopter/Quadrocopter/Environmetal influences/Step_r_psi_E_error';
Opt_sens_rec_path = 'System_Design_Quadrocopter/Quadrocopter/Sensors/Optical System'
To_File_path = 'System_Design_Quadrocopter/Quadrocopter/Analysis Lab/To File';
Select_OC_Path = 'System_Design_Quadrocopter/Quadrocopter/Control/Select_OC';
Simulation_path = 'System_Design_Quadrocopter';

% Backup original values
% ======================
% Params of Step Table Block
%     Time: [1x1 struct]
%     After: [1x1 struct]

filename_rec_orig=get_param(To_File_path,'File name');

Step_v_x_E_error_Time_orig=get_param(Step_v_x_E_error_path,'Time');
Step_v_x_E_error_After_orig=get_param(Step_v_x_E_error_path,'After');

Step_v_y_E_error_Time_orig=get_param(Step_v_y_E_error_path,'Time');
Step_v_y_E_error_After_orig=get_param(Step_v_y_E_error_path,'After');

Step_v_z_E_error_Time_orig=get_param(Step_v_z_E_error_path,'Time');
Step_v_z_E_error_After_orig=get_param(Step_v_z_E_error_path,'After');

Step_r_psi_E_error_Time_orig=get_param(Step_r_psi_E_error_path,'Time');
Step_r_psi_E_error_After_orig=get_param(Step_r_psi_E_error_path,'After');

Opt_sens_rec_orig=get_param(Opt_sens_rec_path,'Opt_Sens_Rec');

Select_OC_val_orig=get_param(Select_OC_Path,'value');

filename_rec=strcat(fileNamePrfx, numStrCat(fileID),'.mat');

fileName=filename_rec;
%Set file name
set_param(To_File_path,'File name',filename_rec);

%Set stimuli
set_param(Step_v_x_E_error_path, 'Time', strcat('[',num2str(x_err_stimuli(1)),']'));
set_param(Step_v_x_E_error_path, 'After', strcat('[',num2str(x_err_stimuli(2)),']'));

set_param(Step_v_y_E_error_path, 'Time', strcat('[',num2str(y_err_stimuli(1)),']'));
set_param(Step_v_y_E_error_path, 'After', strcat('[',num2str(y_err_stimuli(2)),']'));

set_param(Step_v_z_E_error_path, 'Time', strcat('[',num2str(z_err_stimuli(1)),']'));
set_param(Step_v_z_E_error_path, 'After', strcat('[',num2str(z_err_stimuli(2)),']'));

set_param(Step_r_psi_E_error_path, 'Time', strcat('[',num2str(rate_psi_err_stimuli(1)),']'));
set_param(Step_r_psi_E_error_path, 'After', strcat('[',num2str(rate_psi_err_stimuli(2)),']'));

set_param(Select_OC_Path, 'value', num2str(selectOC));

%----------------------Optical System--------------------------------------
set_param(Opt_sens_rec_path, 'Opt_Sens_Rec', strcat('[',num2str(opt_sensor_rec(1)),',',...
                                                        num2str(opt_sensor_rec(2)),',',...
                                                        num2str(opt_sensor_rec(3)),',',...
                                                        num2str(opt_sensor_rec(4)),',',...
                                                        num2str(opt_sensor_rec(5)),',',...
                                                        num2str(opt_sensor_rec(6)),',',...
                                                        num2str(opt_sensor_rec(7)),',',...
                                                        num2str(opt_sensor_rec(8)),',',...
                                                        num2str(opt_sensor_rec(9)),',',...
                                                        num2str(opt_sensor_rec(10)),']'));

%Execute Simulation
sim(Simulation_path, simTime);

%Restore parameters
set_param(Step_v_x_E_error_path,'Time', Step_v_x_E_error_Time_orig);
set_param(Step_v_x_E_error_path,'After', Step_v_x_E_error_After_orig);

set_param(Step_v_y_E_error_path,'Time', Step_v_y_E_error_Time_orig);
set_param(Step_v_y_E_error_path,'After', Step_v_y_E_error_After_orig);

set_param(Step_v_z_E_error_path,'Time', Step_v_z_E_error_Time_orig);
set_param(Step_v_z_E_error_path,'After', Step_v_z_E_error_After_orig);

set_param(Step_r_psi_E_error_path,'Time', Step_r_psi_E_error_Time_orig);
set_param(Step_r_psi_E_error_path,'After', Step_r_psi_E_error_After_orig);

set_param(To_File_path,'File name', filename_rec_orig);

set_param(Opt_sens_rec_path,'Opt_Sens_Rec', Opt_sens_rec_orig);

set_param(Select_OC_Path, 'value', Select_OC_val_orig);

end