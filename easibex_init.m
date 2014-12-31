% Ideally, you should call : 
% easibex_init
% in the beginning (otherwise the initialization will be done when necessary but might take several seconds), and :
% unloadlibrary('intervalx_adapt');
% at the end (this will not be done automatically, but it should not be important in most cases...).
switch (computer)
    case 'PCWIN64'
        loadlibrary('intervalx_adapt', @intervalx_adapt_proto);
    otherwise
        loadlibrary('intervalx_adapt');
end
