//bhdatatoroot======================================//
//lwang-edit, la,ld fix=============================//
//==Use to transform bh.dat to *.root===============//
//=================================================================//
//command:[prog.] [directory] [filename(.dat)*] [rootname(.root)*]=//
//========[directory] data file directory==========================//
//========[filename]: data filename--bh.dat(default)===============//
//========[rootname]: output root filename--bhroot.root(default)===//
//========Notes!: don't add filename and rootname suffix===========//
//=================================================================//
//==root structrue: Tree: BHTree1, BHtree2=========================//
//=======BHtree*: time_cur,mass,x,y,z,r,vx,vy,vz,v,pot,ax,ay,az,a==//
//=============== adotx,adoty,adotz,adot,dt,xb,yb,zb,rb,vbx,vby,vbz//
//=============== rb,Lx,Ly,Lz,Lr,Lalpha,Ldelta=====================//
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
  string rootname="bhroot";
  string filename="bh";
  string directory="./";
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
    sstr>>directory;
    sstr.str("");
    sstr.clear();
    break;
  case 3:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>directory;
    sstr.str("");
    sstr.clear();
    sstr<<argv[2];
    sstr>>filename;
    sstr.str("");
    sstr.clear();
    break;
  default:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>directory;
    sstr.str("");
    sstr.clear();
    sstr<<argv[2];
    sstr>>filename;
    sstr.str("");
    sstr.clear();
    sstr<<argv[3];
    sstr>>rootname;
    sstr.str("");
    sstr.clear();
    break;
  }

  rootname=rootname+".root";
  filename=filename+".dat";
  cout<<directory<<filename<<" to "<<rootname<<","<<endl;

  ifstream orgdata((directory+filename).c_str());
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
    //       time_cur, m[i], ^M
    //       x[i][0], x[i][1], x[i][2], tmp_r, ^M
    //       v[i][0], v[i][1], v[i][2], tmp_v, ^M
    //       pot[i], ^M
    //       a[i][0], a[i][1], a[i][2], tmp_a, ^M
    //       adot[i][0], adot[i][1], adot[i][2], tmp_adot, ^M
    //       dt[i]);^M
    // for black hole 1=================================//
    Double_t t_cur1;
    Double_t mass1;
    Double_t x1,y1,z1,r1;
    Double_t vx1,vy1,vz1,v1;
    Double_t xb1,yb1,zb1,rb1;
    Double_t vbx1,vby1,vbz1,vb1;
    Double_t pot1;
    Double_t ax1,ay1,az1,a1;
    Double_t adotx1,adoty1,adotz1,adot1;
    Double_t dt1;
    Double_t lx1,ly1,lz1,lalpha1,ldelta1;
    Double_t dlr1;
    Double_t lr1=0;
    // for black hole 2=================================//
    Double_t t_cur2;
    Double_t mass2;
    Double_t x2,y2,z2,r2;
    Double_t vx2,vy2,vz2,v2;
    Double_t xb2,yb2,zb2,rb2;
    Double_t vbx2,vby2,vbz2,vb2;
    Double_t pot2;
    Double_t ax2,ay2,az2,a2;
    Double_t adotx2,adoty2,adotz2,adot2;
    Double_t dt2;
    Double_t lx2,ly2,lz2,lalpha2,ldelta2;
    Double_t dlr2;
    Double_t lr2=0;
    
    //data==============================================//
    // for black hole 1=================================//
    TTree *BHTree1=new TTree ("BH1","Black hole 1 data");
    BHTree1->Branch("time_cur",&t_cur1);
    BHTree1->Branch("mass",&mass1);
    BHTree1->Branch("x",&x1);
    BHTree1->Branch("y",&y1);
    BHTree1->Branch("z",&z1);
    BHTree1->Branch("r",&r1);
    BHTree1->Branch("vx",&vx1);
    BHTree1->Branch("vy",&vy1);
    BHTree1->Branch("vz",&vz1);
    BHTree1->Branch("v",&v1);
    BHTree1->Branch("xb",&xb1);
    BHTree1->Branch("yb",&yb1);
    BHTree1->Branch("zb",&zb1);
    BHTree1->Branch("rb",&rb1);
    BHTree1->Branch("vbx",&vbx1);
    BHTree1->Branch("vby",&vby1);
    BHTree1->Branch("vbz",&vbz1);
    BHTree1->Branch("vb",&vb1);
    BHTree1->Branch("pot",&pot1);
    BHTree1->Branch("ax",&ax1);
    BHTree1->Branch("ay",&ay1);
    BHTree1->Branch("az",&az1);
    BHTree1->Branch("a",&a1);
    BHTree1->Branch("adotx",&adotx1);
    BHTree1->Branch("adoty",&adoty1);
    BHTree1->Branch("adotz",&adotz1);
    BHTree1->Branch("adot",&adot1);
    BHTree1->Branch("dt",&dt1);
    //angular momentum==================================//
    BHTree1->Branch("Lx",&lx1);
    BHTree1->Branch("Ly",&ly1);
    BHTree1->Branch("Lz",&lz1);
    BHTree1->Branch("Lr",&lr1);
    BHTree1->Branch("dLr",&dlr1);
    BHTree1->Branch("Lalpha",&lalpha1);
    BHTree1->Branch("Ldelta",&ldelta1);
    
    // for black hole 2=================================//
    TTree *BHTree2=new TTree ("BH2","Black hole 2 data");
    BHTree2->Branch("time_cur",&t_cur2);
    BHTree2->Branch("mass",&mass2);
    BHTree2->Branch("x",&x2);
    BHTree2->Branch("y",&y2);
    BHTree2->Branch("z",&z2);
    BHTree2->Branch("r",&r2);
    BHTree2->Branch("vx",&vx2);
    BHTree2->Branch("vy",&vy2);
    BHTree2->Branch("vz",&vz2);
    BHTree2->Branch("v",&v2);
    BHTree2->Branch("xb",&xb2);
    BHTree2->Branch("yb",&yb2);
    BHTree2->Branch("zb",&zb2);
    BHTree2->Branch("rb",&rb2);
    BHTree2->Branch("vbx",&vbx2);
    BHTree2->Branch("vby",&vby2);
    BHTree2->Branch("vbz",&vbz2);
    BHTree2->Branch("vb",&vb2);
    BHTree2->Branch("pot",&pot2);
    BHTree2->Branch("ax",&ax2);
    BHTree2->Branch("ay",&ay2);
    BHTree2->Branch("az",&az2);
    BHTree2->Branch("a",&a2);
    BHTree2->Branch("adotx",&adotx2);
    BHTree2->Branch("adoty",&adoty2);
    BHTree2->Branch("adotz",&adotz2);
    BHTree2->Branch("adot",&adot2);
    BHTree2->Branch("dt",&dt2);
    //angular momentum==================================//
    BHTree2->Branch("Lx",&lx2);
    BHTree2->Branch("Ly",&ly2);
    BHTree2->Branch("Lz",&lz2);
    BHTree2->Branch("Lr",&lr2);
    BHTree2->Branch("dLr",&dlr2);
    BHTree2->Branch("Lalpha",&lalpha2);
    BHTree2->Branch("Ldelta",&ldelta2);
    
    //new pars============================================//
    Double_t bh1m,bh1x,bh1y,bh1z,bh1vx,bh1vy,bh1vz;
    Double_t bh2m,bh2x,bh2y,bh2z,bh2vx,bh2vy,bh2vz;
    Double_t bhx,bhy,bhz,bhvx,bhvy,bhvz,bha2,bha;
    Double_t lxt,lyt,lzt,lrt,lxyt;

    while (!orgdata.eof())
    {
      // for BH1==========================================//
      orgdata>>t_cur1;
      orgdata>>mass1;
      orgdata>>x1;
      orgdata>>y1;
      orgdata>>z1;
      orgdata>>r1;
      orgdata>>vx1;
      orgdata>>vy1;
      orgdata>>vz1;
      orgdata>>v1;
      orgdata>>pot1;
      orgdata>>ax1;
      orgdata>>ay1;
      orgdata>>az1;
      orgdata>>a1;
      orgdata>>adotx1;
      orgdata>>adoty1;
      orgdata>>adotz1;
      orgdata>>adot1;
      orgdata>>dt1;

      // for BH2==========================================//
      orgdata>>t_cur2;
      orgdata>>mass2;
      orgdata>>x2;
      orgdata>>y2;
      orgdata>>z2;
      orgdata>>r2;
      orgdata>>vx2;
      orgdata>>vy2;
      orgdata>>vz2;
      orgdata>>v2;
      orgdata>>pot2;
      orgdata>>ax2;
      orgdata>>ay2;
      orgdata>>az2;
      orgdata>>a2;
      orgdata>>adotx2;
      orgdata>>adoty2;
      orgdata>>adotz2;
      orgdata>>adot2;
      orgdata>>dt2;

      // calculated bh coordinates data===================//
      bh1m=mass1;
      bh1x=x1;
      bh1y=y1;
      bh1z=z1;
      bh1vx=vx1;
      bh1vy=vy1;
      bh1vz=vz1;
      bh2m=mass2;
      bh2x=x2;
      bh2y=y2;
      bh2z=z2;
      bh2vx=vx2;
      bh2vy=vy2;
      bh2vz=vz2;
    
      bhx=(bh1m*bh1x+bh2m*bh2x)/(bh1m+bh2m);
      bhy=(bh1m*bh1y+bh2m*bh2y)/(bh1m+bh2m);
      bhz=(bh1m*bh1z+bh2m*bh2z)/(bh1m+bh2m);
      bhvx=(bh1m*bh1vx+bh2m*bh2vx)/(bh1m+bh2m);
      bhvy=(bh1m*bh1vy+bh2m*bh2vy)/(bh1m+bh2m);
      bhvz=(bh1m*bh1vz+bh2m*bh2vz)/(bh1m+bh2m);

      bha2=pow((bh1x-bh2x),2)+pow((bh1y-bh2y),2)+pow((bh1z-bh2z),2);
      bha=sqrt(bha2);

      xb1=x1-bhx;
      yb1=y1-bhy;
      zb1=z1-bhz;
      rb1=sqrt(xb1*xb1+yb1*yb1+zb1*zb1);
      vbx1=vx1-bhvx;
      vby1=vy1-bhvy;
      vbz1=vz1-bhvz;
      vb1=sqrt(vbx1*vbx1+vby1*vby1+vbz1*vbz1);
      
      xb2=x2-bhx;
      yb2=y2-bhy;
      zb2=z2-bhz;
      rb2=sqrt(xb2*xb2+yb2*yb2+zb2*zb2);
      vbx2=vx2-bhvx;
      vby2=vy2-bhvy;
      vbz2=vz2-bhvz;
      vb2=sqrt(vbx2*vbx2+vby2*vby2+vbz2*vbz2);

      // angular momentum calculation=====================//
      lxt=(-vby1*zb1+vbz1*yb1);
      lyt=(-vbz1*xb1+vbx1*zb1);
      lzt=(-vbx1*yb1+vby1*xb1);
      lrt=sqrt(lxt*lxt+lyt*lyt+lzt*lzt);
      lxyt=sqrt(lxt*lxt+lyt*lyt);
      lx1=mass1*lxt;
      ly1=mass1*lyt;
      lz1=mass1*lzt;
      dlr1=mass1*lrt-lr1;
      lr1=mass1*lrt;
      if (lxyt==0)
        lalpha1=0;
      else if (lyt>0)
        lalpha1=acos(lxt/lxyt);
      else
        lalpha1=2*3.1415926-acos(lxt/lxyt);
      ldelta1=acos(lzt/lrt);

      lxt=(-vby2*zb2+vbz2*yb2);
      lyt=(-vbz2*xb2+vbx2*zb2);
      lzt=(-vbx2*yb2+vby2*xb2);
      lrt=sqrt(lxt*lxt+lyt*lyt+lzt*lzt);
      lxyt=sqrt(lxt*lxt+lyt*lyt);
      lx2=mass2*lxt;
      ly2=mass2*lyt;
      lz2=mass2*lzt;
      dlr2=mass2*lrt-lr2;
      lr2=mass2*lrt;
      if (lxyt==0)
        lalpha2=0;
      else if (lyt>0)
        lalpha2=acos(lxt/lxyt);
      else
        lalpha2=2*3.1415926-acos(lxt/lxyt);
      ldelta2=acos(lzt/lrt);

      // Fill=============================================//
      BHTree1->Fill();
      BHTree2->Fill();
    }

    BHTree1->Write("",TObject::kOverwrite);
    BHTree2->Write("",TObject::kOverwrite);
  }

  return 0;
}
