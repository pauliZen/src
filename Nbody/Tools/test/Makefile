target: test

FC=gfortran
FFLAGS= -O3 -Wall -ffast-math
SOURCE=findroot.f test.f ran2.f



OBJECT=$(SOURCE:.f=.o)

test: $(OBJECT)
	$(FC) $(FFLAGS) $(OBJECT) -o test

clean: 
	rm *.o test
