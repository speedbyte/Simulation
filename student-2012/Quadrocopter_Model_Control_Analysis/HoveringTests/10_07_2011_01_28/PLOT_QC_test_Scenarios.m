
%
%param files: Vector with Strings of the files to print
%param index: The index of the files which has to been printed (y-axis)
%param tags: Vector with tags of the corresponding curves to print
%

files=[];
%LOAD_SYSTEM('System_Design_Quadrocopter');
hold on
% figure(2);
% files=['Rec011.mat'];
% hold on
% %PLOT_FILES(files, 5, 'Time [s]', 'x-velocity [m/s]')
% load(files(1,:),'Tfile');
% plot(Tfile(5,:), Tfile(6,:), 'r');
% hold on
% plot(Tfile(11,:), Tfile(12,:), 'g');
% hold off
 %figure('Position',[0 -50 fullscreen(3) fullscreen(4)]);
%   hold on
%   figure(2)
%   PLOT_FILES_TRAJ('Rec001.mat',11,12,10,11,12,13, 'b')
%   hold on
%   PLOT_FILES_TRAJ('Rec001.mat',5,6,10,11,12,13, 'g')
%   hold off
%   
%     hold on
%     figure(3)
%   PLOT_FILES_TRAJ('Rec002.mat',11,12,10,11,12,13, 'b')
%   hold on
%   PLOT_FILES_TRAJ('Rec002.mat',5,6,10,11,12,13, 'g')
%   hold off
% 
%     hold on
%   figure(6)
%   PLOT_FILES_TRAJ('Rec003.mat',11,12,10,11,12,13, 'b')
%   hold on
%   PLOT_FILES_TRAJ('Rec003.mat',5,6,10,11,12,13, 'g')
%   hold off
%   
%     hold on
%     figure(7)
%   PLOT_FILES_TRAJ('Rec004.mat',11,12,10,11,12,13, 'b')
%   hold on
%   PLOT_FILES_TRAJ('Rec004.mat',5,6,10,11,12,13, 'g')
%   hold off
%   
%     hold on
%     figure(9)
%   PLOT_FILES_TRAJ('Rec005.mat',11,12,10,11,12,13, 'b')
%   hold on
%   PLOT_FILES_TRAJ('Rec005.mat',5,6,10,11,12,13, 'g')
%   hold off
%   
  hold on
  figure(10)
  hold on
  PLOT_FILES_TRAJ('Rec001.mat',11,12,10,11,12,13, 'r', '.-')
  PLOT_FILES_TRAJ('Rec002.mat',11,12,10,11,12,13, 'g', '.-')
  PLOT_FILES_TRAJ('Rec003.mat',11,12,10,11,12,13, 'b', '.-')
  PLOT_FILES_TRAJ('Rec004.mat',11,12,10,11,12,13, 'c', '.-')
  PLOT_FILES_TRAJ('Rec005.mat',11,12,10,11,12,13, 'm', '.-')
  %PLOT_FILES_TRAJ('Rec005.mat',5,6,10,11,12,13, 'k')  
  hold off

    hold on
  figure(11)
  hold on
  PLOT_FILES_TRAJ('Rec011.mat',11,12,10,11,12,13, 'r', '.-')
  PLOT_FILES_TRAJ('Rec012.mat',11,12,10,11,12,13, 'g', '.-')
  PLOT_FILES_TRAJ('Rec013.mat',11,12,10,11,12,13, 'b', '.-')
  PLOT_FILES_TRAJ('Rec014.mat',11,12,10,11,12,13, 'c', '.-')
  PLOT_FILES_TRAJ('Rec015.mat',11,12,10,11,12,13, 'm', '.-')
  %PLOT_FILES_TRAJ('Rec015.mat',5,6,10,11,12,13, 'k')  
  hold off

    hold on
  figure(12)
  hold on
  PLOT_FILES_TRAJ('Rec021.mat',11,12,10,11,12,13, 'r', '.-')
  PLOT_FILES_TRAJ('Rec022.mat',11,12,10,11,12,13, 'g', '.-')
  PLOT_FILES_TRAJ('Rec023.mat',11,12,10,11,12,13, 'b', '.-')
  PLOT_FILES_TRAJ('Rec024.mat',11,12,10,11,12,13, 'c', '.-')
  PLOT_FILES_TRAJ('Rec025.mat',11,12,10,11,12,13, 'm', '.-')
  %PLOT_FILES_TRAJ('Rec025.mat',5,6,10,11,12,13, 'k')  
  hold off
  
     hold on
  figure(13)
  hold on
  PLOT_FILES_TRAJ('Rec031.mat',11,12,10,11,12,13, 'r', '.-')
  PLOT_FILES_TRAJ('Rec032.mat',11,12,10,11,12,13, 'g', '.-')
  PLOT_FILES_TRAJ('Rec033.mat',11,12,10,11,12,13, 'b', '.-')
  PLOT_FILES_TRAJ('Rec034.mat',11,12,10,11,12,13, 'c', '.-')
  PLOT_FILES_TRAJ('Rec035.mat',11,12,10,11,12,13, 'm', '.-')
   % PLOT_FILES_TRAJ('Rec035.mat',5,6,10,11,12,13, 'k')  
  hold off
  
     hold on
  figure(14)
  hold on
  PLOT_FILES_TRAJ('Rec041.mat',11,12,10,11,12,13, 'r', '.-')
  PLOT_FILES_TRAJ('Rec042.mat',11,12,10,11,12,13, 'g', '.-')
  PLOT_FILES_TRAJ('Rec043.mat',11,12,10,11,12,13, 'b', '.-')
  PLOT_FILES_TRAJ('Rec044.mat',11,12,10,11,12,13, 'c', '.-')
  PLOT_FILES_TRAJ('Rec045.mat',11,12,10,11,12,13, 'm', '.-')
  %PLOT_FILES_TRAJ('Rec045.mat',5,6,10,11,12,13, 'k')  
  hold off
  
  %-----------------------------------------------------------------------
  
  
  figure(21)
  hold on
  PLOT_FILES_TRAJ('HVS011.mat',11,12,10,11,12,13, 'r', '.-')
  PLOT_FILES_TRAJ('HVS012.mat',11,12,10,11,12,13, 'g', '.-')
  PLOT_FILES_TRAJ('HVS013.mat',11,12,10,11,12,13, 'b', '.-')
  PLOT_FILES_TRAJ('HVS014.mat',11,12,10,11,12,13, 'c', '.-')
  PLOT_FILES_TRAJ('HVS015.mat',11,12,10,11,12,13, 'm', '.-')
  %PLOT_FILES_TRAJ('HVS015.mat',5,6,10,11,12,13, 'k')  
  hold off

    hold on
  figure(22)
  hold on
  PLOT_FILES_TRAJ('HVS021.mat',11,12,10,11,12,13, 'r', '.-')
  PLOT_FILES_TRAJ('HVS022.mat',11,12,10,11,12,13, 'g', '.-')
  PLOT_FILES_TRAJ('HVS023.mat',11,12,10,11,12,13, 'b', '.-')
  PLOT_FILES_TRAJ('HVS024.mat',11,12,10,11,12,13, 'c', '.-')
  PLOT_FILES_TRAJ('HVS025.mat',11,12,10,11,12,13, 'm', '.-')
  %PLOT_FILES_TRAJ('HVS025.mat',5,6,10,11,12,13, 'k')  
  hold off
  
     hold on
  figure(23)
  hold on
  PLOT_FILES_TRAJ('HVS031.mat',11,12,10,11,12,13, 'r', '.-')
  PLOT_FILES_TRAJ('HVS032.mat',11,12,10,11,12,13, 'g', '.-')
  PLOT_FILES_TRAJ('HVS033.mat',11,12,10,11,12,13, 'b', '.-')
  PLOT_FILES_TRAJ('HVS034.mat',11,12,10,11,12,13, 'c', '.-')
  PLOT_FILES_TRAJ('HVS035.mat',11,12,10,11,12,13, 'm', '.-')
   % PLOT_FILES_TRAJ('HVS035.mat',5,6,10,11,12,13, 'k')  
  hold off
  
     hold on
  figure(24)
  hold on
  PLOT_FILES_TRAJ('HVS041.mat',11,12,10,11,12,13, 'r', '.-')
  PLOT_FILES_TRAJ('HVS042.mat',11,12,10,11,12,13, 'g', '.-')
  PLOT_FILES_TRAJ('HVS043.mat',11,12,10,11,12,13, 'b', '.-')
  PLOT_FILES_TRAJ('HVS044.mat',11,12,10,11,12,13, 'c', '.-')
  PLOT_FILES_TRAJ('HVS045.mat',11,12,10,11,12,13, 'm', '.-')
  %PLOT_FILES_TRAJ('HVS045.mat',5,6,10,11,12,13, 'k')  
  hold off