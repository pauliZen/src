#include "TTree.h"
#include "TROOT.h"
#include "TFile.h"
#include <initial.h>

#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]) {
  pars_initial init(".nreg_config");
  init.add("name","file name","fort.100");
  init.add("lines","file lines",(int)10000);
  init.add("save","save name","nreg.root");
  init.initial(argc,argv);
  
  FILE *str;
  if ( (str=fopen(init.gets("name").c_str(),"r")) == NULL) {
    std::cerr<<"Erro, Cannot open file "<<init.gets("name")<<std::endl;
    return 0;
  }

  int lines=init.geti("lines");

  int nreg;
  int name;
  double stepr;
  double time;

  TFile *f=new TFile(init.gets("save").c_str(),"create");
  TTree *tnreg=new TTree("tnreg","data of regular blocks");
  tnreg->Branch("nreg",&nreg);
  tnreg->Branch("name",&name);
  tnreg->Branch("stepr",&stepr);
  tnreg->Branch("time",&time);
  for (int i=0;i<lines;i++) {
    fscanf(str,"%d %d %lg %lg",&nreg,&name,&stepr,&time);
    tnreg->Fill();
  }

  tnreg->Write("",TObject::kOverwrite);
  f->Close();

  std::cout<<"Finished\n";
  return 0;
}
