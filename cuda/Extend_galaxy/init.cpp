#include <iostream>
#include <fstream>
#include "initial.h"
#include <cstdlib>
#include <string>
#include <cmath>

#define pi 3.1415926

int main(int argc, char *argv[])
{
  pars_initial ini(".init_galaxy_config");
  ini.add("nsrc","number of sources", (int)70000);
  ini.add("xmax","max bins of x-axis", (int)1024);
  ini.add("ymax","max bins of y-axis", (int)1024);
  ini.add("mmax","max mass",(float)254.0);
  ini.add("randtype","gaus:normal","gaus");
  ini.initial(argc,argv);
  std::ofstream outd("source.dat");

  float x,y;
  float m;
  std::string opt=ini.get<std::string>("randtype");
  int xmax=ini.get<int>("xmax");
  int ymax=ini.get<int>("ymax");
  for (int i=0;i<ini.get<int>("nsrc");i++)
  {
    if (opt=="gaus")
    {
      float r1=(float)rand()/(float)RAND_MAX;
      float r2=(float)rand()/(float)RAND_MAX;
      x=xmax/2.0+xmax/2.0*sqrt(-2.0*log(1-r1))*cos(2*pi*r2);
      y=ymax/2.0+ymax/2.0*sqrt(-2.0*log(1-r1))*sin(2*pi*r2);
    }
    else
    {
      x=(float)rand()/(float)RAND_MAX*ini.get<int>("xmax");
      y=(float)rand()/(float)RAND_MAX*ini.get<int>("ymax");
    }
    m=(float)rand()/(float)RAND_MAX*ini.get<float>("mmax");
    if (x<0||x>xmax||y<0||y>xmax)
      i--;
    else
      outd<<x<<"\t"<<y<<"\t"<<m<<std::endl;
  }
  outd.close();
  return 0;
}
