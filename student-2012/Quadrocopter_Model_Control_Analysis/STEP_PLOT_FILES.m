function STEP_PLOT_FILES(Files, index)

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
    if(size(Tfile(index,:), 2) < MinDpSize)
      MinDpSize=size(Tfile(index,:), 2);
    end    
end

for i=1:size(Files, 1)
    load(Files(i,:),'Tfile');
    timeCollect=[timeCollect; Tfile(1,1:MinDpSize)];
    TCollect=[TCollect; Tfile(index,1:MinDpSize)];
end

for i=1:size(Files, 1)
    plot(timeCollect(i,:),TCollect(i,:),plotcolors(i));
    hold on
end