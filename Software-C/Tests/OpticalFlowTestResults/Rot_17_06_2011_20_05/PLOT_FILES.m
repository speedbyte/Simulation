function pl=PLOT_FILES(Files, index, gain)

% Plotting
%
%param files: Vector with Strings of the files to print
%param index: The index of the files which has to been printed (y-axis)
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

MinIndexDpSize=inf;
MinTimeDpSize=inf;
% for i=1:size(Files, 1)
%     load(Files(i,:),'Tfile');
%     
%     if(size(Tfile(index,:),2) < MinIndexDpSize)
%        MinIndexDpSize=size(Tfile(index,:),2)
%     end 
%    
%     if(size(Tfile(1,:),2) < MinTimeDpSize)
%        MinTimeDpSize=size(Tfile(1,:),2)
%     end 
% end
for i=1:size(Files, 1)
    load(Files(i,:),'Tfile');
    timeCollect=[timeCollect; Tfile(1,:)];
    TCollect=[TCollect; gain(i).*Tfile(index,:)];
end

% Create figure and plot data
for i=1:size(Files, 1)
    pl=plot(timeCollect(i,:),TCollect(i,:),plotcolors(i));
    hold on;
end