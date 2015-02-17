// get potential of particle list

#include <cstdlib>
#include <stdio.h>
#include <initial.h>
#include <omp.h>
#include <cmath>

//#define NMAX 1000000

//extern "C" void gpupot_send_float(int n, float m[], float x1[], float x2[], float x3[]);
//extern "C" void gpupot(int ni, int list[], double pot[]);

double dis(double x1, double x2, double x3) {
  return sqrt(x1*x1+x2*x2+x3*x3);
}

int main(int argc, char* argv[])
{
  pars_initial init(".pot_data.config");
  init.add("datain","input dataset name","pot_data_in.0.0");
  init.add("dataout","output data name","pot_data.0.0");
  init.initial(argc,argv);

  FILE *fin;
  if ( (fin = fopen(init.gets("datain").c_str(),"r")) == NULL) {
    fprintf(stderr,"Error: Cannot open input file !\n");
    return 0;
  }
  
  int ni=0;
  fscanf(fin,"%d",&ni);
  if (ni<=0) {
    fprintf(stderr,"Error: ni <=0! (%d)\n",ni);
    return 0;
  }
  
  int* lst=new int[ni];
  //  int lst[NMAX];

  for (int i=0; i<ni; i++) {
    fscanf(fin,"%d",&lst[i]);
  }
  
  int n,nc,ncs,ncsb;

  fscanf(fin,"%d %d %d %d",&n,&nc,&ncs,&ncsb);
  
  if (n<=0) {
    fprintf(stderr,"Error: n <=0! (%d)\n",n);
    return 0;
  }
  
  float *m=new float[n];
  float *x1=new float[n];
  float *x2=new float[n];
  float *x3=new float[n];
//  float m[NMAX];
//  float x1[NMAX];
//  float x2[NMAX];
//  float x3[NMAX];

  for (int i=0;i<n;i++) {
    fscanf(fin,"%g %g %g %g",&m[i],&x1[i],&x2[i],&x3[i]);
  }

  //  for (int i=0;i<n;i++) fprintf(stderr,"%g %g %g %g\n",m[i],x1[i],x2[i],x3[i]);

  double *pot=new double[ni];

  for (int j=0;j<ni;j++) {
    double sum = 0;
#pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++) {
      const int k = lst[j];
      if(k!=i) {
        double tmp = m[i]/dis(x1[k]-x1[i],x2[k]-x2[i],x3[k]-x3[i]);
        sum +=tmp;
      }
    }
    pot[j] = sum;
  }
  
  //  double pot[NMAX];

  //  gpupot_send_float(n,m,x1,x2,x3);
  //  gpupot(ni,lst,pot);

  FILE *fout;
  if ( (fout = fopen(init.gets("dataout").c_str(),"w")) == NULL) {
    fprintf(stderr,"Error: Cannot open output file !\n");
    return 0;
  }
    
  fprintf(fout,"# %d %d %d\n",nc,ncs,ncsb);
  for (int i=0;i<ni;i++) fprintf(fout,"%d %.8e\n",lst[i],pot[i]);

  return 0;
}

