% [X, X1, X2] = Bisect([[-10,10];[2,10];[10,11]], [[-Inf,Inf];[-Inf,Inf];[-Inf,Inf]], [[-Inf,Inf];[-Inf,Inf];[-Inf,Inf]])
function [X, X1, X2] = Bisect(X_p, X1_p, X2_p)

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

size_X_p = size(X_p);
size_X1_p = size(X1_p);
size_X2_p = size(X2_p);
if ((size_X_p ~= size_X1_p) | (size_X_p ~= size_X2_p))
    error('Error : Sizes must match.');
end

n = size_X_p(1); % Box dimension.

% Shape conversions suitable for the pointers to send to the library.
X_p = reshape(X_p', [1 2*n]);
X1_p = reshape(X1_p', [1 2*n]);
X2_p = reshape(X2_p', [1 2*n]);

pX_p = libpointer('doublePtr', X_p);
pX1_p = libpointer('doublePtr', X1_p);
pX2_p = libpointer('doublePtr', X2_p);

calllib('intervalx_adapt', 'Bisectx', pX_p, pX1_p, pX2_p, n);

% Conversions to human-readable format.
X = reshape(pX_p.value, [2 n])';
X1 = reshape(pX1_p.value, [2 n])';
X2 = reshape(pX2_p.value, [2 n])';

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
