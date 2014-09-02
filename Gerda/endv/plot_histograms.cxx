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

int main(int argc, char* argv[])
{
  //-------------------------------------------------//
  //Reset ROOT and connect tree file-----------------//
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  //-------------------------------------------------//
  //choose ------------------------------------------//

  //-------------------------------//
  //parameters---------------------//

  const int segnum=18;
  const int partnum=3;
  const int hnum=12;
  float energydiff=10;
  float Exenergydiff=1000;
  int datasr=1;
  stringstream sstr;

  //-----------------//
  //custom name------//

  string directory="$gerda/data/";
  string datan="sii";
  string source="S-II";
  string dir_his=directory+"histograms/";
  string dir_plot=directory+"plots/";
  string filename=dir_his+"h.";

  map<int, string> part;
  part[0]="bottom";
  part[1]="mid";
  part[2]="top";

  map<int, string> hname;
  hname[0]="total events";
  hname[1]="total single-segment events";
  hname[2]="abnormal events (ecore-tote>";
  hname[3]="abnormal single-segment events (ecore-tote>";
  hname[4]="Extra-Abnormal events (ecore-tote>";
  hname[5]="Extra-Abnormal single-segment events (ecore-tote>";
  hname[6]="Energy difference";
  hname[7]="Energy difference single-segment";
  hname[8]="abnormal/total events";
  hname[9]="abnormal/total single-segment events";
  hname[10]="Extra-Abnormal/total events";
  hname[11]="Extra-Abnormal/total single-segment events";

  //-------------------------------//
  bool flagf=1;
  if (argc!=1)
  {
    sstr.str("");
    sstr.clear();
    
    sstr<<argv[1];
    sstr>>datasr;
    sstr.str("");
    sstr.clear();

    sstr<<argv[2];
    sstr>>energydiff;
    sstr.str("");
    sstr.clear();
    
    sstr<<argv[3];
    sstr>>Exenergydiff;
    sstr.str("");
    sstr.clear();

    flagf=0;
  }

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
  
  if (argc==1)
    flagf=1;
  while(flagf)
  {
    cout<<"Energy difference:";
    cin>>energydiff;
    if (energydiff>0)
      flagf=0;
    else
    {
      flagf=1;
      cout<<"Error"<<endl;
    }
  }

  if (argc==1)
    flagf=1;
  while(flagf)
  {
    cout<<"Extra Energy difference:";
    cin>>Exenergydiff;
    if (Exenergydiff>0)
      flagf=0;
    else
    {
      flagf=1;
      cout<<"Error"<<endl;
    }
  }
    
  if (datasr==1)
    datan="sii";
  else if (datasr==2)
  {
    datan="siii";
    source +="I";
  }
  
  
  filename +=datan+".ecoto.root";
  dir_plot +="ed"+datan+"/";

  //--------------------------------------------------//
  //print data inf.-----------------------------------//
  cout<<"Figures Directory: "<<dir_plot<<endl;
  
  //--------------------------------------------------//
  //Input root data-----------------------------------//
  cout<<"Input histograms data: "<<filename<<endl;
  
  TFile* finput = new TFile(filename.c_str());
  finput->cd();
  
  //--------------------------------------------------//
  //Input histograms----------------------------------//

  TH1F** hecore = new TH1F*[segnum+1];
  TH1F** hecorep = new TH1F*[partnum];

  string namestr;
  stringstream order;

  for(int i=0;i<segnum+1;i++)
    hecore[i]= new TH1F[hnum];

  for(int i=0;i<partnum;i++)
    hecorep[i]= new TH1F[hnum];

  for(int i=0;i<=segnum;i++)
    for(int k=0;k<hnum;k++)
    {
      sstr<<i;
      sstr<<"_";
      sstr<<k;
      TH1F *f1=(TH1F*) gDirectory->Get(("h"+sstr.str()).c_str())->Clone();
      hecore[i][k]=*f1;
      sstr.str("");
      sstr.clear();
      cout<<"Input "<<hecore[i][k].GetTitle()<<endl;
    }

  for(int i=0;i<partnum;i++)
    for(int k=0;k<hnum;k++)
    {
      sstr<<i;
      sstr<<"_";
      sstr<<k;
      TH1F *f2=(TH1F*) gDirectory->Get(("hp"+sstr.str()).c_str())->Clone();
      hecorep[i][k]=*f2;
      sstr.str("");
      sstr.clear();
      cout<<"Input"<<hecorep[i][k].GetTitle()<<endl;
    }

  //---------------------------------------------------------------//
  //Plot histograms------------------------------------------------//
  cout<<"Plot histograms"<<endl;
  

  //----------------------------//
  //part 1--------------------//
  cout<<"part 1"<<endl;

  TCanvas* c1 = new TCanvas("c1","c1",10,10,900,600);
  c1->cd();
  gPad->SetLogy();
  for(int i=0;i<=segnum;i++)
  {
    hecore[i][0].GetXaxis()->SetTitle("Ecore [keV]");
    hecore[i][0].GetYaxis()->SetTitle("Entries");
    TLegend* lone = new TLegend(0.5,0.5,0.85,0.75);
    lone->SetFillStyle(0);
    for(int k=0;k<6;k++)
    {
      if(k==2||k==3)
      {
        sstr<<energydiff;
        sstr<<"keV)";
      }
      else if(k==4||k==5)
      {
        sstr<<Exenergydiff;
        sstr<<"keV)";
      }
      sstr<<" at seg";
      sstr<<i+1;
      
      hecore[i][k].SetLineColor(k+1);
      hecore[i][k].SetLineWidth(1);
      if(k==0)
        hecore[i][k].Draw();
      else
        hecore[i][k].Draw("same");
      lone->AddEntry(&hecore[i][k],(hname[k]+sstr.str()).c_str(),"l");
      sstr.str("");
      sstr.clear();
    }
    lone->Draw();
    c1->Update();
    sstr<<"seg";
    sstr<<i+1;
    c1->Print((dir_plot+datan+"_entries_"+sstr.str()+".eps").c_str());
    sstr.str("");
    sstr.clear();
  }
  
  for(int i=0;i<partnum;i++)
  {
    hecorep[i][0].GetXaxis()->SetTitle("Ecore [keV]");
    hecorep[i][0].GetYaxis()->SetTitle("Entries");
    TLegend* lone = new TLegend(0.5,0.5,0.85,0.75);
    lone->SetFillStyle(0);
    for(int k=0;k<6;k++)
    {
      if(k==2||k==3)
      {
        sstr<<energydiff;
        sstr<<"keV)";
      }
      else if(k==4||k==5)
      {
        sstr<<Exenergydiff;
        sstr<<"keV)";
      }
      hecorep[i][k].SetLineColor(k+1);
      hecorep[i][k].SetLineWidth(1);
      if(k==0)
        hecorep[i][k].Draw();
      else
        hecorep[i][k].Draw("same");
      lone->AddEntry(&hecorep[i][k],(hname[k]+sstr.str()+" at "+part[i]).c_str(),"l");
      sstr.str("");
      sstr.clear();
    }
    lone->Draw();
    c1->Update();
    c1->Print((dir_plot+datan+"_entries_"+part[i]+".eps").c_str());
  }

  //-----------------------------//
  //part 2-----------------------//
  cout<<"part 2"<<endl;
  
  for(int i=0;i<=segnum;i++)
  {
    hecore[i][6].GetXaxis()->SetTitle("Ecore [keV]");
    hecore[i][6].GetYaxis()->SetTitle("Entries");
    TLegend* lone = new TLegend(0.5,0.5,0.85,0.75);
    lone->SetFillStyle(0);
    for(int k=6;k<8;k++)
    {
      sstr<<" at seg";
      sstr<<i+1;
      
      hecore[i][k].SetLineColor(k-5);
      hecore[i][k].SetLineWidth(1);
      if(k==6)
        hecore[i][k].Draw();
      else
        hecore[i][k].Draw("same");
      lone->AddEntry(&hecore[i][k],(hname[k]+sstr.str()).c_str(),"l");
      sstr.str("");
      sstr.clear();
    }
    lone->Draw();
    c1->Update();
    sstr<<"seg";
    sstr<<i+1;
    c1->Print((dir_plot+datan+"_energydiff_"+sstr.str()+".eps").c_str());
    sstr.str("");
    sstr.clear();
  }
  
  for(int i=0;i<partnum;i++)
  {
    hecorep[i][6].GetXaxis()->SetTitle("Ecore [keV]");
    hecorep[i][6].GetYaxis()->SetTitle("Entries");
    TLegend* lone = new TLegend(0.5,0.5,0.85,0.75);
    lone->SetFillStyle(0);
    for(int k=6;k<8;k++)
    {
      hecorep[i][k].SetLineColor(k-5);
      hecorep[i][k].SetLineWidth(1);
      if(k==6)
        hecorep[i][k].Draw();
      else
        hecorep[i][k].Draw("same");
      lone->AddEntry(&hecorep[i][k],(hname[k]+part[i]).c_str(),"l");
    }
    lone->Draw();
    c1->Update();
    c1->Print((dir_plot+datan+"_energydiff_"+part[i]+".eps").c_str());
  }
  //================================================================//
  //add test================================================//
  cout<<"test part"<<endl;
  TCanvas* test=new TCanvas("test","test",10,10,900,600);
  TH1F* tes= new TH1F("dt0","Diff_tot-part",10000,0.0,10000.0);
  
  TH1F* tep= new TH1F("dt","diff_total-segall",10000,0.0,10000.0);
  for(int in=1;in<=10000;in++)
  {
    float htt=0;
    for(int k=0;k<segnum;k++)
      htt += hecore[k][1].GetBinContent(in);
    tep->SetBinContent(in,htt-hecore[segnum][1].GetBinContent(in));
  }
  test->cd();
  gPad->SetLogy();
  tep->GetXaxis()->SetTitle("Ecore[keV]");
  tep->Draw();
  test->Update();
  test->Print((dir_plot+"test.eps").c_str());
  for(int i=1;i<=10000;i++)
  {
    float htt=0;
    for (int k=0;k<partnum;k++)
      htt += hecorep[k][1].GetBinContent(i);
    tes->SetBinContent(i,htt-hecore[segnum][1].GetBinContent(i));
  }
  gPad->SetLogy();
  tes->GetXaxis()->SetTitle("Ecore[keV]");
  tes->Draw();
  test->Update();
  test->Print((dir_plot+"tests.eps").c_str());
  test->Delete();
  
      
  //-------------------------------------------------//
  //part 3-----------------------------------------//
  cout<<"part 3"<<endl;
  TCanvas* c2= new TCanvas("c2","c2",10,10,900,600);
  c2->cd();
  for(int i=0;i<=segnum;i++)
  {
    hecore[i][8].GetXaxis()->SetTitle("Ecore [keV]");
    hecore[i][8].GetYaxis()->SetTitle("rate");
    TLegend* lone = new TLegend(0.5,0.5,0.85,0.75);
    lone->SetFillStyle(0);
    for(int k=8;k<hnum;k++)
    {
      sstr<<" at seg";
      sstr<<i+1;
   
      hecore[i][k].SetLineColor(k-7);
      hecore[i][k].SetLineWidth(1);
      if(k==8)
        hecore[i][k].Draw();
      else
        hecore[i][k].Draw("same");
      lone->AddEntry(&hecore[i][k],(hname[k]+sstr.str()).c_str(),"l");
      sstr.str("");
      sstr.clear();
    }
    lone->Draw();
    c2->Update();
    sstr<<"seg";
    sstr<<i+1;
    c2->Print((dir_plot+datan+"_rate_"+sstr.str()+".eps").c_str());
    sstr.str("");
    sstr.clear();
  }
  
  for(int i=0;i<partnum;i++)
  {
    hecorep[i][8].GetXaxis()->SetTitle("Ecore [keV]");
    hecorep[i][8].GetYaxis()->SetTitle("rate");
    hecorep[i][8].SetTitle((source+" abnormal, error and total events distributed on core energy").c_str());
    TLegend* lone = new TLegend(0.5,0.5,0.85,0.75);
    lone->SetFillStyle(0);
    for(int k=8;k<hnum;k++)
    {
  
      hecorep[i][k].SetLineColor(k-7);
      hecorep[i][k].SetLineWidth(1);
      if(k==8)
        hecorep[i][k].Draw();
      else
        hecorep[i][k].Draw("same");
      lone->AddEntry(&hecorep[i][k],(hname[k]+part[i]).c_str(),"l");
    }
    lone->Draw();
    c2->Update();
    c2->Print((dir_plot+datan+"_rate_"+part[i]+".eps").c_str());
  }
  c2->Delete();

  //-------------------------------------------------//
  //part 4-------------------------------------------//
  cout<<"part 4"<<endl;
  TCanvas* c3=new TCanvas("c3","c3",10,10,900,600);
  c3->cd();
  gPad->SetLogy();
  for(int k=0;k<6;k++)
  {
    TLegend* lone= new TLegend(0.5,0.5,0.85,0.75);
    lone->SetFillStyle(0);
    hecore[0][k].GetXaxis()->SetTitle("Ecore [keV]");
    hecore[0][k].GetYaxis()->SetTitle("Entries");
    for(int i=0;i<segnum;i++)
    {
      sstr<<i+1;
      hecore[i][k].Rebin(100);
      hecore[i][k].SetLineColor(i+1);
      hecore[i][k].SetLineWidth(1);
      if(i==0)
        hecore[i][k].Draw();
      else
        hecore[i][k].Draw("same");
      lone->AddEntry(&hecore[i][k],(hname[k]+" seg"+sstr.str()).c_str(),"l");
      sstr.str("");
      sstr.clear();
    }
    lone->Draw();
    c3->Update();
    c3->Print((dir_plot+hecore[segnum][k].GetTitle()+".eps").c_str());
  }
  c3->Delete();
  
  for(int i=0;i<=segnum;i++)
    for(int k=0;k<hnum;k++)
      hecore[i][k].Delete();

  for(int i=0;i<partnum;i++)
    for(int k=0;k<hnum;k++)
      hecorep[i][k].Delete();

  return 0;
}


