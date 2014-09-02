ROOTCFLAGS              =$(shell root-config  --cflags)
ROOTGLIBS               =$(shell root-config  --glibs)

CC=g++ -O3
CCLFLAG=-shared -fPIC
CCFLAG=-c -fPIC
ROOTFLAG =$(ROOTCFLAGS)
ROOTFLAG +=$(ROOTGLIBS)
Libdir=~/lib
Headerdir=~/include

TARGET:	libinitial.so 

libinitial.so: initial.o
	$(CC) $(CCLFLAG) initial.o -o libinitial.so

initial.o: initial.h initial.cpp
	$(CC) $(CCFLAG) initial.h initial.cpp

#librootio.so: rootio.o
#	$(CC) $(CCLFLAG) $(ROOTGLIBS) rootio.o -o librootio.so

#rootio.o: rootio.h rootio.cxx
#	$(CC) $(CCFLAG) $(ROOTCFLAGS) -I./ rootio.h rootio.cxx

install: libinitial.so initial.h uftools.h ptime.h rootio.h
	mv libinitial.so $(Libdir)
	ln -sf $(shell pwd)/initial.h $(Headerdir)/initial.h
	ln -sf $(shell pwd)/uftools.h $(Headerdir)/uftools.h
	ln -sf $(shell pwd)/ptime.h $(Headerdir)/ptime.h
#	ln -sf $(shell pwd)/rootio.h $(Headerdir)/rootio.h

clean:
	rm -f *.o *.so *.gch
