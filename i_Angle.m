% r = i_Angle([[-1,1];[-1,1]], [[2,4];[2,4]])
function r = i_Angle(X_p, Y_p)
if (nargin ~= 2)
    error('Error : Wrong number of parameters.');
end
r = i_defaultdoublefn2arg(X_p, Y_p, 'Anglex');
