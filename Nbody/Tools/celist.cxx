#include <nbodycelist.h>
#include <nbodyce.h>
#include <initial.h>

#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  pars_initial init(".celist_config");
  init.add("vtype","velocity of planets distribution type: 0 or 4",(int)0);
  init.add("flist","filelist to chain: format: filename pars(ns rbar nbr npr [m1 p1] rands)","filelist");
  init.add("rootname","root name to store","celist.root");
  init.initial(argc,argv);

  ifstream fl(init.gets("flist").c_str());
  if (!fl.is_open())
  {
    std::cerr<<"Error: filelist not found!\n";
    return 0;
  }

  nbodycelist tcl(init.gets("rootname"));
  std::string filename;
  Double_t rbar, npr, nbr, m1=0, p1=0;
  Int_t ns, np, nb, rands;
  while (1)
  {
    fl>>filename;
    fl>>ns;
    fl>>rbar;
    fl>>nbr;
    fl>>npr;
    if (init.geti("vtype")==4)
    {
      fl>>m1;
      fl>>p1;
    }
    fl>>rands;
    if (fl.eof()) break;
    tcl.ns=ns;
    tcl.np=ns*npr;
    tcl.nb=ns*nbr;
    tcl.rbar=rbar;
    tcl.model=rands;
    tcl.m1=m1;
    tcl.p1=p1;
    nbodyce tc(filename+"/ce.root");
    for (int i=0; i<tc.GetEntries();i++)
    {
      int nt=tcl.ns+tcl.nb;
      int na=nt+tcl.np;
      tcl.LoadData(tc,i);
      if(tcl.name[0]==0||tcl.name[1]==0) tcl.type=16;
      else if(tcl.type>3&&tcl.name[2]==0) tcl.type=17;
      else if(tcl.type>9&&tcl.name[3]==0) tcl.type=18;
      else if(tcl.name[0]>na||tcl.name[1]>na) tcl.type=19;
      else if(tcl.type>3&&tcl.name[2]>na) tcl.type=20;
      else if(tcl.type>9&&tcl.name[3]>na) tcl.type=21;
      if(tcl.type==9&&(tcl.name[1]<=nt||tcl.name[2]<=nt)) tcl.type=7;
      if(tcl.type==15) {
        int n1,n2,n3,n4;
        if(tcl.name[0]>tcl.name[1]) {
          n1=tcl.name[1];
          n2=tcl.name[0];
        }
        else{
          n1=tcl.name[0];
          n2=tcl.name[1];
        }
        if(tcl.name[2]>tcl.name[3]) {
          n3=tcl.name[3];
          n4=tcl.name[2];
        }
        else{
          n3=tcl.name[2];
          n4=tcl.name[3];
        }
        if(n1<=nt&&n2>nt&&n4<=nt) tcl.type=11;
        if(n1>nt&&n3<=nt&&n4>nt) tcl.type=14;
        if(n1>nt&&n4<=nt) tcl.type=13;
      }
      tcl.Fill();
    }
#ifdef DEBUG
    std::cout<<"Filename: "<<filename<<"; Entries: "<<tcl.GetEntries()<<std::endl;
#endif    
  }
  tcl.Write("",TObject::kOverwrite);
  return 0;
}
