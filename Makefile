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
