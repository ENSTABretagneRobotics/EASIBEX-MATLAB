% x = {[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]}
% r = i_Inter(x)
function r = i_Inter(x)

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

size_x = size(x);

if (iscell(x) == 1)
    % vector<interval> or vector<box>.
    nb = size_x(1); % Number of elements in the vector.
    s = size(x{1});
    n = s(1); % Box dimension (should be 1 for interval).
elseif (isfloat(x) == 1)
    % interval, box or imatrix.
    nb = 1;
    n = size_x(1); % Box dimension (should be 1 for interval).
else
    error('Error : Unhandled argument type.');
end

% Shape conversions suitable for the pointers to send to the library.
r = repmat(NaN, [1 2*n]);
if (nb > 1)
    x = cell2mat(x);
end
x = reshape(x', [1 2*n*nb]);

pr = libpointer('doublePtr', r);
px = libpointer('doublePtr', x);

calllib('intervalx_adapt', 'Interx', pr, px, nb, n);

r = reshape(pr.value, [2 n])';

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
