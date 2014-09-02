//For nreg counts and gpu call timing===============//
#include <iostream>
#include <cstdlib>
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>

#include <initial.h>
#include <uftools.h>

int main(int argc, char **argv) {
  pars_initial init(".sercdata_config");
  init.add("list","data list","fort.lst");
  init.add("save","root for save","serc.root");
  init.initial(argc,argv);

  FILE *fl;
  if ((fl=fopen(init.gets("list").c_str(),"r") ) ==NULL) {
    std::cerr<<"Error:List file cannot open!\n";
    return 0;
  }

  TFile *f=new TFile(init.gets("save").c_str(),"update");
  f->cd();
  TTree *tr=new TTree("data","time data of sendrecv");
  double time,dt;
  int nreg,rank,loop;
  tr->Branch("rank",&rank);
  tr->Branch("loop",&loop);
  tr->Branch("time",&time);
  tr->Branch("nreg",&nreg);
  tr->Branch("dt",&dt);
  
  int ntot;
  fscanf(fl,"%d",&ntot);
  for (int i=0;i<ntot;i++) {
    rank=i;
    char fn[20];
    fscanf(fl,"%s",fn);
    std::cout<<"Read file "<<fn<<std::endl;
    FILE *fd;
    if ((fd=fopen(fn,"r") )==NULL) {
      std::cerr<<"Error: file "<<fn<<" cannot open!\n";
    }
    loop=0;
    while (fgetc(fd) !=EOF) {
      fscanf(fd,"%lf %d %lf",&time,&nreg,&dt);
      loop++;
      if(loop>=ntot) loop=1;
      tr->Fill();
    }
    fclose(fd);
  }
  tr->Write("",TObject::kOverwrite);
  f->Close();
  fclose(fl);
  
  return 0;
}
