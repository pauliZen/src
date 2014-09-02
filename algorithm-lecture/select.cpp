#include <iostream>

template <typename Data> void max5(int n, Data *list, Data result[5]) {
  for (int i=0;i<5;i++)  {
    result[i]=list[i];
    int position=0;
    for (int j=i+1;j<n;j++) {
      if (result[i]<list[j]) {
        result[i]=list[j];
        position=j;
      }
    }
    list[position]=list[i];
  }
}

int main(int argc, char *argv[]) {

  const int maxn=1000;
  int *d=new int[maxn];
  for (int i=0;i<maxn;i++) d[i]=rand();
  std::cout<<"rand "<<maxn<<" : ";
  for (int i=0;i<maxn;i++) std::cout<<d[i]<<" ";

  int *r=new int[5];
  
  max5(maxn,d,r);
  std::cout<<std::endl<<"max 5: ";
  for (int i=0;i<5;i++) std::cout<<r[i]<<" ";
  std::cout<<std::endl;
  
  return 0;
}
