
files1=['Rec041.mat';'Rec042.mat';'Rec043.mat';'Rec044.mat';'Rec045.mat'];
files2=['Rec411.mat';'Rec412.mat';'Rec413.mat';'Rec414.mat';'Rec415.mat'];
files3=['Rec421.mat';'Rec432.mat';'Rec433.mat';'Rec434.mat';'Rec435.mat'];
files4=['Rec431.mat';'Rec432.mat';'Rec433.mat';'Rec434.mat';'Rec435.mat'];
files5=['Rec441.mat';'Rec442.mat';'Rec443.mat';'Rec444.mat';'Rec445.mat'];
files=[files1;files2;files3;files4;files5]

%figure(1);
PLOT_3D(files, 10, 5, [1,1,1,1,1],'Image Size [1=320x240]', 'Block Size [1=65x49]', 'Error')