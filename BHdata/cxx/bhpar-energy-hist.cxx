// Unused now!======================================//
// calculate delta (1/a) for bh-par data============//
// the result will be stored in -result.root========//
//Command: [prog.] [rootname] [treename] [newtreename] //
//  rootname: bh-par root name (no"-bhpar.root")====//
//  treename: bh-par tree name======================//
//  newtreename: new tree name======================//
//  newtreetitle: new tree title====================//

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"

using namespace std;

int main(int argc,char* argv[])
{
  //variables=========================================//
  string rootname;
  string treename;
  string newtreename;
  string newtreetitle;

  stringstream namestr;
  string checksh;
  char inflagc='y';
  bool inflag=1;

  switch (argc)
  {
  case 1:
    cout<<"Load last input(y/n)?";
    cin>>inflagc;
    if (inflagc=='n')
      inflag=0;
    if (inflag)
    {
      ifstream configf(".bhpar-energy-hist.conf");
      if (!configf.is_open())
        cout<<"No config file"<<endl;
      else
      {
        configf>>rootname;
        configf>>treename;
        configf>>newtreename;
        configf>>newtreetitle;
        configf.close();
      }
    }
    
    //input=============================================//
    cout<<"root name("<<rootname<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input root name(no suffix):";
      cin>>rootname;
    }
    cout<<"Tree name("<<treename<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Tree name:";
      cin>>treename;
    }
    cout<<"New tree name("<<newtreename<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
    cout<<"New Tree name:";
    cin>>newtreename;
    }
    cout<<"New Tree title("<<newtreetitle<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input New Tree title(no space):";
      cin>>newtreetitle;
    }
    break;
  case 2:
    namestr.str("");
    namestr.clear();
    namestr<<argv[1];
    namestr>>checksh;
    if (checksh=="-l")
    {
      ifstream configf(".bhpar-energy-hist.conf");
      if (!configf.is_open())
        cout<<"No config file"<<endl;
      else
      {
        configf>>rootname;
        configf>>treename;
        configf>>newtreename;
        configf>>newtreetitle;
        configf.close();
      }
    }
    else
    {
      cout<<"input incomplete"<<endl;
      return 0;
    }
    break;
  case 5:
    namestr.str("");
    namestr.clear();
    namestr<<argv[1];
    namestr>>rootname;
    namestr.str("");
    namestr.clear();
    namestr<<argv[2];
    namestr>>treename;
    namestr.str("");
    namestr.clear();
    namestr<<argv[3];
    namestr>>newtreename;
    namestr.str("");
    namestr.clear();
    namestr<<argv[4];
    namestr>>newtreetitle;
    break;
  default:
    cout<<"input incomplete"<<endl;
    return 0;
    break;
  }

  ofstream outconf(".bhpar-energy-hist.conf");
  outconf<<rootname<<endl;
  outconf<<treename<<endl;
  outconf<<newtreename<<endl;
  outconf<<newtreetitle<<endl;
  outconf.close();
  
  string newrootname=rootname+"-result.root";
  rootname +="-bhpar.root";
  cout<<rootname<<":"<<treename<<"->"<<newrootname<<":"<<newtreename<<"("<<newtreetitle<<")"<<endl;

  //analysis==========================================//
  TFile *f1=new TFile(rootname.c_str(),"update");
  
  //Parameters========================================//
  //     t, dr, a, over_a, EB, e, T_orb, XCM_BH,
  //     YCM_BH, ZCM_BH, VXCM_BH, VYCM_BH, VZCM_BH
  //==================================================//
  Double_t td,drd,ad,oad,ebd,ed,torbd;
  Double_t xcmbhd,ycmbhd,zcmbhd,vxcmbhd,vycmbhd,vzcmbhd;

  //data==============================================//
  // for black hole 1=================================//
  TTree *BHp=(TTree*)(f1->Get(treename.c_str()));
  BHp->SetBranchAddress("t",&td);
  BHp->SetBranchAddress("dr",&drd);
  BHp->SetBranchAddress("a",&ad);
  BHp->SetBranchAddress("over_a",&oad);
  BHp->SetBranchAddress("EB",&ebd);
  BHp->SetBranchAddress("e",&ed);
  BHp->SetBranchAddress("t_orb",&torbd);
  BHp->SetBranchAddress("xcm_bh",&xcmbhd);
  BHp->SetBranchAddress("ycm_bh",&ycmbhd);
  BHp->SetBranchAddress("zcm_bh",&zcmbhd);
  BHp->SetBranchAddress("vxcm_bh",&vxcmbhd);
  BHp->SetBranchAddress("vycm_bh",&vycmbhd);
  BHp->SetBranchAddress("vzcm_bh",&vzcmbhd);

  TFile *f2=new TFile(newrootname.c_str(),"update");
  f2->cd();
  TTree *bha=new TTree(newtreename.c_str(),newtreetitle.c_str());
  Int_t totnum=BHp->GetEntries();
  for (Int_t i=0;i<totnum;i++)
  {
  }
  bha->Write("",TObject::kOverwrite);
  return 0;
}


  
