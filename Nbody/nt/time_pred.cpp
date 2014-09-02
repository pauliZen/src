#include "time_pred.h"

#include <cmath>
#include <cassert>

// 1rd force order time prediction========================//
double time_pred_init(double eta, force *p){
  assert(eta!=0);
  assert(p->f1!=0);
  return sqrt(eta*dot(p->f,p->f)/dot(p->f1,p->f1));
}

// 3rd force order time prediction========================//
double time_pred(double eta, force_corr *p){
  double f=dot(p->f,p->f);
  double f1=dot(p->f1,p->f1);
  double f2=dot(p->f2,p->f2);
  double f3=dot(p->f3,p->f3);
  double res=sqrt(eta*(sqrt(f*f2)+f1)/(sqrt(f1*f3)+f2));
  assert(res==res);
  return res;
}
