#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <uftools.h>

const int NFRAC=8;
const float rfrac[NFRAC]={0.001,0.01,0.1,0.3,0.5,0.7,0.9,1.0};

float sum(int n, float *x){
  float res=0.0;
  if (n>0) {
#pragma omp parallel for reduction ( + : res )
    for (int i=0; i<n; i++) {
      res = res + x[i];
    }
  }
  return res;
}

float dot(float x1, float x2, float x3) {
  return x1*x2 + x2*x2 + x3*x3;
}

float fxovery(float x,float y) {
  if (y>0.0) return x/y;
  else return 0.0;
}

void lagr(float time, int N_SINGLE, int N_BINARY, int N_MERGER, float *mass, float *x1, float *x2, float *x3, float *v1, float *v2, float *v3,
          float *bm1, float *bm2, float *bxc1, float *bxc2, float *bxc3, float *bvc1, float *bvc2, float *bvc3, int *bn1, int *bn2,
          float *mm1, float *mm2, float *mm3, float *mxc1, float *mxc2, float *mxc3, float *mvc1, float *mvc2, float *mvc3,
          bool fshell=true, bool fbres=false) {
  
  //  Single and binary number
  int N_SB = N_SINGLE + N_BINARY;

  //  Initialize the velocity vectors
  int N_TOT = N_SB + N_MERGER;

  //  binary and merger
  int N_BM = N_BINARY + N_MERGER;
  // Resolved case
  if (fbres){
    N_BM = N_BINARY*2 + N_MERGER*3;
  }
  // For total counter, unresolved and resolved case 
  int N_TOTR = N_BM + N_SINGLE;

  float tsmass = sum(N_SINGLE, mass);
  float	tbmass = sum(N_BINARY, bm1) + sum(N_BINARY, bm2);
  float	tmmass = sum(N_MERGER, mm1) + sum(N_MERGER, mm2) + sum(N_MERGER, mm3);
  // Total mass
  float tmass = tsmass + tbmass + tmmass;
  // Treat triple as binary
  tbmass = tbmass + tmmass;

  //  mass limit for different R_lagr
  float *rmass = new float[NFRAC];
  float *rsmass = new float[NFRAC];
  float *rbmass = new float[NFRAC];
  
  for (int i=0;i<NFRAC;i++) {
    rmass[i] = tmass*rfrac[i];
    rsmass[i] = tsmass*rfrac[i];
    rbmass[i] = tbmass*rfrac[i];
  }

  float *r2 = new float[N_TOT];
#pragma omp parallel for
  for (int i=0;i<N_SINGLE;i++) {
    r2[i]=dot(x1[i],x2[i],x3[i]);
  }

#pragma omp parallel for
  for (int i=0;i<N_BINARY;i++) {
    r2[i+N_SINGLE]=dot(bxc1[i],bxc2[i],bxc3[i]);
  }

  for (int i=0;i<N_MERGER;i++) {
    r2[i+N_SB]=dot(bxc1[i],bxc2[i],bxc3[i]);
  }
        
  //  Get distance sorting index
  int *idx = new int[N_TOT];
#pragma omp parallel for
  for (int i=0;i<N_TOT;i++) {
    idx[i] = i;
  }
  quicksort(r2,idx,N_TOT);
  
  // lagrangian radii
  float* rlagr =new float[NFRAC]; 
  float* rslagr=new float[NFRAC]; 
  float* rblagr=new float[NFRAC]; 

  // numbers
  int* nlagr =new int[NFRAC]; 
  int* nslagr=new int[NFRAC];
  int* nblagr=new int[NFRAC];

  // average mass
  float* mlagr =new float[NFRAC];
  float* mslagr=new float[NFRAC];
  float* mblagr=new float[NFRAC];

  // average velocity
  float* vlagr =new float[NFRAC];
  float* vslagr=new float[NFRAC];
  float* vblagr=new float[NFRAC];

  // average x velocity
  float* vxlagr =new float[NFRAC];
  float* vxslagr=new float[NFRAC];
  float* vxblagr=new float[NFRAC];

  // average y velocity
  float* vylagr=new float[NFRAC];
  float* vyslagr=new float[NFRAC];
  float* vyblagr=new float[NFRAC];

  // average z velocity
  float* vzlagr=new float[NFRAC];
  float* vzslagr=new float[NFRAC];
  float* vzblagr=new float[NFRAC];

  // average tangential velocity
  float* vtlagr=new float[NFRAC];
  float* vtslagr=new float[NFRAC];
  float* vtblagr=new float[NFRAC];

  // average radial velocity
  float* vrlagr=new float[NFRAC];
  float* vrslagr=new float[NFRAC];
  float* vrblagr=new float[NFRAC];

  // velocity dispersion
  float* siglagr=new float[NFRAC];
  float* sigslagr=new float[NFRAC];
  float* sigblagr=new float[NFRAC];

  // radial velocity dispersion
  float* sigrlagr=new float[NFRAC];
  float* sigrslagr=new float[NFRAC];
  float* sigrblagr=new float[NFRAC];

  // tangential velocity dispersion
  float* sigtlagr=new float[NFRAC];
  float* sigtslagr=new float[NFRAC];
  float* sigtblagr=new float[NFRAC];

  // x velocity dispersion
  float* sigxlagr=new float[NFRAC];
  float* sigxslagr=new float[NFRAC];
  float* sigxblagr=new float[NFRAC];

  // y velocity dispersion
  float* sigylagr=new float[NFRAC];
  float* sigyslagr=new float[NFRAC];
  float* sigyblagr=new float[NFRAC];

  // z velocity dispersion
  float* sigzlagr=new float[NFRAC];
  float* sigzslagr=new float[NFRAC];
  float* sigzblagr=new float[NFRAC];

  // rotational velocity
  float* vrotlagr=new float[NFRAC];
  float* vrotslagr=new float[NFRAC];
  float* vrotblagr=new float[NFRAC];

  // rotational velocity dispersion
  float* sigrotlagr=new float[NFRAC];
  float* sigrotslagr=new float[NFRAC];
  float* sigrotblagr=new float[NFRAC];

  //	Binary mass/number inside different R_lagr
  float* msblagr=new float[NFRAC];
  int* nsblagr=new int[NFRAC];

  //	Primordial binary mass/number inside different R_lagr
  float* mspblagr=new float[NFRAC];
  int* nspblagr=new int[NFRAC];

  // counter for different R_lagr bins
  int kk = 0;
  int kks = 0;
  int kkb = 0;

  // Number counter
  int nc = 0;
  int ncs = 0;
  int ncb = 0;
  //   Previous counter
  int ncprev  = 0; 
  int ncsprev = 0; 
  int ncbprev = 0; 

  // Mass counter
  float cmass = 0; 
  float bmass = 0; 
  float smass = 0; 

  // Previous counter
  float mcprev = 0;
  float mcsprev = 0;
  float mcbprev = 0;

  // velocity, x,y,z,r,t,rot
  float* vx = new float[N_TOT];
  float* vy = new float[N_TOT];
  float* vz = new float[N_TOT];
  // The radial velocity uses the spherical coordinate system, thus not a vector
  float* vr = new float[N_TOT];
  // Notice the tangential velocity is also vector in (x,y,z) coordinate system
  float** vt = new float*[N_TOT];
  // Average tangetial velocity
  float** vtave  = new float*[N_TOT];
  float** vtbave = new float*[N_TOT];
  float** vtsave = new float*[N_TOT];
  for (int i=0;i<N_TOT;i++){
    vt[i]     = new float[3];
    vtave[i]  = new float[3];
    vtbave[i] = new float[3];
    vtsave[i] = new float[3];
  }
  // rotational velocity
  float* vrot = new float[N_TOT];
  // Initialize mass array
  float*  mmb = new float[N_TOT];

  for (int j=0;j<N_TOT;j++) {
    //  Initialization
    // position
    float rx = 0.0; 
    float ry = 0.0; 
    float rz = 0.0; 
    float ri = sqrt(r2[j]);

    //   Binary/merger case
    if (j>=N_SINGLE){
      // increase binary counter by one
      ncb++;
      if (fbres){
        // increase total counter by one in binary case
        nc++;
        // increase binary counter by one for resolved case
        ncb++;
        //  Merger case
      }
      if (j>=N_SB) {
        if (fbres) {
          // increase total counter by one in merger case
          nc++;
          // increase binary counter by one for resolved case
          ncb++;
        }
        int inx = j - N_SB;
        mmb[j] = mm1[inx]+mm2[inx]+mm3[inx];
        vx[j] = mvc1[inx];
        vy[j] = mvc2[inx]; 
        vz[j] = mvc3[inx]; 
        rx    = mxc1[inx]; 
        ry    = mxc2[inx]; 
        rz    = mxc3[inx]; 
        //   Binary case
      } else{
        int inx = j - N_SINGLE;
        mmb[j] = bm1[inx]+bm2[inx];
        vx[j] = bvc1[inx]; 
        vy[j] = bvc2[inx]; 
        vz[j] = bvc3[inx]; 
        rx    = bxc1[inx]; 
        ry    = bxc2[inx]; 
        rz    = bxc3[inx]; 
      }
    }//   Single case
    else{
      // increase number counter
      ncs++;
      mmb[j] = mass[j];
      rx     = x1[j]; 
      ry     = x2[j]; 
      rz     = x3[j]; 
      vx[j]  = v1[j]; 
      vy[j]  = v2[j]; 
      vz[j]  = v3[j]; 
    }

    //  increase total counter
    nc++;

    //   Get velocity information
    // x-y plane radial velocity * rxy
    float rvxy = rx*vx[j] + ry*vy[j];
    // radial velocity value
    vr[j] = (rvxy + rz*vz[j])/ri;
    // tangential velocity vector
    vt[j][0] = vx[j] - vr[j]*rx/ri;
    vt[j][1] = vy[j] - vr[j]*ry/ri;
    vt[j][2] = vz[j] - vr[j]*rz/ri;
    // x-y plane radial position square
    float rxy2 = rx*rx + ry*ry;
    // rotational velocity
    float vrot1 = vx[j] - rvxy*rx/rxy2;
    float vrot2 = vy[j] - rvxy*ry/rxy2;
    vrot[j] = sqrt(vrot1*vrot1+vrot2*vrot2);
    // rotational direction sign
    float vrotd = vrot1*ry - vrot2*rx;
    if (vrotd<0.0) vrot[j] = -vrot[j];

    //   Check whether need to reach next bin
    if (j>=N_SINGLE) {
      //  Add mass
      bmass += mmb[j];

      //  average velocity
      vxblagr[kkb] += mmb[j]*vx[j]; 
      vyblagr[kkb] += mmb[j]*vy[j]; 
      vzblagr[kkb] += mmb[j]*vz[j]; 
      vrblagr[kkb] += mmb[j]*vr[j]; 
      for (int k=0;k<3;k++) vtbave[kkb][k] += mmb[j]*vt[j][k];
      vrotblagr[kkb] += mmb[j]*vrot[j];

      // increase mass/number counter for binaries in R_lagr
      msblagr[kk] += mmb[j];
      nsblagr[kk]++;
      if (fbres) nsblagr[kk]++;

      // primordial binareis
      if (j<N_SB){
        if (abs(bn1[j-N_SINGLE]-bn2[j-N_SINGLE])==1){
          mspblagr[kk] += mmb[j];
          nspblagr[kk]++;
          if (fbres) nspblagr[kk]++;
        }
      }
      // Go to next bin if mass reach the R_Lagr limit
      if (kkb < NFRAC){
        if ((bmass >= rbmass[kkb]) || ((kkb == NFRAC-1) && (ncb == N_BM))){
          // update mass
          rbmass[kkb] = bmass;
          // Get R_lagr for binary
          rblagr[kkb] = ri;
          // Get number for binary
          nblagr[kkb] = ncb;
          // For shell cases:
          if ((fshell) && (kkb>0)){
            rbmass[kkb] -= mcbprev;
            nblagr[kkb] -= ncbprev;
          }
          mcbprev = bmass;
          ncbprev = ncb;
          // Increase bin index
          kkb++;
          // initial next bins
          if (kkb < NFRAC){
            if ((not fshell) && (nblagr[kkb] == 0)){
              vxblagr[kkb] = vxblagr[kkb-1]; 
              vyblagr[kkb] = vyblagr[kkb-1]; 
              vzblagr[kkb] = vzblagr[kkb-1]; 
              vrblagr[kkb] = vrblagr[kkb-1]; 
              vtbave[kkb] = vtbave[kkb-1];
              vrotblagr[kkb] = vrotblagr[kkb-1];
            }
          }
        }
      }
    } else {
      // Add mass
      smass += mmb[j];

      //  average velocity
      vxslagr[kks] += mmb[j]*vx[j]; 
      vyslagr[kks] += mmb[j]*vy[j]; 
      vzslagr[kks] += mmb[j]*vz[j]; 
      vrslagr[kks] += mmb[j]*vr[j]; 
      for (int k=0;k<3;k++) vtsave[kks][k] += mmb[j]*vt[j][k]; 
      vrotslagr[kks] += mmb[j]*vrot[j];

      // Go to next bin if mass reach the R_lagr limit
      if (kks < NFRAC) {
        if ((smass >= rsmass[kks]) || ((kks == NFRAC-1) && (ncs == N_SINGLE))) {
          // update mass
          rsmass[kks] = smass;
          // Get R_lagr for single
          rslagr[kks] = ri;
          // Get number for single
          nslagr[kks] = ncs;
          // For shell cases:
          if ((fshell) && (kks>0)) {
            rsmass[kks] -= mcsprev;
            nslagr[kks] -= ncsprev;
          }
          mcsprev = smass;
          ncsprev = ncs;
          // increase bin index
          kks++;
          // initial next bins
          if (kks < NFRAC) {
            if((not fshell) && (nslagr[kks] == 0)){
              vxslagr[kks] = vxslagr[kks-1];
              vyslagr[kks] = vyslagr[kks-1];
              vzslagr[kks] = vzslagr[kks-1];
              vrslagr[kks] = vrslagr[kks-1];
              vtsave[kks] = vtsave[kks-1];
              vrotslagr[kks] = vrotslagr[kks-1];
            }
          }
        }
      }
    }

    //   Go to next R_lagr if mass reach limit
    cmass += mmb[j];
    //  average velocity
    vxlagr[kk] += mmb[j]*vx[j];
    vylagr[kk] += mmb[j]*vy[j];
    vzlagr[kk] += mmb[j]*vz[j]; 
    vrlagr[kk] += mmb[j]*vr[j]; 
    for (int k=0;k<3;k++) vtave[kk][k] += mmb[j]*vt[j][k]; 
    vrotlagr[kk] += mmb[j]*vrot[j];

    if (kk < NFRAC) {
      if ((cmass >= rmass[kk]) || ((kk == NFRAC-1) && (nc == N_TOTR))) {
        // update mass
        rmass[kk] = cmass;
        // Get R_lagr 
        rlagr[kk] = ri;
        // Get number
        nlagr[kk] = nc;
        // For shell cases:
        if ((fshell) && (kk>0)){
          rmass[kk] -= mcprev;
          nlagr[kk] -= ncprev;
        }
        mcprev = cmass;
        ncprev = nc;
        // increase bin index
        kk++;
        // Get initial value for next bin 
        if (kk < NFRAC ){
          if (not fshell) {
            // binary counter
            if (nsblagr[kk] == 0) {
              msblagr[kk] = msblagr[kk-1];
              nsblagr[kk] = nsblagr[kk-1];
            }
            if (nspblagr[kk] == 0) {
              mspblagr[kk] = mspblagr[kk-1];
              nspblagr[kk] = nspblagr[kk-1];
            }
            // total counter
            if (nlagr[kk] == 0) {
              vxlagr[kk] = vxlagr[kk-1];
              vylagr[kk] = vylagr[kk-1];
              vzlagr[kk] = vzlagr[kk-1];
              vrlagr[kk] = vrlagr[kk-1];
              vtave[kk] = vtave[kk-1];
              vrotlagr[kk] = vrotlagr[kk-1];
            }
          }
        }
      }
    }
  }

  //   Fill empty bins with neighbor bin values
  if (not fshell) {
    //   Total
    int kn = kk - 1;
    while (kk < NFRAC) {
      rlagr[kk] = rlagr[kn];
      nlagr[kk] = nlagr[kn];
      nsblagr[kk] = nsblagr[kn];
      msblagr[kk] = msblagr[kn];
      nspblagr[kk] = nspblagr[kn];
      mspblagr[kk] = mspblagr[kn];
      vxlagr[kk] = vxlagr[kn];
      vylagr[kk] = vylagr[kn];
      vzlagr[kk] = vzlagr[kn];
      vrlagr[kk] = vrlagr[kn];
      vtave[kk] = vtave[kn];
      vrotlagr[kk] = vrotlagr[kn];
      kk++;
    }
    //   Single
    int ksn = kks - 1;
    while (kks < NFRAC) {
      rslagr[kks] = rslagr[ksn];
      nslagr[kks] = nslagr[ksn];
      vxslagr[kks] = vxslagr[ksn];
      vyslagr[kks] = vyslagr[ksn];
      vzslagr[kks] = vzslagr[ksn];
      vrslagr[kks] = vrslagr[ksn];
      vtsave[kks] = vtsave[ksn];
      vrotslagr[kks] = vrotslagr[ksn];
      kks++;
    }
    //   Binary + Merger
    int kbn = kkb - 1;
    while (kkb < NFRAC){
      rblagr[kkb] = rblagr[kbn];
      nblagr[kkb] = nblagr[kbn];
      vxblagr[kkb] = vxblagr[kbn];
      vyblagr[kkb] = vyblagr[kbn];
      vzblagr[kkb] = vzblagr[kbn];
      vrblagr[kkb] = vrblagr[kbn];
      vtbave[kkb] = vtbave[kbn];
      vrotblagr[kkb] = vrotblagr[kbn];
      kkb++;
    }
  }

  for (int i=0;i<NFRAC;i++){
    // Average mass
    mlagr[i]  = fxovery(rmass[i],nlagr[i]);   
    mslagr[i] = fxovery(rsmass[i],nslagr[i]);
    mblagr[i] = fxovery(rbmass[i],nblagr[i]);
    // Average velocity
    // total
    vxlagr[i]  = fxovery(vxlagr[i]  ,rmass[i]); 
    vylagr[i]  = fxovery(vylagr[i]  ,rmass[i]); 
    vzlagr[i]  = fxovery(vzlagr[i]  ,rmass[i]); 
    vrlagr[i]  = fxovery(vrlagr[i]  ,rmass[i]); 
    for (int j=0;j<3;j++) vtave[i][j] = fxovery(vtave[i][j] ,rmass[i]); 
    vrotlagr[i]= fxovery(vrotlagr[i],rmass[i]); 
    vlagr[i]   = sqrt(dot(vxlagr[i], vylagr[i], vzlagr[i]));
    vtlagr[i]  = sqrt(dot(vtave[i][0],vtave[i][1],vtave[i][2]));
    //single
    vxslagr[i]  = fxovery(vxslagr[i]  ,rsmass[i]); 
    vyslagr[i]  = fxovery(vyslagr[i]  ,rsmass[i]); 
    vzslagr[i]  = fxovery(vzslagr[i]  ,rsmass[i]); 
    vrslagr[i]  = fxovery(vrslagr[i]  ,rsmass[i]); 
    for (int j=0;j<3;j++) vtsave[i][j] = fxovery(vtsave[i][j] ,rsmass[i]); 
    vrotslagr[i]= fxovery(vrotslagr[i],rsmass[i]);
    vslagr[i]   = sqrt(dot(vxslagr[i],vyslagr[i], vzslagr[i]));
    vtslagr[i]  = sqrt(dot(vtsave[i][0], vtsave[i][1], vtsave[i][2]));
    //binary/merger
    if(N_BINARY) {
      vxblagr[i]  = fxovery(vxblagr[i] ,rbmass[i]);
      vyblagr[i]  = fxovery(vyblagr[i] ,rbmass[i]);
      vzblagr[i]  = fxovery(vzblagr[i] ,rbmass[i]);
      vrblagr[i]  = fxovery(vrblagr[i] ,rbmass[i]);
      for (int j=0;j<3;j++) vtbave[i][j] = fxovery(vtbave[i][j] ,rbmass[i]);
      vrotblagr[i]= fxovery(vrotblagr[i],rbmass[i]);
      vblagr[i]   = sqrt(dot(vxblagr[i], vyblagr[i], vzblagr[i]));
      vtblagr[i]  = sqrt(dot(vtbave[i][0],vtbave[i][1],vtbave[i][2]));
    }
  }
    
  //   Loop again to get velocity dispersion
  //   counter for different R_lagr bins
  kk = 0;
  kks = 0;
  kkb = 0;
  //   Number counter
  nc = 0;
  ncs = 0;
  ncb = 0;
  //   Previous counter
  ncprev = 0;
  ncsprev = 0;
  ncbprev = 0;
//
  for (int j=0;j<N_TOT;j++) {
    //  increase total counter
    nc++;
    //   Binary/merger case
    if (j>=N_SINGLE) {
      // increase binary counter by two 
      ncb++;
      if (fbres) {
        // increase total counter by one in binary case
        nc++;
        // increase binary counter by one for resolved case
        ncb++;
        if (j>=N_SB) {
          // For merger case
          nc ++;
          ncb++;
        }
      }
      // x,y,z
      float dx = vx[j] - vxblagr[kkb]; 
      float dy = vy[j] - vyblagr[kkb]; 
      float dz = vz[j] - vzblagr[kkb]; 
      float dr = vr[j] - vrblagr[kkb]; 
      float dt[3];
      for (int k=0;k<3;k++) dt[k]= vt[j][k] - vtbave[kkb][k];
      float drot = vrot[j] - vrotblagr[kkb];
      // mass weighted square
      float dx2 = mmb[j]*dx*dx; 
      float dy2 = mmb[j]*dy*dy; 
      float dz2 = mmb[j]*dz*dz; 
      float dr2 = mmb[j]*dr*dr; 
      float dt2 = mmb[j]*(dt[0]*dt[0] + dt[1]*dt[1] + dt[2]*dt[2]);
      float drot2= mmb[j]*drot*drot;
      // velocity value
      // dispersion
      sigxblagr[kkb] += dx2;
      sigyblagr[kkb] += dy2;
      sigzblagr[kkb] += dz2;
      sigrblagr[kkb] += dr2;
      sigtblagr[kkb] += dt2;
      sigrotblagr[kkb] += drot2;

      // check whether need to increase kkb
      if (ncb-ncbprev==nblagr[kkb]) {
        if (fshell) ncbprev += nblagr[kkb];
        kkb++;
        if ((not fshell) && (kkb < NFRAC)) {
          sigxblagr[kkb] = sigxblagr[kkb-1]; 
          sigyblagr[kkb] = sigyblagr[kkb-1]; 
          sigzblagr[kkb] = sigzblagr[kkb-1]; 
          sigrblagr[kkb] = sigrblagr[kkb-1]; 
          sigtblagr[kkb] = sigtblagr[kkb-1]; 
          sigrotblagr[kkb] = sigrotblagr[kkb-1];
        }
      }
    }
//   Single case
    else {
      // increase number counter
      ncs++;
      // x,y,z
      float dx = vx[j] - vxslagr[kks]; 
      float dy = vy[j] - vyslagr[kks]; 
      float dz = vz[j] - vzslagr[kks]; 
      float dr = vr[j] - vrslagr[kks]; 
      float dt[3];
      for (int k=0;k<3;k++) dt[k]= vt[j][k] - vtsave[kks][k];
      float drot = vrot[j] - vrotslagr[kks];
      // mass weighted square
      float dx2 = mmb[j]*dx*dx; 
      float dy2 = mmb[j]*dy*dy; 
      float dz2 = mmb[j]*dz*dz; 
      float dr2 = mmb[j]*dr*dr; 
      float dt2 = mmb[j]*(dt[0]*dt[0] + dt[1]*dt[1] + dt[2]*dt[2]);
      float drot2= mmb[j]*drot*drot;
      // dispersion
      sigxslagr[kks] += dx2; 
      sigyslagr[kks] += dy2; 
      sigzslagr[kks] += dz2; 
      sigrslagr[kks] += dr2;
      sigtslagr[kks] += dt2;
      sigrotslagr[kks] += drot2;

      // check whether need to increase kks
      if (ncs-ncsprev==nslagr[kks]) {
        if (fshell) ncsprev += nslagr[kks];
        kks++;
        if ((not fshell) && (kks < NFRAC)) {
          sigxslagr[kks] = sigxslagr[kks-1]; 
          sigyslagr[kks] = sigyslagr[kks-1]; 
          sigzslagr[kks] = sigzslagr[kks-1]; 
          sigrslagr[kks] = sigrslagr[kks-1]; 
          sigtslagr[kks] = sigtslagr[kks-1]; 
          sigrotslagr[kks] = sigrotslagr[kks-1];
        }
      }
    }

//   Total                 
    // x,y,z
    float dx = vx[j] - vxlagr[kk]; 
    float dy = vy[j] - vylagr[kk]; 
    float dz = vz[j] - vzlagr[kk]; 
    float dr = vr[j] - vrlagr[kk]; 
    float dt[3];
    for (int k=0;k<3;k++) dt[k]= vt[j][k] - vtave[kk][k];
    float drot = vrot[j] - vrotlagr[kk];
    // mass weighted square
    float dx2 = mmb[j]*dx*dx; 
    float dy2 = mmb[j]*dy*dy; 
    float dz2 = mmb[j]*dz*dz; 
    float dr2 = mmb[j]*dr*dr; 
    float dt2 = mmb[j]*(dt[0]*dt[0] + dt[1]*dt[1] + dt[2]*dt[2]);
    float drot2= mmb[j]*drot*drot;
    // dispersion
    sigxlagr[kk] += dx2;
    sigylagr[kk] += dy2;
    sigzlagr[kk] += dz2;
    sigrlagr[kk] += dr2;
    sigtlagr[kk] += dt2;
    sigrotlagr[kk] += drot2;

    // check whether need to increase kk
    if (nc-ncprev==nlagr[kk]) {
      if (fshell) ncprev += nlagr[kk];
      kk++;
      if ((not fshell) && (kk < NFRAC)) {
        sigxlagr[kk] = sigxlagr[kk-1]; 
        sigylagr[kk] = sigylagr[kk-1]; 
        sigzlagr[kk] = sigzlagr[kk-1]; 
        sigrlagr[kk] = sigrlagr[kk-1]; 
        sigtlagr[kk] = sigtlagr[kk-1]; 
        sigrotlagr[kk] = sigrotlagr[kk-1];
      }
    }
  }

  if (not fshell) {
    int kn = kk - 1;
    while (kk < NFRAC) {
      sigxlagr[kk] = sigxlagr[kn]; 
      sigylagr[kk] = sigylagr[kn]; 
      sigzlagr[kk] = sigzlagr[kn]; 
      sigrlagr[kk] = sigrlagr[kn]; 
      sigtlagr[kk] = sigtlagr[kn]; 
      sigrotlagr[kk] = sigrotlagr[kn];
      kk++;
    }
    int ksn = kks - 1;
    while (kks < NFRAC) {
      sigxslagr[kks] = sigxslagr[ksn]; 
      sigyslagr[kks] = sigyslagr[ksn]; 
      sigzslagr[kks] = sigzslagr[ksn]; 
      sigrslagr[kks] = sigrslagr[ksn]; 
      sigtslagr[kks] = sigtslagr[ksn]; 
      sigrotslagr[kks] = sigrotslagr[ksn];
      kks++;
    }
    int kbn = kkb - 1;
    while (kkb < NFRAC) {
      sigxblagr[kkb] = sigxblagr[kbn]; 
      sigyblagr[kkb] = sigyblagr[kbn]; 
      sigzblagr[kkb] = sigzblagr[kbn]; 
      sigrblagr[kkb] = sigrblagr[kbn]; 
      sigtblagr[kkb] = sigtblagr[kbn]; 
      sigrotblagr[kkb] = sigrotblagr[kbn];
      kkb++;
    }
  }

  // Divide mass
  for (int i=0;i<NFRAC;i++) {
    // total
    sigxlagr[i]  = fxovery(sigxlagr[i]  ,rmass[i]); 
    sigylagr[i]  = fxovery(sigylagr[i]  ,rmass[i]); 
    sigzlagr[i]  = fxovery(sigzlagr[i]  ,rmass[i]); 
    sigrlagr[i]  = fxovery(sigrlagr[i]  ,rmass[i]); 
    sigtlagr[i]  = fxovery(sigtlagr[i]  ,rmass[i]); 
    sigrotlagr[i]= fxovery(sigrotlagr[i],rmass[i]);
    siglagr[i]   = sigxlagr[i] + sigylagr[i] + sigzlagr[i];
    //single
    sigxslagr[i]  = fxovery(sigxslagr[i]  ,rsmass[i]); 
    sigyslagr[i]  = fxovery(sigyslagr[i]  ,rsmass[i]); 
    sigzslagr[i]  = fxovery(sigzslagr[i]  ,rsmass[i]); 
    sigrslagr[i]  = fxovery(sigrslagr[i]  ,rsmass[i]); 
    sigtslagr[i]  = fxovery(sigtslagr[i]  ,rsmass[i]); 
    sigrotslagr[i]= fxovery(sigrotslagr[i],rsmass[i]); 
    sigslagr[i]   = sigxslagr[i] + sigyslagr[i] + sigzslagr[i];
    //binary/merger
    if(N_BINARY) {
      sigxblagr[i]  = fxovery(sigxblagr[i]  ,rbmass[i]); 
      sigyblagr[i]  = fxovery(sigyblagr[i]  ,rbmass[i]); 
      sigzblagr[i]  = fxovery(sigzblagr[i]  ,rbmass[i]); 
      sigrblagr[i]  = fxovery(sigrblagr[i]  ,rbmass[i]); 
      sigtblagr[i]  = fxovery(sigtblagr[i]  ,rbmass[i]); 
      sigrotblagr[i]= fxovery(sigrotblagr[i],rbmass[i]); 
      sigblagr[i]   = sigxblagr[i] + sigyblagr[i] + sigzblagr[i];
    }
  }

  //   Print data 
  printf("%.8e ", time);
  // R_Lagr
  for (int j=0;j<NFRAC;j++) 
    printf("%.8e ", rlagr[j]);
  for (int j=0;j<NFRAC;j++) 
    printf("%.8e ", rslagr[j]);
  for (int j=0;j<NFRAC;j++) 
    printf("%.8e ", rblagr[j]);
  // <M>
  for (int j=0;j<NFRAC;j++) 
    printf("%.8e ", mlagr[j]);
  for (int j=0;j<NFRAC;j++) 
    printf("%.8e ", mslagr[j]);
  for (int j=0;j<NFRAC;j++) 
    printf("%.8e ", mblagr[j]);
  // N
  for (int j=0;j<NFRAC;j++) 
    printf("%d ", nlagr[j]);
  for (int j=0;j<NFRAC;j++) 
    printf("%d ", nslagr[j]);
  for (int j=0;j<NFRAC;j++) 
    printf("%d ", nblagr[j]);
  // Mb in R_lagr
  for (int j=0;j<NFRAC;j++) 
    printf("%.8e ", msblagr[j]);
  // Nb in R_lagr
  for (int j=0;j<NFRAC;j++) 
    printf("%d ", nsblagr[j]);
  // <V>
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vblagr[j]);
  // <V_x>
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vxlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vxslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vxblagr[j]);
  // <V_y>
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vylagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vyslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vyblagr[j]);
  // <V_z>
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vzlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vzslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vzblagr[j]);
  // <V_r>
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vrlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vrslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vrblagr[j]);
  // <V_t>
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vtlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vtslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vtblagr[j]);
  // Sigma^2
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", siglagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigblagr[j]);
  // Sigma_x^2
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigxlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigxslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigxblagr[j]);
  // Sigma_y^2
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigylagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigyslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigyblagr[j]);
  // Sigma_z^2
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigzlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigzslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigzblagr[j]);
  // Sigma_r^2
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigrlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigrslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigrblagr[j]);
  // Sigma_t^2
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigtlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigtslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigtblagr[j]);
  // v_rot
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vrotlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vrotslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", vrotblagr[j]);
  // Sigma_rot^2
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigrotlagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigrotslagr[j]);
  for (int j=0;j<NFRAC;j++)
    printf("%.8e ", sigrotblagr[j]);
  // Primordial Mb in R_lagr
  for (int j=0;j<NFRAC;j++) 
    printf("%.8e ", mspblagr[j]);
  // Primrodial Nb in R_lagr
  for (int j=0;j<NFRAC;j++) 
    printf("%d ", nspblagr[j]);
  printf("\n");
}
