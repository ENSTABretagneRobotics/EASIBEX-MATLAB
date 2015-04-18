% To define an interval :
% x = [-2,2]
% x(1,2) would be 2.
% Empty : 
% x = [NaN,NaN]
% Infinity : 
% x = [-Inf,Inf]

% To define a box :
% x = [[-2,2];[2,4];[-4,1]]
% x(2,:) would be [2,4].

% To define an imatrix :
% x = imatrix(3, 4, [[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]])
% This will be represented by a MATLAB 3D array.
% x(:,:,1) would be [[-2,2];[2,4];[-4,1]] and x(3,:,4) would be [-1,2].

% To define a vector<interval> :
% x = {[-2,2];[2,4];[-4,1]}
% This will be represented by a MATLAB cell array.
% x{3} would be [-4,1] and x{3}(1,2) would be 1.

% To define a vector<box> :
% x = {[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]}
% This will be represented by a MATLAB cell array.
% x{4}(3,:) would be [-1,2].

% iboolean : itrue -> [1,1], ifalse -> [0,0], iperhaps -> [0,1].

% Ideally, you should call : 
% easibex_init
% in the beginning (otherwise the initialization will be done when necessary but might take several seconds), and :
% unloadlibrary('intervalx_adapt');
% at the end (this will not be done automatically, but it should not be important in most cases...).

% Z = i_Add([0,2], [-1,2])
% Z = i_Add([[0,1];[0,10];[0,10]], [[-1,0];[2,5];[-1,0]])
% X = i_imatrix(3, 4, [[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]])
% Y = i_imatrix(3, 4, [[[-4,1];[1,2];[-3,2]];[[-5,1];[-4,7];[-4,1]];[[-3,2];[2,2];[-1,0]];[[0,1];[-2,0];[-3,1]]])
% Z = i_Add(X,Y)
% X = {[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]}
% Y = {[[-4,1];[1,2];[-3,2]];[[-5,1];[-4,7];[-4,1]];[[-3,2];[2,2];[-1,0]];[[0,1];[-2,0];[-3,1]]}
% Z = i_Add(X,Y)
function Z = i_Add(X_p, Y_p)
Z = i_defaultfn2arg(X_p, Y_p, 'Addx');
