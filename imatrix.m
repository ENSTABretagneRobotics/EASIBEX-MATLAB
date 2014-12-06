% A = imatrix(3, 4, [[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]])
function A = imatrix(n, m, data)

switch nargin
    case 3
        ;
    otherwise
        error('Error : Wrong number of parameters.');
end

% To force MATLAB to resize correctly.
A = permute(reshape(data, [n m 2]), [1 3 2]);
