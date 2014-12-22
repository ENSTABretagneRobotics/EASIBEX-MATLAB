function [X, Y] = i_SinRing(X_p, Y_p, cx, cy, R, outer)

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
size_Y_p = size(Y_p);
size_cx = size(cx);
size_cy = size(cy);
size_R = size(R);
size_outer = size(outer);
if ((size_X_p ~= size_Y_p) | (size_X_p ~= size_cx) | (size_X_p ~= size_cy) | (size_X_p ~= size_R) | (size_X_p ~= size_outer))
    error('Error : Sizes must match.');
end

if (iscell(X_p) == 1)
    % vector<interval> or vector<box>.
    nb = size_X_p(1); % Number of elements in the vector.
    s = size(X_p{1});
    n = s(1); % Box dimension (should be 1 for interval).
    m = 1; % Number of columns in the imatrix (should be 1 for interval and box, vector<imatrix> unsupported).
elseif (isfloat(X_p) == 1)
    % interval, box or imatrix.
    nb = 1;
    n = size_X_p(1); % Box dimension (should be 1 for interval).
    s = size(size_X_p);
    if (s(2) == 3)
        % imatrix
        m = size_X_p(3);
        error('Error : Unhandled argument type.');
    else
        % interval or box
        m = 1;
    end
else
    error('Error : Unhandled argument type.');
end

if (n > 1)
    error('Error : Unhandled argument type.');
end

% Shape conversions suitable for the pointers to send to the library.
if (nb > 1)
    X_p = cell2mat(X_p);
    Y_p = cell2mat(Y_p);
    cx = cell2mat(cx);
    cy = cell2mat(cy);
    R = cell2mat(R);
    outer = cell2mat(outer);
end
X_p = reshape(X_p', [1 2*nb]);
Y_p = reshape(Y_p', [1 2*nb]);
cx = reshape(cx', [1 nb]);
cy = reshape(cy', [1 nb]);
R = reshape(R', [1 2*nb]);
outer = reshape(outer', [1 nb]);

pX_p = libpointer('doublePtr', X_p);
pY_p = libpointer('doublePtr', Y_p);
pcx = libpointer('doublePtr', cx);
pcy = libpointer('doublePtr', cy);
pR = libpointer('doublePtr', R);
pbOuter = libpointer('int32Ptr', outer);

calllib('intervalx_adapt', 'SinRingx', pX_p, pY_p, pcx, pcy, pR, pbOuter, nb, n, m);

X = pX_p.value;
Y = pY_p.value;

% Conversions to human-readable format.
X = reshape(X, [2 nb])';
Y = reshape(Y, [2 nb])';
if (nb > 1)
    X = mat2cell(X,ones(1,nb));
    Y = mat2cell(Y,ones(1,nb));
end

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
