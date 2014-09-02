#include <iostream>
#include <iomanip>
#include <map>
#include <utility>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include "TObject.h"
#include "TGraph.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TGraphErrors.h"
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

double fwhmfun(double *x,double *par)
{
  return par[0]+par[1]*pow(x[0],0.5)+par[2]*x[0];
}

using namespace std;

int main(int argc,char* argv[]) //(fractions,{peaks,xmin,xmax},datasource)
{
  //-------------------------------------------------//
  //choose ------------------------------------------//

  int fracts=2;
  int sel=1;
  bool flag=1;
  stringstream sstr;
  sstr.str("");
  sstr.clear();
  
  if(argc!=1)
  {
    sstr<<argv[1];
    sstr>>fracts;
    sstr.str("");
    sstr.clear();
  }
  else
    while(flag)
    {
      cout<<"Fractions of findpeaks:";
      cin>>fracts;
      if(fracts<0)
        cout<<"Error\n";
      else
        flag=0;
    }
  
  int *peaks=new int[fracts];
  string *xmin=new string[fracts];
  string *xmax=new string[fracts];
  
  if(argc!=1)
  {
    for(int i=0;i<fracts;i++)
    {
      sstr<<argv[2+3*i];
      sstr>>peaks[i];
      sstr.str("");
      sstr.clear();
      sstr<<argv[3+3*i];
      sstr>>xmin[i];
      sstr.str("");
      sstr.clear();
      sstr<<argv[4+3*i];
      sstr>>xmax[i];
      sstr.str("");
      sstr.clear();
    }
    sstr<<argv[fracts*3+2];
    sstr>>sel;
    sel--;
    sstr.str("");
    sstr.clear();
  }

  else
  {
    flag=1;
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
    for(int i=0;i<fracts;i++)
    {
      flag=1;
      while(flag)
      {
        cout<<"Fraction "<<i+1<<": The peaks number:";
        cin>>peaks[i];
        if(peaks[i]<0)
        {
          cout<<"Error"<<endl;
        }
        else
          flag=0;
      }
      
      cout<<"Fraction"<<i+1<<": Fit Range:"<<"Xmin:";
      cin>>xmin[i];
      cout<<"Xmax:";
      cin>>xmax[i];

    }
  }

  //parameters================================================================//
  string directory="$gerda/data/";
  string datan[2]={"sii","siii"};
  string source[2]={"S-II","S-III"};
  string filename[2];
  string plotsdir[2];
  string fitdata[2];
  string *fitrange=new string[fracts];

  for(int i=0;i<fracts;i++)
  {
    sstr<<xmin[i];
    sstr<<"_";
    sstr<<xmax[i];
    fitrange[i]=sstr.str();
    sstr.str("");
    sstr.clear();
  }

  for (int i=0;i<2;i++)
  {
    filename[i]=directory+"histograms/"+datan[i]+".energy.resolution.root";
    plotsdir[i]=directory+"plots/ed"+datan[i]+"/energy_resolution.eps";
    fitdata[i]="/home/lswl/Documents/works/Gerda/data/table/ed"+datan[i]+"/"+datan[i]+"_fitdata.txt";
    
  }

  int tpeaks=0;
  for(int i=0;i<fracts;i++)
    tpeaks +=peaks[i];
  double *x=new double[tpeaks]();
  double *y=new double[tpeaks]();
  double *ex=new double[tpeaks]();
  double *ey=new double[tpeaks]();

  //fit function======================================//
  TF1 *fitfun=new TF1("fitfun",fwhmfun,0,10000,3);
  fitfun->SetParameters(10,0.0405,0.00007726);
  fitfun->SetParLimits(1,0.0405,0.1);
  fitfun->SetParLimits(2,0.00007726,1);
  

  //data analysis================================================//
  
  //Reset ROOT and connect tree file-----------------//
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  //input data================================//
  cout<<"Input peaks fit data: "<<filename[sel]<<"\n";

  TFile* finput=new TFile(filename[sel].c_str());
  if(finput->IsOpen())
    cout<<"Input success\n";
  finput->cd();

  //read data================================//
  cout<<"Read peaks data\n";
  int count=0;
  int peaknum=0;
  
  ofstream dout(fitdata[sel].c_str());
  cout<<"Outfitdata "<<fitdata[sel]<<endl;
  
  dout<<"\\hline\n";
  dout<<"Peaks Num.& mean [keV]& $mean_{err.}$ & FWHM [keV] & $FWHM_{err.}$ \\\\\\hline\n";
  dout<<setprecision(4);

  for(int i=0;i<fracts;i++)
  {
    TFitResultPtr tn = (TFitResult*) gDirectory->Get(("Ecore_resolution_fit_"+fitrange[i]).c_str())->Clone();
    
    
    for(int k=0;k<peaks[i];k++)
    {
      double xt=tn->Value(3*k+6+1);
      double yt=abs(6*pow(2*log(2),0.5)*tn->Value(3*k+6+2));
      double ext=tn->Errors()[3*k+6+1];
      double eyt=6*pow(2*log(2),0.5)*tn->Errors()[3*k+6+2];
      peaknum++;
      
      dout<<peaknum<<"& "<<xt<<"& "<<abs(ext)<<"& "<<yt/3<<"& "<<abs(eyt/3)<<"\\\\\\hline\n";

      double ytn=yt;
      double eytn=eyt;
      double ytnn=yt;
      double eytnn=eyt;
      if(k<peaks[i]-1)
      {
        ytn=abs(6*pow(2*log(2),0.5)*tn->Value(3*(k+1)+6+2));
        eytn=6*pow(2*log(2),0.5)*tn->Errors()[3*(k+1)+6+2];
        ytnn=ytn;
        eytn=eytnn;
      }
      if(k<peaks[i]-2)
      {
        ytnn=abs(6*pow(2*log(2),0.5)*tn->Value(3*(k+2)+6+2));
        eytnn=6*pow(2*log(2),0.5)*tn->Errors()[3*(k+2)+6+2];
      }

      if((yt<18&&yt>11&&sel==1)||(yt<20&&(yt-eyt)<=(ytn+eytnn)&&(yt-eyt)<=(ytnn+eytnn)&&xt>500&&sel==0))
      {
        x[count]=xt;
        y[count]=yt;
        ex[count]=ext;
        ey[count]=eyt;
        count++;
      }
    }
 
  }

 
  
  //build graph================================//
  cout<<"build data graph\n";

  TGraphErrors *resf=new TGraphErrors(count,x,y,ex,ey);
  //TGraph *resf=new TGraph(count,x,y);

  //build Canvas
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1000,900);
  c1->cd();
  resf->SetTitle((source[sel]+" energy resolution").c_str());
  resf->GetXaxis()->SetTitle("Ecore [keV]");
  resf->GetYaxis()->SetTitle("3*FWHM [keV]");
  
  resf->SetMarkerColor(4);
  resf->SetMarkerStyle(21);
  resf->Draw("AP*");
  TFitResultPtr r=resf->Fit("fitfun","si");
  c1->Update();
  c1->Print(plotsdir[sel].c_str());
  r->Print("v");
  TFile *output =new TFile(filename[sel].c_str(),"update");
  dout<<"\n\\hline\n";
  dout<<"Par& value& error\\\\\\hline\n";
  for(int i=0;i<3;i +=2)
    dout<<i<<"& "<<r->Value(i)<<"& "<<abs(r->Errors()[i])<<"\\\\\\hline\n";

  dout.close();
  
  output->cd();
  r->Write("Resolution",6);
  output->Close();
  cout<<"\noutput data success\n";
  
  return 0;
}
