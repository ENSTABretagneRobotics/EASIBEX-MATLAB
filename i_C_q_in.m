% x = [[-10,10];[0,10];[-10,0]];
% yj = {[[-2,2];[2,4];[-4,1]];[[-1,5];[-5,8];[-7,2]];[[-1,1];[0,2];[1,2]];[[-2,2];[2,8];[-1,2]]}
% r = i_C_q_in(x, 2, yj)
function x = i_C_q_in(x_p, q, yj)

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

size_x_p = size(x_p);
size_yj = size(yj);

if (iscell(yj) == 1)
    % vector<interval> or vector<box>.
    nb = size_yj(1); % Number of elements in the vector.
    s = size(yj{1});
    n = s(1); % Box dimension (should be 1 for interval).
elseif (isfloat(yj) == 1)
    % interval, box or imatrix.
    nb = 1;
    n = size_yj(1); % Box dimension (should be 1 for interval).
else
    error('Error : Unhandled argument type.');
end

if (n ~= size_x_p(1))
    error('Error : Box sizes must match.');
end

% Shape conversions suitable for the pointers to send to the library.
x_p = reshape(x_p', [1 2*n]);
if (nb > 1)
    yj = cell2mat(yj);
end
yj = reshape(yj', [1 2*n*nb]);

px_p = libpointer('doublePtr', x_p);
pyj = libpointer('doublePtr', yj);

calllib('intervalx_adapt', 'C_q_inx', px_p, q, pyj, nb, n);

x = reshape(px_p.value, [2 n])';

% To remove in release, user should unload manually, but should not be
% important if it is not unloaded...
% unloadlibrary('intervalx_adapt');
