% This function should be called when a key is pressed.
function keycontrol()
% Global variables to share with other files.
global u;
global bExit;
global scale;

key = get(gcbf,'CurrentCharacter');
% Actions to do depending on the key pressed.
switch (key)
    case 27,
        bExit = 1;
    case 'z',
        u = [0, 10];
    case 's',
        u = [0, -10];
    case 'q',
        u = [10, 0];
    case 'd',
        u = [-10, 0];
    case '+',
        scale = scale*0.9;
    case '-',
        scale = scale/0.9;
end
end
