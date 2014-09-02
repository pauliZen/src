#include <iostream>
#include <iomanip>
#include <map>
#include <utility>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include "TSystem.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TH1.h"
#include "TH1F.h"
#include "TTree.h"
#include "TROOT.h"
#include "TF1.h"
#include "TRandom.h"
#include "TSpectrum.h"
#include "TVirtualFitter.h"
#include "TFile.h"
#include "TLine.h"
#include "TChain.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TLinearMinimizer.h"

using namespace std;

Int_t npeaks = 30;
Double_t fpeaks(Double_t *x, Double_t *par) {
  Double_t result = par[0] + par[1]*x[0]+par[2]*x[0]*x[0]+par[3]*pow(x[0],3)+par[4]*pow(x[0],4)+par[5]*pow(x[0],5);
  for (Int_t p=0;p<npeaks;p++) {
    Double_t norm  = par[3*p+6];
    Double_t mean  = par[3*p+7];
    Double_t sigma = par[3*p+8];
    result += norm*TMath::Gaus(x[0],mean,sigma);
  }
  return result;
}

void requeue(Float_t *x, Int_t n)
{
  Float_t temp=0;
  for(int i=n-1;i>=1;i--)
    for(int k=0;k<i;k++)
      if(x[k]>x[k+1])
      {
        temp=x[k];
        x[k]=x[k+1];
        x[k+1]=temp;
      }
}

void peaks(TH1F *h,Double_t par[],Int_t np, string filename, string plotsdir,string fitrange,string source) {
   npeaks = TMath::Abs(np);

   TCanvas *c1 = new TCanvas("c1","c1",10,10,1000,900);
 
   c1->Divide(1,2);
   c1->cd(1);
   c1->cd(1)->SetLogy();
   h->GetXaxis()->SetTitle("Ecore [keV]");
   h->GetYaxis()->SetTitle("Entries");
   h->SetTitle((source+" total events with peaks").c_str());
   h->Draw();
   TH1F *h2 = (TH1F*)h->Clone("h2");
   h2->SetTitle(("Fit "+source+" total events with peaks").c_str());
   
   
   //Use TSpectrum to find the peak candidates
   TSpectrum *s = new TSpectrum(npeaks);
   Int_t nfound = s->Search(h,2,"",0.001);
   printf("Found %d candidate peaks to fit\n",nfound);

   //Estimate background using TSpectrum::Background
   TH1 *hb = s->Background(h,20,"same");
   if (hb) c1->Update();
   if (np <0) return;

   //estimate linear background using a fitting method
   c1->cd(2);
   c1->cd(2)->SetLogy();
   TF1 *fback = new TF1("fback","pol5",0,1000);
   h->Fit("fback","qn");
   //Loop on all found peaks. Eliminate peaks at the background level
   par[0] = fback->GetParameter(0);
   par[1] = fback->GetParameter(1);
   par[2] = fback->GetParameter(2);
   par[3] = fback->GetParameter(3);
   par[4] = fback->GetParameter(4);
   par[5] = fback->GetParameter(5);
   
   npeaks = 0;
   Float_t *xpeaks = s->GetPositionX();
   requeue(xpeaks,nfound);
   for (int p=0;p<nfound;p++) {
      Float_t xp = xpeaks[p];
      Int_t bin = h->GetXaxis()->FindBin(xp);
      Float_t yp = h->GetBinContent(bin);
      if (yp-TMath::Sqrt(yp) < fback->Eval(xp)) continue;
      par[3*npeaks+6] = yp;
      par[3*npeaks+7] = xp;
      par[3*npeaks+8] = 3;
      npeaks++;
   }
   printf("Found %d useful peaks to fit\n",npeaks);
   printf("Now fitting: Be patient\n");
   TF1 *fit = new TF1("fit",fpeaks,0,1000,6+3*npeaks);
   //we may have more than the default 25 parameters
   TVirtualFitter::Fitter(h2,14+3*npeaks);
   fit->SetParameters(par);
   fit->SetNpx(1000);

   TFitResultPtr r=h2->Fit("fit","S");
   c1->Print(plotsdir.c_str());
   r->Print("V");
   TFile* output=new TFile(filename.c_str(),"update");
   output->cd();
   r->Write(("Ecore_resolution_fit_"+fitrange).c_str(),6);
   output->Close();
   cout<<"output completed"<<endl;
   
   delete fback;
   delete hb;
   delete h2;
   delete s;
   delete xpeaks;
   delete fit;
   delete c1;
   delete output;
}

int main(int argc,char* argv[])// (peaks num,source data, range min,range max) 
{
  //-------------------------------------------------//
  //choose ------------------------------------------//

  int np=15;
  int sel=0;
  int range[2]={300,3000};
  bool flag=1;
  stringstream sstr;
  sstr.str("");
  sstr.clear();
  
  if(argc!=1)
  {
    sstr<<argv[1];
    sstr>>np;
    sstr.str("");
    sstr.clear();
    
    sstr<<argv[2];
    sstr>>sel;
    sel--;
    sstr.str("");
    sstr.clear();
    
    sstr<<argv[3];
    sstr>>range[0];
    sstr.str("");
    sstr.clear();
    
    sstr<<argv[4];
    sstr>>range[1];
    sstr.str("");
    sstr.clear();
  }
  else
  {
    while(flag)
    {
      cout<<"data source(1.sii;2.siii):";
      cin>>sel;
      if(sel<1||sel>2)
        cout<<"Error\n";
      else
      {
        flag=0;
        sel--;
      }
    }
    flag=1;
    while(flag)
    {
      cout<<"The peaks number:";
      cin>>np;
      if(np<0)
      {
        cout<<"Error"<<endl;
      }
      else
        flag=0;
    }
    flag=1;
    while(flag)
    {
      cout<<"Set Fit Range:"<<"Xmin:";
      cin>>range[0];
      cout<<"Xmax:";
      cin>>range[1];
      if(range[0]<0||range[0]>range[1]||range[1]>10000)
        cout<<"Error\n";
      else
        flag=0;
    }
    
  }
  
  //-------------------------------//
  //parameters---------------------//

  string directory="$gerda/data/";
  string datan[2]={"sii","siii"};
  string source[2]={"S-II","S-III"};
  string outputfilename[2];
  string filename[2];
  string plotsdir[2];
  sstr<<range[0];
  sstr<<"_";
  sstr<<range[1];
  string fitrange=sstr.str();

  for (int i=0;i<2;i++)
  {
    outputfilename[i]=directory+"histograms/"+datan[i]+".energy.resolution.root";
    filename[i]=directory+"histograms/h."+datan[i]+".ecoto.root";
    plotsdir[i]=directory+"plots/ed"+datan[i]+"/energy_resolution_"+sstr.str()+".eps";
  }
  
  sstr.str("");
  sstr.clear();
  
  Double_t *par = new Double_t[np*3+6]();

  //-------------------------------------------------//
  //Reset ROOT and connect tree file-----------------//
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  //================================================================//
  cout<<"Part "<<datan[sel]<<endl;
  
  //input data================================//
  cout<<"Input histograms\n";
  
  TFile* finput=new TFile(filename[sel].c_str());
  cout<<"Switch to this file:"<<filename[sel]<<"\n";

  if(finput->IsOpen())
    cout<<"Input success\n";
  finput->cd();

  //build histograms point================================//
  cout<<"Point to the histogrmas\n";
  
  TH1F *htot=(TH1F*) gDirectory->Get("h18_0")->Clone();

  cout<<"SetRange: "<<range[0]<<" to "<<range[1]<<endl;
  htot->GetXaxis()->SetRange(range[0],range[1]);

  //call fit function================================//
  cout<<"Call fit function\n";
    
  peaks(htot,par,np,outputfilename[sel],plotsdir[sel],fitrange,source[sel]);
  cout<<"Fit completed"<<endl;
  
  // delete htot;
  // delete finput;

  cout<<"Part completed"<<endl;
  return 0;
  
}
