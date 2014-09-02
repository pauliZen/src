FC = gfortran
#FC = gfortran44
#FFLAGS = -g -fbounds-check -O0 -finit-real=nan -fbacktrace -Wall
FFLAGS = -O3 -Wall -ffast-math
#FFLAGS -pg
#CXX = g++ -O -g -fbounds-check -Wall -march=core2
CXX = g++ -O3 -Wall -march=core2
#CXX += pg
CUDA_PATH = /usr/local/cuda
SDK_PATH = /usr/local/cuda_sdk
NVCC = $(CUDA_PATH)/bin/nvcc --host-compilation C++ -Xcompiler "-Wall -O3 -fopenmp" -I $(SDK_PATH)/common/inc/ -I$(shell echo ~)/include
NVCC += -arch sm_20 -Xptxas -dlcm=cg
RUNDIR = .

OBJECTS = $(SOURCE:.f=.o)

all: gpu sse

gpu: gpunb.gpu.o gpupot.gpu.o intgrt.o gpucor.o nbintp.o cnbint.o nbint.o start.o fpoly2a.o adjust.o energy2.o phicor.o cmfirr.o cmfirr2.o checkl2.o kspert.o swap.o scale.o wtime.o cxvpred.o gpuirr.o jpred.o fpcorr2.o repair.o sweep2.o jpred2.o ksres3.o bdata.o output.o nbody6.o input.o
	cp -f gpunb.gpu.o gpunb.o
	cp -f gpupot.gpu.o gpupot.o
	cp -f *.o ../Ncode
	make gpu -C ../Ncode -f ../OUT/Makefile_arc -j4
	mv -f ../Ncode/nbody7 $(RUNDIR)/nbody7r.gpu

sse: gpunb.sse.o gpupot.sse.o intgrt.o gpucor.o nbintp.o cnbint.o nbint.o start.o fpoly2a.o adjust.o energy2.o phicor.o cmfirr.o cmfirr2.o checkl2.o kspert.o swap.o scale.o wtime.o cxvpred.o gpuirr.o jpred.o fpcorr2.o repair.o sweep2.o jpred2.o ksres3.o bdata.o output.o nbody6.o input.o
	cp -f gpunb.sse.o gpunb.o
	cp -f gpupot.sse.o gpupot.o
	cp -f *.o ../Ncode
	make sse -C ../Ncode -f ../OUT/Makefile_arc -j8
	mv -f ../Ncode/nbody7 $(RUNDIR)/nbody7r.sse

cnbint.o: ../GPU2/lib/cnbint.cpp
	$(CXX) -c $^

wtime.o: ../GPU2/lib/wtime.cpp
	$(CXX) -c $^

cxvpred.o: ../GPU2/lib/cxvpred.cpp
	$(CXX) -fopenmp -c $^

gpuirr.o: ../GPU2/irrlib/gpuirr.sse.cpp
	$(CXX) -fopenmp -c $^ -o $@

gpuirr.s: ../GPU2/irrlib/gpuirr.sse.cpp
	$(CXX) -fopenmp -S $^ -o $@

intgrt.o: ../GPU2/intgrt.omp.f
	$(FC) $(FFLAGS) -fopenmp $^ -c -o $@ 

intgrt.s: ../GPU2/intgrt.omp.f
	$(FC) $(FFLAGS) -fopenmp $^ -S -o $@

start.o: ../GPU2/start.omp.F
	$(FC) $(FFLAGS) -fopenmp $^ -c -o $@

#gpunb.gpu.o: ../GPU2/lib/gpunb.reduce.cu
gpunb.gpu.o: ../GPU2/lib/gpunb.velocity.cu
	$(NVCC) $^ -c -o $@

gpupot.gpu.o: ../GPU2/lib/gpupot.gpu.cu
	$(NVCC) $^ -c -o $@

gpunb.sse.o: ../GPU2/lib/gpunb.sse.cpp
	$(CXX) -fopenmp $^ -c -o $@

gpupot.sse.o: ../GPU2/lib/gpupot.sse.cpp
	$(CXX) -fopenmp $^ -c -o $@

bdata.o: bdata.cpp
	$(CXX) $(shell root-config --cflags) $^ -c -o $@

FOBJECTS=gpucor.o nbintp.o nbint.o fpoly2a.o adjust.o energy2.o phicor.o cmfirr.o cmfirr2.o checkl2.o kspert.o swap.o scale.o jpred.o fpcorr2.o repair.o sweep2.o jpred2.o ksres3.o

$(FOBJECTS): %.o:../GPU2/%.f
	$(FC) $(FFLAGS) -fopenmp $^ -c -o $@

clean:
	rm -f *.o
	make -C ../Ncode -f ../OUT/Makefile_arc clean

archive:
	tar -czvf ../GPU2/gpu2.tar.gz ../GPU2	
