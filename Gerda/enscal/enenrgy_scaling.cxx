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

int main(int argc,char* argv[])
{
  gROOT->cd();
  //Tree-----------------------------------------//
  TTree *PSTree = new TTree("PSTree","Secondary");
  TClain *otree= new TClain("otree");

  //parameter------------------------------------//
  const int segnum=18;
  const float tl208=2614.5;
  const float k40=1460;

  stringstream sstr;
  string directory="$gerda/data/";
  string output_filename=directory+"secondary.root";

  //Add root-------------------------------------//
  otree->AddFile((directory+"Bipo/BiPo_10.root").c_str());
  otree->AddFile((directory+"Bipo/BiPo_11.root").c_str());
  otree->AddFile((directory+"Bipo/BiPo_12.root").c_str());

  //Declaration of leaves types
  int Cha_SegNum[20];
  int Cha_MCAEnergy[20];
  int nsegs;
  float eseg[20];
  int iseg[20];
  float tote;
  float ecore;
  int triggertime[20];
  int trig;
  int evt_timehigh[5];
  int evth;
  int evt_timelow[5];
  int evtl;
  
  otree->SetBranchAddress("Evt_Number",&Evt_Number);
  otree->SetBranchAddress("Cha_SegNum",Cha_SegNum);
  otree->SetBranchAddress("Cha_MCAEnergy",Cha_MCAEnergy);
  otree->SetBranchAddress("evt_timehigh",Evt_TimeHigh);
  otree->SetBranchAddress("evt_timelow",Evt_TimeLow);
  otree->SetBranchAddress("triggertime",Cha_TriggerTime);

  PSTree->Branch("evt_number",&Evt_Number,"Evt_Number/i");
  PSTree->Branch("nsegs",&nsegs,"nsegs/i");
  PSTree->Branch("eseg",eseg,"eseg[20]/f");
  PSTree->Branch("iseg",iseg,"iseg[20]/i");
  PSTree->Branch("tote",&tote,"tote/f");
  PSTree->Branch("ecore",&ecore,"ecore/f");
  PSTree->Branch("triggertime",&trig,"trig/i");
  PSTree->Branch("evt_timehigh",&evth,"evth/i");
  PSTree->Branch("evt_timelow",&evtl,"evtl/i");
  
  
  return0;
}
