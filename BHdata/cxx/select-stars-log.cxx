// Version 2 =======================================//
// scan stars in all time from index file list======//
// then store them in new tree in -result.root======//
// add black hole center coordinates velocity and ==//
// distance and total energy to each black hole=====//
//Use: [prog.] [rootname] [treename] [treetitle]    //
//     [starindex] [timeindex] [bhsplitnumber]      //
//Input: rootname: star data rootname===============//
//                 eg. run-020-020-1mil (no suffix) //
//       treename: new tree name to store data======//
//       treetitle: new tree title==================//
//       starindex: select star index file          //
//                  eg. [dirname]-select-star.index //
//                  (should remove black hole index)//
//       timeindex: data file time list             //
//                  eg. [dirname]-dat.lst===========//
//       bhsplitnumber: bhpar time interval/star's  //
//pars: [xyzr]b: position in BH center coordinate   //
//      vb[xyz ]: velocity in BH center coordinate  //
//      as[xyz]: acceleration only from all stars   //
//      pots: potential only of stars               //
//      etot: total energy in original coordinate   //
//      etot_rcm: energy remove BHs center mass     //
//                kinematical energy                //
//      L[xyz]: angular momentum related to BHs     //
//              center in (x,y,z) coordinates       //
//      L[r(alpha)(delta)]: L[xyz] transformed to   //
//                          spherical coordinates   //
//                alpha: angle from x to y          //
//                delta: angle from z to xy plane   //

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
  string bhparrootname;
  string newrootname;
  string newtreename;
  string newtreetitle;
  string starindex;
  string timeindex;
  int bhsplit;
  char inflagc='y';
  bool inflag=1;
  stringstream namestr;
  stringstream sstr;
  string checksh;

  switch (argc)
  {
  case 1:
    cout<<"Load last input(y/n)?";
    cin>>inflagc;
    if (inflagc=='n')
      inflag=0;
    if (inflag)
    {
      ifstream configf(".vselect-star.conf");
      if (!configf.is_open())
        cout<<"No config file"<<endl;
      else
      {
        configf>>rootname;
        configf>>newtreename;
        configf>>newtreetitle;
        configf>>starindex;
        configf>>timeindex;
        configf>>bhsplit;
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
    cout<<"Star Index name("<<starindex<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input star index file name:";
      cin>>starindex;
    }
    cout<<"Time index name("<<timeindex<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input time index file name:";
      cin>>timeindex;
    }
    cout<<"bh-par timestep split number("<<bhsplit<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input bh-par timestep split number:";
      cin>>bhsplit;
    }
    break;
  case 2:
    namestr.str("");
    namestr.clear();
    namestr<<argv[1];
    namestr>>checksh;
    if (checksh=="-l")
    {
      ifstream configf(".vselect-star.conf");
      if (!configf.is_open())
        cout<<"No config file"<<endl;
      else
      {
        configf>>rootname;
        configf>>newtreename;
        configf>>newtreetitle;
        configf>>starindex;
        configf>>timeindex;
        configf>>bhsplit;
        configf.close();
      }
    }
    else
    {
      cout<<"input incomplete"<<endl;
      return 0;
    }
    break;
  case 7:
    namestr.str("");
    namestr.clear();
    namestr<<argv[1];
    namestr>>rootname;
    namestr.str("");
    namestr.clear();
    namestr<<argv[2];
    namestr>>newtreename;
    namestr.str("");
    namestr.clear();
    namestr<<argv[3];
    namestr>>newtreetitle;
    namestr.str("");
    namestr.clear();
    namestr<<argv[4];
    namestr>>starindex;
    namestr.str("");
    namestr.clear();
    namestr<<argv[5];
    namestr>>timeindex;
    namestr.str("");
    namestr.clear();
    namestr<<argv[6];
    namestr>>bhsplit;
    namestr.str("");
    namestr.clear();
    break;
  default:
    cout<<"input incomplete"<<endl;
    return 0;
    break;
  }

  ofstream outconf(".vselect-star.conf");
  outconf<<rootname<<endl;
  outconf<<newtreename<<endl;
  outconf<<newtreetitle<<endl;
  outconf<<starindex<<endl;
  outconf<<timeindex<<endl;
  outconf<<bhsplit<<endl;
  outconf.close();

  newrootname=rootname+"-result.root";
  bhparrootname=rootname+"-bhpar.root";
  rootname=rootname+"-star-extra.root";

  //analysis==========================================//
  TFile *fn=new TFile(rootname.c_str(),"update");
  TFile *fb=new TFile(bhparrootname.c_str(),"update");
  TFile *f2=new TFile(newrootname.c_str(),"update");
  
  //new tree =========================================//
  TTree *nntree=new TTree (newtreename.c_str(),newtreetitle.c_str());
  Double_t t_cur,mass;
  Int_t index;
  Double_t x,y,z,r,xb,yb,zb,rb;
  Double_t vx,vy,vz,v,vbx,vby,vbz,vb;
  Double_t ax,ay,az,pot,pots,etot,etotrcm;
  Double_t asx,asy,asz;
  Double_t lx,ly,lz,lr,la,ld;
  Double_t abh;
  //temp pars=========================================//
  Double_t lxt,lyt,lzt,lrt,lxyt;
  Double_t bh1m,bh1x,bh1y,bh1z,bh1vx,bh1vy,bh1vz;
  Double_t bh2m,bh2x,bh2y,bh2z,bh2vx,bh2vy,bh2vz;
  Double_t bhx,bhy,bhz,bhvx,bhvy,bhvz,bha2,bha,bhv2;
  Double_t dbh21,dbh22,dbh1,dbh2;
  Double_t lbh12[3];

  //inherit pars======================================//
  nntree->Branch("time_cur",&t_cur);
  nntree->Branch("index",&index);
  nntree->Branch("mass",&mass);
  nntree->Branch("x",&x);
  nntree->Branch("y",&y);
  nntree->Branch("z",&z);
  nntree->Branch("r",&r);
  nntree->Branch("vx",&vx);
  nntree->Branch("vy",&vy);
  nntree->Branch("vz",&vz);
  nntree->Branch("v",&v);
  nntree->Branch("pot",&pot);
  nntree->Branch("ax",&ax);
  nntree->Branch("ay",&ay);
  nntree->Branch("az",&az);
  //new pars==========================================//
  //position and velocity in black hole coordinate====//
  nntree->Branch("xb",&xb);
  nntree->Branch("yb",&yb);
  nntree->Branch("zb",&zb);
  nntree->Branch("rb",&rb);
  nntree->Branch("vbx",&vbx);
  nntree->Branch("vby",&vby);
  nntree->Branch("vbz",&vbz);
  nntree->Branch("vb",&vb);
  //acceleration & potential of stars and energy======//
  nntree->Branch("asx",&asx);
  nntree->Branch("asy",&asy);
  nntree->Branch("asz",&asz);
  nntree->Branch("pots",&pots);
  nntree->Branch("etot",&etot);
  nntree->Branch("etot_rcm",&etotrcm);  //remove bhs center mass kinematic energy
  //angular momentum==================================//
  nntree->Branch("Lx",&lx);
  nntree->Branch("Ly",&ly);
  nntree->Branch("Lz",&lz);
  nntree->Branch("Lr",&lr);
  nntree->Branch("Lalpha",&la);
  nntree->Branch("Ldelta",&ld);
  //Black hole inherit================================//
  nntree->Branch("bh_a",&abh);
  nntree->Branch("lbh12",lbh12,"lbh12[3]/D");
  
  //header tree=======================================//
  TTree *htree=(TTree*)(fn->Get("HTree"));
  Int_t nd1;
  htree->SetBranchAddress("time_cur",&t_cur);
  htree->SetBranchAddress("N",&nd1);

  //BHpar tree========================================//
  TTree *bhpar=(TTree*)(fb->Get("BHpars"));
  Double_t tbh;
  bhpar->SetBranchAddress("t",&tbh);
  bhpar->SetBranchAddress("a",&abh);
  
  string treetmp;
  Int_t counts=0;
  ifstream tlst(timeindex.c_str());
  if (!tlst.is_open())
    cout<<"No file match timeindex "<<timeindex<<endl;
  else
    while (!tlst.eof())
    {
      //treename==========================================//
      string treename="";
      tlst>>treename;
      if (treename==treetmp)
      {
        cout<<"treename dup! "<<treename<<"-"<<treetmp<<endl;
        continue;
      }
      if (treename=="")
        continue;
      treename ="P"+treename;
      treetmp=treename;
      cout<<"now "<<treename<<endl;

      //tree->treename====================================//
      TTree *ntree=(TTree*)(fn->Get(treename.c_str()));
      ntree->SetBranchAddress("index",&index);
      ntree->SetBranchAddress("mass",&mass);
      ntree->SetBranchAddress("x",&x);
      ntree->SetBranchAddress("y",&y);
      ntree->SetBranchAddress("z",&z);
      ntree->SetBranchAddress("r",&r);
      ntree->SetBranchAddress("vx",&vx);
      ntree->SetBranchAddress("vy",&vy);
      ntree->SetBranchAddress("vz",&vz);
      ntree->SetBranchAddress("v",&v);
      ntree->SetBranchAddress("pot",&pot);
      ntree->SetBranchAddress("ax",&ax);
      ntree->SetBranchAddress("ay",&ay);
      ntree->SetBranchAddress("az",&az);
    
      //save bh data temp=================================//
      htree->GetEntry(counts);
      bhpar->GetEntry(counts*bhsplit);
      Int_t tnow=counts*bhsplit;
      counts++;
      Int_t tcount=0;
      while (t_cur!=tbh)
      {
        cout<<"Err: black hole time and star time unmatch! t_bh: "<<tbh<<"; t_star:"<<t_cur<<". Check index"<<endl;
        if (t_cur>tbh)
        {
          tnow++;
          bhpar->GetEntry(tnow);
        }
        else if (t_cur<tbh)
        {
          tnow--;
          bhpar->GetEntry(tnow);
        }
        tcount++;
        if (tcount>5000)
        {
          cout<<"No match!"<<"tbh:"<<tbh<<";tstar:"<<t_cur<<endl;
          return 0;
        }
      }
      ntree->GetEntry(nd1-2);
      bh1m=mass;
      bh1x=x;
      bh1y=y;
      bh1z=z;
      bh1vx=vx;
      bh1vy=vy;
      bh1vz=vz;
      ntree->GetEntry(nd1-1);
      bh2m=mass;
      bh2x=x;
      bh2y=y;
      bh2z=z;
      bh2vx=vx;
      bh2vy=vy;
      bh2vz=vz;
    
      bhx=(bh1m*bh1x+bh2m*bh2x)/(bh1m+bh2m);
      bhy=(bh1m*bh1y+bh2m*bh2y)/(bh1m+bh2m);
      bhz=(bh1m*bh1z+bh2m*bh2z)/(bh1m+bh2m);
      bhvx=(bh1m*bh1vx+bh2m*bh2vx)/(bh1m+bh2m);
      bhvy=(bh1m*bh1vy+bh2m*bh2vy)/(bh1m+bh2m);
      bhvz=(bh1m*bh1vz+bh2m*bh2vz)/(bh1m+bh2m);
      lbh12[0]=bh2x-bh1x;
      lbh12[1]=bh2y-bh1y;
      lbh12[2]=bh2z-bh1z;
      bha2=pow((bh1x-bh2x),2)+pow((bh1y-bh2y),2)+pow((bh1z-bh2z),2);
      bha=sqrt(bha2);
      bhv2=bhvx*bhvx+bhvy*bhvy+bhvz*bhvz;

      //save to newtree===================================//
      ifstream orgdata(starindex.c_str());
      if (!orgdata.is_open())
      {
        cout<<"No log file"<<endl;
        return 0;
      }
      else
      {
        for (int j=1;j<=2;j++)
        {
          ntree->GetEntry(nd1-j);
          // calculated bh coordinates data===================//
          xb=x-bhx;
          yb=y-bhy;
          zb=z-bhz;
          rb=sqrt(xb*xb+yb*yb+zb*zb);
          vbx=vx-bhvx;
          vby=vy-bhvy;
          vbz=vz-bhvz;
          vb=sqrt(vbx*vbx+vby*vby+vbz*vbz);
          // calculated field potential and total energy======//
          asx=ax+(bh1m*(x-bh1x)+bh2m*(x-bh2x))/bha2*bha;
          asy=ay+(bh1m*(y-bh1y)+bh2m*(y-bh2y))/bha2*bha;
          asz=az+(bh1m*(z-bh1z)+bh2m*(z-bh2z))/bha2*bha;
          if (j==1)
            pots=pot+bh1m/bha;
          else
            pots=pot+bh2m/bha;
          etot=(pot+0.5*v*v)*mass;
          etotrcm=etot-0.5*bhv2*(bh1m+bh2m);
          //angular momentum==================================//
          lxt=(-vby*zb+vbz*yb);
          lyt=(-vbz*xb+vbx*zb);
          lzt=(-vbx*yb+vby*xb);
          lrt=sqrt(lxt*lxt+lyt*lyt+lzt*lzt);
          lxyt=sqrt(lxt*lxt+lyt*lyt);
          lx=mass*lxt;
          ly=mass*lyt;
          lz=mass*lzt;
          lr=mass*lrt;
          if (lxyt==0)
            la=0;
          else if (lyt>0)
            la=acos(lxt/lxyt);
          else
            la=2*3.1415926-acos(lxt/lxyt);
          ld=acos(lzt/lrt);

          nntree->Fill();
        }
        while (!orgdata.eof())
        {
          Int_t sindex;
          Int_t tmpindex=sindex;
          orgdata>>sindex;
          if (tmpindex==sindex)
            continue;
          ntree->GetEntry(sindex);
          if (index!=sindex)
          {
            cout<<"tree "<<treename<<" index .NE. checked log index"<<endl;
            Int_t numv=ntree->GetEntries();
            int j=0;
            bool finded=0;
            while (!finded&&j<numv)
            {
              ntree->GetEntry(j);
              j++;
              if (index==sindex)
                finded=1;
            }
          }
          if (index!=sindex)
          {
            cout<<"Error: check fail: index: "<<index<<","<<sindex<<endl;
            break;
          }
          xb=x-bhx;
          yb=y-bhy;
          zb=z-bhz;
          rb=sqrt(xb*xb+yb*yb+zb*zb);
          vbx=vx-bhvx;
          vby=vy-bhvy;
          vbz=vz-bhvz;
          vb=sqrt(vbx*vbx+vby*vby+vbz*vbz);
        
          dbh21=pow((x-bh1x),2)+pow((y-bh1y),2)+pow((z-bh1z),2);
          dbh22=pow((x-bh2x),2)+pow((y-bh2y),2)+pow((z-bh2z),2);
          dbh1=sqrt(dbh21);
          dbh2=sqrt(dbh22);
          asx=ax+bh1m*(x-bh1x)/dbh21*dbh1+bh2m*(x-bh2x)/dbh22*dbh2;
          asy=ay+bh1m*(y-bh1y)/dbh21*dbh1+bh2m*(y-bh2y)/dbh22*dbh2;
          asz=az+bh1m*(z-bh1z)/dbh21*dbh1+bh2m*(z-bh2z)/dbh22*dbh2;
          pots=pot+bh1m/dbh1+bh2m/dbh2;
          etot=(pot+0.5*v*v)*mass;
          etotrcm=etot-0.5*bhv2*(bh1m+bh2m);

          //angular momentum==================================//
          lxt=(-vby*zb+vbz*yb);
          lyt=(-vbz*xb+vbx*zb);
          lzt=(-vbx*yb+vby*xb);
          lrt=sqrt(lxt*lxt+lyt*lyt+lzt*lzt);
          lxyt=sqrt(lxt*lxt+lyt*lyt);
          lx=mass*lxt;
          ly=mass*lyt;
          lz=mass*lzt;
          lr=mass*lrt;
          if (lxyt==0)
            la=0;
          else if (lyt>0)
            la=acos(lxt/lxyt);
          else
            la=2*3.1415926-acos(lxt/lxyt);
          ld=acos(lzt/lrt);

          nntree->Fill();
        }
      }
    }
  f2->cd();
  nntree->Write("",TObject::kOverwrite);
  return 0;
}
