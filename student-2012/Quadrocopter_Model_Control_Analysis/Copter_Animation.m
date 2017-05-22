function [sys,x0,str,ts] = Copter_Animation(t,x,u,flag,Config)
% Pendel_Animation S-Function zum visualisieren des mobilen, inversen
% Pendels
%
%   Abgeleitet von:
%   Simulink model 'aero_guidance'
%   Copyright 1990-2002 The MathWorks, Inc.
%   J.Hodgson
%   $Revision: 1.10 $  $Date: 2002/04/10 18:40:02 $

switch flag,

  %%%%%%%%%%%%%%%%%%
  % Initialization %
  %%%%%%%%%%%%%%%%%%
  case 0,
     [sys,x0,str,ts]=mdlInitializeSizes(Config);

  %%%%%%%%%%%%%%%
  % Derivatives %
  %%%%%%%%%%%%%%%
  case {1 , 3},
     sys=[];
     
  %%%%%%%%%%
  % Update %
  %%%%%%%%%%
  case 2,
     sys = [];
     if Config.Animenable
        mdlUpdate(t,x,u,Config);
     end

  %%%%%%%%%%%%%%%%%%%%%%%
  % GetTimeOfNextVarHit %
  %%%%%%%%%%%%%%%%%%%%%%%
  case 4,
    sys=mdlGetTimeOfNextVarHit(t,x,u,Config);

  %%%%%%%%%%%%%
  % Terminate %
  %%%%%%%%%%%%%
  case 9,
     sys=[];
     if Config.Animenable
       h_f= get(findobj('type','figure','Tag','3DOF anim'),'children');
       h=findobj(h_f,'type','uimenu','label','&Camera');
       if (isempty(h) & ~isempty(h_f))  
         cameramenu('noreset')
       end
     end  
otherwise
  %%%%%%%%%%%%%%%%%%%%
  % Unexpected flags %
  %%%%%%%%%%%%%%%%%%%%

   error(['Unhandled flag = ',num2str(flag)]);

end

% end Pendel_Animation
%
%=============================================================================
% mdlInitializeSizes
% Return the sizes, initial conditions, and sample times for the S-function.
%=============================================================================
%
function [sys,x0,str,ts]=mdlInitializeSizes(Config)
%
% Set Sizes Matrix
%
sizes = simsizes;

sizes.NumContStates  = 0;
sizes.NumDiscStates  = 0;
sizes.NumOutputs     = 0;
sizes.NumInputs      = 6;
sizes.DirFeedthrough = 0;
sizes.NumSampleTimes = 1;   % at least one sample time is needed

sys = simsizes(sizes);

%
% initialise the initial conditions
%
x0  = [];

%
% str is always an empty matrix
%
str = [];

%
% initialise the array of sample times
%
ts  = [-2 0]; % variable sample time

if ~Config.Animenable
   return
end

%
% Initialisiere Fenster
%

   h_f=findobj('type','figure','Tag','3DOF anim');
   
   if isempty(h_f)
     h_anim=figure;
   else
     h_anim=h_f;
   end

   opengl hardware;
   
   set(h_anim,'name','Animation Figure', ...
           'renderer','OpenGL','resize','off', ...
           'position',[500, 200, 525, 450], ...
           'Tag','3DOF anim');
   
   if ~isempty(h_anim)
     h_del = findobj(h_anim,'type','axes');
     delete(h_del);
     figure(h_anim);
   end

%
% Initialisiere Achsen
%
   handle.axes(1)=axes;
   axis(Config.axes);
   set(handle.axes(1),'visible','on','xtick',[],'ytick',[],'ztick', [],'box','off', ...
           'dataaspectratio',[1 1 1], ...
           'projection','pers', ...
           'units','normal', ...
           'position',[0.1 0.1 0.75 0.75], ...
           'Color',[.8 .8 .8], ...
           'drawmode','fast', ...
           'XGrid', 'off',...
           'YGrid', 'off',...
           'ZGrid', 'off'); ...

%
% Zeichne den Boden
%
 
   
%
% Zeichne Copter in Copter Benutzerdaten
%      
%Parameter
D = 1; %Druchmesser
H = 0.1; % Höhe
R = 0.05; % Radius des Körpers
RP = 0.35; % Radius eines Propellers

   [xcraft,ycraft,zcraft]=craft(Config, H, D, R);
   handle.craft = patch(xcraft,ycraft,zcraft,[1 0 0]);
   set(handle.craft,'userdata',get(handle.craft,'vertices'))
   set(handle.craft,'facecolor',[.25 .25 .25], ...
                    'edgecolor',[0 0 0], ...
                    'erasemode','nor','clipping','off');
                
 
         
[xprop,yprop,zprop]=props(Config, H, RP);

%
% Zeichne Propeller 1
%      
   
   handle.prop1 = patch(xprop+D/2,yprop,zprop,[0 1 0]);
   set(handle.prop1,'userdata',get(handle.prop1,'vertices'))
   set(handle.prop1,'facecolor',[1 0 0], ...
                    'edgecolor',[1 0 0], ...
                    'erasemode','nor','clipping','off');
                
%
% Zeichne Propeller 2
%      
   
   handle.prop2 = patch(xprop,yprop+D/2,zprop,[0 1 0]);
   set(handle.prop2,'userdata',get(handle.prop2,'vertices'))
   set(handle.prop2,'facecolor',[0 0 1], ...
                    'edgecolor',[0 0 1], ...
                    'erasemode','nor','clipping','off');
                
                %
% Zeichne Propeller 3
%      
   
   handle.prop3 = patch(xprop-D/2,yprop,zprop,[0 1 0]);
   set(handle.prop3,'userdata',get(handle.prop3,'vertices'))
   set(handle.prop3,'facecolor',[0 0 1], ...
                    'edgecolor',[0 0 1], ...
                    'erasemode','nor','clipping','off');
                
                %
% Zeichne Propeller 4
%      
   
   handle.prop4 = patch(xprop,yprop-D/2,zprop,[0 1 0]);
   set(handle.prop4,'userdata',get(handle.prop4,'vertices'))
   set(handle.prop4,'facecolor',[0 0 1], ...
                    'edgecolor',[0 0 1], ...
                    'erasemode','nor','clipping','off');
                

%
% Set Handles of graphics in Figure UserData
%   
   set(h_anim,'userdata',handle);

%
%=============================================================================
% mdlUpdate
% Handle discrete state updates, sample time hits, and major time step
% requirements.
%=============================================================================
%
function mdlUpdate(t,x,u,Config)

%
% Handle der Fensterobjekte erhalten
%
    handle = get(findobj('type','figure','Tag','3DOF anim'),'userdata');

    if isempty(findobj('type','figure','Tag','3DOF anim'))
     %figure has been manually closed
     return
    end

%
% Aktualisiere das Copter-Object 
% 
% Lade Vertexinformation Pendelkörper
   craft  = get(handle.craft,'userdata');
   prop1  = get(handle.prop1,'userdata');
   prop2  = get(handle.prop2,'userdata');
   prop3  = get(handle.prop3,'userdata');
   prop4  = get(handle.prop4,'userdata');

% %
% % Rotations-Matrix um phi (pitch)
% %
%     if(Config.phi)
% 
%     cphi = cos(u(4));            
%     sphi = sin(u(4));
%     rot_phi = [cphi 0 sphi; ...  % Rotationsmatrix um phi(pitch)
%                 0   1   0; ...
%                -sphi 0  cphi];
%            
%    
% % apply on craft
%    craft = (rot_phi*craft')'; 
%    % apply on propellers
%    prop1 = (rot_phi*prop1')';
%    prop2 = (rot_phi*prop2')';
%    prop3 = (rot_phi*prop3')';
%    prop4 = (rot_phi*prop4')';
%     end       
% %
% % Rotations-Matrix um theta (roll)
% %
% if(Config.theta)
%     
%     ctheta = cos(u(5));            
%     stheta = sin(u(5));
%     rot_theta = [1     0       0   ; ...  % Rotationsmatrix um theta(roll)
%                  0  ctheta  -stheta; ...
%                  0  stheta   ctheta];
%              
%    % apply on craft
%    craft = (rot_theta*craft')'; 
%    % apply on propellers
%    prop1 = (rot_theta*prop1')';
%    prop2 = (rot_theta*prop2')';
%    prop3 = (rot_theta*prop3')';
%    prop4 = (rot_theta*prop4')';
% end
% %
% % Rotations-Matrix um Psi (yaw)
% %
% if(Config.psi)
%     cpsi = cos(u(6));            
%     spsi = sin(u(6));
% 
%     rot_psi = [cpsi -spsi 0; ...  % Rotationsmatrix um psi(yaw)
%                 spsi  cpsi 0; ...
%                   0    0   1];
%               
%    % apply on craft
%    craft = (rot_psi*craft')'; 
%    % apply on propellers
%    prop1 = (rot_psi*prop1')';
%    prop2 = (rot_psi*prop2')';
%    prop3 = (rot_psi*prop3')';
%    prop4 = (rot_psi*prop4')';
% end
if(Config.theta)
  ctheta = cos(u(5));            
  stheta = sin(u(5));     
else
  ctheta = cos(0);            
  stheta = sin(0);     
end
if(Config.psi)
  cpsi = cos(u(6));            
  spsi = sin(u(6));
else
  cpsi = cos(0);            
  spsi = sin(0);
end    
if(Config.phi)
  cphi = cos(u(4));            
  sphi = sin(u(4));
else
  cphi = cos(0);            
  sphi = sin(0);
end

S  = [ cpsi*ctheta  cpsi*stheta*sphi-spsi*cphi cpsi*stheta*cphi+spsi*sphi;
       spsi*ctheta  spsi*stheta*sphi+cphi*cpsi spsi*stheta*cphi-cpsi*sphi;
          -stheta               ctheta*sphi             ctheta*cphi      ];
   
craft = (S*craft')'; 
prop1 = (S*prop1')'; 
prop2 = (S*prop2')'; 
prop3 = (S*prop3')'; 
prop4 = (S*prop4')'; 
      
if(Config.x)
    xt = u(1);
else
    xt = 0;
end
if(Config.y)
    yt = u(2);
else
    yt = 0;
end
if(Config.z)
    zt = u(3);
else
    zt = 0;
end

% do a translation only if enabled
  if(Config.x || Config.y || Config.z)           
    % create translation-matrix for propellers
    [a_prop,b_prop] = size(prop1);
    Trans_prop = ([ xt yt zt]'*ones(1,a_prop))';  
    % apply on propellers
    prop1 = prop1+Trans_prop;
    prop2 = prop2+Trans_prop;
    prop3 = prop3+Trans_prop;
    prop4 = prop4+Trans_prop;
  
     % create translation-matrix for craft
    [a_craft,b_craft] = size(craft);
    Trans_craft = ([ xt yt zt]'*ones(1,a_craft))'; 
    % apply on propellers
    craft = craft+Trans_craft;
    
  end
  
  set(handle.prop1,'vertices',prop1);
  set(handle.prop2,'vertices',prop2);
  set(handle.prop3,'vertices',prop3);
  set(handle.prop4,'vertices',prop4);
  set(handle.craft,'vertices',craft);
  
%
% Setzen der Position und Orientierung der Kamera
%
switch Config.camera_view
    case 1
       % Feste Kamera Position
        set(handle.axes(1), 'cameraupvector',    [0 0 1], ...
                            'cameraposition',    Config.camera_pos, ...
                            'cameratarget',      [0 0 0], ...
                            'cameraviewangle',   Config.view);
    case 2
       % Frei Kamera Positon Kamera nur von Benutzer gesteuert
end

%
% Aktualisieren des Fensters erzwingen 
%
        drawnow

% end mdlUpdate

%
%=============================================================================
% mdlGetTimeOfNextVarHit
% Return the time of the next hit for this block.  
%=============================================================================
%
function sys=mdlGetTimeOfNextVarHit(t,x,u,Config)
   sys = t+Config.update;

% end mdlGetTimeOfNextVarHit

%
%=============================================================================
% miss_shape
% Function to draw shape of missile object
%=============================================================================
%
function [x,y,z]=craft(Config, H, D, R)

x = [];
y = [];
z = [];



W2R = R/2^(1/2); % R durch Wurzel(2)

%Bodenfläche
x = [x [W2R ;  W2R ;-W2R ;-W2R ] ]; 
y = [y [W2R ; -W2R ;-W2R ; W2R ] ];
z = [z [-H  ; -H   ; -H  ; -H  ] ];

% Ein Arm
% obere und untere Fläche
xa =  [0 W2R ; W2R W2R ;D/2 D/2   ; W2R  W2R] ; 
ya =  [0 0   ; W2R W2R ;0   0     ;-W2R -W2R] ;
za =  [0 -H  ; 0   -H  ;0  -H*0.3 ;  0    -H] ;
% Seitenflächen
xas =  [W2R  W2R ; D/2 D/2 ; D/2    D/2   ; W2R  W2R] ; 
yas =  [W2R -W2R ; 0    0  ;  0      0    ; W2R -W2R] ;
zas =  [0    0   ; 0    0  ;-H*0.3 -H*0.3 ; -H  -H  ] ;

%first arm
x = [x xa xas ];
y = [y ya yas ];
z = [z za zas ]; 
%second arm
x = [x ya  yas ]; 
y = [y xa  xas ];
z = [z za  zas ]; 
%third arm
x = [x  ya   yas];
y = [y -xa  -xas];
z = [z  za   zas];
%forth arm
x = [x -xa -xas ];
y = [y  ya  yas ];
z = [z  za  zas ]; 

function [x,y,z]=props(Config, H, R) % Konfigurationsdaten und Radbreite
x = [];
y = [];
z = [];


% Erstellen des linken Rades
stepsize = pi/4;
for i = 0:stepsize:2*pi-stepsize
    Rcosi = R*cos(i);
    Rcoss2 = R*cos(i+stepsize/2);
    Rcoss = R*cos(i+stepsize);
    Rsini = R*sin(i);
    Rsins2 = R*sin(i+stepsize/2);
    Rsins = R*sin(i+stepsize);
   
%Rotor
    x = [x [0 ; Rsini; Rsins2 ; Rsins]];
    y = [y [0 ; Rcosi; Rcoss2 ; Rcoss]];
    z = [z [H*0.1; H*0.1 ;H*0.1 ; H*0.1]];

end


   
% End miss_shape
