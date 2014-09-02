#include "rootio.h"

#include <iostream>
#include <string>
#include <cassert>
#include <uftools.h>
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"

bool BranchFormat::get(std::string form) {
  bformat=form;
  name="";
  dimension=0;
  int i=0;
  while(i<form.size()&&form[i]!='['&&form[i]!='/'){
    name += form[i];
    i++;
  }
#ifdef DEBUG
  std::cerr<<name<<std::endl;
#endif  
  assert(i<form.size());
  std::string tmp="";
  while(i<form.size()&&form[i]=='[') {
    tmp = "";
    while(i<form.size()&&form[i]!=']'){
      tmp += form[i];
      i++;
    }
    assert(i<form.size());
    i++;
    if (!nsize) nsize=new int[3];
    nsize[dimension]=to<int>(tmp);
    dimension++;
  }
  if(i<form.size()&&form[i]=='/') type=form[i+1];
  assert(form[i]=='/');
  return true;
}

bool TreeDataFormat::readconfigure(FILE *conf){
  fscanf(conf,"%d",&Nbranch);
  assert(Nbranch>0);
  Format=new BranchFormat[Nbranch];
  for (int i=0;i<Nbranch;i++) {
    char n[50];
    fscanf(conf,"%s",n);
    std::string tmp(n);
    assert(Format[i].get(tmp));
  }
  return true;
}

bool TreeDataFormat::readformat(std::string dataformat) {
  int i=0;
  std::string tmp="";
  while(i<dataformat.size()&&dataformat[i]!=':') {
    tmp +=dataformat[i];
    i++;
  }
  assert(i<dataformat.size());
  Nbranch=to<int>(tmp);
  for (int j=0;j<Nbranch;j++){
    tmp="";
    while(i<dataformat.size()&&dataformat[i]!=':') {
      tmp +=dataformat[i];
    }
    assert(Format[j].get(tmp));
  }
  return true;
}

int TreeDataFormat::setformat(int i, std::string dataformat) {
  if (!Format) return -2;
  if (i>=Nbranch) return -1;
  if(!Format[i].get(dataformat)) return -3;
  return 1;
}

bool mallow(char Type, void* p){
  switch (Type) {
  case 'C': (char**)p=new char*; break;
  case 'B': (Char_t*)p=new Char_t; break;
  case 'b': (UChar_t*)p=new UChar_t; break;
  case 'S': (Short_t*)p=new Short_t; break;
  case 's': (UShort_t*)p=new UShort_t; break;
  case 'I': (Int_t*)p=new Int_t; break;
  case 'i': (UInt_t*)p=new UInt_t; break;
  case 'F': (Float_t*)p=new Float_t; break;
  case 'D': (Double_t*)p=new Double_t; break;
  case 'L': (Long64_t*)p=new Long64_t; break;
  case 'l': (ULong64_t*)p=new ULong64_t; break;
  case 'O': (Bool_t*)p=new Bool_t; break;
  default: return false; 
  }
  return true;
}

bool mallow_arr(char Type, void* p, int size){
  assert(size>=0);
  switch (Type) {
  case 'C': (char**)p=new char*[size]; break;
  case 'B': (Char_t*)p=new Char_t[size]; break;
  case 'b': (UChar_t*)p=new UChar_t[size]; break;
  case 'S': (Short_t*)p=new Short_t[size]; break;
  case 's': (UShort_t*)p=new UShort_t[size]; break;
  case 'I': (Int_t*)p=new Int_t[size]; break;
  case 'i': (UInt_t*)p=new UInt_t[size]; break;
  case 'F': (Float_t*)p=new Float_t[size]; break;
  case 'D': (Double_t*)p=new Double_t[size]; break;
  case 'L': (Long64_t*)p=new Long64_t[size]; break;
  case 'l': (ULong64_t*)p=new ULong64_t[size]; break;
  case 'O': (Bool_t*)p=new Bool_t[size]; break;
  default: return false; 
  }
  assert(p);
  return true;
}

int reduce(int *d, int n) {
  int res=1;
  for (int i=0;i<n;i++){
    assert(d[i]>0);
    res *=d[i];
  }
  return res;
}

void fred(FILE *fin, std::string form, void *d, char type) {
  switch (type) {
  case 'C': fscanf(fin,form.c_str(),(char**)d);break;
  case 'B': fscanf(fin,form.c_str(),(Char_t*)d);break;
  case 'b': fscanf(fin,form.c_str(),(UChar_t*)d);break;
  case 'S': fscanf(fin,form.c_str(),(Short_t*)d);break;
  case 's': fscanf(fin,form.c_str(),(UShort_t*)d);break;
  case 'I': fscanf(fin,form.c_str(),(Int_t*)d);break;
  case 'i': fscanf(fin,form.c_str(),(UInt_t*)d);break;
  case 'F': fscanf(fin,form.c_str(),(Float_t*)d);break;
  case 'D': fscanf(fin,form.c_str(),(Double_t*)d);break;
  case 'L': fscanf(fin,form.c_str(),(Long64_t*)d);break;
  case 'l': fscanf(fin,form.c_str(),(ULong64_t*)d);break;
  case 'O': fscanf(fin,form.c_str(),(Bool_t*)d);break;
  default: break;
  }
} 

std::string rformat(const char &type) {
  switch (type) {
  case 'C': return "%s ";
  case 'B': return "%hhi ";
  case 'b': return "%hhu ";
  case 'S': return "%hi ";
  case 's': return "%hu ";
  case 'I': return "%i ";
  case 'i': return "%u ";
  case 'F': return "%f ";
  case 'D': return "%lf ";
  case 'L': return "%li ";
  case 'l': return "%lu ";
  case 'O': return "%hhi ";
  default: return ""; 
  }
  return "";
}

bool ToTree(FILE* fin, TFile* out, const TreeDataFormat &configure, std::string treename, std::string treetitle, char flag){
  assert(configure.Nbranch>0);
  int nsum=configure.Nbranch;
  int* nsiz=new int[nsum];
  void **dp=new void*[nsum];
  char* uform=new char[nsum];
  std::string* rform=new std::string[nsum];

  assert(out);
  out->cd();
  TTree* tr;
  switch (flag){
  case 'n': tr=new TTree(treename.c_str(),treetitle.c_str()); break;
  case 'u': tr=(TTree*)gDirectory->Get(treename.c_str());break;
  default: return false;
  }
  assert(tr);
  
  for (int i=0;i<nsum;i++) {
    //initial pointer===================================//
    BranchFormat *fp=&configure.Format[i];
    assert(fp->dimension>=0);
    uform[i]=fp->type;
    if (fp->dimension) {
      nsiz[i]=reduce(fp->nsize,fp->dimension);
      mallow_arr(fp->type,dp[i],nsiz[i]);
    }
    else {
      mallow(fp->type,dp[i]);
      nsiz[i]=0;
    }
    rform[i]=rformat(fp->type);
    switch (flag){
    case 'n':
      if(fp->dimension==2) tr->Branch(fp->name.c_str(),&dp[i],fp->bformat.c_str()); 
      else if(fp->dimension<=1) tr->Branch(fp->name.c_str(),dp[i],fp->bformat.c_str()); 
      else return false;
      break;
    case 'u':tr->SetBranchAddress(fp->name.c_str(),dp[i]); break;
    default: return false;
    }
  }
#ifdef DEBUG
  int count=0;
#endif  
  while (fgetc(fin) !=EOF) {
#ifdef DEBUG
    std::cerr<<"Loop "<<count++<<std::endl;
#endif    
    for (int i=0;i<nsum;i++) {
      if (!nsiz[i]) fred(fin,rform[i],dp[i],uform[i]);
      else for(int j=0;j<nsiz[i];j++) fred(fin,rform[i],&dp[i][j],uform[i]);
      std::cerr<<i<<" "<<*((double*)dp[i])<<std::endl;
    }
    tr->Fill();
  }
  out->Write("",TObject::kOverwrite);
  return true;
}
