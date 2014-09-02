#ifndef particle_h
#define particle_h

// Provide particle structure defination
//  particle: basic structure

#include <cassert>

#ifndef NAN_CHECK
#define NAN_CHECK(val) assert((val) == (val));
#endif

typedef double double3[3];
typedef double double4[4];

//basic particle structure==========================//
struct particle{
  double3 x, v;
  double mass, E;

  //instruction=======================================//
  particle() {} 
  particle(double m, double r[3], double v[3]) {
    load(m,r[0],r[1],r[2],v[0],v[1],v[2]);
  }
  particle(double m, double rx, double ry, double rz, double vx, double vy, double vz) {
    load(m,rx,ry,rz,vx,vy,vz);
  }

  //load data=========================================//
  void load(double m, double rx, double ry, double rz, double vx, double vy, double vz){
    NAN_CHECK(m);
    NAN_CHECK(rx);
    NAN_CHECK(ry);
    NAN_CHECK(rz);
    NAN_CHECK(vx);
    NAN_CHECK(vy);
    NAN_CHECK(vz);

    mass=m;
    x[0]=rx;x[1]=ry;x[2]=rz;
    v[0]=vx;v[1]=vy;v[2]=vz;
  }

};

struct chain_mem{
  //Intgrt value======================================//
  double3 X; // Relative position
  double3 V; // Relative velocity
};

struct chain{
  chain_mem *m;
  int *list;
  double3 *acc;
  double **Wij;
  double4 **rjk;

  //center mass=======================================//
  double mtot;  //total mass
  double3 xc;
  double3 vc;
  
  //paramenters=======================================//
  double Ekin;  //kinetic energy
  double Pot;   //potential
  double W;     //transformation coefficient

  //Intgrt value======================================//
  double t;     //time
  double w;    //transformation coefficient
  double B;    //time momentum

  int num;      //total number of chain particles

  chain(int n): num(n) {
    m=new chain_mem[n-1];
    list=new int[n];
    acc=new double3[n];
    Wij=new double*[n];
    rjk=new double4*[n];
    for (int i=0;i<n;i++) {
      Wij[i]=new double[n];
      rjk[i]=new double4[n];
    }
  }
};

#endif
