#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "flistsort.h"
#include "uftools.h"
#include "initial.h"
#include "nbodystep3.h"
#include "nbodyhfm.h"
#include "TEntryList.h"
#include "TFile.h"
#include "TTree.h"

void sd(std::vector<Int_t>& a, Int_t & data, const Int_t & ave)
{
  for (size_t i=0;i<a.size();i++)
    data +=pow(a[i]-ave,2);
  data = sqrt(data/(a.size()-1))+0.5;
}

void sd(std::vector<Double_t>& a, Double_t & data, const Double_t & ave)
{
  for (size_t i=0;i<a.size();i++)
    data +=pow(a[i]-ave,2);
  data = sqrt(data/(a.size()-1));
}

void getnum(const char* name, std::vector<Int_t> &item, Int_t &member, bool fill = 1)
{
  TTree *tr=(TTree*)gDirectory->Get(name);
  if (tr)
  {
    Int_t tnum=tr->GetEntries();
    item.push_back(tnum);
    member +=tnum;
  }
  else if (fill) item.push_back(0);
  else std::cerr<<name<<" is empty.\n";
}

int main (int argc, char *argv[])
{
  //par initial=======================================//
  pars_initial pars(".step3_config");
  //  pars.add("parlist","group_num:ns:rbar:nbratio:npratio:m1:p1","parlist");
  pars.add("flist","dup:dirname:dirname list(with no '_')","flist");
  pars.add("saverootname","new root to store data","step3.root");
  pars.add("filelist","file name to store filelist","filelist");
  pars.add("parlist","file name to store parlist","parlist");
  pars.initial(argc,argv);

  //File open=========================================//
  std::string filename;
  std::ifstream filein(pars.get<std::string>("flist").c_str());
  if (filein.is_open())
  {
    std::vector<flistsort> fls;
    int dup, ns, m1, p1, rands;
    double rbar, npr, nbr;
    while (!filein.eof())
    {
      filein>>dup;
      filein>>filename;
      filein>>ns;
      filein>>rbar;
      filein>>nbr;
      filein>>npr;
      filein>>m1;
      filein>>p1;
      filein>>rands;
      if (filein.eof()) break;
      flistsort ftmp(dup,ns,rbar,nbr,npr,m1,p1,rands,filename);
      fls.push_back(ftmp);
    }
    std::cout<<"sort filename\n";
    std::sort(fls.begin(),fls.end(),flistshort);

    //Output filelist===================================//
    ofstream flist(pars.get<std::string>("filelist").c_str());
    for (size_t i=0;i<fls.size();i++)
      flist<<fls[i].dup<<" "<<fls[i].filename<<"\n";
    flist.close();
    std::cout<<"filelist generated\n";

    //Generate parlist==================================//
    std::vector<flistsort> pls;
    for (size_t i=0; i<fls.size(); i++)
    {
      if (i==0)
      {
        dup=1;
        ns=fls[i].ns;
        rbar=fls[i].rbar;
        nbr=fls[i].nbr;
        npr=fls[i].npr;
        m1=fls[i].m1;
        p1=fls[i].p1;
      }
      else if (flistequal(fls[i-1],fls[i])) dup++;
      else
      {
        flistsort ftmp(dup,ns,rbar,nbr,npr,m1,p1,0,"");
        pls.push_back(ftmp);
        dup=1;
        ns=fls[i].ns;
        rbar=fls[i].rbar;
        nbr=fls[i].nbr;
        npr=fls[i].npr;
        m1=fls[i].m1;
        p1=fls[i].p1;
      }
      if (i==fls.size()-1)
      {
        flistsort ftmp(dup,ns,rbar,nbr,npr,m1,p1,0,"");
        pls.push_back(ftmp);
      }
    }

    //Output parlist====================================//
    ofstream plist(pars.get<std::string>("parlist").c_str());
    for (size_t i=0;i<pls.size();i++)
      plist<<pls[i].dup<<" "<<pls[i].ns<<" "<<pls[i].rbar<<" "<<pls[i].nbr<<" "<<pls[i].npr<<" "<<pls[i].m1<<" "<<pls[i].p1<<"\n";
    plist.close();
    std::cout<<"parlist generated\n";

    //Fill st3==========================================//
    nbodystep3 st3(pars.get<std::string>("saverootname"));
    std::vector<flistsort>::iterator fi=fls.begin();
    for (std::vector<flistsort>::iterator i=pls.begin();i<pls.end();i++)
    {
      st3.gnum=i->dup;
      if (st3.gnum<=1)
      {
        std::cerr<<"Error: lack samples (gnum="<<st3.gnum<<") for "<<i->ns<<" "<<i->rbar<<" "<<i->nbr<<" "<<i->npr<<" "<<i->m1<<" "<<i->p1<<std::endl;
        continue;
      }
      st3.ns=i->ns;
      st3.rbar=i->rbar;
      st3.m1=i->m1;
      st3.p1=i->p1;
      st3.np=static_cast<Int_t>(st3.ns*i->npr);
      st3.nb=static_cast<Int_t>(st3.ns*i->nbr);

      //Initial members=================================//
      for (int j=0;j<4;j++)
      {
        st3.hnst[j]=0;
        st3.hnpt[j]=0;
        st3.hnpst[j]=0;
      }
      for (int j=0;j<2;j++)
      {
        st3.endt[j]=0;
        st3.ssp[j]=0;
        st3.psp[j]=0;
        st3.sss[j]=0;
        st3.pss[j]=0;
        st3.ss[j]=0;
        st3.sp[j]=0;
        st3.pp[j]=0;
        st3.spsp[j]=0;
        st3.sssp[j]=0;
        st3.ssss[j]=0;
      }

      std::vector<Double_t> thnst, thnpt, thnpst, tendt, thnstp, thnptp, thnpstp;
      std::vector<Int_t> tss, tsp, tpp, tsss, tssp, tpsp, tpss, tssss, tsssp, tspsp;
      for (int gn=0;gn<st3.gnum;gn++)
      {
        dup=fi->dup;
        filename=fi->filename;
        fi++;
        std::cout<<"Dup: "<<dup<<"  Filename: "<<filename<<std::endl;

        //ns np=============================================//
        nbodyhfm nhfm(filename+"_hfm.root");
        if (nhfm.Identify()==1)
        {
          std::cerr<<filename<<" out3 error\n";
          st3.gnum--;
          gn--;
          if (st3.gnum<=1)
            break;
          continue;
        }
        nhfm.GetEntry(nhfm.GetEntries()-1);
        tendt.push_back(nhfm.t);
        st3.endt[0] +=nhfm.t;
        nhfm.GetEntry(0);
        if (nhfm.gethalfns()>0)
        {
          st3.hnst[0] +=nhfm.t;
          thnst.push_back(nhfm.t);
          thnstp.push_back(nhfm.t/tendt.back());
          st3.hnst[2] +=thnstp.back();
        }
        else std::cerr<<"Error: half ns cannot found!\n";
#ifdef DEBUG
        std::cout<<"gethalfns\n";
#endif          
        if (nhfm.gethalfnp()>0)
        {
          st3.hnpt[0] +=nhfm.t;
          thnpt.push_back(nhfm.t);
          thnptp.push_back(nhfm.t/tendt.back());
          st3.hnpt[2] +=thnptp.back();
        }
        else std::cerr<<"Error: half np cannot found!\n";
#ifdef DEBUG
        std::cout<<"gethalfnp\n";
#endif          
        if (nhfm.gethalfnpvsns()>0)
        {
          thnpst.push_back(nhfm.t);
          st3.hnpst[0] +=nhfm.t;
          thnpstp.push_back(nhfm.t/tendt.back());
          st3.hnpst[2] +=thnpstp.back();
        }
        else std::cerr<<"Error: half np/ns cannot found!\n";
#ifdef DEBUG
        std::cout<<"gethalfnpns\n";
#endif
        std::cout<<"gn:"<<gn<<" thnst:"<<(thnst.size()?thnst.back():0)<<" thnpt:"<<(thnpt.size()?thnpt.back():0)<<" thnpst:"<<(thnpst.size()?thnpst.back():0)<<" thnpstp:"<<(thnpstp.size()?thnpstp.back():0)<<std::endl;

        //encounter single==================================//
        TFile *scr=new TFile((filename+"_scr.root").c_str(),"update");
        getnum("ss",tss,st3.ss[0],0);
        getnum("sp",tsp,st3.sp[0]);
        getnum("pp",tpp,st3.pp[0]);
        scr->Close();
        delete scr;
        std::cout<<"gn:"<<gn<<"; ss:"<<(tss.size()?tss.back():0)<<"; sp:"<<(tsp.size()?tsp.back():0)<<"; pp:"<<(tpp.size()?tpp.back():0)<<std::endl;
        if (dup<3)
        {
          tssp.push_back(0);
          tsss.push_back(0);
          tpsp.push_back(0);
          tpss.push_back(0);
          tssss.push_back(0);
          tsssp.push_back(0);
          tspsp.push_back(0);
        }
        if (dup==3)
        {
          tssss.push_back(0);
          tsssp.push_back(0);
          tspsp.push_back(0);
        }          
        if (dup==3||dup==4)
        {
          // triple quater====================================//
          TFile *tcr=new TFile((filename+"_tcr.root").c_str(),"update");
          if (!tcr)
          {
            tsss.push_back(0);
            tssp.push_back(0);
            tpsp.push_back(0);
            tpss.push_back(0);
          }
          else
          {
            getnum("sss",tsss,st3.sss[0]);
            getnum("ssp",tssp,st3.ssp[0]);
            getnum("psp",tpsp,st3.psp[0]);
            getnum("pss",tpss,st3.pss[0]);
          }
          tcr->Close();
          delete tcr;
          std::cout<<"gn:"<<gn<<"; ssp:"<<(tssp.size()?tssp.back():0)<<"; sss"<<(tsss.size()?tsss.back():0)<<"; psp"<<(tpsp.size()?tpsp.back():0)<<"; pss"<<(tpss.size()?tpss.back():0)<<std::endl;
        }
        if (dup==4)
        {
          TFile *qcr=new TFile((filename+"_qcr.root").c_str(),"update");
          if (!qcr)
          {
            tssss.push_back(0);
            tsssp.push_back(0);
            tspsp.push_back(0);
          }
          else
          {
            getnum("ssss",tssss,st3.ssss[0]);
            getnum("sssp",tsssp,st3.sssp[0]);
            getnum("spsp",tspsp,st3.spsp[0]);
          }
          qcr->Close();
          delete qcr;
          std::cout<<"gn:"<<gn<<"; sssp:"<<(tsssp.size()?tsssp.back():0)<<"; spsp:"<<(tspsp.size()?tspsp.back():0)<<"; ssss:"<<(tssss.size()?tssss.back():0)<<std::endl;
        }
      }
#ifdef DEBUG
      std::cout<<"gnum:"<<st3.gnum<<";\n";
#endif
      if (st3.gnum<=1)
      {
        std::cerr<<"Error: lack samples (gnum="<<st3.gnum<<") for "<<i->ns<<" "<<i->rbar<<" "<<i->nbr<<" "<<i->npr<<" "<<i->m1<<" "<<i->p1<<std::endl;
        continue;
      }
      //ns np=============================================//
      st3.hnst[0] /=thnst.size();
      st3.hnpt[0] /=thnpt.size();
      st3.hnpst[0] /=thnpst.size();
      st3.hnpst[2] /=thnpstp.size();
      st3.hnst[2] /=thnstp.size();
      st3.hnpt[2] /=thnptp.size();
      st3.endt[0] /=tendt.size();
      st3.ss[0] =(float)st3.ss[0]/tss.size()+0.5;
      st3.sp[0] =(float)st3.sp[0]/tsp.size()+0.5;
      st3.pp[0] =(float)st3.pp[0]/tpp.size()+0.5;
      st3.ssp[0] =(float)st3.ssp[0]/tssp.size()+0.5;
      st3.psp[0] =(float)st3.psp[0]/tpsp.size()+0.5;
      st3.sss[0] =(float)st3.sss[0]/tsss.size()+0.5;
      st3.pss[0] =(float)st3.pss[0]/tpss.size()+0.5;
      st3.ssss[0] =(float)st3.ssss[0]/tssss.size()+0.5;
      st3.sssp[0] =(float)st3.sssp[0]/tsssp.size()+0.5;
      st3.spsp[0] =(float)st3.spsp[0]/tspsp.size()+0.5;

      sd(thnst, st3.hnst[1], st3.hnst[0]);
      sd(thnpt, st3.hnpt[1], st3.hnpt[0]);
      sd(thnpst, st3.hnpst[1], st3.hnpst[0]);
      sd(thnstp, st3.hnst[3], st3.hnst[2]);
      sd(thnptp, st3.hnpt[3], st3.hnpt[2]);
      sd(thnpstp, st3.hnpst[3], st3.hnpst[2]);
      sd(tss,st3.ss[1],st3.ss[0]);
      sd(tsp,st3.sp[1],st3.sp[0]);
      sd(tpp,st3.pp[1],st3.pp[0]);
      sd(tsss,st3.sss[1],st3.sss[0]);
      sd(tssp,st3.ssp[1],st3.ssp[0]);
      sd(tpsp,st3.psp[1],st3.psp[0]);
      sd(tpss,st3.pss[1],st3.pss[0]);
      sd(tssss,st3.ssss[1],st3.ssss[0]);
      sd(tspsp,st3.spsp[1],st3.spsp[0]);
      sd(tsssp,st3.sssp[1],st3.sssp[0]);

      //encounter=========================================//
      st3.Fill();
    }
    st3.Write("",TObject::kOverwrite);
    std::cout<<"All finished\n.";
  }
  else
    std::cerr<<"Error: parlist or filelist cannot open\n";
  return 0;
}
