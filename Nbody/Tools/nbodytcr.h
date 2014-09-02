#ifndef nbodytcr_h
#define nbodytcr_h

//Mylibrary=========================================//
#include <nbodytools.h>
//root library======================================//
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

//STL===============================================//
#include <string>

class nbodytcr : public nbodytools{
public:
friend class nbodytriple;
  Double_t t;
  Int_t n[3], index;
  Float_t m[3], x[3], y[3], z[3], vx[3], vy[3], vz[3];
  Float_t ecc1, pmin, semi, ecc;

  TBranch *b_x, *b_y, *b_z, *b_vx, *b_vy, *b_vz;
  TBranch *b_index, *b_t, *b_n, *b_m, *b_ecc1, *b_semi, *b_pmin, *b_ecc;

  //Function==========================================//
  nbodytcr(std::string treename): nbodytools(treename,"triple data close encounter count") { Link(); }
  nbodytcr(std::string treename, std::string filename): nbodytools(treename,"triple data close encounter count") { Link(filename); }
protected:
  virtual void Init();
};

//==================================================//
void nbodytcr::Init()
{
  if (state==1)
  {
    ftree->Branch("index",&index);
    ftree->Branch("t",&t);
    ftree->Branch("n",n,"n[3]/I");
    ftree->Branch("m",m,"m[3]/F");
    ftree->Branch("x",x,"x[3]/F");
    ftree->Branch("y",y,"y[3]/F");
    ftree->Branch("z",z,"z[3]/F");
    ftree->Branch("vx",vx,"vx[3]/F");
    ftree->Branch("vy",vy,"vy[3]/F");
    ftree->Branch("vz",vz,"vz[3]/F");
    ftree->Branch("ecc1",&ecc1);
    ftree->Branch("semi",&semi);
    ftree->Branch("pmin",&pmin);
    ftree->Branch("ecc",&ecc);

    b_index=(TBranch*)ftree->GetBranch("index");
    b_t=(TBranch*)ftree->GetBranch("t");
    b_n=(TBranch*)ftree->GetBranch("n");
    b_m=(TBranch*)ftree->GetBranch("m");
    b_x=(TBranch*)ftree->GetBranch("x");
    b_y=(TBranch*)ftree->GetBranch("y");
    b_z=(TBranch*)ftree->GetBranch("z");
    b_vx=(TBranch*)ftree->GetBranch("vx");
    b_vy=(TBranch*)ftree->GetBranch("vy");
    b_vz=(TBranch*)ftree->GetBranch("vz");
    b_ecc1=(TBranch*)ftree->GetBranch("ecc1");
    b_semi=(TBranch*)ftree->GetBranch("semi");
    b_pmin=(TBranch*)ftree->GetBranch("pmin");
    b_ecc=(TBranch*)ftree->GetBranch("ecc");
    std::cout<<"New "<<treename<<" Tree build.\n";
  }
  else if (state==2)
  {
    fchain->SetBranchAddress("index",&index,&b_index);
    fchain->SetBranchAddress("t",&t,&b_t);
    fchain->SetBranchAddress("n",n,&b_n);
    fchain->SetBranchAddress("m",m,&b_m);
    fchain->SetBranchAddress("x",x,&b_x);
    fchain->SetBranchAddress("y",y,&b_y);
    fchain->SetBranchAddress("z",z,&b_z);
    fchain->SetBranchAddress("vx",vx,&b_vx);
    fchain->SetBranchAddress("vy",vy,&b_vy);
    fchain->SetBranchAddress("vz",vz,&b_vz);
    fchain->SetBranchAddress("ecc1",&ecc1,&b_ecc1);
    fchain->SetBranchAddress("semi",&semi,&b_semi);
    fchain->SetBranchAddress("pmin",&pmin,&b_pmin);
    fchain->SetBranchAddress("ecc",&ecc,&b_ecc);
    std::cout<<"Chain "<<treename<<" build.\n";
  }
  else std::cerr<<"Error: state cannot identify!\n";
}

/*
class nbodytcr : public nbodytools{
public:
friend class nbodytriple;
  Double_t t[2];
  Int_t n[3], index, step;
  Float_t m[3], ecc1[2], semi[2], pmin[2], ecc[2];
  Bool_t exchange, timebreak;
  
  TBranch *b_index, *b_step, *b_t, *b_n, *b_m, *b_ecc1, *b_semi, *b_pmin, *b_ecc, *b_exchange, *b_timebreak;

  //Function==========================================//
  nbodytcr(): nbodytools("tcr","triple data close encounter count") { Link(); }
  nbodytcr(std::string filename): nbodytools("tcr","triple data close encounter count") { Link(filename); }
  virtual void Drawssp(std::string var, std::string selection = "", std::string option = "");
  virtual void Drawsss(std::string var, std::string selection = "", std::string option = "");
  virtual void Drawpss(std::string var, std::string selection = "", std::string option = "");
  virtual void Drawpsp(std::string var, std::string selection = "", std::string option = "");
protected:
  virtual void Init();
};

//==================================================//
void nbodytcr::Init()
{
  if (state==1)
  {
    ftree->Branch("index",&index);
    ftree->Branch("step",&step);
    ftree->Branch("t",t,"t[2]/D");
    ftree->Branch("n",n,"n[3]/I");
    ftree->Branch("m",m,"m[3]/F");
    ftree->Branch("ecc1",ecc1,"ecc1[2]/F");
    ftree->Branch("semi",semi,"semi[2]/F");
    ftree->Branch("pmin",pmin,"pmin[2]/F");
    ftree->Branch("ecc",ecc,"ecc[2]/F");
    ftree->Branch("exchange",&exchange);
    ftree->Branch("timebreak",&timebreak);

    b_index=(TBranch*)ftree->GetBranch("index");
    b_step=(TBranch*)ftree->GetBranch("step");
    b_t=(TBranch*)ftree->GetBranch("t");
    b_n=(TBranch*)ftree->GetBranch("n");
    b_m=(TBranch*)ftree->GetBranch("m");
    b_ecc1=(TBranch*)ftree->GetBranch("ecc1");
    b_semi=(TBranch*)ftree->GetBranch("semi");
    b_pmin=(TBranch*)ftree->GetBranch("pmin");
    b_ecc=(TBranch*)ftree->GetBranch("ecc");
    b_exchange=(TBranch*)ftree->GetBranch("exchange");
    b_timebreak=(TBranch*)ftree->GetBranch("timebreak");
    std::cout<<"New tcr Tree build.\n";
  }
  else if (state==2)
  {
    fchain->SetBranchAddress("index",&index,&b_index);
    fchain->SetBranchAddress("step",&step,&b_step);
    fchain->SetBranchAddress("t",t,&b_t);
    fchain->SetBranchAddress("n",n,&b_n);
    fchain->SetBranchAddress("m",m,&b_m);
    fchain->SetBranchAddress("ecc1",ecc1,&b_ecc1);
    fchain->SetBranchAddress("semi",semi,&b_semi);
    fchain->SetBranchAddress("pmin",pmin,&b_pmin);
    fchain->SetBranchAddress("ecc",ecc,&b_ecc);
    fchain->SetBranchAddress("exchange",&exchange,&b_exchange);
    fchain->SetBranchAddress("timebreak",&timebreak,&b_timebreak);
    std::cout<<"Chain tcr build.\n";
  }
  else std::cerr<<"Error: state cannot identify!\n";
}

void nbodytcr::Drawssp(std::string var, std::string selection, std::string option)
{
  if (initns<=0) std::cerr<<"Error: star, planet, binary number not initial.\n";
  else if (state==2)
  {
    if (selection=="")
      fchain->Draw(var.c_str(),(selstar("0")+"&&(("+selstar("1")+"&&"+selplanet("2")+")||("+selstar("2")+"&&"+selplanet("1")+"))").c_str(),option.c_str());
    else
      fchain->Draw(var.c_str(),(selection+"&&"+selstar("0")+"&&(("+selstar("1")+"&&"+selplanet("2")+")||("+selstar("2")+"&&"+selplanet("1")+"))").c_str(),option.c_str());
  }
}

void nbodytcr::Drawsss(std::string var, std::string selection, std::string option)
{
  if (initns<=0) std::cerr<<"Error: star, planet, binary number not initial.\n";
  else if (state==2)
  {
    if (selection=="")
      fchain->Draw(var.c_str(),(selstar("0")+"&&"+selstar("1")+"&&"+selstar("2")).c_str(),option.c_str());
    else
      fchain->Draw(var.c_str(),(selection+"&&"+selstar("0")+"&&"+selstar("1")+"&&"+selstar("2")).c_str(),option.c_str());
  }
}

void nbodytcr::Drawpss(std::string var, std::string selection, std::string option)
{
  if (initns<=0) std::cerr<<"Error: star, planet, binary number not initial.\n";
  else if (state==2)
  {
    if (selection=="")
      fchain->Draw(var.c_str(),(selplanet("0")+"&&"+selstar("1")+"&&"+selstar("2")).c_str(),option.c_str());
    else
      fchain->Draw(var.c_str(),(selection+"&&"+selplanet("0")+"&&"+selstar("1")+"&&"+selstar("2")).c_str(),option.c_str());
  }
}

void nbodytcr::Drawpsp(std::string var, std::string selection, std::string option)
{
  if (initns<=0) std::cerr<<"Error: star, planet, binary number not initial.\n";
  else if (state==2)
  {
    if (selection=="")
      fchain->Draw(var.c_str(),(selplanet("0")+"&&(("+selstar("1")+"&&"+selplanet("2")+")||("+selstar("2")+"&&"+selplanet("1")+"))").c_str(),option.c_str());
    else
      fchain->Draw(var.c_str(),(selection+"&&"+selplanet("0")+"&&(("+selstar("1")+"&&"+selplanet("2")+")||("+selstar("2")+"&&"+selplanet("1")+"))").c_str(),option.c_str());
  }
}
*/

#endif
