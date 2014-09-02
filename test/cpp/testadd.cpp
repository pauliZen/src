#include <iostream>
#include <string>
#include <uftools.h>
using namespace std;
int main(int argc, char* argv[])
{
  if (argc==3)
  {
    int t=to<int>(argv[1]);
    //    cout<<"t"<<t<<endl;
    if (to<char>(argv[2])=='i')
    {
      for (int i=0;i<t;i++)
      {
        s += 0.5;
      }
      cout<<"i"<<s<<endl;
    }
    else if (to<char>(argv[2])=='d')
    {
      double s=0;
      while (s<t) s=s+1.0;
      cout<<"d"<<s<<endl;
    }
  }
  return 0;
}
