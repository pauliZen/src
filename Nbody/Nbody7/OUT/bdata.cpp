#ifdef DEBUG
#include <iostream>
#endif
#include "cmath"
#include <string>
#include <sstream>
#include "TTree.h"
#include "TFile.h"

static Int_t fnum;
static std::string fsnum;
static TFile *f;
static TTree *trs;
static TTree *trc;
static TTree *tpars;
static  Int_t          nstar;
static  Double_t       t;    //time
static  Float_t        m;    //mass 
static  Float_t        r[4];    //position x,y,z,r
static  Float_t        v[4];    //velocity vx,vy,vz,v
static  Int_t          n;    //name
static  Int_t          kstar;   //star type
static  Int_t          ntot;   //total partical
static  Int_t          model;  //model
static  Int_t          nrun;   //nrun
static  Int_t          npairs;
static  Double_t        rbar;
static  Double_t        zmbar;
static  Double_t        rtide;
static  Double_t        tidal;
static  Double_t        rdens[3];
static  Double_t        ttotvstcr;
static  Double_t        tscale;
static  Double_t        vstar;
static  Double_t        rc;
static  Double_t        nc;
static  Double_t        vc;
static  Double_t        rhom;
static  Double_t        cmax;
static  Double_t        rscale;
static  Double_t        rsmin;
static  Double_t        dmin1;

extern "C"
{
  void bdata_init_(int *);
  void bdata_restart_(int *, int *);
  void bdata_header_(int *, int *, int *, double *);
  void bdata_body_(float *, float *, float *, float *, float *, float *, float *, int *, int *);
  void bdata_write_();
  void bdata_close_();
}

void trs_new()
{
  trs=new TTree("star","star data");
  trs->Branch("t",&t);
  trs->Branch("m",&m);
  trs->Branch("r",r,"r[4]/F");
  trs->Branch("v",v,"v[4]/F");
  trs->Branch("n",&n);
  trs->Branch("kstar",&kstar);
}

void trc_new()
{
  trc=new TTree("center","center data");
  trc->Branch("t",&t);
  trc->Branch("m",&m);
  trc->Branch("r",r,"r[4]/F");
  trc->Branch("v",v,"v[4]/F");
  trc->Branch("n",&n);
  trc->Branch("kstar",&kstar);
}

void tpars_new()
{
  tpars=new TTree("pars","parameters");
  tpars->Branch("t",&t);
  tpars->Branch("ntot",&ntot);
  tpars->Branch("model",&model);
  tpars->Branch("nrun",&nrun);
  tpars->Branch("npairs",&npairs);
  tpars->Branch("rbar",&rbar);
  tpars->Branch("zmbar",&zmbar);
  tpars->Branch("rtide",&rtide);
  tpars->Branch("tidal",&tidal);
  tpars->Branch("rdens",rdens,"rdens[3]/D");
  tpars->Branch("ttotvstcr",&ttotvstcr);
  tpars->Branch("tscale",&tscale);
  tpars->Branch("vstar",&vstar);
  tpars->Branch("rc",&rc);
  tpars->Branch("nc",&nc);
  tpars->Branch("vc",&vc);
  tpars->Branch("rhom",&rhom);
  tpars->Branch("cmax",&cmax);
  tpars->Branch("rscale",&rscale);
  tpars->Branch("rsmin",&rsmin);
  tpars->Branch("dmin1",&dmin1);
}  

//initial tree======================================//
void bdata_init_(int *ns)
{
#ifdef DEBUG
  std::cout<<"LW_OUT: initial begin\n";
#endif  
  f=new TFile("bdata1.root","create");
  f->cd();
  nstar=*ns;
  fnum=1;

  trs_new();
  trc_new();
  tpars_new();
  
#ifdef DEBUG
  std::cout<<"LW_OUT: initial successful\n";
#endif  
}

void bdata_restart_(int *ns, int *num)
{
  fnum=*num;
#ifdef DEBUG
  std::cout<<"LW_OUT: initial begin, num="<<fnum<<"\n";
#endif
  std::stringstream sstr;
  sstr.str("");
  sstr.clear();
  sstr<<fnum;
  sstr>>fsnum;
  f=new TFile(("bdata"+fsnum+".root").c_str(),"update");
  f->cd();
  nstar=*ns;
#ifdef DEBUG
  std::cout<<"before trs_new\n";
#endif  
  trs=(TTree*)gDirectory->Get("star");
  if (!trs) trs_new();
  else
  {
    trs->SetBranchAddress("t",&t);
    trs->SetBranchAddress("m",&m);
    trs->SetBranchAddress("r",r);
    trs->SetBranchAddress("v",v);
    trs->SetBranchAddress("n",&n);
    trs->SetBranchAddress("kstar",&kstar);
  }
  trc=(TTree*)gDirectory->Get("center");
  if (!trc) trc_new();
  else
  {
    trc->SetBranchAddress("t",&t);
    trc->SetBranchAddress("m",&m);
    trc->SetBranchAddress("r",r);
    trc->SetBranchAddress("v",v);
    trc->SetBranchAddress("n",&n);
    trc->SetBranchAddress("kstar",&kstar);
  }
  tpars=(TTree*)gDirectory->Get("pars");
  if (!tpars) tpars_new();
  else
  {
    tpars->SetBranchAddress("t",&t);
    tpars->SetBranchAddress("ntot",&ntot);
    tpars->SetBranchAddress("model",&model);
    tpars->SetBranchAddress("nrun",&nrun);
    tpars->SetBranchAddress("npairs",&npairs);
    tpars->SetBranchAddress("rbar",&rbar);
    tpars->SetBranchAddress("zmbar",&zmbar);
    tpars->SetBranchAddress("rtide",&rtide);
    tpars->SetBranchAddress("tidal",&tidal);
    tpars->SetBranchAddress("rdens",rdens);
    tpars->SetBranchAddress("ttotvstcr",&ttotvstcr);
    tpars->SetBranchAddress("tscale",&tscale);
    tpars->SetBranchAddress("vstar",&vstar);
    tpars->SetBranchAddress("rc",&rc);
    tpars->SetBranchAddress("nc",&nc);
    tpars->SetBranchAddress("vc",&vc);
    tpars->SetBranchAddress("rhom",&rhom);
    tpars->SetBranchAddress("cmax",&cmax);
    tpars->SetBranchAddress("rscale",&rscale);
    tpars->SetBranchAddress("rsmin",&rsmin);
    tpars->SetBranchAddress("dmin1",&dmin1);
  }
#ifdef DEBUG
  std::cout<<"LW_OUT: initial successful\n";
#endif  
}

//write header======================================//
void bdata_header_(int *nntot, int *mmodel, int *nnrun, double *as)
{
#ifdef DEBUG
  std::cout<<"LW_OUT: begin body input\n";
#endif  
  ntot=*nntot;
  model=*mmodel;
  nrun=*nnrun;
  t=as[0];
  npairs=(int)as[1];
  rbar=as[2];
  zmbar=as[3];
  rtide=as[4];
  tidal=as[5];
  rdens[0]=as[6];
  rdens[1]=as[7];
  rdens[2]=as[8];
  ttotvstcr=as[9];
  tscale=as[10];
  vstar=as[11];
  rc=as[12];
  nc=as[13];
  vc=as[14];
  rhom=as[15];
  cmax=as[16];
  rscale=as[17];
  rsmin=as[18];
  dmin1=as[19];
  tpars->Fill();
#ifdef DEBUG
  std::cout<<"LW_OUT: tpars fill once, NTOT="<<ntot<<"\n";
#endif
}

//write body========================================//
void bdata_body_(float *bodys, float *x, float *y, float *z, float *vx, float *vy, float *vz, int *name, int *kkstar)
{
  m=*bodys;
#ifdef DEBUG
  std::cout<<"LW_OUT: m fill once\n";
#endif    
  r[0]=*x;
  r[1]=*y;
  r[2]=*z;
  r[3]=sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
  v[0]=*vx;
  v[1]=*vy;
  v[2]=*vz;
  v[3]=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
  n=*name;
  kstar=*kkstar;
  if (n<=nstar) trs->Fill();
  else trc->Fill();
#ifdef DEBUG
  std::cout<<"LW_OUT: left body call\n";
#endif  
}

void bdata_write_()
{
  f->cd();
  trs->Write("",TObject::kOverwrite);
  trc->Write("",TObject::kOverwrite);
  tpars->Write("",TObject::kOverwrite);
  if (trs->GetEntries()/10000000>=fnum)
  {
    f->Close("R");
    fnum++;
    std::stringstream sstr;
    sstr.str("");
    sstr.clear();
    sstr<<fnum;
    sstr>>fsnum;
    f=new TFile(("bdata"+fsnum+".root").c_str(),"create");
    f->cd();
    trs_new();
    trc_new();
    tpars_new();
  }
}

void bdata_close_()
{
  f->cd();
  trs->Write("",TObject::kOverwrite);
  trc->Write("",TObject::kOverwrite);
  tpars->Write("",TObject::kOverwrite);
  delete trs;
  delete trc;
  delete tpars;
  f->Close("R");
  delete f;
}
