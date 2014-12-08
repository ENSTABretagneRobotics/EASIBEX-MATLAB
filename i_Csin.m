% [Y, X] = i_Csin([-0.5,1], [0,2])
% [Y, X] = i_Csin([[-0.1,0.1];[-0.2,1];[0.8,1]], [[0,1];[-2,2];[0,1.7]])
function [Y, X] = i_Csin(Y_p, X_p)
if (nargin ~= 2)
    error('Error : Wrong number of parameters.');
end
[Y, X] = i_Cdefaultbinarycontractor(Y_p, X_p, 'Csinx');
