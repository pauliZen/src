#include <cstdlib>
#include <initial.h>
#include <string>

#include <TTree.h>
#include <TFile.h>

int main(int argc, char** argv) {
  pars_initial init(".transstephist_config");
  init.add("file","data file name","fort.120");
  init.add("out","output file name","step.root");
  init.initial(argc,argv);

  FILE *fin;
  if ( (fin = fopen(init.gets("file").c_str(),"r") )==NULL ) {
    perror("Error: data file cannot open!\n");
    exit(1);
  }

  TFile *f=new TFile(init.gets("out").c_str(),"create");
  TTree *tr=new TTree("step","step counts");
  Double_t time,stepm,stepi,stepr;
  Int_t flag,index;
  tr->Branch("time",&time);
  tr->Branch("index",&index);
  tr->Branch("flag",&flag);
  tr->Branch("stepm",&stepm);
  tr->Branch("stepi",&stepi);
  tr->Branch("stepr",&stepr);

  Int_t ifirst,n,ntot;
  while(!feof(fin)) {
    fscanf(fin,"%lf %d %d %d",&time,&ifirst,&n,&ntot);
    flag=1;
    for (int i=1;i<ifirst;i++) {
      fscanf(fin,"%d %lf %lf %lf",&index,&stepm,&stepi,&stepr);
      tr->Fill();
    }
    flag=2;
    for(int i=ifirst;i<=n;i++) {
      fscanf(fin,"%d %lf %lf %lf",&index,&stepm,&stepi,&stepr);
      tr->Fill();
    }
    flag=3;
    for(int i=n+1;i<=ntot;i++) {
      fscanf(fin,"%d %lf %lf %lf",&index,&stepm,&stepi,&stepr);
      tr->Fill();
    }
  }

  f->Write("",TObject::kOverwrite);

  printf("Finished\n");
  return 0;
}

