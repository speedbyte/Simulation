
%
%param files: Vector with Strings of the files to print
%param index: The index of the files which has to been printed (y-axis)
%param tags: Vector with tags of the corresponding curves to print
%
%hold off
plotcolors ='bgcmkbgcmkbgcmk';

%--------------------------------------------------------------------------
% Test Sequence 1
% Stimuli:
%   x_vel_stimuli: [0 2 0 0.2]
%   y_vel_stimuli: [0]
%   rate_spi_stimuli: [0]
% Image Config:
%   fps: 10
%   Size: [640 480] (VGA)
%   Image: HSE_Bottom_1, HSE_Bottom_2, HSE_Aerial_3 
% Block Matching Config:
%   Block Size: [65x49], [81x61], [129x97], [215x161], [321x241]
%   Block Overlap: [0 0]
%   Max. Displaysment: [7 7]
%--------------------------------------------------------------------------
%Variation of Block Size (and Image)
%--------------------------------------------------------------------------


% % %Image: HSE_Bottom_1
% figure(1);
% files=['Rec011.mat';'Rec012.mat';'Rec013.mat';'Rec014.mat';'Rec015.mat'];
% PLOT_FILES(files(1,:),2, [1])
% hold on
% PLOT_FILES(files,14, [1,1,1,1,1])
% legend(['Stimuli   '; 'BS=65x49  ';'BS=81x61  ';'BS=129x97 ';'BS=215x161';'BS=321x241']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation BS;UND=Amorphous;FR=10 FPS;IS=640x480;ALGO=BMOF');
% hold off

%PLT SAVED: FR10_IS640x480_COOF_Var_UND_TRAN
%Image: HSE_Bottom_1
% figure(1);
% files=['Rec011.mat';'Rec021.mat';'Rec031.mat'];
% PLOT_FILES(files(1,:),4, [1])
% hold on
% PLOT_FILES(files,9, [35,35,35,35,35])
% legend(['Stimuli                ';
%         'UND=Amorphous          ';
%         'UND=Segmented Amorphous';
%         'UND=Cornered           ']);
% xlabel('Time [s]');
% ylabel('psi-velocity [rad/s]');
% title('FR=10 FPS;IS=640x480;ALGO=COOF');
% hold off

% %Image: HSE_Bottom_2
% figure(2);
% files=['Rec021.mat';'Rec022.mat';'Rec023.mat';'Rec024.mat';'Rec025.mat'];
% PLOT_FILES(files(1,:),2 , [1])
% hold on
% PLOT_FILES(files,14, [1,1,1,1,1])
% legend(['Stimuli'; '65x49  ';'81x61  ';'129x97 ';'215x161';'321x241']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation BS;UND=Segmented Amorphous;FR=10 FPS;IS=640x480;ALGO=BMOF');
% hold off
% % 
% % %Image: HSE_Aerial_3
% figure(3);
% files=['Rec031.mat';'Rec032.mat';'Rec033.mat';'Rec034.mat';'Rec035.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [1])
% PLOT_FILES(files,14, [1,1,1,1,1])
% legend(['Stimuli'; '65x49  ';'81x61  ';'129x97 ';'215x161';'321x241']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation BS;UND=Cornered;FR=10 FPS;IS=640x480;ALGO=BMOF');
% hold off

% % %Image: HSE_Aerial_3
% figure(3);
% files=['Rec011.mat';'Rec015.mat';'Rec021.mat';'Rec025.mat',;'Rec031.mat';'Rec035.mat'];
% hold on
% pl3=PLOT_FILES(files(1,:),4, [1])
% set(pl3,'Color','y')
% PLOT_FILES(files,14, [57.12,66.64,76.36,85.98,95.6,105.22])
% legend(['Stimuli                           ';
%         'UND=Amorphous BS=65x49            ';
%         'UND=Amorphous BS=321x241          ';
%         'UND=Segmented Amorphous BS=81x61  ';
%         'UND=Segmented Amorphous BS=321x241';
%         'UND=Cornered BS=81x61             ';
%         'UND=Cornered BS=321x241           ';
%       ]);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation BS;UND=Cornered;FR=10 FPS;IS=640x480;ALGO=BMOF');
% hold off
% %--------------------------------------------------------------------------
% %pause
% 
% %--------------------------------------------------------------------------
% % Test Sequence 2
% % Stimuli:
% %   x_vel_stimuli: [0 2 0 0.2]
% %   y_vel_stimuli: [0]
% %   rate_spi_stimuli: [0]
% % Image Config:
% %   fps: 10
% %   Size: [640 480] (VGA)
% %   Image: HSE_Aerial_3 
% % Block Matching Config:
% %   Block Size: [65x49], [81x61], [129x97], [215x161], [321x241]
% %   Block Overlap: [0 0]
% %   Max. Displaysment: [7 7]
% %--------------------------------------------------------------------------
% %Variation of Block Size (and Image)
% %--------------------------------------------------------------------------
% hold on
% figure(5);
% files=['Rec041.mat';'Rec042.mat';'Rec043.mat';'Rec044.mat';'Rec045.mat'];
% hold on
% pl2=PLOT_FILES(files(1,:),4, 1)
% set(pl2,'Color','k')
% PLOT_FILES(files, 14,  [55,67,57,52,40])
% legend(['Stimuli    '; 'IS=320x240 ';'IS=640x480 ';'IS=768x576 ';'IS=800x600 ';'IS=1024x768']);
% xlabel('Time [s]');
% ylabel('psi-velocity [rad/s]');
% title('Variation IS;BS=65x49;UND=Segmented Amorphous;FR=80 FPS;ALGO=BMOF');
% hold off

% hold on
% figure(6);
% files=['Rec411.mat';'Rec412.mat';'Rec413.mat';'Rec414.mat';'Rec415.mat'];
% hold on
% PLOT_FILES(files(1,:),4, 1)
% PLOT_FILES(files,14,  [125,60,60,60,50])
% legend(['Stimuli    '; 'IS=320x240 ';'IS=640x480 ';'IS=768x576 ';'IS=800x600 ';'IS=1024x768']);
% xlabel('Time [s]');
% ylabel('psi-velocity [rad/s]');
% hold off


% hold on
% figure(8);
% files=['Rec421.mat';'Rec422.mat';'Rec423.mat';'Rec424.mat';'Rec425.mat'];
% hold on
% PLOT_FILES(files(1,:),4, 1)
% PLOT_FILES(files,14,  [125,60,60,60,50])
% legend(['Stimuli    '; 'IS=320x240 ';'IS=640x480 ';'IS=768x576 ';'IS=800x600 ';'IS=1024x768']);
% xlabel('Time [s]');
% ylabel('psi-velocity [rad/s]');
% hold off

% hold on
% figure(9);
% files=['Rec431.mat';'Rec432.mat';'Rec433.mat';'Rec434.mat';'Rec435.mat'];
% hold on
% PLOT_FILES(files(1,:),4, 1)
% PLOT_FILES(files,14,  [125,70,70,70,60])
% legend(['Stimuli    '; 'IS=320x240 ';'IS=640x480 ';'IS=768x576 ';'IS=800x600 ';'IS=1024x768']);
% xlabel('Time [s]');
% ylabel('psi-velocity [rad/s]');
% hold off
% 
% hold on
% figure(7);
% files=['Rec441.mat';'Rec442.mat';'Rec443.mat';'Rec444.mat';'Rec445.mat'];
% hold on
% pl3=PLOT_FILES(files(1,:),4, 1)
% set(pl3,'Color','k')
% PLOT_FILES(files,14,  [125,100,100,100,90])
% legend(['Stimuli    '; 'IS=320x240 ';'IS=640x480 ';'IS=768x576 ';'IS=800x600 ';'IS=1024x768']);
% xlabel('Time [s]');
% ylabel('psi-velocity [rad/s]');
% title('Variation IS;BS=321x241;UND=Segmented Amorphous;FR=80 FPS;ALGO=BMOF');
% hold off
% 
hold on
figure(13);
files=['Rec041.mat';'Rec042.mat';'Rec043.mat';'Rec044.mat';'Rec045.mat'];
hold on
pl4=PLOT_FILES(files(1,:),4, 1)
set(pl4,'Color','k')
PLOT_FILES(files, 9,  [40*2.49,40*2.49,40*2.49,40*2.49,40*2.49])
legend(['Stimuli    '; 'IS=320x240 ';'IS=640x480 ';'IS=768x576 ';'IS=800x600 ';'IS=1024x768']);
xlabel('Time [s]');
ylabel('psi-velocity [rad/s]');
title('Variation IS;BS=321x241;UND=Segmented Amorphous;FR=80 FPS;ALGO=COOF');
hold off
%--------------------------------------------------------------------------
%--------------------------------------------------------------------------

% 
% hold on
% figure(7);
% files=['Rec051.mat';'Rec052.mat';'Rec053.mat';'Rec054.mat';'Rec055.mat'];
% hold on
% %PLOT_FILES(files(1,:),2, [1])
% PLOT_FILES(files,14, [0.8, 1.29, 1.7, 2.9, 6.2])
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off
% 
% hold on
% figure(8);
% files=['Rec061.mat';'Rec062.mat';'Rec063.mat';'Rec064.mat';'Rec065.mat'];
% hold on
% %PLOT_FILES(files(1,:),2, [1])
% PLOT_FILES(files,14, [0.8, 1.29, 1.7, 2.9, 6.2])
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off
% 
% 
% hold on
% figure(9);
% files=['Rec061.mat';'Rec062.mat';'Rec063.mat';'Rec064.mat';'Rec065.mat'];
% hold on
% %PLOT_FILES(files(1,:),2, [1])
% PLOT_FILES(files,14, 3*[0.8, 1.29, 1.7, 2.9, 6.2])
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off