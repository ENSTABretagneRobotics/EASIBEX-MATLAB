function z = i_defaultdoublefn2arg(X_p, Y_p, function_p)

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

size_Y_p = size(Y_p);
size_X_p = size(X_p);
if (size_Y_p ~= size_X_p)
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
    else
        % interval or box
        m = 1;
    end
else
    error('Error : Unhandled parameter type.');
end

% Shape conversions suitable for the pointers to send to the library.
if (nb > 1)
    X_p = cell2mat(X_p);
    Y_p = cell2mat(Y_p);
end
if (m > 1)
    X_p = reshape(permute(X_p, [1 3 2]), [n*nb*m 2]);
    Y_p = reshape(permute(Y_p, [1 3 2]), [n*nb*m 2]);
end
z = repmat(NaN, [1 nb]);
X_p = reshape(X_p', [1 2*n*nb*m]);
Y_p = reshape(Y_p', [1 2*n*nb*m]);

pz = libpointer('doublePtr', z);
pX_p = libpointer('doublePtr', X_p);
pY_p = libpointer('doublePtr', Y_p);

calllib('intervalx_adapt', function_p, pz, pX_p, pY_p, nb, n, m);

z = pz.value;

% Conversions to human-readable format.
if (nb > 1)
    z = mat2cell(z,ones(1,nb));
end

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
