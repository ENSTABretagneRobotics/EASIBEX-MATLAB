% [Z, X, Y] = i_Cnorm([1,4], [0,2], [2,5])
function [N, X, Y] = i_Cnorm(N_p, X_p, Y_p)
[N, X, Y] = i_Cdefaultternarycontractor(N_p, X_p, Y_p, 'Cnormx');
