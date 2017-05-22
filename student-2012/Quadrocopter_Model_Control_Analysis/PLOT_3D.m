function PLOT_3D(Files, index, tags, xLabel, yLabel)

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
DeltaStimuli=[];

MinDpSize=inf;
load(Files(1,:),'Tfile');
Stimuli=Tfile(2,:);
%Collect data for plotting
for i=1:size(Files, 1)
    load(Files(i,:),'Tfile');
    timeCollect=[timeCollect; Tfile(1,:)];
    TCollect=[TCollect; Tfile(index,:)];
    DeltaStimuli=[DeltaStimuli; sum(Stimuli-Tfile(index,:))];
end

 surf(Stimuli, [1:1:size(Files,1)], DeltaStimuli);
 xlabel('Velocity [m/s]');
 ylabel('Block Size [pixel^2]');
 zlabel('Delta Velocity [m/s]');