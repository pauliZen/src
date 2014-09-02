#ifndef intgrt_h
#define intgrt_h

// Provide integrate method for the basic time step DTMax;

#include "particle.h"

// integrate for first step=========================//
void particle_init(const &int n, particle *list);

// integrate for standard step======================//
// Maximum time step DTMax
void particle_intgrt(const &int n, particle *list, const &double dtmax);

#endif
