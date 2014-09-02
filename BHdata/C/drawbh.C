#include <string>
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "TCanvas.h"

int main()
{
  std::string fl[7]={"run-040-040-1mil-bhpar.root","run-040-020-1mil-bhpar.root","run-020-020-1mil-bhpar.root","run-010-010-1mil-bhpar.root","run-010-002-1mil-bhpar.root","run-010-005-1mil-bhpar.root","run-010-001-1mil-bhpar.root"};
  std::string ll[7]={"4040","4020","2020","1010","1002","1005","1001"};
  TFile **ff=new TFile*[7];
  TTree **tt=new TTree*[7];
  TGraph **gg=new TGraph*[7];
  Double_t **a=new Double_t*[7];
  Double_t **t=new Double_t*[7];
  TCanvas c1;
  TMultiGraph *gm=new TMultiGraph();
  TLegend *tl=new TLegend(0.5,0.7,0.9,0.9);
  tl->SetFillColor(0);
  gm->SetTitle("1/a evolution;t;1/a");
  for (int i=0;i<7;i++)
  {
    ff[i]=new TFile(fl[i].c_str(),"update");
    ff[i]->cd();
    tt[i]=(TTree*)gDirectory->Get("BHpars");
    tt[i]->Draw("over_a:t","","goff");
    a[i]=tt[i]->GetV1();
    t[i]=tt[i]->GetV2();
    Int_t n=tt[i]->GetEntries();
    gg[i]=new TGraph(n,t[i],a[i]);
    gg[i]->SetLineColor(i+1);
    gg[i]->GetYaxis()->SetRange(0,800);
    gm->Add(gg[i]);
    tl->AddEntry(gg[i],ll[i].c_str());
  }
  gm->Draw("AL");
  tl->Draw();
  c1.Print("1at.png");
}
