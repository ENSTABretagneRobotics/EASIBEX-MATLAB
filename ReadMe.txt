EASIBEX-MATLAB
==============
Windows : 
- In MATLAB, go to File\Set Path...\Add Folder... and add this folder as well as x86 folder if you use MATLAB 32 bit or x64 folder if you use MATLAB 64 bit.
- Run sivia_easibex.m to test.
- Check i_Add.m and the other files for usage information.

Linux : 
- Type in a terminal something similar to (replace x64 by x86 if you use MATLAB 32 bit) : 
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/EASIBEX-MATLAB-master/linux_x64
to enable MATLAB to find the libraries, and launch MATLAB from the terminal. In some cases (MATLAB before 2013?) you might have to launch MATLAB using something similar to this : 
LD_PRELOAD=/usr/lib/libstdc++.so.6 matlab
to force it to run using the system default version of the C++ Standard Library (otherwise MATLAB might use its own version, which might be too old)...
- In MATLAB, go to File\Set Path...\Add Folder... and add this folder as well as linux_x64 folder.
- Run sivia_easibex.m to test. If you get errors, close MATLAB, delete the provided linux_x64 folder and follow the instructions in the Makefile.
- Check i_Add.m and the other files for usage information.

Mac : 
- Type in a terminal something similar to : 
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:~/EASIBEX-MATLAB-master/mac
to enable MATLAB to find the libraries, and launch MATLAB from the terminal.
- In MATLAB, go to File\Set Path...\Add Folder... and add this folder as well as mac folder.
- Run sivia_easibex.m to test. If you get errors, close MATLAB, delete the provided mac folder and follow the instructions in the Makefile.
- Check i_Add.m and the other files for usage information.

Check also http://www.ensta-bretagne.fr/lebars/easibex_matlab.pdf for more information.

IBEX 2.1.10 was used to build the provided libraries.
Tested on Windows 8 64 bit using MATLAB R2014a, Ubuntu 10.10 64 bit using MATLAB R2010b, iMac OS X Yosemite 10.10.3 using MATLAB R2013b.
