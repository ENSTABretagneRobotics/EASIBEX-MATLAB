% Download and test : 
% https://github.com/ENSTABretagneRobotics/EASIBEX-MATLAB/

% To define an EASIBEX-MATLAB interval :
x=[-2,2]
% x(1,2) would be 2
% An empty interval would be :
x=[NaN,NaN]
% Infinity :
x=[-Inf,Inf]

% To define a box :
x=[[-2,2];[2,4];[-4,1]]
% x(2,:) would be [2,4]

% 2 intervals can be added using :
Z=i_Add([0,2],[-1,2])
% and 2 boxes :
Z=i_Add([[0,1];[0,10];[0,10]],[[-1,0];[2,5];[-1,0]])

% To contract 3 intervals Z=[-10,1], X=[0,2], Y=[-1,2] knowing the
% constraint Z=X+Y :
[Z,X,Y]=i_Cadd([-10,1],[0,2],[-1,2])

% To contract the vector x=[-10,10]*[0,10]*[-10,0] w.r.t. the q-relaxed intersection 
% of the 4 vectors [-2,2]*[2,4]*[-4,1], [-1,5]*[-5,8]*[-7,2], [-1,1]*[0,2]*[1,2], [-2,2]*[2,8]*[-1,2], 
% with q=2 :
x = [[-10,10];[0,10];[-10,0]]
y_j = {[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]}
x = i_C_q_in(x, 2, y_j)

% imatrix
x = [[1,2];[0,1]]; % box
A = i_imatrix(2, 2, [[[0,1];[0,0]];[[0,0];[0,1]]]); % imatrix
i_Mulimatrixbox(A, x) % Ax

y = [[2,3];[1,2]]; % box 
[v, M, u] = i_Cmulimatrixbox(y, A, x) % Contract y=Ax
 
A = i_imatrix(2, 2, [[[0,1];[0,0]];[[0,0];[0,1]]]);
B = i_imatrix(2, 2, [[[1,2];[0,0]];[[0,0];[1,2]]]);
C =  i_imatrix(2, 2, [[[2,3];[0,0]];[[0,0];[2,3]]]);
i_Mul(A, B) % AB

[M, P, Q] = i_Cmul(C, A, B) % Contract C=AB
