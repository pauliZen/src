//Transform dat file to root.file===================//
//data structure: MM YYYY (m_M)_0 +-================//
//Use: [prog.] [filename(no .list)]=================//

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

  rootname=filename+".root";
  treename=filename;
  filename+=".list";

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
    Double_t mm,yyyy,Dm,Dm_err,date;
    Int_t style;
    data->Branch("mm",&mm);
    data->Branch("yyyy",&yyyy);
    data->Branch("Dm",&Dm);
    data->Branch("Dm_err",&Dm_err);
    data->Branch("date",&date);
    data->Branch("style",&style);

    while (!orgdata.eof())
    {
      orgdata>>mm;
      orgdata>>yyyy;
      orgdata>>Dm;
      orgdata>>Dm_err;
      orgdata>>style;
      date=yyyy+mm/12.0;
      data->Fill();
    }
    data->Write("",TObject::kOverwrite);
  }
  return 0;
}
