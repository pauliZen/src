#include <iostream>

using namespace std;

int main()
{
  for (int j=10;j<100;j=j+10)
    for (int i=1;i<10;i++)
      {
	if (i==4)
	  break;
	else
	  cout<<i<<" "<<j<<endl;
      }
  cout<<"finished"<<endl;
  return 0;
}
