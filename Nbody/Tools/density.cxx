//Check data (m,x,y,z,vx,vy,vz) density profile or randomize the order of data
#include <stdio.h>
#include <cstdlib>
#include <cassert>
#include <string>
#include <algorithm>
#include <cmath>
#include <initial.h>
#include <omp.h>
#include <time.h>
// #include <TGraph.h>
// #include <TCanvas.h>
#ifndef NAN_CHECK
#define NAN_CHECK(val) assert((val) == (val));
#endif

struct mr{
  double m;
  double r;
};

struct id{
  int id;
  int irand;
};

struct particle{
  double mass, r[3], v[3];

  //instruction=======================================//
  particle() {} 
  particle(double m, double x[3], double v[3]) {
    load(m,x[0],x[1],x[2],v[0],v[1],v[2]);
  }
  particle(double m, double x, double y, double z, double vx, double vy, double vz) {
    load(m,x,y,z,vx,vy,vz);
  }

  //load data=========================================//
  void load(double m, double x, double y, double z, double vx, double vy, double vz){
    NAN_CHECK(m);
    NAN_CHECK(x);
    NAN_CHECK(y);
    NAN_CHECK(z);
    NAN_CHECK(vx);
    NAN_CHECK(vy);
    NAN_CHECK(vz);

    mass=m;
    r[0]=x;r[1]=y;r[2]=z;
    v[0]=vx;v[1]=vy;v[2]=vz;
  }
};

void particle_scanf(const char* name, particle *list, int count)
{
  if ( freopen(name, "r",stdin) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s.\n",name);
    return;
  }
  for (int i=0;i<count;i++)
  {
    int sct;
    sct=scanf("%lg %lg %lg %lg %lg %lg %lg",&list[i].mass,&list[i].r[0],&list[i].r[1],
              &list[i].r[2],&list[i].v[0],&list[i].v[1],&list[i].v[2]);
    if (sct<7) fprintf(stderr, "Error: Line %d Reading Fail (intput %d < 7).\n",i,sct);
  }
  fclose(stdin);
}

bool is_shorter (const mr& i,const mr& j) { return (i.r<j.r); }
bool id_shorter (const id& i, const id& j) { return (i.irand<j.irand); }

int main(int argc, char **argv) {
  pars_initial init(".density_config");
  init.add("input","data","fort.10");
  init.add("N","number",1000000);
  init.add("Opt","1. output density profile; 2. output new data with random order",1);
  init.add("output","file","data");
  init.initial(argc,argv);

  int nt=init.geti("N");
  int opt=init.geti("Opt");
  particle *N=new particle[nt];
  particle_scanf(init.gets("input").c_str(),N,nt);
  
  FILE *out;
  if ( (out = fopen(init.gets("output").c_str(),"w")) == NULL) {
    fprintf(stderr,"Output cannot open\n");
    return 0;
  }

  if(opt==1) {
    mr *dr=new mr[nt];
    double avr=0.;
    for (int i=0;i<nt;i++) {
      dr[i].r=sqrt(N[i].r[0]*N[i].r[0]+N[i].r[1]*N[i].r[1]+N[i].r[2]*N[i].r[2]);
      avr +=dr[i].r;
      dr[i].m=N[i].mass;
    }
    avr /=nt;

    std::sort(dr,dr+nt,is_shorter);

    //   double *x=new double[nt];
    //   double *cm=new double[nt];
  
    for (int i=1;i<nt;i++) {
      dr[i].m +=dr[i-1].m;
      //     cm[i] = dr[i].m;
      //     x[i] = dr[i].r;
    }
    printf("Average R: %g\n",avr);

    fprintf(out,"R, M\n");
    for (int i=0; i<nt;i++) {
      fprintf(out,"%g %g\n",dr[i].r,dr[i].m);
    }
  }
  else {
    srand(time(NULL));
    id *in = new id[nt];
    for (int i=0; i<nt; i++) {
      in[i].irand = rand();
      in[i].id = i;
    }
    std::sort(in,in+nt,id_shorter);
    for (int i=0;i<nt;i++) {
      int k = in[i].id;
      fprintf(out,"%.16E %.16E %.16E %.16E %.16E %.16E %.16E\n", N[k].mass,N[k].r[0],N[k].r[1],N[k].r[2],N[k].v[0],N[k].v[1],N[k].v[2]);
    }
    
  }
    
//   TCanvas c1;
//   TGraph *h1=new TGraph(nt,x,cm);
//   h1->SetTitle("mass profile;r;cum. mass");
//   h1->Draw("AL");
//   c1.SetLogx(1);
//   c1.SetLogy(1);
//   c1.Print((init.gets("output")+".pdf").c_str());
  fclose(out);
  return 0;
}
