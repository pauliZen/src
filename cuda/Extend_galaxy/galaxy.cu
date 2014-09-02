#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "initial.h"
#include "cuda.h"
#include "cpu_bitmap.h"

const int xthreadsperblock=16;
const int ythreadsperblock=16;

struct element
{
  float x;
  float y;
  float m;
};

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
__global__ void kernel(element *src, int p, float *disp)
#endif
#ifdef _VISUAL
__global__ void kernel(element *src, int p, unsigned char *disp)
#endif
{
  int x=threadIdx.x+blockIdx.x*blockDim.x;
  int y=threadIdx.y+blockIdx.y*blockDim.y;
  int offset=x+y*blockDim.x*gridDim.x;
  __shared__ float shared[xthreadsperblock][ythreadsperblock];
  shared[threadIdx.x][threadIdx.y]=src->m*pow((float)((x-src->x)*(x-src->x)+(y-src->y)*(y-src->y)+1),(float)p/2.0f);
  __syncthreads();
#ifdef _NOVISUAL
  disp[offset] +=shared[threadIdx.x][threadIdx.y];
#endif
#ifdef _VISUAL
  disp[4*offset+1] +=shared[threadIdx.x][threadIdx.y];
  disp[4*offset+2] -=shared[threadIdx.x][threadIdx.y];
#endif
  __syncthreads();
}

int main(int argc, char* argv[])
{
  pars_initial ini(".galaxy_gpu_config");
  ini.add("p","index of r",(int)-2);
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
  int p=ini.get<int>("p");
  
  std::ifstream infile(ini.get<std::string>("infile").c_str());
  if (infile.is_open())
  {
    //Measure performance===============================//
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start,0);

    //Begin=============================================//
    element *dev_src;
    element *source=(element*)malloc(sizeof(element)*nsrc);

#ifdef _VISUAL
    CPUBitmap map(xmax,ymax);
    unsigned char* dev_map;
#endif
#ifdef _NOVISUAL
    float *dev_map;
    float *map=(float*)malloc(sizeof(float)*xmax*ymax);
#endif

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
    
    //    for (int i=0;i<xmax*ymax;i++)
    //      map[i]=0;
#ifdef _VISUAL    
    cudaMalloc((void**)&dev_map,map.image_size());
#endif
#ifdef _NOVISUAL
    cudaMalloc((void**)&dev_map,xmax*ymax*sizeof(float));
#endif
    cudaMalloc((void**)&dev_src,nsrc*sizeof(element));

    cudaMemcpy(dev_src,source,nsrc*sizeof(element),cudaMemcpyHostToDevice);
    free(source);

    //    cudaMemcpy(dev_map,map,xmax*ymax*sizeof(float), cudaMemcpyHostToDevice);
    
    dim3 grids(xmax/xthreadsperblock,ymax/ythreadsperblock);
    dim3 threads(xthreadsperblock,ythreadsperblock);

    initial<<<grids,threads>>>(dev_map);
    for (int i=0;i<nsrc;i++)
      kernel<<<grids,threads>>>(&dev_src[i],p,dev_map);

#ifdef _NOVISUAL
    cudaMemcpy(map,dev_map,xmax*ymax*sizeof(float),cudaMemcpyDeviceToHost);
#endif
#ifdef _VISUAL
    cudaMemcpy(map.get_ptr(),dev_map,map.image_size(),cudaMemcpyDeviceToHost);
#endif
    
    cudaFree(dev_map);
    cudaFree(dev_src);

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
