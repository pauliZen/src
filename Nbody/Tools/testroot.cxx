#include "uftools.h"
#include <iostream>
#include <string>
#include "TFile.h"
#include "nbodyout.h"
#include "nbodyhfm.h"

int main()
{
  nbodyout nout;
  if (nout.LoadFile("bdata.root"))
  {
    nbodyhfm nhfm("test_result.root");
    nout.Fillhfm(nhfm);
    std::cout<<"Finished\n";
  }
  return 0;
}
