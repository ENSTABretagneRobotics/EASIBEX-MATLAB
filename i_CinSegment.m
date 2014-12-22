function [X, Y] = i_CinSegment(X_p, Y_p, ax, ay, bx, by)

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
size_ax = size(ax);
size_ay = size(ay);
size_bx = size(bx);
size_by = size(by);
if ((size_X_p ~= size_Y_p) | (size_X_p ~= size_ax) | (size_X_p ~= size_ay) | (size_X_p ~= size_bx) | (size_X_p ~= size_by))
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
    ax = cell2mat(ax);
    ay = cell2mat(ay);
    bx = cell2mat(bx);
    by = cell2mat(by);
end
X_p = reshape(X_p', [1 2*nb]);
Y_p = reshape(Y_p', [1 2*nb]);
ax = reshape(ax', [1 nb]);
ay = reshape(ay', [1 nb]);
bx = reshape(bx', [1 nb]);
by = reshape(by', [1 nb]);

pX_p = libpointer('doublePtr', X_p);
pY_p = libpointer('doublePtr', Y_p);
pax = libpointer('doublePtr', ax);
pay = libpointer('doublePtr', ay);
pbx = libpointer('doublePtr', bx);
pby = libpointer('doublePtr', by);

calllib('intervalx_adapt', 'CinSegmentx', pX_p, pY_p, pax, pay, pbx, pby, nb, n, m);

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
