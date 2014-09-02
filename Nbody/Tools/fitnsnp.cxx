#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <initial.h>

#include <TFile.h>
#include <nbodyvfit.h>
#include <TTree.h>
#include <TGraph.h>
#include <TF1.h>

int main(int argc, char *argv[])
{
  pars_initial init(".fitnsnp_config");
  init.add("hfm","hfm list file directory","hfmlst");
  init.add("file","store file","nsfit.root");
  init.add("vf","v4 or v0",(int)0);
  init.initial(argc,argv);

  ifstream f(init.gets("hfm").c_str());
  if (!f.is_open()) { std::cerr<<"Error: File not found!\n"; return 0;}
  nbodyvfit *nv=new nbodyvfit("nsnpfit",init.gets("file"),0);
  nv->vsigma=0;
  nv->vserr=0;
  nv->h=0;
  nv->herr=0;
  nv->m1=0;
  nv->p1=0;

  TF1 *lf=new TF1("line","[0]+[1]*x",0,2000);
  
  while (1){
    std::string tmp;
    Double_t nbr,npr;
    f>>tmp;
    f>>nv->ns;
    f>>nv->rbar;
    f>>nbr;
    f>>npr;
    if (init.geti("vf")==4) {
      f>>nv->m1;
      f>>nv->p1;
    }
    else {
      nv->m1=0;
      nv->p1=0;
    }
    f>>nv->type;
    if (f.eof()) break;
    nv->nb=nv->ns*nbr;
    nv->np=nv->ns*npr;
    
    TFile *f=new TFile((tmp+"/hfm.root").c_str(),"update");
    TTree *tr=0;
    f->GetObject("hfm",tr);
    if (!tr) {
      std::cerr<<"Error: tree not exist\n";
      continue;
    }
    Int_t num=tr->Draw("t:np/ns","","goff");
    Double_t *t=tr->GetV1();
    Double_t *nps=tr->GetV2();
    TGraph *tg=new TGraph(num,t,nps);
    tg->Fit("line","R0");
    TF1 *fit=tg->GetFunction("line");
    //vcut->offset======================================//
    nv->vcut=fit->GetParameter(0);
    //vmax->slope=======================================//
    nv->vcerr=fit->GetParError(0);
    nv->vmax=fit->GetParameter(1);
    nv->vmerr=fit->GetParError(1);
    nv->chi2=fit->GetChisquare();
    nv->Fill();
  }
  nv->Write("",TObject::kOverwrite);
  return 0;
}
