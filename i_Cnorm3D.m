function [N, X, Y, Z] = i_Cnorm3D(N_p, X_p, Y_p, Z_p)
if (nargin ~= 4)
    error('Error : Wrong number of parameters.');
end
[N, X, Y, Z] = i_Cdefaultquaternarycontractor(N_p, X_p, Y_p, Z_p, 'Cnorm3Dx');
