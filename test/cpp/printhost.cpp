#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
  std::cout<<"HOST ";
  char *p=getenv("HOSTNAME");
  std::cout<<p<<std::endl;
  return 0;
}
