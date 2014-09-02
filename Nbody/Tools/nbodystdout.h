#ifndef nbodystdout_h
#define nbodystdout_h

#include <string>
#include <nbodytools.h>
#include <TROOT.h>
#include <TChain.h>

class nbodystdout: public nbodytools {
public:
  TChain        *tpars;   //pars chain

  Double_t       t;    //time
  Float_t        m;    //mass 
  Float_t        r[4];    //position x,y,z,r
  Float_t        v[4];    //velocity vx,vy,vz,v
  Int_t          n;    //name
  Int_t          kstar;   //star type

  Int_t          ntot;   //total partical
  Int_t          model;  //model
  Int_t          nrun;   //nrun
  //  Float_t        as[20];  //as
  //  Float_t        ttot;
  Int_t          npairs;
  Double_t       rbar;
  Double_t       zmbar;
  Double_t       rtide;
  Double_t       tidal;
  Double_t       rdens[3];
  Double_t       ttotvstcr;
  Double_t       tscale;
  Double_t       vstar;
  Double_t       rc;
  Double_t       nc;
  Double_t       vc;
  Double_t       rhom;
  Double_t       cmax;
  Double_t       rscale;
  Double_t       rsmin;
  Double_t       dmin1;

  // List of branches
  TBranch        *b_t, *b_m, *b_r, *b_v, *b_n, *b_kstar;   
  TBranch        *b_pt, *b_ntot, *b_model, *b_nrun;
  TBranch        *b_npairs, *b_rbar, *b_zmbar, *b_rtide, *b_tidal, *b_rdens, *b_ttotvstcr;
  TBranch        *b_tscale, *b_vstar, *b_prc, *b_pnc, *b_pvc, *b_rhom, *b_cmax, *b_rscale, *b_rsmin, *b_dmin1;

  nbodystdout(std::string treename): nbodytools(treename) { Init();}
  virtual Bool_t LoadFile(std::string filename);

protected:
  void Init();
};

void nbodystdout::Init()
{
  state=2;
  fchain=new TChain(treename.c_str());
  fchain->SetBranchAddress("t", &t, &b_t);
  fchain->SetBranchAddress("m", &m, &b_m);
  fchain->SetBranchAddress("r", r, &b_r);
  fchain->SetBranchAddress("v", v, &b_v);
  fchain->SetBranchAddress("n", &n, &b_n);
  fchain->SetBranchAddress("kstar", &kstar, &b_kstar);

  tpars = new TChain("pars");
  tpars->SetBranchAddress("t",&t, &b_pt);
  tpars->SetBranchAddress("ntot",&ntot,&b_ntot);
  tpars->SetBranchAddress("model",&model,&b_model);
  tpars->SetBranchAddress("nrun",&nrun,&b_nrun);
  tpars->SetBranchAddress("npairs",&npairs,&b_npairs);
  tpars->SetBranchAddress("rbar",&rbar,&b_rbar);
  tpars->SetBranchAddress("zmbar",&zmbar,&b_zmbar);
  tpars->SetBranchAddress("rtide",&rtide,&b_rtide);
  tpars->SetBranchAddress("tidal",&tidal,&b_tidal);
  tpars->SetBranchAddress("rdens",rdens,&b_rdens);
  tpars->SetBranchAddress("ttotvstcr",&ttotvstcr,&b_ttotvstcr);
  tpars->SetBranchAddress("tscale",&tscale,&b_tscale);
  tpars->SetBranchAddress("vstar",&vstar,&b_vstar);
  tpars->SetBranchAddress("rc",&rc,&b_prc);
  tpars->SetBranchAddress("nc",&nc,&b_pnc);
  tpars->SetBranchAddress("vc",&vc,&b_pvc);
  tpars->SetBranchAddress("rhom",&rhom,&b_rhom);
  tpars->SetBranchAddress("cmax",&cmax,&b_cmax);
  tpars->SetBranchAddress("rscale",&rscale,&b_rscale);
  tpars->SetBranchAddress("rsmin",&rsmin,&b_rsmin);
  tpars->SetBranchAddress("dmin1",&dmin1,&b_dmin1);
#ifdef DEBUG
  std::cout<<"stdout initial "<<treename<<"\n";
#endif  
}

Bool_t nbodystdout::LoadFile(std::string filename)
{
  fchain->AddFile(filename.c_str());
#ifdef DEBUG
  std::cout<<"LoadFile "<<filename<<" for chain\n";
#endif  
  tpars->AddFile(filename.c_str());
#ifdef DEBUG
  std::cout<<"LoadFile "<<filename<<" for pars\n";
#endif  
  if (!fchain->GetEntries()) return 0;
  if (!tpars->GetEntries()) return 0;
  return 1;
}

#endif
