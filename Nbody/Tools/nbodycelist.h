#ifndef nbodycelist_h
#define nbodycelist_h

#include <nbodytools.h>
#include <nbodyce.h>

#include <string>
#ifdef DEBUG
#include <iostream>
#endif

class nbodycelist: public nbodytools{
public:
  Double_t x[3][3], v[3][3], m[4], ecc[3], peri[3], semi[3], t[3], E[3];
  Double_t vinf[3], vp[3], bip[3];
  Double_t rau, rbar, tstar, zmbar, vstar;
  Bool_t exchange;
  Int_t name[4], type;

  Int_t ns, np, nb, model, m1, p1;
  Double_t rsbar;
  
  TBranch  *b_x, *b_v, *b_m, *b_ecc, *b_peri, *b_semi, *b_t, *b_E, *b_vinf, *b_vp, *b_bip;
  TBranch  *b_rau, *b_rbar, *b_tstar, *b_zmbar, *b_vstar;
  TBranch  *b_exchange, *b_name, *b_type;

  TBranch *b_ns, *b_np, *b_nb, *b_model, *b_rsbar, *b_m1, *b_p1;

  nbodycelist(): nbodytools("celist","ce list") { Link(); }
  nbodycelist(std::string filename): nbodytools("celist") { Link(filename); }

  virtual void LoadData(nbodyce &tce, Int_t i_entry);
protected:
  virtual void Init();
};

void nbodycelist::Init()
{
  if (state==1)
  {
    ftree->Branch("name",name,"name[4]/I");
    ftree->Branch("type",&type,"type/I");
    ftree->Branch("t",t,"t[3]/D");
    ftree->Branch("x",x,"x[3][3]/D");
    ftree->Branch("v",v,"v[3][3]/D");
    ftree->Branch("m",m,"m[4]/D");
    ftree->Branch("ecc",ecc,"ecc[3]/D");
    ftree->Branch("peri",peri,"peri[3]/D");
    ftree->Branch("semi",semi,"semi[3]/D");
    ftree->Branch("exchange",&exchange);
    ftree->Branch("E",E,"E[3]/D");
    ftree->Branch("bip",bip,"bip[3]/D");
    ftree->Branch("vinf",vinf,"vinf[3]/D");
    ftree->Branch("vp",vp,"vp[3]/D");
    ftree->Branch("rau",&rau);
    ftree->Branch("rsbar",&rsbar);
    ftree->Branch("tstar",&tstar);
    ftree->Branch("zmbar",&zmbar);
    ftree->Branch("vstar",&vstar);

    ftree->Branch("ns",&ns);
    ftree->Branch("np",&np);
    ftree->Branch("nb",&nb);
    ftree->Branch("model",&model);
    ftree->Branch("rbar",&rbar);
    ftree->Branch("m1",&m1);
    ftree->Branch("p1",&p1);

    b_name=(TBranch*)ftree->GetBranch("name");
    b_type=(TBranch*)ftree->GetBranch("type");
    b_t=(TBranch*)ftree->GetBranch("t");
    b_x=(TBranch*)ftree->GetBranch("x");
    b_v=(TBranch*)ftree->GetBranch("v");
    b_m=(TBranch*)ftree->GetBranch("m");
    b_ecc=(TBranch*)ftree->GetBranch("ecc");
    b_peri=(TBranch*)ftree->GetBranch("peri");
    b_semi=(TBranch*)ftree->GetBranch("semi");
    b_exchange=(TBranch*)ftree->GetBranch("exchange");
    b_E=(TBranch*)ftree->GetBranch("E");
    b_bip=(TBranch*)ftree->GetBranch("bip");
    b_vinf=(TBranch*)ftree->GetBranch("vinf");
    b_vp=(TBranch*)ftree->GetBranch("vp");
    b_rau=(TBranch*)ftree->GetBranch("rau");
    b_rsbar=(TBranch*)ftree->GetBranch("rsbar");
    b_tstar=(TBranch*)ftree->GetBranch("tstar");
    b_zmbar=(TBranch*)ftree->GetBranch("zmbar");
    b_vstar=(TBranch*)ftree->GetBranch("vstar");

    b_ns=(TBranch*)ftree->GetBranch("ns");
    b_np=(TBranch*)ftree->GetBranch("np");
    b_nb=(TBranch*)ftree->GetBranch("nb");
    b_rbar=(TBranch*)ftree->GetBranch("rbar");
    b_model=(TBranch*)ftree->GetBranch("model");
    b_m1=(TBranch*)ftree->GetBranch("m1");
    b_p1=(TBranch*)ftree->GetBranch("p1");
#ifdef DEBUG
    std::cout<<"New tree celist build.\n";
#endif  
 
  }
  else if (state==2)
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
    fchain->SetBranchAddress("rau",&rau,&b_rau);
    fchain->SetBranchAddress("rsbar",&rsbar,&b_rsbar);
    fchain->SetBranchAddress("tstar",&tstar,&b_tstar);
    fchain->SetBranchAddress("zmbar",&zmbar,&b_zmbar);
    fchain->SetBranchAddress("vstar",&vstar,&b_vstar);

    fchain->SetBranchAddress("ns",&ns,&b_ns);
    fchain->SetBranchAddress("np",&np,&b_np);
    fchain->SetBranchAddress("nb",&nb,&b_nb);
    fchain->SetBranchAddress("model",&model,&b_model);
    fchain->SetBranchAddress("rbar",&rbar,&b_rbar);
    fchain->SetBranchAddress("m1",&m1,&b_m1);
    fchain->SetBranchAddress("p1",&p1,&b_p1);
#ifdef DEBUG
    std::cout<<"Chain celist build.\n";
#endif  
  }
}

void nbodycelist::LoadData(nbodyce &tce,Int_t i_entry)
{
  tce.fchain->GetEntry(i_entry);
  for (int i=0;i<3;i++)
  {
    name[i]=tce.name[i];
    t[i]=tce.t[i];
    for (int j=0;j<3;j++)
    {
      x[j][i]=tce.x[j][i];
      v[j][i]=tce.v[j][i];
    }
    m[i]=tce.m[i]*tce.zmbar;
    ecc[i]=tce.ecc[i];
    peri[i]=tce.peri[i];
    semi[i]=tce.semi[i];
    E[i]=tce.E[i];
    bip[i]=tce.bip[i];
    vinf[i]=tce.vinf[i];
    vp[i]=tce.vp[i];
  }
  name[3]=tce.name[3];
  m[3]=tce.m[3]*tce.zmbar;
  type=tce.type;
  exchange=tce.exchange;
  rau=tce.rau;
  rsbar=tce.rbar;
  tstar=tce.tstar;
  zmbar=tce.zmbar;
  vstar=tce.vstar;
}

#endif
