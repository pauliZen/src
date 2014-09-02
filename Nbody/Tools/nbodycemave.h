#ifndef nbodycemave_h
#define nbodycemave_h

#include <nbodytools.h>

#include <string>
#ifdef DEBUG
#include <iostream>
#endif

class nbodycemave: public nbodytools{
public:
  Int_t  type, ntot;  //ntot: total number of encounters
  Double_t ctime[11];  //{0.001, 0.021, 0.159, 0.5, 0.841, 0.9755, 0.998, 0.1, 0.25, 0.75, 0.9};
  Double_t ctime_err[11];

  Int_t ns, np, nb, nmodel, m1, p1;
  Double_t rbar;

  TBranch  *b_ntot, *b_type, *b_ctime, *b_ctime_err;
  TBranch  *b_ns, *b_np, *b_nb, *b_nmodel, *b_rbar, *b_m1, *b_p1;

  nbodycemave(): nbodytools("cemave","ce list") { Link(); }
  nbodycemave(std::string filename): nbodytools("cemave") { Link(filename); }

protected:
  virtual void Init();
};

void nbodycemave::Init()
{
  if (state==1)
  {
    ftree->Branch("type",&type,"type/I");
    ftree->Branch("ntot",&ntot,"ntot/I");
    ftree->Branch("ctime",ctime,"ctime[11]/D");
    ftree->Branch("ctime_err",ctime_err,"ctime_err[11]/D");
        
    ftree->Branch("ns",&ns);
    ftree->Branch("np",&np);
    ftree->Branch("nb",&nb);
    ftree->Branch("nmodel",&nmodel);
    ftree->Branch("rbar",&rbar);
    ftree->Branch("m1",&m1);
    ftree->Branch("p1",&p1);

    b_ntot=(TBranch*)ftree->GetBranch("ntot");
    b_type=(TBranch*)ftree->GetBranch("type");
    b_ctime=(TBranch*)ftree->GetBranch("ctime");
    b_ctime_err=(TBranch*)ftree->GetBranch("ctime_err");

    b_ns=(TBranch*)ftree->GetBranch("ns");
    b_np=(TBranch*)ftree->GetBranch("np");
    b_nb=(TBranch*)ftree->GetBranch("nb");
    b_rbar=(TBranch*)ftree->GetBranch("rbar");
    b_nmodel=(TBranch*)ftree->GetBranch("nmodel");
    b_m1=(TBranch*)ftree->GetBranch("m1");
    b_p1=(TBranch*)ftree->GetBranch("p1");
#ifdef DEBUG
    std::cout<<"New tree cemave build.\n";
#endif  
 
  }
  else if (state==2)
  {
    fchain->SetBranchAddress("type",&type,&b_type);
    fchain->SetBranchAddress("ntot",&ntot,&b_ntot);
    fchain->SetBranchAddress("ctime",ctime,&b_ctime);
    fchain->SetBranchAddress("ctime_err",ctime_err,&b_ctime_err);

    fchain->SetBranchAddress("ns",&ns,&b_ns);
    fchain->SetBranchAddress("np",&np,&b_np);
    fchain->SetBranchAddress("nb",&nb,&b_nb);
    fchain->SetBranchAddress("nmodel",&nmodel,&b_nmodel);
    fchain->SetBranchAddress("rbar",&rbar,&b_rbar);
    fchain->SetBranchAddress("m1",&m1,&b_m1);
    fchain->SetBranchAddress("p1",&p1,&b_p1);
#ifdef DEBUG
    std::cout<<"Chain cemave build.\n";
#endif  
  }
}

#endif
