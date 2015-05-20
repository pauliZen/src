#include <cstdio>
#include <cmath>

// use bins
//extern "C" void surfacedensity(int n, float* x, float* y, float* z, float* weight, float* rs, float xbin, float ybin, float xmin, float xmax, float ymin, float ymax) {
//  
//}  
  
extern "C" void surfacedensity(int n, float* x, float* y, float* weight, float* m, int rbin, float rmax, float rmin, float* rshell, float* rden, float* rm, int* rcount, float* rarea) {
  float lmin=log10(rmin);
  float scale=(float)rbin/(log10(rmax)-lmin);
  for (int i=rbin-1;i>=0;i--) {
    rden[i]=0.0;
    rm[i]=0.0;
    rshell[i]=pow(10.0,(i+1)/scale+lmin);
    rcount[i]=0;
    rarea[i]=3.1415926*rshell[i]*rshell[i];
    if(i<rbin-1) rarea[i+1]=rarea[i+1]-rarea[i];
  }
  
  float rmin2=rmin*rmin;
  float rmax2=rmax*rmax;
  //  int outcouter=0;
  for (int i=0;i<n;i++) {
    float r2=x[i]*x[i]+y[i]*y[i];
    if (r2>rmin2) {
      if (r2<rmax2) {
        int nlr=(int)((0.5*log10(r2)-lmin)*scale);
        if(nlr<rbin) {
          //          if (r2>rshell[nlr]*rshell[nlr] || (nlr>0 && r2<rshell[nlr-1]*rshell[nlr-1])) printf("Not match: r=%f; rshell[i-1]=%f; rshell[i]=%f; nc=%d\n",sqrt(r2),rshell[nlr],rshell[nlr-1],nlr);
          rden[nlr] +=weight[i];
          rm[nlr] +=m[i];
          rcount[nlr]++;
        }
//         else {
//           outcouter++;
//         }
      }
    } else {
      rden[0] +=weight[i];
      rm[0] +=m[i];
      rcount[0]++;
    }
  }
  for (int i=0;i<rbin;i++) {
    rden[i] /=rarea[i];
    rm[i] /=rarea[i];
    // Get the distance which devides the shell into two parts with same areas.
    if(i>0) rshell[i]=sqrt(0.5*(rshell[i]*rshell[i]+rshell[i-1]*rshell[i-1]));
    //if(i>0)    rshell[i+1]=sqrt(rshell[i+1]*rshell[i]);
  }
  // sqrt(0.5)=0.707107
  rshell[0]=0.707107*rshell[0];
  
  //  printf("Out counts = %d\n",outcouter);
}
