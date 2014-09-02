#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main (int argc, char* argv[])
{
  stringstream sstr;
  string tout;
  if (argc!=1)
    {
      sstr<<argv[1];
      sstr>>tout;
    }
  else
    cin>>tout;

  cout<<tout<<endl;
  return 0;
  
}

  
