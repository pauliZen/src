#include <iomanip>
#include <map>
#include <utility>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TLine.h"
#include "TChain.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TLegend.h"

using namespace std;

int main(int argc, char* argv[]) //(element,source)
{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  //Parameters =======================================//

  int numdecay=1;
  int datasr=1;
  bool flagf=1;
  stringstream sstr;

  Int_t npt=5;
  float decayt=164.3;
  float lowlim=3200;
  float uplim=9000;
  float rmax=0;

  string datan="sii";
  string source="S-II";
  string directory="$gerda/data/";
  string dir_plot=directory+"plots/";
  string elename="Bi214";
  string filename=directory+"histograms/";

  map<int, string> seg;
  seg[1]="top";
  seg[2]="mid";
  seg[3]="bottom";
  seg[4]="total";

//choose ===========================================//
  
  if (argc!=1)
  {
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>numdecay;

    sstr.str("");
    sstr.clear();
    sstr<<argv[2];
    sstr>>datasr;

    sstr.str("");
    sstr.clear();
  
    flagf=0;
  }
  else
  {
    while(flagf)
    {
      cout<<"Decay kind:(1.Bi214;2.Bi212)";
      cin>>numdecay;
      if (numdecay==2||numdecay==1)
        flagf=0;
      else 
      {
        flagf=1;
        cout<<"Error"<<endl;
      }
    }

    flagf=1;
    while(flagf)
    {
      cout<<"Source:(1.SII;2.SIII)";
      cin>>datasr;
      if (datasr==1||datasr==2)
        flagf=0;
      else
      {
        flagf=1;
        cout<<"Error"<<endl;
      }
    }
  }
  
  //choose element decay =============================//
  
  if (numdecay==1)
  {
    decayt=1.44*164.3;
    filename +="bi214.";
    elename="Bi214";
    dir_plot +="bi214/";
    uplim=8000;
  }
  else if(numdecay==2)
  {
    decayt=10;
    filename +="bi212.";
    elename="Bi212";
    dir_plot +="bi212/";
    uplim=9000;
  }
  
  //choose source ====================================//
  if (datasr==1)
    datan="sii";
  else if (datasr==2)
  {
    datan="siii";
    source +="I";
  }
  

  filename +=datan+".root";
  dir_plot +=datan+"/";

  //File input =======================================//
  
  TFile* finput = new TFile(filename.c_str());
  finput->cd();
  
  string namestr;
  string decaytime;  
  stringstream order;
  order<<decayt;
  decaytime=order.str()+" #mus";
  order.str("");
  
  TH1F *hecore = (TH1F*)  gDirectory->Get("hecore")->Clone();
  TH1F *hecores = (TH1F*) gDirectory->Get("hecores")->Clone();
  TH1F *hecore_first = (TH1F*) gDirectory->Get("hecore_first")->Clone();
  TH1F *hecore_second = (TH1F*) gDirectory->Get("hecore_second")->Clone();
  TH1F *hecore_seconds = (TH1F*) gDirectory->Get("hecore_seconds")->Clone();
  TH1F *hetimediff= (TH1F*) gDirectory->Get("hevttime_diff")->Clone();
  TH1F *htimediff= (TH1F*) gDirectory->Get("htime_diff")->Clone();

  TH1F* hecoret = new TH1F[npt];
  TH1F** hecorets = new TH1F*[npt];

  for(int i=0;i<npt;++i)
  {
    hecorets[i] = new TH1F[4];
  }
    
  for (int i=1;i<npt+1;i++)
  {
    for (int k=1;k<5;k++)
    {
      order<<i;
      order<<"_";
      order<<seg[k];
      namestr=order.str();
      TH1F *f2= (TH1F*) gDirectory->Get(("hecore_secondts"+namestr).c_str())->Clone();;
      hecorets[i-1][k-1]=*f2;
      order.str("");
      hecorets[i-1][k-1].Rebin(100);
    }
    order<<i;
    namestr=order.str();
    TH1F *f1 = ((TH1F*) gDirectory->Get(("hecore_secondt"+namestr).c_str())->Clone());
    hecoret[i-1]=*f1;
    order.str("");
    hecoret[i-1].Rebin(100);
  }

  hecore->Rebin(10);
  hecores->Rebin(10);
  
  hecore_first->Rebin(100);
  hecore_second->Rebin(100);
  hecore_seconds->Rebin(100);

  //plot total with single event =====================//
  
  TCanvas* c1 = new TCanvas("c1","c1",10,10,900,600);
  c1->cd();
  gPad->SetLogy();
  hecore->GetXaxis()->SetTitle("Ecore [keV]");
  hecore->GetYaxis()->SetTitle("Entries/10keV");
  hecore->SetTitle((source+" events").c_str());
  hecore->Draw();
  hecores->SetLineColor(kRed);
  hecores->Draw("same");
  TLegend* lone = new TLegend(0.5,0.6,0.85,0.75);
  lone->SetFillStyle(0);
  lone->AddEntry(hecore,"all events with #Delta E < 10 keV", "l");
  lone->AddEntry(hecores,"single-segment events with #Delta E < 10 keV ", "l");
  lone->Draw();
  c1->Update();
  c1->Print((dir_plot+"ecore_ss.eps").c_str());
  c1->Delete();

  //time differece plots =============================//
  TCanvas* c2 = new TCanvas("c2","c2",10,10,900,600);
  c2->cd();
  gPad->SetLogx();
  hetimediff->GetXaxis()->SetTitle("Time Difference [#mus]");
  hetimediff->GetYaxis()->SetTitle("Entries");
  hetimediff->SetTitle((source+" consecutive events time difference").c_str());
  bool notfind=1;
  int findcount=0;
  float timecut=0;
  while(notfind)
  {
    findcount++;
    float now=hetimediff->GetBinContent(findcount);
    if(now<=5)
      continue;
    else
    {
      timecut=findcount-1;
      sstr.str("");
      sstr.clear();
      sstr<<findcount-1;
      notfind=0;
    }
 }
  TLegend* info=new TLegend(0.3,0.75,0.85,0.83);
  info->SetFillStyle(0);
  info->AddEntry(hetimediff,(" minimal value of time difference in "+source+" is "+sstr.str()+" #mus").c_str());
  sstr.str("");
  sstr.clear();
  
  if(datasr==1)
    hetimediff->SetAxisRange(10,10000,"X");
  else if(datasr==2)
    hetimediff->SetAxisRange(0,10000,"X");
  rmax=hetimediff->GetMaximum()*1.5;
  hetimediff->SetAxisRange(0,rmax,"Y");
  hetimediff->Draw();
  info->Draw();
  c2->Update();
  c2->Print((dir_plot+datan+"_timediff.eps").c_str());

  htimediff->SetAxisRange(0,10000,"X");
  htimediff->Draw();
  c2->Print((dir_plot+datan+"_timediff_origin.eps").c_str());
  c2->Delete();

  //different time cutoff with total signle plots ====//
  
  TCanvas* c3 = new TCanvas("c3","c3",10,10,900,600);
  c3->cd();
  gPad->SetLogy();
  hecore_second->SetTitle((elename+" events").c_str());
  hecore_second->GetXaxis()->SetTitle("Ecore [keV]");
  hecore_second->GetYaxis()->SetTitle("Entries/100keV");
  hecore_second->SetLineWidth(2);
  hecore_second->SetMinimum(0.1);
  for (int k=0;k<5;k++)
  {
    order<<k+1;
    namestr=order.str();
    hecore_second->Draw();
    hecoret[k].SetLineColor(kBlue);
    hecoret[k].SetLineWidth(4);
    hecoret[k].Draw("same");
    hecorets[k][3].SetLineColor(kRed);
    hecorets[k][3].SetLineWidth(1);
    hecorets[k][3].Draw("same");
    TLegend* ltwo = new TLegend(0.4,0.55,0.85,0.80);
    ltwo->SetFillStyle(0);
    ltwo->AddEntry(hecore_second,(elename+" consecutive events").c_str(),"l");
    ltwo->AddEntry(&hecoret[k],(namestr+"x"+decaytime+" time difference events").c_str(),"l");
    ltwo->AddEntry(&hecorets[k][3],(namestr+"x"+decaytime+" and single-segment events").c_str(),"l");
    ltwo->Draw();
    c3->Update();
    c3->Print((dir_plot+elename+"_"+datan+"_totsg_td"+namestr+".eps").c_str());
    order.str("");
    hecore_second->GetXaxis()->SetRange(lowlim/100,uplim/100);
    rmax=hecore_second->GetMaximum()*1.5;
    hecore_second->SetAxisRange(0.5,rmax,"Y");
    hecore_second->Draw();
    hecoret[k].Draw("same");
    hecorets[k][3].Draw("same");
    ltwo->Draw();
    c3->Update();
    c3->Print((dir_plot+"l_"+elename+"_"+datan+"_totsg_td"+namestr+".eps").c_str());
  }
  c3->Delete();
  
  //all time cutoff plots ============================//

  TCanvas* c4 = new TCanvas("c4","c4",10,10,900,600);
  c4->cd();
  
  gPad->SetLogy();
  hecore_second->SetTitle((source+" Coincidence events under different #Delta T").c_str());
  hecore_second->GetXaxis()->SetTitle("Ecore [keV]");
  hecore_second->GetYaxis()->SetTitle("Entries/100keV");
  hecore_second->SetLineWidth(2);
  hecore_second->SetMinimum(0.1);
  hecore_second->Draw();
 
  for (int k=4;k>=0;k--)
  {
    hecorets[k][3].SetLineColor(k+2);
    hecorets[k][3].SetLineWidth(k+1);
    hecorets[k][3].Draw("same");
  }
  TLegend* ltwo = new TLegend(0.4,0.55,0.85,0.80);
  ltwo->SetFillStyle(0);
  ltwo->AddEntry(hecore_second,(elename+" consecutive events").c_str(),"l");
  for (int k=0;k<5;k++)
  {
    order<<k+1;
    namestr=order.str();
    ltwo->AddEntry(&hecorets[k][3],(namestr+"x"+decaytime+" and single-segment").c_str(),"l");
    order.str("");
  }
  ltwo->Draw();
  c4->Update();
  c4->Print((dir_plot+elename+"_"+datan+"_alltd.eps").c_str());
  hecore_second->GetXaxis()->SetRange(lowlim/100,uplim/100);
  rmax=hecore_second->GetMaximum()*1.5;
  hecore_second->SetAxisRange(0.5,rmax,"Y");
  hecore_second->Draw();
  for (int k=4;k>=0;k--)
  {
    hecorets[k][3].Draw("same");
  }
  ltwo->Draw();
  c4->Update();
  c4->Print((dir_plot+"l_"+elename+"_"+datan+"_alltd.eps").c_str());
  c4->Delete();
  
  //different part and time cutoff plots =============//
  
  TCanvas* c5 = new TCanvas("c5","c5",10,10,900,600);
  c5->cd();
  for (int k=0;k<5;k++)
  {
    gPad->SetLogy(); 
    hecorets[k][3].SetTitle((elename+" events in different part of detector").c_str());
    hecorets[k][3].GetXaxis()->SetTitle("Ecore [keV]");
    hecorets[k][3].GetYaxis()->SetTitle("Entries/100keV");
    hecorets[k][3].SetLineWidth(4);
    hecorets[k][3].SetMinimum(0.1);
    hecorets[k][3].SetLineColor(1);
    hecorets[k][3].Draw();
    for (int s=0;s<3;s++)
    {
      hecorets[k][s].SetLineWidth(3-s);
      hecorets[k][s].SetLineColor(s+2);
      hecorets[k][s].Draw("same");
    }
    
    TLegend* ltwo = new TLegend(0.4,0.55,0.85,0.8);
    ltwo->SetFillStyle(0);
    order<<k+1;
    namestr=order.str();
    order.str("");
    for (int s=0;s<4;s++)
    {
      ltwo->AddEntry(&hecorets[k][s],(namestr+"x"+decaytime+" and single-segment in "+seg[s+1]+" part").c_str(),"l");
    }
    ltwo->Draw();
    c5->Update();
    c5->Print((dir_plot+elename+"_"+datan+"_segs_td"+namestr+".eps").c_str());

    gPad->SetLogy(0);
    hecorets[k][3].GetXaxis()->SetRange(lowlim/100,uplim/100);
    rmax=hecorets[k][3].GetMaximum()*2;
    hecorets[k][3].SetAxisRange(0,rmax,"Y");
    hecorets[k][3].Draw();
    for(int s=0;s<3;s++)
    {
      hecorets[k][s].Draw("same");
    }
    ltwo->Draw();
    c5->Update();
    c5->Print((dir_plot+"l_"+elename+"_"+datan+"_segs_td"+namestr+".eps").c_str());
  }
  c5->Delete();
  
  //End ==============================================//
  
  hecore->Delete();
  hecores->Delete();
  hecore_first->Delete();
  hecore_second->Delete();
  hecore_seconds->Delete();
  hecoret->Delete();
  for(int i=0;i<5;i++)
    hecorets[i]->Delete();

  return 0;
  
}


