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

using namespace std;

bool check_seg(int i[20],int ns)
{
  int sego[3][6]={{7,8,9,10,11,12},{4,5,6,13,14,15},{1,2,3,16,17,18}};
  
  for(int k=0;k<6;k++)
  {
    if (i[0]==sego[ns][k])
      return true;
  }
  return false;
}


int main(int argc,char* argv[]) //(decay element, source)
{
  //Reset ROOT and connect tree file================//
  
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  //parameters========================================//

  TChain* PSTree = new TChain("PSTree");
  
  int numdecay=1;
  int datasr=1;
  bool flagf=1;
  stringstream sstr;

  Int_t nbi=11;
  Int_t npt=5;
  float decayt=164.3;     //units: us
  float lowlim=3000.0;
  float uplim=7686.82;
  string elename="bi214";
  string directory="$gerda/data/";
  string datan="sii";
  string output_histogram_filename=directory+"histograms/";
  string doutdir="/home/lswl/Documents/works/Gerda/data/table/";

  map<int, double> ebi;
  map<int, string> seg;
  seg[1]="bottom";
  seg[2]="mid";
  seg[3]="top";
  seg[4]="total";

  //choose ===========================================//
  
  if(argc!=1)
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

  //element select ===================================//

  if (numdecay==1)
  {
    elename="bi214";
    lowlim=2800.0;
    uplim=7686.82;
    decayt=164.3*1.44;
    nbi=11;
    ebi[0]=609.312;
    ebi[1]=1120.287;
    ebi[2]=1377.669;
    ebi[3]=1729.595;
    ebi[4]=1764.494;
    ebi[5]=1847.420;
    ebi[6]=2204.21;
    ebi[7]=1238.110;
    ebi[8]=768.356;
    ebi[9]=934.061;
    ebi[10]=1407.98;
  }
  else if (numdecay==2)
  {
    elename="bi212";
    lowlim=2800.0;
    uplim=8784.377;
    decayt=10;
    nbi=5;
    ebi[0]=727.330;
    ebi[1]=1620.50;
    ebi[2]=785.37;
    ebi[3]=1078.62;
    ebi[4]=893.408;
  }
  
  //cutoff time ======================================//
  
  Int_t choose[npt];
  for (int i=0;i<npt;i++)
    choose[i]=static_cast<Int_t>((i+1)*decayt/0.0133333);

  //source input select ==============================//
  
  if (datasr==2)
  {
    //-------------------------------
    // S-III in G-III 2010
    //-------------------------------  
    PSTree->AddFile((directory+"shrinked.root").c_str());
    datan="siii";
  }
  else if (datasr==1)
  {
    //---------------------------------------------
    // Siegfried-II in liquid Nitrogen
    //---------------------------------------------
    
    PSTree->AddFile((directory+"SII_ntuple/nbg484.root").c_str());
    PSTree->AddFile((directory+"SII_ntuple/nbg485.root").c_str());
    PSTree->AddFile((directory+"SII_ntuple/nbg486.root").c_str());
    PSTree->AddFile((directory+"SII_ntuple/nbg487.root").c_str());
    PSTree->AddFile((directory+"SII_ntuple/nbg488.root").c_str());
    PSTree->AddFile((directory+"SII_ntuple/nbg489.root").c_str());
    datan="sii";
  }

  doutdir +=elename+"/"+datan+"/";
  output_histogram_filename +=elename+"."+datan+".root";
  
  ofstream dout[npt][4];  
  ofstream doutl[npt][4];
  
  //print information ================================//
  
  cout<<"Output root filename: "<<output_histogram_filename<<endl;
  cout<<"Output table directory: "<<doutdir<<endl;
  cout<<"Energy Line: ";
  for (int i=0;i<nbi;i++)
    cout<<setw(12)<<ebi[i];
  cout<<endl;

  //-------------------------------
  //Declaration of leaves types
  //-------------------------------
  Int_t           Evt_Number;
  Int_t           nsegs;
  Float_t         eseg[20];
  Int_t           iseg[20];
  Float_t         tote;
  Float_t         tote_threshold;
  Float_t         ecore;
  Int_t           triggertime;
  Int_t           evt_timehigh;
  Int_t           evt_timelow;
  
  //-------------------------------
  // the first and the second event 
  //-------------------------------
  Float_t  ecore_f;
  Int_t    nsegs_f;
  Float_t  eseg_f[20];
  Int_t    iseg_f[20];
  Int_t    triggertime_f;
  Int_t    evt_timehigh_f;
  Int_t    evt_timelow_f;
  Float_t  tote_f;
  
  Float_t  ecore_s;
  Int_t    nsegs_s;
  Float_t  eseg_s[20];
  Int_t    iseg_s[20];
  Int_t    triggertime_s;
  Int_t    evt_timehigh_s;
  Int_t    evt_timelow_s;
  Float_t  tote_s;
  
  // set branch addresses ============================//
  
  PSTree->SetBranchAddress("Evt_Number",&Evt_Number);
  PSTree->SetBranchAddress("nsegs",&nsegs);
  PSTree->SetBranchAddress("eseg",eseg);
  PSTree->SetBranchAddress("iseg",iseg);
  PSTree->SetBranchAddress("tote",&tote);
  PSTree->SetBranchAddress("tote_threshold",&tote_threshold);
  PSTree->SetBranchAddress("ecore",&ecore);
  PSTree->SetBranchAddress("triggertime",&triggertime);
  PSTree->SetBranchAddress("evt_timehigh",&evt_timehigh);
  PSTree->SetBranchAddress("evt_timelow",&evt_timelow);

  //Declare histograms values ========================//
  
  TH1F* hecore = new TH1F("hecore","hecore",10000,0.0,10000.0);
  TH1F* hecores = new TH1F("hecores","hecores",10000,0.0,10000.0);
  TH1F* hecore_first = new TH1F("hecore_first","hecore_first",10000,0.0,10000.0);
  TH1F* hecore_second = new TH1F("hecore_second","hecore_second",10000,0.0,10000.0);
  TH1F* hecore_seconds = new TH1F("hecore_seconds","hecore_seconds",10000,0.0,10000.0);
  
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
      sstr<<i;
      sstr<<"_";
      sstr<<seg[k];

      TH1F f2(("hecore_secondts"+sstr.str()).c_str(),("hecore_secondts"+sstr.str()).c_str(),10000,0.0,10000.0);
      hecorets[i-1][k-1]=f2;
      
      dout[i-1][k-1].open((doutdir+elename+"."+datan+".td"+sstr.str()+".txt").c_str());
      dout[i-1][k-1]<<"time differece:"<<i*decayt<<"us   segment:"<<seg[k]<<endl;
      dout[i-1][k-1]<<"ecore_f"<<" ecore_s"<<" time_diff"<<" iseg_s"<<" eseg_s"<<endl;

      doutl[i-1][k-1].open((doutdir+"el."+elename+"."+datan+".td"+sstr.str()+".txt").c_str());
      doutl[i-1][k-1]<<"time differece:"<<i*decayt<<"us   segment:"<<seg[k]<<"   Energy range:"<<lowlim<<" - "<<uplim<<" (keV)"<<endl;
      doutl[i-1][k-1]<<"ecore_f"<<" ecore_s"<<" time_diff"<<" iseg_s"<<" eseg_s"<<endl;
      
      sstr.str("");
      sstr.clear();
    }
    
    sstr<<i;
    TH1F f1(("hecore_secondt"+sstr.str()).c_str(),("hecore_secondt"+sstr.str()).c_str(),10000,0.0,10000.0);
    hecoret[i-1]=f1;
    sstr.str("");
    sstr.clear();
  }
  
  //---------------------------------------------------//

  TH1F* htime_diff = new TH1F("htime_diff","htime_diff",60000,0,60000);
  TH1F* htriggertime_diff = new TH1F("htriggertime_diff","htriggertime_diff",10000,0.0,66000.0);
  TH1F* hevttime_diff = new TH1F("hevttime_diff","hevttime_diff",10000,0.0,10000.0);  // all events

  //print total events ===============================//
  
  Int_t nentries = PSTree->GetEntries();
  cout<<" total number of events "<<nentries<<endl;

  //data analysis ====================================//
   
  Bool_t first_is_bi;

  for (Int_t ievt=0; ievt<(nentries-1);ievt++)
  {
    //print now event ==================================//
    if (ievt%1000000==0) cout<<"now event "<<ievt<<endl;

    //GetEntry =========================================//
    PSTree->GetEntry(ievt);
    ecore_f = ecore;
    nsegs_f = nsegs;
    tote_f  = tote;
    triggertime_f = triggertime;
    evt_timehigh_f = evt_timehigh;
    evt_timelow_f = evt_timelow;
    for (Int_t icha=0; icha<nsegs; icha++) {
      iseg_f[icha] = iseg[icha];
      eseg_f[icha] = eseg[icha];
    }
    
    PSTree->GetEntry(ievt+1);
    ecore_s = ecore;
    nsegs_s = nsegs;
    tote_s  = tote;
    triggertime_s = triggertime;
    evt_timehigh_s = evt_timehigh;
    evt_timelow_s = evt_timelow;
    for (Int_t icha=0; icha<nsegs; icha++) {
      iseg_s[icha] = iseg[icha];
      eseg_s[icha] = eseg[icha];
    }
    
    // following cut is for S-III who has no signal in segment 16
    if (TMath::Abs(ecore_f-tote_f)>10.0 || TMath::Abs(ecore_s-tote_s)>10.0) continue;

    //triggertime ======================================//
    if (triggertime_s>triggertime_f) 
      htriggertime_diff->Fill(float(triggertime_s-triggertime_f));
    else                             
      htriggertime_diff->Fill(float(triggertime_s-triggertime_f+65536));

    //Fill total event histograms ======================//
    hecore->Fill(ecore_f);
    if (nsegs_f==1) hecores->Fill(ecore_f);

    //Fill timediff histograms =========================//
    Int_t time_diff = (evt_timehigh_s-evt_timehigh_f)*65536+(evt_timelow_s-evt_timelow_f);
    if ((evt_timehigh_s-evt_timehigh_f)<0||((evt_timehigh_s==evt_timehigh_f)&&(evt_timelow_s-evt_timelow_f)<0))
      time_diff=((evt_timehigh_s-evt_timehigh_f+65536)*65536+(evt_timelow_s-evt_timelow_f+65537));
    hevttime_diff->Fill(time_diff*0.0133333);
    htime_diff->Fill(time_diff);
    
    //Beta decay select ================================//
    first_is_bi = kFALSE;
    for (Int_t ie=0; ie<nbi; ie++)
    {
      if (TMath::Abs(ecore_f-ebi[ie])<5.0)
        first_is_bi=kTRUE;
    }
    
    if (first_is_bi)
    {
      hecore_first->Fill(ecore_f); 
      hecore_second->Fill(ecore_s);
      
      if (nsegs_s==1) hecore_seconds->Fill(ecore_s);
      
      //alpha decay selection ============================//
      for( Int_t chi=0; chi<npt; chi++)
      {
        if (time_diff>0 && time_diff<choose[chi])
        {
          hecoret[chi].Fill(ecore_s);
          if (nsegs_s==1)
          {
            hecorets[chi][3].Fill(ecore_s);
            for( Int_t s=0; s<3; s++)
            {
              if (check_seg(iseg_s,s))
              {
                hecorets[chi][s].Fill(ecore_s);

                dout[chi][s]<<ecore_f<<"&  "<<ecore_s<<"&  "
                            <<float(time_diff)*0.0133333<<"&  "
                            <<iseg_s[0]<<"&  "<<eseg_s[0]<<"\\\\hline"<<endl;
                dout[chi][3]<<ecore_f<<"&  "<<ecore_s<<"&  "
                            <<float(time_diff)*0.0133333<<"&  "
                            <<iseg_s[0]<<"&  "<<eseg_s[0]<<"\\\\hline"<<endl;
                
                if (ecore_s>lowlim && ecore_s<uplim)
                {
                  doutl[chi][s]<<ecore_f<<"&  "<<ecore_s<<"&  "
                              <<float(time_diff)*0.0133333<<"&  "
                              <<iseg_s[0]<<"&  "<<eseg_s[0]<<"\\\\hline"<<endl;
                  doutl[chi][3]<<ecore_f<<"&  "<<ecore_s<<"&  "
                              <<float(time_diff)*0.0133333<<"&  "
                              <<iseg_s[0]<<"&  "<<eseg_s[0]<<"\\\\hline"<<endl;

                  cout<<"select time differece:"<<setw(6)<<choose[chi];
                  cout<<setw(10)<<ecore_f<<setw(10)<<ecore_s;
                  cout<<setw(10)<<float(time_diff)*0.0133333;
                  cout<<setw(5)<<iseg_s[0]<<setw(10)<<eseg_s[0]<<endl;
                }
              }
            }
          }
        }
      }
    }
  }
  
  //save histograms ==================================//

  TFile* houtput = new TFile(output_histogram_filename.c_str(),"recreate");
  houtput->cd();
  hecore->Write();
  htime_diff->Write();
  htriggertime_diff->Write();
  hevttime_diff->Write();
  hecores->Write();
  hecore_first->Write();
  hecore_second->Write();
  hecore_seconds->Write();

  for(int i=0;i<5;i++)
  {
    hecoret[i].Write();
    for(int k=0;k<4;k++)
    {
      hecorets[i][k].Write();
      dout[i][k].close();
      doutl[i][k].close();
    }
  }
  
  houtput->Close();
  return 0;
}
