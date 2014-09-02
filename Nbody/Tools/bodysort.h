#ifndef bodysort_h
#define bodysort_h

#include <vector>
#include <algorithm>
#include <iostream>

class bodysort{
public:
  int index;
  double peri;
  std::vector<int> n;
  bodysort(int nj, int n1, double iperi, int iindex): index(iindex), peri(iperi)
  { n.push_back(nj); n.push_back(n1); }
  bodysort(int nj, int n1, int n2, double iperi, int iindex): index(iindex), peri(iperi) 
  { n.push_back(nj); n.push_back(n1); n.push_back(n2); }
  bodysort(int nj1, int nj2, int n1, int n2, double iperi, int iindex): index(iindex), peri(iperi)
  { n.push_back(nj1); n.push_back(nj2); n.push_back(n1); n.push_back(n2); }
  virtual void sortn();        //sort vector n with increasing order
  size_t vsize() const;      //return n size
  virtual void reset(std::vector<int> nv, double iperi, int iindex);        //reset all data
  virtual void print();
  virtual int &operator[] (const size_t nindex);
  virtual const int &operator[] (const size_t nindex) const;
};

 size_t bodysort::vsize() const
{
  return n.size();
}

void bodysort::sortn()
{
  std::sort(n.begin(), n.end());
}

void bodysort::print()
{
  for (size_t i=0;i<n.size();i++)
    std::cout<<n[i]<<"\t";
  std::cout<<peri<<"\t"<<index<<std::endl;
}

void bodysort::reset(std::vector<int> nv, double iperi, int iindex)
{
  peri=iperi;
  index=iindex;
  n=nv;
}

int& bodysort::operator[] (const size_t nindex)
{
  if (nindex<n.size()) return n[nindex];
  else if (nindex==n.size()) return index;
  else
  {
    std::cerr<<"Error: nindex out of range when call bodysort::[], return index.\n";
    return index;
  }
}

const int& bodysort::operator[] (const size_t nindex) const
{
  if (nindex<n.size()) return n[nindex];
  else if (nindex==n.size()) return index;
  else
  {
    std::cerr<<"Error: nindex out of range when call bodysort::[], return index.\n";
    return index;
  }
}

bool bodyshort(const bodysort &a, const bodysort &b)
{
  if (a.vsize()!=b.vsize())
  {
    std::cerr<<"Error: compared a and b have different n size!\n";
    return 0;
  }
  for (int i=0;i<a.vsize();i++)
  {
    if (a[i]==b[i]) continue;
    else return a[i]<b[i];
  }
  return a.peri<b.peri;
}

bool bodyequal(const bodysort&a, const bodysort&b)
{
  if (a.vsize()==b.vsize())
  {
    bool eq=1;
    for (size_t i=0;i<a.vsize();i++)
      eq =eq&&a[i]==b[i];
    return eq;
  }
  else return 0;
}

bool indexshort(const bodysort&a, const bodysort&b)
{
  return a.index<b.index;
}

// class sbodysort{
// public:
//   int index;
//   double peri;
//   sbodysort(int inj, int in1, double iperi, int iindex): nj(inj), n1(in1), peri(iperi), index(iindex) {}
//   virtual ~sbodysort();
//   virtual void sortn();
// private:
//   int n[2];
// };

// void sbodysort::sortn()
// {
//   if (nj>n1) SWAP(nj,n1);
// }

// class tbodysort: public sbodysort{
// public:
//   int n2;
//   tbodysort(int inj, int in1, int in2, double iperi, int iindex): sbodysort(inj, in1, iperi, iindex), n2(in2) {}
//   virtual void sortn();
// };
  
// void tbodysort::sortn()
// {
//   int a=n1;
//   if (nj>n1)
//   {
//     n1=nj;
//     nj=a;
//   }
//   a=n2;
//   if (n1>n2)
//   {
//     n2=n1;
//     if (nj>n1)
//     {
//       n1=nj;
//       nj=a;
//     }
//     else n1=a;
//   }
// }

// class qbodysort: public tbodysort{
// public:
//   int nj2;
//   qbodysort(int inj, int inj2, int in1, int in2, double iperi, int iindex): tbodysort(inj, in1, in2, iperi, iindex), nj2(inj2) {}
//   virtual void sortn();
// };

// void qbodysort::sortn()
// {
//   int a=nj2;
//   if (nj>nj2)
//   {
//     nj2=nj;
//     nj=a;
//   }
//   a=n1;
//   if (nj2>n1)
//   {
//     n1=nj2;
//     if (nj>nj2)
//     {
//       nj2=nj;
//       nj=a;
//     }
//     else n1=a;
//   }
//   a=n2;
//   if (n1>n2)
//   {
//     n2=n1;
//     if (nj2>n1)
//     {
//       n1=nj2;
//       if (nj>nj2)
//       {
//         nj2=nj;
//         nj=a;
//       }
//       else nj2=a;
//     }
//     else n1=a;
//   }
// }

#endif
