function [X, Y] = i_Cortho(X_p, Y_p)
if (nargin ~= 2)
    error('Error : Wrong number of parameters.');
end
[X, Y] = i_Cdefaultbinarycontractor(X_p, Y_p, 'Corthox');
