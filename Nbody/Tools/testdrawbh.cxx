#include <nbodystdout.h>
#include <initial.h>
#include <string>
#include <cmath>
#include <iostream>
#include "TGraph.h"
#include "TEntryList.h"
#include "TFile.h"
#include "TTree.h"

Double_t dot3(Double_t a[])
{
  return a[0]*a[0]+a[1]*a[1]+a[2]*a[2];
}

int main (int argc, char *argv[])
{
  pars_initial init(".test_draw_bh");
  init.add("rootlist","rootlist to chain","rootlist.lst");
  init.add("newrootname","new root filename to save","test.root");
  init.initial(argc,argv);

  nbodystdout *st=new nbodystdout("star");
  st->LoadList(init.get<std::string>("rootlist"));
#ifdef DEBUG
  std::cout<<"LoadFile list\n";
#endif  
  TEntryList **tl=new TEntryList*[2];
  st->Draw(">>e1list","n==1","entrylist");
  tl[0]=(TEntryList*)gDirectory->Get("e1list");
  st->Draw(">>e2list","n==2","entrylist");
  tl[1]=(TEntryList*)gDirectory->Get("e2list");

#ifdef DEBUG
  std::cout<<"N1="<<tl[0]->GetN()<<"; N2="<<tl[1]->GetN()<<"\n";
#endif  
  if (tl[0]->GetN()!=tl[1]->GetN())
  {
    std::cerr<<"Error: Black holes data not same time intervals!\n";
    return 0;
  }

  TFile *f=new TFile(init.get<std::string>("newrootname").c_str(),"update");
  TTree *tr=new TTree("bh","bh data");
  Double_t a,t,ecc,r[2][4],v[2][4],d[4],vr[4],m[2],eng;
  tr->Branch("t",&t);
  tr->Branch("a",&a);
  tr->Branch("ecc",&ecc);
  tr->Branch("r",r,"r[2][4]/D");
  tr->Branch("v",v,"v[2][4]/D");
  tr->Branch("d",d,"d[4]/D");
  tr->Branch("vr",vr,"vr[4]/D");
  tr->Branch("m",m,"m[2]/D");
  tr->Branch("eng",&eng);

  Int_t tnum=tl[0]->GetN();
  for (Int_t i=0;i<tnum;i++)
  {
    st->fchain->SetEntryList(tl[0]);
    Int_t treenum=0;
    Int_t tentry=tl[0]->GetEntryAndTree(i,treenum);
    st->GetEntry(tentry+st->fchain->GetTreeOffset()[treenum]);
    t=st->t;
#ifdef DEBUG
    std::cout<<"entry:"<<tentry+st->fchain->GetTreeOffset()[treenum]<<"\ttime:"<<t<<"\tr[0][0]:"<<st->r[0]<<std::endl;
#endif    
    for (int j=0;j<4;j++)
    {
      r[0][j]=st->r[j];
      v[0][j]=st->r[j];
      m[0]=st->m;
    }
    st->fchain->SetEntryList(tl[1]);
    tentry=tl[1]->GetEntryAndTree(i,treenum);
    st->GetEntry(tentry+st->fchain->GetTreeOffset()[treenum]);
    if (t!=st->t)
    {
      std::cerr<<"Error: bh1 time != bh2 time\n";
      return 0;
    }
    for (int j=0;j<4;j++)
    {
      r[1][j]=st->r[j];
      v[1][j]=st->r[j];
      m[1]=st->m;
    }
    for (int j=0;j<3;j++)
    {
      d[j]=r[0][j]-r[1][j];
      vr[j]=v[0][j]-v[1][j];
    }
    Double_t msys=m[0]+m[1];
    Double_t dotx=sqrt(dot3(d));
    Double_t bE=dot3(vr)/msys-2.0/dotx;
    a=-1.0/bE;
    eng=m[0]*m[1]*bE/2.0;
    Double_t p1=1-dotx/a;
    Double_t crs=d[0]*vr[0]+d[1]*vr[1]+d[2]*vr[2];
    ecc=sqrt(p1*p1+crs*crs/a/msys);
#ifdef DEBUG
    std::cout<<"Ecc:"<<ecc<<"\tp1:"<<p1<<"\tcrs:"<<crs<<"\ta:"<<a<<"\tmsys:"<<msys<<std::endl;
#endif    
    tr->Fill();
  }
  tr->Write("",TObject::kOverwrite);

  std::cout<<"Finished\n";
  return 0;
}
