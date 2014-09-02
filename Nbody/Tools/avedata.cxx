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

int main (int argc, char *argv[])
{
  //par initial=======================================//
  pars_initial pars(".step3_config");
  //  pars.add("parlist","group_num:ns:rbar:nbratio:npratio:m1:p1","parlist");
  pars.add("vtype","velocity of planets distribution type: 0 or 4",(int)0);
  pars.add("flist","dup:dirname:dirname list(with no '_')","flist");
  pars.add("saverootname","new root to store data","step3.root");
  pars.add("rootpath","celist root path","../root/");
  pars.add("filelist","file name to store filelist","filelist");
  pars.add("parlist","file name to store parlist","parlist");
  pars.initial(argc,argv);

  //File open=========================================//
  std::string filename;
  std::string rootpath=pars.get<std::string>("rootpath").c_str();
  std::ifstream filein(pars.get<std::string>("flist").c_str());
  if (filein.is_open())
  {
    std::vector<flistsort> fls;
    int dup, ns, rands;
    int m1=0;
    int p1=0;
    int vtype=pars.get<int>("vtype");
    double rbar, npr, nbr;
    while (!filein.eof())
    {
      filein>>filename;
      filein>>ns;
      filein>>rbar;
      filein>>nbr;
      filein>>npr;
      if (vtype==4)
      {
        filein>>m1;
        filein>>p1;
      }
      filein>>rands;
      if (filein.eof()) break;
      flistsort ftmp(1,ns,rbar,nbr,npr,m1,p1,rands,filename);
      fls.push_back(ftmp);
    }
    std::cout<<"sort filename\n";
    std::sort(fls.begin(),fls.end(),flistshort);

    //Filelist: ========================================//
    //          root file number for one model =========//
    //          parlist ================================//
    //          filename ===============================//
    //Generate parlist==================================//
    ofstream flist(pars.get<std::string>("filelist").c_str());
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
        if (vtype==4)
        {
          m1=fls[i].m1;
          p1=fls[i].p1;
        }
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
        if (vtype==4)
        {
          m1=fls[i].m1;
          p1=fls[i].p1;
        }
      }
      if (i==fls.size()-1)
      {
        flistsort ftmp(dup,ns,rbar,nbr,npr,m1,p1,0,"");
        pls.push_back(ftmp);
      }
      flist<<fls[i].filename<<" "<<fls[i].ns<<" "<<fls[i].rbar<<" "<<fls[i].nbr<<" "<<fls[i].npr<<" "<<fls[i].m1<<" "<<fls[i].p1<<std::endl;
    }
    flist.close();

    //Output parlist====================================//
    ofstream plist(pars.get<std::string>("parlist").c_str());
    for (size_t i=0;i<pls.size();i++)
      plist<<pls[i].dup<<" "<<pls[i].ns<<" "<<pls[i].rbar<<" "<<pls[i].nbr<<" "<<pls[i].npr<<" "<<pls[i].m1<<" "<<pls[i].p1<<"\n";
    plist.close();
    std::cout<<"parlist generated\n";

    //Fill st3==========================================//
    nbodystep3 st3(pars.get<std::string>("saverootname"));
#ifdef DEBUG
    std::cout<<"Nb step3\n";
#endif
    std::vector<flistsort>::iterator fi=fls.begin();
    for (std::vector<flistsort>::iterator i=pls.begin();i<pls.end();i++)
    {
      st3.gnum=i->dup;
#ifdef DEBUG
      std::cout<<"Begin loop: "<<i->dup<<"\t"<<i->ns<<"\t"<<i->npr<<"\t"<<i->rbar<<"\t"<<i->nbr<<"\t"<<i->m1<<"\t"<<i->p1<<std::endl;
#endif
      //check the number of samples=======================//
      if (st3.gnum<=1)
      {
        std::cerr<<"Error: lack samples (gnum="<<st3.gnum<<") for "<<i->ns<<" "<<i->rbar<<" "<<i->nbr<<" "<<i->npr<<" "<<i->m1<<" "<<i->p1<<std::endl;
        continue;
      }
      st3.ns=i->ns;
#ifdef DEBUG
      std::cout<<"ns:"<<i->ns<<std::endl;
#endif
      st3.rbar=i->rbar;
#ifdef DEBUG
      std::cout<<"rbar:"<<i->rbar<<std::endl;
#endif
      if (vtype==4)
      {
        st3.m1=i->m1;
        st3.p1=i->p1;
      }
      else
      {
        st3.m1=st3.p1=0;
      }
      st3.np=static_cast<Int_t>(st3.ns*i->npr);
#ifdef DEBUG
      std::cout<<"np:"<<st3.np<<std::endl;
#endif
      st3.nb=static_cast<Int_t>(st3.ns*i->nbr);
#ifdef DEBUG
      std::cout<<"nb:"<<st3.nb<<std::endl;
#endif
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
        for (int jj=1;jj<=15;jj++)
          st3[jj][j]=0;
      }
#ifdef DEBUG
      std::cout<<"Finish initial\n";
#endif
      std::vector<Double_t> thnst, thnpt, thnpst, tendt, thnstp, thnptp, thnpstp;
      std::vector<Int_t> tnce[16];
#ifdef DEBUG
      std::cout<<"Go inside loop to open root file\n";
#endif
      TFile *ce=0;
      TTree *tce=0;
      for (int gn=0;gn<st3.gnum;gn++)
      {
        // dup=fi->dup;
        filename=fi->filename;
        fi++;
        // if (dup!=2)
        // {
        //   std::cerr<<"Error: "<<filename<<"file number error\n";
        //   st3.gnum--;
        //   gn--;
        //   if (st3.gnum<=1)
        //     break;
        //   continue;
        // }
        // std::cout<<"Dup: "<<dup<<"  Filename: "<<filename<<std::endl;
        
        nbodyhfm nhfm(filename+"/hfm.root");
        if (nhfm.Identify()==1)
        {
          std::cerr<<"Error: "<<filename<<" hfm empty\n";
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

        std::string ttype="v0";
        std::string nfile;
        if (vtype==4) ttype="v4";

        //encounter=========================================//
        if (!ce) {
          int i=filename.length()-1;
          while (filename[i]!='_') i--;
          if (vtype==4) {
            i--;
            while (filename[i]!='_') i--;
            i--;
            while (filename[i]!='_') i--;
          }
          nfile=filename.substr(0,i);
          ce=new TFile((rootpath+nfile+ttype+"_celist.root").c_str());
          tce=(TTree*)gDirectory->Get("celist");
        }
        if (!tce)
        {
          std::cerr<<"Error: "<<rootpath<<nfile<<ttype<<"_celist.root empty\n";
          exit(1);
          st3.gnum--;
          gn--;
          if (st3.gnum<=1)
            break;
          continue;
        }
        for (int j=1;j<=15;j++)
        {
          if (vtype==4) tnce[j].push_back(tce->GetEntries(("type=="+to<std::string>(j)+"&&m1=="+to<std::string>(fi->m1)+"&&p1=="+to<std::string>(fi->p1)+"&&model=="+to<std::string>(fi->rands)).c_str()));
          else tnce[j].push_back(tce->GetEntries(("type=="+to<std::string>(j)+"&&model=="+to<std::string>(fi->rands)).c_str()));
#ifdef DEBUG
          if (tnce[j].back()==0) std::cerr<<"Warning: get zero for encounters, type "<<j<<std::endl;
#endif    
          st3[j][0] +=tnce[j].back();
        }
      }
      ce->Close();
      delete ce;

#ifdef DEBUG
      std::cout<<"gnum:"<<st3.gnum<<";\n";
#endif
      if (st3.gnum<=1)
      {
        std::cerr<<"Error: lack samples (gnum="<<st3.gnum<<") for "<<i->ns<<" "<<i->rbar<<" "<<i->nbr<<" "<<i->npr<<" "<<i->m1<<" "<<i->p1<<std::endl;
        continue;
      }
      st3.hnst[0] /=thnst.size();
      st3.hnpt[0] /=thnpt.size();
      st3.hnpst[0] /=thnpst.size();
      st3.hnpst[2] /=thnpstp.size();
      st3.hnst[2] /=thnstp.size();
      st3.hnpt[2] /=thnptp.size();
      st3.endt[0] /=tendt.size();
      sd(thnst, st3.hnst[1], st3.hnst[0]);
      sd(thnpt, st3.hnpt[1], st3.hnpt[0]);
      sd(thnpst, st3.hnpst[1], st3.hnpst[0]);
      sd(thnstp, st3.hnst[3], st3.hnst[2]);
      sd(thnptp, st3.hnpt[3], st3.hnpt[2]);
      sd(thnpstp, st3.hnpst[3], st3.hnpst[2]);
      for (int j=1;j<=15;j++)
      {
        st3[j][0] = (float)st3[j][0]/tnce[j].size()+0.5;
        sd(tnce[j],st3[j][1],st3[j][0]);
      }

      st3.Fill();
    }
    st3.Write("",TObject::kOverwrite);
    std::cout<<"All finished\n.";
  }
  else
    std::cerr<<"Error: parlist or filelist cannot open\n";
  return 0;
}

