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
#include "TCanvas.h"
#include "TF1.h"
#include "TLine.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TLine.h"
#include "TChain.h"

using namespace std;
int main(int argc,char* argv[]) //source
{
  //-------------------------------------------------//
  //Reset ROOT and connect tree file-----------------//
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  TChain* P1 = new TChain("PSTree");
  TChain* P2 = new TChain("PSTree");

  //parameters---------------------//

  string dir="$gerda/data/";
  string dir_h=dir+"histograms/";
  string dir_p=dir+"plots/";
  string datan[2]={"sii","siii"};
  stringstream sstr;
  string filename[2];
  string plotname=dir_p+"ecore.etot.eps";

  for(int i=0;i<2;i++)
  {
    dir_p[i]==dir+"plots/ed"+datan[i]+"/";
    filename[i]=dir_h+"h."+datan[i]+".ecoto.root";
  }

  //-------------------------------
  // S-III in G-III 2010
    
  P2->AddFile((dir+"shrinked.root").c_str());
  
  //---------------------------------------------
  // Siegfried-II in liquid Nitrogen

  P1->AddFile((dir+"SII_ntuple/nbg484.root").c_str());
  P1->AddFile((dir+"SII_ntuple/nbg485.root").c_str());
  P1->AddFile((dir+"SII_ntuple/nbg486.root").c_str());
  P1->AddFile((dir+"SII_ntuple/nbg487.root").c_str());
  P1->AddFile((dir+"SII_ntuple/nbg488.root").c_str());
  P1->AddFile((dir+"SII_ntuple/nbg489.root").c_str());

  //print data inf.-----------------------------------//
  cout<<"Plots filename: "<<plotname<<endl;

  //--------------------------------------------------//
  //Declaration of leaves types
  cout<<"Declaration of values"<<endl;
    
  float tote1;
  float tote2;
  float ecore1;
  float ecore2;
  
  //---------------------------------------------------//
  // Set branch addresses.-----------------------------//
  cout<<"Set Branch Addresses"<<endl;

  P1->SetBranchAddress("tote",&tote1);
  P1->SetBranchAddress("ecore",&ecore1);
  P2->SetBranchAddress("tote",&tote2);
  P2->SetBranchAddress("ecore",&ecore2);
  
  //Histograms =======================================//
  TH2F *h1=new TH2F("htcsii","The distribution of total segments energy and core energy (S-II)",1000,0,10000,1000,0,10000);
  TH2F *h2=new TH2F("htcsiii","The distribution of total segments energy and core energy (S-III)",1600,0,16000,1600,0,16000);

  //build ============================================//
  int *nentries=new int[2]();
  nentries[0]= P1->GetEntries();
  nentries[1]= P2->GetEntries();
  cout<<"SII:"<<nentries[0]<<" SIII:"<<nentries[1]<<" Max:"<<max(nentries[0],nentries[1])<<endl;

  for(int i=0;i<max(nentries[0],nentries[1]);i++)
  {
    if(i%1000000==0) cout<<"now "<<i<<endl;
    
    if(i<nentries[0])
    {
      P1->GetEntry(i);
      h1->Fill(ecore1,tote1);
    }
    if(i<nentries[1])
    {
      P2->GetEntry(i);
      h2->Fill(ecore2,tote2);
    }
    
  }
  
  
  //draw =============================================//
  TCanvas* c1=new TCanvas("c1","c1",10,10,900,600);
  c1->Divide(2);
  c1->cd(1);
  h1->GetXaxis()->SetTitle("Ecore [keV]");
  h1->GetYaxis()->SetTitle("Etotal [keV]");
  h1->GetYaxis()->SetTitleColor(4);
  h1->Draw();

  c1->cd(2);
  h2->GetXaxis()->SetTitle("Ecore [keV]");
  h2->GetYaxis()->SetTitle("Etotal [keV]");
  h2->GetYaxis()->SetTitleColor(4);
  h2->Draw();

  c1->Print(plotname.c_str());

  TFile *output1=new TFile(filename[0].c_str(),"update");
  output1->cd();
  h1->Write("htc",6);
  output1->Close();

  TFile *output2=new TFile(filename[1].c_str(),"update");
  output2->cd();
  h2->Write("htc",6);
  output2->Close();

  return 0;
}

  











