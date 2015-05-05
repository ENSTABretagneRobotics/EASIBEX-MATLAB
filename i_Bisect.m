% [X1, X2] = i_Bisect([[-10,10];[2,10];[10,11]])
function [X1, X2] = i_Bisect(X_p)

% Ideally, user should load manually...
if not(libisloaded('intervalx_adapt'))
    switch (computer)
        case 'PCWIN64'
            loadlibrary('intervalx_adapt', @intervalx_adapt_proto);
        otherwise
            loadlibrary('intervalx_adapt');
    end
end

%libfunctions intervalx_adapt -full

size_X_p = size(X_p);
n = size_X_p(1); % Box dimension.

% Shape conversions suitable for the pointers to send to the library.
X_p = reshape(X_p', [1 2*n]);
X1 = repmat(NaN, [1 2*n]);
X2 = repmat(NaN, [1 2*n]);

pX_p = libpointer('doublePtr', X_p);
pX1 = libpointer('doublePtr', X1);
pX2 = libpointer('doublePtr', X2);

calllib('intervalx_adapt', 'Bisectx', pX_p, pX1, pX2, n);

% Conversions to human-readable format.
X1 = reshape(pX1.value, [2 n])';
X2 = reshape(pX2.value, [2 n])';

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
