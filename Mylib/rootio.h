//Translate table file to root format===============//
#ifndef ROOTIO_H
#define ROOTIO_H

#include "TROOT.h"
#include "TTree.h"
#include <cstdlib>
#include <string>
#include <iostream>

struct BranchFormat{
  int dimension;      // 0: single 1: array >2: matrix
  int *nsize;         // size of each dimension
  char type;          // Root type of data
  /*        - C : a character string terminated by the 0 character
            - B : an 8 bit signed integer (Char_t)
            - b : an 8 bit unsigned integer (UChar_t)
            - S : a 16 bit signed integer (Short_t)
            - s : a 16 bit unsigned integer (UShort_t)
            - I : a 32 bit signed integer (Int_t)
            - i : a 32 bit unsigned integer (UInt_t)
            - F : a 32 bit floating point (Float_t)
            - D : a 64 bit floating point (Double_t)
            - L : a 64 bit signed integer (Long64_t)
            - l : a 64 bit unsigned integer (ULong64_t)
            - O : [the letter 'o', not a zero] a boolean (Bool_t)     */
  std::string name;   // Name 
  std::string bformat;// Branch format (name[dimension]/type)
  //read format=======================================//
  BranchFormat(): dimension(1), nsize(NULL),type('I'), name(""), bformat("") {}
  BranchFormat(std::string form) {
    if(!get(form)) {
      std::cerr<<"Error: Branch format not correct: "<<form<<std::endl;
    }
  }
  //read format=======================================//
  bool get(std::string form);
};

struct TreeDataFormat{
  int Nbranch;  // Branch number;
  BranchFormat* Format;

  TreeDataFormat(int n): Nbranch(n) {
    Format = new BranchFormat[Nbranch];
  }
  
  TreeDataFormat(FILE *configure_file) {
    if(!readconfigure(configure_file))  {
      std::cerr<<"Error: configure file format not correct\n";
    }
  }
  TreeDataFormat(std::string dataformat) {
    if(!readformat(dataformat) ) {
      std::cerr<<"Error: data format not correct, should be: NBranch:format1:format2:... \n";
    }
  }

  //Read format from file=============================//
  //File style:=======================================//
  //  Number_of_Branch Format1 Format2 ...============//
  bool readconfigure(FILE *conf);

  //Read format from string===========================//
  bool readformat(std::string dataformat);

  //Set i of BranchFormat with dataformat=============//
  // return -1: i >= Nbranch
  // return -2: Format not initialized
  // return -3: dataformat not correct
  int setformat(int i, std::string dataformat);
};

//Transform table to tree===========================//
//  out: root file for storing tree=================//
//  configure: configure structure to describe the  //
//             data structure of new tree           //
//  flag: n: new; u: update                         //
bool ToTree(FILE* fin, TFile* out, const TreeDataFormat &configure, std::string treename, std::string treetitle="", char flag='n');

//bool ToText(TFile* in, FILE* out, const TreeDataFormat &configure, std::string treename, char flag='n');

#endif
