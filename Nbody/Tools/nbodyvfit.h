#ifndef nbodyvfit_h
#define nbodyvfit_h

#include <nbodytools.h>
#include <nbodycelist.h>

#include <string>
#ifdef DEBUG
#include <iostream>
#endif

class nbodyvfit: public nbodytools{
public:
  Double_t rbar;
  Int_t ns,np,nb,m1,p1,type;
  Double_t chi2, vmax, vmerr,vcut,vcerr;
  Double_t vsigma,vserr;
  Double_t h,herr;
  
  TBranch *b_ns, *b_np, *b_nb, *b_model, *b_rbar, *b_m1, *b_p1, *b_type;
  TBranch *b_chi2, *b_vmax, *b_vmerr, *b_h, *b_herr, *b_vcut, *b_vcerr, *b_vsigma, *b_vserr;

  //Chain new files with treename=====================//
  nbodyvfit(std::string treename): nbodytools(treename,"fit parameters") { nbodytools::Link(); }
  //Chain new file with name treename=================//
  nbodyvfit(std::string treename, std::string filename): nbodytools(treename) { Link(filename, 1); }
  //Open new file with name treename and loadchain for 1//
  nbodyvfit(std::string treename, std::string filename, bool loadchain): nbodytools(treename) { Link(filename, loadchain); }
  //Build file with filename==========================// 
  nbodyvfit(std::string filename, bool loadchain): nbodytools() { f = new TFile(filename.c_str(),"update"); }
  
  virtual void Link(std::string filename, bool loadchain);
  virtual void LoadData(nbodycelist &tc, Int_t i_entry);
  virtual void Close();
  virtual void Switch(std::string treename);

protected:
  virtual void Init();
};

void nbodyvfit::Switch(std::string treename)
{
#ifdef DEBUG
  std::cout<<"Switch treename\n";
#endif  
  f->cd();
  delete ftree;
  ftree=(TTree*)gDirectory->Get(treename.c_str());
  if (!ftree)
  {
    ftree=new TTree(treename.c_str(),treeintro.c_str());
    state=1;
    Init();
  }
  else
  {
    state=3;
    Init();
  }
}

void nbodyvfit::Close()
{
  if (state==1) f->Close("R");
}

void nbodyvfit::Link(std::string filename, bool loadchain)
{
  f = new TFile(filename.c_str(),"update");
  f->GetObject(treename.c_str(),ftree);
  if (!ftree)
  {
    ftree=new TTree(treename.c_str(),treeintro.c_str());
    state=1;
    Init();
  }
  else if (loadchain)
  {
    fchain=new TChain(treename.c_str());
    fchain->AddFile(filename.c_str());
    state=2;
    Init();
  }
  else
  {
    state=3;
    Init();
  }
}

void nbodyvfit::Init()
{
  if (state==1)
  {
    ftree->Branch("ns",&ns);
    ftree->Branch("np",&np);
    ftree->Branch("nb",&nb);
    ftree->Branch("rbar",&rbar);
    ftree->Branch("m1",&m1);
    ftree->Branch("p1",&p1);

    ftree->Branch("chi2",&chi2);
    ftree->Branch("vmax",&vmax);
    ftree->Branch("vmerr",&vmerr);
    ftree->Branch("vcut",&vcut);
    ftree->Branch("vcerr",&vcerr);
    ftree->Branch("vsigma",&vsigma);
    ftree->Branch("vserr",&vserr);
    ftree->Branch("h",&h);
    ftree->Branch("herr",&herr);
    ftree->Branch("type",&type);

    b_ns=(TBranch*)ftree->GetBranch("ns");
    b_np=(TBranch*)ftree->GetBranch("np");
    b_nb=(TBranch*)ftree->GetBranch("nb");
    b_rbar=(TBranch*)ftree->GetBranch("rbar");
    b_m1=(TBranch*)ftree->GetBranch("m1");
    b_p1=(TBranch*)ftree->GetBranch("p1");

    b_chi2=(TBranch*)ftree->GetBranch("chi2");
    b_vmax=(TBranch*)ftree->GetBranch("vmax");
    b_vmerr=(TBranch*)ftree->GetBranch("vmerr");
    b_vcut=(TBranch*)ftree->GetBranch("vcut");
    b_vcerr=(TBranch*)ftree->GetBranch("vcerr");
    b_vsigma=(TBranch*)ftree->GetBranch("vsigma");
    b_vserr=(TBranch*)ftree->GetBranch("vserr");
    b_h=(TBranch*)ftree->GetBranch("h");
    b_herr=(TBranch*)ftree->GetBranch("herr");
    b_type=(TBranch*)ftree->GetBranch("type");
    
    
#ifdef DEBUG
    std::cout<<"New vfit build.\n";
#endif    
  }
  else if (state==2)
  {
    fchain->SetBranchAddress("ns",&ns,&b_ns);
    fchain->SetBranchAddress("np",&np,&b_np);
    fchain->SetBranchAddress("nb",&nb,&b_nb);
    fchain->SetBranchAddress("rbar",&rbar,&b_rbar);
    fchain->SetBranchAddress("m1",&m1,&b_m1);
    fchain->SetBranchAddress("p1",&p1,&b_p1);

    fchain->SetBranchAddress("chi2",&chi2,&b_chi2);
    fchain->SetBranchAddress("vmax",&vmax,&b_vmax);
    fchain->SetBranchAddress("vmerr",&vmerr,&b_vmerr);
    fchain->SetBranchAddress("vcut",&vcut,&b_vcut);
    fchain->SetBranchAddress("vcerr",&vcerr,&b_vcerr);
    fchain->SetBranchAddress("vsigma",&vsigma,&b_vsigma);
    fchain->SetBranchAddress("vserr",&vserr,&b_vserr);
    fchain->SetBranchAddress("h",&h,&b_h);
    fchain->SetBranchAddress("herr",&herr,&b_herr);
    fchain->SetBranchAddress("type",&type,&b_type);
#ifdef DEBUG
    std::cout<<"Chain vfit build.\n";
#endif
  }
  else if (state==3)
  {
    ftree->SetBranchAddress("ns",&ns,&b_ns);
    ftree->SetBranchAddress("np",&np,&b_np);
    ftree->SetBranchAddress("nb",&nb,&b_nb);
    ftree->SetBranchAddress("rbar",&rbar,&b_rbar);
    ftree->SetBranchAddress("m1",&m1,&b_m1);
    ftree->SetBranchAddress("p1",&p1,&b_p1);

    ftree->SetBranchAddress("chi2",&chi2,&b_chi2);
    ftree->SetBranchAddress("vmax",&vmax,&b_vmax);
    ftree->SetBranchAddress("vmerr",&vmerr,&b_vmerr);
    ftree->SetBranchAddress("vcut",&vcut,&b_vcut);
    ftree->SetBranchAddress("vcerr",&vcerr,&b_vcerr);
    ftree->SetBranchAddress("vsigma",&vsigma,&b_vsigma);
    ftree->SetBranchAddress("vserr",&vserr,&b_vserr);
    ftree->SetBranchAddress("h",&h,&b_h);
    ftree->SetBranchAddress("herr",&herr,&b_herr);
    ftree->SetBranchAddress("type",&type,&b_type);

    state=1;
#ifdef DEBUG
    std::cout<<"Tree vfit link.\n";
#endif
  }
}

void nbodyvfit::LoadData(nbodycelist &tc, Int_t i_entry)
{
  tc.GetEntry(i_entry);
  ns=tc.ns;
  np=tc.np;
  nb=tc.nb;
  rbar=tc.rbar;
  m1=tc.m1;
  p1=tc.p1;
}

#endif
