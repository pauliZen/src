//Calculate chi square of c1 and c2 pars============//
//       Store results in Ttree chi2================//

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TEntryList.h"

using namespace std;

Int_t chi2c(Int_t r,Double_t c1min,Double_t c1max, Double_t c2min,Double_t c2max,bool save=0, Int_t c1bins=1,Int_t c2bins=1,bool update=1,string treename="data",Double_t sigmav=0.2)
{
  TTree *t=(TTree*)gDirectory->Get(treename.c_str());
  t->Draw(">>slist","P>0","entrylist");
  TEntryList *tlst=(TEntryList*)gDirectory->Get("slist");
  Double_t v,p,c1,c2;
  Int_t run=r;
  Double_t chisum=0;
  Double_t c1step=(c1max-c1min)/c1bins;
  Double_t c2step=(c2max-c2min)/c2bins;
  t->SetBranchAddress("V",&v);
  t->SetBranchAddress("P",&p);
  if (!update)
  {
    TTree chi2("chi2","Chi square data of c1 and c2");
    chi2.Branch("r",&run);
    chi2.Branch("c1",&c1);
    chi2.Branch("c2",&c2);
    chi2.Branch("chi",&chisum);
    chi2.Write("",TObject::kOverwrite);
  }
  TTree *n=(TTree*)gDirectory->Get("chi2");
  n->SetBranchAddress("r",&run);
  n->SetBranchAddress("c1",&c1);
  n->SetBranchAddress("c2",&c2);
  n->SetBranchAddress("chi",&chisum);
  Int_t tnum=tlst->GetN();
  Int_t entryj;
  cout<<setprecision(10)<<"calculate"<<endl;
  if (c2bins==1)
  {
    c2=c2min;
    for(Double_t j=c1min; j<c1max; j +=c1step)
    {
      c1=j;
      for (Int_t i=0;i<tnum;i++)
      {
        entryj=tlst->GetEntry(i);
        t->GetEntry(entryj);
        chisum +=pow((v-c1*log10(p)-c2)/sigmav,2);
      }
      cout<<"c1:"<<c1<<";c2:"<<c2<<";chisum:"<<chisum<<endl;
      if (save) n->Fill();
      chisum=0;
    }
  }
  else if(c1bins==1)
  {
    c1=c1min;
    for(Double_t j=c2min; j<c2max;j +=c2step)
    {
      c2=j;
      for (Int_t i=0;i<tnum;i++)
      {
        entryj=tlst->GetEntry(i);
        t->GetEntry(entryj);
        chisum +=pow((v-c1*log10(p)-c2)/sigmav,2);
      }
      cout<<"c1:"<<c1<<";c2:"<<c2<<";chisum:"<<chisum<<endl;
      if (save) n->Fill();
      chisum=0;
    }
  }
  else
    cout<<"Range conflicts"<<endl;
  n->Write("",TObject::kOverwrite);
  cout<<"Finished"<<endl;
  return tnum;
}

Int_t cycchi(Int_t cyn=10)
{
  cout<<"#Initial: create root-----------------------------#"<<endl;
  chi2c(1,-3,-2,17.16,17.16,0,10,1,0);
  stringstream sstr;
  string ii;
  sstr.str("");
  sstr.clear();
  Double_t cmin[2]={-3,16};
  Double_t cmax[2]={-1,18};
  Double_t cmean[2][2]={};
  Double_t vmmin;
  Int_t bins[2]={10,1};
  ofstream datt("cycle.lst");
  datt<<setprecision(10);
  for (int i=1;i<=cyn;i++)
    for (int m=0;m<2;m++)
    {
      bool flag=1;
      Int_t cck=1;
      cout<<"#---cycle "<<i<<" c"<<m+1<<"---------------------------#"<<endl;
      cout<<"##c1:"<<cmin[0]<<" "<<cmax[0]<<" "<<"; c2:"<<cmin[1]<<" "<<cmax[1]<<" "<<"; bins:"<<bins[0]<<","<<bins[1]<<endl;
      bins[0]=bins[1]=1;
      bins[m]=10;
      cmean[1-m][0]=(cmax[1-m]+cmin[1-m])/2.0;
      cmean[1-m][1]=cmean[1-m][0];
      while (flag)
      {
        sstr.str("");
        sstr.clear();
        sstr<<2*i-1+m+2*cyn*cck;
        sstr>>ii;
        cmean[m][0]=cmin[m];
        cmean[m][1]=cmax[m];
        cout<<"###i:"<<ii<<";  c1min:"<<cmin[0]<<";  c1max:"<<cmax[0]<<";  c2min:"<<cmin[1]<<";  c2max"<<cmax[1]<<";  bins:"<<bins[0]<<","<<bins[1]<<endl;
        chi2c(2*i-1+m+2*cyn*cck,cmean[0][0],cmean[0][1],cmean[1][0],cmean[1][1],1,bins[0],bins[1]);
        TTree *ch=(TTree*)gDirectory->Get("chi2");
        Double_t tc[2],tchi;
        Int_t tr;
        ch->SetBranchAddress("c1",&tc[0]);
        ch->SetBranchAddress("c2",&tc[1]);
        ch->SetBranchAddress("chi",&tchi);
        ch->SetBranchAddress("r",&tr);
        ch->Draw(">>clist",("r=="+ii).c_str(),"entrylist");
        TEntryList *clst=(TEntryList*)gDirectory->Get("clist");
        Int_t tnum=clst->GetN();
        Double_t chk1,chk2;
        for (int j=0;j<tnum;j++)
        {
          Int_t entryj=clst->GetEntry(j);
          ch->GetEntry(entryj);
          chk2=tchi;
          if (j==0)
          {
            chk1=chk2;
            continue;
          }
          else if (chk2>chk1&&j==1)
          {
            cmin[m] -=(cmax[m]-cmin[m])/10;
            flag=1;
            cck++;
            cout<<"##--------c"<<m+1<<"min: changed to "<<cmin[m]<<endl;
            break;
          }
          else if (chk2<chk1&&j==tnum-1)
          {
            cmax[m] +=(cmax[m]-cmin[m])/10;
            flag=1;
            cck++;
            cout<<"##--------c"<<m+1<<"max: changed to "<<cmax[m]<<endl;
            break;
          }
          else if (chk2<chk1&&j<tnum-1)
          {
            chk1=chk2;
          }
          else if (chk2>=chk1&&j>1)
          {
            flag=0;
            cmax[m]=tc[m];
            //   cout<<"bug check: tc1:"<<entryj<<" "<<tc1<<" "<<tc2<<" "<<tchi<<" "<<tr<<endl;
            entryj=clst->GetEntry(j-1);
            ch->GetEntry(entryj);
            vmmin=tchi;
            entryj=clst->GetEntry(j-2);
            ch->GetEntry(entryj);
            cmin[m]=tc[m];
            datt<<2*i-1+m<<" "<<cmean[0][0]<<" "<<cmean[0][1]<<" "<<cmean[1][0]<<" "<<cmean[1][1]<<" "<<bins[0]<<" "<<bins[1]<<" "<<vmmin<<endl;
            cout<<"###Output: i:"<<2*i-1+m<<";  c1min:"<<cmean[0][0]<<";  c1max:"<<cmean[0][1]<<";  c2min:"<<cmean[1][0]<<";  c2max"<<cmean[1][1]<<";  bins:"<<bins[0]<<","<<bins[1]<<";  chi"<<vmmin<<endl;
            //   cout<<"bug check: tc1:"<<entryj<<" "<<tc1<<" "<<tc2<<" "<<tchi<<" "<<tr<<endl;
            chi2c(2*i-1+m,cmean[0][0],cmean[0][1],cmean[1][0],cmean[1][1],1,bins[0],bins[1]);
            break;
          }
        }
      }
    }
  return vmmin;;
}

int main(int argc,char* argv[])
{
  stringstream nstr;
  int cycnum=10;
  switch (argc)
  {
  case 2:
    nstr.str("");
    nstr.clear();
    nstr<<argv[1];
    nstr>>cycnum;
    nstr.str("");
    nstr.clear();
    break;
  default:
    cout<<"Input cycle number:";
    cin>>cycnum;
    break;
  }
  TFile f("data.root","update");
  f.Delete("chi2;1");
  cycchi(cycnum);
  return 0;
}
