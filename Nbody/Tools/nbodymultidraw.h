#ifndef nbodymultidraw_h
#define nbodymultidraw_h

#ifdef DEBUG
#include <iostream>
#endif

#include <fstream>
#include <string>
#include <vector>
#include <TChain.h>
#include <TCanvas.h>
#include <TCut.h>
#include <TAxis.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <map>

static std::map<std::string, std::string> labelmap;

void labelinit(){
  labelmap["rbar"]="R_{vir}";
  labelmap["ns+nb"]="N_{s,b}";
  labelmap["ns"]="N_{s}";
  labelmap["np"]="N_{p}";
  labelmap["nb"]="N_{b}";
  labelmap["ns+nb+np"]="N_{s,b}+N_{p}";
  labelmap["m1+10*p1=11"]="M_{s}=1, E_{j}=D";
  labelmap["m1+10*p1=12"]="M_{s}=0.6, E_{j}=D";
  labelmap["m1+10*p1=22"]="M_{s}=0.6, E_{j}=P";
  labelmap["m1+10*p1=21"]="M_{s}=1, E_{j}=P";
  labelmap["m1+10*p1=0"]="Z";
  labelmap["type=1"]="S-S";
  labelmap["type=2"]="S-P";
  labelmap["type=3"]="P-P";
  labelmap["type=4"]="SS-S";
  labelmap["type=5"]="SP-S";
  labelmap["type=6"]="SS-P";
  labelmap["type=7"]="SP-P";
  labelmap["type=8"]="PP-S";
  labelmap["type=9"]="PP-P";
  labelmap["type=10"]="SS-SS";
  labelmap["type=11"]="SS-SP";
  labelmap["type=12"]="SP-SP";
  labelmap["type=13"]="SS-PP";
  labelmap["type=14"]="SP-PP";
  labelmap["type=15"]="PP-PP";
}

bool TChain_LoadList(TChain *tc, std::string filename)
{
  ifstream ifile(filename.c_str());
  if (!ifile.is_open())
  {
    std::cerr<<"Error: Filelist "<<filename<<" is not found!\n";
    return 0;
  }
  std::string tmp;
  while (1)
  {
    ifile>>tmp;
    if (ifile.eof()) break;
    tc->AddFile(tmp.c_str());
    if (!tc->GetEntries()) std::cerr<<"Warning: File "<<tmp<<" is empty!\n";
  }
  return 1;
}

std::string selpars(std::string &selpar, std::string seltype, std::string selrange, std::string selva)
{
  if (seltype=="n") return selpar+"=="+selva;
  else if (seltype=="d"||seltype=="f") return "("+selpar+">="+selva+"-"+selrange+"&&"+selpar+"<="+selva+"+"+selrange+")";
  else return "";
}

template <class T>
void MultiDraw(T *ntree, std::string dir, std::string figname, std::string parsfile, const std::string varexp, Float_t *pleg, const std::string xtitle="", const std::string ytitle="", const std::string selection = "", const std::string title="NULL",bool xfix=0, Double_t xmin=0, Double_t xmax=0, bool yfix=0, Double_t ymin=0, Double_t ymax=0, bool xerr=1, bool yerr=1, Float_t marksize=0, bool tl1=true, bool tl2=true)
{
  labelinit();
  std::ifstream pl(parsfile.c_str());
  //First line: parname,valuetype,valueDelta, valuenum, value list=========//
  //Second line: draw parname,valuetype, valuenum, value list===//
  if (pl.is_open())
  {
#ifdef DEBUG
    std::cout<<"Pars load\n";
#endif      
    std::string selpar, seltype, drawpar[2], drawtype[2], srange, drange[2], tmp, totlimit;
    std::vector<std::string> selval, drawval[2];
    Int_t selnum, drawnum[2];
    pl>>totlimit;
    pl>>selpar;
    pl>>seltype;
    pl>>srange;
    pl>>selnum;
    for (int i=0;i<selnum;i++)
    {
      pl>>tmp;
      selval.push_back(tmp);
    }
    for (int j=0;j<2;j++)
    {
      pl>>drawpar[j];
      pl>>drawtype[j];
      pl>>drange[j];
      pl>>drawnum[j];
      for (int i=0;i<drawnum[j];i++)
      {
        pl>>tmp;
        drawval[j].push_back(tmp);
      }
    }
#ifdef DEBUG
    std::cout<<"Build Canvas\n";
#endif      
    TCanvas c1;
    TCut cutt=totlimit.c_str();
    TCut cuts,cut1,cut2;
    TCut cutp=selection.c_str();
    drawnum[1] +=1;
    drawnum[0] +=1;
    for (int s=0;s<selnum;s++)
    {
#ifdef DEBUG
      std::cout<<"Global limit: "<<totlimit<<std::endl;
      std::cout<<selpar<<" "<<seltype<<" "<<srange<<" "<<selval[s]<<std::endl;
      std::cout<<selpars(selpar,seltype,srange,selval[s]).c_str()<<std::endl;
      std::cout<<"Tnum: "<<drawnum[0]*drawnum[1]<<std::endl;
#endif        
      cuts=selpars(selpar,seltype,srange,selval[s]).c_str();
      //      float tlratio=(float)(drawnum[1]-1)/1.05/(float)(drawnum[1]+drawnum[0]-2);
      //      float tlint=0.05/(float)(drawnum[1]-1);
      TGraphErrors **h=new TGraphErrors*[drawnum[0]*drawnum[1]];
      bool *drawflag=new bool[drawnum[1]-1];
      bool *ttot=new bool[drawnum[0]-1];
      for (int i=0;i<drawnum[1]-1;i++) drawflag[i]=false;
      //      Double_t plmid=pleg[1]+(pleg[3]-pleg[1])*tlratio;
      //      Double_t plmid2=plmid*(1+tlint);
      //      TLegend *tl=new TLegend(pleg[0],pleg[1],pleg[2],plmid);
      //      TLegend *tl2=new TLegend(pleg[0],plmid2,pleg[2],pleg[3]);
      TLegend *tl=new TLegend(pleg[0],pleg[1],pleg[2],pleg[3]);
      TMultiGraph *mh=new TMultiGraph();
      if(title!="NULL")
        mh->SetTitle((title+";"+xtitle+";"+ytitle).c_str());
      else
        mh->SetTitle((selpar+" = "+selval[s]+"("+totlimit+");"+xtitle+";"+ytitle).c_str());

      for (int d1=0;d1<drawnum[0]-1;d1++)
      {
#ifdef DEBUG
        std::cout<<"Limit 1:"<<selpars(drawpar[0],drawtype[0],drange[0],drawval[0][d1]).c_str()<<std::endl;
#endif            
        int idd=d1+1;
        idd=idd%10?idd:idd+10;
        ttot[d1]=false;
        cut1=selpars(drawpar[0],drawtype[0],drange[0],drawval[0][d1]).c_str();
        for (int d2=0;d2<drawnum[1]-1;d2++)
        {
#ifdef DEBUG
          std::cout<<"Limit 2:"<<selpars(drawpar[1],drawtype[1],drange[1],drawval[1][d2]).c_str()<<std::endl;
#endif
          cut2=selpars(drawpar[1],drawtype[1],drange[1],drawval[1][d2]).c_str();
          Int_t tnum=ntree->GetEntries(cutt&&cuts&&cut1&&cut2&&cutp);
          if (tnum)
          {
            ttot[d1]=true;
            int d2index=d1*drawnum[1]+d2;
            Double_t *s=0,*es=0,*p=0,*ep=0;
            ntree->Draw(varexp.c_str(),cutt&&cuts&&cut1&&cut2&&cutp,"goff");
            s=ntree->GetV1();
            if (xerr) es=ntree->GetV2();
            p=ntree->GetV3();
            if (yerr) ep=ntree->GetV4();
            h[d2index]=new TGraphErrors(tnum,s,p,es,ep);
            h[d2index]->SetMarkerColor(idd);
            h[d2index]->SetLineColor(idd);
            //            h[d2index]->SetLineWidth(0.5*(drawnum[0]-d1));
            h[d2index]->SetMarkerStyle(d2+20);
            if (marksize) h[d2index]->SetMarkerSize(marksize);
            if (!drawflag[d2]) {
              std::string label1="";
              if (labelmap.count(drawpar[1])) label1=labelmap[drawpar[1]]+"="+drawval[1][d2];
              else if (labelmap.count(drawpar[1]+"="+drawval[1][d2])) label1=labelmap[drawpar[1]+"="+drawval[1][d2]];
              else {
                std::cerr<<"Error label!: "<<drawpar[1]+"="+drawval[1][d2]<<"\n";
                exit(1);
              }
              int markerindex=(drawnum[0]-1)*drawnum[1]+d2;
              h[markerindex]=new TGraphErrors;
              h[markerindex]->SetMarkerStyle(d2+20);
              h[markerindex]->SetMarkerColor(1);
              if (marksize) h[markerindex]->SetMarkerSize(marksize);
              if(tl1) tl->AddEntry(h[markerindex],label1.c_str(),"p");
              drawflag[d2]=true;
            }
            mh->Add(h[d2index]);
            std::cout<<d2index<<": "<<drawpar[0]+" = "+drawval[0][d1]+"; "+drawpar[1]+" = "+drawval[1][d2]+" drawn.\n";
          }
        }
      }
      for(int d1=0;d1<drawnum[0]-1;d1++){
        if (ttot[d1]) {
          int idd=d1+1;
          idd=idd%10?idd:idd+10;
          int d1eindex=(d1+1)*drawnum[1]-1;
          std::string label0="";
          if (labelmap.count(drawpar[0])) label0=labelmap[drawpar[0]]+"="+drawval[0][d1];
          else if (labelmap.count(drawpar[0]+"="+drawval[0][d1])) label0=labelmap[drawpar[0]+"="+drawval[0][d1]];
          else {
            std::cerr<<"Error label!: "<<drawpar[0]+"="+drawval[0][d1]<<"\n";
            exit(1);
          }
          h[d1eindex]=new TGraphErrors;
          h[d1eindex]->SetLineColor(idd);
          if(tl2) tl->AddEntry(h[d1eindex],label0.c_str(),"l");
        }
      }
      mh->Draw("AP");
      if(tl1||tl2) tl->Draw("same");
      tl->SetFillStyle(0);
      tl->SetFillColor(0);
      tl->SetLineStyle(0);
      tl->SetLineColor(0);
      tl->SetShadowColor(0);
      // tl2->Draw("same");
      // tl2->SetFillStyle(0);
      // tl2->SetFillColor(0);
      // tl2->SetLineStyle(0);
      // tl2->SetShadowColor(0);
      // tl2->SetLineColor(0);
      gPad->Modified();
      if(xfix) mh->GetXaxis()->SetLimits(xmin,xmax);
      if(yfix) {
        mh->SetMinimum(ymin);
        mh->SetMaximum(ymax);
      }
      mh->GetYaxis()->SetTitleOffset(1.2);
      c1.Print((dir+selpar+"_"+selval[s]+"_"+figname).c_str());
      c1.Clear();
    }
  }
}

#endif
