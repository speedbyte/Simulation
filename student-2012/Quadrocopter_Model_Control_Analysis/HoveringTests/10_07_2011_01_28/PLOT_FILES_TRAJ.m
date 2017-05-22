
function PLOT_FILES_TRAJ(File, xIdx, yIdx, zIdx, phiIdx, thetaIdx, psiIdx, color, pattern)

%close all
%fullscreen = get(0,'ScreenSize');

plotcolors ='bgcmkbgcmkbgcmk';
timeCollect=[];
TCollect=[];

load(File,'Tfile');

% Plot the position of the copter
x = Tfile(xIdx,:);xmax = max(x)+0.5;xmin = min(x)-0.5;
y = Tfile(yIdx,:);ymax = max(y)+0.5;ymin = min(y)-0.5;
z = Tfile(zIdx,:);zmax = max(z)+0.5;zmin = min(z)-0.5;
xmax=10;
ymax=10;
zmax=10;
xmin=-10;
ymin=-10;
zmin=-10;
% xmax_old=xmax;
% ymax_old=ymax;
% zmax_old=zmax;
% xmin_old=xmin;
% ymin_old=ymin;
% zmin_old=zmin;

%plot3(x,y,z,'--bo');
%grid on
%xlabel('X')
%ylabel('Y')
%zlabel('Z')

% Plot the attitude
%figure('Position',[0 -50 fullscreen(3) fullscreen(4)]);
p1 = [1 0 0];
p2 = [0 1 0];
p3 = [-1 0 0];
p4 = [0 -1 0];
phi = Tfile(phiIdx, :);%-xout(:,4);
theta = Tfile(thetaIdx, :);%-xout(:,5);
psi = Tfile(psiIdx, :);%-xout(:,6);
tout=Tfile(1,:);
grid on
%for i=1:20:size(tout,2)
%     D = [cos(psi(i))*cos(theta(i)) -sin(psi(i))*cos(phi(i))+cos(psi(i))*sin(theta(i))*sin(phi(i)) sin(psi(i))*sin(phi(i))+cos(psi(i))*sin(theta(i))*cos(phi(i));
%          sin(psi(i))*cos(theta(i)) cos(psi(i))*cos(phi(i))+sin(psi(i))*sin(theta(i))*sin(phi(i))  -cos(psi(i))*sin(phi(i))+sin(psi(i))*sin(theta(i))*cos(phi(i));
%          -sin(theta(i))            cos(theta(i))*sin(phi(i))                                      cos(theta(i))*cos(phi(i))];
%     p1_akt = p1*D;
%     p2_akt = p2*D;
%     p3_akt = p3*D;
%     p4_akt = p4*D;
%     p = [p1_akt; p2_akt; p3_akt; p4_akt];
%     %subplot(2,1,1)
%     
%     fill3([1 1 -1 -1],[-1 1 1 -1],[0 0 0 0],'k');
%     alpha(0.4);
%     hold on
%     fill3(p(:,1),p(:,2),p(:,3),'r');
%     plot3(p1_akt(1,1),p1_akt(1,2),p1_akt(1,3),'o','MarkerFaceColor','k','MarkerSize',12);
%     hold off
    %text(0,0,0,['t = ',num2str(tout(i)),'s'],'fontsize',10);
    %text(0,0,1.3,['\Phi = ',num2str(-phi(i)*180/pi),'°'],'fontsize',10);
    %text(0,0,1.1,['\Theta = ',num2str(-theta(i)*180/pi),'°'],'fontsize',10);
    %text(0,0,0.9,['\Psi = ',num2str(-psi(i)*180/pi),'°'],'fontsize',10);
    %subplot(2,1,2)
    pl=plot3(x(:),y(:),z(:),pattern);
    grid on
%    pause(0.0005);
%end
    %axis([xmin xmax ymin ymax zmin zmax]);
    set(pl, 'Color', color);
    %axis equal
    %view(30, 20);
    %axis([-1 1 -1 1 -0.5 0.5]);
    grid on
    xlabel('X')
    ylabel('Y')
    zlabel('Z')
end

