# You will need to build ibex as a shared library (see ibex documentation) to be able to build this library.
# Then, put all the built libraries (intervalx_adapt.so, libibex.so, libsoplex.so, libprim.so.0) in this folder.
# Type : 
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/Ibex/EASIBEX-MATLAB-master
# and you will likely have to launch MATLAB using something similar to this : 
# LD_PRELOAD=/usr/lib64/libstdc++.so.6 matlab
# to force it to run using the system default version of C++ Standard Library (otherwise MATLAB might use its 
# own version, that is very likely to be different from the one used when you built the shared libraries)...

LIB = intervalx_adapt.so

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
