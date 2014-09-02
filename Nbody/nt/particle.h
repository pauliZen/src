#ifndef particle_h
#define particle_h

// Provide particle structure defination
//  particle: basic structure
//  particle_header: links table for particle

#include <cassert>

#ifndef NAN_CHECK(val)
#define NAN_CHECK(val) assert((val) == (val));
#endif

//basic particle structure==========================//
struct particle{
  double mass, r[3], v[3];

  //instruction=======================================//
  particle() {} 
  particle(double m, double x[3], double v[3]) {
    load(m,x[0],x[1],x[2],v[0],v[1],v[2]);
  }
  particle(double m, double x, double y, double z, double vx, double vy, double vz) {
    load(m,x,y,z,vx,vy,vz);
  }

  //load data=========================================//
  void load(double m, double x, double y, double z, double vx, double vy, double vz){
    NAN_CHECK(m);
    NAN_CHECK(x);
    NAN_CHECK(y);
    NAN_CHECK(z);
    NAN_CHECK(vx);
    NAN_CHECK(vy);
    NAN_CHECK(vz);

    mass=m;
    r[0]=x;r[1]=y;r[2]=z;
    v[0]=vx;v[1]=vy;v[2]=vz;
  }
};

//link table for particle===========================//
struct particle_link{
  int now;
  particle_link* inext;

  particle_link(int n): now(n), inext(0) {}
  ~particle_link(){
    now=0;
    if(inext) delete inext;
  }
};

//link header ======================================//
struct particle_header{
  int ntot;
  particle_link* first;
  particle_link* last;
  particle_link* pbefore;
  particle_link* pnext;

  particle_header(): ntot(0), first(0), last(0), pnext(0), pbefore(0) {}
  ~particle_header(){
    clear();
  }

  void clear()
  {
    last=0;
    pnext=0;
    pbefore=0;
    if(first) delete first;
    ntot=0;
  }
  
  void push_back(int inext){
    if (!ntot)
    {
      first=new particle_link(inext);
      assert(first);
      last=first;
      pnext=first;
      ntot++;
    }
    else
    {
      last->inext=new particle_link(inext);
      last=last->inext;
      assert(last);
      ntot++;
    }
  }

  //return now index==================================//
  int now(){
    assert(pnext);
    return pnext->now;
  }

  //next particle, return now particle index==========//
  void next() {
    assert(ntot);
    assert(pnext);
    pbefore=pnext;
    if (pnext!=last) pnext=pnext->inext;
    else pnext=0;
  }

  //initial pnext, pbefore============================//
  void goback() {
    assert(ntot);
    pnext=first;
    pbefore=0;
  }

  //remove pnext, return its address=================//
  particle_link* drop_now() {
    assert(ntot);
    if (pbefore) pbefore->inext=pnext->inext;
    else first=pnext->inext;
    ntot--;
    particle_link* res=pnext;
    pnext=pnext->inext;
    return res;
  }

  void push_back(particle_link* pnew) {
    if (ntot) last->inext=pnew;
    else {
      first=pnew;
      last=first;
      pnext=first;
    }
    ntot++;
    pnew->inext=0;
  }
};

#endif
