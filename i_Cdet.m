function [Z, V, W, X, Y] = i_Cdet(Z_p, V_p, W_p, X_p, Y_p)
if (nargin ~= 5)
    error('Error : Wrong number of parameters.');
end
[Z, V, W, X, Y] = i_Cdefaultquinarycontractor(Z_p, V_p, W_p, X_p, Y_p, 'Cdetx');
