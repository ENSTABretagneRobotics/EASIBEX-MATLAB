% r = i_Subset([[10,15];[10,15]], [[11,12];[11,12]])
function r = i_Subset(X_p, Y_p)
if (nargin ~= 2)
    error('Error : Wrong number of parameters.');
end
r = i_defaultboolfn2arg(X_p, Y_p, 'Subsetx');
