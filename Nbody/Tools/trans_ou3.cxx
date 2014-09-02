//Transform OUT3 to root format=====================//
//Intro: transform OUT3/58 to [dirname]-out3.root===//
//       OUT3 should in current directory===========//
//Command: [prog.] datadirname, savedir=============//
//Structure: =======================================//
//     Tree: out3: t: astronomical time=============//
//                 m: astronomical unit=============//
//                 r[3]: astronomical unit==========//
//                 v[3]: astronomical unit==========//
//                 n: particle name=================//
//                 kstar: star types==e=============//
//           pars: ntot: total particle number======//
//                 model: ==========================//
//                 nrun: ===========================//
//                 nk: =============================//
//                 t: astronomical time=============//
//                 tstar: unit scale for time=======//
//                 zmbar: unit scale for mass=======//
//                 rbar: unit scale for distance====//
//                 vstar: unit scale for velocity===//
//                 ak(nk): nk=20====================//
//History: Jun 26, 2012: recreated...===============//
//         Jun 29, 2012: complete for Nbody6_new====//
//                       2012Jun29 version==========//
//#define DEBUG

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

#include "initial.h"
#include "uftools.h"
#include "TFile.h"
#include "TTree.h"

using namespace std;

int main(int argc, char* argv[])
{
#ifdef DEBUG
  cout<<"Debug:\n";
#endif  
  //parameters initial================================//
  pars_initial option(".trans_out3_config");
  option.add("filenum","OUT3/58 file number (used restart)",(int)1);
  option.add("rootname","rootname before _out3/58.root, better use dir name","");
  option.add("needsplit","If need split OUT3 root file, input entry number for each file, or input 0",(int)0);
  option.add("savedir","root file save directory","./");
  option.add("nstar","initial star number",(int)1000);
  option.add("nplanet","initial planet number",(int)1000);
  option.add("nbin","initial binaries",(int)200);
  option.initial(argc,argv);

  int filenum=option.get<int>("filenum");
  
  pars_initial dir(".trans_out3_config.dir");
  for (int i=0; i<filenum;i++)
    dir.add("dir"+to<string>(i),"OUT3/58 file directory name","./rs"+to<string>(i)+"/");
  dir.initial(argc,argv,option.getnextargc());
         
  //data transform====================================//
  ifstream *datain=new ifstream[filenum];
  ifstream *parsin=new ifstream[filenum];
  bool allopen=1;
  for (int i=0;i<filenum; i++ )
  {
    datain[i].open((dir.get<string>("dir"+to<string>(i))+"OUT3").c_str());
    parsin[i].open((dir.get<string>("dir"+to<string>(i))+"OUT58").c_str());
    if(!datain[i].is_open())
      cerr<<"Error: "<<dir.get<string>("dir"+to<string>(i))+"OUT3 not open!\n";
    if(!parsin[i].is_open())
      cerr<<"Error: "<<dir.get<string>("dir"+to<string>(i))+"OUT58 not open!\n";
    allopen = allopen && datain[i].is_open() && parsin[i].is_open();
  }
  if (!allopen)
  {
    cerr<<"Error: No enough OUT3/58 file found! (required number: "<<filenum<<")\n";
    exit(1);
  }
  else
  {
    int filecount=0;
#ifdef DEBUG
    cout<<"Begin\n";
#endif    
    string rootname=option.get<string>("rootname")+"_out3_"+to<string>(filecount)+".root";
    Int_t nstar=option.get<int>("nstar");
    Int_t nplanet=option.get<int>("nplanet");
    Int_t nbin=option.get<int>("nbin");
    Int_t nsp=nstar+nplanet, ntt=nsp+nbin;
    Float_t t, m, r[4], v[4], as[20];
    Int_t ntot, model, nrun, nk, n, kstar;
    Double_t tstar,zmbar,rbar,vstar;
    
    TFile *f=new TFile((option.get<string>("savedir")+rootname).c_str(),"create");
    f->cd();
    //header============================================//
    TTree *pars=new TTree("pars",(option.get<string>("rootname")+" OUT3 data").c_str());
    pars->Branch("t",&t);
    pars->Branch("ntot",&ntot);
    pars->Branch("model",&model);
    pars->Branch("nrun",&nrun);
    pars->Branch("nk",&nk);
    pars->Branch("as",as,"as[20]/F");
    //scale=============================================//
    TTree *scal=new TTree("scal",(option.get<string>("rootname")+" scale factor").c_str());
    scal->Branch("tstar",&tstar);
    scal->Branch("zmbar",&zmbar);
    scal->Branch("rbar",&rbar);
    scal->Branch("vstar",&vstar);
    // parsin[0]>>tstar;
    // parsin[0]>>zmbar;
    // parsin[0]>>rbar;
    // parsin[0]>>vstar;
    // scal->Fill();
    // scal->Write("",TObject::kOverwrite);
#ifdef DEBUG
    cout<<"scal finish\n"<<flush;
#endif    
    for(int i=0;i<filenum;i++)
    {
      parsin[i]>>tstar;
      parsin[i]>>zmbar;
      parsin[i]>>rbar;
      parsin[i]>>vstar;
      if (i==0)
      {
        scal->Fill();
        scal->Write("",TObject::kOverwrite);
      }
      while(!parsin[i].eof())
      {
        parsin[i]>>t;
#ifdef DEBUG
        cout<<"now "<<t<<endl<<flush;
#endif        
        parsin[i]>>ntot;
        parsin[i]>>model;
        parsin[i]>>nrun;
        parsin[i]>>nk;
        for (int j=0;j<20;j++)
          parsin[i]>>as[j];
        if (!parsin[i].eof())
          pars->Fill();
      }
    }
    pars->Write("",TObject::kOverwrite);
#ifdef DEBUG
    cout<<"pars finished\n"<<flush;
#endif    
    int dirn=0;
    while (dirn<filenum)
    {
      int entrycount=1;
      if (filecount==0)
      {
        filecount++;
      }
      else
      {
        rootname=option.get<string>("rootname")+"_out3_"+to<string>(filecount)+".root";     
        filecount++;
        f=new TFile((option.get<string>("savedir")+rootname).c_str(),"create");
      }
      f->cd();
      //data==============================================//
      TTree *out3s=new TTree("out3s",(option.get<string>("rootname")+" OUT3 star data").c_str());
      TTree *out3p=new TTree("out3p",(option.get<string>("rootname")+" OUT3 planet data").c_str());
      TTree *out3c=new TTree("out3c",(option.get<string>("rootname")+" OUT3 center mass data").c_str());
      out3s->Branch("t",&t);
      out3s->Branch("m",&m);
      out3s->Branch("r",r,"r[4]/F");
      out3s->Branch("v",v,"v[4]/F");
      out3s->Branch("n",&n);
      out3s->Branch("kstar",&kstar);
      out3p->Branch("t",&t);
      out3p->Branch("m",&m);
      out3p->Branch("r",r,"r[4]/F");
      out3p->Branch("v",v,"v[4]/F");
      out3p->Branch("n",&n);
      out3p->Branch("kstar",&kstar);
      out3c->Branch("t",&t);
      out3c->Branch("m",&m);
      out3c->Branch("r",r,"r[4]/F");
      out3c->Branch("v",v,"v[4]/F");
      out3c->Branch("n",&n);
      out3c->Branch("kstar",&kstar);
      while(dirn<filenum&&!datain[dirn].eof())
      {
#ifdef DEBUG
        if (entrycount%1000==0)
          cout<<"Now: "<<entrycount<<endl<<flush;
#endif	
        if (entrycount>option.get<int>("needsplit")&&option.get<int>("needsplit")>0)
        {
          out3s->Write("",TObject::kOverwrite);
          out3p->Write("",TObject::kOverwrite);
          out3c->Write("",TObject::kOverwrite);
          f->Close();
          break;
        }
        datain[dirn]>>t;
        datain[dirn]>>m;
        datain[dirn]>>r[0];
        datain[dirn]>>r[1];
        datain[dirn]>>r[2];
        r[3]=sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
        datain[dirn]>>v[0];
        datain[dirn]>>v[1];
        datain[dirn]>>v[2];
        v[3]=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
        datain[dirn]>>n;
        datain[dirn]>>kstar;
        if (!datain[dirn].eof())
        {
          if ((n>0&&n<=nstar)||(n>nsp&&n<=ntt)) out3s->Fill();
          else if (n>nstar&&n<=nsp) out3p->Fill();
          else out3c->Fill();
          entrycount++;
        }
        if (datain[dirn].eof())
          dirn++;
      }
      if (dirn==filenum)
      {
        out3s->Write("",TObject::kOverwrite);
        out3p->Write("",TObject::kOverwrite);
        out3c->Write("",TObject::kOverwrite);
      }
      out3s->Delete();
      out3p->Delete();
      out3c->Delete();
    }
    cout<<option.get<string>("rootname")<<" Finished."<<endl;
    ofstream fflag((dir.get<string>("dir0")+"out3_finish").c_str());
    fflag<<"out3 finish successful!\n";
  }
  return 0;
}
