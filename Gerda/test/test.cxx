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
      if (i[n]==sego[ns][k])
        return true;
    }
  return false;
}


int main(int argc,char* argv[])
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
  
  int datasr=1;
  stringstream sstr;

  string directory="$gerda/data/";
  string datan="sii";


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
    
  //------------------------------------------------//
  //choosing----------------------------------------//

  cout<<"Step: choosing"<<endl;

  if (datasr==2)
  {
    //-------------------------------
    // S-III in G-III 2010

    PSTree->AddFile((directory+"shrinked.root").c_str());
    datan="siii";

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

  }
 
  //--------------------------------------------------//
  //print data inf.-----------------------------------//

  ofstream dout;
  dout.open((datan+"datacheck.txt").c_str());
  cout<<"Data source:"<<datan<<endl;

    
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

  
  //--------------------------------------------------//
  //build histograms values---------------------------//
  cout<<"Build Histograms values"<<endl;

  string namestr;
  stringstream order;

  //----------------------------------------------//
  //print the total events------------------------//
  cout<<"Print Total Events"<<endl;

  int nentries = PSTree->GetEntries();
  cout<<" total number of events "<<nentries<<endl;

  //----------------------------------------------//
  //data analysis---------------------------------//
  cout<<"Step: Data Analysis"<<endl;
  cout<<"Fill histograms total//segment//part"<<endl;
  
  dout<<setw(14)<<"event"<<" ";
  for(int i=1;i<19;i++)
    dout<<setw(3)<<i;
  dout<<setw(4)<<"t"<<endl;

  for (int ievt=0; ievt<10000;ievt++)
  {
    if (ievt%1000000==0)
      cout<<"Event:"<<ievt<<endl;

    PSTree->GetEntry(ievt);

    dout<<setw(14)<<ievt<<":";
    //----------------//
    //segment fill----//
    for (int sn=0;sn<=segnum;sn++)
    {
      if(nsegs==1)
        dout<<setw(3)<<(check_part(iseg,nsegs,sn+1)||sn==segnum);
      else dout<<setw(3)<<"n";
    }
    dout<<endl;
    dout<<setw(14)<<"iseg"<<":";
    for(int sn=0;sn<=segnum;sn++)
    {
      dout<<setw(3)<<iseg[sn];
    }
    dout<<endl;
    dout<<endl;
    
    
  }

  dout.close();
  return 0;
}


