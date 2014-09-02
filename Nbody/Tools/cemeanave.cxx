//Get average Fraction of EC vs. time from cemean=============//

#include <nbodycemean.h>
#include <nbodycemave.h>
#include <initial.h>
#include <uftools.h>

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

int main(int argc, char* argv[])
{
  pars_initial init(".cemean_config");
  init.add("cemlist","cemean file list","cemfile.lst");
  init.add("nroot","new data file name for storage","cemave.root");
  init.add("parlist","pars list file","pars.lst");
  init.add("vtype","v4 or v0",(bool)false);
  init.initial(argc,argv);

  ifstream fs(init.get<std::string>("parlist").c_str());
  if (!fs.is_open())  {
    std::cerr<<"Error: No filelist found!\n";
  }

  //initial celist====================================//
  nbodycemean tcl;
  nbodycemave tcm(init.get<std::string>("nroot"));

  //load celist=======================================//
  tcl.LoadList(init.get<std::string>("cemlist"));

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
    //When reach end, go out============================//
    if (fs.eof()) break;

    tcm.nb=rnb*tcm.ns;
    tcm.np=rnp*tcm.ns;
    //Find in root file=================================//
    std::string drawopt;
    drawopt="ns=="+to<std::string>(tcm.ns)+"&&np=="+to<std::string>(tcm.np)+"&&nb=="+to<std::string>(tcm.nb)+"&&rbar<="+to<std::string>(1.01*tcm.rbar)+"&&rbar>="+to<std::string>(0.99*tcm.rbar);
    if (isv4) drawopt=drawopt+"&&m1=="+to<std::string>(tcm.m1)+"&&p1=="+to<std::string>(tcm.p1);

    for (int it=0;it<15;it++) {
      std::string drawopti=drawopt+"&&type=="+to<std::string>(it+1);
      tcl.Draw(">>tlist",drawopti.c_str(),"entrylist");
      TEntryList *tel=(TEntryList*)gDirectory->Get("tlist");
      tcl.fchain->SetEntryList(tel);
      tcm.nmodel=tel->GetN();
      if (tcm.nmodel==0) continue;
      tcm.type=it+1;

      Double_t **ttype=new Double_t*[11];
      for (int j=0;j<11;j++) {
        ttype[j]=new Double_t[tcm.nmodel]; 
      }
      Double_t ttypem[11];
      Double_t ttype_err[11];
      
      memset(ttypem,0,sizeof(Double_t)*11);
      memset(ttype_err,0,sizeof(Double_t)*11);

      tcm.ntot=0;
      
      std::cout<<drawopti<<" Ntot:"<<tcm.nmodel<<std::endl;

      for (int j=0;j<tcm.nmodel;j++)  {
        int tj=tcl.GetListEntry(j,tel);
        tcl.GetEntry(tj);
        tcm.ntot +=tcl.ntot;
        for (int jj=0;jj<11;jj++) {
          ttypem[jj] +=tcl.ctime[jj];
          ttype[jj][j]=tcl.ctime[jj];
        }
      }

      tcm.ntot /=tcm.nmodel;

      for (int jj=0;jj<11;jj++) {
        ttypem[jj] /=(Double_t)tcm.nmodel;
        tcm.ctime[jj]=ttypem[jj];
        for (int j=0;j<tcm.nmodel;j++) {
          Double_t tmp=ttype[jj][j]-ttypem[jj];
          ttype_err[jj] +=tmp*tmp;
        }
        tcm.ctime_err[jj]=std::sqrt(ttype_err[jj]/(Double_t)tcm.nmodel);
      }
      tcm.Fill();
      tcl.fchain->SetEntryList(0);
      delete tel;
    }
  }
  tcm.Write("",TObject::kOverwrite);
  
  return 0; 
}
