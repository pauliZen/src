// Draw dE vs T, E vs T, Lout/Lint =================//
// Store graphs in eps format=======================//
// Command:[prog.] [rootname] [figdir] [selstartree]//
//         [destartree] [dEfigname] [etfigname]=====//
//         [Liofigname] [Ldfigname] [Lcfigname]=====//
//         [dEtsplit] [bhmass1] [bhmass2]===========//
//         [Etreename] [critde] ====================//
//          rootname: [dirname]=====================//
//                    (no suffix, no order)=========//
//          figdir: directory to store figures======//
//          selstartree: selected star data=========//
//          destartree: selected star dE&t data tree//
//          dEfigname: dE vs. T figure name=========//
//          etfigname: E vs. T figure name==========//
//          Liofigname: L out/L in figure name======//
//                      suffix number 1-3:x,y,z=====//
//                      4-6: r,a,d==================//
//          Ldfigname: L distribution figure name===//
//                     suffix number as above=======//
//          Lcfigname: cumulative L vs T============//
//                     suffix (bh/s)================//
//          dEtsplit: dEt file split number=========//
//                    if 1, no split================//
//          bhmass1/2: black hole mass, in nbody unit/
//          Etreename: E****to**** treename=========//
//          critde:    Energy Criterion to select star
// Notes: all figure name no '.eps' suffix==========//

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
#include "TBits.h"
#include "TLegend.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TEntryList.h"
#include "TAxis.h"
#include "TPaveText.h"
#include "TPad.h"
#include "TFrame.h"

using namespace std;

//Fuction define====================================//
//Draw EvsT star====================================//
Int_t drawstarEt (TFile *savefile,string dEvsTstarhist="dEvsTstar",string newhistname="EvsTstar",string drawoption="")
{
  TH1D *starde=(TH1D*)gDirectory->Get(dEvsTstarhist.c_str());
  Int_t bins=starde->GetNbinsX();
  Double_t xmin=starde->GetXaxis()->GetXmin();
  Double_t xmax=starde->GetXaxis()->GetXmax();
  Double_t sum=0;
  TH1D *stare=new TH1D(newhistname.c_str(),"total energy of eject stars vs. time",bins,xmin,xmax);
  //  TH1D *h2=new TH1D("deltaEvsTime","Consecutive Delta E of eject stars vs. time_eject",150,0,150);
  for (Int_t i=1;i<=bins;i++)
  {
    sum +=starde->GetBinContent(i);
    stare->SetBinContent(i,sum);
  }
  stare->SetXTitle("time");
  stare->SetYTitle("total energy");
  stare->Draw(drawoption.c_str());
  savefile->cd();
  stare->Write("",TObject::kOverwrite);
  return sum;
}  

//draw both dE, dL vs T and L out/in======//
//draw angle between Ls to lbh out/in=====//
//draw histograme of angle==========================//
//draw histograme of angle and time=================//
//draw histogram of theta vs. phi===================//
Int_t drawstardE (TFile *savefile,TChain *ftree,string figdir,string liofig,Double_t ave_e,Double_t ave_over_a,Double_t bhmass[2],bool drall=1,string histname="dEvsTstar",string lxh="dLxvsTstar",string lyh="dLyvsTstar",string lzh="dLzvsTstar",string lbsdhi="Angle_Hist",string lbsdho="ALstobhodist",string lbsdhfig="Angle_Lstobhdist",string drawoption="",Int_t bins=150,Double_t xmin=0,Double_t xmax=150)
{
  string bh1m,bh2m,ae,aoa;
  stringstream ssstr;
  ssstr.str("");
  ssstr.clear();
  ssstr<<bhmass[0];
  ssstr>>bh1m;
  ssstr.str("");
  ssstr.clear();
  ssstr<<bhmass[1];
  ssstr>>bh2m;
  ssstr.str("");
  ssstr.clear();
  ssstr<<ave_e;
  ssstr>>ae;
  ssstr.str("");
  ssstr.clear();
  ssstr<<ave_over_a;
  ssstr>>aoa;

  Double_t teject[3],deltaE[2],li[6],lo[6],lbi[6],lbo[6],lim[3][6],lom[3][6],lie[3][6],loe[3][6];
  Int_t index;
  //lbsdot: ls.lb; lbdot:lb.lb; lsdot: ls.ls; lbsc: lb*ls; lbscdot=lbsc.lbsc;
  Double_t lbsdot,lbdot,lsdot,lbscdot,bh12dot;
  Double_t lbsc[3],bhi12[3],bho12[3],bh_y[3],lbsc_bh12dot;
  Double_t te,theta[2],phi[2],cosphi[2];
  Double_t rbi[4],rbo[4];
  ftree->SetBranchAddress("t",teject);
  ftree->SetBranchAddress("index",&index);
  ftree->SetBranchAddress("En",deltaE);
  ftree->SetBranchAddress("Lsi",li);
  ftree->SetBranchAddress("Lso",lo);
  ftree->SetBranchAddress("Lbhi",lbi);
  ftree->SetBranchAddress("Lbho",lbo);
  ftree->SetBranchAddress("Lsi_mean",lim);
  ftree->SetBranchAddress("Lso_mean",lom);
  ftree->SetBranchAddress("Lsi_err",lie);
  ftree->SetBranchAddress("Lso_err",loe);
  ftree->SetBranchAddress("bh12i",bhi12);
  ftree->SetBranchAddress("bh12o",bho12);
  ftree->SetBranchAddress("rbi",rbi);
  ftree->SetBranchAddress("rbd",rbo);
  TTree *ntree=new TTree("langle","Angle_&_L_data_of_ESs");
  ntree->Branch("index",&index);
  ntree->Branch("t",&te);
  ntree->Branch("En",deltaE,"En[2]/D");
  ntree->Branch("theta",theta,"theta[2]/D");
  ntree->Branch("phi",phi,"phi[2]/D");
  ntree->Branch("Lsi",li,"Lsi[6]/D");
  ntree->Branch("Lso",lo,"Lso[6]/D");
  ntree->Branch("Lbhi",lbi,"Lbhi[6]/D");
  ntree->Branch("Lbho",lbo,"Lbho[6]/D");
  ntree->Branch("Lsi_mean",lim,"Lsi_mean[3][6]/D");
  ntree->Branch("Lso_mean",lom,"Lso_mean[3][6]/D");
  ntree->Branch("Lsi_err",lie,"Lsi_err[3][6]/D");
  ntree->Branch("Lso_err",loe,"Lso_err[3][6]/D");
  ntree->Branch("rbi",rbi,"rbi[4]/D");
  ntree->Branch("rbo",rbo,"rbo[4]/D");
  Int_t totnum=ftree->GetEntries();
  TH1D *starde=new TH1D(histname.c_str(),"Delta E of eject stars vs. time_eject",bins,xmin,xmax);
  //  TH1D *h2=new TH1D("deltaEvsTime","Consecutive Delta E of eject stars vs. time_eject",150,0,150);
  TH1D *slx=new TH1D(lxh.c_str(),"Delta Lx of ejects stars vs. time",bins,xmin,xmax);
  TH1D *sly=new TH1D(lyh.c_str(),"Delta Ly of ejects stars vs. time",bins,xmin,xmax);
  TH1D *slz=new TH1D(lzh.c_str(),"Delta Lz of ejects stars vs. time",bins,xmin,xmax);
  TH1D *lbsdi=new TH1D(lbsdhi.c_str(),"Angle between Lstar to Lbh before eject",60,0,3.1415926);
  TH1D *lbsdo=new TH1D(lbsdho.c_str(),"Angle between Lstar to Lbh after eject",60,0,3.1415926);
  TH1D *lbsdcosi=new TH1D((lbsdhi+"c").c_str(),"Cos Angle between Lstar to Lbh before eject",100,-1,1);
  TH1D *lbsdcoso=new TH1D((lbsdho+"c").c_str(),"Cos Angle between Lstar to Lbh after eject",100,-1,1);
  TH1D *lbsphii=new TH1D("phi_dist_i","#phi distribution before ejecting",90,0,6.2832);
  TH1D *lbsphio=new TH1D("phi_dist_o","#phi distribution after ejecting",90,0,6.2832);
  TH1D *lbscosphii=new TH1D("phi_dist_ic","#phi distribution before ejecting",100,-1,1);
  //  TH1D *lbscosphio=new TH1D("phi_dist_oc","#phi distribution after ejecting",100,-1,1);
  TH2D *lbsthetaphii=new TH2D("theta_vs_phi_i","#theta vs. #phi before eject",360,0,6.2832,180,0,3.1415926);
  TH2D *lbsthetaphio=new TH2D("theta_vs_phi_o","#theta vs. #phi after eject",360,0,6.2832,180,0,3.1415926);
  TH2D *lbspg=new TH2D("phi_vs_t","#phi vs. t_{eject}",150,0,150,180,0,6.2832);
  TH2D *lbstg=new TH2D("theta_vs_t","#theta vs. t_{eject}",150,0,150,180,0,3.1415926);
  //  Double_t *lbsangle=new Double_t[totnum];
  //  Double_t *lbst=new Double_t[totnum];
  for (Int_t i=0;i<totnum;i++)
  {
    ftree->GetEntry(i);
    ////    lbst[i]=teject[0];
    starde->Fill(teject[1]-1,deltaE[1]);

    slx->Fill(teject[1]-1,lo[0]-li[0]);
    sly->Fill(teject[1]-1,lo[1]-li[1]);
    slz->Fill(teject[1]-1,lo[2]-li[2]);

    //For input star====================================//
    //Basic pars========================================//
    lsdot=sqrt(li[0]*li[0]+li[1]*li[1]+li[2]*li[2]);
    lbdot=sqrt(lbi[0]*lbi[0]+lbi[1]*lbi[1]+lbi[2]*lbi[2]);
    lbsdot=li[0]*lbi[0]+li[1]*lbi[1]+li[2]*lbi[2];
    lbsc[0]=lbi[1]*li[2]-lbi[2]*li[1];
    lbsc[1]=lbi[2]*li[0]-lbi[0]*li[2];
    lbsc[2]=lbi[0]*li[1]-lbi[1]*li[0];
    lbscdot=sqrt(lbsc[0]*lbsc[0]+lbsc[1]*lbsc[1]+lbsc[2]*lbsc[2]);
        
    //angle=============================================//
    //theta=============================================//
    theta[0]=acos(lbsdot/(lsdot*lbdot));
    //phi===============================================//
    bh_y[0]=lbi[1]*bhi12[2]-lbi[2]*bhi12[1];
    bh_y[1]=lbi[2]*bhi12[0]-lbi[0]*bhi12[2];
    bh_y[2]=lbi[0]*bhi12[1]-lbi[1]*bhi12[0];
    bh12dot =sqrt(bhi12[0]*bhi12[0]+bhi12[1]*bhi12[1]+bhi12[2]*bhi12[2]);
    lbsc_bh12dot =lbsc[0]*bhi12[0]+lbsc[1]*bhi12[1]+lbsc[2]*bhi12[2];
    cosphi[0]=lbsc_bh12dot/(lbscdot*bh12dot);
    if(lbsc[0]*bh_y[0]+lbsc[1]*bh_y[1]+lbsc[2]*bh_y[2]>=0)
      phi[0]=acos(cosphi[0]);
    else
      phi[0]=2*3.1415926-acos(cosphi[0]);
#ifdef DEBUG
    std::cout<<"phi:"<<phi[0]<<std::endl;
#endif    
    //Fill histogram====================================//
    lbsdi->Fill(theta[0]);
    lbsphii->Fill(phi[0]);
    lbscosphii->Fill(cosphi[0]);
    lbsdcosi->Fill((lbsdot/(lsdot*lbdot)));
    lbstg->Fill(teject[1]-1,theta[0]);
    lbspg->Fill(teject[1]-1,phi[0]);
    lbsthetaphii->Fill(phi[0],theta[0]);

    //output pars=======================================//
    te=teject[1]-1;
    //    cout<<"lsdot:"<<lsdot<<"; lbdot:"<<lbdot<<"; lbsdot:"<<lbsdot<<acos(lbsdot/(lsdot*lbdot))<<endl;
    lsdot=sqrt(lo[0]*lo[0]+lo[1]*lo[1]+lo[2]*lo[2]);
    lbdot=sqrt(lbo[0]*lbo[0]+lbo[1]*lbo[1]+lbo[2]*lbo[2]);
    lbsdot=lo[0]*lbo[0]+lo[1]*lbo[1]+lo[2]*lbo[2];
    lbsc[0]=lbo[1]*lo[2]-lbo[2]*lo[1];
    lbsc[1]=lbo[2]*lo[0]-lbo[0]*lo[2];
    lbsc[2]=lbo[0]*lo[1]-lbo[1]*lo[0];
    lbscdot=sqrt(lbsc[0]*lbsc[0]+lbsc[1]*lbsc[1]+lbsc[2]*lbsc[2]);

    //angle=============================================//
    theta[1]=acos(lbsdot/(lsdot*lbdot));
    //phi===============================================//
    bh_y[0]=lbo[1]*bho12[2]-lbo[2]*bho12[1];
    bh_y[1]=lbo[2]*bho12[0]-lbo[0]*bho12[2];
    bh_y[2]=lbo[0]*bho12[1]-lbo[1]*bho12[0];
    bh12dot =sqrt(bho12[0]*bho12[0]+bho12[1]*bho12[1]+bho12[2]*bho12[2]);
    lbsc_bh12dot =lbsc[0]*bho12[0]+lbsc[1]*bho12[1]+lbsc[2]*bho12[2];
    cosphi[1]=lbsc_bh12dot/(lbscdot*bh12dot);
    if(lbsc[0]*bh_y[0]+lbsc[1]*bh_y[1]+lbsc[2]*bh_y[2]>=0)
      phi[1]=acos(cosphi[1]);
    else
      phi[1]=2*3.1415926-acos(cosphi[1]);

    //Fill histogram====================================//
    lbsdo->Fill(theta[1]);
    lbsphio->Fill(phi[1]);
    lbsdcoso->Fill((lbsdot/(lsdot*lbdot)));
    lbsthetaphio->Fill(phi[1],theta[1]);

    ntree->Fill();
  }
  //  TGraph *lbstg=new TGraph(totnum,lbst,lbsangle);
  lbstg->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
  lbspg->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
  lbstg->GetXaxis()->SetTitle("t");
  lbspg->GetXaxis()->SetTitle("t");
  lbstg->GetYaxis()->SetTitle("#theta");
  lbspg->GetYaxis()->SetTitle("#phi");
  lbstg->SetStats(kFALSE);
  lbspg->SetStats(kFALSE);
  starde->SetXTitle("time");
  slx->SetXTitle("time");
  sly->SetXTitle("time");
  slz->SetXTitle("time");
  slx->SetYTitle("Lx change");
  sly->SetYTitle("Ly change");
  slz->SetYTitle("Lz change");
  //  lbsdi->SetXTitle("Angle(L_{star} to L_{SMBHs})");
  //  lbsdo->SetXTitle("Angle(L_{star} to L_{SMBHs})");
  lbsdi->SetXTitle("#theta");
  lbsdo->SetXTitle("#theta");
  lbsdcosi->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
  lbsdcoso->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
  lbsdcosi->SetXTitle("Cos(#theta)");
  lbsdcoso->SetXTitle("Cos(#theta)");
  if (bhmass[0]<0.02)
  {
    lbsdcosi->SetMaximum(300);
    lbsdcosi->SetMinimum(0);
    lbsdcoso->SetMaximum(300);
    lbsdcoso->SetMinimum(0);
  }
  else if (bhmass[0]==0.02)
  {
    lbsdcosi->SetMaximum(600);
    lbsdcosi->SetMinimum(0);
    lbsdcoso->SetMaximum(600);
    lbsdcoso->SetMinimum(0);
  }
  else
  {
    lbsdcosi->SetMaximum(1500);
    lbsdcosi->SetMinimum(0);
    lbsdcoso->SetMaximum(1500);
    lbsdcoso->SetMinimum(0);
  }
  lbsphii->SetXTitle("#phi");
  lbscosphii->SetXTitle("cos#phi");
  lbsphio->SetXTitle("#phi");
  lbsphii->SetYTitle("#phi distribution");
  lbscosphii->SetYTitle("cos#phi distribution");
  lbsphio->SetYTitle("#phi distribution");
  lbsphii->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
  lbscosphii->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
  lbsphio->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
  if (bhmass[0]<0.02)
  {
    lbsphii->SetMaximum(300);
    lbsphii->SetMinimum(0);
    //    lbscosphii->SetMaximum(300);
    //    lbscosphii->SetMinimum(0);
    lbsphio->SetMaximum(300);
    lbsphio->SetMinimum(0);
  }
  else if (bhmass[0]==0.02)
  {
    lbsphii->SetMaximum(600);
    lbsphii->SetMinimum(0);
  }
  else
  {
    lbsphii->SetMaximum(1200);
    lbsphii->SetMinimum(300);
    // lbscosphii->SetMaximum(1200);
    // lbscosphii->SetMinimum(300);
    lbsphio->SetMaximum(1200);
    lbsphio->SetMinimum(300);
  }
  lbsdi->SetYTitle("Angle distribution");
  lbsdo->SetYTitle("Angle distribution");
  lbsdcosi->SetYTitle("Number of ejected stars");
  lbsdcoso->SetYTitle("Cos[#theta] distribution");
  lbsthetaphii->SetYTitle("#theta");
  lbsthetaphio->SetYTitle("#theta");
  lbsthetaphii->SetStats(kFALSE);
  lbsthetaphio->SetStats(kFALSE);
  lbsthetaphii->SetXTitle("#phi");
  lbsthetaphio->SetXTitle("#phi");
  lbsthetaphii->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
  lbsthetaphio->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
  savefile->cd();
  slx->Write("",TObject::kOverwrite);
  sly->Write("",TObject::kOverwrite);
  slz->Write("",TObject::kOverwrite);
  lbsdi->Write("",TObject::kOverwrite);
  lbsdo->Write("",TObject::kOverwrite);
  lbsdcosi->Write("",TObject::kOverwrite);
  lbsdcoso->Write("",TObject::kOverwrite);
  lbsthetaphii->Write("",TObject::kOverwrite);
  lbsthetaphio->Write("",TObject::kOverwrite);
  starde->SetYTitle("energy change");
  starde->Draw(drawoption.c_str());
  starde->Write("",TObject::kOverwrite);
  ntree->Write("",TObject::kOverwrite);
  TCanvas c2("c2","c2",720,600);
  lbstg->Draw("CONT1Z");
  c2.Print((figdir+"thetavstimec.eps").c_str());
  c2.Clear();
  lbspg->Draw("CONT1Z");
  c2.Print((figdir+"phivstimec.eps").c_str());
  c2.Clear();
  lbstg->Draw();
  c2.Print((figdir+"thetavstime.eps").c_str());
  c2.Clear();
  lbsthetaphii->Draw("CONT1Z");
  c2.Print((figdir+"thetavsphii.eps").c_str());
  c2.Clear();
  lbsthetaphio->Draw("CONT1Z");
  c2.Print((figdir+"thetavsphio.eps").c_str());
  c2.Clear();
  lbscosphii->Draw("");
  c2.Print((figdir+"cosphidisti.eps").c_str());
  c2.Clear();
  //Draw phi dist=====================================//
  TH1D *lbsphi=(TH1D*)lbsphii->Clone();
  lbsphi->SetTitle("");
  lbsphi->SetLineWidth(3);
  lbsphi->SetLineColor(kBlack);
  lbsphi->GetYaxis()->SetTitleOffset(1.5);
  lbsphi->Draw();
  lbsphio->SetLineWidth(2);
  lbsphio->SetLineColor(14);
  lbsphio->GetYaxis()->SetTitleOffset(1.5);
  lbsphio->Draw("same");
  Double_t tlby1=0.67, tlby2=0.75;
  if ((bhmass[0]==0.01&&bhmass[1]==0.01)||(bhmass[0]==0.04&&bhmass[1]==0.04))
  {
    tlby1=0.37;
    tlby2=0.45;
  }
  TLegend *tlbsphi=new TLegend(0.72,tlby1,0.9,tlby2);
  tlbsphi->SetFillStyle(0);
  tlbsphi->AddEntry(lbsphi,"before eject");
  tlbsphi->AddEntry(lbsphio,"after eject");
  tlbsphi->Draw();
  TPaveText *tlatphi=new TPaveText(0.14,0.75,0.3,0.9,"NDC");
  tlatphi->SetFillStyle(0);
  tlatphi->SetLineStyle(0);
  tlatphi->SetShadowColor(0);
  tlatphi->SetTextAlign(12);
  tlatphi->AddText(("M_{ BH1} = "+bh1m).c_str());
  tlatphi->AddText(("M_{ BH2} = "+bh2m).c_str());
  tlatphi->AddText(("#LTe#GT ="+ae).c_str());
  tlatphi->AddText(("#LT1/a#GT ="+aoa).c_str());
  tlatphi->Draw();
  c2.Print((figdir+"phidist.eps").c_str());
  c2.Clear();
  TH1D *lbsd=(TH1D*)lbsdi->Clone();
  //  lbsd->SetTitle("Angle of L_{star} to L_{SMBHs} distribution");
  lbsd->SetTitle("");
  lbsd->SetLineColor(kBlue);
  lbsd->GetYaxis()->SetTitleOffset(1.5);
  lbsd->Draw();
  lbsdo->SetLineColor(kRed);
  lbsdo->GetYaxis()->SetTitleOffset(1.5);
  lbsdo->Draw("same");
  TLegend *tlbsd=new TLegend(0.72,0.67,0.9,0.75);
  tlbsd->SetFillStyle(0);
  tlbsd->AddEntry(lbsd,"before eject");
  tlbsd->AddEntry(lbsdo,"after eject");
  //  tlbsd->AddEntry((TObject*)0,("Black hole mass: "+bh1m+", "+bh2m).c_str());
  //  tlbsd->AddEntry((TObject*)0,("Average e between time of 100 to 150: "+ae).c_str());
  //  tlbsd->AddEntry((TObject*)0,("Average 1/a between time of 100 to 150: "+aoa).c_str());
  tlbsd->Draw();
  TPaveText *tlat=new TPaveText(0.14,0.75,0.3,0.9,"NDC");
  //  tlat->SetTextAlign(23);
  //  tlat->SetTextSize(0.04);
  tlat->SetFillStyle(0);
  tlat->SetLineStyle(0);
  tlat->SetShadowColor(0);
  tlat->SetTextAlign(12);
  tlat->AddText(("M_{ BH1} = "+bh1m).c_str());
  tlat->AddText(("M_{ BH2} = "+bh2m).c_str());
  tlat->AddText(("#LTe#GT ="+ae).c_str());
  tlat->AddText(("#LT1/a#GT ="+aoa).c_str());
  tlat->Draw();
  c2.Print((figdir+lbsdhfig+".eps").c_str());
  c2.Clear();
  TH1D *lbsdcos=(TH1D*)lbsdcosi->Clone();
  lbsdcos->SetTitle("");
  lbsdcos->SetLineWidth(3);
  lbsdcos->SetLineColor(kBlack);
  lbsdcos->GetYaxis()->SetTitleOffset(1.5);
  lbsdcos->Draw();
  lbsdcoso->SetLineColor(14);
  lbsdcoso->SetLineWidth(2);
  lbsdcoso->GetYaxis()->SetTitleOffset(1.5);
  lbsdcoso->Draw("same");
  TLegend *tlbsdc=new TLegend(0.6,0.82,0.78,0.9);
  tlbsdc->SetFillStyle(0);
  tlbsdc->AddEntry(lbsdcos,"before eject");
  tlbsdc->AddEntry(lbsdcoso,"after eject");
  tlbsdc->Draw();
  tlat->Draw();
  c2.Print((figdir+lbsdhfig+"_cos.eps").c_str());
  c2.Clear();
  if (drall)
  {
  
  //draw L out/in=====================================//
  string lil[6]={"L_{x}(before)", "L_{y}(before)", "L_{z}(before)", "L_{r}(before)", "#alpha_{before}", "cos(#delta)_{before}"};
  string lol[6]={"L_{x}(after)", "L_{y}(after)", "L_{z}(after)", "L_{r}(after)", "#alpha_{after}", "cos(#delta)_{after}"};
  Double_t lbhi[6], lbho[6];
  ftree->SetBranchAddress("Lbho",lbho);
  ftree->SetBranchAddress("Lbhi",lbhi);
  for (int i=0;i<6;i++)
  {
    stringstream sstr;
    sstr.str("");
    sstr.clear();
    sstr<<i;
    string ii;
    sstr>>ii;
    if (i<4)
      ftree->Draw(("Lso["+ii+"]:Lsi["+ii+"]").c_str(),("abs(Lsi["+ii+"])<0.2E-6&&abs(Lso["+ii+"])<0.2E-6").c_str(),"CONTZ");
    else if (i==4)
      ftree->Draw(("Lso["+ii+"]:Lsi["+ii+"]").c_str(),"","CONTZ");
    else
      ftree->Draw(("cos(Lso["+ii+"]):cos(Lsi["+ii+"])").c_str(),"","CONTZ");
    TH2F *htp=(TH2F*)gPad->GetPrimitive("htemp");
    TH2F *ht=(TH2F*)htp->Clone();
    ht->SetName(("Lio["+ii+"]").c_str());
    ht->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
    ht->SetXTitle(lil[i].c_str());
    ht->SetYTitle(lol[i].c_str());
    if (i==4)
    {
      ht->GetXaxis()->SetRangeUser(0,6.283);
      ht->GetYaxis()->SetRangeUser(0,6.283);
    }
    if (i==5)
    {
      ht->GetXaxis()->SetRangeUser(-1,1);
      ht->GetYaxis()->SetRangeUser(-1,1);
    }
    savefile->cd();
    ht->Write("",TObject::kOverwrite);
    //c2.Print((figdir+liofig+ii+".eps").c_str());
    //    if (i<4)
    //      ftree->Draw(("Lbho["+ii+"]:Lbhi["+ii+"]").c_str(),("abs(Lbhi["+ii+"])<0.2E-6&&abs(Lbho["+ii+"])<0.2E-6").c_str(),"CONTZ");
    //    else
    //    ftree->Draw(("Lbho["+ii+"]:Lbhi["+ii+"]>>htemp").c_str());
    Int_t totnum=ftree->GetEntries();
    Float_t xrange,yrange,xrm,yrm;
    if (i==4)
    {
      xrm=0;
      yrm=0;
      xrange=6.283;
      yrange=6.283;
    }
    else if (i==5)
    {
      xrm=-1;
      yrm=-1;
      xrange=1;
      yrange=1;
    }
    else
    {
      xrm=0;
      yrm=0;
      xrange=0.2E-6;
      yrange=0.2E-6;
    }
    TH2F *hbt=new TH2F("hbt","Black hole angular momentum",180,xrm,xrange,180,yrm,yrange);
    for (int j=0;j<totnum;j++)
    {
      ftree->GetEntry(j);
      if (i==5)
        hbt->Fill(cos(lbhi[i]),cos(lbho[i]));
      else
        hbt->Fill(lbhi[i],lbho[i]);
    }
    hbt->SetName(("Lbho["+ii+"]").c_str());
    //    hbt->SetTitle("Black Hole angular momentum after vs. before eject");
    hbt->SetXTitle(lil[i].c_str());
    hbt->SetYTitle(lol[i].c_str());
    hbt->SetMarkerStyle(20);
    hbt->SetLineColor(kBlack);
    ht->Draw("CONT1Z");
    hbt->Draw("CONT2same");
    savefile->cd();
    hbt->Write("",TObject::kOverwrite);
    c2.Print((figdir+liofig+"bh"+ii+".eps").c_str());
  }

  //Draw L star to bh angle distribution==============//
  //ftree->Draw("Lbh[");
  }  
  return totnum;
}

//Draw dEvsT bh=====================================//
Int_t drawbhdE (TFile *savefile,Double_t bhmass1,Double_t bhmass2, Double_t *ave_e, Double_t *ave_over_a,string treename="BHpars",string histnamedE="dEvsTbh",string histE="EvsTbh",string drawoption="",Int_t bins=150,Double_t xmin=0,Double_t xmax=150)
{
  *ave_e=0;
  *ave_over_a=0;
  Int_t counti=0;
  Double_t time,doa,overa,e;
  TTree *ftree=(TTree*)gDirectory->Get(treename.c_str());
  ftree->SetBranchAddress("t",&time);
  ftree->SetBranchAddress("dover_a",&doa);
  ftree->SetBranchAddress("over_a",&overa);
  ftree->SetBranchAddress("e",&e);
  Int_t totnum=ftree->GetEntries();
  TH1D *bhde=new TH1D(histnamedE.c_str(),"Delta E of bh binary vs. time",bins,xmin,xmax);
  //  TH1D *h2=new TH1D("deltaEvsTime","Consecutive Delta E of eject stars vs. time_eject",150,0,150);
  for (Int_t i=0;i<totnum;i++)
  {
    ftree->GetEntry(i);
    bhde->Fill(time,doa*bhmass1*bhmass2/2);
    if (time>100&&time<150)
    {
      counti++;
      *ave_e +=e;
      *ave_over_a +=overa;
    }
  }
  *ave_e /=counti;
  *ave_over_a /=counti;
  bhde->SetXTitle("t");
  bhde->SetYTitle("#Delta E");
  bhde->Draw(drawoption.c_str());
  savefile->cd();
  bhde->Write("",TObject::kOverwrite);
  Int_t bins2=totnum-1;
  ftree->GetEntry(0);
  Double_t xmin2=time;
  ftree->GetEntry(bins2-1);
  Double_t xmax2=time;
  ftree->GetEntry(1);
  Double_t tmp=time;
  bins2=(xmax2-xmin2)/(tmp-xmin2)+1;
  TH1D *bhe=new TH1D(histE.c_str(),"total energy of BHs vs. time", bins2,xmin2,xmax2);
  for (Int_t i=0;i<bins2;i++)
  {
    ftree->GetEntry(i);
    bhe->Fill(time,overa*bhmass1*bhmass2/2);
  }
  bhe->SetXTitle("time");
  bhe->SetYTitle("total energy");
  bhe->Draw(drawoption.c_str());
  savefile->cd();
  bhe->Write("",TObject::kOverwrite);
  return totnum;
}

// Int_t drawbhEt (TFile *savefile,Double_t bhmass1,Double_t bhmass2,string treename="BHpars",string histname="EvsTbh",string drawoption="")
// {
//   Double_t time,
//   TTree *ftree=(TTree*)gDirectory->Get(treename.c_str());
//   ftree->SetBranchAddress("t",&time);

//   return bins;
// }

//Draw EvsT all=====================================//
void drawbhstarE (TFile *savefile, string bhhistname="EvsTbh",string starhistname="EvsTstar",string drawoption="")
{
  TH1D *star=(TH1D*)gDirectory->Get(starhistname.c_str());
  TH1D *comp=(TH1D*)star->Clone();
  TH1D *bh=(TH1D*)gDirectory->Get(bhhistname.c_str());
  comp->SetTitle("Total energy vs. time");
  comp->GetYaxis()->SetTitleOffset(1.25);
  comp->SetLineColor(kRed);
  comp->SetName("Energy");
  comp->Draw();
  bh->SetLineColor(kBlack);
  bh->Draw("same");
  TLegend *tl=new TLegend(0.4,0.2,0.85,0.35);
  tl->SetFillStyle(0);
  tl->AddEntry(comp,"star total energy change");
  tl->AddEntry(bh,"BHs energy M_{SMBHs}^2/(2a)");
  tl->Draw();
}

//Draw dEvsT all====================================//
Int_t drawtotdE (TFile *savefile, Double_t bhmass[2],string figdir, string defig, string star="dEvsTstar", string bh="dEvsTbh",string drawoption="")
{
  string bh1m,bh2m;
  stringstream ssstr;
  ssstr.str("");
  ssstr.clear();
  ssstr<<bhmass[0];
  ssstr>>bh1m;
  ssstr.str("");
  ssstr.clear();
  ssstr<<bhmass[1];
  ssstr>>bh2m;
  ssstr.str("");
  ssstr.clear();
  TH1D *s1=(TH1D*)gDirectory->Get(star.c_str());
  TH1D *b1=(TH1D*)gDirectory->Get(bh.c_str());
  Int_t snum=s1->GetNbinsX();
  Int_t bnum=b1->GetNbinsX();
  if (snum==bnum)
  {
    Double_t smin=s1->GetXaxis()->GetXmin();
    Double_t bmin=b1->GetXaxis()->GetXmin();
    if (smin==bmin)
    {
      Double_t smax=s1->GetXaxis()->GetXmax();
      Double_t bmax=b1->GetXaxis()->GetXmax();
      if (smax==bmax)
      {
        TCanvas c3;
        TH1D *t1=new TH1D("totdE","Delta E of total energy vs. time",snum,smin,smax);
        for (Int_t i=0;i<=snum;i++)
        {
          Double_t snow=s1->GetBinContent(i);
          Double_t bnow=b1->GetBinContent(i);
          Double_t tnow=-snow+bnow;
          t1->SetBinContent(i,tnow);
        }
        savefile->cd();
        t1->Write("",TObject::kOverwrite);
        TH1D *t3=(TH1D*)b1->Clone();
        t3->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
        t3->SetStats(kFALSE);
        t3->GetYaxis()->SetTitleOffset(1.25);
        t3->SetLineColor(kBlack);
        t3->SetName("dE");
        t3->Draw();
        b1->SetLineColor(kBlack);
        b1->SetLineWidth(2);
        b1->SetStats(kFALSE);
        s1->SetLineColor(12);
        s1->SetLineWidth(2);
        s1->SetStats(kFALSE);
        t1->Draw("same");
        b1->Draw("same");
        s1->Draw("same");
        t1->SetLineColor(15);
        t1->SetFillColor(15);
        TLegend *tl=new TLegend(0.4,0.2,0.85,0.35);
        if (bhmass[0]>=0.04||bhmass[1]>=0.04)
        {
          tl->SetY1(0.6);
          tl->SetY2(0.75);
        }
        tl->SetFillStyle(0);
        tl->AddEntry(t1,"Residual energy change: #Delta E_{b}(t) - #Delta E_{s}(t)");
        tl->AddEntry(b1,"SMBH's energy loss: #Delta E_{b}(t) = - #Delta #frac{M_{BH1}M_{BH2}}{2a(t)}");
        tl->AddEntry(s1,"ESs total energy change: #Delta E_{s}(t)");
        tl->Draw();
        c3.Print((figdir+defig+".eps").c_str());
        c3.Print((figdir+defig+".png").c_str());
        c3.Clear();
      }
      else
        cout<<"smax NE bmax"<<endl;
    }
    else
      cout<<"smin NE bmin"<<endl;
  }
  else
    cout<<"snum NE bnum"<<endl;
  return snum;
}

//draw all CONT of end:start============================//
//draw E/E_start hist and vs. time======================//
void drawLdist(string figdir,string ldfig, Double_t bhmass[2],Double_t critde,string treename="E0000to0150",bool drawall=0)
{
  string bh1m,bh2m,crit;
  stringstream ssstr;
  ssstr.str("");
  ssstr.clear();
  ssstr<<bhmass[0];
  ssstr>>bh1m;
  ssstr.str("");
  ssstr.clear();
  ssstr<<bhmass[1];
  ssstr>>bh2m;
  ssstr.str("");
  ssstr.clear();
  ssstr<<critde;
  ssstr>>crit;
  TCanvas c2("c2","c2",800,600);
  Double_t de,es;
  TTree *e=(TTree*)gDirectory->Get(treename.c_str());
  e->SetBranchAddress("dE",&de);
  e->SetBranchAddress("E_start",&es);
  Int_t tnu=e->GetEntries();
  TH1F *he=new TH1F("dEEshist","log(-dE/E_start) histogram",100,-1,1);
  TH1F *he2=new TH1F("dEEshist2","log(-dE/E_start) histogram",100,-1,1);
  TH2F *h2=new TH2F("dEEsEhist","E:log(-dE/E_start) histogram",100,-1,1,100,-2.0E-6,-0.2E-6);
  // TH2F *h3=new TH2F("dEEsEhist2",("E:log(-dE/E_start)>"+crit+" histogram").c_str(),100,-1,1,100,-1.4E-6,-0.4E-6);
  critde=log10(exp(critde));
  for (int i=0;i<tnu;i++)
  {
    e->GetEntry(i);
    if (-de/es>0&&es<0)
    {
      if (log10(-de/es)>critde)
      {
        he2->Fill(log10(-de/es));
        //        h3->Fill(log(-de/es),es);
      }
      else
      {
        he->Fill(log10(-de/es));
      }
      h2->Fill(log10(-de/es),es);
    }
  }
  he->SetXTitle("log(-#Delta E_{t}/E_{0})");
  he->GetXaxis()->SetTitleOffset(1);
  he->SetYTitle("Distribution");
  he->GetYaxis()->SetTitleOffset(0.7);
  he->SetTitle("");
  h2->SetXTitle("log(-#Delta E_{t}/E_{0})");
  h2->GetXaxis()->SetTitleOffset(1);
  h2->SetYTitle("E_{0}");
  h2->GetYaxis()->SetTitleOffset(0.7);
  h2->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m).c_str());
  h2->SetTitleSize(0.2);
  he->SetStats(kFALSE);
  h2->SetStats(kFALSE);
  TLine *hl=new TLine(critde,-2.0E-6,critde,-0.2E-6);
  hl->SetLineColor(kBlack);
  c2.Divide(1,2);
  c2.cd(1);
  h2->SetMarkerColor(kBlack);
  h2->GetXaxis()->SetTitleSize(0.045);
  h2->GetYaxis()->SetTitleSize(0.07);
  h2->GetXaxis()->SetLabelSize(0.05);
  h2->GetYaxis()->SetLabelSize(0.06);
  h2->Draw("CONTZ");
  gPad->SetLogz();
  //  gPad->SetPad(0,1,1,0.5);
  //  h3->SetMarkerColor(kBlack);
  //  h3->SetMarkerStyle(2);
  //  h3->SetMarkerSize(0.4);
  //  h3->Draw("CONT1same");
  hl->Draw();
  c2.cd(2);
  he->SetLineColor(12);
  he->GetYaxis()->SetTitleOffset(0.7);
  he->GetXaxis()->SetTitleSize(0.045);
  he->GetYaxis()->SetTitleSize(0.07);
  he->GetXaxis()->SetLabelSize(0.05);
  he->GetYaxis()->SetLabelSize(0.06);
  he->Draw();
  he2->SetLineColor(kBlack);
  he2->SetFillColor(12);
  he2->Draw("same");
  c2.Print((figdir+"dEEs.eps").c_str());
  c2.Print((figdir+"dEEs.pdf").c_str());
  c2.cd(1);
  c2.GetPad(1)->SetFillColor(kBlack);
  h2->GetXaxis()->SetLabelColor(kWhite);
  h2->GetXaxis()->SetTitleColor(kWhite);
  h2->GetXaxis()->SetAxisColor(kWhite);
  h2->GetYaxis()->SetAxisColor(kWhite);
  h2->GetYaxis()->SetLabelColor(kWhite);
  h2->GetYaxis()->SetTitleColor(kWhite);
  hl->SetLineColor(kWhite);
  he->GetXaxis()->SetLabelColor(kWhite);
  he->GetXaxis()->SetTitleColor(kWhite);
  he->GetXaxis()->SetAxisColor(kWhite);
  he->GetYaxis()->SetAxisColor(kWhite);
  he->GetYaxis()->SetLabelColor(kWhite);
  he->GetYaxis()->SetTitleColor(kWhite);
  he->SetLineColor(kWhite);
  he2->SetLineColor(kWhite);
  he2->SetFillColor(kWhite);
  h2->Draw("CONTZ");
  hl->Draw();
  c2.GetPad(1)->GetFrame()->SetLineColor(kWhite);
  c2.GetPad(1)->GetFrame()->Draw();
  c2.cd(2);
  c2.GetPad(2)->SetFillColor(kBlack);
  he->Draw();
  he2->Draw("same");
  c2.GetPad(2)->GetFrame()->SetLineColor(kWhite);
  c2.GetPad(2)->GetFrame()->Draw();
  c2.Print((figdir+"dEEs.png").c_str());
  c2.Clear();
  if (drawall)
  {
    string l[6]={"Lalpha_start","Ldelta_start","Lr_start","Lx_start","Ly_start","Lz_start"};
    for (int i=0;i<6;i++)
    {
      stringstream sstr;
      sstr.str("");
      sstr.clear();
      sstr<<i;
      string ii;
      sstr>>ii;
      c2.cd();
      e->Draw(l[i].c_str());
      // TH1F *lsd=(TH1F*)gDirectory->Get("h1");
      // lsd->SetTitle((l[i]+" distribution").c_str());
      // lsd->SetXTitle(l[i].c_str());
      // lsd->SetYTitle("N");
      // lsd->Draw();
      c2.Update();
      c2.Print((figdir+ldfig+ii+".eps").c_str());
    }
  }
}

//Draw cumulative L vs T============================//
void drawLc(string figdir,string lcfig,string selstarstree="selstars",string lxh="dLxvsTstar",string lyh="dLyvsTstar",string lzh="dLzvsTstar",string drawoption="AL")
{
  TCanvas c2;
  TTree *slt=(TTree*)gDirectory->Get(selstarstree.c_str());
  Double_t lbdot,lby,lbz,lbr,lba,lbd,lt,mass;
  Int_t index;
  slt->SetBranchAddress("Lx",&lbdot);
  slt->SetBranchAddress("Ly",&lby);
  slt->SetBranchAddress("Lz",&lbz);
  slt->SetBranchAddress("Lr",&lbr);
  slt->SetBranchAddress("Lalpha",&lba);
  slt->SetBranchAddress("Ldelta",&lbd);
  slt->SetBranchAddress("time_cur",&lt);
  slt->SetBranchAddress("mass",&mass);
  slt->SetBranchAddress("index",&index);
  double bm1=0,bm2=0;
  slt->GetEntry(0);
  if (index==999998)
    bm1=mass;
  else
  {
    int ii=0;
    while(!bm1)
    {
      slt->GetEntry(ii++);
      if (index==999998) bm1=mass;
    }
  }
  // slt->GetEntry(0);
  // Double_t lx0=lbdot;
  // Double_t ly0=lby;
  // Double_t lz0=lbz;
  slt->Draw(">>drawbhlist","index==999999&&time_cur>30","entrylist");
  TEntryList *bhlist=(TEntryList*)gDirectory->Get("drawbhlist");
  Int_t entrynum=bhlist->GetN();
  slt->GetEntry(bhlist->GetEntry(0));
  bm2=mass;
  double ratio=(bm2+bm1)/bm1;
  Double_t* lbhx=new Double_t[entrynum];
  Double_t* lbhy=new Double_t[entrynum];
  Double_t* lbhz=new Double_t[entrynum];
  Double_t* lbhr=new Double_t[entrynum];
  Double_t* lbha=new Double_t[entrynum];
  Double_t* lbhd=new Double_t[entrynum];
  Double_t* tbh=new Double_t[entrynum];
  for (int i=0;i<entrynum;i++)
  {
    Int_t entryi=bhlist->GetEntry(i);
    slt->GetEntry(entryi);
    lbhx[i]=ratio*lbdot;
    lbhy[i]=ratio*lby;
    lbhz[i]=ratio*lbz;
    lbhr[i]=ratio*lbr;
    lbha[i]=lba;
    lbhd[i]=lbd;
    tbh[i]=lt;
  }
  TGraph *gx=new TGraph(entrynum,tbh,lbhx);
  TGraph *gy=new TGraph(entrynum,tbh,lbhy);
  TGraph *gz=new TGraph(entrynum,tbh,lbhz);
  TGraph *gr=new TGraph(entrynum,tbh,lbhr);
  TGraph *ga=new TGraph(entrynum,tbh,lbha);
  TGraph *gd=new TGraph(entrynum,tbh,lbhd);
  gx->GetXaxis()->SetTitle("time");
  gy->GetXaxis()->SetTitle("time");
  gz->GetXaxis()->SetTitle("time");
  gr->GetXaxis()->SetTitle("time");
  ga->GetXaxis()->SetTitle("time");
  gd->GetXaxis()->SetTitle("time");
  gx->GetYaxis()->SetTitle("cumulative Lx");
  gy->GetYaxis()->SetTitle("cumulative Ly");
  gz->GetYaxis()->SetTitle("cumulative Lz");
  gr->GetYaxis()->SetTitle("cumulative Lr");
  ga->GetYaxis()->SetTitle("cumulative Lalpha");
  gd->GetYaxis()->SetTitle("cumulative Ldelta");
  gx->SetTitle("Cumulative Lx of black hole vs time");
  gy->SetTitle("Cumulative Ly of black hole vs time");
  gz->SetTitle("Cumulative Lz of black hole vs time");
  gr->SetTitle("Cumulative Lr of black hole vs time");
  ga->SetTitle("Cumulative Lalpha of black hole vs time");
  gd->SetTitle("Cumulative Ldelta of black hole vs time");

  // c2.Update();
  // c2.Print((figdir+lcfig+"_bh.eps").c_str());
  // c2.Clear();
  
  TH1D *lxs=(TH1D*)gDirectory->Get(lxh.c_str());
  TH1D *lys=(TH1D*)gDirectory->Get(lyh.c_str());
  TH1D *lzs=(TH1D*)gDirectory->Get(lzh.c_str());
  Int_t bins=lxs->GetNbinsX();
  Double_t xmin=lxs->GetXaxis()->GetXmin();
  Double_t xmax=lxs->GetXaxis()->GetXmax();
  Double_t sumx=0;
  Double_t sumy=0;
  Double_t sumz=0;
  Double_t sxy,sr;
  Double_t *lscx=new Double_t[bins];
  Double_t *lscy=new Double_t[bins];
  Double_t *lscz=new Double_t[bins];
  Double_t *lscr=new Double_t[bins];
  Double_t *lsca=new Double_t[bins];
  Double_t *lscd=new Double_t[bins];
  Double_t *dlx=new Double_t[bins];
  Double_t *dly=new Double_t[bins];
  Double_t *dlz=new Double_t[bins];
  Double_t *dlr=new Double_t[bins];
  Double_t *t=new Double_t[bins];
  Int_t begin=0;
  for (Int_t i=1;i<=bins;i++)
  {
    t[i-1]=(xmax-xmin)/bins*i-0.5;
    if (t[i-1]<30)
    {
      begin++;
      continue;
    }
    sumx +=lxs->GetBinContent(i);
    lscx[i-1]=sumx;
    sumy +=lys->GetBinContent(i);
    lscy[i-1]=sumy;
    sumz +=lzs->GetBinContent(i);
    lscz[i-1]=sumz;
    sr +=lzs->GetBinContent(i);
    sr=sqrt(sumx*sumx+sumy*sumy+sumz*sumz);
    sxy=sqrt(sumx*sumx+sumy*sumy);
    lscr[i-1]=sr;
    if (sxy==0)
      lsca[i-1]=0;
    if (sumy>0)
      lsca[i-1]=acos(sumx/sxy);
    else
      lsca[i-1]=2*3.1415926-acos(sumx/sxy);
    lscd[i-1]=acos(sumz/sr);
  }
  for (Int_t i=begin;i<bins;i++)
  {
    dlx[i]=lscx[i]+lbhx[i-begin]-lbhx[0];
    dly[i]=lscy[i]+lbhy[i-begin]-lbhy[0];
    dlz[i]=lscz[i]+lbhz[i-begin]-lbhz[0];
    dlr[i]=lscr[i]+lbhr[i-begin]-lbhr[0];
  }
  TGraph *d1=new TGraph(bins-begin,&t[begin],&dlx[begin]);
  TGraph *d2=new TGraph(bins-begin,&t[begin],&dly[begin]);
  TGraph *d3=new TGraph(bins-begin,&t[begin],&dlz[begin]);
  TGraph *dr=new TGraph(bins-begin,&t[begin],&dlr[begin]);
  TGraph *g1=new TGraph(bins-begin,&t[begin],&lscx[begin]);
  TGraph *g2=new TGraph(bins-begin,&t[begin],&lscy[begin]);
  TGraph *g3=new TGraph(bins-begin,&t[begin],&lscz[begin]);
  TGraph *g4=new TGraph(bins-begin,&t[begin],&lscr[begin]);
  TGraph *g5=new TGraph(bins-begin,&t[begin],&lsca[begin]);
  TGraph *g6=new TGraph(bins-begin,&t[begin],&lscd[begin]);
  d1->GetXaxis()->SetTitle("time");
  d2->GetXaxis()->SetTitle("time");
  d3->GetXaxis()->SetTitle("time");
  dr->GetXaxis()->SetTitle("time");
  d1->GetYaxis()->SetTitle("cLx+Lbhx");
  d2->GetYaxis()->SetTitle("cLy+Lbhy");
  d3->GetYaxis()->SetTitle("cLz+Lbhz");
  dr->GetYaxis()->SetTitle("cLr+Lbhr");
  g1->GetXaxis()->SetTitle("time");
  g1->GetYaxis()->SetTitle("cumulative Lx");
  g1->SetTitle("Cumulative change of Lx for stars vs time");
  g2->GetXaxis()->SetTitle("time");
  g2->GetYaxis()->SetTitle("cumulative Ly");
  g2->SetTitle("Cumulative change of Lx for stars vs time");
  g3->GetXaxis()->SetTitle("time");
  g3->GetYaxis()->SetTitle("cumulative Lz");
  g3->SetTitle("Cumulative change of Lz for stars vs time");
  g4->GetXaxis()->SetTitle("time");
  g4->GetYaxis()->SetTitle("cumulative Lr");
  g4->SetTitle("Cumulative change of Lr for stars vs time");
  g5->GetXaxis()->SetTitle("time");
  g5->GetYaxis()->SetTitle("cumulative La");
  g5->SetTitle("Cumulative change of Lalpha for stars vs time");
  g6->GetXaxis()->SetTitle("time");
  g6->GetYaxis()->SetTitle("cumulative Ld");
  g6->SetTitle("Cumulative change of Ldelta for stars vs time");
  
  TMultiGraph *gm=new TMultiGraph();
  gx->SetLineColor(kRed);
  gx->SetLineStyle(2);
  gx->SetFillColor(0);
  gy->SetLineColor(kGreen);
  gy->SetLineStyle(2);
  gy->SetFillColor(0);
  gz->SetLineColor(kBlue);
  gz->SetLineStyle(2);
  gz->SetFillColor(0);
  gr->SetLineColor(kBlack);
  gr->SetLineStyle(2);
  gr->SetFillColor(0);
  g1->SetLineColor(kRed);
  g1->SetFillColor(0);
  g1->SetLineStyle(3);
  g2->SetLineColor(kGreen);
  g2->SetFillColor(0);
  g2->SetLineStyle(3);
  g3->SetLineColor(kBlue);
  g3->SetFillColor(0);
  g3->SetLineStyle(3);
  g4->SetLineColor(kBlack);
  g4->SetFillColor(0);
  g4->SetLineStyle(3);
  d1->SetLineColor(kRed);
  d1->SetFillColor(0);
  d2->SetLineColor(kGreen);
  d2->SetFillColor(0);
  d3->SetLineColor(kBlue);
  d3->SetFillColor(0);
  dr->SetLineColor(kBlack);
  dr->SetFillColor(0);
  gm->Add(g1);
  gm->Add(gx);
  gm->Add(g2);
  gm->Add(gy);
  gm->Add(g3);
  gm->Add(gz);
  gm->Add(g4);
  gm->Add(gr);
  gm->Add(d1);
  gm->Add(d2);
  gm->Add(d3);
  gm->Add(dr);
  //gm->GetXaxis()->SetTitle("time");
  //gm->GetYaxis()->SetTitle("cumulative L");
  gm->SetTitle("Cumulative L(x,y,z) of stars(black hole) vs time");
  gm->Draw(drawoption.c_str());
  TLegend *tle=new TLegend(0.57,0.75,0.9,0.9);
  tle->AddEntry(g1,"Cumulative change of Lx for all ejected stars");
  tle->AddEntry(g2,"Cumulative change of Ly for all ejected stars");
  tle->AddEntry(g3,"Cumulative change of Lz for all ejected stars");
  tle->AddEntry(g4,"Cumulative change of L for all ejected stars");
  tle->AddEntry(gx,"Lx of bhs");
  tle->AddEntry(gy,"Ly of bhs");
  tle->AddEntry(gz,"Lz of bhs");
  tle->AddEntry(gr,"L of bhs");
  tle->AddEntry(d1,"DLx");
  tle->AddEntry(d2,"DLy");
  tle->AddEntry(d3,"DLz");
  tle->AddEntry(dr,"DL");
  tle->SetFillStyle(0);
  tle->Draw();
  c2.Update();
  c2.Print((figdir+lcfig+"_xyz.eps").c_str());
  c2.Clear();
  
  TMultiGraph *gmd=new TMultiGraph();
  ga->SetLineColor(kRed);
  ga->SetLineStyle(2);
  gd->SetLineColor(kBlue);
  gd->SetLineStyle(2);
  g5->SetLineColor(kRed);
  g6->SetLineColor(kBlue);
  gmd->Add(ga);
  gmd->Add(gd);
  gmd->Add(g5);
  gmd->Add(g6);
  gmd->SetTitle("Cumulative Lalpha(delta) of stars(black hole) vs time");
  gmd->Draw(drawoption.c_str());
  TLegend *tled=new TLegend(0.57,0.75,0.9,0.9);
  tled->AddEntry(g5,"Cumulative change of Lalpha for all ejected stars");
  tled->AddEntry(g6,"Cumulative change of Ldelta for all ejected stars");
  tled->AddEntry(ga,"Lalpha of one black hole (999999)");
  tled->AddEntry(gd,"Ldelta of one black hole (999999)");
  tled->SetFillStyle(0);
  tled->Draw();
  c2.Update();
  c2.Print((figdir+lcfig+"_angle.eps").c_str());
}  

//Draw BH Lx,Ly,Lz==================================//
void drawBHL(TFile *f, TTree *bh, Double_t bhmass[2],TCanvas *c1, string figdir)
{
  f->cd();
  stringstream sstr;
  string bh1m, bh2m;
  sstr.str("");
  sstr.clear();
  sstr<<bhmass[0];
  sstr>>bh1m;
  sstr.str("");
  sstr.clear();
  sstr<<bhmass[1];
  sstr>>bh2m;
  Int_t num=bh->Draw("log10(abs(Lx)):time_cur","","goff");
  Double_t *y=bh->GetV1();
  Double_t *x=bh->GetV2();
  TGraph *tx=new TGraph(num,x,y);
  num=bh->Draw("log10(abs(Ly)):time_cur","","goff");
  y=bh->GetV1();
  x=bh->GetV2();
  TGraph *ty=new TGraph(num,x,y);
  num=bh->Draw("log10(abs(Lz)):time_cur","","goff");
  y=bh->GetV1();
  x=bh->GetV2();
  TGraph *tz=new TGraph(num,x,y);
  TMultiGraph *tbhl=new TMultiGraph();
  tx->SetLineColor(kRed);
  ty->SetLineColor(kGreen);
  tz->SetLineColor(kBlack);
  tx->SetFillStyle(0);
  ty->SetFillStyle(0);
  tz->SetFillStyle(0);
  tbhl->Add(tx);
  tbhl->Add(ty);
  tbhl->Add(tz);
  tbhl->SetTitle(("M_{ BH1} = "+bh1m+" , M_{ BH2} = "+bh2m+";t;Log(L)").c_str());
  TLegend *tlll=new TLegend(0.75,0.76,0.9,0.9);
  tlll->AddEntry(tx,"Log(L_{ x})");
  tlll->AddEntry(ty,"Log(L_{ y})");
  tlll->AddEntry(tz,"Log(L_{ z})");
  tlll->SetFillStyle(0);
  c1->cd();
  c1->Clear();
  tbhl->Draw("AL");
  gPad->Modified();
  tbhl->GetXaxis()->SetLimits(0,150);
  tbhl->SetMinimum(-10.0);
  tbhl->SetMaximum(-1.0);
  //c1->BuildLegend();
  tlll->Draw();
  c1->Print((figdir+"BH_Lxyz.eps").c_str());
  c1->Print((figdir+"BH_Lxyz.png").c_str());
}
//Main function=====================================//

int main(int argc,char* argv[])
{
  string rootname,figdir,selstartree,destartree,defig,etfig,liofig,ldfig,lcfig,Etreename;
  Int_t detsplit;
  Double_t bhmass[2],critde;
  stringstream namestr;
  string checksh;
  char inflagc='y';
  bool inflag=1;
  namestr.str("");
  namestr.clear();

  switch (argc)
  {
  case 1:
    cout<<"Load last input(y/n)?";
    cin>>inflagc;
    if (inflagc=='n')
      inflag=0;
    if (inflag)
    {
      ifstream configf(".drawdEgraph.conf");
      if (!configf.is_open())
        cout<<"No config file"<<endl;
      else
      {
        configf>>rootname;
        configf>>figdir;
        configf>>selstartree;
        configf>>destartree;
        configf>>defig;
        configf>>etfig;
        configf>>liofig;
        configf>>ldfig;
        configf>>lcfig;
        configf>>detsplit;
        configf>>bhmass[0];
        configf>>bhmass[1];
        configf>>Etreename;
        configf>>critde;
        configf.close();
      }
    }
    
    //input=============================================//
    cout<<"root name("<<rootname<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input root name(no suffix):";
      cin>>rootname;
    }
    cout<<"figure directory("<<figdir<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input figure directory(need '/' at end):";
      cin>>figdir;
    }
    cout<<"Selected star data tree name("<<selstartree<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Selstar Tree name:";
      cin>>selstartree;
    }
    cout<<"Selected star dE/t data tree name("<<destartree<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"destar Tree name:";
      cin>>destartree;
    }
    cout<<"dE vs T figure name("<<defig<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input dE.T figure name(no .eps, same for all figures):";
      cin>>defig;
    }
    cout<<"E vs T figure name("<<etfig<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input ET figure name:";
      cin>>etfig;
    }
    cout<<"L out/L in figure name("<<liofig<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Input Lo/i figure name:";
      cin>>liofig;
    }
    cout<<"L distribution figure name("<<ldfig<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"L dist figure name:";
      cin>>ldfig;
    }
    cout<<"Cumulative L figure name("<<lcfig<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Lc figure name:";
      cin>>lcfig;
    }
    cout<<"dEt file splited number(if 1, no split)("<<detsplit<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"dEt splited number:";
      cin>>detsplit;
    }
    cout<<"BH mass 1/2("<<bhmass[0]<<","<<bhmass[1]<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"BH mass 1:";
      cin>>bhmass[0];
      cout<<"BH mass 2:";
      cin>>bhmass[1];
    }
    cout<<"Etree(E****to****) name:("<<Etreename<<")('y'/n):";
    cin>>inflagc;
    if (inflagc=='n')
    {
      cout<<"Etreename:";
      cin>>Etreename;
    }
    cout<<"log(-dE/E_start) Criterion for select stars:("<<critde<<")('y'/n):";
    cin>>critde;
    if (inflagc=='n')
    {
      cout<<"Criterion:";
      cin>>critde;
    }
    break;
  case 2:
    namestr.str("");
    namestr.clear();
    namestr<<argv[1];
    namestr>>checksh;
    if (checksh=="-l")
    {
      ifstream configf(".drawdEgraph.conf");
      if (!configf.is_open())
        cout<<"No config file"<<endl;
      else
      {
        configf>>rootname;
        configf>>figdir;
        configf>>selstartree;
        configf>>destartree;
        configf>>defig;
        configf>>etfig;
        configf>>liofig;
        configf>>ldfig;
        configf>>lcfig;
        configf>>detsplit;
        configf>>bhmass[0];
        configf>>bhmass[1];
        configf>>Etreename;
        configf>>critde;
        configf.close();
      }
    }
    else
    {
      cout<<"input incomplete"<<endl;
      return 0;
    }
    break;
  case 15:
    namestr.str("");
    namestr.clear();
    namestr<<argv[1];
    namestr>>rootname;
    namestr.str("");
    namestr.clear();
    namestr<<argv[2];
    namestr>>figdir;
    namestr.str("");
    namestr.clear();
    namestr<<argv[3];
    namestr>>selstartree;
    namestr.str("");
    namestr.clear();
    namestr<<argv[4];
    namestr>>destartree;
    namestr.str("");
    namestr.clear();
    namestr<<argv[5];
    namestr>>defig;
    namestr.str("");
    namestr.clear();
    namestr<<argv[6];
    namestr>>etfig;
    namestr.str("");
    namestr.clear();
    namestr<<argv[7];
    namestr>>liofig;
    namestr.str("");
    namestr.clear();
    namestr<<argv[8];
    namestr>>ldfig;
    namestr.str("");
    namestr.clear();
    namestr<<argv[9];
    namestr>>lcfig;
    namestr.str("");
    namestr.clear();
    namestr<<argv[10];
    namestr>>detsplit;
    namestr.str("");
    namestr.clear();
    namestr<<argv[11];
    namestr>>bhmass[0];
    namestr.str("");
    namestr.clear();
    namestr<<argv[12];
    namestr>>bhmass[1];
    namestr.str("");
    namestr.clear();
    namestr<<argv[13];
    namestr>>Etreename;
    namestr.str("");
    namestr.clear();
    namestr<<argv[14];
    namestr>>critde;
    namestr.str("");
    namestr.clear();
    break;
  default:
    cout<<"input incomplete"<<endl;
    return 0;
    break;
  }

  ofstream outconf(".drawdEgraph.conf");
  outconf<<rootname<<endl;
  outconf<<figdir<<endl;
  outconf<<selstartree<<endl;
  outconf<<destartree<<endl;
  outconf<<defig<<endl;
  outconf<<etfig<<endl;
  outconf<<liofig<<endl;
  outconf<<ldfig<<endl;
  outconf<<lcfig<<endl;
  outconf<<detsplit<<endl;
  outconf<<bhmass[0]<<endl;
  outconf<<bhmass[1]<<endl;
  outconf<<Etreename<<endl;
  outconf<<critde<<endl;
  outconf.close();

  cout<<"rootname:"<<rootname<<",(split:"<<detsplit<<")\n";
  cout<<"selstartree:"<<selstartree<<";destartree"<<destartree<<endl;
  cout<<"figdir:"<<figdir<<endl;
  cout<<"dE vs T fig:"<<defig<<endl;
  cout<<"E vs T fig:"<<etfig<<endl;
  cout<<"L out/in fig:"<<liofig<<endl;
  cout<<"L dist fig:"<<ldfig<<endl;
  cout<<"L cum fig:"<<lcfig<<endl;
  cout<<"bhmass:"<<bhmass[0]<<","<<bhmass[1]<<endl;
  cout<<"Etreename:"<<Etreename<<endl;
  cout<<"Criterion:"<<critde<<endl;

  //Main process======================================//

  stringstream sstr;
  
  TFile *fr=new TFile((rootname+"-result.root").c_str(),"update");
  TFile *fb=new TFile((rootname+"-bhpar.root").c_str(),"update");
  TFile *fbh=new TFile((rootname+"-bh.root").c_str(),"update");
  TChain *fs=new TChain(destartree.c_str());
  fbh->cd();
  TTree *bh=(TTree*)gDirectory->Get("BH1");
  if (detsplit==1)
    fs->AddFile((rootname+"-result-dEt.root").c_str());
  else
    for (int i=0;i<detsplit;i++)
    {
      string index;
      sstr.str("");
      sstr.clear();
      sstr<<i;    
      sstr>>index;
      fs->AddFile((rootname+"-result-dEt-"+index+".root").c_str());
    }
  TCanvas c1;

  //Draw dEvsT bh=====================================//
  fb->cd();
  Double_t avee,aveovera;
  drawbhdE(fr,bhmass[0],bhmass[1],&avee,&aveovera);

  //Draw dEvsT star==================================//
  //Draw dL vs T and L out/in=========================//
  //Draw angle between Ls to lbh out/in===============//
  //Draw histogram of angle and time==================//
  //Draw histogram of theta vs phi====================//
  //drawstardE(fr,fs,figdir,liofig,avee,aveovera,bhmass,1);

  
  //Draw dEvsT all====================================//
  //  fr->cd();
  //  drawtotdE(fr,bhmass,figdir,defig);
  
  //Draw EvsT star====================================//
  //  drawstarEt(fr);
  //  c1.Clear();
  
  ////No use:Draw EvsT bh======================================//
  ////  fb->cd();
  ////  drawbhEt(fr,bhmass[0],bhmass[1]);
  
  //Draw EvsT all=====================================//
  //  fr->cd();
  //  drawbhstarE(fr);
  //  c1.Print((figdir+etfig+".eps").c_str());
  //  c1.Clear();

  //Draw L out/in ====================================//
  //  drawLoi(fr,fs,figdir,liofig);

  //Draw L distribution===============================//
  //Draw dE/Es vs. Es
  drawLdist(figdir,ldfig,bhmass,critde,Etreename);
  //drawLdist(figdir,ldfig,bhmass,critde,"E0000to0149");

  //Draw cumulative L of stars========================//
  // if (detsplit==1)
  //   drawLc(figdir,lcfig,selstartree);
  // else
  //   drawLc(figdir,lcfig,selstartree+"0");

  //Draw BH Lx,Ly,Lz vs. t in log=====================//
  //  drawBHL(fbh,bh,bhmass,&c1,figdir);
  
  cout<<"All finished"<<endl;
  return 0;
}
