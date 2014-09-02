#include "nbodyhfm.h"
#include "nbodyout.h"
#include "initial.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
  pars_initial pars(".trans_hfm_config");
  pars.add("filelist","dir file list","filelist");
  pars.initial(argc,argv);

  ifstream fin(pars.get<std::string>("filelist").c_str());
  if(!fin.is_open())
  {
    std::cerr<<"Error: filelist ("<<pars.get<std::string>("filelist")<<") not found.\n";
    return 0;
  }
  //  std::ios::sync_with_stdio(false);
  std::string ftmp;
  while (1)
  {
    fin>>ftmp;
    if (fin.eof()) break;
    nbodyout nout;
    if (nout.LoadFile(ftmp+"/bdata.root"))
    {
      nbodyhfm nhfm(ftmp+"/hfm.root");
      nout.Fillhfm(nhfm);
      std::cout<<ftmp+"hfm Finished\n";
    }
    else std::cerr<<"Error: cannot load out3 root File "<<ftmp<<std::endl;
  }
  return 0;
}
