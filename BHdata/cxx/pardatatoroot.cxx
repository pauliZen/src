// transform bh_par.dat to root=====================//
//Command: [prog.] [filename] [*rootname]===========//
//  filename: bh-param.dat==========================//
//  rootname: store bh-par data root name===========//
//            default:bh-par-root===================//
//Notes!: filename,rootname no siffix===============//
//Tree: t, dr, a, over_a, dover_a, EB, e, T_orb,====//
//      XCM_BH, YCH_BH, ZCM_BH, VXCM_BH, VYCH_BH,===//
//      VZCM_BH=====================================//
//Pars: [XYZ]CM_BH: black hole center position in ==//
//      original coordinate=========================//

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TLine.h"
#include "TChain.h"

using namespace std;

int main(int argc,char* argv[])
{
  string rootname="bh-par-root";
  string filename="bh-param";
  stringstream sstr;
  sstr.str("");
  sstr.clear();

  //Error=============================================//
  string err1="Error pars: transtoroot [filename(.dat)] [rootfilename(.root)]";
  string err2="Error filename: no such filename";
  string err3="Error file: reach the end";
  
  //Input=============================================//
  //Pars: filename(no .dat), rootname(no .root), =====//
  //Default: bh.dat, bhroot.root======================//
  
  switch (argc)
  {
  case 1:
    break;
  case 2:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>filename;
    sstr.str("");
    sstr.clear();
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
    break;
  }

  rootname=rootname+".root";
  filename=filename+".dat";
  cout<<filename<<" to "<<rootname<<","<<endl;

  ifstream orgdata(filename.c_str());
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
    TFile f(rootname.c_str(),"update");
    
    //Parameters===========================================//
    //     t, dr, a, over_a, dover_a ,EB, e, T_orb, 
    //     XCM_BH, YCM_BH, ZCM_BH, VXCM_BH, VYCM_BH, VZCM_BH
    // dover_a: delta 1/a =================================//
    //=====================================================//
    Double_t t,dr,a,oa,doa,eb,e,torb;
    Double_t xcmbh,ycmbh,zcmbh,vxcmbh,vycmbh,vzcmbh;

    //data==============================================//
    // for black hole 1=================================//
    TTree *BHp=new TTree ("BHpars","Black hole binary parameters data");
    BHp->Branch("t",&t);
    BHp->Branch("dr",&dr);
    BHp->Branch("a",&a);
    BHp->Branch("over_a",&oa);
    BHp->Branch("dover_a",&doa);
    BHp->Branch("EB",&eb);
    BHp->Branch("e",&e);
    BHp->Branch("t_orb",&torb);
    BHp->Branch("xcm_bh",&xcmbh);
    BHp->Branch("ycm_bh",&ycmbh);
    BHp->Branch("zcm_bh",&zcmbh);
    BHp->Branch("vxcm_bh",&vxcmbh);
    BHp->Branch("vycm_bh",&vycmbh);
    BHp->Branch("vzcm_bh",&vzcmbh);

    Double_t overatmp=0;
    bool first=1;
    while (!orgdata.eof())
    {
      orgdata>>t;
      orgdata>>dr;
      orgdata>>a;
      orgdata>>oa;
      if (first)
      {
        first=0;
        doa=0;
      }
      else
        doa=oa-overatmp;
      overatmp=oa;
      orgdata>>eb;
      orgdata>>e;
      orgdata>>torb;
      orgdata>>xcmbh;
      orgdata>>ycmbh;
      orgdata>>zcmbh;
      orgdata>>vxcmbh;
      orgdata>>vycmbh;
      orgdata>>vzcmbh;

      BHp->Fill();
    }
    BHp->Write("",TObject::kOverwrite);
  }

  return 0;
}
