% r = i_Width([[-10,10];[2,10];[10,11]])
function r = i_Width(X_p)

% Ideally, user should load manually...
if not(libisloaded('intervalx_adapt'))
    loadlibrary('intervalx_adapt');
end

%libfunctions intervalx_adapt -full

switch nargin
    case 1
        ;
    otherwise
        error('Error : Wrong number of parameters.');
end

size_X_p = size(X_p);
n = size_X_p(1); % Box dimension.

% Shape conversions suitable for the pointers to send to the library.
r = 0;
X_p = reshape(X_p', [1 2*n]);

pr = libpointer('doublePtr', r);
pX_p = libpointer('doublePtr', X_p);

calllib('intervalx_adapt', 'Widthx', pr, pX_p, n);

r = pr.value;

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
