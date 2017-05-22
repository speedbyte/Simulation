fileNameCollect = [];

fileNameCollect=[fileNameCollect;'Record_ToFile(1)_.mat'];
fileNameCollect=[fileNameCollect;'Record_ToFile(6)_.mat'];

T=[];
TCollect=[];
TCollect2=[];
timeCollect=[];
first=1;
MinDpSize=inf;
for i=1:size(fileNameCollect, 1)
    load(fileNameCollect(i,:),'Tfile');
    Tfile=Tfile';
    if(size(Tfile, 1) < MinDpTime)
      MinDpSize=size(Tfile, 1);
    end
end
