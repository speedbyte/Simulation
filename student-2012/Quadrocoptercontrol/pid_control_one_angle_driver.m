R1 = 5.438/132.6; % Rückkoppelfaktoren
R2 = 4.6305/132.6; % Rückkoppelfaktoren

sys = linmod('pid_control_one_angle')
sys_open = linmod('pid_control_one_angle_open')

[num1, den1] = ss2tf(sys.a, sys.b, sys.c,sys.d,1)
Gs1 = tf(num1,den1)

[num2, den2] = ss2tf(sys_open.a, sys_open.b, sys_open.c,sys_open.d,1)
Gs2 = tf(num2,den2)
 

figure(1)
hold on;
step(Gs1,'g',Gs2,'r', 1)
legend('PID-Cascade', 'No PID-Cascade');
hold off;

P1=pole(Gs1)
P2=pole(Gs2)

figure(3)

hold on;
%plot(real(P1(3)), imag(P1(3)), 'bo')
plot(real(P1(4)), imag(P1(4)), 'go', 'MarkerSize',15)
plot(real(P2(4)), imag(P2(4)), 'rx', 'MarkerSize',15)
legend('PID-Cascade', 'No PID-Cascade');
title('Pole Map')
plot(real(P1(5)), imag(P1(5)), 'go', 'MarkerSize',15)
plot(real(P1(6)), imag(P1(6)), 'go', 'MarkerSize',15)

%plot(real(P2(3)), imag(P2(3)), 'rx')
plot(real(P2(5)), imag(P2(5)), 'rx', 'MarkerSize',15)
plot(real(P2(6)), imag(P2(6)), 'rx', 'MarkerSize',15)
xlabel('Re')
ylabel('Im')
plot(0, linspace(-30,30), 'b--')
%legend('No Feedback')
hold off;


figure(4)
hold on;
bode(Gs1, 'g', Gs2, 'r')
legend('PID-Cascade', 'No PID-Cascade');
hold off;