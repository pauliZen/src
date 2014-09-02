//Transform dat file to root.file===================//
//data structure: Catalog,No,Rah(h),RAM(m),RAs(s),  //
//                DEd(deg),DEm(arcmin),             //
//                DEs(arcsec),DelV(mag),P(d),B(mag),//
//                V(mag),R(mag),I(mag)              //
//Use: [prog.] =====================================//

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

int main(int argc, char* argv[])
{
  stringstream sstr;
  string filename;
  string rootname;
  string treename;
  switch (argc)
  {
  case 2:
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>filename;
    sstr.str("");
    sstr.clear();
    break;
  default:
    cout<<"Input filename:(no '.lisr')";
    cin>>filename;
    break;
  }
  rootname="data.root";
  treename="data";

  cout<<filename<<" to "<<rootname<<"("<<treename<<")"<<endl;

  ifstream orgdata(filename.c_str());
  if (!orgdata.is_open())
  {
    cout<<"No such file"<<endl;
    return 0;
  }
  else
  {
    gROOT->Reset();
    gROOT->SetStyle("Plain");
    TFile f(rootname.c_str(),"create");

    TTree *data=new TTree(treename.c_str(),"distances data");
    string n1,n2;
    Int_t rah,ram,ded,dem;
    Int_t count=0;
    Double_t ras,des,delv,p,b,v,r,i;
    data->Branch("Name",&n1);
    data->Branch("No",&n2);
    data->Branch("Rah",&rah);
    data->Branch("Ram",&ram);
    data->Branch("Ras",&ras);
    data->Branch("Ded",&ded);
    data->Branch("Dem",&dem);
    data->Branch("Des",&des);
    data->Branch("DelV",&delv);
    data->Branch("P",&p);
    data->Branch("B",&b);
    data->Branch("V",&v);
    data->Branch("R",&r);
    data->Branch("I",&i);
                 
    while (!orgdata.eof())
    {
      orgdata>>n1;
      orgdata>>n2;
      orgdata>>rah;
      orgdata>>ram;
      orgdata>>ras;
      orgdata>>ded;
      orgdata>>dem;
      orgdata>>des;
      orgdata>>delv;
      orgdata>>p;
      orgdata>>b;
      orgdata>>v;
      orgdata>>r;
      orgdata>>i;
      data->Fill();
      cout<<n1<<n2<<endl;
      if(count++>620)
        break;
    }
    data->Write("",TObject::kOverwrite);
  }
  return 0;
}

    
