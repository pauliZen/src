#include "neighbor.h"
#include "force.h"
#include <iostream>
#include <cmath>

bool reg_force(particle &target, force &freg, const int nbmax, neighbor &nbt, double acc_criterion, const &int n, particle *list){
  bool overflow = false;
  force_initial(1,&freg);
  for (int j=0;j<n;j++){
    if(&target!=&list[j]) {
      if(!force_calc(&freg, &target, &list[j], acc_criterion))
        overflow=!nbt.add(j,nbmax);
    }
  }
  return overflow;
}

bool reg_calc(const &int n, particle *list, force *freg_lst, const int nbmax, neighbor *nblist, double acc_criterion) {
  bool overflow = false;
  for (int i=0;i<n;i++){
    if(reg_force(list[i],freg_lst[i], nbmax, nblist[i], acc_criterion, n, list)) {
      std::cerr<<"Neighbor List Overflow for particle "<<i<<std::endl;
      overflow = true;
    }
  }
  return overflow;
}

void reg_pred(double dt, force &target) {
  target.f[0] = target.f[0] + target.f1[0]*dt;
  target.f[1] = target.f[1] + target.f1[1]*dt;
  target.f[2] = target.f[2] + target.f1[2]*dt;
}

bool irr_force(particle &target, force &firr, neighbor &nbt, particle *list, double acc_criterion) {
  bool ierr = false;
  force_initial(1,&firr);
  for (int j=0;j<nbt.neighbor_num;j++) {
    if(!force_calc(&firr,&target,&list[nbt.index[j]],acc_criterion))
      ierr=true;
  }
  return ierr;
}

bool step_forward(particle &target, neighbor &nbt, particle *list, force &firr, force &freg, force_corr &ftcorr, double dt, double acc_criterion) {
  bool ierr = false;
  force ftot0;                 // total force at T0
  force_add(ftot0,firr,freg);  // Firr+Freg 
  
  particle ipred;              // predict particle at T0
  part_pred(&ipred,&ftot0,&target,dt); // predict particle r, v based on ftot0

  reg_pred(dt,freg);           // update Freg to T0 + dt

  // predict irregular force based on ipred;
  if(irr_force(ipred,firr,nbt,list,acc_criterion)) {
    std::cerr<<"Particle "<<j<<" irregular force larger than "<<acc_criterion<<std::endl;
    ierr = true;
  }

  force_add(ftcorr,firr,freg); // Firr+Freg of prediction
  ftcorr.fc_calc(&ftot0,dt);   // calculate force 3-4 order correctors
  
  part_corr(&target, &ipred, &ftcorr, dt);  // correct the particle r and v

  // calculate new irregular force
  if(irr_force(target, firr, nbt, list, acc_criterion)) {
    std::cerr<<"Particle "<<j<<" irregular force larger than "<<acc_criterion<<std::endl;
    ierr = true;
  }
}

double calc_acc_criterion(const force &firr, const force &freg) {
  double fx=firr.f[0]+freg.f[0];
  double fy=firr.f[1]+freg.f[1];
  double fz=firr.f[2]+freg.f[2];
  return 0.1*sqrt(fx*fx+fy*fy+fz*fz);
}
