#ifndef nbodyce_h
#define nbodyce_h

//Mylibrary=========================================//
#include <nbodybase.h>
//root library======================================//
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
//STL===============================================//
#include <string>
#ifdef DEBUG
#include <iostream>
#endif

class nbodyce: public nbodybase{
public:
  Double_t x[3][3], v[3][3], m[4], ecc[3], peri[3], semi[3], t[3], E[3];
  Double_t vinf[3], vp[3], bip[3];
  Double_t rau, rbar, tstar, zmbar, vstar;
  Bool_t exchange;
  Int_t name[4], type;

  TChain *funit;
  
  TBranch  *b_x, *b_v, *b_m, *b_ecc, *b_peri, *b_semi, *b_t, *b_E, *b_vinf, *b_vp, *b_bip;
  TBranch  *b_rau, *b_rbar, *b_tstar, *b_zmbar, *b_vstar;
  TBranch  *b_exchange, *b_name, *b_type;

  nbodyce(): nbodybase("ce") { Link(); }
  nbodyce(std::string filename): nbodybase("ce") { Link(); LoadFile(filename); }
  virtual ~nbodyce();

  virtual void Link();
  virtual Bool_t LoadFile(std::string filename);

protected:
  virtual void Init();
};

void nbodyce::Link()
{
  funit=new TChain("unit");
  funit->SetMakeClass(1);
  fchain=new TChain(treename.c_str());
  fchain->SetMakeClass(1);
  Init();
}

void nbodyce::Init()
{
  fchain->SetBranchAddress("name",name,&b_name);
  fchain->SetBranchAddress("type",&type,&b_type);
  fchain->SetBranchAddress("t",t,&b_t);
  fchain->SetBranchAddress("x",x,&b_x);
  fchain->SetBranchAddress("v",v,&b_v);
  fchain->SetBranchAddress("m",m,&b_m);
  fchain->SetBranchAddress("ecc",ecc,&b_ecc);
  fchain->SetBranchAddress("peri",peri,&b_peri);
  fchain->SetBranchAddress("semi",semi,&b_semi);
  fchain->SetBranchAddress("exchange",&exchange,&b_exchange);
  fchain->SetBranchAddress("E",E,&b_E);
  fchain->SetBranchAddress("bip",bip,&b_bip);
  fchain->SetBranchAddress("vinf",vinf,&b_vinf);
  fchain->SetBranchAddress("vp",vp,&b_vp);
  funit->SetBranchAddress("rau",&rau,&b_rau);
  funit->SetBranchAddress("rbar",&rbar,&b_rbar);
  funit->SetBranchAddress("tstar",&tstar,&b_tstar);
  funit->SetBranchAddress("zmbar",&zmbar,&b_zmbar);
  funit->SetBranchAddress("vstar",&vstar,&b_vstar);
#ifdef DEBUG
  std::cout<<"Chain ce & unit build.\n";
#endif  
}

nbodyce::~nbodyce()
{
  if (!fchain) return;
  delete fchain->GetCurrentFile();
  if (!funit) return;
  delete funit->GetCurrentFile();
}

Bool_t nbodyce::LoadFile(std::string filename)
{
  fchain->AddFile(filename.c_str());
  if (!fchain->GetEntries()) return 0;
  funit->AddFile(filename.c_str());
  if (!funit->GetEntries()) return 0;
  funit->GetEntry(0);
  return 1;
#ifdef DEBUG
  std::cout<<"Entries: "<<fchain->GetEntries();
#endif  
}

#endif
