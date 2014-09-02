#ifndef force_h
#define force_h

// provide force structure defination for hermit4

#include "particle.h"

//Force structure with 2 order======================//
struct force{
  double f[3];      // force
  double f1[3];     // force 1st derivation
};

//Add force a and b to tot==========================//
void force_add(force &tot, const force &a, const force &b) {
  tot.f[0]=a.f[0]+b.f[0];
  tot.f[1]=a.f[1]+b.f[1];
  tot.f[2]=a.f[2]+b.f[2];

  tot.f1[0]=a.f1[0]+b.f1[0];
  tot.f1[1]=a.f1[1]+b.f1[1];
  tot.f1[2]=a.f1[2]+b.f1[2];
}

//high order corrector for force====================//
struct force_corr{
  double f[3];     // predicted force
  double f1[3];    // predicted 1st force derivation
  double f2[3];    // 2nd force derivation corrector
  double f3[3];    // 3rd force derivation corrector

  //get force derivation corrector from f,fd for target=====//
  void fc_calc(force *f0, double dt);
};

void force_corr_add(force_corr &tot, const force &a, const force &b) {
  tot.f[0]=a.f[0]+b.f[0];
  tot.f[1]=a.f[1]+b.f[1];
  tot.f[2]=a.f[2]+b.f[2];

  tot.f1[0]=a.f1[0]+b.f1[0];
  tot.f1[1]=a.f1[1]+b.f1[1];
  tot.f1[2]=a.f1[2]+b.f1[2];
}

//get f and fdot from source, only add when less than acceleration//
//  return true if add=====//
bool force_calc(force *target, particle *ptarget, particle *source, const double &acc_criterion);

//get force initial=================================//
void force_initial(int n, force *f_list) {
  memset(f_list,0,sizeof(force)*n);
}

//predict position and velocity=======================//
void part_pred(particle *pred, force *f0, particle *target, double dt);

//correct position and velocity=====================//
void part_corr(particle *target, particle *pred, force_corr *fc, double dt);
#endif
