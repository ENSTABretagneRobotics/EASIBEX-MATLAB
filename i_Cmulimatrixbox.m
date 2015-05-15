function [c, A, b] = i_Cmulimatrixbox(c_p, A_p, b_p)

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

size_c_p = size(c_p);
size_A_p = size(A_p);
size_b_p = size(b_p);
if (size_c_p ~= size_b_p)
    error('Error : Sizes must match.');
end

if (iscell(A_p) == 1)
    % vector<interval> or vector<box>.
    error('Error : Unhandled argument type.');
elseif (isfloat(A_p) == 1)
    % interval, box or imatrix.
    nb = 1;
    n = size_A_p(1); % Box dimension (should be 1 for interval).
    s = size(size_A_p);
    if (s(2) == 3)
        % imatrix
        m = size_A_p(3);
    else
        % interval or box
        error('Error : Unhandled argument type.');
    end
else
    error('Error : Unhandled argument type.');
end

if ((n ~= size_b_p(1)) | (n ~= m))
    error('Error : Incompatible sizes.');
end

% Shape conversions suitable for the pointers to send to the library.
A_p = reshape(permute(A_p, [1 3 2]), [n*m 2]);
c_p = reshape(c_p', [1 2*n]);
A_p = reshape(A_p', [1 2*n*m]);
b_p = reshape(b_p', [1 2*n]);

pc_p = libpointer('doublePtr', c_p);
pA_p = libpointer('doublePtr', A_p);
pb_p = libpointer('doublePtr', b_p);

calllib('intervalx_adapt', 'Cmulimatrixboxx', pc_p, pA_p, pb_p, nb, n, m);

c = pc_p.value;
A = pA_p.value;
b = pb_p.value;

% Conversions to human-readable format.
c = reshape(c, [2 n])';
A = reshape(A, [2 n*m])';
b = reshape(b, [2 n])';
A = permute(reshape(A, [n m 2]), [1 3 2]);

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
