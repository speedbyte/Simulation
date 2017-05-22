
% This file tries to give an idea of how the copter behaved during the
% previous simulation
close all
fullscreen = get(0,'ScreenSize');


% Plot the position of the copter
x = xout(:,10);xmax = max(x)+0.1;xmin = min(x)-0.1;
y = xout(:,11);ymax = max(y)+0.1;ymin = min(y)-0.1;
z = xout(:,12);zmax = max(z)+0.1;zmin = min(z)-0.1;
%plot3(x,y,z,'--bo');
%grid on
%xlabel('X')
%ylabel('Y')
%zlabel('Z')

% Plot the attitude
figure('Position',[0 -50 fullscreen(3) fullscreen(4)]);
p1 = [1 0 0];
p2 = [0 1 0];
p3 = [-1 0 0];
p4 = [0 -1 0];
phi = -xout(:,1);
theta = -xout(:,2);
psi = -xout(:,3);

grid on

for i=1:100:size(tout,1)+1
    D = [cos(psi(i))*cos(theta(i)) -sin(psi(i))*cos(phi(i))+cos(psi(i))*sin(theta(i))*sin(phi(i)) sin(psi(i))*sin(phi(i))+cos(psi(i))*sin(theta(i))*cos(phi(i));
         sin(psi(i))*cos(theta(i)) cos(psi(i))*cos(phi(i))+sin(psi(i))*sin(theta(i))*sin(phi(i))  -cos(psi(i))*sin(phi(i))+sin(psi(i))*sin(theta(i))*cos(phi(i));
         -sin(theta(i))            cos(theta(i))*sin(phi(i))                                      cos(theta(i))*cos(phi(i))];
    p1_akt = p1*D;
    p2_akt = p2*D;
    p3_akt = p3*D;
    p4_akt = p4*D;
    p = [p1_akt; p2_akt; p3_akt; p4_akt];
    subplot(2,1,1)
    
    fill3([1 1 -1 -1],[-1 1 1 -1],[0 0 0 0],'k');
    alpha(0.4);
    hold on
    fill3(p(:,1),p(:,2),p(:,3),'r');
    plot3(p1_akt(1,1),p1_akt(1,2),p1_akt(1,3),'o','MarkerFaceColor','k','MarkerSize',12);
    hold off
    text(0,0,0,['t = ',num2str(tout(i)),'s'],'fontsize',10);
    text(0,0,1.3,['\Phi = ',num2str(-phi(i)*180/pi),'°'],'fontsize',10);
    text(0,0,1.1,['\Theta = ',num2str(-theta(i)*180/pi),'°'],'fontsize',10);
    text(0,0,0.9,['\Psi = ',num2str(-psi(i)*180/pi),'°'],'fontsize',10);
    axis equal
    grid on
    view(30, 20);
    axis([-1 1 -1 1 -0.5 0.5]);
    xlabel('X')
    ylabel('Y')
    zlabel('Z')
    subplot(2,1,2)
    plot3(x(1:i),y(1:i),z(1:i),'--bo');
    axis([xmin xmax ymin ymax zmin zmax]);
    grid on
    xlabel('X')
    ylabel('Y')
    zlabel('Z')
    pause(0.02);
end
