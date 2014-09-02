#include "initial.h"
#include "uftools.h"
#include <iostream>
#include <cmath>
#include "TFile.h"
#include "TTree.h"

int main(int argc, char *argv[])
{
  pars_initial init(".getinfradius_config");
  init.add("rootfiledir","star root file name","run-020-020-1mil");
  init.add("Pmax","Time step maximum",(int)150);
  init.add("bhindex1","black hole index 1",(int)999998);
  init.add("bhindex2","black hole index 2",(int)999999);
  init.initial(argc,argv);

  std::string dir=init.get<std::string>("rootfiledir");
  std::string filename=dir+"-star-extra.root";
  std::string resultname=dir+"-result.root";
  Int_t bin1=init.get<int>("bhindex1");
  Int_t bin2=init.get<int>("bhindex2");
  TFile f2(resultname.c_str(),"update");
  f2.cd();
  TTree *nt=new TTree("infradi","influence radius");
  Double_t t,rinf;
  nt->Branch("t",&t);
  nt->Branch("rinf",&rinf);
  TFile f1(filename.c_str(),"update");
  f1.cd();
  TTree *ht=(TTree*)gDirectory->Get("HTree");
  ht->SetBranchAddress("time_cur",&t);
  std::string nowtree="";
  int hcount=0;
  for (int i=0;i<init.get<int>("Pmax");i++)
  {
    ht->GetEntry(hcount);
    if (i<10) nowtree="P000"+to<std::string>(i);
    else if (i<100) nowtree="P00"+to<std::string>(i);
    else if (i<1000) nowtree="P0"+to<std::string>(i);
    else nowtree="P"+to<std::string>(i);
    std::cout<<"Now "<<nowtree<<std::endl;
    TTree *tr=(TTree*)gDirectory->Get(nowtree.c_str());
    if (!tr)
    {
      std::cout<<"Pass "<<nowtree<<"\n";
      continue;
    }
    hcount++;
    Double_t x,y,z,m;
    Int_t index;
    tr->SetBranchAddress("index",&index);
    tr->SetBranchAddress("x",&x);
    tr->SetBranchAddress("y",&y);
    tr->SetBranchAddress("z",&z);
    tr->SetBranchAddress("mass",&m);
    tr->GetEntry(bin1);
    Double_t *rlist=new Double_t[bin1];
    if (index!=bin1)
    {
      std::cerr<<"Error: BH index not match: "<<index<<"\t"<<bin1<<std::endl;
      return 0;
    }
    Double_t b1x=x, b1y=y, b1z=z,b1m=m;
    tr->GetEntry(bin2);
    if (index!=bin2)
    {
      std::cerr<<"Error: BH index not match: "<<index<<"\t"<<bin2<<std::endl;
      return 0;
    }
    Double_t b2x=x, b2y=y, b2z=z,b2m=m;
    Double_t bx=(b1x*b1m+b2x*b2m)/(b1m+b2m);
    Double_t by=(b1y*b1m+b2y*b2m)/(b1m+b2m);
    Double_t bz=(b1z*b1m+b2z*b2m)/(b1m+b2m);
    tr->GetEntry(0);
    rlist[0]=(x-bx)*(x-bx)+(y-by)*(y-by)+(z-bz)*(z-bz);
    Double_t ms=m;
    for (int j=0;j<bin1;j++)
    {
      tr->GetEntry(j);
      rlist[j]=(x-bx)*(x-bx)+(y-by)*(y-by)+(z-bz)*(z-bz);
    }
    quicksort(rlist,bin1);
    rinf=sqrt(rlist[static_cast<int>((b1m+b2m)/ms)]);
    nt->Fill();
    delete tr;
    delete rlist;
  }
  f2.cd();
  nt->Write("",TObject::kOverwrite);
  return 0;
}
