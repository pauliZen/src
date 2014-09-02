NVCC = nvcc -Xcompiler "-Wall -O3 -lglut"
CPP = g++ -Wall -O3 
#NVCC = nvcc 
NVCC += -arch sm_13 

MYCFLAGS=-I$(shell echo ~)/include -D_VISUAL
EXTRALIBS=-L$(shell echo ~)/lib -linitial

Target=galaxy_simply init
CTarget=init

$(Target): %: %.cu
	$(NVCC) $(MYCFLAGS) $(EXTRALIBS) $^ -o $@

$(CTarget): %: %.cpp
	$(CPP) $(MYCFLAGS) $(EXTRALIBS) $^ -o $@

clean:
	rm -rf $(Target)
