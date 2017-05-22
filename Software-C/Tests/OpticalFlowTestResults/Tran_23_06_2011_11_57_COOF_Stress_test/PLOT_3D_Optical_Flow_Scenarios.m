
files1=['Rec041.mat';'Rec042.mat';'Rec043.mat';'Rec044.mat';'Rec045.mat'];
files2=['Rec411.mat';'Rec412.mat';'Rec413.mat';'Rec414.mat';'Rec415.mat'];
files3=['Rec421.mat';'Rec432.mat';'Rec433.mat';'Rec434.mat';'Rec435.mat'];
files4=['Rec431.mat';'Rec432.mat';'Rec433.mat';'Rec434.mat';'Rec435.mat'];
files5=['Rec441.mat';'Rec442.mat';'Rec443.mat';'Rec444.mat';'Rec445.mat'];
files=[files1;files2;files3;files4;files5]

hold on
figure(14);
histData1=PLOT_3D(files, 10, 5, [1,1,1,1,1],'Image Size [1=320x240]', 'Block Size [1=65x49]', 'Error')
hold on
histData2=PLOT_3D(files, 5, 5, [1,1,1,1,1],'Image Size [1=320x240]', 'Block Size [1=65x49]', 'Error')
title('BMOF vs. COOF  Image Size vs Block Size')
hold off


hold on
figure(18);
hold on
histData2=PLOT_3D(files, 5, 5, [1,1,1,1,1],'Image Size [1=320x240]', 'Block Size [1=65x49]', 'Error')
title('BMOF vs. COOF  Image Size vs Block Size')
hold off

files1=['Rec051.mat';'Rec052.mat';'Rec053.mat';'Rec054.mat';'Rec055.mat'];
files2=['Rec511.mat';'Rec512.mat';'Rec513.mat';'Rec514.mat';'Rec515.mat'];
files3=['Rec521.mat';'Rec532.mat';'Rec533.mat';'Rec534.mat';'Rec535.mat'];
files4=['Rec531.mat';'Rec532.mat';'Rec533.mat';'Rec534.mat';'Rec535.mat'];
files5=['Rec541.mat';'Rec542.mat';'Rec543.mat';'Rec544.mat';'Rec545.mat'];
files=[files1;files2;files3;files4;files5]

hold on
figure(2);
histData3=PLOT_3D(files, 10, 5, [1,1,1,1,1],'Frame Rate [1=10ms]', 'Block Size [1=65x49]', 'Error')
hold on
histData4=PLOT_3D(files, 5, 5, [1,1,1,1,1],'Frame Rate [1=10ms]', 'Block Size [1=65x49]', 'Error')
title('BMOF vs. COOF Frame Rate vs Block Size')
hold off

files1=['Rec061.mat';'Rec062.mat';'Rec063.mat';'Rec064.mat';'Rec065.mat'];
files2=['Rec611.mat';'Rec612.mat';'Rec613.mat';'Rec614.mat';'Rec615.mat'];
files3=['Rec621.mat';'Rec632.mat';'Rec633.mat';'Rec634.mat';'Rec635.mat'];
files4=['Rec631.mat';'Rec632.mat';'Rec633.mat';'Rec634.mat';'Rec635.mat'];
files5=['Rec641.mat';'Rec642.mat';'Rec643.mat';'Rec644.mat';'Rec645.mat'];
files=[files1;files2;files3;files4;files5]

hold on
figure(3);
histData5=PLOT_3D(files, 10, 5, [1,1,1,1,1],'Image Size [1=320x240]', 'Frame Rate [1=10ms]', 'Error')
hold on
histData6=PLOT_3D(files, 5, 5, [1,1,1,1,1],'Image Size [1=320x240]', 'Frame Rate [1=65x49]', 'Error')
title('BMOF vs. COOF Image Size vs Frame Rate')
hold off


hold on
figure(4);
hist(histData1)
hold off
hold on
figure(5);
hist(histData2)
hold off
hold on
figure(6);
hist(histData4)
hold off
hold on
figure(7);
hist(histData4)
hold off
hold on
figure(8);
hist(histData5)
hold off
hold on
figure(9);
hist(histData6)
hold off


