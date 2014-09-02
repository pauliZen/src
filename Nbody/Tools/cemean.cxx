//Get Fraction of EC vs. time from celist===========//
//pars:=============================================//
//     celist: celist_root file lst=================//
//     nroot: new root name=========================//
//     parlist: directory list file with no '_'=====//
//     vtype: true for v4, false for v0=============//

#include <nbodycelist.h>
#include <nbodycemean.h>
#include <initial.h>
#include <uftools.h>

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


static Double_t tfrac[11]={0.001, 0.021, 0.159, 0.5, 0.841, 0.9755, 0.998, 0.1, 0.25, 0.75, 0.9};

int main(int argc, char* argv[])
{
  pars_initial init(".cemean_config");
  init.add("celist","ce file list","cefile.lst");
  init.add("nroot","new data file name for storage","cemean.root");
  init.add("parlist","pars list file","pars.lst");
  init.add("vtype","v4 or v0",(bool)false);
  init.initial(argc,argv);

  ifstream fs(init.get<std::string>("parlist").c_str());
  if (!fs.is_open())  {
    std::cerr<<"Error: No filelist found!\n";
  }

  //initial celist====================================//
  nbodycelist tcl;
  nbodycemean tcm(init.get<std::string>("nroot"));

  //load celist=======================================//
  tcl.LoadList(init.get<std::string>("celist"));

  //get type of run v4 or v0 =========================//
  bool isv4=init.get<bool>("vtype");

  //Value of pars=====================================//
  Double_t rnp,rnb;

  //Main loop=========================================//
  while(true)  {
    //Get pars data=====================================//
    fs>>tcm.ns;
    fs>>tcm.rbar;
    fs>>rnb;
    fs>>rnp;
    if (isv4) {
      fs>>tcm.m1;
      fs>>tcm.p1;
    }
    else {
      tcm.m1=0;
      tcm.p1=0;
    }
      
    fs>>tcm.model;
    //When reach end, go out============================//
    if (fs.eof()) break;

    tcm.nb=rnb*tcm.ns;
    tcm.np=rnp*tcm.ns;
    //Find in root file=================================//
    std::string drawopt;
    drawopt="ns=="+to<std::string>(tcm.ns)+"&&np=="+to<std::string>(tcm.np)+"&&nb=="+to<std::string>(tcm.nb)+"&&model=="+to<std::string>(tcm.model)+"&&rbar<="+to<std::string>(1.01*tcm.rbar)+"&&rbar>="+to<std::string>(0.99*tcm.rbar);
    if (isv4) drawopt=drawopt+"&&m1=="+to<std::string>(tcm.m1)+"&&p1=="+to<std::string>(tcm.p1);

    tcl.Draw(">>tlist",drawopt.c_str(),"entrylist");
    TEntryList *tel=(TEntryList*)gDirectory->Get("tlist");
    tcl.fchain->SetEntryList(tel);
    if (!tel)
    {
      std::cerr<<"Warning: model not exist!\n";
      continue;
    }
    int ntot=tel->GetN();
    if (ntot==0) continue;
    Double_t **ttype=new Double_t*[15];
    int tnum[15];
    for (int i=0;i<15;i++)  {
      tnum[i]=0;
      ttype[i]=new Double_t[ntot];
    }

    Int_t tj=tcl.GetListEntry(0,tel);
    tcl.GetEntry(tj);
    //tcl.b_tstar->GetEntry(tj);
    tcm.tstar=tcl.tstar;

    std::cout<<drawopt<<" Ntot:"<<ntot<<std::endl;

    for (int j=0;j<ntot;j++)  {
      tj=tcl.GetListEntry(j,tel);
      tcl.GetEntry(tj);
      //      tcl.b_type->GetEntry(tj);
      //      tcl.b_t->GetEntry(tj);
#ifdef DEBUG
      std::cout<<"j "<<j<<" tj "<<tj<<" type "<<tcl.type<<" t "<<tcl.t[1]<<std::endl;
#endif      
      if (tcl.type>15) continue;
      int type=tcl.type-1;
      ttype[type][tnum[type]]=tcl.t[1];
      tnum[type]++;
    }

#ifdef DEBUG
    for (int i=0;i<15;i++)
      std::cout<<"Type: "<<i+1<<"; Ntot:"<<tnum[i]<<std::endl;
#endif    
    
    for(int i=0;i<15;i++) {
      tcm.ntot=tnum[i];
      tcm.type=i+1;
      if (tnum[i]==0) {
        memset(tcm.ctime,0,sizeof(Double_t)*11);
        tcm.Fill();
      }
      else {
        std::sort(ttype[i],ttype[i]+tnum[i]);
        for (int j=0;j<11;j++) {
          int tindex=(int)(tnum[i]*tfrac[j]+0.5);
          if (tindex>tnum[i]) tindex=tnum[i]-1;
          else if(tindex>0) tindex=tindex-1;
          tcm.ctime[j]=ttype[i][tindex];
        }
        tcm.Fill();
      }
    }
    tcl.fchain->SetEntryList(0);
    delete tel;
  }
  tcm.Write("",TObject::kOverwrite);
  
  return 0; 
}
