function PLOT_FILES(Files, index, tags, xLabel, yLabel)

% Plotting
%
%param files: Vector with Strings of the files to print
%param index: The index of the files which has to been printed (y-axis)
%param tags: Vector with tags of the corresponding curves to print
%
% Find minimum index of datapoints
% for i=1:size(Files, 1)
%     load(fileNameCollect(i,:),'Tfile');
%     Tfile=Tfile';
%     if(size(Tfile, 1) < MinDpSize)
%       MinDpSize=size(Tfile, 1);
%     end
% end
plotcolors ='bgcmkbgcmkbgcmk';
timeCollect=[];
TCollect=[];

MinDpSize=inf;
%Collect data for plotting
for i=1:size(Files, 1)
    load(Files(i,:),'Tfile');
    timeCollect=[timeCollect; Tfile(1,:)];
    TCollect=[TCollect; Tfile(index,:)];
end

% Create figure and plot data
    %figure(1);
    tagCollect=[];
for i=1:size(Files, 1)
    plot(timeCollect(i,:),TCollect(i,:),plotcolors(i));
    tagCollect=[tagCollect; Files(i,:)];
    hold on
end
legend(tagCollect);
xlabel(xLabel);
ylabel(yLabel);