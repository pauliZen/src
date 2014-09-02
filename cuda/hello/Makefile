#NVCC = nvcc --host-compilation C++ -Xcompiler "-Wall -O3 -fopenmp" -I $(SDK_PATH)/common/inc/
NVCC = nvcc 
NVCC += -arch sm_13 

hello: hello.cu
	$(NVCC) $^ -o $@

clean:
	rm -rf hello
