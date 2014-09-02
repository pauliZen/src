//Stardatatoroot====================================//
//lwang-edit========================================//
//==Use to transform *.dat.extra to *.foot==========//
//=================================================================//
//command:[prog.] [filename(.dat.extra)] [rootname(.root)*]        //
//        [option*] [dataname*]                                    //
//========[option]: rootname option--"create", "update"(default)===//
//========[dataname]: data treename--P+filename(default)===========//
//========[rootname]: output root filename--outroot.root(default)==//
//========Notes!: don't add filename and rootname suffix===========//
//=================================================================//
//==root structrue: Tree: HTree(header)============================//
//========================P****(data)==============================//
//=======P****: constant time group of all stars and black holes===//
//==============branch:index,mass,x,y,z,vx,vy,vz,r,v,pot,ax,ay,az==//
//=======HTree: Header for all P****===============================//
//==============branch: diskstep, N, time_cur======================//
//=================================================================//
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
#include "TBits.h"

using namespace std;

int main(int argc,char* argv[])
{
  string rootname="outroot";
  string filename;
  string dataname="PTree";
  string fileopt="update";
  stringstream sstr;
  sstr.str("");
  sstr.clear();

  //Error=============================================//
  string err1="Error pars: transtoroot [filename(.dat)] [rootfilename(.root)]";
  string err2="Error filename: no such filename";
  string err3="Error file: reach the end";
  
  //Input=============================================//
  //Pars: filename(no .dat), rootname(no .root), =====//
  //      update/create, data Tree name===============//
  //Default: filename, outroot.root, update, P+filename/
  
  switch (argc)
  {
  case 1:
    cout<<"filename";
    cin>>filename;
    cout<<"root filename";
    cin>>rootname;
    break;
  case 2:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>filename;
    sstr.str("");
    sstr.clear();
    rootname="outroot";
    dataname="P"+filename;
    break;
  case 3:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>filename;
    sstr.str("");
    sstr.clear();
    sstr<<argv[2];
    sstr>>rootname;
    sstr.str("");
    sstr.clear();
    dataname="P"+filename;
    break;
  case 4:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>filename;
    sstr.str("");
    sstr.clear();
    sstr<<argv[2];
    sstr>>rootname;
    sstr.str("");
    sstr.clear();
    sstr<<argv[3];
    sstr>>fileopt;
    sstr.str("");
    sstr.clear();
    dataname="P"+filename;
    break;
  default:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>filename;
    sstr.str("");
    sstr.clear();
    sstr<<argv[2];
    sstr>>rootname;
    sstr.str("");
    sstr.clear();
    sstr<<argv[3];
    sstr>>fileopt;
    sstr.str("");
    sstr.clear();
    sstr<<argv[4];
    sstr>>dataname;
    sstr.str("");
    sstr.clear();
    break;
  }

  rootname=rootname+".root";
  cout<<filename<<" to "<<rootname<<","<<fileopt<<","<<"data Tree name:"<<dataname<<endl;

  ifstream orgdata((filename+".dat.extra").c_str());
  if (!orgdata.is_open())
  {
    cout<<err2<<endl;
    return 0;
  }
  else
  {
    //Reset ROOT and connect tree file-----------------//
    gROOT->Reset();
    gROOT->SetStyle("Plain");
    TFile f(rootname.c_str(),fileopt.c_str());
    
    //Parameters========================================//
    Double_t mass,x,y,z,vx,vy,vz,r,v;
    Double_t pot,ax,ay,az;
    Int_t index=0;
    Int_t diskstep;
    Int_t N;
    Double_t time_cur;

    //Header===========================================//
    if (fileopt=="create")
    {
      TTree *HTree=new TTree ("HTree","Header");
      HTree->Branch("diskstep",&diskstep);
      HTree->Branch("N",&N);
      HTree->Branch("time_cur",&time_cur);
      if (!orgdata.eof())
      {
        orgdata>>diskstep;
        orgdata>>N;
        orgdata>>time_cur;
        HTree->Fill();
      }
      else
      {
        cout<<err3<<endl;
        return 0;
      }
      HTree->Write("",TObject::kOverwrite);
    }
    else
    {
      TTree *HTree=(TTree*)(f.Get("HTree"));
      HTree->SetBranchAddress("diskstep",&diskstep);
      HTree->SetBranchAddress("N",&N);
      HTree->SetBranchAddress("time_cur",&time_cur);
      if (!orgdata.eof())
      {
        orgdata>>diskstep;
        orgdata>>N;
        orgdata>>time_cur;
        HTree->Fill();
      }
      else
      {
        cout<<err3<<endl;
        return 0;
      }
      HTree->Write("",TObject::kOverwrite);
    }
    
    //data==============================================//
    
    TTree *PTree=new TTree (dataname.c_str(),("Particles data "+filename).c_str());
    PTree->Branch("index",&index);
    PTree->Branch("mass",&mass);
    PTree->Branch("x",&x);
    PTree->Branch("y",&y);
    PTree->Branch("z",&z);
    PTree->Branch("vx",&vx);
    PTree->Branch("vy",&vy);
    PTree->Branch("vz",&vz);
    PTree->Branch("r",&r);
    PTree->Branch("v",&v);
    PTree->Branch("pot",&pot);
    PTree->Branch("ax",&ax);
    PTree->Branch("ay",&ay);
    PTree->Branch("az",&az);

    Int_t tempindex;
    bool startcount=1;
    while (!orgdata.eof())
    {
      tempindex=index;
      orgdata>>index;
      if (startcount)
        startcount=0;
      else if (tempindex==index)
        continue;
      orgdata>>mass;
      orgdata>>x;
      orgdata>>y;
      orgdata>>z;
      orgdata>>vx;
      orgdata>>vy;
      orgdata>>vz;
      orgdata>>pot;
      orgdata>>ax;
      orgdata>>ay;
      orgdata>>az;
      r=sqrt(x*x+y*y+z*z);
      v=sqrt(vx*vx+vy*vy+vz*vz);
      
      PTree->Fill();
    }
    
    PTree->Write("",TObject::kOverwrite);
  }
  
  return 0;
}
