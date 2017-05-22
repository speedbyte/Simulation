phi0 = 0;
r_phi0=0;
theta0 = 0;
r_theta0 = 0;
psi0 = 0;
r_psi0 = 0;

sys = dlinmod('System_Design_Quadrocopter_reduced', 0.05, [0],[0]);

[Num1, Den1] = ss2tf(sys.a, sys.b, sys.c, sys.d,1)
Gs1 = tf(Num1,Den1)
step(Gs1)
% [Num2, Den2] = ss2tf(sys.a, sys.b, sys.c, sys.d, 2)
% [Num3, Den3] = ss2tf(sys.a, sys.b, sys.c, sys.d, 3)
%[Num4, Den4] = ss2tf(sys.a, sys.b, sys.c, sys.d, 4)