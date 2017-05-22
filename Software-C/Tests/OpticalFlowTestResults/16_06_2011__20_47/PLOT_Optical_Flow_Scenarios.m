
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

%Image: HSE_Bottom_1
% figure(1);
% files=['Rec011.mat';'Rec012.mat';'Rec013.mat';'Rec014.mat';'Rec015.mat'];
% PLOT_FILES(files(1,:),2, [1])
% hold on
% PLOT_FILES(files,10, [1,1,1,1,1])
% legend(['Stimuli   '; 'BS=65x49  ';'BS=81x61  ';'BS=129x97 ';'BS=215x161';'BS=321x241']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation BS;UND=Amorphous;FR=10 FPS;IS=640x480;ALGO=BMOF');
% hold off
% 
% %PLT SAVED: FR10_IS640x480_COOF_Var_UND_TRAN
% % %Image: HSE_Bottom_1
% % figure(1);
% % files=['Rec011.mat';'Rec021.mat';'Rec031.mat'];
% % PLOT_FILES(files(1,:),2, [1])
% % hold on
% % PLOT_FILES(files,5, [2.3*0.918,2.3*0.918,2.3*0.918,2.3*0.918,2.3*0.918])
% % legend(['Stimuli                ';
% %         'UND=Amorphous          ';
% %         'UND=Segmented Amorphous';
% %         'UND=Cornered           ']);
% % xlabel('Time [s]');
% % ylabel('x-velocity [m/s]');
% % title('FR=10 FPS;IS=640x480;ALGO=COOF');
% % hold off
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
% title('Variation BS;UND=Segmented Amorphous;FR=10 FPS;IS=640x480;ALGO=BMOF');
% hold off
% 
% %Image: HSE_Aerial_3
% figure(3);
% files=['Rec031.mat';'Rec032.mat';'Rec033.mat';'Rec034.mat';'Rec035.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [1])
% PLOT_FILES(files,10, [1,1,1,1,1])
% legend(['Stimuli'; '65x49  ';'81x61  ';'129x97 ';'215x161';'321x241']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation BS;UND=Cornered;FR=10 FPS;IS=640x480;ALGO=BMOF');
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
% 
% files=['Rec041.mat';'Rec441.mat']%;'Rec421.mat';'Rec431.mat';'Rec441.mat'];
% hold on
% figure(12);
% PLOT_FILES(files(1,:),2, 1)
% PLOT_FILES(files,10, [1,1,1,1,1])
% legend(['Stimuli   '; 'BS=65x49  ';'BS=321x241']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation BS;IS=320x240;UND=Segmented Amorphous;FR=10 FPS;ALGO=BMOF');
% hold off
% 
% files=['Rec045.mat';'Rec445.mat']%;'Rec425.mat';'Rec435.mat';'Rec445.mat'];
% hold on
% figure(17);
% PLOT_FILES(files(1,:),2, 1)
% PLOT_FILES(files,10, [0.9,0.9,0.9,0.9,0.9])
% legend(['Stimuli   '; 'BS=65x49  '; 'BS=321x241']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation BS;IS=1024x768;UND=Segmented Amorphous;FR=10 FPS;ALGO=BMOF');
% hold off
% hold on
% figure(5);
% files=['Rec411.mat';'Rec412.mat';'Rec413.mat';'Rec414.mat';'Rec415.mat'];
% hold on
% PLOT_FILES(files(1,:),2, 1)
% PLOT_FILES(files,10, [1,1,1,1,1])
% legend(['Stimuli    ';
%         'IS=320x240 ';
%         'IS=640x480 ';
%         'IS=768x576 ';
%         'IS=800x600 ';
%         'IS=1024x768']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation IS;BS=65x49;UND=Segmented Amorphous;FR=10 FPS;ALGO=BMOF');
% hold off
% 
% hold on
% figure(6);
% files=['Rec421.mat';'Rec422.mat';'Rec423.mat';'Rec424.mat';'Rec425.mat'];
% hold on
% PLOT_FILES(files(1,:),2, 1)
% PLOT_FILES(files,10, [1,1,1,1,1])
% legend(['Stimuli    ';
%         'IS=320x240 ';
%         'IS=640x480 ';
%         'IS=768x576 ';
%         'IS=800x600 ';
%         'IS=1024x768']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation IS;BS=65x49;UND=Segmented Amorphous;FR=10 FPS;ALGO=BMOF');
% hold off
% 
% hold on
% figure(7);
% files=['Rec041.mat';'Rec412.mat';'Rec413.mat';'Rec414.mat';'Rec415.mat'];
% hold on
% PLOT_FILES(files(1,:),2, 1)
% PLOT_FILES(files,10, [1,1,1,1,1])
% legend(['Stimuli    ';
%         'IS=320x240 ';
%         'IS=640x480 ';
%         'IS=768x576 ';
%         'IS=800x600 ';
%         'IS=1024x768']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation IS;BS=65x49;UND=Segmented Amorphous;FR=10 FPS;ALGO=BMOF');
% hold off
% 
% hold on
% figure(8);
% files=['Rec441.mat';'Rec442.mat';'Rec443.mat';'Rec444.mat';'Rec445.mat'];
% hold on
% PLOT_FILES(files(1,:),2, 1)
% PLOT_FILES(files,10, [1,1,1,1,1])
% legend(['Stimuli    ';
%         'IS=320x240 ';
%         'IS=640x480 ';
%         'IS=768x576 ';
%         'IS=800x600 ';
%         'IS=1024x768']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% title('Variation IS;BS=65x49;UND=Segmented Amorphous;FR=10 FPS;ALGO=BMOF');
% hold off

% gain=1;
% figure(6);
% files=['Rec051.mat';'Rec052.mat';'Rec053.mat';'Rec054.mat';'Rec055.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [gain])
% PLOT_FILES(files,10, [0.8, 1.3, 2.0, 3.1, 6.2]*gain)
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off

% figure(7);
% files=['Rec511.mat';'Rec512.mat';'Rec513.mat';'Rec514.mat';'Rec515.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [gain])
% PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2]*gain)
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off
% 
% figure(8);
% files=['Rec521.mat';'Rec522.mat';'Rec523.mat';'Rec524.mat';'Rec525.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [gain])
% PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2]*gain)
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off
% 
% figure(9);
% files=['Rec531.mat';'Rec532.mat';'Rec533.mat';'Rec534.mat';'Rec535.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [gain])
% PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2]*gain)
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off
% 
% figure(10);
% files=['Rec541.mat';'Rec542.mat';'Rec543.mat';'Rec544.mat';'Rec545.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [gain])
% PLOT_FILES(files,10, [0.8, 1.6, 2.5, 3.6, 6.2]*gain)
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off


% figure(13);
% files=['Rec541.mat';'Rec545.mat']%;'Rec543.mat';'Rec544.mat';'Rec545.mat'];
% hold on
% plt=PLOT_FILES(files(1,:),2, [gain])
% set(plt,'Color','k')
% PLOT_FILES(files,5, [3*0.69, 3*6.92])%3*1.39, 3*2.2, 3*3.3, 3*6.92]*gain)
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off

figure(7);
files=['Rec061.mat';'Rec062.mat';'Rec063.mat';'Rec064.mat';'Rec065.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off

figure(8);
files=['Rec061.mat';'Rec062.mat';'Rec063.mat';'Rec064.mat';'Rec065.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off

figure(9);
files=['Rec611.mat';'Rec612.mat';'Rec613.mat';'Rec614.mat';'Rec615.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off

figure(10);
files=['Rec621.mat';'Rec622.mat';'Rec623.mat';'Rec624.mat';'Rec625.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off

figure(11);
files=['Rec631.mat';'Rec632.mat';'Rec633.mat';'Rec634.mat';'Rec635.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off


figure(12);
files=['Rec641.mat';'Rec642.mat';'Rec643.mat';'Rec644.mat';'Rec645.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,10, [0.8, 1.29, 1.7, 2.9, 6.2])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off

%COOF----------------------------------------------------------------------

figure(28);
files=['Rec061.mat';'Rec062.mat';'Rec063.mat';'Rec064.mat';'Rec065.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,5, [2.1,4,6.25,10.52,22.47])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off

figure(29);
files=['Rec611.mat';'Rec612.mat';'Rec613.mat';'Rec614.mat';'Rec615.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,5, [2.1,4,6.25,10.52,22.47])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off

figure(20);
files=['Rec621.mat';'Rec622.mat';'Rec623.mat';'Rec624.mat';'Rec625.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,5, [2.1,4,6.25,10.52,22.47])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off

figure(21);
files=['Rec631.mat';'Rec632.mat';'Rec633.mat';'Rec634.mat';'Rec635.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,5, [2.1,4,6.25,10.52,22.47])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off


figure(22);
files=['Rec641.mat';'Rec642.mat';'Rec643.mat';'Rec644.mat';'Rec645.mat'];
hold on
PLOT_FILES(files(1,:),2, [1])
PLOT_FILES(files,5, [2.1,4,6.25,10.52,22.47])
legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
xlabel('Time [s]');
ylabel('x-velocity [m/s]');
hold off
% 
% figure(13);
% files=['Rec641.mat';'Rec642.mat';'Rec643.mat';'Rec644.mat';'Rec645.mat'];
% hold on
% PLOT_FILES(files(1,:),2, [1])
% PLOT_FILES(files,5, [2.1,4,6.25,10.52,22.47])
% legend(['Stimuli'; '10 FPS ';'20 FPS ';'40 FPS ';'60 FPS ';'80 FPS ']);
% xlabel('Time [s]');
% ylabel('x-velocity [m/s]');
% hold off