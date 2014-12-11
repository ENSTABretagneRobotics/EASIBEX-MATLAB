% [Z, X, Y] = i_Cnorm([1,4], [0,2], [2,5])
function [N, X, Y] = i_Cnorm(N_p, X_p, Y_p)
if (nargin ~= 3)
    error('Error : Wrong number of parameters.');
end
[N, X, Y] = i_Cdefaultternarycontractor(N_p, X_p, Y_p, 'Cnormx');
