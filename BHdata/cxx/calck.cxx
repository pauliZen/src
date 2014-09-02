#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "initial.h"
#include "TFile.h"
#include "TGraph.h"
#include "TTree.h"
#include "TAxis.h"
#include "TH2F.h"
#include "TEntryList.h"
#include "uftools.h"
#include "TF1.h"
#include "TMarker.h"
#include <cmath>

struct fname{
  std::string name;
  std::string bh1,bh2;
};

Double_t kx (Double_t *x, Double_t *par)
{
  return x[0]*pow(1-x[0]*x[0],par[0])*(par[1]+par[2]*x[0]);
}

Double_t ke (Double_t *x, Double_t *par)
{
  return 0.5*(x[0]*x[0]-1)/x[0];
}

int main(int argc, char* argv[])
{
  pars_initial pars(".calck_config");
  pars.add("rootdirlist","root directory name list","drawlist.lst");
  pars.add("drawopt","to draw or to store",(bool)0);
  pars.initial(argc,argv);

  std::ifstream of(pars.get<std::string>("rootdirlist").c_str());
  if (!of.is_open())
  {
    std::cerr<<"Error: No drawlist\n";
    return 0;
  }
  fname ftmp;
  float nulll;
  std::vector<fname> flist;
  while (1)
  {
    of>>ftmp.name;
    of>>ftmp.bh1;
    of>>ftmp.bh2;
    of>>nulll;
    if (of.eof()) break;
    flist.push_back(ftmp);
  }
  if (!pars.get<bool>("drawopt"))
  {
    for (unsigned int li=0;li<flist.size();li++)
    {
      TFile f((flist[li].name+"-bhpar.root").c_str(),"update");
      f.cd();
      Double_t t[2],a[2],e[2];
      Double_t da,de,k;
      TTree *bp=(TTree*)gDirectory->Get("BHpars");
      bp->SetBranchAddress("t",&t[0]);
      bp->SetBranchAddress("a",&a[0]);
      bp->SetBranchAddress("e",&e[0]);
      TTree *nt=new TTree("kae","k a and e");
      nt->Branch("t",t,"t[2]/D");
      nt->Branch("a",a,"a[2]/D");
      nt->Branch("e",e,"e[2]/D");
      nt->Branch("da",&da);
      nt->Branch("de",&de);
      nt->Branch("k",&k);
      int tnum=bp->GetEntries()-1;
      Double_t tmp,atmp,etmp;
      bp->GetEntry(0);
      tmp=t[0];
      atmp=a[0];
      etmp=e[0];
      for (int i=1;i<tnum;i++)
      {
        bp->GetEntry(i);
        if (t[0]-tmp<1) continue;
        t[1]=(tmp+t[0])/2.0;
        a[1]=(atmp+a[0])/2.0;
        e[1]=(etmp+e[0])/2.0;
        da=a[0]-atmp;
        de=e[0]-etmp;
        k=-de/da*a[1];
        nt->Fill();
        tmp=t[0];
        atmp=a[0];
        etmp=e[0];
      }
      nt->Write("",TObject::kOverwrite);
      delete bp;
      delete nt;
    }
  }
  else
  {
    TCanvas c1;
    TH2F **tm=new TH2F*[flist.size()];
    TMarker **tmark=new TMarker*[flist.size()];
    TMarker **tmarkfill=new TMarker*[flist.size()];
    Double_t* tmarkx=new Double_t[flist.size()];
    Double_t* tmarky=new Double_t[flist.size()];
    Double_t tmpa[2]={}, tmpe[2]={};
    for (unsigned int li=0;li<flist.size();li++)
      tm[li]=new TH2F(("ke"+to<std::string>((int)li)).c_str(),"ke",100,0,1,100,-0.4,0.6);
    TH2F *tt=new TH2F("ke","ke",100,0,1,100,-0.4,0.6);
    tt->SetTitle("");
    tt->SetXTitle("ecc");
    tt->SetYTitle("K");
    TLegend *tl=new TLegend(0.12,0.73,0.32,0.89);
    tl->SetFillColor(0);
    tl->SetLineColor(0);
    for (unsigned int li=0;li<flist.size();li++)
    {
      TFile f((flist[li].name+"-bhpar.root").c_str(),"update");
      f.cd();
      TTree *nt=(TTree*)gDirectory->Get("kae");
      Double_t k,e[2],a[2];
      nt->SetBranchAddress("e",e);
      nt->SetBranchAddress("k",&k);
      nt->SetBranchAddress("a",&a);
      nt->Draw(">>dlist","t[0]>50","entrylist");
      TEntryList *tlst=(TEntryList*)gDirectory->Get("dlist");
      Int_t etum=tlst->GetN();
      for (int j=0;j<etum;j++)
      {
        nt->GetEntry(tlst->GetEntry(j));
        tm[li]->Fill(e[1],k);
        if (j==30)
        {
          tmpa[0]=a[0];
          tmpe[0]=e[0];
        }
        if (j==etum-1)
        {
          tmpa[1]=a[0];
          tmpe[1]=e[0];
          tmarkx[li]=(tmpe[1]+tmpe[0])/2.0;
          tmarky[li]=(tmpe[0]-tmpe[1])*(tmpa[0]+tmpa[1])/2.0/(tmpa[1]-tmpa[0]);
        }
      }
      tm[li]->SetTitle("");
      tm[li]->SetXTitle("ecc");
      tm[li]->SetYTitle("K");
      tm[li]->SetLineColor(0);
      tm[li]->SetMarkerColor(li+1);
      tm[li]->SetMarkerStyle(8);
      tm[li]->SetMarkerSize(0.4);
      std::string ll="M_{BH1}="+flist[li].bh1+"; M_{BH2}="+flist[li].bh2;
      tl->AddEntry(tm[li],ll.c_str());
      tmark[li]=new TMarker(tmarkx[li],tmarky[li],4);
      tmarkfill[li]=new TMarker(tmarkx[li],tmarky[li],2);
      tmarkfill[li]->SetMarkerColor(li+1);
    }
    tt->SetStats(0);
    tt->Draw();

    TF1 **kf=new TF1*[10];
    Double_t pars[2][5][3]={{{0.731,0.265,0.230},{0.841,0.106,0.534},{0.724,0.053,0.275},{1.271,-0.198,0.445},{1.169,0.102,-0.022}},{{0.822,0.383,0.402},{0.584,0.552,-0.140},{0.381,0.202,-0.120},{0.739,-0.156,0.135},{1.221,-0.180,0.463}}};
    std::string tlv[5]={"v=0.01","v=0.032","v=0.1","v=0.32","v=1.00"};
    std::string tlm[2]={"m_{1}/m_{2}=1","m_{1}/m_{2}=16"};
    TLegend *tf=new TLegend(0.7,0.7,0.89,0.89);
    tf->SetFillColor(0);
    tf->SetLineColor(0);
    for (int ji=0;ji<2;ji++)
      for (int jj=0;jj<5;jj++)
      {
        kf[jj+ji*5]=new TF1("k1",kx,0,1,3);
        kf[jj+ji*5]->SetParameters(pars[ji][jj]);
        kf[jj+ji*5]->SetLineColor(jj+1);
        kf[jj+ji*5]->SetMarkerColor(jj+1);
        kf[jj+ji*5]->SetLineStyle(ji+1);
        tf->AddEntry(kf[jj+ji*5],(tlm[ji]+"; "+tlv[jj]).c_str());
        kf[jj+ji*5]->Draw("Lsame");
      }

    TF1 *kfe=new TF1("k2",ke,0,1,0);
    kfe->SetLineColor(1);
    kfe->SetMarkerColor(1);
    kfe->SetLineStyle(5);
    tf->AddEntry(kfe,"#Delta J = 0");
    kfe->Draw("Lsame");
    tf->Draw();
    
    for (unsigned int li=0;li<flist.size();li++) tm[li]->Draw("same");
    for (unsigned int li=0;li<flist.size();li++)
    {
      tmark[li]->Draw("same");
      tmarkfill[li]->Draw("same");
    }
    
    tl->Draw();

    c1.Print("/home/lwang/Dropbox/Datas/BHdata/figures/ke.png");
    c1.Print("/home/lwang/Dropbox/Datas/BHdata/figures/ke.eps");
    c1.Print("/home/lwang/Dropbox/Datas/BHdata/figures/ke.pdf");
  }

  return 0;
}
