#ifndef neighbor_h
#define neighbor_h

// Provide neighbor scheme integration methods

#include "force.h"

// neighbor list structure==========================//
struct neighbor{
  int neighbor_num;   // neighbor number
  int *index;         // list

  //Initial neighbor with maximum num neighborlist====//
  neighbor(int num): neighbor_num(0) {
    index=new int[num];
  }

  ~neighbor(){
    delete index;
  }

  //Add new neighbor, if overflow, return 0============//
  bool add(int i, const int num){
    if (neighbor_num >= num) return false;
    index[neighbor_num++]=i;
    return true;
  }
};

//Calculate maximum neighbor number method========//
int calc_nbmax();

//Calculate acceleration criterion for select neighbor//
double calc_acc_criterion(const force &firr, const force &freg);

//Regular force calculation for all particles=======//
// return true if overflow                          //
bool reg_calc(const &int n, particle *list, force *freg_lst, const int nbmax, neighbor *nblist, double acc_criterion);

//Regular force calculation for target==============//
////If overflow return true=========================//
bool reg_force(particle &target, force &freg, const int nbmax, neighbor &nbt, double acc_criterion, const &int n, particle *list);

//Predict regular force after dt based on f0 of target//
void reg_pred(double dt, force &target);

//Calculate irregular force for target==============//
bool irr_force(particle &target, force &firr, neighbor &nbt, particle *list, double acc_criterion);

//Integrate one step dt for particle target=========//
//  Also update reglular force prediction===========//
//              and irregular force=================//
//  Return true if force larger than acc_criterion  //
bool step_forward(particle &target, neighbor &nbt, particle *list, force &firr, force &freg, force_corr &ftcorr, double dt, double acc_criterion=1E20);

#endif
