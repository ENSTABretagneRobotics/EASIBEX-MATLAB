function [Z, X, Y] = i_Cdefaultternarycontractor(Z_p, X_p, Y_p, function_p)

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

size_Z_p = size(Z_p);
size_X_p = size(X_p);
size_Y_p = size(Y_p);
if ((size_Z_p ~= size_X_p) | (size_X_p ~= size_Y_p))
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
    error('Error : Unhandled argument type.');
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

calllib('intervalx_adapt', function_p, pZ_p, pX_p, pY_p, nb, n, m);

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
% unloadlibrary('intervalx_adapt');
