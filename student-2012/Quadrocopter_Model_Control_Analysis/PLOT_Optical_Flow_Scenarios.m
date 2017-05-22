
%
%param files: Vector with Strings of the files to print
%param index: The index of the files which has to been printed (y-axis)
%param tags: Vector with tags of the corresponding curves to print
%
%hold off
%figure(1);
%PLOT_FILES(['Rec011.mat'], 2, ['31x31  ';'131x131';'231x231';'331x331';'431x431'], 'Time [s]', 'x-velocity [m/s]')
hold on
PLOT_FILES(files, 5, ['31x31  ';'131x131';'231x231';'331x331';'431x431'], 'Time [s]', 'x-velocity [m/s]')
hold off