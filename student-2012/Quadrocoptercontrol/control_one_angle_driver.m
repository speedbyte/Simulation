R1 = 5.438/132.6; % Rückkoppelfaktoren
R2 = 4.6305/132.6; % Rückkoppelfaktoren

sys = linmod('control_one_angle')
% 
% sys = 
% 
%              a: [3x3 double]
%              b: [3x1 double]
%              c: [1 0 0]
%              d: 0
%      StateName: {3x1 cell}
%     OutputName: {'test_all_temp/Out1'}
%      InputName: {'test_all_temp/In1'}
%      OperPoint: [1x1 struct]
%             Ts: 0

[num, den] = ss2tf(sys.a, sys.b, sys.c,sys.d,1)

% num =
% 
%          0    0.0000   -0.0000  132.6000
% 
% 
% den =
% 
%     1.0000    5.1282         0         0

Gs = tf(num,den)
 
% Transfer function:
% 1.066e-014 s^2 - 1.599e-014 s + 132.6
% -------------------------------------
%            s^3 + 5.128 s^2
 
step(Gs)
pole(Gs)

% ans =
% 
%          0
%          0
%    -5.1282