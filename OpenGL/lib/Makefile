CC=g++ -O3
CCLFLAG=-shared -fPIC
CCFLAG=-c -fPIC
Libdir=~/lib
Headerdir=../include

TARGET:	libLoadShaders.so

LoadShaders.o: LoadShaders.cpp
	$(CC) $(CCFLAG) -I$(Headerdir) LoadShaders.cpp -o LoadShaders.o

libLoadShaders.so: LoadShaders.o
	$(CC) $(CCLFLAG) LoadShaders.o -o libLoadShaders.so

clean:
	rm -f *.o *.so *.gch
