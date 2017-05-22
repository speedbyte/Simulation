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

% Backup original values
% ======================
step_Time_orig=get_param('System_Design_Quadrocopter/Environmetal influences/Step_v_x_E_error','Time');
step_After_orig=get_param('System_Design_Quadrocopter/Environmetal influences/Step_v_x_E_error','After');
filename_rec_orig=get_param('System_Design_Quadrocopter/Analysis Lab/To File','File name');


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