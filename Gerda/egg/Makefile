ROOTCFLAGS		=$(shell root-config  --cflags)
ROOTLIBS		=$(shell root-config  --libs)
ROOTGLIBS		=$(shell root-config  --glibs)

EXTRALIBS	+=$(ROOTLIBS)
EXTRALIBS	+=$(ROOTGLIBS)

#CPPFLAGS	+=$(ROOTCFLAGS)
target : hworld


hworld: hworld.cxx
	g++ -Wall -O2 $(EXTRALIBS) $(ROOTCFLAGS) hworld.cxx -o hworld
