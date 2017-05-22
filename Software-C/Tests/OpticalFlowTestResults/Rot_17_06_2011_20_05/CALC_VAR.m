function [vars]=CALC_VAR(Files, SigIndex, OrigIndex)

vars=[];
for i=1:size(Files, 1)
     load(Files(i,:),'Tfile');
     var_=var(Tfile(SigIndex,:), Tfile(OrigIndex,:))
     vars=[vars; var_];
end  

  