#include "initial.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1F.h"
#include "TF1.h"
#include <string>
#include <fstream>
#include <iostream>
#include "uftools.h"

int main (int argc, char *argv[])
{
  pars_initial init(".calcms_config");
  init.add("bdata","bdata.list","data.lst");
  init.add("bins","bins to count",(int)10);
  init.add("tstep","time interval",(int)200);
  init.add("file","store file","out.lst");
  init.initial(argc,argv);

  TChain *t=new TChain("star");
  ifstream file(init.gets("bdata").c_str());
  if (!file.is_open()) { std::cerr<<"Error: File not found!\n"; return 0; }
  ofstream out(init.gets("file").c_str());
  std::string tmp;
  
  while (1)
  {
    file>>tmp;
    if (file.eof()) break;
    t->AddFile(tmp.c_str());
  }

  int bins=init.geti("bins");
  double bi=3.0/(double)bins;
  int tb=init.geti("tstep");
  TF1 *lf=new TF1("line","10^([0]*x+[1])",-5,-2);
  out<<"T <r> slope err offset err chi2"<<std::endl;
  for (int i=0;i<bins;i++)
  {
    for (int j=0;j<=1000; j+=tb)
    {
      t->Draw("log10(m)>>htemp",("r[3]>"+to<std::string>(i*bi)+"&&r[3]<"+to<std::string>((i+1)*bi)+"&&t=="+to<std::string>(j)).c_str());
      TH1F *f1=(TH1F*)gDirectory->Get("htemp")->Clone();
      f1->Fit("line","R0");
      TF1* fit1=f1->GetFunction("line");
      double p1=fit1->GetParameter(0);
      double p1e=fit1->GetParError(0);
      double p2=fit1->GetParameter(1);
      double p2e=fit1->GetParError(1);
      double chi=fit1->GetChisquare();
      out<<j<<" "<<(i+0.5)*bi<<" "<<p1<<" "<<p1e<<" "<<p2<<" "<<p2e<<" "<<chi<<std::endl;
      std::cout<<"List i j "<<i<<" "<<j<<std::endl;
    }
  }
  
  return 0;
}
