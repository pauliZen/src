#include "block.h"
#include "timepred.h"
#include "neighbor.h"
#include "force.h"
#include "particle.h"

void block::reloop(int &idep, int &idepmax, particle *list, neighbor *nblist, force *firr, force *freg, const double &eta){
  if (idep<idepmax&&flag[idep][1]) {
    reloop(++idep,idepmax,list,nblist,firr,freg,eta);
  }
  else {
    if (blocks[idep].ntot) {
      for (int i=0;i<blocks[idep].ntot;i++) {
        int index=blocks[idep].now;
        force_corr fcorr;
        step_forward(list[index],nblist[index],list,firr[index],freg[index],fcorr,dtlist[idep]);
        int newdep=locate(time_pred(eta,&fcorr),dtlist[0]);
        if (newdep>idep&&newdep<depth) {
          move(idep,newdep);
          if (newdep>idepmax) idepmax=newdep;
        }
        else if(newdep<idep&&!flag[idep][0]) move(idep,newdep);
        else if(newdep>=depth) {
          std::cerr<<"Small time step "<<dt<<" for "<<pindex<<std::endl;
          exit(0);
        }
        blocks[idep].next();
      }
    }
    flag[idep][0]=!flag[idep][0];
    if (flag[idep][0]) flag[idep][1]=1;
    else {
      flag[idep][1]=1;
      if (--idep<0) return;
      flag[idep][1]=0;
    }
    reloop(idep,idepmax,list,nblist,firr,freg,eta);
  }
}

void block::intgrt(particle *list, neighbor *nblist, force *firr, force *freg, const double &eta) {
  assert(dtlist[depth-1]);
  int ibegin=0,iend=depth-1;
  while (!blocks[ibegin].ntot) ibegin++;
  while (!blocks[iend].ntot) iend--;
  reloop(ibegin,iend,list,nblist,firr,freg,eta);
}

int locate(double dt, double tmax) {
  assert(tmax>0);
  assert(dt>0);
  int tsize=(tmax-0.01dt)/dt;
  unsigned int idep=0;
  while (tsize) {
    tsize=(tsize>>1);
    idep++;
  }
  return idep;
}

