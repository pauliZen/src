//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug  3 15:28:40 2012 by ROOT version 5.32/01
// from TTree tri/test triple data
// found on file: test_body_0.root
//////////////////////////////////////////////////////////

#ifndef nbodyquater_h
#define nbodyquater_h

//My library========================================//
#include <nbodyqcr.h>
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

class nbodyquater : public nbodybase {
public :
  // Declaration of leaf types
  Double_t        t;
  Float_t         ecc1, pmin, semi, ecc;
  Float_t         m[4], x[4], y[4], z[4], vx[4], vy[4], vz[4];
  Int_t           n[4];

  // List of branches
  TBranch        *b_t, *b_ecc1, *b_pmin, *b_semi, *b_ecc, *b_m;   //!
  TBranch        *b_x, *b_y, *b_z, *b_vx, *b_vy, *b_vz, *b_n;   //!

  nbodyquater(): nbodybase("quat") { Link(); }
  //  virtual void   Fillqcr_once(nbodyqcr &qcr, Int_t entry, Int_t ntmp[4]);
  //  virtual Bool_t Fillqcr(nbodyqcr &qcr, Double_t deltat=0.1);
  virtual Bool_t Fillqcr(std::string filename);
protected:
  virtual void   Init();
};

//Members===========================================//
void nbodyquater::Init()
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
  fchain->SetBranchAddress("ecc1", &ecc1, &b_ecc1);
  fchain->SetBranchAddress("pmin", &pmin, &b_pmin);
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

/*
void nbodyquater::Fillqcr_once(nbodyqcr &qcr, Int_t entry, Int_t ntmp[4])
{
  fchain->GetEntry(entry-1);
  qcr.t[1]=t;
  qcr.ecc1[1]=ecc1;
  qcr.semi[1]=semi;
  qcr.pmin[1]=pmin;
  qcr.ecc[1]=ecc;
  qcr.Fill();
  fchain->GetEntry(entry);
  qcr.index=entry;
  qcr.t[0]=t;
  qcr.ecc1[0]=ecc1;
  qcr.semi[0]=semi;
  qcr.pmin[0]=pmin;
  qcr.ecc[0]=ecc;
  qcr.exchange=0;
  qcr.step=1;
  for (Int_t j=0;j<4;j++)
  {
    qcr.n[j]=n[j];
    qcr.m[j]=m[j];
  }
  if (!qcr.timebreak)
  {
    for (Int_t j=1;j<4;j++)
      ntmp[j]=qcr.n[j];
    piksrt(ntmp,4);
  }
}

Bool_t nbodyquater::Fillqcr(nbodyqcr &qcr, Double_t deltat)
{
  Double_t ttmp;
  Int_t ntmp[4];
  Int_t totnum=fchain->GetEntries();
  for (Int_t i=0;i<totnum;i++)
  {
    b_t->GetEntry(i);
    b_n->GetEntry(i);
    if (i==0)
    {
      fchain->GetEntry(i);
      for (Int_t j=0;j<4;j++)
      {
        qcr.n[j]=n[j];
        qcr.m[j]=m[j];
        ntmp[j]=n[j];
      }
      piksrt(ntmp,4);
      qcr.t[0]=t;
      ttmp=t;
      qcr.ecc1[0]=ecc1;
      qcr.semi[0]=semi;
      qcr.pmin[0]=pmin;
      qcr.ecc[0]=ecc;
      qcr.exchange=0;
      qcr.timebreak=0;
      qcr.index=0;
      qcr.step=1;
    }
    else if (((n[0]==qcr.n[0]&&n[1]==qcr.n[1])||(n[1]==qcr.n[0]&&n[0]==qcr.n[1]))&&((n[3]==qcr.n[3]&&n[2]==qcr.n[2])||(n[3]==qcr.n[2]&&n[2]==qcr.n[3])))
    {
      if (t-ttmp>deltat)
      {
        qcr.timebreak=1;
        Fillqcr_once(qcr,i,ntmp);
        ttmp=t;
      }
      else
      {
        qcr.step++;
        ttmp=t;
      }
    }
    else
    {
      piksrt(n,4);
      if (n[0]==ntmp[0]&&n[1]==ntmp[1]&&n[2]==ntmp[2]&&n[3]==ntmp[3])
      {
        if (t-ttmp>deltat)
        {
          qcr.timebreak=1;
          qcr.exchange=1;
          Fillqcr_once(qcr,i,ntmp);
          ttmp=t;
        }
        else
        {
          qcr.exchange=1;
          ttmp=t;
          qcr.step++;
        }
      }
      else
      {
        Fillqcr_once(qcr,i,ntmp);
        qcr.timebreak=0;
        ttmp=t;
      }
    }
  }
  qcr.Write("",TObject::kOverwrite);
}
*/

Bool_t nbodyquater::Fillqcr(std::string filename)
{
  if (endns<=0)
  {
    std::cerr<<"Error: number of star/planet/binary not set\n";
    return 0;
  }
  Int_t totnum=fchain->GetEntries();
  std::string tname[3]={"ssss","sssp","spsp"};
  std::vector<bodysort> tbody[3]; 
  for (Int_t i=0; i<totnum; i++)
  {
    fchain->GetEntry(i);
    bodysort btp(n[0], n[1], n[2], n[3], pmin, i);
    if (selstar(n,0)&&selstar(n,1)&&selstar(n,2)&&selstar(n,3)) tbody[0].push_back(btp);
    else if ((selstar(n,0)&&selstar(n,1)&&((selstar(n,2)&&selplanet(n,3))||(selplanet(n,2)&&selstar(n,3))))||(selstar(n,2)&&selstar(n,3)&&((selstar(n,0)&&selplanet(n,1))||(selplanet(n,0)&&selstar(n,1))))) tbody[1].push_back(btp);
    else if (((selstar(n,0)&&selplanet(n,1))||(selplanet(n,0)&&selstar(n,1)))&&((selstar(n,2)&&selplanet(n,3))||(selplanet(n,2)&&selstar(n,3)))) tbody[2].push_back(btp);
  }
  std::vector<bodysort>::iterator u;
  for (Int_t i=0; i<3; i++)
  {
    std::sort(tbody[i].begin(),tbody[i].end(),bodyshort);
    u=std::unique(tbody[i].begin(),tbody[i].end(),bodyequal);
    tbody[i].erase(u,tbody[i].end());
    std::sort(tbody[i].begin(),tbody[i].end(),indexshort);
    nbodyqcr qcrn(tname[i],filename);
    if (qcrn.Identify()==1)
    {
      for (size_t j=0; j<tbody[i].size(); j++)
      {
        qcrn.index=tbody[i][j].index;
        fchain->GetEntry(tbody[i][j].index);
        for (int jj=0;jj<4;jj++)
        {
          qcrn.n[jj]=n[jj];
          qcrn.m[jj]=m[jj];
          qcrn.x[jj]=x[jj];
          qcrn.y[jj]=y[jj];
          qcrn.z[jj]=z[jj];
          qcrn.vx[jj]=vx[jj];
          qcrn.vy[jj]=vy[jj];
          qcrn.vz[jj]=vz[jj];
        }
        qcrn.t=t;
        qcrn.ecc1=ecc1;
        qcrn.pmin=pmin;
        qcrn.semi=semi;
        qcrn.ecc=ecc;
        qcrn.Fill();
      }
      qcrn.Write("",TObject::kOverwrite);
    }
    else
    {
      std::cerr<<"Error: "<<tname[i]<<" tree exist in "<<filename<<std::endl;
      return 0;
    }
  }
  return 1;
}

#endif
