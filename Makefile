# You will need to build IBEX as a shared library (see IBEX documentation) and download EASIBEX-CPP (rename the folder as 
# interval_adapt) and matrix_lib to be able to build this library (check and modify the content of this Makefile to match 
# your configuration if needed).
#
# Then, put all the built libraries (intervalx_adapt.so/.dylib, libibex.so/.dylib, libsoplex.so/.dylib, libprim.so/.0.dylib) 
# in this folder (.so for Linux, .dylib for Mac, libsoplex and libprim might not be necessary depending on your IBEX 
# version or options).
#
# For Linux, type in a terminal something similar to : 
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/EASIBEX-MATLAB-master
# to enable MATLAB to find the libraries, and launch MATLAB from the same terminal.
# In some cases (MATLAB before 2013?) you might have to launch MATLAB using something similar to this : 
# LD_PRELOAD=/usr/lib64/libstdc++.so.6 matlab
# or 
# LD_PRELOAD=/usr/lib64/libstdc++.so.6:/lib64/libgcc_s.so.1 matlab
# to force it to run using the system default version of the C++ Standard Library (otherwise MATLAB might use its 
# own version, which is likely to be different from the one used when you built the shared libraries)...
#
# For Mac, type in a terminal something similar to : 
# export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:~/EASIBEX-MATLAB-master
# to enable MATLAB to find the libraries, and launch MATLAB from the same terminal.
# In some cases (MATLAB before 2013?) you might have to launch MATLAB using something similar to this : 
# DYLD_INSERT_LIBRARIES=/usr/lib/libstdc++.6.dylib /Applications/MATLAB_R2012a.app/bin/matlab
# or 
# DYLD_INSERT_LIBRARIES=/usr/lib/libstdc++.6.dylib:/usr/lib/libgcc_s.1.dylib /Applications/MATLAB_R2012a.app/bin/matlab
# to force it to run using the system default version of the C++ Standard Library (otherwise MATLAB might use its 
# own version, which is likely to be different from the one used when you built the shared libraries)...
#
# In MATLAB, go to File\Set Path...\Add Folder... and add this folder.
# Run sivia_easibex.m to test. 
# Check i_Add.m and the other files for usage information.

# Change here depending on your OS (.so for Linux, .dylib for Mac).
LIB = intervalx_adapt.so
#LIB = intervalx_adapt.dylib

CC = g++
CFLAGS += -fPIC
#CFLAGS += -g -pg
CFLAGS += -Wno-deprecated -O3 -frounding-math -msse2 -mfpmath=sse -DNDEBUG
#CFLAGS += -Wall
#CFLAGS += -Wextra -Winline

CFLAGS += -I. -I.. -I../interval_adapt -I../matrix_lib -I../ibex/include/ibex -I../soplex/src -I../ibex/include

LDFLAGS += -L../ibex/lib -L../soplex/lib -libex -lsoplex -lprim

default: $(LIB)

iboolean.o: ../interval_adapt/iboolean.cpp ../interval_adapt/iboolean.h
	$(CC) $(CFLAGS) -c $<

interval.o: ../interval_adapt/interval.cpp ../interval_adapt/interval.h
	$(CC) $(CFLAGS) -c $<

box.o: ../interval_adapt/box.cpp ../interval_adapt/box.h
	$(CC) $(CFLAGS) -c $<

rmatrix.o: ../interval_adapt/rmatrix.cpp ../interval_adapt/rmatrix.h
	$(CC) $(CFLAGS) -c $<

imatrix.o: ../interval_adapt/imatrix.cpp ../interval_adapt/imatrix.h
	$(CC) $(CFLAGS) -c $<

intervalx_adapt.o: intervalx_adapt.cpp intervalx_adapt.h
	$(CC) $(CFLAGS) -c $<

$(LIB): intervalx_adapt.o imatrix.o rmatrix.o box.o interval.o iboolean.o
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(LIB) *.o *.obj core *.gch
