//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug  3 15:28:40 2012 by ROOT version 5.32/01
// from TTree single/test single data
// found on file: test_body_0.root
//////////////////////////////////////////////////////////

#ifndef nbodysingle_h
#define nbodysingle_h

//My library========================================//
#include <nbodyscr.h>
#include <nbodybase.h>
#include <uftools.h>
#include <bodysort.h>
//root library======================================//
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
//STL===============================================//
#include <string>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class nbodysingle : public nbodybase {
public :
  // Declaration of leaf types
  Double_t        t;
  Float_t         peri, semi, ecc;
  Float_t         m[2], x[3], y[3], z[3], vx[3], vy[3], vz[3];
  Int_t           n[2];

  // List of branches
  TBranch        *b_t, *b_peri, *b_semi, *b_ecc, *b_m;   //!
  TBranch        *b_x, *b_y, *b_z, *b_vx, *b_vy, *b_vz, *b_n;   //!

  nbodysingle(): nbodybase("sing") { Link(); }
  //  virtual void   Fillscr_once(nbodyscr &scr, Int_t entry);
  //  virtual Bool_t   Fillscr(nbodyscr &scr, Double_t deltat=0.1);
  virtual Bool_t Fillscr(std::string filename);
protected:
  virtual void     Init();
};

//Members===========================================//
void nbodysingle::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
  fchain->SetBranchAddress("t", &t, &b_t);
  fchain->SetBranchAddress("peri", &peri, &b_peri);
  fchain->SetBranchAddress("semi", &semi, &b_semi);
  fchain->SetBranchAddress("ecc", &ecc, &b_ecc);
  fchain->SetBranchAddress("m", m, &b_m);
  fchain->SetBranchAddress("x", x, &b_x);
  fchain->SetBranchAddress("y", y, &b_y);
  fchain->SetBranchAddress("z", z, &b_z);
  fchain->SetBranchAddress("vx", vx, &b_vx);
  fchain->SetBranchAddress("vy", vy, &b_vy);
  fchain->SetBranchAddress("vz", vz, &b_vz);
  fchain->SetBranchAddress("n", n, &b_n);
  //  Notify();
}

Bool_t nbodysingle::Fillscr(std::string filename)
{
  if (endns<=0)
  {
    std::cerr<<"Error: number of star/planet/binary not set\n";
    return 0;
  }
  Int_t totnum=fchain->GetEntries();
  std::string tname[3]={"ss","sp","pp"};
  std::vector<bodysort> tbody[3];
  for (Int_t i=0; i<totnum; i++)
  {
    fchain->GetEntry(i);
    bodysort btp(n[0], n[1], peri, i);
    if (selstar(n,0)&&selstar(n,1)) tbody[0].push_back(btp);
    else if ((selstar(n,0)&&selplanet(n,1))||(selplanet(n,0)&&selstar(n,1))) tbody[1].push_back(btp);
    else if (selplanet(n,0)&&selplanet(n,1)) tbody[2].push_back(btp);
  }
  std::vector<bodysort>::iterator u;
  for (Int_t i=0; i<3; i++)
  {
    std::sort(tbody[i].begin(),tbody[i].end(),bodyshort);
    u=std::unique(tbody[i].begin(),tbody[i].end(),bodyequal);
    tbody[i].erase(u,tbody[i].end());
    std::sort(tbody[i].begin(),tbody[i].end(),indexshort);
    nbodyscr scrn(tname[i],filename);
    if (scrn.Identify()==1)
    {
      for (size_t j=0; j<tbody[i].size(); j++)
      {
        scrn.index=tbody[i][j].index;
        fchain->GetEntry(tbody[i][j].index);
        for (int jj=0;jj<2;jj++)
        {
          scrn.n[jj]=n[jj];
          scrn.m[jj]=m[jj];
          scrn.x[jj]=x[jj];
          scrn.y[jj]=y[jj];
          scrn.z[jj]=z[jj];
          scrn.vx[jj]=vx[jj];
          scrn.vy[jj]=vy[jj];
          scrn.vz[jj]=vz[jj];
        }
        scrn.t=t;
        scrn.peri=peri;
        scrn.semi=semi;
        scrn.ecc=ecc;
        scrn.Fill();
      }
      scrn.Write("",TObject::kOverwrite);
    }
    else
    {
      std::cerr<<"Error: "<<tname[i]<<" tree exist in "<<filename<<std::endl;
      return 0;
    }
  }
  return 1;
}
  
/*
void nbodysingle::Fillscr_once(nbodyscr &scr, Int_t entry)
{
  fchain->GetEntry(entry-1);
  scr.t[1]=t;
  scr.semi[1]=semi;
  scr.peri[1]=peri;
  scr.ecc[1]=ecc;
  scr.Fill();
  fchain->GetEntry(entry);
  scr.index=entry;
  scr.t[0]=t;
  scr.semi[0]=semi;
  scr.peri[0]=peri;
  scr.ecc[0]=ecc;
  scr.step=1;
  for (Int_t j=0;j<2;j++)
  {
    scr.n[j]=n[j];
    scr.m[j]=m[j];
  }
}

Bool_t nbodysingle::Fillscr(nbodyscr &scr, Double_t deltat)
{
  Double_t ttmp;
  Int_t totnum=fchain->GetEntries();
  for (Int_t i=0;i<totnum;i++)
  {
    b_t->GetEntry(i);
    b_n->GetEntry(i);
    if (i==0)
    {
      fchain->GetEntry(i);
      for (Int_t j=0;j<2;j++)
      {
        scr.n[j]=n[j];
        scr.m[j]=m[j];
      }
      scr.t[0]=t;
      ttmp=t;
      scr.semi[0]=semi;
      scr.peri[0]=peri;
      scr.ecc[0]=ecc;
      scr.timebreak=0;
      scr.index=0;
      scr.step=1;
    }
    else if ((n[0]==scr.n[0]&&n[1]==scr.n[1])||(n[1]==scr.n[0]&&n[0]==scr.n[1]))
    {
      if (t-ttmp>deltat)
      {
        scr.timebreak=1;
        Fillscr_once(scr,i);
        ttmp=t;
      }
      else
      {
        scr.step++;
        ttmp=t;
      }
    }
    else
    {
      Fillscr_once(scr,i);
      scr.timebreak=0;
      ttmp=t;
    }
  }
  scr.Write("",TObject::kOverwrite);
}
*/
#endif
