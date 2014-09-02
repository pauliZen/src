#include <iostream>

typedef int (*func1) (const int&, const int&);

int pu(const int& a, const int& b)
{
  return a+b;
}

int ct(func1 sdf)
{
  std::cout<<sdf(1,2)<<std::endl;
}

int main(int argc, char* argv[])
{
  ct(pu);
  return 0;
}
