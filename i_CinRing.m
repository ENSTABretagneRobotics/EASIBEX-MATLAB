function [X, Y] = i_CinRing(X_p, Y_p, cx, cy, R)

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

size_cx = size(cx);
size_cy = size(cy);
size_R = size(R);
if ((size_cx ~= size_cy) | (size_cx ~= size_R))
    error('Error : Sizes must match.');
end

if (iscell(cx) == 1)
    % vector<interval> or vector<box>.
    nb = size_cx(1); % Number of elements in the vector.
    s = size(cx{1});
    n = s(1); % Box dimension (should be 1 for interval).
    m = 1; % Number of columns in the imatrix (should be 1 for interval and box, vector<imatrix> unsupported).
elseif (isfloat(cx) == 1)
    % interval, box or imatrix.
    nb = 1;
    n = size_cx(1); % Box dimension (should be 1 for interval).
    s = size(size_cx);
    if (s(2) == 3)
        % imatrix
        m = size_cx(3);
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
X_p = reshape(X_p', [1 2]);
Y_p = reshape(Y_p', [1 2]);
if (nb > 1)
    cx = cell2mat(cx);
    cy = cell2mat(cy);
    R = cell2mat(R);
end
cx = reshape(cx', [1 nb]);
cy = reshape(cy', [1 nb]);
R = reshape(R', [1 2*nb]);

pX_p = libpointer('doublePtr', X_p);
pY_p = libpointer('doublePtr', Y_p);
pcx = libpointer('doublePtr', cx);
pcy = libpointer('doublePtr', cy);
pR = libpointer('doublePtr', R);

calllib('intervalx_adapt', 'CinRingx', pX_p, pY_p, pcx, pcy, pR, nb, n, m);

X = pX_p.value;
Y = pY_p.value;

% Conversions to human-readable format.
X = reshape(X, [2 1])';
Y = reshape(Y, [2 1])';

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
