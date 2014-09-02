ROOTCFLAGS              =$(shell root-config  --cflags)
ROOTLIBS                =$(shell root-config  --libs)
ROOTGLIBS               =$(shell root-config  --glibs)

EXTRALIBS       +=$(ROOTLIBS)
EXTRALIBS       +=$(ROOTGLIBS)
EXTRALIBS       +=-lSpectrum
EXTRALIBS	+=-fpermissive

#CPPFLAGS       +=$(ROOTCFLAGS)                                              

SOURCE	=$(shell ls *.cxx)
OBJECTS = $(SOURCE:.cxx=)

CC= g++ -Wall -p

all: $(OBJECTS)

$(OBJECTS): %: %.cxx
	$(CC) $(EXTRALIBS) $(ROOTCFLAGS) $< -o $@
	echo $@ >>.mvlist
	sort .mvlist|uniq >.mvlist.tmp
	mv .mvlist.tmp .mvlist

install: $(shell cat .mvlist)
	mv -f $(shell uniq .mvlist) ~/bin/

clean:
	rm -f $(OBJECTS)
	rm -f .mvlist
