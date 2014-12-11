function X = i_Cinteger(X_p)
if (nargin ~= 1)
    error('Error : Wrong number of parameters.');
end
X = i_Cdefaultunarycontractor(X_p, 'Cintegerx');
