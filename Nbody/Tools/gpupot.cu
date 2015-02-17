#include <cstdio>
#include <cassert>
#ifdef CUDA_5
#  include <helper_cuda.h>
#  define CUDA_SAFE_CALL checkCudaErrors
#else
#  include <cutil.h>
#endif
#include "cuda_pointer.h"

#define NTHREAD 64 // 64, 96, 128 or 192; should be same as the one in gpunb.gpu.cu
#define NJBLOCK 28 // 8800GTS/512 has 16

#define NXREDUCE 32 // must be >NJBLOCK
#define NYREDUCE 8

#define NAN_CHECK(val) assert((val) == (val));

#define PROFILE
#ifdef PROFILE
#include <sys/time.h>
static double get_wtime(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + 1.e-6 * tv.tv_usec;
}
#else
static double get_wtime(){
	return 0.0;
}
#endif

static float2 float2_split(double x){
	const int shift = 20;
	float2 ret;
	x *= (1<<shift);
	double xi = (int)x;
	double xf = x - xi;
	ret.x = xi * (1./(1<<shift));
	ret.y = xf * (1./(1<<shift));
	return ret;
}

static __device__ float2 float2_accum(float2 acc, float x){
  float tmp = acc.x + x;
  acc.y -= (tmp - acc.x) - x;
  acc.x = tmp;
  return acc;
}

static  __device__ float2 float2_regularize(float2 acc){
  float tmp = acc.x + acc.y;
  acc.y = acc.y -(tmp - acc.x);
  acc.x = tmp;
  return acc;
}

static __device__ float2 float2_add(float2 a, float2 b){
  float tmp = a.x + b.x;
  a.y -= (tmp - a.x) - b.x - b.y;
  a.x = tmp;
  // a.x = a.x + b.x;
  // a.y = a.y + b.y;
  return a;
}

//from gpunb.gpu.cu=================================//

struct Particle{
	float2 pos[3];
	float mass;
	float pad;

	Particle(double x[3], double m){
		pos[0] = float2_split(x[0]);
		pos[1] = float2_split(x[1]);
		pos[2] = float2_split(x[2]);
		mass = (float)m;

        NAN_CHECK(x[0]);
        NAN_CHECK(x[1]);
        NAN_CHECK(x[2]);
        NAN_CHECK(m);
	}

    Particle(double x1, double x2, double x3, double m){
		pos[0] = float2_split(x1);
		pos[1] = float2_split(x2);
		pos[2] = float2_split(x3);
		mass = (float)m;

        NAN_CHECK(x1);
        NAN_CHECK(x2);
        NAN_CHECK(x3);
        NAN_CHECK(m);
	}
    
	Particle(int){
		pos[0].x = pos[0].y = pos[1].x = pos[1].y = pos[2].x = pos[2].y = mass = pad = 0.f;
	}
	__device__ Particle() {}
};

__global__ void pot_reduce_kernel(
		const int ni,
		const float2 phipart[][NJBLOCK],
        float2 phi[]){
  //thread x * y + block x============================//
  //thread x for NJBLOCK==============================//
	const int xid = threadIdx.x;
	const int yid = threadIdx.y;
	const int bid = blockIdx.x;
    //thread y & block x for active particle============//
	const int iaddr = yid + blockDim.y * bid;

	__shared__ float2 phishare[NYREDUCE][NXREDUCE];

    __syncthreads();
	if(xid < NJBLOCK){
      phishare[yid][xid] = phipart[iaddr][xid];
	}else{
      phishare[yid][xid] = make_float2(0.f,0.f);
	}
    __syncthreads();
	float2 *phis = phishare[yid];
    
#if NXREDUCE==32
	if(xid < 16) phis[xid] = float2_add(phis[xid],phis[xid + 16]);
#endif
	if(xid < 8) phis[xid] = float2_add(phis[xid],phis[xid + 8]);
	if(xid < 4) phis[xid] = float2_add(phis[xid],phis[xid + 4]);
	if(xid < 2) phis[xid] = float2_add(phis[xid],phis[xid + 2]);
	if(xid < 1) phis[xid] = float2_add(phis[xid],phis[xid + 1]);
	
	if(iaddr < ni){
      phi[iaddr] = float2_regularize(phis[0]);
	}
}

__global__ void pot_kernel(
          int ni,                           
          int n,
          Particle *ipbuf,
          Particle *ptcl,
          float2 phipart[][NJBLOCK]){
	int i = NTHREAD * blockIdx.x + threadIdx.x;
    int jbid = blockIdx.y;
    int jstart = (n * (jbid  )) / NJBLOCK;
    int jend   = (n * (jbid+1)) / NJBLOCK;

    Particle ip=Particle();
    if(i<ni) ip = ipbuf[i];
	float2 phii = make_float2(0.f, 0.f);
	for(int j=jstart; j<jend; j+= NTHREAD){
      __shared__ Particle jpbuf[NTHREAD];

      __syncthreads();
      float4 *src = (float4 *)&ptcl[j];
      float4 *dst = (float4 *)jpbuf;
      dst[threadIdx.x]         = src[threadIdx.x];
      dst[NTHREAD+threadIdx.x] = src[NTHREAD+threadIdx.x];
      __syncthreads();

      if(jend-j < NTHREAD) {
#pragma unroll 4        
        for(int jj=0; jj<jend-j; jj++){
			// if(j+jj == i) continue;
			Particle &jp = jpbuf[jj];
			float dx = (jp.pos[0].x - ip.pos[0].x) + (jp.pos[0].y - ip.pos[0].y);
			float dy = (jp.pos[1].x - ip.pos[1].x) + (jp.pos[1].y - ip.pos[1].y);
			float dz = (jp.pos[2].x - ip.pos[2].x) + (jp.pos[2].y - ip.pos[2].y);
			float r2 = dx*dx + dy*dy + dz*dz;
			// if(r2==0.f) continue;
			float pij = jp.mass * rsqrtf(r2);
			// phii = float2_accum(phii, pij);
			if(r2 > 0.f) phii = float2_accum(phii, pij);
		}
      }else{
#pragma unroll 8
        for(int jj=0; jj<NTHREAD; jj++){
			// if(j+jj == i) continue;
			Particle &jp = jpbuf[jj];
			float dx = (jp.pos[0].x - ip.pos[0].x) + (jp.pos[0].y - ip.pos[0].y);
			float dy = (jp.pos[1].x - ip.pos[1].x) + (jp.pos[1].y - ip.pos[1].y);
			float dz = (jp.pos[2].x - ip.pos[2].x) + (jp.pos[2].y - ip.pos[2].y);
			float r2 = dx*dx + dy*dy + dz*dz;
			// if(r2==0.f) continue;
			float pij = jp.mass * rsqrtf(r2);
			// phii = float2_accum(phii, pij);
			if(r2 > 0.f) phii = float2_accum(phii, pij);
		}
      }
      phii = float2_regularize(phii);
	}
	phipart[i][jbid] = phii;
}

static int n;
static cudaPointer <Particle> ptcl;

extern "C" void gpupot_send(
		int nn,
		double m[],
        //		double x[][3],
        double x1[],
        double x2[],
        double x3[]){

	double t0 = get_wtime();
    n = nn;

    int numGPU=0;
    cudaGetDeviceCount(&numGPU);
    assert(numGPU>0);
    cudaSetDevice(0);
  
	int ng = NTHREAD * (n/NTHREAD + (n%NTHREAD ? 1 : 0));

	ptcl.allocate(ng);

	for(int i=0; i<n; i++){
      ptcl[i] = Particle(x1[i], x2[i], x3[i], m[i]);
	}
    for(int i=n; i<ng; i++){
      ptcl[i] = Particle(0);
    }
    ptcl.htod(ng);
    double t1 = get_wtime();
#ifdef PROFILE
	fprintf(stderr, "gpupot_send: %f sec\n", t1 - t0);
#endif
}

extern "C" void gpupot_send_3(
		int nn,
		double m[],
		double x[][3]){

	double t0 = get_wtime();
    n = nn;

    int numGPU=0;
    cudaGetDeviceCount(&numGPU);
    assert(numGPU>0);
    cudaSetDevice(0);
  
	int ng = NTHREAD * (n/NTHREAD + (n%NTHREAD ? 1 : 0));

	ptcl.allocate(ng);

	for(int i=0; i<n; i++){
      ptcl[i] = Particle(x[i], m[i]);
	}
    for(int i=n; i<ng; i++){
      ptcl[i] = Particle(0);
    }
    ptcl.htod(ng);
    double t1 = get_wtime();
#ifdef PROFILE
	fprintf(stderr, "gpupot_send: %f sec\n", t1 - t0);
#endif
}

extern "C" void gpupot_send_float(
		int nn,
		float m[],
		float x1[],
		float x2[],
		float x3[]){

	double t0 = get_wtime();
    n = nn;

    int numGPU=0;
    cudaGetDeviceCount(&numGPU);
    assert(numGPU>0);
    cudaSetDevice(0);
  
	int ng = NTHREAD * (n/NTHREAD + (n%NTHREAD ? 1 : 0));

	ptcl.allocate(ng);

    printf("m,x %f %f %f %f\n",m[0],x1[0],x2[0],x3[0]);

	for(int i=0; i<n; i++){
      ptcl[i] = Particle((double)x1[i], (double)x2[i], (double)x3[i], (double)m[i]);
	}
    for(int i=n; i<ng; i++){
      ptcl[i] = Particle(0);
    }
    ptcl.htod(ng);
    double t1 = get_wtime();
#ifdef PROFILE
	fprintf(stderr, "gpupot_send: %f sec\n", t1 - t0);
#endif
}

extern "C" void gpupot(
        int ni,
        int list[],
		double pot[]){

	double t0 = get_wtime();

    cudaPointer <float2[NJBLOCK]> phipart;
    cudaPointer <Particle> ibuf;
    cudaPointer <float2> phi;

	int ng = NTHREAD * (n/NTHREAD + (n%NTHREAD ? 1 : 0));
	int nig = NTHREAD * (ni/NTHREAD + (ni%NTHREAD ? 1 : 0));

	phi.allocate(nig);
    phipart.allocate(nig);
    ibuf.allocate(nig);

    for(int i=0; i<ni; i++) {
      ibuf[i] = ptcl[list[i]];
    }
    for(int i=ni; i<nig; i++) {
      ibuf[i] = Particle(0);
    }
    
    ibuf.htod(nig);

	dim3 grid(ng/NTHREAD, NJBLOCK, 1);
	dim3 threads(NTHREAD, 1, 1);

	pot_kernel <<<grid, threads>>> (ni, n, ibuf, ptcl, phipart);

    
    const int ni8 = 1 + (ni-1) / NYREDUCE;
    dim3 rgrid (ni8, 1, 1);
    dim3 rthreads(NXREDUCE, NYREDUCE, 1);
    pot_reduce_kernel <<< rgrid, rthreads >>> (ni, phipart, phi);

    phi.dtoh(ni);

    for(int i=0; i<ni; i++){
      pot[i] = (double)phi[i].x + (double)phi[i].y;
	}

    phi.free();
    phipart.free();
    ptcl.free();
    ibuf.free();

	double t1 = get_wtime();
#ifdef PROFILE
	fprintf(stderr, "gpupot: %f sec\n", t1 - t0);
#endif
}
