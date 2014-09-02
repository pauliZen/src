#include "initial.h"
#include "particle.h"
#include "file.h"
#include "ptime.h"
#include "params.h"
#include "intgrt.h"
#include "init.h"
#include <cassert>

int main(int argc, char* argv[])
{
  pars_initial init(".nt_config");
  init.add("N","Initial particle number",(int)1000);
  init.add("List","Particle List File (m,x,y,z,vx,vy,vz)","Pdata");
  init.add("Tstep","Maximum Time Step coefficient",(double)0.1);
  init.add("Ttot","Total time for simulation",(double)100.0);
  init.initial(argc,argv);

  assert(init.geti("N")>0);

  //Initial Globular Values===========================//
  int N=init.get<unsigned int>("N");
  particle *List=new particle[N];
  double T=0.0;
  double DTMax=init.get<double>("Tstep");
  double TMax=init.get<double>("Ttot");

  assert(DTMax<TMax);

  //Initial Time measure==============================//
  TList.add(&Tscan);
  TList.add(&Tint);
  
  //Reading Particle Data=============================//
  Tscan.set();
  particle_scanf(init.gets("List").c_str(),List,N);
  Tscan.add();

  //Integrate=========================================//
  Tinit.set();
  particle_scale(N,List);
  Tinit.add();
  
  while(T<=TMax)
  {
    Tint.set();
    particle_intgrt(N,List,DTMAX);
    printf("Time = %lg\n",T);
    TList.print();
  }
  
  printf("End Run\n");
  return 0;
}
