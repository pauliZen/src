#include "force.h"
#include "particle.h"
#include "vector.h"

#include <cassert>

bool force_calc(force *target, particle *ptarget, particle *source, const double &acc_criterion) {
  //get ri-rj=========================================//
  double dr[4];
  dr[0]=ptarget->r[0]-source->r[0];
  dr[1]=ptarget->r[1]-source->r[1];
  dr[2]=ptarget->r[2]-source->r[2];
  dr[3]=dot(dr);

  assert(dr[3]>0);
  //get force ij======================================//
  double a=source->mass/dr[3];
  if ( a>acc_criterion ) return false;
  double mor=a/sqrt(dr[3]);
  target->f[0] +=-mor*dr[0];
  target->f[1] +=-mor*dr[1];
  target->f[2] +=-mor*dr[2];

  //get vi-vj=========================================//
  double dv[3];
  dv[0]=ptarget->v[0]-source->v[0];
  dv[1]=ptarget->v[1]-source->v[1];
  dv[2]=ptarget->v[2]-source->v[2];

  //get force dot=====================================//
  double rv=dot(dr,dv)/dr[3];
  target->f1[0] +=-mor*dv[0]-3*rv*target->f[0];
  target->f1[1] +=-mor*dv[1]-3*rv*target->f[1];
  target->f1[2] +=-mor*dv[2]-3*rv*target->f[2];

  return true;
}

void part_pred(particle *pred, force *f0,particle *target, double dt) {
  //position prediction to 2rd order==================//
  pred->r[0]=((1.66666666666666667e-01*f0->f1[0]*dt+0.5*f0->f[0])*dt+target->v[0])*dt+target->r[0];
  pred->r[1]=((1.66666666666666667e-01*f0->f1[1]*dt+0.5*f0->f[1])*dt+target->v[1])*dt+target->r[1];
  pred->r[2]=((1.66666666666666667e-01*f0->f1[2]*dt+0.5*f0->f[2])*dt+target->v[2])*dt+target->r[2];

  //velocity prediction to 1st order==================//
  pred->v[0]=(0.5*f0->f1[0]*dt+f0->f[0])*dt+target->v[0];
  pred->v[1]=(0.5*f0->f1[1]*dt+f0->f[1])*dt+target->v[1];
  pred->v[2]=(0.5*f0->f1[2]*dt+f0->f[2])*dt+target->v[2];
}

void force_corr::fc_calc(force *f0,double dt) {
  assert(dt>0);
  double df[3],sf1[3];

  //f0-f==============================================//
  df[0]=f0->f[0]-f[0];
  df[1]=f0->f[1]-f[1];
  df[2]=f0->f[2]-f[2];

  //f0dot+fdot========================================//
  double p2fix=2/(dt*dt);
  sf1[0]=f0->f1[0]+f1[0];
  sf1[1]=f0->f1[1]+f1[1];
  sf1[2]=f0->f1[2]+f1[2];

  //f2================================================//
  f2[0]=p2fix*(-3*df[0]-(f0->f1[0]+sf1[0])*dt);
  f2[1]=p2fix*(-3*df[1]-(f0->f1[1]+sf1[1])*dt);
  f2[2]=p2fix*(-3*df[2]-(f0->f1[2]+sf1[2])*dt);

  //f3================================================//
  double p3fix=3*p2fix/dt;
  f3[0]=p3fix*(2*df[0]+sf1[0]*dt);
  f3[1]=p3fix*(2*df[1]+sf1[1]*dt);
  f3[2]=p3fix*(2*df[2]+sf1[2]*dt);
}

void part_corr(particle *target, particle *pred, force_corr *fc, double dt) {
  assert(dt>0);
  double dt2=dt*dt;
  double dt4=dt2*dt2;
  double dt3=dt2*dt;
  double dt5=dt4*dt;
  //position==========================================//
  target->r[0]=pred->r[0]+4.16666666666666667e-02*fc->f2[0]*dt4+8.33333333333333333e-03*fc->f3[0]*dt5;
  target->r[1]=pred->r[1]+4.16666666666666667e-02*fc->f2[1]*dt4+8.33333333333333333e-03*fc->f3[1]*dt5;
  target->r[2]=pred->r[2]+4.16666666666666667e-02*fc->f2[2]*dt4+8.33333333333333333e-03*fc->f3[2]*dt5;
  //velocity==========================================//
  target->v[0]=pred->v[0]+1.66666666666666667e-01*fc->f2[0]*dt3+4.16666666666666667e-02*dt4;
  target->v[1]=pred->v[1]+1.66666666666666667e-01*fc->f2[1]*dt3+4.16666666666666667e-02*dt4;
  target->v[2]=pred->v[2]+1.66666666666666667e-01*fc->f2[2]*dt3+4.16666666666666667e-02*dt4;
}
