#include <initial.h>
#include <uftools.h>
#include <cstdlib>

#include <string>

#include <TFile.h>
#include <TTree.h>

int main(int argc, char **argv) {
  pars_initial init(".transcount_conf");
  init.add("file","data file name","ceper_star.table");
  init.add("out","output file name","cecount.root");
  init.initial(argc,argv);

  FILE *fin;
  if ((fin = fopen(init.gets("file").c_str(),"r") )==NULL) {
    perror("Error: cannot open file !\n");
    exit(1);
  }

  TFile *fout=new TFile(init.gets("out").c_str(),"create");
  TTree *ftree=new TTree("fcount","fraction of encounters per star");
  Int_t ns,np,nb,m1,p1;
  Double_t rbar;
  Int_t type,sfrac[11],pfrac[11],frac0[5][2];
  ftree->Branch("ns",&ns);
  ftree->Branch("np",&np);
  ftree->Branch("nb",&nb);
  ftree->Branch("rbar",&rbar);
  ftree->Branch("m1",&m1);
  ftree->Branch("p1",&p1);
  ftree->Branch("frac0",frac0,"frac0[5][2]/I");
  ftree->Branch("type",&type);
  ftree->Branch("sfrac",sfrac,"sfrac[11]/I");
  ftree->Branch("pfrac",pfrac,"pfrac[11]/I");

  while (!feof(fin)) {
    fscanf(fin,"%d %d %d %lf %d %d",&ns,&np,&nb,&rbar,&m1,&p1);
    if (feof(fin)) break;
    for (int i=0;i<5;i++) {
      fscanf(fin,"%d",&frac0[i][0]);
      fscanf(fin,"%d",&frac0[i][1]);
    }
    for (int i=0;i<15;i++) {
      fscanf(fin,"%d",&type);
      for (int j=0;j<11;j++) fscanf(fin,"%d",&sfrac[j]);
      for (int j=0;j<11;j++) fscanf(fin,"%d",&pfrac[j]);
      ftree->Fill();
    }
  }

  fout->Write("",TObject::kOverwrite);
  
  printf("Finished!\n");

  return 0;
}
