clear all;
close all;
clc;
delete Record_*_.mat;
%pause
open_system('Record')

% Initializations
% ===============
tagCollect =[];
timeCollect =[];
TCollect =[];
plotcolors ='bgcmkbgcmkbgcmk';
nvals = 0;

% Backup original values
% ======================
gval_orig=get_param('Record/Gain','Gain');
filename_rec_orig=get_param('Record/To File','File name');

% Calculations
% ============
for gval=0.2:0.2:1.0
    nvals = nvals + 1;
    gvalStr = num2str(gval,3);
    
    % --> Record with To File
	filename_rec=strcat('Record_ToFile(',gvalStr,')_.mat');
	set_param('Record/To File','File name',filename_rec);
    
    % --> Record with To Workspace
	set_param('Record/Gain','Gain',gvalStr);
    sim('Record');
    save(strcat('Record_T(',gvalStr,')_.mat'),'T');
    
    timeCollect = [timeCollect, time];
    TCollect = [TCollect, T];
    tag = ['Gain = ',gvalStr];
    tagCollect = [tagCollect,{tag}];
end

% --> Record whole collection
save('Record_TCollect_.mat','TCollect');

% Restore original values
% ======================
set_param('Record/Gain','Gain',gval_orig);
set_param('Record/To File','File name',filename_rec_orig);


% Plotting
% ========
hold off
for i=1:nvals
    plot(timeCollect(:,i),TCollect(:,i),plotcolors(i));
    hold on
end
hold off
legend(tagCollect);
xlabel('Time (mins)');
ylabel('Temperature (^oF)');