% A = i_imatrix(3, 4, [[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]])
function A = i_imatrix(n, m, data)
% To force MATLAB to resize correctly.
A = permute(reshape(data, [n m 2]), [1 3 2]);
