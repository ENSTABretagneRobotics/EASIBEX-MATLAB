function c = i_Mulimatrixbox(A_p, b_p)

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

size_A_p = size(A_p);
size_b_p = size(b_p);

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
c = repmat(NaN, [1 2*n]);
A_p = reshape(permute(A_p, [1 3 2]), [n*m 2]);
A_p = reshape(A_p', [1 2*n*m]);
b_p = reshape(b_p', [1 2*n]);

pc = libpointer('doublePtr', c);
pA_p = libpointer('doublePtr', A_p);
pb_p = libpointer('doublePtr', b_p);

calllib('intervalx_adapt', 'Mulimatrixboxx', pc, pA_p, pb_p, nb, n, m);

c = pc.value;

% Conversions to human-readable format.
c = reshape(c, [2 n])';

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
