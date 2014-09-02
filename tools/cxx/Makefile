#CC= g++ -Wall -O3
CC= g++ -g -O0

MYCFLAGS =-I$(shell echo ~)/include
CXXEXTRALIBS	+=-L$(shell echo ~)/lib -linitial -lrootio

ROOTCFLAGS              =$(shell root-config  --cflags)
#ROOTLIBS                =$(shell root-config  --libs)
ROOTGLIBS               =$(shell root-config  --glibs)

#CXXEXTRALIBS       +=$(ROOTLIBS)
CXXEXTRALIBS       +=$(ROOTGLIBS)
CXXEXTRALIBS       +=-lSpectrum
CXXEXTRALIBS	+=-fpermissive

CXXSOURCE	=$(shell ls *.cxx)
COBJECTS = $(CXXSOURCE:.cxx=)

all: $(COBJECTS) 

$(COBJECTS): %: %.cxx
	$(CC) $(CXXEXTRALIBS) $(MYCFLAGS) $(ROOTCFLAGS) $< -o $@
	echo $@ >>.mvlist
	sort .mvlist|uniq >.mvlist.tmp
	mv .mvlist.tmp .mvlist

install: $(shell cat .mvlist)
	mv -f $(shell uniq .mvlist) ~/bin/

clean:
	rm -f $(COBJECTS)
	rm -f .mvlist

