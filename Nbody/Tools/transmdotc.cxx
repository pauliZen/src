#include <cstdlib>
#include <initial.h>
#include <string>

#include <TTree.h>
#include <TFile.h>

int main(int argc, char** argv) {
  pars_initial init(".transmdotc_config");
  init.add("file","data file name","fort.130");
  init.add("out","output file name","mdotc.root");
  init.initial(argc,argv);

  FILE *fin;
  if ( (fin = fopen(init.gets("file").c_str(),"r") )==NULL ) {
    perror("Error: data file cannot open!\n");
    exit(1);
  }

  TFile *f=new TFile(init.gets("out").c_str(),"create");
  TTree *tr=new TTree("mdotc","mdot counts");
  Double_t time,dm,tcpu;
  Int_t flag,index,mdotc,kstar;
  tr->Branch("flag",&flag);
  tr->Branch("mdotc",&mdotc);
  tr->Branch("index",&index);
  tr->Branch("dm",&dm);  
  tr->Branch("kstar",&kstar);
  tr->Branch("time",&time);
  tr->Branch("tcpu",&tcpu);

  while(!feof(fin)) {
    fscanf(fin,"%d %d %d %lf %d %lf %lf",&flag,&mdotc,&index,&dm,&kstar,&time,&tcpu);
    tr->Fill();
  }

  f->Write("",TObject::kOverwrite);

  printf("Finished\n");
  return 0;
}
