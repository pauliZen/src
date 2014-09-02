#include <iomanip>
#include <map>
#include <utility>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TLine.h"
#include "TChain.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TLegend.h"
#include "TAxis.h"

using namespace std;

void errorc(double x, double y,double *f)
{
  f[0]=x/y;
  double dx=pow(x,0.5);
  double dy=pow(x,0.5);
  f[1]=1/y*pow(pow(dx,2)+pow(f[0]*dy,2),0.5);
}

int main(int argc, char* argv[]) //(sources, energy min, energy max)
{
  //Reset Root========================================//

  gROOT->Reset();
  gROOT->SetStyle("Plain");

  //Parameters========================================//

  const int segnum=18;

  int datasr=1;
  int emin=150;
  int emax=3000;
  
  stringstream sstr;

  string directory="$gerda/data/";
  string datan="sii";
  string dir_his=directory+"histograms/";
  string dir_plot=directory+"plots/";
  string filename=dir_his+"h.";

  //selections========================================//
  
  bool flagf=1;
  if (argc!=1)
  {
    sstr.str("");
    sstr.clear();
    
    sstr<<argv[1];
    sstr>>datasr;
    sstr.str("");
    sstr.clear();

    sstr<<argv[2];
    sstr>>emin;
    sstr.str("");
    sstr.clear();

    sstr<<argv[3];
    sstr>>emax;
    sstr.str("");
    sstr.clear();
  }
  else
  {
    while(flagf)
    {
      cout<<"Source:(1.SII;2.SIII)";
      cin>>datasr;
      if (datasr==1||datasr==2)
        flagf=0;
      else
      {
        flagf=1;
        cout<<"Error"<<endl;
      }
    }
    flagf=1;
    while(flagf)
    {
      cout<<"Energy minimum:";
      cin>>emin;
      cout<<"Energy maximum:";
      cin>>emax;
      if (emin<0||emin>emax||emax>10000)
        cout<<"Error\n";
      else
        flagf=0;
    }
  }
  

  if (datasr==1)
    datan="sii";
  else if (datasr==2)
    datan="siii";

  filename +=datan+".ecoto.root";
  dir_plot +="ed"+datan+"/";

  //Input histograms==================================//
  
  TFile *finput =new TFile(filename.c_str());
  finput->cd();
  if(finput->IsOpen())
  {
    cout<<"Input root data successful\n";

    //Read histograms===================================//
    
    TH1F** segab= new TH1F*[segnum]();
    TH1F** segt= new TH1F*[segnum]();
    TH1F** seger= new TH1F*[segnum]();
    int *count=new int();

    for(int i=0;i<segnum;i++)
    {
      sstr<<"h";
      sstr<<i;
      sstr<<"_";
      cout<<"Get "+sstr.str()<<"1"<<endl;
      gDirectory->GetObject((sstr.str()+"1").c_str(),segt[i]);
      cout<<"Get "+sstr.str()<<"3"<<endl;
      gDirectory->GetObject((sstr.str()+"3").c_str(),segab[i]);
      cout<<"Get "+sstr.str()<<"5"<<endl;
      gDirectory->GetObject((sstr.str()+"5").c_str(),seger[i]);
      if(segt[i]&&segab[i]&&seger[i])
        (*count)++;
      sstr.str("");
      sstr.clear();
    }
    
    //build seg ab/tot histograms=======================//

    double **rate=new double*[segnum];
    double **erate=new double*[segnum];
    
    for(int i=0;i<segnum;i++)
    {
      rate[i]=new double[2]();
      erate[i]=new double[2]();
    }

    if(*count==18)
    {
      *count=0;
      cout<<"Read histograms successful\n";
      for(int i=0;i<segnum;i++)
      {
        double abt=0;
        double tot=0;
        double err=0;
        for(int n=(emin);n<=(emax);n++)
        {
          abt +=segab[i]->GetBinContent(n);
          tot +=segt[i]->GetBinContent(n);
          err +=seger[i]->GetBinContent(n);
        }
        cout<<"Segment "<<i+1<<" : abnormal single-segment events:"<<abt<<endl;
        cout<<"Segment "<<i+1<<" : total single-segment events:"<<tot<<endl;
        cout<<"Segment "<<i+1<<" : error single-segment events:"<<err<<endl;
          
        if (tot==0)
        {
          tot=1;
          cout<<"Warning:Seg total events between "<<emin<<" to "<<emax<<" is zero\n";
        }
        if (abt/tot>1)
        {
          cout<<"Data Error: abnormal/total is larger than 1\n";
        }
        if (err/abt>1)
        {
          cout<<"Data Error: error/abnormal is larger than 1\n";
        }
        
        if(err<=abt&&abt<=tot)
        {
          errorc(abt,tot,rate[i]);
          errorc(err,tot,erate[i]);
          cout<<"Calculation seg "<<i+1<<" successful"<<endl;
          (*count)++;
        }
      }
    }
    else
    {
      cout<<"Get 2*"<<*count<<" histograms, lack "<<(18-*count)*2<<" histograms\n";
      cout<<"Histograms may contain error or don't exist\n";
    }
    
    //Plots results=====================================//
    if(*count==18)
    {
      cout<<"Data calculation successful, plot result now\n";
      TH1F *rateseg=new TH1F("rateseg","rateseg",18,0,18);
      TH1F *erateseg=new TH1F("erateseg","erateseg",18,0,18);
      
      for(int i=1;i<19;i++)
      {
        sstr<<i;
        rateseg->SetBinContent(i,(float)rate[i-1][0]);
        erateseg->SetBinContent(i,(float)erate[i-1][0]);
        rateseg->SetBinError(i,(float)rate[i-1][1]);
        erateseg->SetBinError(i,(float)erate[i-1][1]);
        rateseg->GetXaxis()->SetBinLabel(i,sstr.str().c_str());
        erateseg->GetXaxis()->SetBinLabel(i,sstr.str().c_str());
        sstr.str("");
        sstr.clear();
      }

      TCanvas* c1=new TCanvas("c1","c1",10,10,900,600);
      c1->cd();
      rateseg->GetXaxis()->SetTitle("Segment");
      rateseg->GetYaxis()->SetTitle("Events rate");
      rateseg->SetTitle("Abnormal/total single-segment events rate");
      float *rmax=new float;
      *rmax=rateseg->GetMaximum()*1.2;
      rateseg->SetAxisRange(0,*rmax,"Y");
      delete rmax;
      rateseg->GetXaxis()->SetNdivisions(18,1);

      TLegend* l=new TLegend(0.2,0.8,0.7,0.85);
      l->SetFillStyle(0);
      sstr<<emin;
      sstr<<" to ";
      sstr<<emax;
      l->AddEntry(rateseg,("abnormal/total events rate(single segment) from "+sstr.str()+" keV").c_str());
      l->AddEntry(erateseg,("error/total events rate(single segment) from "+sstr.str()+" keV").c_str());
      sstr.str("");
      sstr.clear();
      rateseg->SetFillColor(3);
      erateseg->SetFillColor(2);
      
      rateseg->Draw("bar3");
      erateseg->Draw("bar3same");
      l->Draw();
      c1->Update();
      c1->Print((dir_plot+datan+".ab.tot.rate.eps").c_str());
      cout<<"Plot successful\n";
      
      TFile *output=new TFile(filename.c_str(),"Update");
      rateseg->Write("rateseg",6);
      erateseg->Write("erateseg",6);
      output->Close();
      cout<<"Output histogram successful\n";
    }

    delete count;
    delete [] rate;

  }
  else
    cout<<"Input root data error,please check whether the file exists\n";

  return 0;
}

        
          
              
