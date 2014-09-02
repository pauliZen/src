//base class for data reading class=================//
//nbodybase=========================================//
//Construct:() all zero=============================//
//          (str name) treename(name)===============//
//Function:=========================================//
//(void) Link(): for constructer in derived class===//
//               call Init();=======================//
//(Int)GetEntry(Long64 entry)...====================//
//(Bool)LoadFile(str file): Load file for chain=====//
//(void)Show(Long64 entry)...=======================//

#ifndef nbodybase_h
#define nbodybase_h

//My library========================================//
#include <uftools.h>
//root library======================================//
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
//STL===============================================//
#include <string>
#ifdef DEBUG
#include <iostream>
#endif

class nbodybase {
public :
  TChain          *fchain;   //!pointer to the analyzed TTree or TChain
  std::string    treename;   //treename to initial chain

  nbodybase(): fchain(0), treename("") {}
  nbodybase(std::string name): fchain(0), treename(name) {} ;
  virtual ~nbodybase();
  //  virtual Int_t    Cut(Long64_t entry);
  virtual void     Link();     //call init() for derived class chain
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Bool_t   LoadFile(std::string filename);
  virtual void     setinit(Int_t ns, Int_t np, Int_t nb);
  virtual Bool_t   selstar(Int_t n[], Int_t nindex);
  virtual Bool_t   selplanet(Int_t n[], Int_t nindex);
  virtual Int_t    GetEntries(std::string cut=""); // get total number for chain or new tree;

  //  virtual void     Loop();
  //  virtual void     Fillter();
  //  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
protected:
  virtual void     Init();
  Int_t endns, endnp, endnb; //initial star planet binary range (endns=initns; endnp=initns+initnp; endnb=initns+initnp+initnb)
};

//Members===========================================//
void nbodybase::Link()
{
  fchain=new TChain(treename.c_str());
  fchain->SetMakeClass(1);
  Init();
}

nbodybase::~nbodybase()
{
   if (!fchain) return;
   delete fchain->GetCurrentFile();
}

Int_t nbodybase::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fchain) return 0;
   return fchain->GetEntry(entry);
}

Int_t nbodybase::GetEntries(std::string cut)
{
  if (cut=="") return fchain->GetEntries();
  else return fchain->GetEntries(cut.c_str());
}

Bool_t nbodybase::LoadFile(std::string filename)
{
  fchain->AddFile(filename.c_str());
  if (!fchain->GetEntries()) return 0;
  return 1;
}

void nbodybase::setinit(Int_t ns, Int_t np, Int_t nb)
{
  endns=ns;
  endnp=ns+np;
  endnb=endnp+nb;
}

void nbodybase::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
#ifdef DEBUG
  std::cout<<"Nbodybase initial.\n";
#endif  
}

void nbodybase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fchain) return;
   fchain->Show(entry);
}

Bool_t nbodybase::selstar(Int_t n[], Int_t nindex)
{
  return (n[nindex]>0&&n[nindex]<=endns)||(n[nindex]>endnp&&n[nindex]<=endnb);
}

Bool_t nbodybase::selplanet(Int_t n[], Int_t nindex)
{
  return n[nindex]>endns&&n[nindex]<=endnp;
}
// Long64_t nbodybase::LoadTree(Long64_t entry)
// {
// // Set the environment to read one entry
//    if (!fchain) return -5;
//    Long64_t centry = fchain->LoadTree(entry);
//    if (centry < 0) return centry;
//    if (fchain->GetTreeNumber() != fCurrent) {
//       fCurrent = fchain->GetTreeNumber();
//       Notify();
//    }
//    return centry;
// }
// Bool_t nbodybase::Notify()
// {
//    // The Notify() function is called when a new file is opened. This
//    // can be either for a new TTree in a TChain or when when a new TTree
//    // is started when using PROOF. It is normally not necessary to make changes
//    // to the generated code, but the routine can be extended by the
//    // user if needed. The return value is currently not used.

//    return kTRUE;
// }
// Int_t nbodybase::Cut(Long64_t entry)
// {
// // This function may be called from Loop.
// // returns  1 if entry is accepted.
// // returns -1 otherwise.
//    return 1;
// }
#endif
