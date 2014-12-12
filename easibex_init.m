switch (computer)
    case 'PCWIN64'
        loadlibrary('intervalx_adapt', @intervalx_adapt_proto);
    otherwise
        loadlibrary('intervalx_adapt');
end
