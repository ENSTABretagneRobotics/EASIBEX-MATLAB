% [Z, X, Y] = i_Cadd([-10,1], [0,2], [-1,2])
% [Z, X, Y] = i_Cadd([[-10,10];[2,10];[10,11]], [[0,1];[0,10];[0,10]], [[-1,0];[2,5];[-1,0]])
function [Z, X, Y] = i_Cadd(Z_p, X_p, Y_p)
if (nargin ~= 3)
    error('Error : Wrong number of parameters.');
end
[Z, X, Y] = i_Cdefaultternarycontractor(Z_p, X_p, Y_p, 'Caddx');