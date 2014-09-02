#include <stdio.h>
#include <initial.h>
#include <fstream>
#include <string>

struct dat{
  float mass,x[3],v[3];
  int name;
};

int main(int argc, char *argv[]){
  pars_initial init(".readout3_config");
  init.add("data","data name to read","OUT3");
  init.add("out","data name to write","OUT3");
  init.initial(argc,argv);

  int *h=new int[4];
  float *a=new float[20];
  
  FILE *stream;
  if ( (stream = fopen(init.gets("data").c_str(),"r")) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("data").c_str());
    return 0;
  }

  fread(h,sizeof(int),4,stream);
  fread(a,sizeof(float),20,stream);
  dat *dtmp=new dat[h[0]];
  fread(dtmp,sizeof(dat),h[0],stream);

  FILE *out;
  if ( (out = fopen(init.gets("out").c_str(),"w")) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("out").c_str());
    return 0;
  }
  
  fprintf(out,"%d %d %d %d\n",h[0],h[1],h[2],h[3]);
  fprintf(out,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19]);
  for (int ii=0;ii<h[0];ii++){
    fprintf(out,"%f %f %f %f %f %f %f %d\n", dtmp[ii].mass,dtmp[ii].x[0],dtmp[ii].x[1],dtmp[ii].x[2],dtmp[ii].v[0],dtmp[ii].v[1],dtmp[ii].v[2],dtmp[ii].name);
  }
  
  fclose(stream);

  return 0;
}
