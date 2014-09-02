CXX=clang++
CPPFLAGS=-g
CPPFLAGS+=-I$(shell echo ~)/include
TFLAGS=-g -I$(shell echo ~)/include -L$(shell echo ~)/lib -linitial

SOURCE=main.cpp ptime.cpp

OBJECT=$(SOURCE:.cpp=.o)

target:	nbodyt

$(OBJECT): %.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

nbodyt: $(OBJECT)
	$(CXX) $(TFLAGS) $(OBJECT) -o nbodyt

clean:
	rm -rf *.o
