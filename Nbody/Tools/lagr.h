// Calculation of lagrangian radii, average mass, number of particles, average velocities, velocity dispersions
// output: (total, single, binary seperately)
//  R_lagr: Lagrangian radii
//  <M>   : Average mass
//  N     : Number of stars
//  Mb    : Binary mass in R_lagr
//  Nb    : Binary number in R_lagr
//  <V>   : Average velocity
//  <V_x> : Average velocity in x-axis
//  <V_y> : Average velocity in y-axis
//  <V_z> : Average velocity in z-axis
//  <V_r> : Average velocity in r-axis
//  <V_t> : Average velocity in t-axis
//  <S>   : Velocity dispersion square  
//  <S_x> : Velocity dispersion square in x-axis
//  <S_y> : Velocity dispersion square in y-axis
//  <S_z> : Velocity dispersion square in z-axis
//  <S_r> : Velocity dispersion square in r-axis
//  <S_t> : Velocity dispersion square in t-axis
//  <V_rot>: Average rotational velocity in x-y plane
//  <S_rot>: Velocity dispersion square of rotation in x-y plane
//  PMb   : Primordial binaries mass in R_lagr
//  PNb   : Primordial binaries number in R_lagr

#pragma once

extern "C" void lagr(float time, int N_SINGLE, int N_BINARY, int N_MERGER,bool fshell, bool fbres, float *mass, float *x1, float *x2, float *x3, float *v1, float *v2, float *v3, float *bm1=NULL, float *bm2=NULL, float *bxc1=NULL, float *bxc2=NULL, float *bxc3=NULL, float *bvc1=NULL, float *bvc2=NULL, float *bvc3=NULL, int *bn1=NULL, int *bn2=NULL, float *mm1=NULL, float *mm2=NULL, float *mm3=NULL, float *mxc1=NULL, float *mxc2=NULL, float *mxc3=NULL, float *mvc1=NULL, float *mvc2=NULL, float *mvc3=NULL );
