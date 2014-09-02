testf: testf.f add.cpp
	g++ -c add.cpp -o add.o
	gfortran -c testf.f -o testf.o
	gfortran -lstdc++ add.o testf.o -o testf

clean:
	rm -f *.o