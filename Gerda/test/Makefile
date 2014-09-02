target: test

ROOTCFLAGS		=$(shell root-config  --cflags)
ROOTLIBS		=$(shell root-config  --libs)
ROOTGLIBS		=$(shell root-config  --glibs)

EXTRALIBS	+=$(ROOTLIBS)
EXTRALIBS	+=$(ROOTGLIBS)

CPPFLAGS	+=$(ROOTCFLAGS)
test: test.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) test.cxx -o test

clean:	
	rm -f test
	rm -f datacheck.txt