#include "uftools.h"
#include <iostream>
#include <string>
#include "TFile.h"
#include "nbodysingle.h"
#include "nbodyscr.h"
#include "initial.h"

int main(int argc, char* argv[])
{
  pars_initial opt(".test_single.config");
  opt.add("nstar","number of initial stars", (int)1000);
  opt.add("nplanet","number of initial planets", (int)1000);
  opt.add("nbin","number of initial binarys",(int)500);
  opt.initial(argc,argv);
  nbodysingle single;
  if (single.LoadFile("test_single_0.root"))
  {
    single.setinit(opt.get<int>("nstar"),opt.get<int>("nplanet"),opt.get<int>("nbin"));
    single.Fillscr("test_scr.root");
    std::cout<<"Finished\n";
  }
  return 0;
}
