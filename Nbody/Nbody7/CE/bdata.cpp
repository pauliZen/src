#ifdef DEBUG
#include <iostream>
#endif
#include "cmath"
#include "TTree.h"
#include "TFile.h"

static TFile *f;
static TTree *trs;
static TTree *trp;
static TTree *trc;
static TTree *tpars;
static  Int_t          nstar;
static  Int_t          nplanet;
static  Double_t        t;    //time
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
  void bdata_init_(int *, int *);
  void bdata_header_(int *, int *, int *, double *);
  void bdata_body_(float *, float *, float *, float *, float *, float *, float *, int *, int *);
  void bdata_close_();
}

//initial tree======================================//
void bdata_init_(int *ns, int *np)
{
#ifdef DEBUG
  std::cout<<"LW_OUT: initial begin\n";
#endif  
  f=new TFile("bdata.root","create");
  f->cd();
  trp=new TTree("planet","planet data");
  trs=new TTree("star","star data");
  trc=new TTree("center","center data");
  tpars=new TTree("pars","parameters");
  nstar=*ns;
  nplanet=*np+nstar;
  
  trs->Branch("t",&t);
  trs->Branch("m",&m);
  trs->Branch("r",r,"r[4]/F");
  trs->Branch("v",v,"v[4]/F");
  trs->Branch("n",&n);
  trs->Branch("kstar",&kstar);
  trp->Branch("t",&t);
  trp->Branch("m",&m);
  trp->Branch("r",r,"r[4]/F");
  trp->Branch("v",v,"v[4]/F");
  trp->Branch("n",&n);
  trp->Branch("kstar",&kstar);
  trc->Branch("t",&t);
  trc->Branch("m",&m);
  trc->Branch("r",r,"r[4]/F");
  trc->Branch("v",v,"v[4]/F");
  trc->Branch("n",&n);
  trc->Branch("kstar",&kstar);
    
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
  else if (n<=nplanet) trp->Fill();
  else trc->Fill();
#ifdef DEBUG
  std::cout<<"LW_OUT: left body call\n";
#endif  
}

void bdata_close_()
{
  f->cd();
  trs->Write("",TObject::kOverwrite);
  trp->Write("",TObject::kOverwrite);
  trc->Write("",TObject::kOverwrite);
  tpars->Write("",TObject::kOverwrite);
  delete trs;
  delete trp;
  delete trc;
  delete tpars;
  f->Close("R");
  delete f;
}
