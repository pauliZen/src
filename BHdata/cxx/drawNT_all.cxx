//Draw T_ejecting histogram, dEvsT histogram for group of runs//
//Store graphs in pdf format========================//
//Need run drawNT first to get the figure root file=//

#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <initial.h>
#include <uftools.h>
#include <map>
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TChain.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TEntryList.h"

struct fdata{
  std::string fname;
  double m[2],ce;
};

int main(int argc, char** argv) {
  pars_initial init(".drawNT_all_config");
  init.add("rootname","root file of NT figures","NT.root");
  init.add("filelist","file that list the filename of models, BH masses and E_criterion","drawlist.lst");
  init.add("desplit","dE split number",10);
  init.add("dNt","T histogram figure name suffix","dNt");
  init.add("dNAt","T histogram figure name suffix","dNAt");
  init.add("Nmax","Nmax for total T histogram",1000);
  init.add("dEt","dE weighted T histogram figure name suffix","dEt_hist");
  init.add("Emax","Emax for total dE weighted T histogram",0.01);
  init.add("path","figures storage path","./"); 
  init.add("format","output figure format","eps");
  init.add("yoff","y label offset",1.5);
  init.initial(argc,argv);
  
  std::string filelist=init.gets("filelist");

  ifstream fr(filelist.c_str());

  if(!fr.is_open()) {
    std::cerr<<"Error! cannot open file"<<filelist<<std::endl;
    return 0;
  }
  
  std::string ftmp;
  double m1,m2,ce;
  fdata tmp;
  std::vector<fdata> flist;
  while(!fr.eof()){
    fr>>ftmp;
    fr>>m1;
    fr>>m2;
    fr>>ce;
    tmp.fname=ftmp;
    tmp.m[0]=m1;
    tmp.m[1]=m2;
    tmp.ce=ce;
    if(!fr.eof()) flist.push_back(tmp);
  }
  
  TFile *f=new TFile(init.gets("rootname").c_str(),"update");

  int ides=init.geti("desplit");

  TCanvas c1;
  for(int j=0;j<ides;j++) {
    TH1F *ntn=(TH1F*)gDirectory->Get((flist[flist.size()-1].fname+"-"+init.gets("dNt")+tostr(j)).c_str())->Clone();
    TH1F **dnt=new TH1F*[flist.size()-1];
    ntn->SetLineColor((flist.size()-1)%10?(flist.size()-1):(flist.size()+19));
    ntn->GetYaxis()->SetTitleOffset(init.getd("yoff"));
    ntn->Draw();
    TLegend *tl=new TLegend(0.6,0.6,0.89,0.89);
    tl->SetFillStyle(0);
    tl->SetLineColor(0);
    for(unsigned int i=0;i<flist.size()-1;i++) {
      dnt[i]=(TH1F*)gDirectory->Get((flist[i].fname+"-"+init.gets("dNt")+tostr(j)).c_str());
      tl->AddEntry(dnt[i],("M_{BH1}="+tostr(flist[i].m[0])+"  M_{BH2}="+tostr(flist[i].m[1])).c_str());
      dnt[i]->SetLineColor(i%10?i:i+20);
      dnt[i]->Draw("same");
    }
    tl->AddEntry(ntn,("M_{BH1}="+tostr(flist[flist.size()-1].m[0])+"  M_{BH2}="+tostr(flist[flist.size()-1].m[1])).c_str());
    tl->Draw();
    c1.Print((init.gets("path")+init.gets("dNt")+tostr(j)+"."+init.gets("format")).c_str());
    c1.Clear();

    TH1F *natn=(TH1F*)gDirectory->Get((flist[flist.size()-1].fname+"-"+init.gets("dNAt")+tostr(j)).c_str())->Clone();
    TH1F **dnat=new TH1F*[flist.size()-1];
    natn->SetLineColor((flist.size()-1)%10?(flist.size()-1):(flist.size()+19));
    natn->GetYaxis()->SetTitleOffset(init.getd("yoff"));
    double maxfc=1;
    TLegend *tal=new TLegend(0.6,0.6,0.89,0.89);
    tal->SetFillStyle(0);
    tal->SetLineColor(0);
    for(unsigned int i=0;i<flist.size()-1;i++) {
      dnat[i]=(TH1F*)gDirectory->Get((flist[i].fname+"-"+init.gets("dNAt")+tostr(j)).c_str());
      maxfc=std::max(dnat[i]->GetMaximum(),maxfc);
      tal->AddEntry(dnat[i],("M_{BH1}="+tostr(flist[i].m[0])+"  M_{BH2}="+tostr(flist[i].m[1])).c_str());
      dnat[i]->SetLineColor(i%10?i:i+20);
    }
    natn->SetMaximum(maxfc);
    natn->Draw();
    for(unsigned int i=0;i<flist.size()-1;i++) dnat[i]->Draw("same");
    tal->AddEntry(natn,("M_{BH1}="+tostr(flist[flist.size()-1].m[0])+"  M_{BH2}="+tostr(flist[flist.size()-1].m[1])).c_str());
    tal->Draw();
    c1.Print((init.gets("path")+init.gets("dNAt")+tostr(j)+"."+init.gets("format")).c_str());
    c1.Clear();

    TH1F *nte=(TH1F*)gDirectory->Get((flist[flist.size()-1].fname+"-"+init.gets("dEt")+tostr(j)).c_str())->Clone();
    TH1F **det=new TH1F*[flist.size()-1];      
    nte->SetLineColor((flist.size()-1)%10?(flist.size()-1):(flist.size()+19));
    nte->GetYaxis()->SetTitleOffset(init.getd("yoff"));
    nte->Draw();
    TLegend *tel=new TLegend(0.6,0.6,0.89,0.89);
    tel->SetFillStyle(0);
    tel->SetLineColor(0);
    for(unsigned int i=0;i<flist.size()-1;i++) {
      det[i]=(TH1F*)gDirectory->Get((flist[i].fname+"-"+init.gets("dEt")+tostr(j)).c_str());
      tel->AddEntry(det[i],("M_{BH1}="+tostr(flist[i].m[0])+"  M_{BH2}="+tostr(flist[i].m[1])).c_str());
      det[i]->SetLineColor(i%10?i:i+20);
      det[i]->Draw("same");
    }
    tel->AddEntry(nte,("M_{BH1}="+tostr(flist[flist.size()-1].m[0])+"  M_{BH2}="+tostr(flist[flist.size()-1].m[1])).c_str());
    tl->Draw();
    c1.Print((init.gets("path")+init.gets("dEt")+tostr(j)+"."+init.gets("format")).c_str());
    c1.Clear();
  }

  FILE* fo;
  if ( (fo = fopen((init.gets("path")+init.gets("dNt")+".dat").c_str(),"w")) == NULL) {
    std::cerr<<"Error! cannot open file "<<init.gets("path")<<init.gets("dNt")<<".dat\n";
    return 0;
  }
  int **dat=new int*[flist.size()];
  int *cumdat=new int[flist.size()];
  memset(cumdat,0,sizeof(int)*flist.size());
  TH1F *ntn=(TH1F*)gDirectory->Get((flist[flist.size()-1].fname+"-"+init.gets("dNt")).c_str())->Clone();
  TH1F **dnt=new TH1F*[flist.size()-1];
  int xbins=ntn->GetNbinsX();
  int *t=new int[xbins];
  for (unsigned int i=0;i<flist.size();i++) dat[i]=new int[xbins];
  for(int i=0;i<xbins;i++) {
    t[i]=(int)ntn->GetBin(i);
    dat[flist.size()-1][i]=ntn->GetBinContent(i);
    cumdat[flist.size()-1] +=ntn->GetBinContent(i);
  }
  ntn->GetYaxis()->SetTitleOffset(init.getd("yoff"));
  ntn->SetLineColor((flist.size()-1)%10?(flist.size()-1):(flist.size()+19));
  ntn->SetMaximum(init.geti("Nmax"));
  ntn->SetTitle("");
  ntn->Draw();
  TLegend *tl=new TLegend(0.6,0.6,0.89,0.89);
  tl->SetFillStyle(0);
  tl->SetLineColor(0);
  for(unsigned int i=0;i<flist.size()-1;i++) {
    dnt[i]=(TH1F*)gDirectory->Get((flist[i].fname+"-"+init.gets("dNt")).c_str());
    for (int j=0;j<xbins;j++) {
      dat[i][j]=dnt[i]->GetBinContent(j);
      cumdat[i]+=dnt[i]->GetBinContent(j);
    }
    tl->AddEntry(dnt[i],("M_{BH1}="+tostr(flist[i].m[0])+"  M_{BH2}="+tostr(flist[i].m[1])).c_str());
    dnt[i]->SetMaximum(init.geti("Nmax"));
    dnt[i]->SetLineColor(i%10?i:i+20);
    dnt[i]->Draw("same");
  }
  tl->AddEntry(ntn,("M_{BH1}="+tostr(flist[flist.size()-1].m[0])+"  M_{BH2}="+tostr(flist[flist.size()-1].m[1])).c_str());
  tl->Draw();
  c1.Print((init.gets("path")+init.gets("dNt")+"."+init.gets("format")).c_str());
  c1.Clear();
  fprintf(fo,"Time[NB]");
  for (unsigned int i=0;i<flist.size();i++) fprintf(fo,"\t%5.3f/%5.3f",flist[i].m[0],flist[i].m[1]);
  fprintf(fo,"\n");
  for (int j=0;j<xbins;j++) {
    fprintf(fo,"%d",t[j]);
    for (unsigned int i=0;i<flist.size();i++) fprintf(fo,"\t%d",dat[i][j]);
    fprintf(fo,"\n");
  }
  fclose(fo);
  delete [] dat;

  //==================================================//

  FILE* foa;
  if ( (foa = fopen((init.gets("path")+init.gets("dNAt")+".dat").c_str(),"w")) == NULL) {
    std::cerr<<"Error! cannot open file "<<init.gets("path")<<init.gets("dNAt")<<".dat\n";
    return 0;
  }
  int **dat2=new int*[flist.size()];
  int *cumdat2=new int[flist.size()];
  memset(cumdat2,0,sizeof(int)*flist.size());
  TH1F *natn=(TH1F*)gDirectory->Get((flist[flist.size()-1].fname+"-"+init.gets("dNAt")).c_str())->Clone();
  TH1F **dnat=new TH1F*[flist.size()-1];
  int maxfc=1;
  xbins=natn->GetNbinsX();
  int *ta=new int[xbins];
  for (unsigned int i=0;i<flist.size();i++) dat2[i]=new int[xbins];
  for(int i=0;i<xbins;i++) {
    ta[i]=(int)natn->GetBin(i);
    dat2[flist.size()-1][i]=natn->GetBinContent(i);
    maxfc=std::max(dat2[flist.size()-1][i],maxfc);
    cumdat2[flist.size()-1] +=natn->GetBinContent(i);
  }
  natn->GetYaxis()->SetTitleOffset(init.getd("yoff"));
  natn->SetLineColor((flist.size()-1)%10?(flist.size()-1):(flist.size()+19));
  TLegend *tal=new TLegend(0.6,0.6,0.89,0.89);
  tal->SetFillStyle(0);
  tal->SetLineColor(0);
  //  int maxfactor=1;
  for(unsigned int i=0;i<flist.size()-1;i++) {
    dnat[i]=(TH1F*)gDirectory->Get((flist[i].fname+"-"+init.gets("dNAt")).c_str());
    for (int j=0;j<xbins;j++) {
      dat2[i][j]=dnat[i]->GetBinContent(j);
      maxfc=std::max(dat2[i][j],maxfc);
      cumdat2[i]+=dnat[i]->GetBinContent(j);
    }
    tal->AddEntry(dnat[i],("M_{BH1}="+tostr(flist[i].m[0])+"  M_{BH2}="+tostr(flist[i].m[1])).c_str());
    dnat[i]->SetMaximum(std::max(init.geti("Nmax")*1000,maxfc));
    dnat[i]->SetLineColor(i%10?i:i+20);
  }
  natn->SetMaximum(std::max(init.geti("Nmax")*1000,maxfc));
  natn->SetTitle("");
  natn->Draw();
  for(unsigned int i=0;i<flist.size()-1;i++) dnat[i]->Draw("same");
  tal->AddEntry(natn,("M_{BH1}="+tostr(flist[flist.size()-1].m[0])+"  M_{BH2}="+tostr(flist[flist.size()-1].m[1])).c_str());
  tal->Draw();
  c1.Print((init.gets("path")+init.gets("dNAt")+"."+init.gets("format")).c_str());
  c1.Clear();
  fprintf(foa,"Time[NB]");
  for (unsigned int i=0;i<flist.size();i++) fprintf(foa,"\t%5.3f/%5.3f",flist[i].m[0],flist[i].m[1]);
  fprintf(foa,"\n");
  for (int j=0;j<xbins;j++) {
    fprintf(foa,"%d",ta[j]);
    for (unsigned int i=0;i<flist.size();i++) fprintf(foa,"\t%d",dat2[i][j]);
    fprintf(foa,"\n");
  }
  fclose(foa);
  delete [] dat2;

  //dEt===============================================//  
  if( (fo = fopen((init.gets("path")+init.gets("dEt")+".dat").c_str(),"w")) == NULL) {
    std::cerr<<"Error! cannot open file "<<init.gets("path")<<init.gets("dEt")<<".dat\n";
    return 0;
  }
  double **datn=new double*[flist.size()];
  double *cumdatn=new double[flist.size()];
  memset(cumdatn,0,sizeof(int)*flist.size());
  TH1F *nte=(TH1F*)gDirectory->Get((flist[flist.size()-1].fname+"-"+init.gets("dEt")).c_str())->Clone();
  TH1F **det=new TH1F*[flist.size()-1];      
  xbins=nte->GetNbinsX();
  for (unsigned int i=0;i<flist.size();i++) datn[i]=new double[xbins];
  for(int i=0;i<xbins;i++) {
    datn[flist.size()-1][i]=nte->GetBinContent(i);
    cumdatn[flist.size()-1] +=nte->GetBinContent(i);
  }
  nte->GetYaxis()->SetTitleOffset(init.getd("yoff"));
  nte->SetLineColor((flist.size()-1)%10?(flist.size()-1):(flist.size()+19));
  nte->SetMaximum(init.getd("Emax"));
  nte->SetTitle("");
  nte->Draw();
  TLegend *tel=new TLegend(0.6,0.6,0.89,0.89);
  tel->SetFillStyle(0);
  tel->SetLineColor(0);
  for(unsigned int i=0;i<flist.size()-1;i++) {
    det[i]=(TH1F*)gDirectory->Get((flist[i].fname+"-"+init.gets("dEt")).c_str());
    for (int j=0;j<xbins;j++) {
      datn[i][j]=det[i]->GetBinContent(j);
      cumdatn[i] +=det[i]->GetBinContent(j);
    }
    tel->AddEntry(det[i],("M_{BH1}="+tostr(flist[i].m[0])+"  M_{BH2}="+tostr(flist[i].m[1])).c_str());
    det[i]->SetMaximum(init.getd("Emax"));
    det[i]->SetLineColor(i%10?i:i+20);
    det[i]->Draw("same");
  }
  tel->AddEntry(nte,("M_{BH1}="+tostr(flist[flist.size()-1].m[0])+"  M_{BH2}="+tostr(flist[flist.size()-1].m[1])).c_str());
  tel->Draw();
  c1.Print((init.gets("path")+init.gets("dEt")+"."+init.gets("format")).c_str());
  c1.Clear();
  fprintf(fo,"Time[NB]");
  for (unsigned int i=0;i<flist.size();i++) fprintf(fo,"\t%5.3f/%5.3f",flist[i].m[0],flist[i].m[1]);
  fprintf(fo,"\n");
  for (int j=0;j<xbins;j++) {
    fprintf(fo,"%d",t[j]);
    for (unsigned int i=0;i<flist.size();i++) fprintf(fo,"\t%f",datn[i][j]);
    fprintf(fo,"\n");
  }
  fclose(fo);
  delete [] datn;

  if( (fo = fopen((init.gets("path")+"sum.dat").c_str(),"w")) == NULL) {
    std::cerr<<"Error! cannot open file "<<init.gets("path")<<"sum.dat\n";
    return 0;
  }
  fprintf(fo,"M1\tM2\tM1+M2\tmu\tN\tdE\n");
  for (unsigned int i=0;i<flist.size();i++) {
    double m1=flist[i].m[0];
    double m2=flist[i].m[1];
    fprintf(fo,"%f\t%f\t%f\t%f\t%d\t%f\n",m1,m2,m1+m2,m1*m2/(m1+m2),cumdat[i],cumdatn[i]);
  }
  fclose(fo);
  delete cumdatn;
  delete cumdat;
  
  f->Close();
    
  return 0;
}
