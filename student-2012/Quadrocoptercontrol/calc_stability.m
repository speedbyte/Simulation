phi0 = 0;
r_phi0=0;
theta0 = 0;
r_theta0 = 0;
psi0 = 0;
r_psi0 = 0;


sys = dlinmod('Quadrocopter_control');

 eig(sys.a)
%Gs = tf(1,[-1 1/0.2 1])

%pole(Gs)

% for i = 1:4 
% [Num, Den] = ss2tf(sys.a, sys.b, sys.c, sys.d, i);
% g_phi_m1 = tf(Num(1,:), Den)
% end
