% Global variables to share with other files.
global u;
global bExit;
global scale;

button = questdlg('Robot localization in dead-reckoning when inside (below the line) and with GPS outside (above the line). Controls are z,s,q,d keys, zoom with +,- and stop with ESC. Ready?', 'Ready?');
if (strcmp(button, 'Yes') == 0)
    return;
end

% Create a figure that will use the function keycontrol() when a key is
% pressed.
fig = figure('Position',[200 200 400 400],'KeyPressFcn','keycontrol','Name','Ecrazor game','NumberTitle','off');
% Force the figure to have input focus (required to capture keys).
set(fig,'WindowStyle','Modal');
axis('off');

bExit = 0;
scale = 50;

x = [0;0;0;10];
u = [0;0];
dt = 0.01;
t = 0;

% Known initial position.
x_hat=[[-0.1,0.1];[-0.1,0.1];[-0.1,0.1];[10-0.1,10+0.1]];

while (bExit == 0)
    % Simulator.
    x = x+f(x,u)*dt; % Simulated evolution equation of the robot.    
    y = g(x); % Simulated observation equation.
    
    % Interval observer.    
    x_hat = i_Add(x_hat,dt*f_hat(x_hat,u)); % Estimated state of the robot using evolution equation.
    x_hat(3,:) = i_Inter({x_hat(3,:);[y(3)-0.1,y(3)+0.1]}); % Contract estimated state using observation equation (compass).
    if (x(2) > 0) % GPS when outside (upper part of the environment).
       x_hat(1,:) = i_Inter({x_hat(1,:);[y(1)-1,y(1)+1]}); 
       x_hat(2,:) = i_Inter({x_hat(2,:);[y(2)-1,y(2)+1]}); 
    end

    clf; hold on; axis([-scale,scale,-scale,scale]); axis square;
    plot([-scale,scale],[0,0],'c'); % Limit between inside (below) and outside (above, where GPS is available).
    draw_hat(x_hat); % Draw estimated position.    
    draw(x); % Simulated robot.
    
    % Wait a little bit.
    pause(dt);
    t = t+dt;
end

close(fig);
