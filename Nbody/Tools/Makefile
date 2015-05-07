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
EXTRALIBS    +=-L$(shell echo ~)/lib -linitial -lnb6out3 -lgpupot

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

installlib: libnb6out3 libgpupot
	mv -f libnb6out3.so $(LIBDIR)/
	mv -f libgpupot.so $(LIBDIR)/
	mv -f liblagr.so $(LIBDIR)/

libnb6out3: nb6out3.h nb6out3.cxx
	$(CXX) -shared -fPIC  nb6out3.cxx -o libnb6out3.so

libgpupot: gpupot.cu cuda_pointer.h
#	nvcc -O3 -arch=sm_30 -dc -Xcompiler '-Wall -D CUDA_5 -fPIC -I/usr/local/cuda/samples/common/inc' gpupot.cu -c -o gpupot.so
	nvcc -O3 -Xcompiler '-Wall -D CUDA_5 -fPIC' -shared -o libgpupot.so gpupot.cu -I/usr/local/cuda/samples/common/inc
#	g++ -O3 -shared -fPIC -Wl,-soname,gpupot.so gpupot.o -o gpupot.so -lcuda -lcudart -L/usr/local/cuda/lib64

liblagr: lagr.cpp
	$(CXX) -shared -fPIC lagr.cpp -o liblagr.so $(MYCFLAGS)

clean:
	rm -f $(OBJECTS)
	rm -rf $(SOURCE:.cxx=.dSYM)
	rm -f .mvlist

