
% %
% %param files: Vector with Strings of the files to print
% %param index: The index of the files which has to been printed (y-axis)
% %param tags: Vector with tags of the corresponding curves to print
% %
% %hold off
% plotcolors ='bgcmkbgcmkbgcmk';
% 
% %--------------------------------------------------------------------------
% % Test Sequence 1
% % Stimuli:
% %   x_vel_stimuli: [0 2 0 0.2]
% %   y_vel_stimuli: [0]
% %   rate_spi_stimuli: [0]
% % Image Config:
% %   fps: 10
% %   Size: [640 480] (VGA)
% %   Image: HSE_Bottom_1, HSE_Bottom_2, HSE_Aerial_3 
% % Block Matching Config:
% %   Block Size: [65x49], [81x61], [129x97], [215x161], [321x241]
% %   Block Overlap: [0 0]
% %   Max. Displaysment: [7 7]
% %--------------------------------------------------------------------------
% %Variation of Block Size (and Image)
% %--------------------------------------------------------------------------
% 
% %Image: HSE_Bottom_1
% figure(1);
% files=['Rec011.mat';'Rec012.mat';'Rec013.mat';'Rec014.mat';'Rec015.mat'];
% PLOT_FILES(files(1,:),2, [1])
% hold on
% PLOT_FILES(files,10, [1,1,1,1,1])
% legend(['Stimuli'; '65x49  ';'81x61  ';'129x97 ';'215x161';'321x241']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off
% 
% pause
% 
% %Image: HSE_Bottom_2
% figure(2);
% files=['Rec021.mat';'Rec022.mat';'Rec023.mat';'Rec024.mat';'Rec025.mat'];
% PLOT_FILES(files(1,:),2 , [1])
% hold on
% PLOT_FILES(files,10, [1,1,1,1,1])
% legend(['Stimuli'; '65x49  ';'81x61  ';'129x97 ';'215x161';'321x241']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off
% 
% pause
% %Image: HSE_Aerial_3
% figure(3);
% files=['Rec031.mat';'Rec032.mat';'Rec033.mat';'Rec034.mat';'Rec035.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [1])
% PLOT_FILES(files,10, [1,1,1,1,1])
% legend(['Stimuli'; '65x49  ';'81x61  ';'129x97 ';'215x161';'321x241']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off
%--------------------------------------------------------------------------
%pause

%--------------------------------------------------------------------------
% Test Sequence 2
% Stimuli:
%   x_vel_stimuli: [0 2 0 0.2]
%   y_vel_stimuli: [0]
%   rate_spi_stimuli: [0]
% Image Config:
%   fps: 10
%   Size: [640 480] (VGA)
%   Image: HSE_Aerial_3 
% Block Matching Config:
%   Block Size: [65x49], [81x61], [129x97], [215x161], [321x241]
%   Block Overlap: [0 0]
%   Max. Displaysment: [7 7]
%--------------------------------------------------------------------------
%Variation of Block Size (and Image)
%--------------------------------------------------------------------------
figure(4);
files=['Rec041.mat';'Rec042.mat';'Rec043.mat';'Rec044.mat';'Rec045.mat'];
hold on
PLOT_FILES(files(1,:),2, 1)
PLOT_FILES(files,5, [1,1,1,1,1])
legend(['Stimuli '; '320x240 ';'640x480 ';'768x576 ';'800x600 ';'1024x768']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off

pause

figure(5);
files=['Rec411.mat';'Rec412.mat';'Rec413.mat';'Rec414.mat';'Rec415.mat'];
hold on
PLOT_FILES(files(1,:),2, 1)
PLOT_FILES(files,5, [2.6,2.6,2.6,2.6,2.6])
legend(['Stimuli '; '320x240 ';'640x480 ';'768x576 ';'800x600 ';'1024x768']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off

% pause
% 
% figure(6);
% files=['Rec051.mat';'Rec052.mat';'Rec053.mat';'Rec054.mat';'Rec055.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [1])
% PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2])
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off
% 
% pause
% 
% figure(7);
% files=['Rec061.mat';'Rec062.mat';'Rec063.mat';'Rec064.mat';'Rec065.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [1])
% PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2])
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off
% 
% pause
% 
% figure(8);
% files=['Rec061.mat';'Rec062.mat';'Rec063.mat';'Rec064.mat';'Rec065.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [1])
% PLOT_FILES(files,5, 3*[0.8, 1.29, 1.7, 2.9, 6.2])
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off