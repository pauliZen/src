#include "uftools.h"
#include <iostream>
#include <string>
#include "TFile.h"
#include "nbodytriple.h"
#include "nbodytcr.h"

int main()
{
  nbodytriple tri;
  tri.LoadFile("test_body_0.root");
  tri.setinit(1000,1000,200);
  tri.Filltcr("test_tri.root");
  std::cout<<"Finished\n";
  return 0;
}
