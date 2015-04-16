EASIBEX-MATLAB
==============
Windows : 
- In MATLAB, go to File\Set Path...\Add Folder... and add this folder as well as x86 folder if you use MATLAB 32 bit or x64 folder if you use MATLAB 64 bit.
- Run sivia_easibex.m to test.
- Check i_Add.m and the other files for usage information.

Linux : 
- Follow the instructions in the Makefile.

Mac : 
- Type in a terminal something similar to : 
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:~/EASIBEX-MATLAB-master/mac
to enable MATLAB to find the libraries, and launch MATLAB from the terminal.
- In MATLAB, go to File\Set Path...\Add Folder... and add this folder as well as mac folder.
- Run sivia_easibex.m to test. If you get errors, close MATLAB, delete the content of the provided mac folder and follow the instructions in the Makefile.
- Check i_Add.m and the other files for usage information.
