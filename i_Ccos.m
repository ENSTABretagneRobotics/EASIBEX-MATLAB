function [Y, X] = i_Ccos(Y_p, X_p)
if (nargin ~= 2)
    error('Error : Wrong number of parameters.');
end
[Y, X] = i_Cdefaultbinarycontractor(Y_p, X_p, 'Ccosx');
