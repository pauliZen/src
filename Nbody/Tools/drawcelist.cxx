#include <nbodycelist.h>
#include <nbodyvfit.h>
#include <uftools.h>
#include <initial.h>
#include <algorithm>
#include <cstring>
#include <omp.h>

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <iomanip>

#include "TTree.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TH2F.h"
#include "TEntryList.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TMath.h"
#include "TCut.h"

static nbodycelist tcl;
static pars_initial init(".drawcelist_config");
static std::map<Int_t, std::string> tlabel;
static TCut drawopt;
static nbodyvfit* vfit;

typedef void (*FitFill) (TF1 *nfit,const Int_t &id);

const double yoffset=1.2;
const double fontsize=0.04;

//Maxwell distribution==============================//
Double_t MBdist(Double_t *v, Double_t *par)
{
  Double_t vx=TMath::Power(v[0]/par[0],2);
  return par[1]*4*TMath::Power(1.0/TMath::Pi(),1.5)*vx/par[0]*TMath::Exp(-vx);
}

void MBFill(TF1 *nfit,const Int_t &id)
{
  vfit->chi2=nfit->GetChisquare();
  vfit->vcut=0;
  vfit->vcerr=0;
  vfit->vmax=nfit->GetParameter(0);
  vfit->vmerr=nfit->GetParError(0);
  vfit->vsigma=0;
  vfit->vserr=0;
  vfit->h=nfit->GetParameter(1);
  vfit->herr=nfit->GetParError(1);
  vfit->type=id;
  vfit->Fill();
}

//Shift velocity Maxwell distribution===============//
Double_t MBdistEx(Double_t *v, Double_t *par)
{
  Double_t vx=TMath::Power((v[0]-par[0])/par[1],2);
  if (v[0]<par[0]) return 0;
  else return par[2]*4*TMath::Power(1.0/TMath::Pi(),1.5)*vx/par[1]*TMath::Exp(-vx);
}

void MBExFill(TF1 *nfit,const Int_t &id)
{
  vfit->chi2=nfit->GetChisquare();
  vfit->vcut=nfit->GetParameter(0);
  vfit->vcerr=nfit->GetParError(0);
  vfit->vmax=nfit->GetParameter(1);
  vfit->vmerr=nfit->GetParError(1);
  vfit->vsigma=0;
  vfit->vserr=0;
  vfit->h=nfit->GetParameter(2);
  vfit->herr=nfit->GetParError(2);
  vfit->type=id;
  vfit->Fill();
}

//Linear distribution===============================//
Double_t Lineardist(Double_t *v, Double_t *par)
{
  return par[1]*v[0]+par[0];
}

void LinearFill(TF1 *nfit, const Int_t &id)
{
  vfit->chi2=nfit->GetChisquare();
  vfit->vcut=0;
  vfit->vcerr=0;
  vfit->vmax=0;
  vfit->vmerr=0;
  vfit->vsigma=nfit->GetParameter(0);
  vfit->vserr=nfit->GetParError(0);
  vfit->h=nfit->GetParameter(1);
  vfit->herr=nfit->GetParError(1);
  vfit->type=id;
  vfit->Fill();
}

//Gaussian distribution=============================//
Double_t Gausdist(Double_t *v, Double_t *par)
{
  return par[2]*TMath::Gaus(v[0],par[0],par[1]);
}

void GausFill(TF1 *nfit, const Int_t &id)
{
  vfit->chi2=nfit->GetChisquare();
  vfit->vcut=0;
  vfit->vcerr=0;
  vfit->vmax=nfit->GetParameter(0);
  vfit->vmerr=nfit->GetParError(0);
  vfit->vsigma=nfit->GetParameter(1);
  vfit->vserr=nfit->GetParError(1);
  vfit->h=nfit->GetParameter(2);
  vfit->h=nfit->GetParError(2);
  vfit->type=id;
  vfit->Fill();
}
  
template <typename T>
void draw_dist_fun(Float_t *plegend, Int_t bins, Float_t xmin, Float_t xmax, Float_t ymin, Float_t ymax, T &d,  TBranch *t_b, std::string xtitle, std::string ytitle, std::string title, Int_t eventlimit=0, std::string exdrawopt="", std::string foldername="", bool fit_flag=0, std::string fittreename="", bool logx=0, bool logy=0, std::string fitmethod="maxf", FitFill vfitfun=0)
{
  if (foldername=="") foldername=xtitle;
  TCut opt2=exdrawopt.c_str();
  TLegend *tl=new TLegend(plegend[0],plegend[1],plegend[2],plegend[3]);
  tl->SetFillColor(0);
  tl->SetLineColor(0);
  TH1F **tf=new TH1F*[15];
  //for fit===========================================//
  TF1 **fit=new TF1*[15];
  if (fit_flag&&vfit==0) vfit=new nbodyvfit(fittreename,init.gets("fitroot"),0);
  else if (fit_flag) vfit->Switch(fittreename);
  //==================================================//
  TCanvas c1("c1","c1");
  tcl.Draw(">>tlist",drawopt&&opt2,"entrylist");
  TEntryList *tel=(TEntryList*)gDirectory->Get("tlist");
  tcl.fchain->SetEntryList(tel);
  int ntot=tel->GetN();
  for (Int_t i=0;i<15;i++)
  {
    Int_t id=i+1;
    std::string si=to<std::string>(id);
    if (tcl.GetEntries(("type=="+si).c_str()&&drawopt&&opt2)<=eventlimit)
    {
      tf[i]=0;
      continue;
    }
    tf[i]=new TH1F((foldername+si).c_str(),(title+si).c_str(),bins,xmin,xmax);
    tf[i]->SetXTitle(xtitle.c_str());
    tf[i]->SetYTitle(ytitle.c_str());
    tf[i]->GetYaxis()->SetTitleOffset(yoffset);
    tf[i]->GetXaxis()->SetTitleSize(fontsize);
    tf[i]->GetYaxis()->SetTitleSize(fontsize);
    tf[i]->GetXaxis()->SetLabelSize(fontsize);
    tf[i]->GetYaxis()->SetLabelSize(fontsize);
    tf[i]->SetLineColor(id%10?id:id+10);
    tf[i]->SetTitle("");
    tf[i]->SetStats(0);
    tf[i]->SetMinimum(ymin);
    if (ymax) tf[i]->SetMaximum(ymax);
    tl->AddEntry(tf[i],tlabel[id].c_str());
  }
  for (int j=0; j<ntot; j++)
  {
    Int_t tentry=tcl.GetListEntry(j,tel);
    //    t_b->GetEntry(tentry+tcl.fchain->GetTreeOffset()[treenum]);
    //    tcl.b_type->GetEntry(tentry+tcl.fchain->GetTreeOffset()[treenum]);
    tcl.GetEntry(tentry);
    if (tcl.type>15) continue;
    if (!tf[tcl.type-1]) continue;
    if (logx) tf[tcl.type-1]->Fill(log10(d));
    else tf[tcl.type-1]->Fill(d);
  }
#ifdef DEBUG
  std::cout<<"Before draw\n";
#endif  
  for (Int_t i=0;i<15;i++)
  {
    if (!tf[i]) continue;
    if (fit_flag)
    {
      Int_t id=i+1;
      tf[i]->Fit(fitmethod.c_str(),"R0");
      fit[i]=tf[i]->GetFunction(fitmethod.c_str());
      Int_t treenum=0;
      Int_t tentry=tel->GetEntryAndTree(0,treenum);
      vfit->LoadData(tcl,tentry+tcl.fchain->GetTreeOffset()[treenum]);
      vfitfun(fit[i],id);
      fit[i]->SetLineColor(id%10?id:id+10);
      fit[i]->SetLineStyle(2);
      tl->AddEntry(fit[i],(tlabel[id]+" fit").c_str());
    }
    if (i==0) tf[0]->Draw();
    else tf[i]->Draw("same");
    if (fit_flag) fit[i]->Draw("same");
  }
#ifdef DEBUG
  std::cout<<"After draw\n";
#endif  
  if (fit_flag)
  {
    vfit->Write("",TObject::kOverwrite);
  }
  tl->Draw();
  if(mkpath((init.gets("figdir")+foldername+"/").c_str(),0777)==-1)
  {
    std::cerr<<"Eroor: "<<strerror(errno)<<std::endl;
    exit(1);
  }
  if (logy)
  {
    c1.SetLogy();
    c1.Update();
  }
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"_"+foldername+".eps").c_str());
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"_"+foldername+".pdf").c_str());
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"_"+foldername+".png").c_str());
  tcl.fchain->SetEntryList(0);
  delete tel;
#ifdef DEBUG
  std::cout<<"Finish draw\n";
#endif  
}

template <typename T, typename M>
void draw_vs_fun(Float_t *plegend, Float_t xmin, Float_t xmax, Float_t ymin, Float_t ymax, Float_t marksize, T &dx, M &dy, TBranch *t_bx, TBranch *t_by, std::string xtitle, std::string ytitle, std::string title, std::string exdrawopt="", std::string foldername="", Int_t point_count=1, bool drawave=1, Int_t abin=20)
{
#ifdef DEBUG
  std::cout<<"before initial\n";
#endif  
  TGraph **tf=new TGraph*[15];
  TGraph **tg=new TGraph*[15];
  TMultiGraph *tm=new TMultiGraph();
  tm->SetTitle((title+";"+xtitle+";"+ytitle).c_str());
  TCut opt2=exdrawopt.c_str();
  TLegend *tl=new TLegend(plegend[0],plegend[1],plegend[2],plegend[3]);
  TCanvas c1("c1","c1");
  if (foldername=="") foldername=xtitle+"_"+ytitle;
  tl->SetFillColor(0);
  tl->SetLineColor(0);
  tcl.Draw(">>tlist",drawopt&&opt2,"entrylist");
  TEntryList *tel=(TEntryList*)gDirectory->Get("tlist");
  int ntot=tel->GetN();
  tcl.fchain->SetEntryList(tel);
#ifdef DEBUG
  std::cout<<"after initial\n";
#endif  
  for (Int_t i=0;i<15;i++)
  {
    Int_t id=i+1;
    std::string si=to<std::string>(id);
    Int_t tn=tcl.GetEntries(("type=="+si).c_str()&&drawopt&&opt2);
    if(tn==0)
    {
      tf[i]=0;
      continue;
    }
    //    tf[i]=new TH2F((foldername+si).c_str(),(title+si).c_str(),xbins,xmin,xmax,ybins,ymin,ymax);
    tf[i]=new TGraph(tn/point_count+1);
    //    tf[i]=new TGraph(tn);
    Int_t colorid=id%10?id:id+10;
    //    tf[i]->SetXTitle(xtitle.c_str());
    //    tf[i]->SetYTitle(ytitle.c_str());
    tf[i]->SetLineColor(colorid);
    tf[i]->SetFillColor(0);
    tf[i]->SetMarkerColor(colorid);
    //    tf[i]->SetMarkerStyle(colorid);
    //    tf[i]->SetMarkerSize(marksize);
    tf[i]->SetMaximum(ymax);
    //    tf[i]->SetTitle("");
    //    tf[i]->SetStats(0);
    if(!drawave) tl->AddEntry(tf[i],tlabel[id].c_str());
  }
  Double_t **tgx=new Double_t*[15];
  Double_t **tgy=new Double_t*[15];
  Int_t **tgc=new Int_t*[15];
  Int_t *tc=new Int_t[15];
  Double_t interval=0;
#ifdef DEBUG
  std::cout<<"after array\n";
#endif  
  if (drawave)
  {
    interval=(xmax-xmin)/abin;
    Double_t hi=interval*0.5;
    for (int j=0;j<15;j++)
    {
      if (!tf[j]) continue;
      tgx[j]=new Double_t[abin];
      tgy[j]=new Double_t[abin];
      tgc[j]=new Int_t[abin];
      tc[j]=0;
      for (int i=0;i<abin;i++)
      {
        tgx[j][i]=interval*i+hi+xmin;
        tgy[j][i]=0;
        tgc[j][i]=0;
      }
    }
  }
#ifdef DEBUG
  std::cout<<"before get data\n";
  std::cout<<"The total encounters:"<<ntot<<std::endl;
#endif  
  for (int j=0; j<ntot; j++)
  {
    Int_t tentry=tcl.GetListEntry(j,tel);
    //    t_bx->GetEntry(tentry+tcl.fchain->GetTreeOffset()[treenum]);
    //    t_by->GetEntry(tentry+tcl.fchain->GetTreeOffset()[treenum]);
    //    tcl.b_type->GetEntry(tentry+tcl.fchain->GetTreeOffset()[treenum]);
    tcl.GetEntry(tentry);
    if (tcl.type>15) continue;
    if (dy!=dy) continue;
    if ((-dy)!=(-dy)) continue;
#ifdef DEBUG
    if (!tf[tcl.type-1]) std::cout<<"Error: "<<tcl.type-1<<" "<<tentry<<std::endl;
    //  std::cout<<"t="<<tcl.type-1<<" dx="<<dx<<" dy="<<dy<<"\t";
#endif
    if (j%point_count==0)
    {
      tc[tcl.type-1]++;
      tf[tcl.type-1]->SetPoint(tc[tcl.type-1],dx,dy);
    }
    if (drawave)
    {
      Int_t index=(dx-xmin)/interval;
      if (index<0||index>=abin) continue;
      tgy[tcl.type-1][index] +=dy;
      tgc[tcl.type-1][index]++;
    }
  }
#ifdef DEBUG
  std::cout<<"Before draw\n";
#endif  
  for (Int_t j=0;j<15;j++)
  {
    if (!tf[j]) continue;
    tm->Add(tf[j]);
  }
  if (drawave)
    for (Int_t j=0;j<15;j++)
    {
      if (!tf[j]) continue;
      Int_t id=j+1;
      Int_t colorid=id%10?id:id+10;
      Int_t tabin=abin;
      for (int i=0;i<tabin;i++)
      {
        if (tgc[j][i])
          tgy[j][i]=tgy[j][i]/tgc[j][i];
        else
        {
          tabin--;
          i--;
        }
      }
#ifdef DEBUG
      for (int i=0;i<tabin;i++) std::cout<<"\tType: "<<j<<"\tbin: "<<i<<"\tvalue: "<<tgy[j][i];
      std::cout<<std::endl;
#endif      
      tg[j]=new TGraph(tabin,tgx[j],tgy[j]);
      tg[j]->SetLineColor(colorid);
      tg[j]->SetFillColor(0);
      tg[j]->SetMarkerStyle(j+20);
      tg[j]->SetMarkerColor(colorid);
      tg[j]->SetMarkerSize(1);
      tl->AddEntry(tg[j],tlabel[id].c_str());
      tm->Add(tg[j]);
    }
  tm->Draw("AP");
  tl->Draw();
  gPad->Modified();
  tm->GetXaxis()->SetLimits(xmin,xmax);
  tm->GetYaxis()->SetTitleOffset(yoffset);
  tm->GetXaxis()->SetTitleSize(fontsize);
  tm->GetYaxis()->SetTitleSize(fontsize);
  tm->GetXaxis()->SetLabelSize(fontsize);
  tm->GetYaxis()->SetLabelSize(fontsize);
  tm->SetMaximum(ymax);
  tm->SetMinimum(ymin);

#ifdef DEBUG
  std::cout<<"After draw\n";
#endif  
  if(mkpath((init.gets("figdir")+foldername+"/").c_str(),0777)==-1)
  {
    std::cerr<<"Eroor: "<<strerror(errno)<<std::endl;
    exit(1);
  }
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"_"+foldername+".eps").c_str());
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"_"+foldername+".pdf").c_str());
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"_"+foldername+".png").c_str());
  tcl.fchain->SetEntryList(0);
  delete tel;
}

void draw_hist_count(Float_t *plegend, std::string foldername="")
{
  if (foldername=="") foldername="counts";
  if(mkpath((init.gets("figdir")+foldername+"/").c_str(),0777)==-1)
  {
    std::cerr<<"Eroor: "<<strerror(errno)<<std::endl;
    exit(1);
  }
  tcl.Draw(">>tlist",drawopt,"entrylist");
  TEntryList *tel=(TEntryList*)gDirectory->Get("tlist");
  tcl.fchain->SetEntryList(tel);
  Int_t ntot=tel->GetN();
  Int_t treenum=0;
  Int_t tentry=tel->GetEntryAndTree(0,treenum);
  tcl.GetEntry(tentry+tcl.fchain->GetTreeOffset()[treenum]);
  Int_t ns=tcl.ns+tcl.nb;
  Int_t np=tcl.np;
  //  Int_t n=ns+np;
  //  Int_t cnt=10*n+1;
  Int_t cnst=10*ns;
  Int_t cnpt=10*np;
  //  Int_t **counts=new Int_t*[15];
  Int_t **scount=new Int_t*[3];  //Type 1,2,4,
  Int_t **pcount=new Int_t*[3];  //Type 2,3,6
  Int_t **bcount=new Int_t*[3];  //Type 4,6,10
  Int_t *stot=new Int_t[3];
  Int_t *ptot=new Int_t[3];
  Int_t *btot=new Int_t[3];
  Int_t *smax=new Int_t[3];  //Maximum encounter counts per star
  Int_t *pmax=new Int_t[3];
  Int_t *bmax=new Int_t[3];
  Int_t **sfrac=new Int_t*[3];
  Int_t **pfrac=new Int_t*[3];
  Int_t **bfrac=new Int_t*[3];
  for (int i=0;i<3;i++) {
    stot[i]=0;
    ptot[i]=0;
    btot[i]=0;
    smax[i]=0;
    pmax[i]=0;
    bmax[i]=0;
    sfrac[i]=new Int_t[11];
    pfrac[i]=new Int_t[11];
    bfrac[i]=new Int_t[11];
    memset(sfrac[i],0,sizeof(Int_t)*11);
    memset(pfrac[i],0,sizeof(Int_t)*11);
    memset(bfrac[i],0,sizeof(Int_t)*11);
    //    counts[i]=new Int_t[cnt];
    pcount[i]=new Int_t[cnpt+1];
    scount[i]=new Int_t[cnst+1];
    bcount[i]=new Int_t[cnst+1];
    if (!scount[i]){
      std::cerr<<"Error: scount memory alloc fail!\n";
      exit(1);
    }
    if (!pcount[i]){
      std::cerr<<"Error: pcount memory alloc fail!\n";
      exit(1);
    }
    if (!bcount[i]){
      std::cerr<<"Error: counts memory alloc fail!\n";
      exit(1);
    }
    //    memset(counts[i],0,sizeof(Int_t)*cnt);
    memset(pcount[i],0,sizeof(Int_t)*cnpt+1);
    memset(scount[i],0,sizeof(Int_t)*cnst+1);
    memset(bcount[i],0,sizeof(Int_t)*cnst+1);
  }
  Int_t model=0;
  Int_t tmod=0;
  tmod=tcl.model;
  for (Int_t i=0;i<ntot;i++)
  {
    Int_t tnow=tcl.GetListEntry(i,tel);
    tcl.GetEntry(tnow);
    //    tcl.b_model->GetEntry(tnow);
    if (tcl.model!=tmod) {
      tmod=tcl.model;
      model++;
    }
    if (model>=10) {
      std::cerr<<"Error: model >10 (i="<<tnow<<")\n";
      exit(1);
    }
    //    tcl.b_type->GetEntry(tnow);
    //    tcl.b_name->GetEntry(tnow);
    Int_t type=tcl.type;
    switch (type) {
    case 1:  //S-S
      scount[0][model*ns+tcl.name[0]]++;
      scount[0][model*ns+tcl.name[1]]++;
      smax[0]=std::max(scount[0][model*ns+tcl.name[0]],smax[0]);
      smax[0]=std::max(scount[0][model*ns+tcl.name[1]],smax[0]);
      stot[0] +=2;
      break;
    case 2:  //S-P
      for (int i=0;i<2;i++) {
        if(tcl.name[i]<=ns) {
          stot[1]++;
          scount[1][model*ns+tcl.name[i]]++;
          smax[1]=std::max(scount[1][model*ns+tcl.name[i]],smax[1]);
        }
        else {
          ptot[0]++;
          pcount[0][model*np+tcl.name[i]-ns]++;
          pmax[0]=std::max(pcount[0][model*np+tcl.name[i]-ns],pmax[0]);
        }
      }
      break;
    case 3:  //P-P
      pcount[1][model*np+tcl.name[0]-ns]++;
      pcount[1][model*np+tcl.name[1]-ns]++;
      pmax[1]=std::max(pcount[1][model*np+tcl.name[0]-ns],pmax[1]);
      pmax[1]=std::max(pcount[1][model*np+tcl.name[1]-ns],pmax[1]);
      ptot[1] +=2;
      break;
    case 4:  //SS-S
      scount[2][model*ns+tcl.name[0]]++;
      smax[2]=std::max(scount[2][model*ns+tcl.name[0]],smax[2]);
      stot[2]++;
      bcount[0][model*ns+tcl.name[1]]++;
      bmax[0]=std::max(bcount[0][model*ns+tcl.name[1]],bmax[0]);
      bcount[0][model*ns+tcl.name[2]]++;
      bmax[0]=std::max(bcount[0][model*ns+tcl.name[2]],bmax[0]);
      btot[0] +=2;
      break;
    case 6: //SS-P
      pcount[2][model*np+tcl.name[0]-ns]++;
      pmax[2]=std::max(pcount[2][model*np+tcl.name[0]-ns],pmax[2]);
      ptot[2]++;
      bcount[1][model*ns+tcl.name[1]]++;
      bmax[1]=std::max(bcount[1][model*ns+tcl.name[1]],bmax[1]);
      bcount[1][model*ns+tcl.name[2]]++;
      bmax[1]=std::max(bcount[1][model*ns+tcl.name[2]],bmax[1]);
      btot[1] +=2;
      break;
    case 10: //SS-SS
      bcount[2][model*ns+tcl.name[0]]++;
      bmax[2]=std::max(bcount[2][model*ns+tcl.name[0]],bmax[2]);
      bcount[2][model*ns+tcl.name[1]]++;
      bmax[2]=std::max(bcount[2][model*ns+tcl.name[1]],bmax[2]);
      bcount[2][model*ns+tcl.name[2]]++;
      bmax[2]=std::max(bcount[2][model*ns+tcl.name[2]],bmax[2]);
      bcount[2][model*ns+tcl.name[3]]++;
      bmax[2]=std::max(bcount[2][model*ns+tcl.name[3]],bmax[2]);
      btot[2] +=4;
    default:
      continue;
      break;
    }
  }
  if (model<9) {
    std::cout<<"Model number less than 10, Nmodel= "<<model+1<<std::endl;
    //    cnt=(model+1)*n;
    cnst=(model+1)*ns;
    cnpt=(model+1)*np;
  }
  //--05/09/14 22:50--------------------------------------//
  /*1. Fraction of P with no encounter at all
    2. Fraction of P with 0 encounters with a massive body
    3. Fraction of S with no encounter at all
    4. Fraction of S with 0 encounters with a massive body
    5. Fraction of S with 0 encounters with a planet  
  1. The encounters experienced by P. That is 2xP-P, 1xP-S, 1xP-B
  2. The encounters experienced by S. That is 2xS-S, 1xS-P, 1xS-B
  3. The encounters experienced by B. That is 2xB-B, 1xB-S, 1xB-P*/

  //  Int_t *nzero=new Int_t[5];
  // Int_t **pfrac0=new Int_t*[2];
  // Int_t **sfrac0=new Int_t*[3];
  // pfrac0[0]=new Int_t[cnpt];
  // pfrac0[1]=new Int_t[cnpt];
  // sfrac0[0]=new Int_t[cnst];
  // sfrac0[1]=new Int_t[cnst];
  // memset(pfrac0[0],0,sizeof(Int_t)*cnpt);
  // memset(pfrac0[1],0,sizeof(Int_t)*cnpt);
  // memset(sfrac0[0],0,sizeof(Int_t)*cnst);
  // memset(sfrac0[1],0,sizeof(Int_t)*cnst);
// #pragma omp parallel for
//   for(int i=0;i<15;i++){
    // for(int j=0;j<10;j++){
    //   memcpy(&scount[i][j*ns],&counts[i][j*n+1],sizeof(Int_t)*ns);
    //   memcpy(&pcount[i][j*np],&counts[i][j*n+ns+1],sizeof(Int_t)*np);
    // }
    // for(int j=0;j<cnpt;j++) pfrac0[0][j] +=pcount[i][j];
    // if(i==1||i==5||i==6) for(int j=0;j<cnpt;j++) pfrac0[1][j] +=pcount[i][j];
    // for(int j=0;j<cnst;j++) sfrac0[0][j] +=scount[i][j];
    // if(i==0||i==3||i==4) for(int j=0;j<cnst;j++) sfrac0[1][j] +=scount[i][j];
    // std::sort(scount[i],&scount[i][cnst]);
    // std::sort(pcount[i],&pcount[i][cnpt]);
  // }
  // sfrac0[2]=scount[1];
  // std::sort(pfrac[0],&pfrac[0][cnpt]);
  // std::sort(pfrac[1],&pfrac[1][cnpt]);
  // std::sort(sfrac[0],&sfrac[0][cnst]);
  // std::sort(sfrac[1],&sfrac[1][cnst]);
  Int_t **tscount=new Int_t*[3];
  Int_t **tpcount=new Int_t*[3];
  Int_t **tbcount=new Int_t*[3];
  for (int i=0;i<3;i++){
    tscount[i]=new Int_t[smax[i]+1];
    tpcount[i]=new Int_t[pmax[i]+1];
    tbcount[i]=new Int_t[bmax[i]+1];
    memset(tscount[i],0,sizeof(Int_t)*(smax[i]+1));
    memset(tpcount[i],0,sizeof(Int_t)*(pmax[i]+1));
    memset(tbcount[i],0,sizeof(Int_t)*(bmax[i]+1));
    for (int j=1;j<=cnst;j++){
      tscount[i][scount[i][j]]++;
    }
    for (int j=1;j<=cnpt;j++){
      tpcount[i][pcount[i][j]]++;
    }
    for (int j=1;j<=cnst;j++){
      tbcount[i][bcount[i][j]]++;
    }
  }
  Int_t csfrac0[3][2]={},cpfrac0[2][2]={};
  Int_t **csfrp0=new Int_t*[3];
  Int_t **cpfrp0=new Int_t*[2];
  for(int i=0;i<3;i++) {
    csfrp0[i]=new Int_t[model+1];
    memset(csfrp0[i],0,sizeof(Int_t)*(model+1));
  }
  for(int i=0;i<2;i++) {
    cpfrp0[i]=new Int_t[model+1];
    memset(cpfrp0[i],0,sizeof(Int_t)*(model+1));
  }
  for (int i=0;i<model+1;i++){
    for (int j=i*ns+1;j<=(i+1)*ns;j++) {
      if(scount[0][j]==0&&scount[1][j]==0&&scount[2][j]==0) csfrp0[0][i]++;
      if(scount[0][j]==0&&scount[2][j]==0) csfrp0[1][i]++;
      if(scount[1][j]==0) csfrp0[2][i]++;
    }
    for (int j=0;j<3;j++) csfrac0[j][0] +=csfrp0[j][i];
    for (int j=i*np+1;j<=(i+1)*np;j++) {
      if(pcount[0][j]==0&&pcount[1][j]==0&&pcount[2][j]==0) cpfrp0[0][i]++;
      if(pcount[0][j]==0&&pcount[2][j]==0) cpfrp0[1][i]++;
    }
    for(int j=0;j<2;j++) cpfrac0[j][0] +=cpfrp0[j][i];
  }
  for (int i=0;i<3;i++) {
    csfrac0[i][0] /=model+1;
    for (int j=0;j<model+1;j++){
      Int_t csdf=csfrp0[i][j]-csfrac0[i][0];
      csfrac0[i][1] += csdf*csdf;
    }
    csfrac0[i][1] /=model+1;
    csfrac0[i][1] = sqrt(csfrac0[i][1]);
  }
  for (int i=0;i<2;i++) {
    cpfrac0[i][0] /=model+1;
    for (int j=0;j<model+1;j++){
      Int_t csdf=cpfrp0[i][j]-cpfrac0[i][0];
      cpfrac0[i][1] += csdf*csdf;
    }
    cpfrac0[i][1] /=model+1;
    cpfrac0[i][1] = sqrt(cpfrac0[i][1]);
  }
    
  TCanvas c1("c1","c1");
  TH1I **th=new TH1I*[3];
  TH1I **thb=new TH1I*[3];
  TH1I **thp=new TH1I*[3];
  TLegend *tl=new TLegend(plegend[0],plegend[1],plegend[2],plegend[3]);
  TLegend *tlb=new TLegend(plegend[0],plegend[1],plegend[2],plegend[3]);
  TLegend *tlp=new TLegend(plegend[0],plegend[1],plegend[2],plegend[3]);
  std::string labels[3][3]={{"S-S","S-P","S-SS"},{"P-S","P-P","P-SS"},{"SS-S","SS-P","SS-SS"}};
  Double_t frac[12]={0.001, 0.021, 0.159, 0.5, 0.841, 0.9755, 0.998, 0.1, 0.25, 0.75, 0.9, 1.1};
  tl->SetFillStyle(0);
  tl->SetFillColor(0);
  tl->SetLineStyle(0);
  tl->SetLineColor(0);
  tl->SetShadowColor(0);
  tlb->SetFillStyle(0);
  tlb->SetFillColor(0);
  tlb->SetLineStyle(0);
  tlb->SetLineColor(0);
  tlb->SetShadowColor(0);
  tlp->SetFillStyle(0);
  tlp->SetFillColor(0);
  tlp->SetLineStyle(0);
  tlp->SetLineColor(0);
  tlp->SetShadowColor(0);
  bool drawp=true;
  bool drawb=true;
  //star==============================================//
  for (Int_t i=0;i<3;i++){
    if(smax[i]) {
      th[i]=new TH1I((labels[0][i]+"counts").c_str(),(labels[0][i]+"encounter counts per star").c_str(),160,0,160);
      Int_t jstot=smax[i]>160?160:smax[i];
      Int_t ccount=0;
      Int_t cpoint=0;
      Int_t nfrac[12];
      for (int j=0;j<12;j++) {
        nfrac[j]=stot[i]*frac[j];
      }
      for (Int_t j=0;j<=jstot;j++) {
        ccount +=j*tscount[i][j];
        if(ccount>=nfrac[cpoint]) {
          sfrac[i][cpoint]=j;
          if(cpoint<12) cpoint++;
          else {
            std::cerr<<"Error: scount ec number > total!\n";
            exit(1);
          }
        }
        th[i]->SetBinContent(j,tscount[i][j]/(model+1));
      }
#ifdef DEBUG
      printf("Type %d, stot %d, htot %d %d\n",i+1,stot[i],ccount,tscount[i][1]);
#endif      
      Int_t colorid=(i+1)%10?i+1:i+41;
      th[i]->SetLineColor(colorid);
      th[i]->SetFillColor(0);
      th[i]->SetTitle("");
      th[i]->SetYTitle("encounter number per star");
      th[i]->SetXTitle("number of stars");
      th[i]->GetYaxis()->SetTitleOffset(yoffset);
      th[i]->GetXaxis()->SetTitleSize(fontsize);
      th[i]->GetYaxis()->SetTitleSize(fontsize);
      th[i]->GetXaxis()->SetLabelSize(fontsize);
      th[i]->GetYaxis()->SetLabelSize(fontsize);
      th[i]->SetStats(0);
      th[i]->SetMaximum(10000);
      tl->AddEntry(th[i],labels[0][i].c_str());
      if(i) th[i]->Draw("same");
      else th[i]->Draw();
    }
  }
  tl->Draw();
  c1.SetLogy();
  c1.Update();
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"_"+foldername+".eps").c_str());
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"_"+foldername+".pdf").c_str());
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"_"+foldername+".png").c_str());
  c1.Clear();
  //binary============================================//
  for (Int_t i=0;i<3;i++){
    if(bmax[i]){
      thb[i]=new TH1I((labels[2][i]+"counts").c_str(),(labels[2][i]+"encounter counts per star").c_str(),160,0,160);
      Int_t jstot=bmax[i]>160?160:bmax[i];
      // Int_t ccount=0;
      // Int_t cpoint=0;
      // Int_t nfrac[12];
      // for (int j=0;j<12;j++) {
      //   nfrac[j]=stot[i]*frac[j];
      // }
      for (Int_t j=0;j<=jstot;j++) {
        // ccount +=j*tscount[i][j];
        // if(ccount>=nfrac[cpoint]) {
        //   sfrac[i][cpoint]=j;
        //   if(cpoint<12) cpoint++;
        //   else {
        //     std::cerr<<"Error: scount ec number > total!\n";
        //     exit(1);
        //   }
        // }
        thb[i]->SetBinContent(j,tscount[i][j]/(model+1)/2);
      }
#ifdef DEBUG
      //      printf("Type %d, stot %d, htot %d %d\n",i+1,stot[i],ccount,tscount[i][1]);
#endif      
      Int_t colorid=(i+1)%10?i+1:i+41;
      thb[i]->SetLineColor(colorid);
      thb[i]->SetFillColor(0);
      thb[i]->SetTitle("");
      thb[i]->SetYTitle("Events Number");
      thb[i]->SetXTitle("N_{c,b}[Counts/binary]");
      thb[i]->SetStats(0);
      thb[i]->SetMaximum(10000);
      tlb->AddEntry(thb[i],labels[2][i].c_str());
      if(drawb) {
        thb[i]->Draw();
        drawb=false;
      }
      else thb[i]->Draw("same");
    }
  }
  tlb->Draw();
  c1.SetLogy();
  c1.Update();
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"b_"+foldername+".eps").c_str());
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"b_"+foldername+".pdf").c_str());
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"b_"+foldername+".png").c_str());
  c1.Clear();
  //Planet============================================//
  for (Int_t i=0;i<3;i++) {
    if (pmax[i]) {
      thp[i]=new TH1I((labels[1][i]+"countsp").c_str(),(labels[1][i]+"encounter counts per planet").c_str(),160,0,160);
      Int_t jptot=pmax[i]>160?160:pmax[i];
      Int_t ccount=0;
      Int_t cpoint=0;
      Int_t nfrac[12];
      for (int j=0;j<12;j++) {
        nfrac[j]=ptot[i]*frac[j];
      }
      for (Int_t j=0;j<=jptot;j++) {
        ccount +=j*tpcount[i][j];
        if(ccount>=nfrac[cpoint]) {
          pfrac[i][cpoint]=j;
          if(cpoint<12) cpoint++;
          else {
            std::cerr<<"Error: pcount ec number > total!\n";
            exit(1);
          }
        }
        thp[i]->SetBinContent(j,tpcount[i][j]/(model+1));
      }
#ifdef DEBUG
      printf("Type %d, stot %d, htot %d %d\n",i+1,ptot[i],ccount,tpcount[i][1]);
#endif      
      Int_t colorid=(i+1)%10?i+1:i+11;
      thp[i]->SetLineColor(colorid);
      thp[i]->SetFillColor(0);
      //      thp[i]->SetLineStyle(2);
      thp[i]->SetTitle("");
      thp[i]->SetYTitle("encounter number per planet");
      thp[i]->SetXTitle("number of planets");
      thp[i]->GetYaxis()->SetTitleOffset(yoffset);
      thp[i]->GetXaxis()->SetTitleSize(fontsize);
      thp[i]->GetYaxis()->SetTitleSize(fontsize);
      thp[i]->GetXaxis()->SetLabelSize(fontsize);
      thp[i]->GetYaxis()->SetLabelSize(fontsize);
      thp[i]->SetStats(0);
      thp[i]->SetMaximum(10000);
      tlp->AddEntry(thp[i],labels[1][i].c_str());
      if(drawp) {
        thp[i]->Draw();
        drawp=false;
      }
      else thp[i]->Draw("same");
    }
  }
  tlp->Draw();
  c1.SetLogy();
  c1.Update();
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"p_"+foldername+".eps").c_str());
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"p_"+foldername+".pdf").c_str());
  c1.Print((init.gets("figdir")+foldername+"/"+init.gets("figname")+"p_"+foldername+".png").c_str());
  FILE *FOUT;
  if ( (FOUT = fopen("ceper_star.table","a+") )==NULL ) {
    fprintf(stderr,"Error: Cannot open input file!\n");
    return;
  }
  fprintf(FOUT,"%d %d %d %lf %d %d\n",tcl.ns,tcl.np,tcl.nb,tcl.rbar,tcl.m1,tcl.p1);
  fprintf(FOUT,"%d %d %d %d %d %d %d %d %d %d\n",csfrac0[0][0],csfrac0[0][1],csfrac0[1][0],csfrac0[1][1],csfrac0[2][0],csfrac0[2][1],cpfrac0[0][0],cpfrac0[0][1],cpfrac0[1][0],cpfrac0[1][1]);
  for (int j=0;j<3;j++) {
    fprintf(FOUT," %d",j+1);
    for (int i=0;i<11;i++) fprintf(FOUT," %d",sfrac[j][i]);
    fprintf(FOUT," ");
    for (int i=0;i<11;i++) fprintf(FOUT," %d",pfrac[j][i]);
    fprintf(FOUT,"\n");
  }
  fclose(FOUT);
  // for (int i=0;i<15;i++){
  //   std::cout<<tlabel[i+1]<<std::endl;
  //   for (int j=0;j<=counts[i][cnt-1];j++)
  //     if(tcount[i][j]) std::cout<<std::setw(6)<<j;
  //   std::cout<<std::endl;
  //   for (int j=0;j<=counts[i][cnt-1];j++)
  //     if(tcount[i][j]) std::cout<<std::setw(6)<<tcount[i][j];
  //   std::cout<<std::endl;
  // }
  tcl.fchain->SetEntryList(0);
  delete tel;
}

int main(int argc, char* argv[])
{
  init.add("flist","root file to chain","drawcelist.lst");
  init.add("figdir","directory path to store figures","./");
  init.add("figname","figname","fig_test");
  init.add("draw_bip_dist","impact parameter distribution",(bool)1);
  init.add("draw_peri_dist","peri-center distribution",(bool)1);
  init.add("draw_t_dist","encounter time distribution",(bool)1);
  init.add("draw_vinf_dist","imcoming velocity distribution",(bool)1);
  init.add("draw_vp_dist","peri-center velocity distribution",(bool)1);
  init.add("draw_a_e","semi-major-axis vs. eccentricity",(bool)1);
  init.add("draw_vp_p","peri-center velocity vs. peri-center",(bool)1);
  init.add("draw_vinf_b","Imcoming velocity vs. impact parameter",(bool)1);
  init.add("draw_hist_count","Histrogram of counts per star",(bool)1);
  init.add("draw_option","draw option","1");
  init.add("fitroot","root file name to store fit result","vfit.root");
  init.add("point_count","point to count for 2D graph",(int)100);
  init.initial(argc,argv);
  
  ifstream fl(init.gets("flist").c_str());
  if (!fl.is_open())
  {
    std::cerr<<"Error: No filelist found!\n";
    return 0;
  }

  tcl.LoadList(init.get<std::string>("flist"));

  tlabel[1]="S-S";
  tlabel[2]="S-P";
  tlabel[3]="P-P";
  tlabel[4]="SS-S";
  tlabel[5]="SP-S";
  tlabel[6]="SS-P";
  tlabel[7]="SP-P";
  tlabel[8]="PP-S";
  tlabel[9]="PP-P";
  tlabel[10]="SS-SS";
  tlabel[11]="SS-SP";
  tlabel[12]="SP-SP";
  tlabel[13]="SS-PP";
  tlabel[14]="SP-PP";
  tlabel[15]="PP-PP";

  drawopt=init.gets("draw_option").c_str();
  
  TF1 *mf=new TF1("maxf",MBdist,0,10,2);
  mf->SetParameters(2,100);

  TF1 *mfe=new TF1("maxfe",MBdistEx,0,10,3);
  mfe->SetParameters(3,100);
  mfe->SetParameters(1,1);
  mfe->SetParameters(2,2);
  mfe->SetParLimits(1,0,10);

  TF1 *lf=new TF1("linearf",Lineardist,100,1000,2);

  TF1 *gf=new TF1("Gausf",Gausdist,0,2.5,3);
  gf->SetParameters(3,1000);
  gf->SetParameters(1,1);
  gf->SetParLimits(1,0,4);
  // gf->SetParLimits(2,0,10);

  vfit=new nbodyvfit(init.gets("fitroot"),0);

  Float_t legend_lnf[4]={0.13,0.5,0.23,0.89};
  Float_t legend_rnf[4]={0.75,0.5,0.89,0.89};
  Float_t legend_rf[4]={0.79,0.49,0.89,0.89};
  if (init.getb("draw_bip_dist")) draw_dist_fun<Double_t>(legend_lnf,100,0,1000,0,0,tcl.bip[1],tcl.b_bip,"b [AU]","ecounter number","Impact parameter distribution",200,"","b",1,"bfit",0, 0,"linearf",LinearFill);
  if (init.getb("draw_peri_dist")) draw_dist_fun<Double_t>(legend_lnf,100,0,1000,0,0,tcl.peri[1],tcl.b_peri,"p [AU]","encounter number", "Periastron distribution",200,"","p",1,"pfit",0, 0,"linearf",LinearFill);
  if (init.getb("draw_t_dist")) draw_dist_fun<Double_t>(legend_rnf,100,0.1,2.5,0,7000,tcl.t[1],tcl.b_t,"log(t [Myr])","encounter number", "Encounter time distribution",20,"","t",1,"tfit",1,0,"Gausf",GausFill);
  if (init.getb("draw_vinf_dist")) draw_dist_fun<Double_t>(legend_rnf,100,0,10,0.5,0,tcl.vinf[1],tcl.b_vinf,"v_{#infty} (km/s)","encounter number","Imcoming velocity distribution",100,"vinf[1]<=10&&vinf[1]>=0","vinf",1,"vinffit",0, 1,"maxf",MBFill);
  if (init.getb("draw_vp_dist")) draw_dist_fun<Double_t>(legend_rnf,100,0,10,0.5,0,tcl.vp[1],tcl.b_vp,"v_{p} (km/s)","encounter number","Periastron velocity distribution",100,"vp[1]>=0&&vp[1]<=10","vp",1,"vpfit",0, 1,"maxfe",MBExFill);
  if (init.getb("draw_a_e")) draw_vs_fun<Double_t,Double_t>(legend_lnf,0,2,-10000,10000,0.1,tcl.ecc[1],tcl.semi[1],tcl.b_ecc,tcl.b_semi,"e","a(AU)","semi-major axis vs. eccentricity","semi[1]<10000&&semi[1]>-10000&&ecc[1]<2","a_e",init.geti("point_count"));
  if (init.getb("draw_vp_p")) draw_vs_fun<Double_t,Double_t>(legend_rf,0,1000,0,20,0.1,tcl.peri[1],tcl.vp[1],tcl.b_peri,tcl.b_vp,"p (AU)","v_{p} (km/s)","","vp[1]>0","vp_p",init.geti("point_count"));
  if (init.getb("draw_vinf_b")) draw_vs_fun<Double_t,Double_t>(legend_rf,0,1000,0,20,0.1,tcl.bip[1],tcl.vinf[1],tcl.b_bip,tcl.b_vinf,"b(AU)","v_{#infty} (km/s)","Imcoming velocity vs. impact parameter","","vinf_b",init.geti("point_count"));
  if (init.getb("draw_hist_count")) draw_hist_count(legend_rf);
  
  std::cout<<"All Finish\n";
  return 0;
}
