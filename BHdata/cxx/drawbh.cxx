#include <string>
#include <uftools.h>
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TAxis.h"

#ifdef NOROT
#define BRANCH 6
#else
#define BRANCH 7
#endif

std::string label(float m[2]){
  return "M_{BH1}"+to<std::string>(m[0])+"; M_{BH2}"+to<std::string>(m[1]);
}

int main()
{
#ifdef DRAWE
  std::string fl[BRANCH];
#ifdef NOROT
  std::string dat[BRANCH]={"040-040","040-020","020-020","010-010","010-002","010-005"};
  for (int i=0;i<BRANCH;i++) fl[i]="run-"+dat[i]+"-1mil-nonrot-bhpar.root";
#else
  std::string dat[BRANCH]={"040-040","040-020","020-020","010-010","010-002","010-005","010-001"};  
  for (int i=0;i<BRANCH;i++) fl[i]="run-"+dat[i]+"-1mil-bhpar.root";
#endif  
#endif
#ifdef DRAWL
  for (int i=0;i<BRANCH;i++) fl[i]="run-"+dat[i]+"-1mil-bh.root";
#endif
  std::string ll[BRANCH];
  float mbh[7][2]={{0.04,0.04},{0.04,0.02},{0.02,0.02},{0.01,0.01},{0.01,0.002},{0.01,0.005},{0.01,0.001}};
  for (int i=0;i<BRANCH;i++) ll[i]=label(mbh[i]);
  TFile **ff=new TFile*[BRANCH];
  TTree **tt=new TTree*[BRANCH];
  TGraph **gg=new TGraph*[BRANCH];
  Double_t **a=new Double_t*[BRANCH];
  Double_t **t=new Double_t*[BRANCH];
  TCanvas c1;
  TMultiGraph *gm=new TMultiGraph();
#ifdef NOROT  
  TLegend *tl=new TLegend(0.60,0.67,0.89,0.89);
#else
  TLegend *tl=new TLegend(0.60,0.13,0.89,0.38);
#endif  
  tl->SetLineColor(0);
  tl->SetFillColor(0);
#ifdef DRAWE
#ifdef NOROT  
  gm->SetTitle("Non-rotating models;t;e");
#else
  gm->SetTitle("Rotating models;t;e");
#endif  
#endif
#ifdef DRAWL
  gm->SetTitle("Angular momentum evolution of MBHs;t;Log(L)");
#endif
  for (int i=0;i<BRANCH;i++)
  {
    ff[i]=new TFile(fl[i].c_str(),"update");
    ff[i]->cd();
#ifdef DRAWE
    tt[i]=(TTree*)gDirectory->Get("BHpars");
    tt[i]->Draw("e:t","t>30","goff");
#endif
#ifdef DRAWL
    tt[i]=(TTree*)gDirectory->Get("BH1");
    tt[i]->Draw("log10(Lr):time_cur","time_cur>30","goff");
#endif
    a[i]=tt[i]->GetV1();
    t[i]=tt[i]->GetV2();
#ifdef DRAWL
    Int_t n=tt[i]->GetEntries("time_cur>30");
#endif
#ifdef DRAWE
    Int_t n=tt[i]->GetEntries("t>30");
#endif
    gg[i]=new TGraph(n,t[i],a[i]);
    gg[i]->SetLineColor((i==4?45:i+1));
    gg[i]->SetFillColor(0);
#ifdef DRAWE
    gg[i]->GetYaxis()->SetRange(0,1);
#endif
#ifdef DRAWL
    gg[i]->GetYaxis()->SetRange(-7.5,-3.5);
#endif
    gm->Add(gg[i]);
    tl->AddEntry(gg[i],ll[i].c_str());
  }
#ifdef DRAWE
  gm->SetMaximum(1);
  gm->SetMinimum(0);
#endif
#ifdef DRAWL
  gm->SetMaximum(-3.5);
  gm->SetMinimum(-7.5);
#endif
  gm->Draw("AL");
  gPad->Modified();
  gm->GetXaxis()->SetTitleOffset(0.5);
  gm->GetXaxis()->SetTitleSize(0.05);
  gm->GetYaxis()->SetTitleOffset(0.5);  
  gm->GetYaxis()->SetTitleSize(0.05);
  gPad->Update();
  tl->Draw();
#ifdef DRAWE
#ifdef NOROT
  c1.Print("/home/lwang/Dropbox/Datas/BHdata/figures/1et_nor.eps");
  c1.Print("/home/lwang/Dropbox/Datas/BHdata/figures/1et_nor.pdf");
#else
  c1.Print("/home/lwang/Dropbox/Datas/BHdata/figures/1et.eps");
  c1.Print("/home/lwang/Dropbox/Datas/BHdata/figures/1et.pdf");
#endif  
#endif
#ifdef DRAWL
  c1.Print("/home/lwang/Dropbox/Datas/BHdata/figures/1Lt.eps");
  c1.Print("/home/lwang/Dropbox/Datas/BHdata/figures/1Lt.pdf");
#endif
}
