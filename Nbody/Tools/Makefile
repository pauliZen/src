## DIR----- ------------------------------------------#
INSTALLDIR=~/bin
HEADERDIR=~/include
LIBDIR=~/lib
###debug--------------------#
#CXX= g++ -O3 -ggdb
#CXX= g++ -O3 -DDEBUG -fopenmp
#CXX= g++ -O0 -g -fbounds-check -Wall -DDEBUG -fopenmp 
#CXX= g++ -O3 -Wall

###release------------------#
CXX= g++ -O3 -Wall -fopenmp


## Library -------------------------------------------#
MYCFLAGS =-I$(shell echo ~)/include
EXTRALIBS    +=-L$(shell echo ~)/lib -linitial -lnb6out3

### root lib----------------------------------------#
ROOTCFLAGS              =$(shell root-config  --cflags)
ROOTGLIBS               =$(shell root-config  --glibs)

#ROOTLIBS       +=-lSpectrum
#ROOTLIBS	+=-fpermissive

## Source --------------------------------------------#
SOURCE	=$(shell ls *.cxx)
OBJECTS = $(SOURCE:.cxx=)

SOURCEP =$(shell ls *.cpp)
OBJECTSP = $(SOURCEP:.cpp=)

HEADER  =$(shell ls *.h)

## Flag ----------------------------------------------#
CXXFLAGS = $(MYCFLAGS)
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(ROOTGLIBS)
CXXFLAGS += $(EXTRALIBS)
CXXFLAGS += $(ROOTLIBS)

CPPFLAGS = $(MYCFLAGS)
CPPFLAGS += $(EXTRALIBS)

## Target --------------------------------------------#
all: $(OBJECTS) $(OBJECTSP)

$(OBJECTSP): %: %.cpp
	$(CXX) $(CPPFLAGS) $< -o $@
	@echo $@ >>.mvlist
	@sort .mvlist|uniq > .mvlist.tmp
	@mv .mvlist.tmp .mvlist

$(OBJECTS): %: %.cxx
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo $@ >>.mvlist
	@sort .mvlist|uniq > .mvlist.tmp
	@mv .mvlist.tmp .mvlist

install: $(shell uniq .mvlist)
	mv -f $(shell uniq .mvlist) $(INSTALLDIR)/

installh: $(HEADER)
	$(foreach name, $(HEADER), ln -sf $(shell pwd)/$(name) $(HEADERDIR)/$(name);)

installlib: libnb6out3
	mv -f libnb6out3.so $(LIBDIR)/

libnb6out3: nb6out3.h nb6out3.cxx
	$(CXX) -shared -fPIC  nb6out3.cxx -o libnb6out3.so

clean:
	rm -f $(OBJECTS)
	rm -rf $(SOURCE:.cxx=.dSYM)
	rm -f .mvlist

