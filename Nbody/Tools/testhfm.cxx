#include "uftools.h"
#include <iostream>
#include <string>
#include "TFile.h"
#include "nbodyhfm.h"

int main()
{
  nbodyhfm nhfm("test_result.root");
  std::cout<<nhfm.GetEntries()<<std::endl;
  return 0;
}
