#include <iostream>
#include <string>
#include <initial.h>
#include <rootio.h>
#include <uftools.h>
#include "TROOT.h"
#include "TFile.h"

int main (int argc, char ** argv) {
  pars_initial init(".transroot_config");
  init.add("conf","configure file format: Nbranch format1 format2 ...","trans.conf");
  init.add("save","root file for save","test.root");
  init.add("read","read text file","test");
  init.initial(argc,argv);

  TFile *f=new TFile(init.gets("save").c_str(),"update");
  FILE *fin;
  FILE *fconf;
  fin=fopen(init.gets("read").c_str(),"r");
  fconf=fopen(init.gets("conf").c_str(),"r");
  TreeDataFormat conf(fconf);
  ToTree(fin,f,conf,"test","test",'n');

  f->Close();
  return 0;
}
