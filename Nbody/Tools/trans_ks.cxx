//Transform ks_term.out to root format=============//
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
  //parameters initial================================//
  pars_initial option(".trans_ks_config");
  option.add("filenum","ks_term.out file number (used restart)",(int)1);
  option.add("rootname","rootname before _ks.root, better use dir name","");
  option.add("needsplit","If need split ks root file, input entry number for each file, or input 0",(int)0);
  option.add("savedir","root file save directory","./");
  option.initial(argc,argv);

  int filenum=option.get<int>("filenum");
  
  pars_initial dir(".trans_ks_config.dir");
  for (int i=0; i<filenum;i++)
    dir.add("dir"+to<string>(i),"ks_term.out file directory name","./rs"+to<string>(i)+"/");
  dir.initial(argc,argv,option.getnextargc());
         
  //data transform====================================//
  ifstream *ksin=new ifstream[filenum];
  bool allopen=1;
  for (int i=0;i<filenum; i++ )
  {
    ksin[i].open((dir.get<string>("dir"+to<string>(i))+"ks_term.out").c_str());
    if(!ksin[i].is_open())
      cerr<<"Error: "<<dir.get<string>("dir"+to<string>(i))+"ks_term.out not open!\n";
    allopen = allopen && ksin[i].is_open();
  }
  if (!allopen)
  {
    cerr<<"Error: No enough ks_term.out file found! (required number: "<<filenum<<")\n";
    exit(1);
  }
  else
  {
    Double_t t;
    Float_t semi;
    Float_t m[2]; //0: I1, 1: I2
    Int_t n[2];
    
    int dirn=0;
    int filecount=0;
    string tmp;
    while (dirn<filenum)
    {
      int entrycount=1;
      string rootname=option.get<string>("rootname")+"_ks_"+to<string>(filecount)+".root";     
      filecount++;
      TFile *f=new TFile((option.get<string>("savedir")+rootname).c_str(),"create");
      f->cd();
      //data==============================================//
      TTree *ks=new TTree("ks",(option.get<string>("rootname")+" ks data").c_str());
      ks->Branch("t",&t);
      ks->Branch("semi",&semi);
      ks->Branch("m",m,"m[2]/F");
      ks->Branch("n",n,"n[2]/I");

      while(dirn<filenum&&!ksin[dirn].eof())
      {
        if (entrycount>option.get<int>("needsplit")&&option.get<int>("needsplit")>0)
        {
          ks->Write("",TObject::kOverwrite);
#ifdef DEBUG
          cout<<"new file\n";
#endif
          break;
        }
        
        ksin[dirn]>>t;
        while (ksin[dirn].fail()&&!ksin[dirn].eof())
        {
          cerr<<"Error: IO fail! "<<rootname<<" index("<<entrycount<<"), t("<<t<<")!\n";
          ksin[dirn].clear();
          getline(ksin[dirn],tmp);
          ksin[dirn]>>t;
        }
            
#ifdef DEBUG
        cout<<"now "<<entrycount<<"; t:"<<t<<endl<<flush;
#endif
        ksin[dirn]>>n[0];
        ksin[dirn]>>n[1];
        ksin[dirn]>>semi;
        ksin[dirn]>>m[0];
        ksin[dirn]>>m[1];
        if (ksin[dirn].fail()&&!ksin[dirn].eof())
        {
          cerr<<"Error: IO fail! "<<rootname<<" index("<<entrycount<<"), t("<<t<<")!\n";
          ksin[dirn].clear();
          getline(ksin[dirn],tmp);
        }
        else if (!ksin[dirn].eof())
        {
          ks->Fill();
          entrycount++;
        }
        if (ksin[dirn].eof())
          dirn++;
      }
      if (dirn==filenum)
      {
        ks->Write("",TObject::kOverwrite);
      }
      ks->Delete();
    }
    cout<<option.get<string>("rootname")<<" Finished."<<endl;
    ofstream fflag((dir.get<string>("dir0")+"ks_finish").c_str());
    fflag<<"ks_term finish successful!\n";
  }
  return 0;
}
