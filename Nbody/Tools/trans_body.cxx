//Transform reg_body.out to root format=============//
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
  pars_initial option(".trans_body_config");
  option.add("filenum","reg_body.out file number (used restart)",(int)1);
  option.add("rootname","rootname before _body.root, better use dir name","");
  option.add("needsplit","If need split body root file, input entry number for each file, or input 0",(int)0);
  option.add("savedir","root file save directory","./");
  option.initial(argc,argv);

  int filenum=option.get<int>("filenum");
  
  pars_initial dir(".trans_body_config.dir");
  for (int i=0; i<filenum;i++)
    dir.add("dir"+to<string>(i),"reg_body.out file directory name","./rs"+to<string>(i)+"/");
  dir.initial(argc,argv,option.getnextargc());
         
  //data transform====================================//
  ifstream *bodyin=new ifstream[filenum];
  bool allopen=1;
  for (int i=0;i<filenum; i++ )
  {
    bodyin[i].open((dir.get<string>("dir"+to<string>(i))+"reg_body.out").c_str());
    if(!bodyin[i].is_open())
      cerr<<"Error: "<<dir.get<string>("dir"+to<string>(i))+"reg_body.out not open!\n";
    allopen = allopen && bodyin[i].is_open();
  }
  if (!allopen)
  {
    cerr<<"Error: No enough reg_body.out file found! (required number: "<<filenum<<")\n";
    exit(1);
  }
  else
  {
    Double_t t;
    Float_t ecc1, pmin, semi, ecc;
    Float_t tm[3], tx[3], ty[3], tz[3], tvx[3], tvy[3], tvz[3];    //0: jump , 1,2: i1,i2
    Int_t tn[3];
    Float_t qm[4], qx[4], qy[4], qz[4], qvx[4], qvy[4], qvz[4];    //0,1: Our_i1/2,  2,3: i1,i2
    Int_t qn[4];
    
    int dirn=0;
    int filecount=0;
    int choose=0;
    string tmp;
    while (dirn<filenum)
    {
      int entrycount=1;
      string rootname=option.get<string>("rootname")+"_body_"+to<string>(filecount)+".root";     
      filecount++;
      TFile *f=new TFile((option.get<string>("savedir")+rootname).c_str(),"create");
      f->cd();
      //data==============================================//
      TTree *triple=new TTree("tri",(option.get<string>("rootname")+" triple data").c_str());
      triple->Branch("t",&t);
      triple->Branch("ecc1",&ecc1);
      triple->Branch("pmin",&pmin);
      triple->Branch("semi",&semi);
      triple->Branch("ecc",&ecc);
      triple->Branch("m",tm,"m[3]/F");
      triple->Branch("x",tx,"x[3]/F");
      triple->Branch("y",ty,"y[3]/F");
      triple->Branch("z",tz,"z[3]/F");
      triple->Branch("vx",tvx,"vx[3]/F");
      triple->Branch("vy",tvy,"vy[3]/F");
      triple->Branch("vz",tvz,"vz[3]/F");
      triple->Branch("n",tn,"n[3]/I");
      TTree *quater=new TTree("quat",(option.get<string>("rootname")+" quater data").c_str());
      quater->Branch("t",&t);
      quater->Branch("ecc1",&ecc1);
      quater->Branch("pmin",&pmin);
      quater->Branch("semi",&semi);
      quater->Branch("ecc",&ecc);
      quater->Branch("m",qm,"m[4]/F");
      quater->Branch("x",qx,"x[4]/F");
      quater->Branch("y",qy,"y[4]/F");
      quater->Branch("z",qz,"z[4]/F");
      quater->Branch("vx",qvx,"vx[4]/F");
      quater->Branch("vy",qvy,"vy[4]/F");
      quater->Branch("vz",qvz,"vz[4]/F");
      quater->Branch("n",qn,"n[4]/I");

      while(dirn<filenum&&!bodyin[dirn].eof())
      {
        if (entrycount>option.get<int>("needsplit")&&option.get<int>("needsplit")>0)
        {
          triple->Write("",TObject::kOverwrite);
          quater->Write("",TObject::kOverwrite);
          break;
        }
        
        bodyin[dirn]>>t;
        while (bodyin[dirn].fail()&&!bodyin[dirn].eof())
        {
          cerr<<"Error: IO fail! "<<rootname<<" index("<<entrycount<<"), t("<<t<<")!\n";
          bodyin[dirn].clear();
          getline(bodyin[dirn],tmp);
          bodyin[dirn]>>t;
        }
            
#ifdef DEBUG
        cout<<"now "<<entrycount<<"; t:"<<t<<endl<<flush;
#endif
        bodyin[dirn]>>qn[0];
        bodyin[dirn]>>qn[1];
        if (qn[1]==0)
        {
          choose=1;
          tn[0]=qn[0];
          bodyin[dirn]>>tn[1];
          bodyin[dirn]>>tn[2];
          bodyin[dirn]>>ecc1;
          bodyin[dirn]>>pmin;
          bodyin[dirn]>>semi;
          bodyin[dirn]>>ecc;
          bodyin[dirn]>>tm[0];
          bodyin[dirn]>>tm[1];
          bodyin[dirn]>>tm[1];
          bodyin[dirn]>>tm[2];
          bodyin[dirn]>>tx[0];
          bodyin[dirn]>>ty[0];
          bodyin[dirn]>>tz[0];
          bodyin[dirn]>>tvx[0];
          bodyin[dirn]>>tvy[0];
          bodyin[dirn]>>tvz[0];
          for (int jj=1;jj<=7;jj++)
            bodyin[dirn]>>tx[1];
          bodyin[dirn]>>ty[1];
          bodyin[dirn]>>tz[1];
          bodyin[dirn]>>tvx[1];
          bodyin[dirn]>>tvy[1];
          bodyin[dirn]>>tvz[1];
          bodyin[dirn]>>tx[2];
          bodyin[dirn]>>ty[2];
          bodyin[dirn]>>tz[2];
          bodyin[dirn]>>tvx[2];
          bodyin[dirn]>>tvy[2];
          bodyin[dirn]>>tvz[2];
          if (bodyin[dirn].fail()&&!bodyin[dirn].eof())
          {
            cerr<<"Error: IO fail! "<<rootname<<" index("<<entrycount<<"), t("<<t<<")!\n";
            bodyin[dirn].clear();
            getline(bodyin[dirn],tmp);
          }
          else if (!bodyin[dirn].eof())
          {
            triple->Fill();
            entrycount++;
          }
        }
        else
        {
          choose=2;
          bodyin[dirn]>>qn[2];
          bodyin[dirn]>>qn[3];
          bodyin[dirn]>>ecc1;
          bodyin[dirn]>>pmin;
          bodyin[dirn]>>semi;
          bodyin[dirn]>>ecc;
          for (int jj=0;jj<4;jj++)
            bodyin[dirn]>>qm[jj];
          for (int jj=0;jj<4;jj++)
          {
            bodyin[dirn]>>qx[jj];
            bodyin[dirn]>>qy[jj];
            bodyin[dirn]>>qz[jj];
            bodyin[dirn]>>qvx[jj];
            bodyin[dirn]>>qvy[jj];
            bodyin[dirn]>>qvz[jj];
          }
          if (bodyin[dirn].fail()&&!bodyin[dirn].eof())
          {
            cerr<<"Error: IO fail! "<<rootname<<" index("<<entrycount<<"), t("<<t<<")!\n";
            bodyin[dirn].clear();
            getline(bodyin[dirn],tmp);
          }
          else if (!bodyin[dirn].eof())
          {
            quater->Fill();
            entrycount++;
          }
        }
        if (bodyin[dirn].eof())
          dirn++;
      }
      if (dirn==filenum)
      {
        triple->Write("",TObject::kOverwrite);
        quater->Write("",TObject::kOverwrite);
      }
      triple->Delete();
      quater->Delete();
    }
    cout<<option.get<string>("rootname")<<" Finished."<<endl;
    ofstream fflag((dir.get<string>("dir0")+"body_finish").c_str());
    fflag<<"body finish successful!\n";
  }
  return 0;
}
