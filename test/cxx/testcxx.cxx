#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

int main(int argc, char *argv[])
{
  stringstream sstr;
  string t1;
  int t2=0;
  sstr.str("");
  sstr.clear();
  sstr<<"dsf";
  sstr>>t1;
  sstr>>t2;
  if(sstr.str()=="dsf")
    cout<<"match\n";
  cout<<t1<<" "<<t2<<endl;
  return 0;
}
  

