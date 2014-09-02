//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug  3 15:28:40 2012 by ROOT version 5.32/01
// from TTree tri/test triple data
// found on file: test_body_0.root
//////////////////////////////////////////////////////////

#ifndef nbodytriple_h
#define nbodytriple_h

//My library========================================//
#include <nbodytcr.h>
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

class nbodytriple : public nbodybase {
public :
  // Declaration of leaf types
  Double_t        t;
  Float_t         ecc1, pmin, semi, ecc;
  Float_t         m[3], x[3], y[3], z[3], vx[3], vy[3], vz[3];
  Int_t           n[3];

  // List of branches
  TBranch        *b_t, *b_ecc1, *b_pmin, *b_semi, *b_ecc, *b_m;   //!
  TBranch        *b_x, *b_y, *b_z, *b_vx, *b_vy, *b_vz, *b_n;   //!

  nbodytriple(): nbodybase("tri") { Link(); }
  //  virtual void   Filltcr_once(nbodytcr &tcr, Int_t entry);
  //  virtual Bool_t Filltcr(nbodytcr &tcr, Double_t deltat=0.1);
  virtual Bool_t Filltcr(std::string filename);
protected:
  virtual void   Init();
};

//Members===========================================//
void nbodytriple::Init()
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

// void nbodytriple::Filltcr_once(nbodytcr &tcr, Int_t entry)
// {
//   fchain->GetEntry(entry-1);
//   tcr.t[1]=t;
//   tcr.ecc1[1]=ecc1;
//   tcr.semi[1]=semi;
//   tcr.pmin[1]=pmin;
//   tcr.ecc[1]=ecc;
//   tcr.Fill();
//   fchain->GetEntry(entry);
//   tcr.index=entry;
//   tcr.t[0]=t;
//   tcr.ecc1[0]=ecc1;
//   tcr.semi[0]=semi;
//   tcr.pmin[0]=pmin;
//   tcr.ecc[0]=ecc;
//   tcr.exchange=0;
//   tcr.step=1;
//   for (Int_t j=0;j<3;j++)
//   {
//     tcr.n[j]=n[j];
//     tcr.m[j]=m[j];
//   }
// }

// Bool_t nbodytriple::Filltcr(nbodytcr &tcr, Double_t deltat)
// {
//   Double_t ttmp;
//   Int_t totnum=fchain->GetEntries();
//   for (Int_t i=0;i<totnum;i++)
//   {
//     b_t->GetEntry(i);
//     b_n->GetEntry(i);
//     if (i==0)
//     {
//       fchain->GetEntry(i);
//       for (Int_t j=0;j<3;j++)
//       {
//         tcr.n[j]=n[j];
//         tcr.m[j]=m[j];
//       }
//       tcr.t[0]=t;
//       ttmp=t;
//       tcr.ecc1[0]=ecc1;
//       tcr.semi[0]=semi;
//       tcr.pmin[0]=pmin;
//       tcr.ecc[0]=ecc;
//       tcr.exchange=0;
//       tcr.timebreak=0;
//       tcr.index=0;
//       tcr.step=1;
//     }
//     else if (n[0]==tcr.n[0]&&((n[1]==tcr.n[1]&&n[2]==tcr.n[2])||(n[1]==tcr.n[2]&&n[2]==tcr.n[1])))
//     {
//       if (t-ttmp>deltat)
//       {
//         tcr.timebreak=1;
//         Filltcr_once(tcr,i);
//         ttmp=t;
//       }
//       else
//       {
//         tcr.step++;
//         ttmp=t;
//       }
//     }
//     else if ((n[1]==tcr.n[0]&&((n[2]==tcr.n[1]&&n[0]==tcr.n[2])||(n[2]==tcr.n[2]&&n[0]==tcr.n[1])))||(n[2]==tcr.n[0]&&((n[1]==tcr.n[1]&&n[0]==tcr.n[2])||(n[1]==tcr.n[2]&&n[0]==tcr.n[1]))))
//     {
//       if (t-ttmp>deltat)
//       {
//         tcr.timebreak=1;
//         tcr.exchange=1;
//         Filltcr_once(tcr,i);
//         ttmp=t;
//       }
//       else
//       {
//         tcr.exchange=1;
//         ttmp=t;
//         tcr.step++;
//       }
//     }
//     else
//     {
//       Filltcr_once(tcr,i);
//       tcr.timebreak=0;
//       ttmp=t;
//     }
//   }
//   tcr.Write("",TObject::kOverwrite);
// }

Bool_t nbodytriple::Filltcr(std::string filename)
{
  if (endns<=0)
  {
    std::cerr<<"Error: number of star/planet/binary not set\n";
    return 0;
  }
  Int_t totnum=fchain->GetEntries();
  std::string tname[4]={"sss","ssp","psp","pss"};
  std::vector<bodysort> tbody[4];  //0:sss, 1:ssp, 2:psp, 3:pss;
  for (Int_t i=0; i<totnum; i++)
  {
    fchain->GetEntry(i);
    bodysort btp(n[0], n[1], n[2], pmin, i);
    if (selstar(n,0)&&selstar(n,1)&&selstar(n,2)) tbody[0].push_back(btp);
    else if (selstar(n,0)&&((selstar(n,1)&&selplanet(n,2))||(selplanet(n,1)&&selstar(n,2)))) tbody[1].push_back(btp);
    else if (selplanet(n,0)&&((selstar(n,1)&&selplanet(n,2))||(selplanet(n,1)&&selstar(n,2)))) tbody[2].push_back(btp);
    else if (selplanet(n,0)&&selstar(n,1)&&selstar(n,2)) tbody[3].push_back(btp);
  }
  std::vector<bodysort>::iterator u;
  for (Int_t i=0; i<4; i++)
  {
    std::sort(tbody[i].begin(),tbody[i].end(),bodyshort);
    u=std::unique(tbody[i].begin(),tbody[i].end(),bodyequal);
    tbody[i].erase(u,tbody[i].end());
    std::sort(tbody[i].begin(),tbody[i].end(),indexshort);
    nbodytcr tcrn(tname[i],filename);
    if (tcrn.Identify()==1)
    {
      for (size_t j=0; j<tbody[i].size(); j++)
      {
        tcrn.index=tbody[i][j].index;
        fchain->GetEntry(tbody[i][j].index);
        for (int jj=0;jj<3;jj++)
        {
          tcrn.n[jj]=n[jj];
          tcrn.m[jj]=m[jj];
          tcrn.x[jj]=x[jj];
          tcrn.y[jj]=y[jj];
          tcrn.z[jj]=z[jj];
          tcrn.vx[jj]=vx[jj];
          tcrn.vy[jj]=vy[jj];
          tcrn.vz[jj]=vz[jj];
        }
        tcrn.t=t;
        tcrn.ecc1=ecc1;
        tcrn.pmin=pmin;
        tcrn.semi=semi;
        tcrn.ecc=ecc;
        tcrn.Fill();
      }
      tcrn.Write("",TObject::kOverwrite);
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
