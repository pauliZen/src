#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "initial.h"
#include "cuda.h"
#include "cpu_bitmap.h"

#define INF 1E-6
#define CONSTMEMMAXSIZE 65535

//#define _VISUAL

const int xthreadsperblock=32;
const int ythreadsperblock=32;

struct element
{
  float x;
  float y;
  float m;
  __device__ float hit(int tx, int ty, int p)
  {
    float dx=tx-x;
    float dy=ty-y;
    float r2=dx*dx+dy*dy;
    return m*pow(r2+1,(float)p);
  }
};

const int splitbin=CONSTMEMMAXSIZE/sizeof(element)-1;
__constant__ element s[splitbin];

#ifdef _NOVISUAL
__global__ void initial(float *disp)
#endif
#ifdef _VISUAL
__global__ void initial(unsigned char *disp)
#endif
{
  int x=threadIdx.x+blockIdx.x*blockDim.x;
  int y=threadIdx.y+blockIdx.y*blockDim.y;
  int offset=x+y*blockDim.x*gridDim.x;
#ifdef _NOVISUAL
  disp[offset]=0;
#endif
#ifdef _VISUAL
  disp[4*offset] =0;
  disp[4*offset+1] =0;
  disp[4*offset+2] =255;
  disp[4*offset+3] =255;
#endif
}

#ifdef _NOVISUAL
__global__ void kernel(int sbin, int p, float *disp)
#endif
#ifdef _VISUAL
__global__ void kernel(int sbin, int p, unsigned char *disp)
#endif
{
  int x=threadIdx.x+blockIdx.x*blockDim.x;
  int y=threadIdx.y+blockIdx.y*blockDim.y;
  int offset=x+y*blockDim.x*gridDim.x;
  for (int i=0;i<sbin;i++)
  {
    float value=s[i].hit(x,y,p);
    if (value>INF)
    {      
#ifdef _NOVISUAL
      disp[offset] +=value;
#endif
#ifdef _VISUAL
      disp[4*offset+1] +=value;
      disp[4*offset+2] -=value;
#endif
    }
  }
}

int main(int argc, char* argv[])
{
  pars_initial ini(".galaxy_gpu_config");
  ini.add("p","index of r",(float)-1.5);
  ini.add("xbin","bins for x-axis",(int)1024);
  ini.add("ybin","bins for y-axis",(int)1024);
  ini.add("Nsrc","source number",(int)70000);
  ini.add("infile","source file for plot: x y m","source.dat");
#ifdef _NOVISUAL
  ini.add("outfile","output file name","result.dat");
#endif
  ini.initial(argc,argv);

  int nsrc=ini.get<int>("Nsrc");
  int xmax=ini.get<int>("xbin");
  int ymax=ini.get<int>("ybin");
  float p=ini.get<int>("p")/2.0f;
  
  std::ifstream infile(ini.get<std::string>("infile").c_str());
  if (infile.is_open())
  {
    //Measure performance===============================//
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start,0);

    //Begin=============================================//
    //allocate memory===================================//
    element *source=(element*)malloc(sizeof(element)*nsrc);
#ifdef _VISUAL
    CPUBitmap map(xmax,ymax);
    unsigned char* dev_map;
#endif
#ifdef _NOVISUAL
    float *dev_map;
    float *map=(float*)malloc(sizeof(float)*xmax*ymax);
#endif

    //input source data=================================//
    for (int i=0;i<nsrc;i++)
    {
      infile>>source[i].x;
      infile>>source[i].y;
      infile>>source[i].m;
      if (infile.eof())
      {
        nsrc=i+1;
        std::cout<<"Warning: Input file reach end, change number of sources to "<<nsrc<<std::endl;
        break;
      }
    }

    //GPU allocate memory===============================//
#ifdef _VISUAL    
    cudaMalloc((void**)&dev_map,map.image_size());
#endif
#ifdef _NOVISUAL
    cudaMalloc((void**)&dev_map,xmax*ymax*sizeof(float));
#endif

    //generate block and threads number=================//
    dim3 grids(xmax/xthreadsperblock,ymax/ythreadsperblock);
    dim3 threads(xthreadsperblock,ythreadsperblock);

    //initial display memory============================//
    initial<<<grids,threads>>>(dev_map);

    //constant memeory==================================//
    for (int i=0;i<nsrc/splitbin+1;i++)
    {
      int sbin=splitbin;
      if (i==nsrc/splitbin)
      {
        sbin=nsrc%splitbin;
      }
      element *ns=&source[i*splitbin];
      cudaMemcpyToSymbol(s,ns,sizeof(element)*sbin);

      //call kernel function==============================//
      kernel<<<grids,threads>>>(sbin,p,dev_map);
    }

    //copy cpu memory to gpu============================//
#ifdef _NOVISUAL
    cudaMemcpy(map,dev_map,xmax*ymax*sizeof(float),cudaMemcpyDeviceToHost);
#endif
#ifdef _VISUAL
    cudaMemcpy(map.get_ptr(),dev_map,map.image_size(),cudaMemcpyDeviceToHost);
#endif

    //free memory=======================================//
    cudaFree(dev_map);
    free(source);
      
    //cuda record time==================================//
    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime,start,stop);
    std::cout<<"Time to generate: "<<elapsedTime<<" ms\n";
        
    //Output result=====================================//
#ifdef _NOVISUAL
    std::ofstream output(ini.get<std::string>("outfile").c_str());
    for (int j=0;j<ymax;j++)
    {
      for (int i=0;i<xmax;i++)
        output<<map[i+j*xmax]<<"\t";
      output<<std::endl;
    }
    output.close();
    free (map);
#endif
#ifdef _VISUAL
    map.display_and_exit();
#endif
    
  }
  else std::cerr<<"Error: input file unfound!\n";
  return 0;
}
