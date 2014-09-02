#include <initial.h>
#include <particle.h>
#include <intgrt.h>
#include <cstdio>
#include <cassert>

void debug_check(const particle *p, const chain *c, const int level=1){
#ifdef DEBUG
  int num=c->num;
  if(level>=0) {
    printf("#==============================Particle================================#\n");
    printf(" ID    mass     x[0]       x[1]       x[2]       v[0]       v[1]       v[2]\n");
    for (int i=0;i<num;i++) {
      printf("%3d %6.5lg %10.6lg %10.6lg %10.6lg %10.6lg %10.6lg %10.6lg\n",i,p[i].mass,p[i].x[0],p[i].x[1],p[i].x[2],p[i].v[0],p[i].v[1],p[i].v[2]);
    }
  }    
  if(level>=1) {
    printf("#===============================Chain==================================#\n");
    printf("num    t      w      B     Ekin    Pot      W     DE    DE/ETOT\n");
    double de=c->B+c->Ekin-c->Pot;
    printf("%3d %6.4lg %6.4lg %6.4lg %6.4lf %6.4lf %6.4lf %6.4lf %6.4lf\n",c->num,c->t,c->w,c->B,c->Ekin,c->Pot,c->W,de,de/c->B);
    printf("List: ");
    for (int i=0;i<num;i++) printf("%d ",c->list[i]);
    printf("\n");
    printf(" ID             X[0]       X[1]       X[2]       V[0]       V[1]       V[2]\n");
    for (int i=0;i<num-1;i++) {
      printf("%3d       %10.6lg %10.6lg %10.6lg %10.6lg %10.6lg %10.6lg\n",i,c->m[i].X[0],c->m[i].X[1],c->m[i].X[2],c->m[i].V[0],c->m[i].V[1],c->m[i].V[2]);
    }
  }
  if(level>=2) {
    printf("Wij: \n");
    for (int i=0;i<num;i++) {
      for (int j=0;j<num;j++) printf("%10.5lf",c->Wij[i][j]);
      printf("\n");
    }
    printf("rjk: \n");
    for (int i=0;i<num;i++) {
      for (int j=0;j<num;j++) printf("%10.5lf",c->rjk[i][j][3]);
      printf("\n");
    }
    printf("acc: \n");
    for (int i=0;i<num;i++) {
      printf("%10.6lg %10.6lg %10.6lg\n",c->acc[i][0],c->acc[i][1],c->acc[i][2]);
    }
  }
#endif    
}

void output(FILE *fout,const double &t, const int &num, const particle *p) {
  fprintf(fout,"%lg %d\n",t,num);
  for (int i=0;i<num;i++) {
    fprintf(fout,"%d %lg %lg %lg %lg %lg %lg %lg\n",i,p[i].mass,p[i].x[0],p[i].x[1],p[i].x[2],p[i].v[0],p[i].v[1],p[i].v[2]);
  }
}  

int main(int argc, char **argv) {
  pars_initial init(".test_config");
  init.add("step","step size",(double)0.01);
  init.add("loop","loop times",(int)10);
  init.add("alpha","integration parameter alpha",(double)0);
  init.add("beta","integration parameter beta",(double)1);
  init.add("gamma","integration parameter alpha",(double)0);
  init.add("filename","output data filename","data");
  init.initial(argc,argv);

  double s=init.getd("step");
  int loop=init.geti("loop");
  double intpar[3];
  intpar[0]=init.getd("alpha");
  intpar[1]=init.getd("beta");
  intpar[2]=init.getd("gamma");

  FILE *fin;
  if ( (fin=fopen("test.dat","r"))==NULL) {
    perror("Error! cannot open test.dat\n");
    return 0;
  }

  FILE *fout;
  if ( (fout=fopen(init.gets("filename").c_str(),"w"))==NULL) {
    perror("Error! cannot open output filename\n");
    return 0;
  }

  int num;
  fscanf(fin,"%d",&num);
  assert(num>0);

  particle *p=new particle[num];
  double m,x,y,z,vx,vy,vz,fx,fy,fz;
  double3 *f=new double3[num];
  for (int i=0;i<num;i++) {
    fscanf(fin,"%lg %lg %lg %lg %lg %lg %lg %lg %lg %lg",&m,&x,&y,&z,&vx,&vy,&vz,&fx,&fy,&fz);
    p[i].load(m,x,y,z,vx,vy,vz);
    f[i][0]=fx;
    f[i][1]=fy;
    f[i][2]=fz;
  }

  chain *c=new chain(num);
  printf("#-------------------------Original------------------------------#\n");  
  debug_check(p,c,0);
  
  printf("#-------------------------Initial-------------------------------#\n");  
  chain_init(0,f,p,c);
  debug_check(p,c,2);

  printf("#--------------------------Intgrt-------------------------------#\n");
  chain_intgrt_X(intpar,0.5*s,p,c);
  debug_check(p,c,1);
  output(fout,c->t,c->num,p);
  
  for (int i=0;i<loop;i++) {
    check_chain(p,c);
    get_chain_pars(p,f,c);
    chain_intgrt_V(intpar,s,f,p,c);
    if(i==loop-1) chain_intgrt_X(intpar,0.5*s,p,c);
    else chain_intgrt_X(intpar,s,p,c);
    debug_check(p,c,1);
    output(fout,c->t,c->num,p);
  }
  
  return 0;
}
