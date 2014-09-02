//Calculate energy and L change for two time==============//
//Store in [dirname]-result.root==========================//
//Command: [prog.] [rootname] [treename1] [treename2] ====//
//         [newtreename] [newtreetitle]===================//
//Notes!: rootname do not need suffix===============//
//Tree: index,mass,t[2],E[2],dE,L[xyz][2],L[rad][2],[xyzr]b[2]//
//      vb[xyz ][2],pot[2],a[xyz][2]==========================//

#include <iomanip>
#include <utility>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"

using namespace std;

int main(int argc, char* argv[])
{
  //variables=========================================//
  string rootname;
  string newrootname;
  string treename[2];
  string newtreename;
  string newtreetitle;
  stringstream namestr;
  stringstream sstr;
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
      ifstream configf(".total-energy-change.conf");
      if (!configf.is_open())
        cout<<"No config file"<<endl;
      else
      {
        configf>>rootname;
        configf>>treename[0];
        configf>>treename[1];
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
    cout<<"Tree name at time start("<<treename[0]<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Tree name 1:";
      cin>>treename[0];
    }
    cout<<"Tree name at time end("<<treename[1]<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Tree name 2:";
      cin>>treename[1];
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
      ifstream configf(".total-energy-change.conf");
      if (!configf.is_open())
        cout<<"No config file"<<endl;
      else
      {
        configf>>rootname;
        configf>>treename[0];
        configf>>treename[1];
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
  case 6:
    namestr.str("");
    namestr.clear();
    namestr<<argv[1];
    namestr>>rootname;
    namestr.str("");
    namestr.clear();
    namestr<<argv[2];
    namestr>>treename[0];
    namestr.str("");
    namestr.clear();
    namestr<<argv[3];
    namestr>>treename[1];
    namestr.str("");
    namestr.clear();
    namestr<<argv[4];
    namestr>>newtreename;
    namestr.str("");
    namestr.clear();
    namestr<<argv[5];
    namestr>>newtreetitle;
    namestr.str("");
    namestr.clear();
    break;
  default:
    cout<<"input incomplete(pars number:"<<argc<<")"<<endl;
    return 0;
    break;
  }

  ofstream outconf(".total-energy-change.conf");
  outconf<<rootname<<endl;
  outconf<<treename[0]<<endl;
  outconf<<treename[1]<<endl;
  outconf<<newtreename<<endl;
  outconf<<newtreetitle<<endl;
  outconf.close();

  newrootname =rootname+"-result.root";
  rootname +="-star-extra.root";
  cout<<rootname<<":"<<treename[1]<<"-"<<treename[0]<<"->"<<newrootname<<":"<<newtreename<<"("<<newtreetitle<<")"<<endl;

  //analysis==========================================//
  TFile *f=new TFile(rootname.c_str(),"update");
  TFile *fn=new TFile(newrootname.c_str(),"update");
  fn->cd();
  
  //new tree==========================================//
  //index, mass, t_start, t_end, E_start, dE==========//
  //L[xyz]_[(start|end)]==============================//
  //L[(r|alpha|delta)]_[(start/end)]==================//
  //inherit from star data============================//

  TTree *ntree=new TTree (newtreename.c_str(),newtreetitle.c_str());
  Double_t mass,de,t[2],e[2],lx[2],ly[2],lz[2],lr[2],la[2],ld[2];
  Double_t x[2],y[2],z[2],vx[2],vy[2],vz[2],r[2],v[2];
  Double_t xb[2],yb[2],zb[2],vbx[2],vby[2],vbz[2],rb[2],vb[2];
  Double_t pot[2],ax[2],ay[2],az[2];
  Int_t index[2];
  //bh pars===========================================//
  Double_t bh1m[2],bh1x[2],bh1y[2],bh1z[2],bh1vx[2],bh1vy[2],bh1vz[2];
  Double_t bh2m[2],bh2x[2],bh2y[2],bh2z[2],bh2vx[2],bh2vy[2],bh2vz[2];
  Double_t bhx[2],bhy[2],bhz[2],bhvx[2],bhvy[2],bhvz[2],bha2[2],bha[2];
  //L pars============================================//
  Double_t lxt,lyt,lzt,lrt,lxyt;
  
  ntree->Branch("index",&index[0]);
  ntree->Branch("mass",&mass);
  ntree->Branch("dE",&de);
  //start=============================================//
  ntree->Branch("t_start",&t[0]);
  ntree->Branch("E_start",&e[0]);
  ntree->Branch("Lx_start",&lx[0]);
  ntree->Branch("Ly_start",&ly[0]);
  ntree->Branch("Lz_start",&lz[0]);
  ntree->Branch("Lr_start",&lr[0]);
  ntree->Branch("Lalpha_start",&la[0]);
  ntree->Branch("Ldelta_start",&ld[0]);
  //position & velocity in BH coordinate==============//
  ntree->Branch("xb_start",&xb[0]);
  ntree->Branch("yb_start",&yb[0]);
  ntree->Branch("zb_start",&zb[0]);
  ntree->Branch("rb_start",&rb[0]);
  ntree->Branch("vbx_start",&vbx[0]);
  ntree->Branch("vby_start",&vby[0]);
  ntree->Branch("vbz_start",&vbz[0]);
  ntree->Branch("vb_start",&vb[0]);
  //inherit===========================================//
  ntree->Branch("x_start",&x[0]);
  ntree->Branch("y_start",&y[0]);
  ntree->Branch("z_start",&z[0]);
  ntree->Branch("r_start",&r[0]);
  ntree->Branch("vx_start",&vx[0]);
  ntree->Branch("vy_start",&vy[0]);
  ntree->Branch("vz_start",&vz[0]);
  ntree->Branch("v_start",&v[0]);
  ntree->Branch("pot_start",&pot[0]);
  ntree->Branch("ax_start",&ax[0]);
  ntree->Branch("ay_start",&ay[0]);
  ntree->Branch("az_start",&az[0]);
  //end===============================================//
  ntree->Branch("t_end",&t[1]);
  ntree->Branch("E_end",&e[1]);
  ntree->Branch("Lx_end",&lx[1]);
  ntree->Branch("Ly_end",&ly[1]);
  ntree->Branch("Lz_end",&lz[1]);
  ntree->Branch("Lr_end",&lr[1]);
  ntree->Branch("Lalpha_end",&la[1]);
  ntree->Branch("Ldelta_end",&ld[1]);
  //position & velocity in BH coordinate==============//
  ntree->Branch("xb_end",&xb[1]);
  ntree->Branch("yb_end",&yb[1]);
  ntree->Branch("zb_end",&zb[1]);
  ntree->Branch("rb_end",&rb[1]);
  ntree->Branch("vbx_end",&vbx[1]);
  ntree->Branch("vby_end",&vby[1]);
  ntree->Branch("vbz_end",&vbz[1]);
  ntree->Branch("vb_end",&vb[1]);
  //inherit===========================================//
  ntree->Branch("x_end",&x[1]);
  ntree->Branch("y_end",&y[1]);
  ntree->Branch("z_end",&z[1]);
  ntree->Branch("r_end",&r[1]);
  ntree->Branch("vx_end",&vx[1]);
  ntree->Branch("vy_end",&vy[1]);
  ntree->Branch("vz_end",&vz[1]);
  ntree->Branch("v_end",&v[1]);
  ntree->Branch("pot_end",&pot[1]);
  ntree->Branch("ax_end",&ax[1]);
  ntree->Branch("ay_end",&ay[1]);
  ntree->Branch("az_end",&az[1]);

  //Ofstream warning =================================//
  ofstream errd("total-energy-change-err.log");
  //Get header tree===================================//
  Double_t t_cur1;
  Int_t nd1,PN[2];
  TTree *htree=(TTree*)(f->Get("HTree"));
  htree->SetBranchAddress("time_cur",&t_cur1);
  htree->SetBranchAddress("N",&nd1);
  
  //Get data tree=====================================//
  TTree **tt=new TTree*[2];
  for (Int_t i=0;i<2;i++)
  {
    tt[i]=(TTree*)(f->Get(treename[i].c_str()));
    tt[i]->SetBranchAddress("index",&index[i]);
    tt[i]->SetBranchAddress("mass",&mass);
    tt[i]->SetBranchAddress("x",&x[i]);
    tt[i]->SetBranchAddress("y",&y[i]);
    tt[i]->SetBranchAddress("z",&z[i]);
    tt[i]->SetBranchAddress("vx",&vx[i]);
    tt[i]->SetBranchAddress("vy",&vy[i]);
    tt[i]->SetBranchAddress("vz",&vz[i]);
    tt[i]->SetBranchAddress("r",&r[i]);
    tt[i]->SetBranchAddress("v",&v[i]);
    tt[i]->SetBranchAddress("pot",&pot[i]);
    tt[i]->SetBranchAddress("ax",&ax[i]);
    tt[i]->SetBranchAddress("ay",&ay[i]);
    tt[i]->SetBranchAddress("az",&az[i]);

    //get time_cur======================================//
    sstr.str("");
    sstr.clear();
    string ptree="";
    for (unsigned int j=1;j<treename[i].size();j++)
      ptree +=treename[i][j];
    sstr<<ptree;
    sstr>>PN[i];
    //lwang-debug=======================================//
    //Notes: problem:  PN[i] is larger than the Entries=//
    //       of htree. In fact, there were only 150 ====//
    //       trees of data in this root file and time===//
    //       steps of tree is not continued like 1,2,3==//
    //       but 0,8,16. So htree length is 150 but ====//
    //       PN[i] is 1200 in some cases. ==============//
    //       Since t_end is not important pars, this ===//
    //       problem is not fixed in order to prevent===//
    //       new trouble================================//
    cout<<"Get Time: Tree No."<<PN[i]<<endl;
    htree->GetEntry(PN[i]);
    t[i]=t_cur1;
    //lwang-debug-end===================================//

    //Get bh pars=======================================//
    tt[i]->GetEntry(nd1-2);
    bh1m[i]=mass;
    bh1x[i]=x[i];
    bh1y[i]=y[i];
    bh1z[i]=z[i];
    bh1vx[i]=vx[i];
    bh1vy[i]=vy[i];
    bh1vz[i]=vz[i];
    tt[i]->GetEntry(nd1-1);
    bh2m[i]=mass;
    bh2x[i]=x[i];
    bh2y[i]=y[i];
    bh2z[i]=z[i];
    bh2vx[i]=vx[i];
    bh2vy[i]=vy[i];
    bh2vz[i]=vz[i];

    bhx[i]=(bh1m[i]*bh1x[i]+bh2m[i]*bh2x[i])/(bh1m[i]+bh2m[i]);
    bhy[i]=(bh1m[i]*bh1y[i]+bh2m[i]*bh2y[i])/(bh1m[i]+bh2m[i]);
    bhz[i]=(bh1m[i]*bh1z[i]+bh2m[i]*bh2z[i])/(bh1m[i]+bh2m[i]);
    bhvx[i]=(bh1m[i]*bh1vx[i]+bh2m[i]*bh2vx[i])/(bh1m[i]+bh2m[i]);
    bhvy[i]=(bh1m[i]*bh1vy[i]+bh2m[i]*bh2vy[i])/(bh1m[i]+bh2m[i]);
    bhvz[i]=(bh1m[i]*bh1vz[i]+bh2m[i]*bh2vz[i])/(bh1m[i]+bh2m[i]);
  
    bha2[i]=pow((bh1x[i]-bh2x[i]),2)+pow((bh1y[i]-bh2y[i]),2)+pow((bh1z[i]-bh2z[i]),2);
    bha[i]=sqrt(bha2[i]);
  }
  
  //Get data all======================================//
  for(Int_t j=0;j<nd1-2;j++)
  {
    //Get the start and end data========================//
    for (Int_t i=0;i<2;i++)
    {
      tt[i]->GetEntry(j);
      //position and velocity in BH coordinate============//
      xb[i]=x[i]-bhx[i];
      yb[i]=y[i]-bhy[i];
      zb[i]=z[i]-bhz[i];
      rb[i]=sqrt(xb[i]*xb[i]+yb[i]*yb[i]+zb[i]*zb[i]);
      vbx[i]=vx[i]-bhvx[i];
      vby[i]=vy[i]-bhvy[i];
      vbz[i]=vz[i]-bhvz[i];
      vb[i]=sqrt(vbx[i]*vbx[i]+vby[i]*vby[i]+vbz[i]*vbz[i]);
      //Energy calculation================================//
      e[i]=(pot[i]+0.5*v[i]*v[i])*mass;
      //Angular momentum calculation======================//
      lxt=(-vby[i]*zb[i]+vbz[i]*yb[i]);
      lyt=(-vbz[i]*xb[i]+vbx[i]*zb[i]);
      lzt=(-vbx[i]*yb[i]+vby[i]*xb[i]);
      lrt=sqrt(lxt*lxt+lyt*lyt+lzt*lzt);
      lxyt=sqrt(lxt*lxt+lyt*lyt);
      lx[i]=mass*lxt;
      ly[i]=mass*lyt;
      lz[i]=mass*lzt;
      lr[i]=mass*lrt;
      if (lxyt==0)
        la[i]=0;
      if (lyt>0)
        la[i]=acos(lxt/lxyt);
      else
        la[i]=2*3.1415926-acos(lxt/lxyt);
      ld[i]=acos(lzt/lrt);
    }
    de=e[1]-e[0];
    if (j%100000==0)
      cout<<"Index "<<j<<" finished"<<endl;
    if (index[0]==index[1])
      ntree->Fill();
    else
    {
      cout<<"Warning: Index match fail! "<<index[0]<<" != "<<index[1]<<endl;
      errd<<index[0]<<" "<<index[1]<<endl;
    }
  }
  ntree->Write("",TObject::kOverwrite);
  return 0;
}
