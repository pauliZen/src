//Transform reg_single.out to root format=============//
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
  pars_initial option(".trans_single_config");
  option.add("filenum","reg_single.out file number (used restart)",(int)1);
  option.add("rootname","rootname before _single.root, better use dir name","");
  option.add("needsplit","If need split single root file, input entry number for each file, or input 0",(int)0);
  option.add("savedir","root file save directory","./");
  option.initial(argc,argv);

  int filenum=option.get<int>("filenum");
  
  pars_initial dir(".trans_single_config.dir");
  for (int i=0; i<filenum;i++)
    dir.add("dir"+to<string>(i),"reg_single.out file directory name","./rs"+to<string>(i)+"/");
  dir.initial(argc,argv,option.getnextargc());
         
  //data transform====================================//
  ifstream *singlein=new ifstream[filenum];
  bool allopen=1;
  for (int i=0;i<filenum; i++ )
  {
    singlein[i].open((dir.get<string>("dir"+to<string>(i))+"reg_single.out").c_str());
    if(!singlein[i].is_open())
      cerr<<"Error: "<<dir.get<string>("dir"+to<string>(i))+"reg_single.out not open!\n";
    allopen = allopen && singlein[i].is_open();
  }
  if (!allopen)
  {
    cerr<<"Error: No enough reg_single.out file found! (required number: "<<filenum<<")\n";
    exit(1);
  }
  else
  {
    Double_t t;
    Float_t peri, semi, ecc;
    Float_t m[2], x[2], y[2], z[2], vx[2], vy[2], vz[2];    //0: icomp , 1: jcomp
    Int_t n[2];
    
    int dirn=0;
    int filecount=0;
    string tmp;
    while (dirn<filenum)
    {
      int entrycount=1;
      string rootname=option.get<string>("rootname")+"_single_"+to<string>(filecount)+".root";     
      filecount++;
      TFile *f=new TFile((option.get<string>("savedir")+rootname).c_str(),"create");
      f->cd();
      //data==============================================//
      TTree *single=new TTree("sing",(option.get<string>("rootname")+" single data").c_str());
      single->Branch("t",&t);
      single->Branch("peri",&peri);
      single->Branch("semi",&semi);
      single->Branch("ecc",&ecc);
      single->Branch("m",m,"m[2]/F");
      single->Branch("x",x,"x[2]/F");
      single->Branch("y",y,"y[2]/F");
      single->Branch("z",z,"z[2]/F");
      single->Branch("vx",vx,"vx[2]/F");
      single->Branch("vy",vy,"vy[2]/F");
      single->Branch("vz",vz,"vz[2]/F");
      single->Branch("n",n,"n[2]/I");

      while(dirn<filenum&&!singlein[dirn].eof())
      {
        if (entrycount>option.get<int>("needsplit")&&option.get<int>("needsplit")>0)
        {
          single->Write("",TObject::kOverwrite);
#ifdef DEBUG
          cout<<"new file\n";
#endif
          break;
        }
        
        singlein[dirn]>>t;
        while (singlein[dirn].fail()&&!singlein[dirn].eof())
        {
          cerr<<"Error: IO fail! "<<rootname<<" index("<<entrycount<<"), t("<<t<<")!\n";
          singlein[dirn].clear();
          getline(singlein[dirn],tmp);
          singlein[dirn]>>t;
        }
            
#ifdef DEBUG
        cout<<"now "<<entrycount<<"; t:"<<t<<endl<<flush;
#endif
        singlein[dirn]>>n[0];
        singlein[dirn]>>n[1];
        singlein[dirn]>>semi;
        singlein[dirn]>>peri;
        singlein[dirn]>>ecc;
        singlein[dirn]>>m[0];
        singlein[dirn]>>m[1];
        singlein[dirn]>>x[0];
        singlein[dirn]>>y[0];
        singlein[dirn]>>z[0];
        singlein[dirn]>>vx[0];
        singlein[dirn]>>vy[0];
        singlein[dirn]>>vz[0];
        singlein[dirn]>>x[1];
        singlein[dirn]>>y[1];
        singlein[dirn]>>z[1];
        singlein[dirn]>>vx[1];
        singlein[dirn]>>vy[1];
        singlein[dirn]>>vz[1];
        if (singlein[dirn].fail()&&!singlein[dirn].eof())
        {
          cerr<<"Error: IO fail! "<<rootname<<" index("<<entrycount<<"), t("<<t<<")!\n";
          singlein[dirn].clear();
          getline(singlein[dirn],tmp);
        }
        else if (!singlein[dirn].eof())
        {
          single->Fill();
          entrycount++;
        }
        if (singlein[dirn].eof())
          dirn++;
      }
      if (dirn==filenum)
      {
        single->Write("",TObject::kOverwrite);
        cout<<"Write to File.\n";
      }
      single->Delete();
    }
    cout<<option.get<string>("rootname")<<" Finished."<<endl;
    ofstream fflag((dir.get<string>("dir0")+"single_finish").c_str());
    fflag<<"single finish successful!\n";
  }
  for (int i=0;i<filenum; i++) singlein[i].close();
  delete[] singlein;
  return 0;
}
