//==nbodyhfm: class to read and creat hfm tree======//
//Construct:
// nbodyhfm(): link all member, for chain
// nbodyhfm(str name): build new tree in name root file
//         if no root file found, create it. if hfm tree
//         already exist and not empty, load the tree and use chain
//Member: (TChain*)fchain, (TFile*)f, (TTree*)ftree
//        (Float_t)t, (Int_t)state,ns,np,shfn,phfn
//        (Double_t)shfm,shfr,phfm,phfr
//        (TBranch*) ...
//Function:
//(Bool)LoadFile (str name): Load root file for chain
//(Int)GetEntry(Long64_t entry): get chain or tree entry
//(Int)GetEntries(): get chain or tree entry total number
//(Int)Identify(): identify whether chain or tree active,
//                 1 for tree, 2 for chain
//(Bool)Setstate(Int i) set state, should be 1 or 2.
//(void)Show(Long64_t entry): show member for chain or tree.

#ifndef nbodyhfm_h
#define nbodyhfm_h

//My library========================================//
#include <nbodytools.h>
//root library======================================//
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
//STL===============================================//
#include <iostream>
#include <string>

//Half mass class===================================//
class nbodyhfm : public nbodytools {
public :
friend class nbodyout;
  //Members===========================================//
  //-hf: half mass, s:star, p:planet, m:mass, r:radius, n:number---//
  Float_t t;
  Int_t ns, np, shfn, phfn;
  Double_t shfm, shfr, phfm, phfr;

  //TBranch ==========================================//
  TBranch *b_shfm, *b_shfr, *b_shfn;
  TBranch *b_phfm, *b_phfr, *b_phfn;
  TBranch *b_t, *b_ns, *b_np;

  //Function==========================================//
  nbodyhfm(): nbodytools("hfm","Half mass data of OUT3") { Link(); }  //use for chain
  nbodyhfm(std::string filename): nbodytools("hfm","Half mass data of OUT3") { Link(filename); }   //use for build tree, filename is for store new tree.
  //Long64_t gethalf(TBranch *b, T &data);  //set and return half data entry bonding to branch b comparing with initial data; Becareful not input wrong data.
  virtual Long64_t gethalfns();  //set and return half ns entry (compare to initial ns);
  virtual Long64_t gethalfnp();  //set and return half np entry (compare to initial np);
  virtual Long64_t gethalfnpvsns();   //set and return half np / ns entry (compare to initial ratio);
protected:
  virtual void Init();  //state=1: new Tree; choice=2: Chain
};

//Function==========================================//
//--07/30/12 15:37-initial------------------------------//
void nbodyhfm::Init()
{
  if(state==1)
  {
    ftree->Branch("t",&t);
    ftree->Branch("shfm",&shfm);
    ftree->Branch("shfr",&shfr);
    ftree->Branch("shfn",&shfn);
    ftree->Branch("phfm",&phfm);
    ftree->Branch("phfr",&phfr);
    ftree->Branch("phfn",&phfn);
    ftree->Branch("ns",&ns);
    ftree->Branch("np",&np);

    b_t=(TBranch*)ftree->GetBranch("t");
    b_shfm=(TBranch*)ftree->GetBranch("shfm");
    b_shfr=(TBranch*)ftree->GetBranch("shfr");
    b_shfn=(TBranch*)ftree->GetBranch("shfn");
    b_phfm=(TBranch*)ftree->GetBranch("phfm");
    b_phfr=(TBranch*)ftree->GetBranch("phfr");
    b_phfn=(TBranch*)ftree->GetBranch("phfn");
    b_ns=(TBranch*)ftree->GetBranch("ns");
    b_np=(TBranch*)ftree->GetBranch("np");
    std::cout<<"New hfm Tree build.\n";
  }
  else if (state==2)
  {
    fchain->SetBranchAddress("t",&t,&b_t);
    fchain->SetBranchAddress("shfm",&shfm,&b_shfm);
    fchain->SetBranchAddress("shfr",&shfr,&b_shfr);
    fchain->SetBranchAddress("shfn",&shfn,&b_shfn);
    fchain->SetBranchAddress("phfm",&phfm,&b_phfm);
    fchain->SetBranchAddress("phfr",&phfr,&b_phfr);
    fchain->SetBranchAddress("phfn",&phfn,&b_phfn);
    fchain->SetBranchAddress("ns",&ns,&b_ns);
    fchain->SetBranchAddress("np",&np,&b_np);
    std::cout<<"hfm Chain build.\n";
  }
  else std::cerr<<"Error: state cannot identify!\n";
}

Long64_t nbodyhfm::gethalfns()
{
  b_ns->GetEntry(0);
  int initns=ns, i=0;
  Int_t totnum=fchain->GetEntries()-1;
  while (ns>initns/2)
  {
    b_ns->GetEntry(++i);
    if (i==totnum)
    {
      std::cerr<<"Error: Cannot find half ns time! Return -1./n";
      return -1;
    }

  }
  if (state==2)
  {
    fchain->GetEntry(i);
    return i;
  }
  else
  {
    std::cerr<<"Error: State not right, dangerous to GetEntry.\n";
    return -1;
  }
}

Long64_t nbodyhfm::gethalfnp()
{
  b_np->GetEntry(0);
  int initnp=np, i=0;
  Int_t totnum=fchain->GetEntries()-1;
  while (np>initnp/2)
  {
    b_np->GetEntry(++i);
    if (i==totnum)
    {
      std::cerr<<"Error: Cannot find half np time! Return -1./n";
      return -1;
    }
  }
  if (state==2)
  {
    fchain->GetEntry(i);
    return i;
  }
  else
  {
    std::cerr<<"Error: State not right, dangerous to GetEntry.\n";
    return -1;
  }
}

Long64_t nbodyhfm::gethalfnpvsns()
{
  b_ns->GetEntry(0);
  b_np->GetEntry(0);
  Int_t initns=ns,initnp=np,i=0;
  Int_t totnum=fchain->GetEntries()-1;
  while (np/static_cast<double>(ns)>initnp/static_cast<double>(initns)/2.0)
  {
    b_ns->GetEntry(++i);
    b_np->GetEntry(i);
    if (i==totnum)
    {
      std::cerr<<"Error: Cannot find half np/ns time! Return -1./n";
      return -1;
    }
  }
  if (state==2)
  {
    fchain->GetEntry(i);
    return i;
  }
  else
  {
    std::cerr<<"Error: State not right, dangerous to GetEntry.\n";
    return -1;
  }
}

#endif
