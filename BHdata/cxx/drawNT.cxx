//Draw T_ejecting histogram, dE vs T profile for one run//
//Store graphs in pdf format and root file==========//
//Need filelist of *-result-dE-* file (one run)=====//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <initial.h>
#include <uftools.h>
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TChain.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TEntryList.h"

#define TCheckNum 3

int main(int argc, char** argv) {
  pars_initial init(".drawNT_config");
  init.add("Filelist","root file list for chain","de.lst");
  init.add("bhparfile","bhparfile name","-bhpars.root");
  init.add("treename","tree name for chain","destars");
  init.add("dNt","dN vs T histgraft","dNt");
  init.add("dNAt","dN vs T histgraft","dNAt");
  init.add("Nmax","Maximum range of dNt plot",1000);
  init.add("Emax","Maximum range of dEhist plot",0.01);
  init.add("tbins","bins for dNt",100);
  init.add("tmin","tmin of dNt and dEt",0.0);
  init.add("tmax","tmax of dNt and dEt",150);
  init.add("desplit","number of bins of dE",10);
  init.add("desm","Method to split bins, 1: linear, 2:log",1);
  init.add("dEt","2D dE vs T histgraft","dEt");
  init.add("ebins","ebins for dEt",100);
  init.add("emin","emin of dEt",0.0);
  init.add("emax","emax of dEt",10.0);
  init.add("zmax","zmax of coutz",100);
  init.add("mbh1","mass of bh1",1.0);
  init.add("mbh2","mass of bh2",1.0);
  init.add("dopt","draw option of 2D plots dEt","CONTZ");
  init.add("path","figures storage path","./");
  init.add("rootname","root to store figures","NT.root");
  init.add("format","output figure format","eps");
  init.initial(argc,argv);
  
  std::string filelist=init.gets("Filelist");
  
  ifstream fr(filelist.c_str());

  if(!fr.is_open()) {
    std::cerr<<"Error! cannot open file"<<filelist<<std::endl;
    return 0;
  }
  
  std::string ftmp;
  std::vector<std::string> flist;
  while(!fr.eof()){
    fr>>ftmp;
    if(!fr.eof()) flist.push_back(ftmp);
  }

  mkdir(init.gets("path"));

  TFile *fbh=new TFile(init.gets("bhparfile").c_str(),"update");
  fbh->cd();
  TTree *ftbh=(TTree*)gDirectory->Get("BHpars");
  Double_t time,overa;
  ftbh->SetBranchAddress("t",&time);
  ftbh->SetBranchAddress("over_a",&overa);
 
  TChain *ftree=new TChain(init.gets("treename").c_str());
  Int_t index;
  Double_t t[3],En[2],En_err[2],mass;
  Double_t Lsi[6],Lbhi[6],Lso[6],Lbho[6],Lsi_err[TCheckNum][6],Lso_err[TCheckNum][6];
  Double_t Lsi_mean[TCheckNum][6],Lso_mean[TCheckNum][6];
  Double_t ri[4],rbi[4],vi[4],vbi[4],poti[2],ai[6];
  Double_t rd[4],rbd[4],vd[4],vbd[4],potd[2],ad[6];
  Double_t bh12i[3],bh12o[3];
  // new parameters===================================//
  ftree->SetBranchAddress("t",t);
  ftree->SetBranchAddress("En",En);
  ftree->SetBranchAddress("En_err",En_err);
  // angular momentum ==============================//
  ftree->SetBranchAddress("Lsi",Lsi);
  ftree->SetBranchAddress("Lsi_mean",Lsi_mean);
  ftree->SetBranchAddress("Lsi_err",Lsi_err);
  ftree->SetBranchAddress("Lbhi",Lbhi);
  ftree->SetBranchAddress("Lso",Lso);
  ftree->SetBranchAddress("Lso_mean",Lso_mean);
  ftree->SetBranchAddress("Lso_err",Lso_err);
  ftree->SetBranchAddress("Lbho",Lbho);
  // inherit before eject=============================//
  ftree->SetBranchAddress("index",&index);
  ftree->SetBranchAddress("mass",&mass);  
  ftree->SetBranchAddress("ri",ri);
  ftree->SetBranchAddress("rbi",rbi);
  ftree->SetBranchAddress("vi",vi);
  ftree->SetBranchAddress("vbi",vbi);
  ftree->SetBranchAddress("poti",poti);
  ftree->SetBranchAddress("ai",ai);
  // variance after eject=============================//
  ftree->SetBranchAddress("rd",rd);
  ftree->SetBranchAddress("rbd",rbd);
  ftree->SetBranchAddress("vd",vd);
  ftree->SetBranchAddress("vbd",vbd);
  ftree->SetBranchAddress("potd",potd);
  ftree->SetBranchAddress("ad",ad);
  ftree->SetBranchAddress("bh12i",bh12i);
  ftree->SetBranchAddress("bh12o",bh12o);

  for (unsigned int i=0;i<flist.size();i++) {
    std::cout<<flist[i]<<std::endl;
    ftree->AddFile(flist[i].c_str());
  }

  // Get dE bins
  int desp=init.geti("desplit");
  double *derange=new double[desp+1];
  double detrange=0.;
  if(init.geti("desm")==1){
    detrange=(init.getd("emax")-init.getd("emin"))/(double)desp;
  }else if(init.geti("desm")==2) {
    detrange=pow(init.getd("emax")/init.getd("emin"),1.0/desp);
  }else {
    std::cerr<<"Error: Incorrect method to split energy!\n";
    return 0;
  }
  derange[0]=init.getd("emin");
  for (int i=1; i<=desp; i++) {
    if(init.geti("desm")==1){
      derange[i]=derange[i-1]+detrange;
    }else if(init.geti("desm")==2) {
      derange[i]=derange[i-1]*detrange;
    }
  }

  double maxfactor=1.0;
  //Histogram
  TH1F **dnt=new TH1F*[desp];
  TH1F **dnat=new TH1F*[desp];
  TH1F **deh=new TH1F*[desp];
  TLegend *tl=new TLegend(0.7,0.6,0.9,0.9);
  TLegend *tal=new TLegend(0.7,0.6,0.9,0.9);
  TLegend *tel=new TLegend(0.7,0.6,0.9,0.9);
  tl->SetFillStyle(0);
  tal->SetFillStyle(0);
  tel->SetFillStyle(0);
  for (int i=0;i<desp;i++) {
    dnt[i]=new TH1F((init.gets("dNt")+tostr(i)).c_str(),("dE~("+tostr(derange[i])+","+tostr(derange[i+1])+")").c_str(),init.geti("tbins"),init.getd("tmin"),init.getd("tmax"));
    dnt[i]->SetLineColor(i%10?i:i+20);
    dnt[i]->SetStats(kFALSE);
    dnt[i]->SetXTitle("Time[NB]");
    dnt[i]->SetYTitle("N_{eject}");
    dnat[i]=new TH1F((init.gets("dNAt")+tostr(i)).c_str(),("dE~("+tostr(derange[i])+","+tostr(derange[i+1])+")").c_str(),init.geti("tbins"),init.getd("tmin"),init.getd("tmax"));
    dnat[i]->SetLineColor(i%10?i:i+20);
    dnat[i]->SetStats(kFALSE);
    dnat[i]->SetXTitle("Time[NB]");
    dnat[i]->SetYTitle("N_{eject}/(M_{12}a)");
    deh[i]=new TH1F((init.gets("dEt")+"_hist"+tostr(i)).c_str(),("dE~("+tostr(derange[i])+","+tostr(derange[i+1])+")").c_str(),init.geti("tbins"),init.getd("tmin"),init.getd("tmax"));
    deh[i]->SetLineColor(i%10?i:i+20);
    deh[i]->SetStats(kFALSE);
    deh[i]->SetXTitle("Time[NB]");
    deh[i]->SetYTitle("dE_{eject}");
    tl->AddEntry(dnt[i],("dE~("+tostr(derange[i])+","+tostr(derange[i+1])+")").c_str());
    tal->AddEntry(dnt[i],("dE~("+tostr(derange[i])+","+tostr(derange[i+1])+")").c_str());
    tel->AddEntry(deh[i],("dE~("+tostr(derange[i])+","+tostr(derange[i+1])+")").c_str());
    ftree->Draw((">>drawlist"+tostr(i)).c_str(),("En[1]>="+tostr(derange[i])+"&&En[1]<"+tostr(derange[i+1])).c_str(),"entrylist");
    TEntryList *tlist=(TEntryList*)gDirectory->Get(("drawlist"+tostr(i)).c_str());
    ftree->SetEntryList(tlist);
    Int_t entrynum=tlist->GetN();
    for(int j=0;j<entrynum;j++) {
      Int_t trnum=0;
      Int_t entryj=tlist->GetEntryAndTree(j,trnum);
      ftree->GetEntry(entryj+ftree->GetTreeOffset()[trnum]);
      dnt[i]->Fill(t[1]-1);
      deh[i]->Fill(t[1]-1,En[1]);
    }
    int bi=0;
    const int btot=ftbh->GetEntries();
    const int nt=dnat[i]->GetNbinsX();
    for (int j=1;j<=nt;j++) {
      double tc=dnt[i]->GetBinCenter(j);
      do{
        ftbh->GetEntry(bi);
        bi++;
        if (bi>btot) break;
      }while (tc-time>0.05);
      if(time-tc>0.5) {
        std::cerr<<"Time-tc>"<<time-tc<<std::endl;
        return 0;
      }
      if (bi>btot) break;
      double dat=dnt[i]->GetBinContent(j)*overa/(init.getd("mbh1")+init.getd("mbh2"));
      maxfactor=std::max(maxfactor,dat);
      dnat[i]->SetBinContent(j,dat);
      //      std::cout<<"COUNT TC"<<tc<<" TIME"<<time<<" dat"<<dat<<std::endl;
    }
    ftree->SetEntryList(0);
  }

  TCanvas c1;
  TH1F *dnd=new TH1F(init.gets("dNt").c_str(),("M_{BH1}="+init.gets("mbh1")+"  M_{BH2}="+init.gets("mbh2")).c_str(),init.geti("tbins"),init.getd("tmin"),init.getd("tmax"));
  dnd->SetMaximum(init.geti("Nmax"));
  dnd->SetXTitle("Time[NB]");
  dnd->SetYTitle("N_{eject}");
  dnd->SetStats(kFALSE);
  dnd->Draw();
  for (int i=0;i<desp;i++) {
    dnt[i]->Draw("same");
  }
  tl->Draw();
  c1.Print((init.gets("path")+init.gets("dNt")+"."+init.gets("format")).c_str());
  //  std::cout<<"Draw dNt\n";

  c1.Clear();
  TH1F *dnad=new TH1F(init.gets("dNAt").c_str(),("M_{BH1}="+init.gets("mbh1")+"  M_{BH2}="+init.gets("mbh2")).c_str(),init.geti("tbins"),init.getd("tmin"),init.getd("tmax"));
  dnad->SetMaximum(std::max(init.geti("Nmax")*1000.0,maxfactor));
  dnad->SetXTitle("Time[NB]");
  dnad->SetYTitle("N_{eject}");
  dnad->SetStats(kFALSE);
  dnad->Draw();
  for (int i=0;i<desp;i++) {
    dnat[i]->Draw("same");
  }
  tal->Draw();
  c1.Print((init.gets("path")+init.gets("dNAt")+"."+init.gets("format")).c_str());
  //  std::cout<<"Draw dNAt\n";

  c1.Clear();
  TH1F *dehist=new TH1F((init.gets("dEt")+"_hist").c_str(),("M_{BH1}="+init.gets("mbh1")+"  M_{BH2}="+init.gets("mbh2")).c_str(),init.geti("tbins"),init.getd("tmin"),init.getd("tmax"));
  dehist->SetMaximum(init.getd("Emax"));
  dehist->SetXTitle("Time[NB]");
  dehist->SetYTitle("dE_{eject}");
  dehist->SetStats(kFALSE);
  dehist->Draw();
  for (int i=0;i<desp;i++) {
    deh[i]->Draw("same");
  }
  tel->Draw();
  c1.Print((init.gets("path")+init.gets("dEt")+"_hist."+init.gets("format")).c_str());
  //  std::cout<<"Draw dE_hist\n";
  
  TH2F *det=new TH2F(init.gets("dEt").c_str(),("M_{BH1}="+init.gets("mbh1")+"  M_{BH2}="+init.gets("mbh2")).c_str(),init.geti("tbins"),init.getd("tmin"),init.getd("tmax"),init.geti("ebins"),init.getd("emin"),init.getd("emax"));
  Int_t ntot=ftree->GetEntries();
  for (Int_t i=0;i<ntot;i++) {
    dnd->Fill(t[1]-1);
    dehist->Fill(t[1]-1,En[1]);
    ftree->GetEntry(i);
    det->Fill(t[1]-1,En[1]);
  }
  int bi=0;
  const int btot=ftbh->GetEntries();
  const int nt=dnad->GetNbinsX();
  for (int j=1;j<=nt;j++) {
    double tc=dnd->GetBinCenter(j);
    do{
      ftbh->GetEntry(bi);
      bi++;
      if (bi>btot) break;
    }while (tc-time>0.05);
    if(time-tc>0.5) {
      std::cerr<<"Time-tc>"<<time-tc<<std::endl;
      return 0;
    }
    if (bi>btot) break;
    double dat=dnd->GetBinContent(j)*overa/(init.getd("mbh1")+init.getd("mbh2"));
    maxfactor=std::max(maxfactor,dat);
    dnad->SetBinContent(j,dat);
    //      std::cout<<"COUNT TC"<<tc<<" TIME"<<time<<" dat"<<dat<<std::endl;
  }
  det->SetXTitle("Time[NB]");
  det->SetYTitle("dE");
  det->SetStats(kFALSE);
  det->GetZaxis()->SetRangeUser(1,init.geti("zmax"));
  c1.SetLogz(1);
  c1.Clear();
  det->Draw(init.gets("dopt").c_str());
  c1.Print((init.gets("path")+init.gets("dEt")+"."+init.gets("format")).c_str());
  //  std::cout<<"Draw dEt\n";

  TFile *fn=new TFile(init.gets("rootname").c_str(),"update");
  for (int i=0;i<desp;i++) {
    dnt[i]->Write("",TObject::kOverwrite);
    dnat[i]->Write("",TObject::kOverwrite);
    deh[i]->Write("",TObject::kOverwrite);
  }
  
  dnd->Write("",TObject::kOverwrite);
  dnad->Write("",TObject::kOverwrite);
  det->Write("",TObject::kOverwrite);
  dehist->Write("",TObject::kOverwrite);
  //  std::cout<<"Write to root\n";

  fbh->Close();
  fn->Close();
  return 0;
}
