% r = i_Volume([[-10,10];[2,10];[10,11]])
function r = i_Volume(X_p)
if (nargin ~= 1)
    error('Error : Wrong number of parameters.');
end
r = i_defaultdoublefn1arg(X_p, 'Volumex');
