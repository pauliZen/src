#include "uftools.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "TFile.h"
#include "nbodyout.h"
#include "nbodyhfm.h"
#include "nbodytriple.h"
#include "nbodytcr.h"
#include "nbodyquater.h"
#include "nbodyqcr.h"
#include "nbodysingle.h"
#include "nbodyscr.h"
#include "bodysort.h"

int main(int argc, char *argv[])
{
  if (argc==3)
  {
    Float_t ratiop,ratiob;
    Int_t ns,np,nb;
    std::ifstream list((to<std::string>(argv[1])).c_str());
    std::string filedir=to<std::string>(argv[2]);
    if (list.is_open())
    {
      std::string nowdir;
      int number;
      while (!list.eof())
      {
        list>>number;
        list>>nowdir;
        list>>ns;
        list>>ratiob;
        list>>ratiop;
        np=ns*ratiop;
        nb=ns*ratiob;
        if (list.eof()) break;
        if (number==3||number==4)
        {
          //hfm===============================================//
          nbodyout nout;
          if (nout.LoadFile(nowdir+"_out3_0.root"))
          {
            nbodyhfm nhfm(filedir+nowdir+"_hfm.root");
            nout.Fillhfm(nhfm);
            std::cout<<nowdir+"hfm Finished\n";
          }
          else std::cerr<<"Error: cannot load out3 root File "<<nowdir<<std::endl;
          //single============================================//
          nbodysingle single;
          if (single.LoadFile(nowdir+"_single_0.root"))
          {
            single.setinit(ns,np,nb);
            single.Fillscr(filedir+nowdir+"_scr.root");
            std::cout<<nowdir+"scr Finished\n";
          }
          else std::cerr<<"Error: cannot load single root File "<<nowdir<<std::endl;
        }
        if (number==4)
        {
          //tcr===============================================//
          nbodytriple tri;
          if (tri.LoadFile(nowdir+"_body_0.root"))
          {
            tri.setinit(ns,np,nb);
            tri.Filltcr(filedir+nowdir+"_tcr.root");
            std::cout<<nowdir+"tcr Finished\n";
          }
          else std::cerr<<"Error: cannot load body root File "<<nowdir<<std::endl;
          //qcr===============================================//
          nbodyquater quat;
          if (quat.LoadFile(nowdir+"_body_0.root"))
          {
            quat.setinit(ns,np,nb);
            quat.Fillqcr(filedir+nowdir+"_qcr.root");
            std::cout<<nowdir+"qcr Finished\n";
          }
          else std::cerr<<"Error: cannot load body root File "<<nowdir<<std::endl;
        }
      }
    }
    else std::cerr<<"Error: listfile cannot open.\n";
  }
  else std::cerr<<"Error: No listfile input.\n";
  return 0;
}
