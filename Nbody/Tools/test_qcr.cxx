#include "uftools.h"
#include <iostream>
#include <string>
#include "TFile.h"
#include "nbodyquater.h"
#include "nbodyqcr.h"

int main()
{
  nbodyquater quat;
  if (quat.LoadFile("test_body_0.root"))
  {
    quat.setinit(1000,1000,200);
    quat.Fillqcr("test_qcr.root");
    std::cout<<"Finished\n";
  }
  return 0;
}
