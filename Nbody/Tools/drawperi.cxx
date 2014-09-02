//Not used now======================================//

#include <nbodytcr.h>
#include <nbodyqcr.h>
#include <nbodyscr.h>
#include <initial.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TROOT.h>
#include <TLegend.h>
#include <uftools.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//Transform stream to string vector=================//
void filllist(std::vector<std::string> &file, std::ifstream &lin)
{
  std::string ftmp; 
  while (!lin.eof())
  {
    lin>>ftmp;
    if (!lin.eof())
    {
      file.push_back(ftmp);
      std::cout<<"Add "<<ftmp<<std::endl;
    }
  }
}
template <typename T> void draw(T &treeclass, TH1F *sh, std::string drawpars, std::string title, std::string xtitle, std::string ytitle, pars_initial &pars)
{
    treeclass.Draw(("peri>>htmp"+to<std::string>(i)).c_str(),"","goff");
    if (treeclass.GetEntries())
    {
      std::cout<<sname[i]<<"\t"<<treeclass.GetEntries()<<std::endl;
      sh=(TH1F*)gDirectory->Get(("htmp"+to<std::string>(i)).c_str())->Clone();
      sh->SetXTitle("Minimum peri(AU)");
      sh->SetYTitle("Number of encounters");
      sh->SetTitle(("Peri distribution "+pars.get<std::string>("figtitle")).c_str());
      sh->SetLineColor(i+1);
      sh->SetLineStyle(1);
      sh->SetLineWidth(1);
      sh->SetStats(kFALSE);
      tl->AddEntry(sh,sname[i].c_str());
      if (i==0) sh->Draw();
      else sh->Draw("same");
    }
}

int main(int argc, char* argv[])
{
  pars_initial pars(".drawperi_config");
  pars.add("slst","scr root list","slist");
  pars.add("tlst","tcr root list","tlist");
  pars.add("qlst","qcr root list","qlist");
  pars.add("savefile","save figure file name","peri.eps");
  pars.add("figtitle","figure title","");
  pars.initial(argc,argv);
  std::ifstream slin(pars.get<std::string>("slst").c_str());
  std::ifstream tlin(pars.get<std::string>("tlst").c_str());
  std::ifstream qlin(pars.get<std::string>("qlst").c_str());
  if (slin.is_open()&&tlin.is_open()&&qlin.is_open())
  {
    std::vector<std::string> lfile[3];
    filllist(lfile[1],slin);
    filllist(lfile[2],tlin);
    filllist(lfile[3],qlin);
    std::string sname[3]={"ss","sp","pp"};
    std::string tname[4]={"sss","ssp","psp","pss"};
    std::string qname[3]={"ssss","sssp","spsp"};
    nbodyscr *scrn[3];
    nbodyqcr *qcrn[3];
    nbodytcr *tcrn[4];
    for (int i=0;i<4;i++)
    {
      if (i<3) scrn[i]=new nbodyscr(sname[i]);
      tcrn[i]=new nbodytcr(tname[i]);
      if (i<3) qcrn[i]=new nbodyqcr(qname[i]);
      for (size_t j=0;j<lfile[i].size();j++)
      {
        if (i<3) scrn[i].LoadFile(sfile[j]);
        tcrn[i].LoadFile(tfile[j]);
        if (i<3) qcrn[i].LoadFile(qfile[j]);
      }
    }
    TH1F **sh=new TH1F*[3];
    TH1F **th=new TH1F*[4];
    TH1F **qh=new TH1F*[3];
    TH2F **sh2=new TH2F*[3];
    TH2F **th2=new TH2F*[4];
    TH2F **qh2=new TH2F*[3];
    TLegend *tl=new TLegend(0.7,0.9,0.9,0.5);
    TCanvas c1;
    c1.cd();
    c1.SetLogy();
    for (int i=0;i<3;i++)
    {
      scrn.Draw(("peri>>htmp"+to<std::string>(i)).c_str(),"","goff");
      if (scrn.GetEntries())
      {
        std::cout<<sname[i]<<"\t"<<scrn.GetEntries()<<std::endl;
        sh[i]=(TH1F*)gDirectory->Get(("htmp"+to<std::string>(i)).c_str())->Clone();
        sh[i]->SetXTitle("Minimum peri(AU)");
        sh[i]->SetYTitle("Number of encounters");
        sh[i]->SetTitle(("Peri distribution "+pars.get<std::string>("figtitle")).c_str());
        sh[i]->SetLineColor(i+1);
        sh[i]->SetLineStyle(1);
        sh[i]->SetLineWidth(1);
        sh[i]->SetStats(kFALSE);
        tl->AddEntry(sh[i],sname[i].c_str());
        if (i==0) sh[i]->Draw();
        else sh[i]->Draw("same");
      }
    }
    for (int i=0;i<4;i++)
    {
      nbodytcr tcrn(tname[i]);
      for (size_t j=0;j<tfile.size();j++)
        tcrn.LoadFile(tfile[j]);
      tcrn.Draw(("pmin>>htmp"+to<std::string>(i*2)).c_str(),"","goff");
      if (tcrn.GetEntries())
      {
      std::cout<<tname[i]<<"\t"<<tcrn.GetEntries()<<std::endl;
      th[i]=(TH1F*)gDirectory->Get(("htmp"+to<std::string>(i*2)).c_str())->Clone();
      th[i]->SetXTitle("Minimum peri(AU)");
      th[i]->SetYTitle("Number of encounters");
      th[i]->SetTitle(("Peri distribution "+pars.get<std::string>("figtitle")).c_str());
      th[i]->SetLineColor(i+1);
      th[i]->SetLineStyle(2);
      th[i]->SetLineWidth(2);
      th[i]->SetStats(kFALSE);
      tl->AddEntry(th[i],tname[i].c_str());
      th[i]->Draw("same");
      }
    }
    for (int i=0;i<3;i++)
    {
      nbodyqcr qcrn(qname[i]);
      for (size_t j=0;j<qfile.size();j++)
        qcrn.LoadFile(qfile[j]);
      qcrn.Draw(("pmin>>htmp"+to<std::string>(i*3)).c_str(),"","goff");
      if (qcrn.GetEntries())
      {
      std::cout<<qname[i]<<"\t"<<qcrn.GetEntries()<<std::endl;
      qh[i]=(TH1F*)gDirectory->Get(("htmp"+to<std::string>(i*3)).c_str())->Clone();
      qh[i]->SetXTitle("Minimum peri(AU)");
      qh[i]->SetYTitle("Number of encounters");
      qh[i]->SetTitle(("Peri distribution "+pars.get<std::string>("figtitle")).c_str());
      qh[i]->SetLineColor(i+7);
      qh[i]->SetLineStyle(1);
      //      qh[i]->SetFillColor(i+7);
      qh[i]->SetLineWidth(1);
      qh[i]->SetStats(kFALSE);
      tl->AddEntry(qh[i],qname[i].c_str());
      qh[i]->Draw("same");
      }
    }
    tl->SetFillStyle(0);
    tl->Draw();
    c1.Print(pars.get<std::string>("savefile").c_str());
  }
  else std::cerr<<"Error: list not open succesfully.\n";
  return 0;
}
