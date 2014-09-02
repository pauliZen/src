#ifndef flistsort_h
#define flistsort_h

#include <vector>
#include <string>
#include <uftools.h>
#include <iomanip>

class flistsort{
public:
  int dup,ns, m1, p1, rands;
  double rbar, npr, nbr;
  std::string filename;
  flistsort(int idup, int ins, double irb, double inb, double inp, int im, int ip, int ira, std::string ifilename): dup(idup), ns(ins), rbar(irb), nbr(inb), npr(inp), m1(im), p1(ip), rands(ira), filename(ifilename) {}
};

bool flistshort(const flistsort &a, const flistsort &b)
{
  if (a.ns==b.ns)
    if (a.rbar==b.rbar)
      if (a.nbr==b.nbr)
        if (a.npr==b.npr)
          if (a.m1==b.m1)
            return a.p1<b.p1;
          else return a.m1<b.m1;
        else return a.npr<b.npr;
      else return a.nbr<b.nbr;
    else return a.rbar<b.rbar;
  else return a.ns<b.ns;
}

bool flistequal(flistsort a,flistsort b)
{
  return (a.ns==b.ns&&a.rbar==b.rbar&&a.nbr==b.nbr&&a.npr==b.npr&&a.m1==b.m1&&a.p1==b.p1);
}

class parlist{
public:
  int dup, ns, np, nb, m1, p1;
  double rbar;
  parlist(int idup, int ins, int inp, int inb, int im, int ip): dup(idup), ns(ins), np(inp), nb(inb), m1(im), p1(ip) {}
};
#endif
