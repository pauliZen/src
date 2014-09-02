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

    TTree *data=new TTree(treename.c_str(),"data");
    Double_t x,y,t;
    data->Branch("x",&x);
    data->Branch("y",&y);
    data->Branch("t",&t);

    while (!orgdata.eof())
    {
      orgdata>>x;
      orgdata>>y;
      orgdata>>t;
      data->Fill();
    }
    data->Write("",TObject::kOverwrite);
  }
  return 0;
}
