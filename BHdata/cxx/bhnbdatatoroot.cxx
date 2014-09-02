//bhnbdatatoroot====================================//
//lwang-edit========================================//
//==Use to transform bh.dat to *.root===============//
//=================================================================//
//command:[prog.] [filename(.dat)*] [rootname(.root)*] [neigbnum*] //
//========[filename]: data filename--bh_nb.dat(default)============//
//========[rootname]: output root filename--bh_nb.root(default)====//
//========[neigbnum]: bh neighbor numbers--50(default)=============//
//========Notes!: don't add filename and rootname suffix===========//
//=================================================================//
//==root structrue: Tree: BHnbTree1,BHnbTree2======================//
//=====BHnbtree*: time_cur,group,No,index,mass,x,y,z,rb,vx,vy,vz,vb//
//=================================================================//

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
  string rootname="bh_nb";
  string filename="bh_nb";
  int neigbnum=50;
  stringstream sstr;
  sstr.str("");
  sstr.clear();

  //Error=============================================//
  string err1="Error pars: transtoroot [filename(.dat)] [rootfilename(.root)]";
  string err2="Error filename: no such filename";
  string err3="Error file: reach the end";
  
  //Input=============================================//
  //Pars: filename(no .dat), rootname(no .root), =====//
  //Default: bh_nb.dat, bh_nb.root====================//
  
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
    break;
  default :
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
    sstr>>neigbnum;
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
    TFile f(rootname.c_str(),"create");
    
    //Parameters========================================//
    // time_cur, 
    // i_bh, 
    // m[i_bh], 
    // x[i_bh][0], x[i_bh][1], x[i_bh][2], 
    // v[i_bh][0], v[i_bh][1], v[i_bh][2]);
    // j, i, 
    // m[i], 
    // x[i][0], x[i][1], x[i][2], tmp_r, 
    // v[i][0], v[i][1], v[i][2], tmp_v);

    // for black hole 1=================================//
    // Double_t t_curb1, indexb1;
    // Double_t massb1;
    // Double_t xb1,yb1,zb1,rb1;
    // Double_t vxb1,vyb1,vzb1,vb1;
    Double_t t_cur1,mass1;
    Int_t num1,index1,group1;
    Double_t x1,y1,z1,r1;
    Double_t vx1,vy1,vz1,v1;
    
    // for black hole 2=================================//
    // Double_t t_curb2, indexb2;
    // Double_t massb2;
    // Double_t xb2,yb2,zb2,rb2;
    // Double_t vxb2,vyb2,vzb2,vb2;
    Double_t t_cur2,mass2;
    Int_t num2,index2,group2;
    Double_t x2,y2,z2,r2;
    Double_t vx2,vy2,vz2,v2;
    
    //data==============================================//
    // for black hole 1=================================//
    // TTree *BHTree1=new TTree ("BH1","Black hole 1 data");

    // BHTree1->Branch("No",&num1);
    // BHTree1->Branch("index",&indexb1);
    // BHTree1->Branch("mass",&massb1);
    // BHTree1->Branch("x",&xb1);
    // BHTree1->Branch("y",&yb1);
    // BHTree1->Branch("z",&zb1);
    // BHTree1->Branch("r",&rb1);
    // BHTree1->Branch("vx",&vxb1);
    // BHTree1->Branch("vy",&vyb1);
    // BHTree1->Branch("vz",&vzb1);
    // BHTree1->Branch("v",&vb1);

    TTree *BHnbTree1=new TTree ("BH1nb","Black hole one 50 neighbors data, first is BH");
    BHnbTree1->Branch("time_cur",&t_cur1);
    BHnbTree1->Branch("group",&group1);
    BHnbTree1->Branch("No",&num1);
    BHnbTree1->Branch("index",&index1);
    BHnbTree1->Branch("mass",&mass1);
    BHnbTree1->Branch("x",&x1);
    BHnbTree1->Branch("y",&y1);
    BHnbTree1->Branch("z",&z1);
    BHnbTree1->Branch("rb",&r1);
    BHnbTree1->Branch("vx",&vx1);
    BHnbTree1->Branch("vy",&vy1);
    BHnbTree1->Branch("vz",&vz1);
    BHnbTree1->Branch("vb",&v1);

    // for black hole 2=================================//
    // TTree *BHTree2=new TTree ("BH2","Black hole 2 data");

    // BHTree2->Branch("index",&indexb2);
    // BHTree2->Branch("mass",&massb2);
    // BHTree2->Branch("x",&xb2);
    // BHTree2->Branch("y",&yb2);
    // BHTree2->Branch("z",&zb2);
    // BHTree2->Branch("r",&rb2);
    // BHTree2->Branch("vx",&vxb2);
    // BHTree2->Branch("vy",&vyb2);
    // BHTree2->Branch("vz",&vzb2);
    // BHTree2->Branch("v",&vb2);

    TTree *BHnbTree2=new TTree ("BH2nb","Black hole two 50 neighbors data, first is BH");
    BHnbTree2->Branch("time_cur",&t_cur2);
    BHnbTree2->Branch("group",&group2);
    BHnbTree2->Branch("No",&num2);
    BHnbTree2->Branch("index",&index2);
    BHnbTree2->Branch("mass",&mass2);
    BHnbTree2->Branch("x",&x2);
    BHnbTree2->Branch("y",&y2);
    BHnbTree2->Branch("z",&z2);
    BHnbTree2->Branch("rb",&r2);
    BHnbTree2->Branch("vx",&vx2);
    BHnbTree2->Branch("vy",&vy2);
    BHnbTree2->Branch("vz",&vz2);
    BHnbTree2->Branch("vb",&v2);

    group1=group2=0;
    while (!orgdata.eof())
    {
      // for BH1==========================================//
      group1++;
      orgdata>>t_cur1;
      num1=0;
      orgdata>>index1;
      orgdata>>mass1;
      orgdata>>x1;
      orgdata>>y1;
      orgdata>>z1;
      r1=sqrt(x1*x1+y1*y1+z1*z1);
      orgdata>>vx1;
      orgdata>>vy1;
      orgdata>>vz1;
      v1=sqrt(vx1*vx1+vy1*vy1+vz1*vz1);

      BHnbTree1->Fill();

      // for BH1-nb=======================================//
      
      for (int i=1;i<neigbnum;i++)
      {
        orgdata>>num1;
        orgdata>>index1;
        orgdata>>mass1;
        orgdata>>x1;
        orgdata>>y1;
        orgdata>>z1;
        orgdata>>r1;
        orgdata>>vx1;
        orgdata>>vy1;
        orgdata>>vz1;
        orgdata>>v1;
        BHnbTree1->Fill();
      }
      
      // for BH2==========================================//
      group2++;
      orgdata>>t_cur2;
      num2=0;
      orgdata>>index2;
      orgdata>>mass2;
      orgdata>>x2;
      orgdata>>y2;
      orgdata>>z2;
      r2=sqrt(x2*x2+y2*y2+z2*z2);
      orgdata>>vx2;
      orgdata>>vy2;
      orgdata>>vz2;
      v2=sqrt(vx2*vx2+vy2*vy2+vz2*vz2);

      BHnbTree2->Fill();

      // for BH2-nb=======================================//
      
      for (int i=1;i<neigbnum;i++)
      {
        orgdata>>num2;
        orgdata>>index2;
        orgdata>>mass2;
        orgdata>>x2;
        orgdata>>y2;
        orgdata>>z2;
        orgdata>>r2;
        orgdata>>vx2;
        orgdata>>vy2;
        orgdata>>vz2;
        orgdata>>v2;
        BHnbTree2->Fill();
      }
    }
    BHnbTree1->Write("",TObject::kOverwrite);
    BHnbTree2->Write("",TObject::kOverwrite);
  }

  return 0;
}
