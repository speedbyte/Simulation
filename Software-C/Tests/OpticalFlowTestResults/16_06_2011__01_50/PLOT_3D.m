function [histDataRet, XData, YData, ZData]=PLOT_3D(Files, index, filesWidth, stimuliIndex, gain, xLabel, yLabel, zLabel)

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
cnt_j=0;
idx_i=1;
idx=[0,0];
zData=zeros(5,5);
hisData=[];
load(Files(1,:),'Tfile');
Stimuli=Tfile(stimuliIndex,:);
hisData=zeros(25, size(Stimuli, 1));
%Collect data for plotting
for i=1:size(Files, 1)
     cnt_j=cnt_j+1;
     load(Files(i,:),'Tfile');
     %timeCollect=[timeCollect; Tfile(1,:)];
     %TCollect=[TCollect; Tfile(index,:)];
     zData(idx_i,cnt_j)=sum((abs((Stimuli-(gain(idx_i).*Tfile(index,:))))/Stimuli));%mean((1-abs((Stimuli-(gain(idx_i).*Tfile(index,:))))/Stimuli));%var((gain(idx_i).*Tfile(index,1:80)), Stimuli(:,1:80));%std((gain(idx_i).*Tfile(index,:)));%
     hisData=[hisData;(Stimuli-(gain(idx_i).*Tfile(index,:)))'];
     idx=[idx_i, cnt_j]
     if(filesWidth==cnt_j)
       cnt_j=0;
     end
     if(0==mod(i,filesWidth))
       idx_i=idx_i+1;
     end
end  
  surf([1:1:filesWidth], [1:1:filesWidth], zData);
  colormap(hsv);
  XData=[1:1:filesWidth];
  YData=[1:1:filesWidth];
  ZData=zData;
  xlabel(xLabel);
  ylabel(yLabel);
  zlabel(zLabel);
  histDataRet=hisData;
  xDataRet=[1:1:filesWidth];
  yDataRet=[1:1:filesWidth];
  zDataRet=zData;
  