IDIR=../dependencies
CC=/usr/local/Cellar/gcc/5.3.0/bin/g++-5
CFLAGS=-std=c++11 

export CPATH=../dependencies

all: bezier.o beziercubapproximator.o bezierquadapproximator.o bsplineapproximator.o gaussianbackwardinterpolator.o gaussianforwardinterpolator.o hdrimage.o input.o lagrangeinterpolator.o linearinterpolator.o math2.o minmax.o naturalcubicsplineinterpolator.o quadraticinterpolator.o stirlinginterpolator.o main.o
	$(CC) $(CFLAGS) -lfreeimage -arch x86_64 *.o -o interpolation.exe
main.o:
	$(CC) $(CFLAGS) -c main.cpp

bezier.o: 
	$(CC) $(CFLAGS) -c bezier.cpp bezier.h

beziercubapproximator.o: 
	$(CC) $(CFLAGS) -c beziercubapproximator.cpp beziercubapproximator.h

bezierquadapproximator.o: 
	$(CC) $(CFLAGS) -c bezierquadapproximator.cpp bezierquadapproximator.h

bsplineapproximator.o: 
	$(CC) $(CFLAGS) -c bsplineapproximator.cpp bsplineapproximator.h

gaussianbackwardinterpolator.o: 
	$(CC) $(CFLAGS) -c gaussianbackwardinterpolator.cpp gaussianbackwardinterpolator.h

gaussianforwardinterpolator.o: 
	$(CC) $(CFLAGS) -c gaussianforwardinterpolator.cpp gaussianforwardinterpolator.h

hdrimage.o: 
	$(CC) $(CFLAGS) -c hdrimage.cpp hdrimage.h

input.o: 
	$(CC) $(CFLAGS) -c input.cpp input.h

lagrangeinterpolator.o: 
	$(CC) $(CFLAGS) -c lagrangeinterpolator.cpp lagrangeinterpolator.h

linearinterpolator.o: 
	$(CC) $(CFLAGS) -c linearinterpolator.cpp linearinterpolator.h

math2.o: 
	$(CC) $(CFLAGS) -c math2.cpp math2.h

minmax.o:
	$(CC) $(CFLAGS) -c minmax.cpp minmax.h

naturalcubicsplineinterpolator.o:
	$(CC) $(CFLAGS) -c naturalcubicsplineinterpolator.cpp naturalcubicsplineinterpolator.h

quadraticinterpolator.o:
	$(CC) $(CFLAGS) -c quadraticinterpolator.cpp quadraticinterpolator.h

stirlinginterpolator.o:
	$(CC) $(CFLAGS) -c stirlinginterpolator.cpp stirlinginterpolator.h




