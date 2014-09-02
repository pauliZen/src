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
CXX= clang++ -g  -Wall -DDEBUG

## Library -------------------------------------------#
MYCFLAGS =-I$(shell echo ~)/include
EXTRALIBS    +=-L$(shell echo ~)/lib -linitial

## Flag ----------------------------------------------#
CXXFLAGS = $(MYCFLAGS)
CXXFLAGS += $(EXTRALIBS)

## Target --------------------------------------------#
libintgrt.so: intgrt.h intgrt.cxx
	$(CXX) -shared -fPIC -I./ intgrt.cxx -o libintgrt.so

test: test.cxx
	$(CXX) $(CXXFLAGS) test.cxx -I./ -L./ -lintgrt -o test

clean:
	rm -f libintgrt.so
	rm -f test
