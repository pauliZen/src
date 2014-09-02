#ifndef bhdatadraw_h
#define bhdatadraw_h

#include <string>

class bhdatadraw{
public:
  TFile   *fr, *fb;
  TChain  *fe;
  bhdatadraw(std::string resultname, std::string bhparname, std::string dEstarttree);
private:
  
};

#endif
