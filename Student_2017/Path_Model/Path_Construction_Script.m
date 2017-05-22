%% This demonstration script generates a timeseries in the workspace
%
X = [ 0, 1, 0,-1, 0, 1, 0, 0]; % meters
Y = [ 0, 0, 1, 0,-1, 0, 0, 0]; % meters
Z = [ 3, 3, 3, 3, 3, 3, 3, 3]; % meters
t = [ 0, 5,10,15,20,25,30, 35]; % seconds
Psi = [0,90*pi/180,0,180*pi/180,0,0,0,90*pi/180]; % radians
path.x = timeseries(X,t);
path.y = timeseries(Y,t);
path.z = timeseries(Z,t);
path.psi = timeseries(Psi,t);
clear X Y Z t Psi
uisave('path', 'Path_Diamond')
%clear path
%% This demonstration script generates a much more absurd path.
% Note that it takes a long time to run and each step is five seconds
% Random Plot
X = [0,0,-1,1,4,   1,  4,   1,4,5.5,6.25,4.75,6.25,7,7.25,8.5,9.25,10,10,12,  14, 12,  14,12,15,17, 16,15,0];% meters 28pts
X = X*0.3;
Y = [0,3, 3,3,3,2.25,1.5,0.75,0,  3, 1.5, 1.5, 1.5,0,   3,   0,  3, 0, 0, 0,0.75,1.5,2.25, 3, 3, 3,1.5, 0,0];
Y = Y*0.3;
Z = [3];

tXY = 1:10:10*length(X); % seconds

Psi = [0]; % radians
path.x = timeseries(X,tXY);
path.y = timeseries(Y,tXY);
path.z = timeseries(Z,tXY);
path.psi = timeseries(Psi,tXY);
clear X Y Z tXY Psi 
uisave('path', 'Path_Random')
%clear path