#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include <uftools.h>
#include <initial.h>

#include "TTree.h"
#include "TFile.h"

struct data{
  int pnum;
  int nbnum;
  double tbar[4];
  double tnbint;
  double tpre;
  double time;
};

int main(int argc, char* argv[]) {
  pars_initial init(".bartoroot_config");
  init.add("datlst","first line show file number, data lst","fort.lst");
  init.add("wcl","reading line number",(int)100);
  init.add("output","root file name","data.root");
  init.initial(argc,argv);
  
  ifstream f(init.gets("datlst").c_str());

  if(!f.is_open()) {
    std::cerr<<"Error: No file list found!\n";
    return 0;
  }

  int fnum,fln;

  f>>fnum;
  fln=init.geti("wcl");

  std::string *fname=new std::string[fnum];
  
  data **lst=new data*[fnum];
  int pnum,nbnum,rank,index;
  double tbarb,tbara,tbar1,tbar2,tnbint,tpre,time;
  float nbsigma,nbsratio;

  TFile* tf=new TFile(init.gets("output").c_str(),"create");
  TTree* tr=new TTree("data","data of n, nb, tbar and time");
  tr->Branch("rank",&rank);
  tr->Branch("i",&index);
  tr->Branch("p",&pnum);
  tr->Branch("nb",&nbnum);
  tr->Branch("tbarb",&tbarb);
  tr->Branch("tbara",&tbara);
  tr->Branch("tbar1",&tbar1);
  tr->Branch("tbar2",&tbar2);
  tr->Branch("tnbint",&tnbint);
  tr->Branch("tnbpre",&tpre);
  tr->Branch("time",&time);
  tr->Branch("nbsigma",&nbsigma);
  tr->Branch("nbsratio",&nbsratio);
  
  for (int i=0;i<fnum;i++) {
    f>>fname[i];
    lst[i]=new data[fln];

    if ( freopen(fname[i].c_str(),"r",stdin) == NULL) {
      std::cerr<<"Error, file "<<fname[i]<<" not found!\n";
      return 0;
    }
    for (int j=0;j<fln;j++) {
      scanf("%d %d %lg %lg %lg %lg %lg %lg %lg",
            &lst[i][j].pnum,&lst[i][j].nbnum,&lst[i][j].tbar[0],&lst[i][j].tbar[1],&lst[i][j].tbar[2],&lst[i][j].tbar[3],&lst[i][j].tnbint,&lst[i][j].tpre,&lst[i][j].time);
    }
    // for (int j=0;j<fln;j++) {
      // scanf("%d %d %lg %lg %lg %lg %lg",
      //       &pnum,&nbnum,&tbarb,&tbara,&tbar1,&tnbint,&time);
      // tr->Fill();
    // }
  }

  float *nsigma=new float[fln];
  int *nmean=new int[fln];
  float *nratio=new float[fln];
  for (int j=0;j<fln;j++){
    nmean[j]=0;
    for (int i=0;i<fnum;i++) {
      nmean[j] +=lst[i][j].nbnum;
    }
    nmean[j] /=fnum;
    nsigma[j]=0;
    for (int i=0;i<fnum;i++) {
      int n2tmp=lst[i][j].nbnum-nmean[j];
      nsigma[j] +=n2tmp*n2tmp;
    }
    nsigma[j] =sqrt(nsigma[j])/fnum;
    nratio[j]=nsigma[j]/(float)nmean[j];
  }

  for (int j=0;j<fln;j++) {
    nbsigma=nsigma[j];
    nbsratio=nratio[j];
    index=j;
    for (int i=0;i<fnum;i++){
      rank=i;
      pnum=lst[i][j].pnum;
      nbnum=lst[i][j].nbnum;
      tbarb=lst[i][j].tbar[0];
      tbara=lst[i][j].tbar[1];
      tbar1=lst[i][j].tbar[2];
      tbar2=lst[i][j].tbar[3];
      tnbint=lst[i][j].tnbint;
      tpre=lst[i][j].tpre;
      time=lst[i][j].time;
      tr->Fill();
    }
  }
  
  tr->Write("",TObject::kOverwrite);
  tf->Close();
  
  return 0;
}
