function [X, Y] = i_CinSegmentsOrCircles(X_p, Y_p, ax, ay, bx, by, cx, cy, r)

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

size_ax = size(ax);
size_ay = size(ay);
size_bx = size(bx);
size_by = size(by);
size_cx = size(cx);
size_cy = size(cy);
size_r = size(r);
if ((size_ax ~= size_ay) | (size_ax ~= size_bx) | (size_ax ~= size_by))
    error('Error : Sizes must match.');
end
if ((size_cx ~= size_cy) | (size_cx ~= size_r))
    error('Error : Sizes must match.');
end

if (iscell(ax) == 1)
    % vector<interval> or vector<box>.
    nbs = size_ax(1); % Number of elements in the vector.
    s = size(ax{1});
    n = s(1); % Box dimension (should be 1 for interval).
    m = 1; % Number of columns in the imatrix (should be 1 for interval and box, vector<imatrix> unsupported).
elseif (isfloat(ax) == 1)
    % interval, box or imatrix.
    nbs = 1;
    n = size_ax(1); % Box dimension (should be 1 for interval).
    s = size(size_ax);
    if (s(2) == 3)
        % imatrix
        m = size_ax(3);
        error('Error : Unhandled argument type.');
    else
        % interval or box
        m = 1;
    end
else
    error('Error : Unhandled argument type.');
end

if (iscell(cx) == 1)
    % vector<interval> or vector<box>.
    nbc = size_cx(1); % Number of elements in the vector.
    s = size(cx{1});
    n = s(1); % Box dimension (should be 1 for interval).
    m = 1; % Number of columns in the imatrix (should be 1 for interval and box, vector<imatrix> unsupported).
elseif (isfloat(cx) == 1)
    % interval, box or imatrix.
    nbc = 1;
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
if (nbs > 1)
    ax = cell2mat(ax);
    ay = cell2mat(ay);
    bx = cell2mat(bx);
    by = cell2mat(by);
end
if (nbc > 1)
    cx = cell2mat(cx);
    cy = cell2mat(cy);
    r = cell2mat(r);
end
ax = reshape(ax', [1 nbs]);
ay = reshape(ay', [1 nbs]);
bx = reshape(bx', [1 nbs]);
by = reshape(by', [1 nbs]);
cx = reshape(cx', [1 nbc]);
cy = reshape(cy', [1 nbc]);
r = reshape(r', [1 nbc]);

pX_p = libpointer('doublePtr', X_p);
pY_p = libpointer('doublePtr', Y_p);
pax = libpointer('doublePtr', ax);
pay = libpointer('doublePtr', ay);
pbx = libpointer('doublePtr', bx);
pby = libpointer('doublePtr', by);
pcx = libpointer('doublePtr', cx);
pcy = libpointer('doublePtr', cy);
pr = libpointer('doublePtr', r);

calllib('intervalx_adapt', 'CinSegmentsOrCirclesx', pX_p, pY_p, pax, pay, pbx, pby, pcx, pcy, pr, nbs, nbc, n, m);

X = pX_p.value;
Y = pY_p.value;

% Conversions to human-readable format.
X = reshape(X, [2 1])';
Y = reshape(Y, [2 1])';

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
