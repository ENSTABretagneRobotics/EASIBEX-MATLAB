% Run this file to make MATLAB 64 bit generate important precompiled files : 
% intervalx_adapt_proto.m and intervalx_adapt_thunk_pcwin64.dll.
% Visual Studio 2008 with 64 bit compiler needs to be installed and
% correctly configured in MATLAB (using mex -setup and mex -setup C++ in
% MATLAB).
% These files will be necessary for MATLAB 64 bit users that do not have
% Visual Studio. 
% Note that this problem does not exist for MATLAB 32 bit (for several 
% reasons, such as the fact that it is provided with a 32 bit internal 
% compiler and therefore do not need Visual Studio...).
switch (computer)
    case 'PCWIN64'
        loadlibrary('intervalx_adapt', 'intervalx_adapt.h', 'notempdir')
    otherwise
        ;
end
