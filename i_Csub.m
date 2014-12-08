function [Z, X, Y] = i_Csub(Z_p, X_p, Y_p)
if (nargin ~= 3)
    error('Error : Wrong number of parameters.');
end
[Z, X, Y] = i_Cdefaultternarycontractor(Z_p, X_p, Y_p, 'Csubx');