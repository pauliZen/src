//Draw L for each time step, save as png=====//
//Command: [program] [filename]=====================//

#include <iostream>
#include <string>
#include <cmath>
#include "initial.h"
#include "uftools.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TEntryList.h"
#include <cstdlib>
#include "TArrow.h"

using namespace std;

void setrange(const int &index, Float_t &min, Float_t&max)
{
  if (index<4) { min=-0.2E-6; max=0.2E-6; }
  else if (index==4) { min=0; max=6.2831; }
  else if (index==5) { min=-1; max=1; }
  else
  {
    std::cerr<<"Error Index!\n";
    exit(1);
  }
}

Float_t lfill(const int &index, Double_t l[6])
{
  if (index<5) return l[index];
  else return cos(l[index]);
}

int main(int argc, char* argv[])
{
  pars_initial init(".drawlmov_config");
  init.add("rootname","data dir name","run-020-020-1mil");
  init.add("rootpath","root file path","/home/lwang/Dropbox/Datas/BHdata/figures/");
  init.add("x","x-axis",(int)0);
  init.add("y","y-axis",(int)1);
  init.add("xtitle","x-axis title","L_{x}");
  init.add("ytitle","y-axis title","L_{y}");
  init.add("figtitle","Figure title","Lxy");
  init.add("drawnormal","option to draw L",(bool)1);
  init.add("drawmean","option to draw L_mean",(bool)0);
  init.add("drawto","option to draw L before to after",(bool)0);
  init.initial(argc,argv);
  string rootname=init.get<string>("rootname");
  string figdir=init.get<string>("figtitle");
  string xt=init.get<string>("xtitle");
  string yt=init.get<string>("ytitle");
  Int_t xindex=init.get<Int_t>("x");
  Int_t yindex=init.get<Int_t>("y");
  bool dm=init.get<bool>("drawmean");
  bool dt=init.get<bool>("drawto");
  bool dn=init.get<bool>("drawnormal");
  string treename="langle";
  string filepath=init.get<string>("rootpath");

  TFile *fr=new TFile((rootname+"-result.root").c_str(),"update");
  fr->cd();
  TTree *tr=(TTree*)gDirectory->Get(treename.c_str());
  Double_t lsi[6],lso[6],lsim[3][6],lsom[3][6],lbhi[6],lbho[6];
  Float_t xmin,xmax,ymin,ymax;
  string filename;
  tr->SetBranchAddress("Lsi",lsi);
  tr->SetBranchAddress("Lso",lso);
  tr->SetBranchAddress("Lsi_mean",lsim);
  tr->SetBranchAddress("Lso_mean",lsom);
  tr->SetBranchAddress("Lbhi",lbhi);
  tr->SetBranchAddress("Lbho",lbho);
  setrange(xindex,xmin,xmax);
  setrange(yindex,ymin,ymax);

  TCanvas c1("c1","c1",600,600);
  c1.cd();
  for (int i=0;i<150;i++)
  {
    string ii=to<string>(i);
    //drawnormal/drawto=================================//
    TH2F *t2i,*t2o;
    //drawmean==========================================//
    TH2F **t3i=new TH2F*[3];
    TH2F **t3o=new TH2F*[3];
    
    //==================================================//
    if (dn||dt)
    {
      t2i=new TH2F((figdir+"i"+ii).c_str(),(figdir+" snapshot "+ii).c_str(),100,xmin,xmax,100,ymin,ymax);
      t2o=new TH2F((figdir+"o"+ii).c_str(),(figdir+" snapshot "+ii).c_str(),100,xmin,xmax,100,ymin,ymax);
    }
    //==================================================//
    if (dm)
      for (int j=0;j<3;j++)
      {
        t3i[j]=new TH2F((figdir+"i_m"+to<string>(j+1)+ii).c_str(),(figdir+"i mean snapshot "+ii).c_str(),100,xmin,xmax,100,xmin,xmax);
        t3o[j]=new TH2F((figdir+"o_m"+to<string>(j+1)+ii).c_str(),(figdir+"o mean snapshot "+ii).c_str(),100,xmin,xmax,100,xmin,xmax);
      }
    //==================================================//

    tr->Draw(">>drawlist",("t=="+ii).c_str(),"entrylist");
    TEntryList *dlist=(TEntryList*)gDirectory->Get("drawlist");
    Int_t totnum=dlist->GetN();
    
    for (int j=0;j<totnum;j++)
    {
      Int_t entryi=dlist->GetEntry(j);
      tr->GetEntry(entryi);
      //==================================================//
      if (dn||dt)
      {
        t2i->Fill(lfill(xindex,lsi),lfill(yindex,lsi));
        t2o->Fill(lfill(xindex,lso),lfill(yindex,lso));
      }
      //==================================================//
      if (dm)
        for (int jj=0;jj<3;jj++)
        {
          t3i[jj]->Fill(lsim[jj][xindex],lsim[jj][yindex]);
          t3o[jj]->Fill(lsom[jj][xindex],lsom[jj][yindex]);
        }
      //==================================================//
    }

    //==================================================//
    if (dn||dt)
    {
      t2i->SetTitle((xt+"(before) vs. "+yt+"(before), time = "+ii).c_str());
      t2i->SetXTitle(xt.c_str());
      t2i->SetYTitle(yt.c_str());
      t2i->SetMarkerColor(kBlue);
      t2i->SetMarkerStyle(8);
      t2i->SetMarkerSize(1);
      t2i->Draw();
    }
    if (dn)
    {
      string filename=filepath+rootname+"/"+figdir+"i/";
      if (i==0)
        if(mkpath(filename.c_str(),0777)==-1)//creating a directory
        {
          cerr<<"Error :  "<<strerror(errno)<<endl;
          exit(1);
        }
      c1.Print((filename+figdir+ii+".png").c_str());
      cout<<"Print "+filename+figdir<<ii<<endl;
    }
    if (dn||dt)
    {
      t2o->SetTitle((xt+"(after) vs. "+yt+"(after), time = "+ii).c_str());
      t2o->SetXTitle(xt.c_str());
      t2o->SetYTitle(yt.c_str());
      t2o->SetMarkerStyle(8);
      t2o->SetMarkerSize(1);
    }
    if (dn)
    {
      t2o->SetMarkerColor(kBlue);
      t2o->Draw();
      filename=filepath+rootname+"/"+figdir+"o/";
      if (i==0)
        if(mkpath(filename.c_str(),0777)==-1)//creating a directory
        {
          cerr<<"Error :  "<<strerror(errno)<<endl;
          exit(1);
        }
      c1.Print((filename+figdir+ii+".png").c_str());
      cout<<"Print "+filename+figdir<<ii<<endl;
    }
    if (dt)
    {
      t2o->SetMarkerColor(kGreen);
      t2o->Draw("same");
      for (int j=0;j<totnum;j++)
      {
        Int_t entryi=dlist->GetEntry(j);
        tr->GetEntry(entryi);
        TArrow *ntr=new TArrow(lfill(xindex,lsi),lfill(yindex,lsi),lfill(xindex,lso),lfill(yindex,lso),0.03);
        ntr->SetLineColor(kRed);
        ntr->Draw();
      }
      filename=filepath+rootname+"/"+figdir+"io/";
      if (i==0)
        if(mkpath(filename.c_str(),0777)==-1)//creating a directory
        {
          cerr<<"Error :  "<<strerror(errno)<<endl;
          exit(1);
        }
      c1.Print((filename+figdir+ii+".png").c_str());
      cout<<"Print "+filename+figdir<<ii<<endl;
    }
    if (dm)
      for (int j=0;j<3;j++)
      {
        string ind=to<string>(j+1);
        t3i[j]->SetTitle(("#LT"+xt+"#GT(before) vs. #LT"+yt+"#GT(before), time = "+ii).c_str());
        t3i[j]->SetXTitle(xt.c_str());
        t3i[j]->SetYTitle(yt.c_str());
        t3i[j]->SetMarkerColor(kBlue);
        t3i[j]->SetMarkerStyle(8);
        t3i[j]->SetMarkerSize(1);
        t3i[j]->Draw();
        filename=filepath+rootname+"/"+figdir+"im"+ind+"/";
        if (i==0)
          if(mkpath(filename.c_str(),0777)==-1)//creating a directory
          {
            cerr<<"Error :  "<<strerror(errno)<<endl;
            exit(1);
          }
        c1.Print((filename+figdir+ii+".png").c_str());
        cout<<"Print "+filename+figdir<<ii<<endl;
        t3o[j]->SetTitle(("#LT"+xt+"#GT(after) vs. #LT"+yt+"#GT(after), time = "+ii).c_str());
        t3o[j]->SetXTitle(xt.c_str());
        t3o[j]->SetYTitle(yt.c_str());
        t3o[j]->SetMarkerColor(kBlue);
        t3o[j]->SetMarkerStyle(8);
        t3o[j]->SetMarkerSize(1);
        t3o[j]->Draw();
        filename=filepath+rootname+"/"+figdir+"om"+ind+"/";
        if (i==0)
          if(mkpath(filename.c_str(),0777)==-1)//creating a directory
          {
            cerr<<"Error :  "<<strerror(errno)<<endl;
            exit(1);
          }
        c1.Print((filename+figdir+ii+".png").c_str());
        cout<<"Print "+filename+figdir<<ii<<endl;
      }
  }
  return 0;
}
