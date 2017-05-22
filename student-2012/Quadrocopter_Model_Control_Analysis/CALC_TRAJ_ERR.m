
function [ErrTrans, ErrRot]=CALC_TRAJ_ERR(file, x1Idx, y1Idx, psi1Idx, x2Idx, y2Idx, psi2Idx)

load(file,'Tfile');

x1 = Tfile(x1Idx,:);
y1 = Tfile(y1Idx,:);
psi1 = Tfile(psi1Idx,:);

x2 = Tfile(x2Idx,:);
y2 = Tfile(y2Idx,:);
psi2 = Tfile(psi2Idx,:);

x_m=mean(abs(x2-x1));
y_m=mean(abs(y2-y1));

psi_m=mean(abs(psi2-psi1));

ErrRot=psi_m;
ErrTrans=x_m+y_m;
end