% To define and interval :
% x = [-2,2]
% x(1,2) would be 2.

% To define a box :
% x = [[-2,2];[2,4];[-4,1]]
% x(2,:) would be [2,4].

% To define an imatrix :
% x = [[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]]
% x = permute(reshape(x, [3 4 2]), [1 3 2]) % To force MATLAB to resize correctly.
% This will be represented by a MATLAB 3D array.
% x(:,:,1) would be [[-2,2];[2,4];[-4,1]] and x(3,:,4) would be [-1,2].

% To define a vector<interval> :
% x = {[-2,2];[2,4];[-4,1]}
% This will be represented by a MATLAB cell array.
% x{3} would be [-4,1] and x{3}(2) would be 1.

% To define a vector<box> :
% x = {[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]}
% This will be represented by a MATLAB cell array.
% x{4}(3,:) would be [-1,2].



% faire des Add (fw) et Cadd (fwbw)...
% Sin, Csin, Bisect, Inter, C_q_in, ...



% Cadd(interval&, interval&, interval&)
% Cadd(box&, box&, box&)
% [Z, X, Y] = Cadd([-10,1], [0,2], [-1,2]);
% [Z, X, Y] = Cadd([[-10,10];[2,10];[10,11]], [[0,1];[0,10];[0,10]], [[-1,0];[2,5];[-1,0]]);
function [Z, X, Y] = Cadd(Z_p, X_p, Y_p)

% Ideally, user should load manually...
if not(libisloaded('intervalx_adapt'))
    loadlibrary('intervalx_adapt');
end

%libfunctions intervalx_adapt -full

switch nargin
    case 3
        ;
    otherwise
        error('Error : Wrong number of parameters.');
end

size_Z_p = size(Z_p);
size_Y_p = size(Y_p);
size_X_p = size(X_p);
if ((size_Z_p ~= size_Y_p) | (size_Y_p ~= size_X_p))
    error('Error : Sizes must match.');
end

if (iscell(Z_p) == 1)
    % vector<interval> or vector<box>.
    nb = size_Z_p(1); % Number of elements in the vector.
    s = size(Z_p{1});
    n = s(1); % Box dimension (should be 1 for interval).
    m = 1; % Number of columns in the imatrix (should be 1 for interval and box, vector<imatrix> unsupported).
elseif (isfloat(Z_p) == 1)
    % interval, box or imatrix.
    nb = 1;
    n = size_Z_p(1); % Box dimension (should be 1 for interval).
    s = size(size_Z_p);
    if (s(2) == 3)
        % imatrix
        m = size_Z_p(3);
    else
        % interval or box
        m = 1;
    end
else
    error('Error : Unhandled parameter type.');
end

% Shape conversions suitable for the pointers to send to the library.
if (nb > 1)
    Z_p = cell2mat(Z_p);
    X_p = cell2mat(X_p);
    Y_p = cell2mat(Y_p);
end
if (m > 1)
    Z_p = reshape(permute(Z_p, [1 3 2]), [n*nb*m 2]);
    X_p = reshape(permute(X_p, [1 3 2]), [n*nb*m 2]);
    Y_p = reshape(permute(Y_p, [1 3 2]), [n*nb*m 2]);
end
Z_p = reshape(Z_p', [1 2*n*nb*m]);
X_p = reshape(X_p', [1 2*n*nb*m]);
Y_p = reshape(Y_p', [1 2*n*nb*m]);

pZ_p = libpointer('doublePtr', Z_p);
pX_p = libpointer('doublePtr', X_p);
pY_p = libpointer('doublePtr', Y_p);

calllib('intervalx_adapt', 'Caddx', pZ_p, pX_p, pY_p, nb, n, m);

Z = pZ_p.value;
X = pX_p.value;
Y = pY_p.value;

% Conversions to human-readable format.
Z = reshape(Z, [2 n*nb*m])';
X = reshape(X, [2 n*nb*m])';
Y = reshape(Y, [2 n*nb*m])';
if (m > 1)
    Z = permute(reshape(Z, [n nb*m 2]), [1 3 2]);
    X = permute(reshape(X, [n nb*m 2]), [1 3 2]);
    Y = permute(reshape(Y, [n nb*m 2]), [1 3 2]);
end
if (nb > 1)
    Z = mat2cell(Z,n*ones(1,nb));
    X = mat2cell(X,n*ones(1,nb));
    Y = mat2cell(Y,n*ones(1,nb));
end

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
unloadlibrary('intervalx_adapt');
