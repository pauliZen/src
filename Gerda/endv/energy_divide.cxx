#include <iomanip>
#include <map>
#include <utility>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include "TDirectory.h"
#include "TFitResult.h"
#include "TF1.h"
#include "TLine.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TLine.h"
#include "TChain.h"

using namespace std;

bool check_seg(int i[20],int nseg,int ns)
{
  for(int k=0;k<nseg;k++)
  {
    if (i[k]==ns)
      return true;
  }
  return false;
}

bool check_part(int i[20],int nseg,int ns)
{
  int sego[3][6]={{7,8,9,10,11,12},{4,5,6,13,14,15},{1,2,3,16,17,18}};
  
  for(int n=0;n<nseg;n++)
    for(int k=0;k<6;k++)
    {
      if (i[n]==sego[ns-1][k])
        return true;
    }
  return false;
}

double fwhmfun(double *x,double *par)
{
  return par[0]+par[1]*pow(x[0],0.5)+par[2]*x[0];
}

int main(int argc,char* argv[]) //(source,energy diff,ex energydiff, ndivision)
{
  //-------------------------------------------------//
  //Reset ROOT and connect tree file-----------------//
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  TChain* PSTree = new TChain("PSTree");

  //-------------------------------------------------//
  //choose ------------------------------------------//

  //-------------------------------//
  //parameters---------------------//

  const int segnum=18;
  const int partnum=3;
  const int hnum=12;
  int ndivision=60000;
  float energydiff=10;
  float Exenergydiff=1000;
  int datasr=1;
  stringstream sstr;

  map<int, string> part;
  part[0]="top";
  part[1]="mid";
  part[2]="bottom";

  map<int, string> hname;
  hname[0]="total";
  hname[1]="total_single";
  hname[2]="abnormal";
  hname[3]="abnormal_single";
  hname[4]="ExtraAbnormal";
  hname[5]="ExtraAbnormal_single";
  hname[6]="Energy_difference";
  hname[7]="Energy_difference_single";
  hname[8]="abnormal_total";
  hname[9]="abnormal_total_single";
  hname[10]="ExtraAbnormal_total";
  hname[11]="ExtraAbnormal_total_single";

  float range[hnum][2]=
    {
      {0.0,10000.0},//total
      {0.0,10000.0},//total-single
      {0.0,10000.0},//abnormal
      {0.0,10000.0},//abnormal-single
      {0.0,10000.0},//ExtraAbnormal
      {0.0,10000.0},//ExtraAbnormal-single
      {-10000.0,10000.0},//Energydiff
      {-10000.0,10000.0},//Energydiff-s
      {0.0,10000.0},//abnormal:total
      {0.0,10000.0},//abnormal:total-s
      {0.0,10000.0},//ExtraAbnormal:total
      {0.0,10000.0} //ExtraAbnormal:total-s
    };

  //-----------------//
  //custom name------//

  string directory="$gerda/data/";
  string datan="sii";
  string output_histogram_filename=directory+"histograms/h.";

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

    sstr<<argv[4];
    sstr>>ndivision;
    sstr.str("");
    sstr.clear();

    flagf=0;
  }
  else
  {
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

    flagf=1;
    while(flagf)
    {
      cout<<"Set Ndivision:";
      cin>>ndivision;
      if (ndivision>1)
        flagf=0;
      else
      {
        flagf=1;
        cout<<"Error"<<endl;
      }
    }
  }
  
  int binrange[hnum]={ndivision,ndivision,ndivision,ndivision,ndivision,ndivision,ndivision,ndivision,100,100,100,100};
  //------------------------------------------------//
  //choosing----------------------------------------//

  cout<<"Step: choosing"<<endl;

  if (datasr==2)
  {
    //-------------------------------
    // S-III in G-III 2010

    PSTree->AddFile((directory+"shrinked.root").c_str());
    datan="siii";
    output_histogram_filename +=datan+".ecoto.root";
  }
  else if (datasr==1)
  {
    //---------------------------------------------
    // Siegfried-II in liquid Nitrogen

    PSTree->AddFile((directory+"SII_ntuple/nbg484.root").c_str());
    PSTree->AddFile((directory+"SII_ntuple/nbg485.root").c_str());
    PSTree->AddFile((directory+"SII_ntuple/nbg486.root").c_str());
    PSTree->AddFile((directory+"SII_ntuple/nbg487.root").c_str());
    PSTree->AddFile((directory+"SII_ntuple/nbg488.root").c_str());
    PSTree->AddFile((directory+"SII_ntuple/nbg489.root").c_str());
    datan="sii";
    output_histogram_filename +=datan+".ecoto.root";
  }
 
  //--------------------------------------------------//
  //print data inf.-----------------------------------//

  cout<<"Output_filename: "<<output_histogram_filename<<endl;
  cout<<"Data source:"<<datan<<endl;
  cout<<"Energy difference:"<<energydiff<<endl;
  cout<<"Extra Energy Difference:"<<Exenergydiff<<endl;
    
  //--------------------------------------------------//
  //Declaration of leaves types
  cout<<"Declaration of values"<<endl;
    
  int           Evt_Number;
  int           nsegs;
  float         eseg[20];
  int           iseg[20];
  float         tote;
  float         tote_threshold;
  float         ecore;
  int           triggertime;
  int           evt_timehigh;
  int           evt_timelow;

  //---------------------------------------------------//
  // Set branch addresses.-----------------------------//
  cout<<"Set Branch Addresses"<<endl;

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

  
  TH1F** hecore = new TH1F*[segnum+1];
  TH1F** hecorep = new TH1F*[partnum];

    
    
  //--------------------------------------------------//
  //build histograms values---------------------------//
  cout<<"Build Histograms values"<<endl;

  string namestr;
  stringstream order;

  for(int i=0;i<segnum+1;i++)
  {
    hecore[i]= new TH1F[hnum];
  }
  
  for(int i=0;i<partnum;i++)
  {
    hecorep[i]= new TH1F[hnum];
  }
  
  for(int i=0;i<segnum;i++)
  {
    for(int k=0;k<hnum;k++)
    {
      order<<i+1;
      namestr=order.str()+"_"+hname[k];
      sstr<<i;
      sstr<<"_";
      sstr<<k;
      TH1F f1(("h"+sstr.str()).c_str(),("hecore_seg"+namestr).c_str(),binrange[k],range[k][0],range[k][1]);
      hecore[i][k]=f1;
      order.str("");
      order.clear();
      sstr.str("");
      sstr.clear();
      cout<<"Build hecore_seg"+namestr<<endl;
    }
  }
  
  for(int k=0;k<hnum;k++)
  {
    namestr=hname[k];
    sstr<<segnum;
    sstr<<"_";
    sstr<<k;
    TH1F t1(("h"+sstr.str()).c_str(),("hecore_total_"+hname[k]).c_str(),binrange[k],range[k][0],range[k][1]);
    hecore[segnum][k]=t1;
    sstr.str("");
    sstr.clear();
    cout<<"Build hecore_total"+hname[k]<<endl;
  }

  for(int i=0;i<partnum;i++)
  {
    for(int k=0;k<hnum;k++)
    {
      namestr=part[i]+"_"+hname[k];
      sstr<<i;
      sstr<<"_";
      sstr<<k;
      TH1F f2(("hp"+sstr.str()).c_str(),("hecore_"+namestr).c_str(),binrange[k],range[k][0],range[k][1]);
      hecorep[i][k]=f2;
      sstr.str("");
      sstr.clear();
      cout<<"Build hecore_"+namestr<<endl;
    }
  }

  //check energy_resolution_function================//
  cout<<"check energy resolution function\n";

  double *par =new double[10]();
  string pline="pol0";
  int *counts=new int();
  *counts=1;

  TFile * finput= new TFile((directory+"histograms/"+datan+".energy.resolution.root").c_str());
  if(finput->IsOpen())
  {
    finput->cd();
    cout<<"File input success\n";
    TFitResult* pl=0;
    gDirectory->GetObject("Resolution",pl);
    if(pl)
    {
      cout<<"Load resolution fit parameters successful\n";
      *counts=pl->NTotalParameters();
      pline="FWHMfun";
      cout<<"Fit method: "<<pline<<endl;
      for(int i=0;i<*counts;i++)
        par[i]=pl->Value(i);
    }
  }
  else
  {
    cout<<"File not found\n";
    cout<<"Fit method: "<<pline<<endl;
  }
  
  //Build resolution function================================//
  cout<<"Build resolution function\n";
  
  TF1 resl1("resl1",fwhmfun,0,10000,3);
  TF1 resl0("resl0","pol0",0,10000);
  TF1 *resl=new TF1;

  if(*counts!=1)
  {
    *resl=resl1;
    for(int i=0;i<*counts;i++)
      resl->SetParameter(i,par[i]);
  }
  else
  {
    *resl=resl0;
    resl->SetParameter(0,energydiff);
  }
  
  cout<<"Build resolution function successful\n";
  delete []par;
  if(*counts!=1)
    for(int i=0;i<*counts;i++)
      cout<<"Parameter "<<i<<":"<<resl->GetParameter(i)<<endl;
  else
    cout<<"Parameter: "<<resl->GetParameter(0)<<endl;
  
  delete counts;
  delete finput;
  
  
  //----------------------------------------------//
  //print the total events------------------------//
  cout<<"Print Total Events"<<endl;

  int nentries = PSTree->GetEntries();
  cout<<" total number of events "<<nentries<<endl;

  //----------------------------------------------//
  //data analysis---------------------------------//
  cout<<"Step: Data Analysis"<<endl;
  cout<<"Fill histograms total//segment//part"<<endl;
  
  
  for (int ievt=0; ievt<nentries;ievt++)
  {
    if (ievt%1000000==0)
      cout<<"Event:"<<ievt<<endl;
    
    PSTree->GetEntry(ievt);

    //----------------//
    //total segment fill----//
    for (int sn=0;sn<=segnum;sn++)
    {
      if(check_seg(iseg,nsegs,sn+1)||sn==segnum)
      {
        hecore[sn][0].Fill(ecore);
        if (nsegs==1)
          hecore[sn][1].Fill(ecore);

        if (TMath::Abs(ecore-tote)>resl->Eval(ecore))
        {
          hecore[sn][2].Fill(ecore);
          hecore[sn][6].Fill(ecore-tote);
          if (nsegs==1)
          {
            hecore[sn][3].Fill(ecore);
            hecore[sn][7].Fill(ecore-tote);
          }
        }
        
        if (TMath::Abs(ecore-tote)>Exenergydiff)
        {
          hecore[sn][4].Fill(ecore);
          if (nsegs==1)
            hecore[sn][5].Fill(ecore);
        }
      }
    }
    
    //---------------//
    //part fill------//
    for (int pa=0;pa<partnum;pa++)
    {
      if(check_part(iseg,nsegs,pa+1))
      {
        hecorep[pa][0].Fill(ecore);
        if (nsegs==1)
          hecorep[pa][1].Fill(ecore);

        if (TMath::Abs(ecore-tote)>resl->Eval(ecore))
        {
          hecorep[pa][2].Fill(ecore);
          hecorep[pa][6].Fill(ecore-tote);
          if (nsegs==1)
          {
            hecorep[pa][3].Fill(ecore);
            hecorep[pa][7].Fill(ecore-tote);
          }
        }
        
        if (TMath::Abs(ecore-tote)>Exenergydiff)
        {
          hecorep[pa][4].Fill(ecore);
          if (nsegs==1)
            hecorep[pa][5].Fill(ecore);
        }
      }
    }
  }

  //--------------//
  //rate fill-----//
  cout<<"Fill histograms: rate"<<endl;

  float **hrate1=new float*[segnum+1];
  float **hrate2=new float*[segnum+1];
  float **hrate3=new float*[segnum+1];
  float **hratep1=new float*[partnum];
  float **hratep2=new float*[partnum];
  float **hratep3=new float*[partnum];
  for(int i=0;i<segnum+1;i++)
  {
    hrate1[i]=new float[2]();
    hrate2[i]=new float[2]();
    hrate3[i]=new float[2]();
  }
  for(int i=0;i<partnum;i++)
  {
    hratep1[i]=new float[2]();
    hratep2[i]=new float[2]();
    hratep3[i]=new float[2]();
  }
  

  for (int i=1;i<=binrange[0];i++)
  {
    for (int sn=segnum;sn>=0;sn--)
      for (int k=0;k<2;k++)
      {
        hrate1[sn][k] +=hecore[sn][2+k].GetBinContent(i);
        hrate3[sn][k] +=hecore[sn][0+k].GetBinContent(i);
        hrate2[sn][k] +=hecore[sn][4+k].GetBinContent(i);
        
        if (i%(binrange[0]/binrange[8])==0)
        {
          if (hrate3[sn][k]==0)
          {
            hrate3[sn][k]=1;
            hrate1[sn][k]=hrate2[sn][k]=0;
          }
          hecore[sn][8+k].SetBinContent(i/(binrange[0]/binrange[8]),hrate1[sn][k]/hrate3[sn][k]);
          hecore[sn][10+k].SetBinContent(i/(binrange[0]/binrange[8]),hrate2[sn][k]/hrate3[sn][k]);
          hrate1[sn][k]=hrate2[sn][k]=hrate3[sn][k]=0;
        }
      }

    for (int pa=0;pa<partnum;pa++)
      for (int k=0;k<2;k++)
      {
        hratep1[pa][k] +=hecorep[pa][2+k].GetBinContent(i);
        hratep3[pa][k] +=hecorep[pa][0+k].GetBinContent(i);
        hratep2[pa][k] +=hecorep[pa][4+k].GetBinContent(i);
        
        if (i%(binrange[0]/binrange[8])==0)
        {
          if (hratep3[pa][k]==0)
          {
            hratep3[pa][k]=1;
            hratep1[pa][k]=hratep2[pa][k]=0;
          }
          hecorep[pa][8+k].SetBinContent(i/(binrange[0]/binrange[8]),hratep1[pa][k]/hratep3[pa][k]);
          hecorep[pa][10+k].SetBinContent(i/(binrange[0]/binrange[8]),hratep2[pa][k]/hratep3[pa][k]);
          hratep1[pa][k]=hratep2[pa][k]=hratep3[pa][k]=0;
        }
      }
    
  }
  

  
  //-----------------------------------------------//
  //save histograms--------------------------------//
  cout<<"Output histograms"<<endl;

  TFile* houtput = new TFile(output_histogram_filename.c_str(),"recreate");
  for(int i=0;i<segnum+1;i++)
    for(int k=0;k<hnum;k++)
      hecore[i][k].Write();
  for(int i=0;i<partnum;i++)
    for(int k=0;k<hnum;k++)
      hecorep[i][k].Write();
  houtput->Close();

  return 0;
}

  
 
