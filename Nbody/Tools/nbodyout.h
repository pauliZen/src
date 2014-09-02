//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul  6 09:03:34 2012 by ROOT version 5.32/01
// from TTree out3/test_new OUT3 data
// found on file: test_new_out3.root
//////////////////////////////////////////////////////////
//--07/07/12 19:54-finish change------------------------//
//Myout3: a class used to analyze out3.root=========//
//Constructer: (TFile *f, Double_t ts, Int_t ns,====//
//              Int_t np): open out3/pars/scal tree //
//              in f, link all branch, let scale====//
//              pars get their values===============//
//Member Function: =================================//
//(Int)calc: (TFile *f)calculate halfmass radius and//
//           number vs t, store in new root file f  //
/////////////////////////////////////////////////////////
//--07/31/12 0:14-Change completely--------------------//
//==nbodyout: class to read out3.root===============//
//Construct: link all members
//Member: (TChain*)trstar/p/c, tpars, tscal
//        (Float_t)t,m,r[4],v[4],as[20]
//        (Int_t)n,kstar,ntot,model,nrun,nk
//        (Double_t)tscale,zmbar,rbar,vstar
//        (TBranch*) ***
//Function:
//(void)TstepLoop (Tcut*, LoopFunc, nbodyout&):
//          Loop all timestep for stars and planets,
//-(Bool)LoopFunc: Bool_t() *(const Int_t & starnum,
//           TEntryList *starlist, const Int_t
//           & planetnum, TEntryList *planetlist,
//           nbodyout &)
//          will work in each step
//(Int)GetEntry (str name, Long64_t entry): get entry
//(void)Show (str name, Long64_t entry=-1): show
//(Bool)Fillhfm (nbodyhfmv &hfm): to fill hfm new tree.


#ifndef nbodyout_h
#define nbodyout_h

//My library========================================//
#include <uftools.h>
#include <nbodyhfm.h>

//root library======================================//
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TEntryList.h>
//STL===============================================//
#include <iostream>
#include <string>

// Header file for the classes stored in the TTree if any.
// Fixed size dimensions of array or collections stored in the TTree if any.
class nbodyout {
public :
  //Friend============================================//
friend class nbodyhfm;

  TChain          *trstar;   //out3 star chain
  TChain          *trplanet;   //out3 planet chain
  TChain          *trcenter;   //out3 center mass chain
  TChain          *tpars;   //pars chain
  //  TChain          *tscal;   //scal chain

  // Declaration of leaf types
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

  // Double_t       tscale;   //time scale
  // Double_t       zmbar;   //mass scale
  // Double_t       rbar;    //distance scale
  // Double_t       vstar;   //velocity scale

  // List of branches
  TBranch        *b_ts, *b_ms, *b_rs, *b_vs, *b_ns, *b_kstars;   
  TBranch        *b_tp, *b_mp, *b_rp, *b_vp, *b_np, *b_kstarp;
  TBranch        *b_tc, *b_mc, *b_rc, *b_vc, *b_nc, *b_kstarc;   
  TBranch        *b_t, *b_ntot, *b_model, *b_nrun;
  TBranch        *b_npairs, *b_rbar, *b_zmbar, *b_rtide, *b_tidal, *b_rdens, *b_ttotvstcr;
  TBranch        *b_tscale, *b_vstar, *b_prc, *b_pnc, *b_pvc, *b_rhom, *b_cmax, *b_rscale, *b_rsmin, *b_dmin1;
  //TBranch        *b_tscale, *b_zmbar, *b_rbar, *b_vstar;

  typedef Bool_t (*LoopFunc) (const Int_t &, TEntryList *,const Int_t &, TEntryList *, nbodyout &);

  //Function==========================================//
  nbodyout();                //Link all member
  virtual ~nbodyout();       
  virtual Bool_t LoadFile(std::string file);    //Load root fro Chain
  virtual void TstepLoop(LoopFunc infunc, nbodyout &nout, const std::string& cut="");    //Loop for stars and planets timestep
  virtual Int_t GetEntry(std::string name,Long64_t entry);    //name : star/p/c, pars, scal
  virtual Int_t GetEntries(std::string name);    //name : star/p/c, pars, scal
  virtual void Show(std::string name,Long64_t entry = -1);
  //  virtual Int_t    Cut(Long64_t entry);
  //  virtual Long64_t LoadTree(Long64_t entry);
  //  virtual Bool_t   Notify();
  //  virtual Bool_t FillAll(nbodyhfm &nhfm);
  virtual Bool_t Fillhfm(nbodyhfm & nhfm);      //need in nbodyout TstepLoop infunc.

protected:
  void Init();   
};

//Nbodyout==========================================//
//constructer=======================================//
nbodyout::nbodyout(): trstar(0), trplanet(0), trcenter(0), tpars(0) { Init(); }

//destructer========================================//
nbodyout::~nbodyout()
{
  if (trstar) delete trstar->GetCurrentFile();
  if (trplanet) delete trplanet->GetCurrentFile();
  if (trcenter) delete trcenter->GetCurrentFile();
  if (tpars) delete tpars->GetCurrentFile();
  //  if (tscal) delete tscal->GetCurrentFile();
}

//Function==========================================//
//--07/29/12 19:20-initial------------------------------//
void nbodyout::Init()
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
    
  // Set branch addresses and branch pointers
  trstar = new TChain("star");
  trplanet = new TChain("planet");
  trcenter = new TChain("center");
  tpars = new TChain("pars");
  //  tscal = new TChain("scal");
  
  trstar->SetMakeClass(1);
  trplanet->SetMakeClass(1);
  trcenter->SetMakeClass(1);
  tpars->SetMakeClass(1);
  //  tscal->SetMakeClass(1);

  trstar->SetBranchAddress("t", &t, &b_ts);
  trstar->SetBranchAddress("m", &m, &b_ms);
  trstar->SetBranchAddress("r", r, &b_rs);
  trstar->SetBranchAddress("v", v, &b_vs);
  trstar->SetBranchAddress("n", &n, &b_ns);
  trstar->SetBranchAddress("kstar", &kstar, &b_kstars);

  trplanet->SetBranchAddress("t", &t, &b_tp);
  trplanet->SetBranchAddress("m", &m, &b_mp);
  trplanet->SetBranchAddress("r", r, &b_rp);
  trplanet->SetBranchAddress("v", v, &b_vp);
  trplanet->SetBranchAddress("n", &n, &b_np);
  trplanet->SetBranchAddress("kstar", &kstar, &b_kstarp);

  trcenter->SetBranchAddress("t", &t, &b_tc);
  trcenter->SetBranchAddress("m", &m, &b_mc);
  trcenter->SetBranchAddress("r", r, &b_rc);
  trcenter->SetBranchAddress("v", v, &b_vc);
  trcenter->SetBranchAddress("n", &n, &b_nc);
  trcenter->SetBranchAddress("kstar", &kstar, &b_kstarc);
    
  tpars->SetBranchAddress("t",&t, &b_t);
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

//   tscal->SetBranchAddress("tscale",&tscale,&b_tscale);
//   tscal->SetBranchAddress("zmbar",&zmbar,&b_zmbar);
//   tscal->SetBranchAddress("rbar",&rbar,&b_rbar);
//   tscal->SetBranchAddress("vstar",&vstar,&b_vstar);
 }

//--07/29/12 21:47-Load root file-----------------------//
Bool_t nbodyout::LoadFile(std::string file)
{
  trstar->AddFile(file.c_str());
  trplanet->AddFile(file.c_str());
  trcenter->AddFile(file.c_str());
  tpars->AddFile(file.c_str());
  //  tscal->AddFile(file.c_str());
  //  if (!tscal->GetEntries()) return 0;
  if (!tpars->GetEntries()) return 0;
  if (!trstar->GetEntries()) return 0;
  if (!trplanet->GetEntries()) return 0;
  if (!trcenter->GetEntries()) return 0;
  return 1;
}
  
//--07/29/12 19:21-loop entry with order----------------//
void nbodyout::TstepLoop(LoopFunc infunc, nbodyout &nout, const std::string& cut)
{
  //  tscal->GetEntry(0);
  Int_t tottimestep=tpars->GetEntries();
  for (Int_t tstep=0;tstep<tottimestep;tstep++)
  {
    tpars->GetEntry(tstep);
    std::string timecut="&&t=="+to<std::string>(t);
    trstar->Draw(">>starlist",(cut+timecut).c_str(),"entrylist");
    trplanet->Draw(">>planetlist",(cut+timecut).c_str(),"entrylist");
    TEntryList *starlist=(TEntryList*)gDirectory->Get("starlist");
    TEntryList *planetlist=(TEntryList*)gDirectory->Get("planetlist");
    Int_t starnum=starlist->GetN();
    Int_t planetnum=planetlist->GetN();
    if(!infunc(starnum,starlist,planetnum,planetlist,nout))
      std::cerr<<"Error: Inner Loop function error!\n";
  }
}

Int_t nbodyout::GetEntry(std::string name, Long64_t entry)
{
  if (name=="star")
  {
    if(!trstar) return 0;
    return trstar->GetEntry(entry);
  }
  else if(name=="planet")
  {
    if(!trplanet) return 0;
    return trplanet->GetEntry(entry);
  }
  else if(name=="center")
  {
    if(!trcenter) return 0;
    return trcenter->GetEntry(entry);
  }
  else if(name=="pars")
  {
    if(!tpars) return 0;
    return tpars->GetEntry(entry);
  }
  // else if(name=="scal")
  // {
  //   if(!tscal) return 0;
  //   return tscal->GetEntry(entry);
  // }
  else return 0;
}

Int_t nbodyout::GetEntries(std::string name)
{
  if (name=="star")
  {
    if(!trstar) return 0;
    return trstar->GetEntries();
  }
  else if(name=="planet")
  {
    if(!trplanet) return 0;
    return trplanet->GetEntries();
  }
  else if(name=="center")
  {
    if(!trcenter) return 0;
    return trcenter->GetEntries();
  }
  else if(name=="pars")
  {
    if(!tpars) return 0;
    return tpars->GetEntries();
  }
  // else if(name=="scal")
  // {
  //   if(!tscal) return 0;
  //   return tscal->GetEntries();
  // }
  else return 0;
}

void nbodyout::Show(std::string name,Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
  if (name=="star")
    trstar->Show(entry);
  else if (name=="planet")
    trplanet->Show(entry);
  else if (name=="center")
    trcenter->Show(entry);
  else if (name=="pars")
    tpars->Show(entry);
  // else if (name=="scal")
  //   tscal->Show(entry);
  //  else return;
}

//--07/30/12 22:31-To fill the hfm new tree---------------------//
Bool_t nbodyout::Fillhfm(nbodyhfm & nhfm)
{
  //  tscal->GetEntry(0);
  Int_t tottimestep=tpars->GetEntries();
  b_t->GetEntry(1);
  Double_t deltat=t;
  b_t->GetEntry(0);
  deltat -=t;
  tpars->GetEntry(0);
  for (Int_t tstep=0;tstep<tottimestep;tstep++)
  {
#ifdef DEBUG
    std::cout<<"Debug: begin tstep="<<tstep<<std::endl;
#endif    
    b_t->GetEntry(tstep);
    std::string timecut="t<="+to<std::string>(t+0.01*deltat)+"&&t>="+to<std::string>(t-0.01*deltat);
    trstar->Draw(">>starlist",timecut.c_str(),"entrylist");
    trplanet->Draw(">>planetlist",timecut.c_str(),"entrylist");
    TEntryList *slist=(TEntryList*)gDirectory->Get("starlist");
    TEntryList *plist=(TEntryList*)gDirectory->Get("planetlist");
    Int_t starn=slist->GetN();
    Int_t planetn=plist->GetN();
#ifdef DEBUG
    std::cout<<"Debug: getN: star="<<starn<<"\tplanet="<<planetn<<std::endl;
#endif    
    if (starn<=0)
    {
      std::cerr<<"Error: Particle number not positive!("+timecut+")\n";
      return 0;
    }
    else if (!slist||!plist)
    {
      std::cerr<<"Error: No Entrylist found!\n";
      return 0;
    }
    Float_t *smdata=new Float_t[starn];
    Float_t *srdata=new Float_t[starn];
    Float_t stmass=0;
    nhfm.ns=starn;
    nhfm.np=planetn;
    //Star Loop=========================================//
    for (Int_t i=0;i<starn;i++)
    {
#ifdef DEBUG
      std::cout<<"Debug: loop i="<<i;
      std::cout<<std::endl;
#endif      
      Int_t stari=slist->GetEntry(i);
#ifdef DEBUG
      std::cout<<"Debug: get slist"<<"\t"<<stari<<"\n";
#endif      
      if (i==0)
      {
        b_ts->GetEntry(stari);
        nhfm.t=t*tscale;
#ifdef DEBUG
        std::cout<<"Debug: ts get stari\t"<<nhfm.t<<std::endl;
#endif      
      }
      b_ms->GetEntry(stari);
#ifdef DEBUG
      std::cout<<"Debug: ms get stari"<<std::endl;
#endif      
      smdata[i]=m;
#ifdef DEBUG
      std::cout<<"Debug: smdata[i] "<<m<<std::endl;
#endif      
      stmass +=smdata[i];
#ifdef DEBUG
      std::cout<<"Debug: stmass"<<std::endl;
#endif      
      b_rs->GetEntry(stari);
#ifdef DEBUG
      std::cout<<"Debug: rs get stari"<<std::endl;
#endif      
      srdata[i]=r[3];
    }
#ifdef DEBUG
    std::cout<<"Debug: star loop get srdata smdata begin sort\n";
#endif    
    quicksort(srdata,smdata,starn);
    Double_t starhfm=0;
    Int_t jj;
    for(jj=1;jj<=starn;jj++)
    {
      starhfm +=smdata[jj-1];
      if (starhfm>stmass/2.0)
        break;
    }
    nhfm.shfn=jj;
    nhfm.shfr=srdata[jj-1]*rbar;
    nhfm.shfm=starhfm*zmbar;
    //Planet Loop=======================================//
    if (planetn==0)
    {
      nhfm.phfm=0;
      nhfm.phfr=0;
      nhfm.phfn=0;
    }
    else
    {
      Float_t ptmass=0, planetmass=0;
      Float_t *prdata=new Float_t[planetn];
      for (Int_t i=0;i<planetn;i++)
      {
        Int_t planeti=plist->GetEntry(i);
        if (i==0)
        {
          b_mp->GetEntry(planeti);
          planetmass=m;
        }
        b_rp->GetEntry(planeti);
        prdata[i]=r[3];
      }
      quicksort(prdata,planetn);
      nhfm.phfn=planetn/2-1;
      nhfm.phfr=prdata[nhfm.phfn]*rbar;
      nhfm.phfm=nhfm.phfn*planetmass*zmbar;
    }
#ifdef DEBUG
    std::cout<<"Debug: planet loop, get phfn, phfr, phrm\n";
#endif    
    if (nhfm.ftree&&nhfm.f)
    {
      nhfm.f->cd();
      nhfm.ftree->Fill();
    }
    else
    {
      std::cerr<<"Error: Tree not open!\n";
      return 0;
    }
  }
#ifdef DEBUG
  std::cout<<"Debug: before write\n";
#endif  
  nhfm.Write("",TObject::kOverwrite);
  return 1;
}

#endif
