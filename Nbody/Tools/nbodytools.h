// Base class for analyzing tree====================//
//nbodytools========================================//
//Construct: (): all zero===========================//
//           (str name): treename(name)=============//
//           (str name, str intro): treename(name),=//
//                                  treeintro(intro)//
//Function:=========================================//
//(void)Link(): For derived class constructer=======//
//              Call Init()=========================//
//(void)Link(str file): For derived class constructer/
//              Load filename to chain, if fail, make/
//              New tree.===========================//
//(Bool)LoadFile(str file): Load root file to chain=//
//              if chain have no entries, return 0==//
//(Int)Identify(): return state, 1: new tree active=//
//              2: chain active=====================//
//(Bool)Setstate(Int_t stat): set state, 1 or 2=====//
//(Int)GetEntry(Long64 entry): same as tree=========//
//(Int)GetEntries(): same as tree===================//
//(void)Show(Long64 entry): same as tree============//
//(void)Fill(): Fill tree if tree active============//
//(Int)Write(const char name=0, Int option=0, Int bufsize=0):
//              same as tree, Write for new tree active.//

#ifndef nbodytools_h
#define nbodytools_h

#include <uftools.h>
//root library======================================//
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TEntryList.h>
//STL===============================================//
#include <iostream>
#include <fstream>
#include <string>

class nbodytools{
public:
  TFile *f;       // For new tree store
  TTree *ftree;    // Tree for create new files
  TChain *fchain; // Chain for collect files
  std::string treename;  // Tree name
  std::string treeintro;  // Tree introduction
  Int_t state;  // indicater: 1 for Tree active, 2 for chain active.

  //Function==========================================//
  nbodytools(): f(0), ftree(0), fchain(0), treename(""), treeintro("") {}
  nbodytools(std::string name): f(0), ftree(0), fchain(0), treename(name),treeintro("") {}
  nbodytools(std::string name,std::string intro): f(0), ftree(0), fchain(0), treename(name),treeintro(intro) {}
  virtual void Link();
  virtual void Link(std::string filename);
  virtual ~nbodytools();
  virtual Bool_t LoadFile(std::string filename); //Load root to Chain
  virtual Bool_t LoadList(std::string filename); //Load root list in listfile 
  virtual Int_t Identify(); //show state, 1 for new tree active, 2 for chain active
  virtual Bool_t Setstate(Int_t stat); //set active state
  virtual Int_t GetEntry(Long64_t entry); // get entry for chain or new tree;
  virtual Int_t GetEntries(); // get total number for chain or new tree;
  virtual Int_t GetEntries(const char* cut);
  virtual Int_t GetListEntry(Long64_t entry, TEntryList *tel); // get entry number for chain if entrylist set);
  virtual Double_t* GetV1();
  virtual Double_t* GetV2();
  virtual Double_t* GetV3();
  virtual Double_t* GetV4();
  virtual void Show(Long64_t entry=-1); //show entry for chain or new tree;
  virtual void Fill();
  virtual void Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
  //  virtual void setinit(Int_t init_ns, Int_t init_np, Int_t init_nb);
  virtual Long64_t Draw(const char* varexp, const char* selection="", Option_t* option = "", Long64_t nentries = 1000000000, Long64_t firstentry = 0);
protected:
  //  Int_t initns, initnp, initnb;
  virtual void Init();
  //  virtual std::string selstar(std::string nindex);
  //  virtual std::string selplanet(std::string nindex);
};

//nbodytools==========================================//
void nbodytools::Link()
{
  f=0;
  ftree=0;
  fchain=new TChain(treename.c_str());
  state=2;
  Init();
}

void nbodytools::Link(std::string filename)
{
  f = new TFile(filename.c_str(),"update");
  f->GetObject(treename.c_str(),ftree);
  if(!ftree)
  {
    ftree=new TTree(treename.c_str(),treeintro.c_str());
    state=1;
    Init();
  }
  else if(!ftree->GetEntries())
  {
    f->Delete((treename+";1").c_str());
    ftree=new TTree(treename.c_str(),treeintro.c_str());
    state=1;
    Init();
  }
  else
  {
    fchain=new TChain(treename.c_str());
    fchain->AddFile(filename.c_str());
    state=2;
    Init();
  }
}

void nbodytools::Init()
{
  std::cout<<"Basic Initial.\n";
}

//destructer========================================//
nbodytools::~nbodytools()
{
  if (fchain) delete fchain->GetCurrentFile();
  if (ftree) delete ftree->GetCurrentFile();
  //  if (f) f->Close("R");
}

//Function==========================================//
//--07/30/12 22:30-Load root file to chain--------------//
Bool_t nbodytools::LoadFile(std::string filename)
{
  fchain->AddFile(filename.c_str());
#ifdef DEBUG
  std::cout<<"LoadFile for chain\n";
#endif
  if (!fchain->GetEntries()) return 0;
  else return 1;
}

Bool_t nbodytools::LoadList(std::string filename)
{
#ifdef DEBUG
  std::cout<<"LoadList\n";
#endif
  ifstream ifile(filename.c_str());
  if (!ifile.is_open())
  {
    std::cerr<<"Error: Filelist "<<filename<<" is not found!\n";
    return 0;
  }
  std::string tmp;
  while (1)
  {
    ifile>>tmp;
    if (ifile.eof()) break;
    if (!LoadFile(tmp)) std::cerr<<"Warning: File "<<tmp<<" is empty!\n";
  }
  return 1;
}

Int_t nbodytools::Identify()
{
  return state;
}

Bool_t nbodytools::Setstate(Int_t stat)
{
  state=stat;
  Init();
  if (state==1||state==2)
    return 1;
  return 0;
}

Int_t nbodytools::GetEntry(Long64_t entry)
{
  if (state==1&&ftree) return ftree->GetEntry(entry);
  else if (state==2&&fchain) return fchain->GetEntry(entry);
  else
  {
    std::cerr<<"Error: state not right or tree/chain empty!\n";
    return 0;
  }
}

Int_t nbodytools::GetEntries()
{
  if (state==1&&ftree) return ftree->GetEntries();
  else if (state==2&&fchain) return fchain->GetEntries();
  else
  {
    std::cerr<<"Error: state not right or tree/chain empty!\n";
    return 0;
  }
}

Int_t nbodytools::GetEntries(const char* cut)
{
  if (state==1&&ftree) return ftree->GetEntries(cut);
  else if (state==2&&fchain) return fchain->GetEntries(cut);
  else
  {
    std::cerr<<"Error: state not right or tree/chain empty!\n";
    return 0;
  }
}

Int_t nbodytools::GetListEntry(Long64_t entry, TEntryList *tel)
{
  Int_t treenum=0;
  Int_t tentry=tel->GetEntryAndTree(entry,treenum);
  return tentry+fchain->GetTreeOffset()[treenum];
}

void nbodytools::Show(Long64_t entry)
{
  if (state==1&&ftree)  ftree->Show(entry);
  else if (state==2&&fchain)  fchain->Show(entry);
  else std::cerr<<"Error: state not right or tree/chain empty!\n";
}

void nbodytools::Fill()
{
  if (state==1&&ftree) ftree->Fill();
  else std::cerr<<"Error: state not right or tree empty!\n";
}

void nbodytools::Write(const char* name, Int_t option, Int_t bufsize)
{
  f->cd();
  if (state==1&&ftree) ftree->Write(name, option, bufsize);
  else std::cerr<<"Error: state not right or tree empty!\n";
}

Long64_t nbodytools::Draw(const char* varexp, const char* selection, Option_t* option, Long64_t nentries, Long64_t firstentry)
{
  if (state==1)
    return ftree->Draw(varexp,selection,option,nentries,firstentry);
  else if (state==2)
    return fchain->Draw(varexp,selection,option,nentries,firstentry);
  else
  {
    std::cerr<<"Error: state not right!\n";
    return -1;
  }
}

Double_t *nbodytools::GetV1()
{
  if (state==1)
    return ftree->GetV1();
  else if (state==2)
    return fchain->GetV1();
  else
  {
    std::cerr<<"Error: state not right!\n";
    return 0;
  }
}

Double_t *nbodytools::GetV2()
{
  if (state==1)
    return ftree->GetV2();
  else if (state==2)
    return fchain->GetV2();
  else
  {
    std::cerr<<"Error: state not right!\n";
    return 0;
  }
}

Double_t *nbodytools::GetV3()
{
  if (state==1)
    return ftree->GetV3();
  else if (state==2)
    return fchain->GetV3();
  else
  {
    std::cerr<<"Error: state not right!\n";
    return 0;
  }
}

Double_t *nbodytools::GetV4()
{
  if (state==1)
    return ftree->GetV4();
  else if (state==2)
    return fchain->GetV4();
  else
  {
    std::cerr<<"Error: state not right!\n";
    return 0;
  }
}

#endif
