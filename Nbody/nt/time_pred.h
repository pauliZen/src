#ifndef time_pred_h
#define time_pred_h

// Provide time prediction methods for initialization and each time steps

#include "force.h"

//time prediction for initial step==================//
//   Depend on parameter eta and force particle p   //
time_pred_init(double eta, force *p);

//time prediction for standard step=================//
//   Depend on parameter eta and force particle p   //
time_pred(double eta, force *p);

#endif
