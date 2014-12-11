% r = i_decrease([[10,15];[10,15]], [[11,12];[11,12]])
function r = i_decrease(X_p, Y_p)
if (nargin ~= 2)
    error('Error : Wrong number of parameters.');
end
r = i_defaultdoublefn2arg(X_p, Y_p, 'decreasex');
