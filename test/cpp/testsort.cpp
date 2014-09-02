#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
#include <time.h>

//#include "uftools.h"

void SWAP(double &a, double &b)
{
  double temp=a;
  a=b;
  b=temp;
}

void show(double arr[],int m)
{
  for (int ii=0;ii<m;ii++)
    std::cout<<std::setw(12)<<std::left<<arr[ii];
  std::cout<<std::endl;
  std::cout<<"--------------------------------------------------\n";
}

void quicksort(double arr[], int m)
{
  static const int M=7, NSTACK=64;
  int i,ir,j,k,jstack=-1,l=0;
  double a;
  int *istack=new int[NSTACK];
  if (m<0)
  {
    throw("m is less than zero! should be arr size");
    return;
  }
  ir=m-1;
  //  std::cout<<std::setprecision(6)<<std::showpoint;
  for (;;) {
    //    show(arr,m);
    if (ir-l < M) {
      for (j=l+1;j<=ir;j++) {
        a=arr[j];
        for (i=j-1;i>=l;i--) {
          if (arr[i] <= a) break;
          arr[i+1]=arr[i];
        }
        arr[i+1]=a;
      }
      if (jstack < 0) break;
      ir=istack[jstack--];
      l=istack[jstack--];
    } else {
      k=(l+ir) >> 1;
      SWAP(arr[k],arr[l+1]);
      if (arr[l] > arr[ir]) {
        SWAP(arr[l],arr[ir]);
      }
      if (arr[l+1] > arr[ir]) {
        SWAP(arr[l+1],arr[ir]);
      }
      if (arr[l] > arr[l+1]) {
        SWAP(arr[l],arr[l+1]);
      }
      //      show(arr,m);
      i=l+1;
      j=ir;
      a=arr[l+1];
      //      std::cout<<"a="<<a<<"\ti="<<i<<"\tj="<<j<<std::endl;
      for (;;) {
        do i++; while (arr[i] < a); 
        do j--; while (arr[j] > a); 
        if (j < i) break;
        SWAP(arr[i],arr[j]);
        //        show(arr,m);
      }
      arr[l+1]=arr[j];
      arr[j]=a;
      //      show(arr,m);
      jstack += 2;
      if (jstack >= NSTACK) throw("NSTACK too small in sort."); if (ir-i+1 >= j-l) {
        istack[jstack]=ir;
        istack[jstack-1]=i;
        ir=j-1;
      } else {
        istack[jstack]=j-1;
        istack[jstack-1]=l;
        l=i;
      }
    }
  }
}

int main(int argc, char* argv[])
{
  int tt1,tt2,tt3,tt4,tt5;
  const int num=10000000;
  tt1=clock();
  double *arrb=new double[num];
  tt2=clock();
  for (int i=num-1;i>=0;i--)
    arrb[i]=(double)rand()/RAND_MAX;
  tt3=clock();
  std::vector<double> arra(num);
  tt4=clock();
  for(std::vector<double>::size_type ix=num-1; ix!=0; --ix)
    arra[ix]=(double)rand()/RAND_MAX;
  tt5=clock();
  std::cout<<"initial array: "<<(double)(tt2-tt1)/CLOCKS_PER_SEC<<"\trand array: "<<(double)(tt3-tt2)/CLOCKS_PER_SEC<<"\tinitial vector: "<<(double)(tt4-tt3)/CLOCKS_PER_SEC<<"\trand vector: "<<(double)(tt5-tt4)/CLOCKS_PER_SEC<<std::endl;

  int choose=1;
  if (argc>1)
  {
    std::stringstream sstr;
    sstr.str("");
    sstr.clear();
    sstr<<argv[1];
    sstr>>choose;
  }
  // if(choose==1)
  // {
  //   quicksort(arra,num);
  //   std::cout<<"after vector sort:"<<std::endl;
  //   //    for (int i=0;i<num;i++)
  //   //      std::cout<<arra[i]<<" ";
  // }
  int t1,t2;
  if (choose==2)
  {
    t1=clock();
    quicksort(arrb,num);
    t2=clock();
    std::cout<<"after array sort:"<<std::endl;
    // for (int i=0;i<num;i++)
    //   std::cout<<arrb[i]<<" ";
  }
  else if(choose==3)
  {
    t1=clock();
    std::sort(arra.begin(),arra.end());
    t2=clock();
    std::cout<<"after vector stl sort:"<<std::endl;
        // for (int i=0;i<num;i++)
        //   std::cout<<arrc[i]<<" ";
  }
  std::cout<<(double)(t2-t1)/CLOCKS_PER_SEC<<std::endl;
  return 0;
}
