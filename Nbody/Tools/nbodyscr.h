#ifndef nbodyscr_h
#define nbodyscr_h

//Mylibrary=========================================//
#include <nbodytools.h>
//root library======================================//
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

//STL===============================================//
#include <string>

class nbodyscr : public nbodytools{
public:
friend class nbodytriple;
  Double_t t;
  Int_t n[2], index;
  Float_t m[2], x[2], y[2], z[2], vx[2], vy[2], vz[2];
  Float_t peri, semi, ecc;

  TBranch *b_x, *b_y, *b_z, *b_vx, *b_vy, *b_vz;
  TBranch *b_index, *b_t, *b_n, *b_m, *b_semi, *b_peri, *b_ecc;

  //Function==========================================//
  nbodyscr(std::string treename): nbodytools(treename,"single data close encounter count") { Link(); }
  nbodyscr(std::string treename, std::string filename): nbodytools(treename,"single data close encounter count") { Link(filename); }
protected:
  virtual void Init();
};

//==================================================//
void nbodyscr::Init()
{
  if (state==1)
  {
    ftree->Branch("index",&index);
    ftree->Branch("t",&t);
    ftree->Branch("n",n,"n[2]/I");
    ftree->Branch("m",m,"m[2]/F");
    ftree->Branch("x",x,"x[2]/F");
    ftree->Branch("y",y,"y[2]/F");
    ftree->Branch("z",z,"z[2]/F");
    ftree->Branch("vx",vx,"vx[2]/F");
    ftree->Branch("vy",vy,"vy[2]/F");
    ftree->Branch("vz",vz,"vz[2]/F");
    ftree->Branch("semi",&semi);
    ftree->Branch("peri",&peri);
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
    b_semi=(TBranch*)ftree->GetBranch("semi");
    b_peri=(TBranch*)ftree->GetBranch("peri");
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
    fchain->SetBranchAddress("semi",&semi,&b_semi);
    fchain->SetBranchAddress("peri",&peri,&b_peri);
    fchain->SetBranchAddress("ecc",&ecc,&b_ecc);
    std::cout<<"Chain "<<treename<<" build.\n";
  }
  else std::cerr<<"Error: state cannot identify!\n";
}

/*
class nbodyscr : public nbodytools{
public:
friend class nbodysingle;
  Double_t t[2];
  Int_t n[2], index, step;
  Float_t m[2], semi[2], peri[2], ecc[2];
  Bool_t timebreak;
  
  TBranch *b_index, *b_step, *b_t, *b_n, *b_m, *b_semi, *b_peri, *b_ecc, *b_timebreak;

  //Function==========================================//
  nbodyscr(): nbodytools("scr","single data close encounter count") { Link(); }
  nbodyscr(std::string filename): nbodytools("scr","single data close encounter count") { Link(filename); }
  virtual void Drawsp(std::string var, std::string selection = "", std::string option = "");
  virtual void Drawss(std::string var, std::string selection = "", std::string option = "");
  virtual void Drawpp(std::string var, std::string selection = "", std::string option = "");
protected:
  virtual void Init();
};

//==================================================//
void nbodyscr::Init()
{
  if (state==1)
  {
    ftree->Branch("index",&index);
    ftree->Branch("step",&step);
    ftree->Branch("t",t,"t[2]/D");
    ftree->Branch("n",n,"n[2]/I");
    ftree->Branch("m",m,"m[2]/F");
    ftree->Branch("semi",semi,"semi[2]/F");
    ftree->Branch("peri",peri,"peri[2]/F");
    ftree->Branch("ecc",ecc,"ecc[2]/F");
    ftree->Branch("timebreak",&timebreak);

    b_index=(TBranch*)ftree->GetBranch("index");
    b_step=(TBranch*)ftree->GetBranch("step");
    b_t=(TBranch*)ftree->GetBranch("t");
    b_n=(TBranch*)ftree->GetBranch("n");
    b_m=(TBranch*)ftree->GetBranch("m");
    b_semi=(TBranch*)ftree->GetBranch("semi");
    b_peri=(TBranch*)ftree->GetBranch("peri");
    b_ecc=(TBranch*)ftree->GetBranch("ecc");
    b_timebreak=(TBranch*)ftree->GetBranch("timebreak");
    std::cout<<"New scr Tree build.\n";
  }
  else if (state==2)
  {
    fchain->SetBranchAddress("index",&index,&b_index);
    fchain->SetBranchAddress("step",&step,&b_step);
    fchain->SetBranchAddress("t",t,&b_t);
    fchain->SetBranchAddress("n",n,&b_n);
    fchain->SetBranchAddress("m",m,&b_m);
    fchain->SetBranchAddress("semi",semi,&b_semi);
    fchain->SetBranchAddress("peri",peri,&b_peri);
    fchain->SetBranchAddress("ecc",ecc,&b_ecc);
    fchain->SetBranchAddress("timebreak",&timebreak,&b_timebreak);
    std::cout<<"Chain scr build.\n";
  }
  else std::cerr<<"Error: state cannot identify!\n";
}

void nbodyscr::Drawsp(std::string var, std::string selection, std::string option)
{
  if (initns<=0) std::cerr<<"Error: star, planet, binary number not initial.\n";
  else if (state==2)
  {
    if (selection=="")
      fchain->Draw(var.c_str(),("("+selstar("0")+"&&"+selplanet("1")+")||("+selstar("1")+"&&"+selplanet("0")+")").c_str(),option.c_str());
    else
      fchain->Draw(var.c_str(),(selection+"&&"+"("+selstar("0")+"&&"+selplanet("1")+")||("+selstar("1")+"&&"+selplanet("0")+")").c_str(),option.c_str());
  }
}

void nbodyscr::Drawss(std::string var, std::string selection, std::string option)
{
  if (initns<=0) std::cerr<<"Error: star, planet, binary number not initial.\n";
  else if (state==2)
  {
    if (selection=="")
      fchain->Draw(var.c_str(),(selstar("0")+"&&"+selstar("1")).c_str(),option.c_str());
    else
      fchain->Draw(var.c_str(),(selection+"&&"+selstar("0")+"&&"+selstar("1")).c_str(),option.c_str());
  }
}

void nbodyscr::Drawpp(std::string var, std::string selection, std::string option)
{
  if (initns<=0) std::cerr<<"Error: star, planet, binary number not initial.\n";
  else if (state==2)
  {
    if (selection=="")
      fchain->Draw(var.c_str(),(selplanet("0")+"&&"+selplanet("1")).c_str(),option.c_str());
    else
      fchain->Draw(var.c_str(),(selection+"&&"+selplanet("0")+"&&"+selplanet("1")).c_str(),option.c_str());
  }
}
*/
#endif
