#C++ library
#ROOT library

MYCFLAGS =-I$(shell echo ~)/include
CXXEXTRALIBS	+=-L$(shell echo ~)/lib -linitial

FEXTRALIBS	+= 

FSOURCE 	=$(shell ls *.f)
FOBJECTS = $(FSOURCE:.f=)

FD= gfortran

all: $(FOBJECTS) 

$(FOBJECTS): %: %.f
	$(FD) $(FEXTRALIBS) $< -o $@
	echo $@ >>.mvlist
	sort .mvlist|uniq >.mvlist.tmp
	mv .mvlist.tmp .mvlist

install: $(shell cat .mvlist)
	mv -f $(shell uniq .mvlist) ~/bin/

clean:
	rm -f $(FOBJECTS) 
	rm -f .mvlist

