switch testcase
    case 1 % Height
        desforce.time = [0 0.7 1 5 6 12 30];            % in s
        desforce.force = [m*g m*g m*g+1 m*g+1 m*g-1.5 m*g m*g];           % in N
        desheight.time = [0 0.01 30];           % in s
        desheight.height = [0 15 15];           % in m
        desroll.time = [0 30];                  % in s
        desroll.angle = [0 0];                  % in rad
        despitch.time = [0 30];                 % in s
        despitch.angle = [0 0];                 % in rad
        desyaw.time = [0 30];                   % in s
        desyaw.velocity = [0 0];                % in rad/s
        
    case 2 % Roll angle
        desforce.time = [0 30];                 % in s
        desforce.force = [m*g m*g];             % in N
        desheight.time = [0 30];                % in s
        desheight.height = [0 0];               % in m
        desroll.time = [0 5 10 15 20 30];		% in s
        desroll.angle = [0 0.1 0.1 0.1 0 0];   % in rad
        despitch.time = [0 30];                 % in s
        despitch.angle = [0 0];                 % in rad
        desyaw.time = [0 30];                   % in s
        desyaw.velocity = [0 0];                % in rad/s
        
    case 3 % Step Roll angle
        desforce.time = [0 5 30];                 % in s
        desforce.force = [m*g m*g m*g];                 % in N        
        desheight.time = [0 30];                % in s
        desheight.height = [0 0];               % in m
        desroll.time = [0 0.01 6.01 9 9.01 10 30]; % in s
        desroll.angle = [0 0.05 0.05 0.05 0.05 0.05 0.05];    % in rad
        despitch.time = [0 30];                 % in s
        despitch.angle = [0 0];                 % in rad
        desyaw.time = [0 30];               	% in s
        desyaw.velocity = [0 0];                % in rad/s
        
    case 4  % Step Pitch angle
        desforce.time = [0 5 30];                 % in s
        desforce.force = [m*g m*g m*g];                 % in N        
        desheight.time = [0 30];                % in s
        desheight.height = [0 0];               % in m
        desroll.time = [0 30];                  % in s
        desroll.angle = [0 0];                  % in rad
        despitch.time = [0 0.01 6.01 9 9.01 10 30];      % in s
        despitch.angle = [0 0.05 0.05 0.05 0.05 0.05 0.05];	% in rad
%         despitch.time = [0 5 10 15 20 30];		% in s
%         despitch.angle = [0 0.1 0.1 0.1 0 0];   % in rad
        desyaw.time = [0 30];                   % in s
        desyaw.velocity = [0 0];                % in rad/s
        
    case 5      % Step Yaw velocity
        desforce.time = [0 5 30];                 % in s
        desforce.force = [m*g m*g m*g];                 % in N  
        desheight.time = [0 30];                % in s
        desheight.height = [0 0];               % in m
        desroll.time = [0 30];                  % in s
        desroll.angle = [0 0];                  % in rad
        despitch.time = [0 30];                 % in s
        despitch.angle = [0 0];                 % in rad
%         desyaw.time = [0 5 10 15 20 30];		% in s
%         desyaw.velocity = [0 0.1 0.1 0.1 0 0];   % in rad/s
        desyaw.time = [0 0.01 6.01 9 9.01 10 30];		% in s
        desyaw.velocity = [0 0.05 0.05 0.05 0.05 0.05 0.05]; % in rad/s
        
    case 6 % Everything
        desforce.time = [0 0.01 30];                 % in s
        desforce.force = [0 6.1 6.1];               % in N
        desheight.time = [0 5 15 20 30];        % in s
        desheight.height = [0 5 -5 0 0];        % in m
        desroll.time = [0 0.01 5 10 15 20 30];       % in s
        desroll.angle = [0 0.25 0.25 0.25 0.25 0.25 0.25];    % in rad
        despitch.time = [0 0.01 3 8 10 30];          % in s
        despitch.angle = [0 0.25 0.25 0.25 0.25 0.25];      % in rad
%         desyaw.time = [0 2 5 10 15 20 30];		% in s
%         desyaw.velocity = [0 0.01 0.01 0.01 0.01 0.01 0.01];   % in rad/s
        desyaw.time = [0 0.01 3 8 10 30];		% in s
        desyaw.velocity = [0 0.25 0.25 0.25 0.25 0.25];   % in rad/s
        
end