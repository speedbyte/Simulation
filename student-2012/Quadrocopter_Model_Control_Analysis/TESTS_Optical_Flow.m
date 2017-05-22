clear all;
close all;
clc;
delete Record_*_.mat;
run quadrocopter_param

% Initializations
% ===============
tagCollect =[];
timeCollect =[];
TCollect =[];
plotcolors ='bgcmkbgcmkbgcmk';
nvals = 0;

%Paths to the objects
x_vel_stimuli_path = 'Optical_Movement_Detection/x_vel_stimuli';
y_vel_stimuli_path = 'Optical_Movement_Detection/y_vel_stimuli';
rate_spi_stimuli_path = 'Optical_Movement_Detection/rate_psi_stimuli';
To_File_path='Optical_Movement_Detection/To File';

% Backup original values
% ======================
% Params of Repeating Table Block
%     rep_seq_t: [1x1 struct]
%     rep_seq_y: [1x1 struct]

x_vel_stimuli_orig=get_param(x_vel_stimuli_path,'rep_seq_t');
x_vel_stimuli_orig=[x_vel_stimuli_orig get_param(x_vel_stimuli_path,'rep_seq_y')];
%x_vel_stimuli_orig format => [rep_seq_t rep_seq_y]

y_vel_stimuli_orig=get_param(y_vel_stimuli_path,'rep_seq_t');
y_vel_stimuli_orig=[y_vel_stimuli_orig getget_param(y_vel_stimuli_path,'rep_seq_y')];
%y_vel_stimuli_orig format => [rep_seq_t rep_seq_y]


rate_spi_stimuli_orig=get_param(rate_spi_stimuli_path,'rep_seq_t');
rate_spi_stimuli_orig=[rate_spi_stimuli_orig get_param(rate_spi_stimuli_path,'rep_seq_y')];
%rate_spi_stimuli_orig format => [rep_seq_t rep_seq_y]

filename_rec_orig=get_param(To_File_path,'File name');

%--------------------------------------------------------------------------
% Test Environment 1
% Stimuli:
%   x_vel_stimuli: 0..10
%   y_vel_stimuli: 0
%   rate_spi_stimuli: 0
% Image Config:
%   fps: 100
%   Size: [500 500]
% Block Matching Config:
%   Block Size: [131 131]
%   Block Overlap: [0 0]
%   Max. Displaysment: [7 7]
%--------------------------------------------------------------------------
fileNameCollect=[];
% Calculations
% ============
for i=0:2:10
    iStr = num2str(i,3);
    
    if(i < 10)
        iStr = strcat('00',iStr);
    elseif(i < 100)
        iStr = strcat('0',iStr);
    end
    
    % --> Record with To File
	filename_rec=strcat('Record_ToFile(',iStr,')_.mat');
    fileNameCollect=[fileNameCollect;filename_rec];
	set_param('System_Design_Quadrocopter/To File','File name',filename_rec);
    set_param('System_Design_Quadrocopter/Dynamics/Step_v_x_E_error','After',iStr);
    set_param('System_Design_Quadrocopter/Dynamics/Step_v_y_E_error','After',iStr);
    
    % --> Record with To Workspace
	sim('System_Design_Quadrocopter');
     
%   timeCollect = [timeCollect, tout];
    tag = ['Gain = ',iStr];
    tagCollect = [tagCollect,{tag}];
end

% Restore original values
% ======================
set_param('System_Design_Quadrocopter/Dynamics/Step_v_x_E_error','After',step_After_orig);
set_param('System_Design_Quadrocopter/Dynamics/Step_v_x_E_error','Time',step_Time_orig);
set_param('System_Design_Quadrocopter/To File','File name',filename_rec_orig);

% Plotting
% ========
hold off
TCollect=[];
TCollect2=[];
timeCollect=[];
MinDpSize=inf;
% Find minimum index of datapoints
for i=1:size(fileNameCollect, 1)
    load(fileNameCollect(i,:),'Tfile');
    Tfile=Tfile';
    if(size(Tfile, 1) < MinDpSize)
      MinDpSize=size(Tfile, 1);
    end
end
%Collect data for plotting
for i=1:size(fileNameCollect, 1)
    load(fileNameCollect(i,:),'Tfile');
    Tfile=Tfile';
    timeCollect=[timeCollect, Tfile(1:MinDpSize,1)];
    TCollect=[TCollect, Tfile(1:MinDpSize,2)];
end

% Create figure and plot data
    figure(2);
for i=1:size(fileNameCollect, 1)
    plot(timeCollect(:,1),TCollect(:,i),plotcolors(i));
    hold on
end
hold off
legend(tagCollect);
xlabel('Time (secs)');
ylabel('Temperature (^oF)');