#include <stdio.h>
#include <initial.h>
#include <fstream>
#include <string>

struct dat{
  float mass,x[3],v[3];
  int name;
};

int main(int argc, char *argv[]){
  pars_initial init(".transout3_config");
  init.add("data","data name to read","OUT3");
  init.add("begin","begin of time",(float)0.0);
  init.add("step","time interval (astro Unit)",(float)1.0);
  init.add("end","end of time",(float)1000.0);
  init.add("prefix","output file prefix","out3_");
  init.add("unformat","whether output is unformated",(bool)true);
  init.initial(argc,argv);

  float tbegin=init.get<float>("begin");
  float tend=init.get<float>("end");
  float step=init.get<float>("step");
  float tcount=tbegin;
  int *h=new int[4];
  float *a=new float[20];
  float pretime=-1;
  bool binary=init.get<bool>("unformat");
  
  FILE *stream;
  if ( (stream = fopen(init.gets("data").c_str(),"r")) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("data").c_str());
    return 0;
  }
  float *tmp=new float[4];
  int dsize=sizeof(float)*7+sizeof(int);
  while (!feof(stream)) {
    fread(tmp,sizeof(int),1,stream);
    fread(h,sizeof(int),4,stream);
    fread(tmp,sizeof(int),2,stream);
    fread(a,sizeof(float),20,stream);
    //    fprintf(stdout,"--a %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19]);
    float tastro=a[0]*a[10];
    if (tastro>=tcount){
      float *m=new float[h[0]];
      float *p=new float[3*h[0]];
      float *v=new float[3*h[0]];
    //    float *rh=new float[h[0]];
    //    float *xn=new float[h[0]];
    //    float *phi=new float[h[0]];
      int *n=new int[h[0]];
      fread(m,sizeof(float),h[0],stream);
    //    fprintf(stdout,"-m %f %f %f\n",m[0],m[1],m[2]);
    //    fread(rh,sizeof(float),h[0],stream);
    //    fprintf(stdout,"-rh %f %f %f\n",rh[0],rh[1],rh[2]);
    //    fread(xn,sizeof(float),h[0],stream);
    //    fprintf(stdout,"-xn %f %f %f\n",xn[0],xn[1],xn[2]);
      fread(p,sizeof(float),3*h[0],stream);
    //    fprintf(stdout,"-p %f %f %f\n",p[0],p[1],p[2]);
      fread(v,sizeof(float),3*h[0],stream);
    //    fread(phi,sizeof(float),h[0],stream);
      fread(n,sizeof(int),h[0],stream);
      fread(tmp,sizeof(int),1,stream);
    //    fprintf(stdout,"-tmp %f\n",tmp[0]);
    //    size_t j=0;
    //    fprintf(stdout,"--n %d %d %d\n",n[0],n[1],n[2]);
      fprintf(stdout,"OUT TIME %f  NTOT %d  MODEL %d  NRUN %d NK %d\n",tastro,h[0],h[1],h[2],h[3]);
      FILE *out;
      std::string fname=init.gets("prefix")+to<std::string>(tastro);
      if ( (out = fopen(fname.c_str(),"w")) ==NULL ) {
        fprintf(stderr,"Error: Cannot create file %s.\n",fname.c_str());
        return 0;
      }
      if (binary) {
        fwrite(h,sizeof(int),4,out);
        fwrite(a,sizeof(float),20,out);
        dat *dtmp=new dat[h[0]];
        for (int ii=0;ii<h[0];ii++) {
          dtmp[ii].mass=m[ii]*a[3];
          dtmp[ii].x[0]=p[3*ii]*a[2];
          dtmp[ii].x[1]=p[3*ii+1]*a[2];
          dtmp[ii].x[2]=p[3*ii+2]*a[2];
          dtmp[ii].v[0]=v[3*ii]*a[11];
          dtmp[ii].v[1]=v[3*ii+1]*a[11];
          dtmp[ii].v[2]=v[3*ii+2]*a[11];
          dtmp[ii].name=n[ii];
        }
        fwrite(dtmp,sizeof(dat),h[0],out);
      }
      else {
        fprintf(out,"%d %d %d %d\n",h[0],h[1],h[2],h[3]);
        fprintf(out,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19]);
        for (int ii=0;ii<h[0];ii++){
          fprintf(out,"%f %f %f %f %f %f %f %d\n",m[ii]*a[3],p[3*ii]*a[2],p[3*ii+1]*a[2],p[3*ii+2]*a[2],v[3*ii]*a[11],v[3*ii+1]*a[11],v[3*ii+2]*a[11],n[ii]);
        }
      }
      fclose(out);
      tcount +=step;
      if (tcount>tend) break;
    }
    else {
      fprintf(stdout,"PASS TIME %f  NTOT %d  MODEL %d  NRUN %d NK %d\n",tastro,h[0],h[1],h[2],h[3]);
      fseek(stream,dsize*h[0]+sizeof(int),SEEK_CUR);
      if (pretime==a[0]) {
        fprintf(stdout,"End of File\n");
        return 0;
      }
      pretime=a[0];
    }
  }
  fclose(stream);
  fprintf(stdout,"Finished\n");
}
