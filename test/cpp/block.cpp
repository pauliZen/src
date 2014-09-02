#include <iostream>

using namespace std;

void reloop(int &i,int &j, bool **flag) {
  if (i<j&&flag[i][1]) {
    reloop(++i,j,flag);
  }
  else {
    for (int ii=i;ii<j;ii++) cout<<" ";
    cout<<i+1<<endl;
    flag[i][0]=!flag[i][0];
    if (flag[i][0]) flag[i][1]=1;
    else {
      flag[i][1]=1;
      if (--i<0) return;
      flag[i][1]=0;
    }
    reloop(i,j,flag);
  }
}

int main()
{
  bool **flag=new bool*[11];
  for (int i=0;i<11;i++)
  {
    flag[i]=new bool[2];
    flag[i][0]=0;
    flag[i][1]=1;
  }
  int i=0,j=10;
  reloop(i,j,flag);
  cout<<endl;
  for (int i=0;i<10;i++) cout<<flag[i][0]<<" "<<flag[i][1]<<"\t";
  cout<<endl;
  return 0;
}
