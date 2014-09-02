#ifndef intgrt_h
#define intgrt_h

#include <particle.h>

//shift particle ===================================//
void particle_shift(const double3 &x, const double3 &v, const int &num, particle *p);

//Initial chain=====================================//
void chain_init(const double &t, const double3 *force, particle *p, chain *c);

//Chech and update chain member=====================//
void check_chain(particle *p, chain *c);

//Get Omega coefficients
void get_Wij(const particle *p, const chain *c,int option=0);

//Get Ekin, Potential, Acceleration, Transformation coefficient
void get_chain_pars(const particle *p, const double3 *force, chain *c);

//Integrate position================================//
void chain_intgrt_X(const double *intpar, const double &s, particle *p, chain *c);

//Integrate velocity================================//
void chain_intgrt_V(const double *intpar, const double &s, const double3 *force, particle *p, chain *c);

#endif
