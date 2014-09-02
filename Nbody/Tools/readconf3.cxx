#include <stdio.h>
#include <initial.h>
#include <nb6out3.h>
#include <vector>
#include <fstream>

int main(int argc, char *argv[]){
  pars_initial init(".readout3_config");
  init.add("dataname","data name to read","conf.3");
  init.add("outfile","output file","output");
  init.add("off1","offset for first line",(int)1);
  init.add("off2","offset for second line",(int)1);
  init.add("off3","offset for end line",(int)1);
  init.add("num","snapshot number",(int)100);
  init.add("nmax","maximum particle number",(int)1000000);
  //  init.add("nslst","ns name list","ns.lst");
  init.initial(argc,argv);

  int num=init.geti("num");
  const int NMAX=init.geti("nmax");

  particle6pp *data=new particle6pp[NMAX];
  header *h=new header;
  pars6pp *par=new pars6pp;
  
  FILE *fin;
  if ( (fin = fopen(init.gets("dataname").c_str(),"r")) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("dataname").c_str());
    return 0;
  }

  FILE *fout;
  if ( (fout = fopen(init.gets("outfile").c_str(),"w")) == NULL) {
    fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("outfile").c_str());
    return 0;
  }

  int off1=init.geti("off1");
  int off2=init.geti("off2");
  int off3=init.geti("off3");

  // float *m=new float[NMAX];
  // float3 *x=new float3[NMAX];
  // float3 *v=new float3[NMAX];
  // float *rh=new float[NMAX];
  // float *phi=new float[NMAX];
  // float *xns=new float[NMAX];
  // int *n=new int[NMAX];
  
  // for (int i=0;i<num;i++){
  //   if(!readp6pp(NMAX,m,x,v,rh,xns,phi,n,h,par,fin,off1,off2,off3)) perror("Error: NMAX too small!\n");
  //   h->print_all(fout);
  //   par->print_all(fout);
  //   fprintf(fout,"mass x[0] x[1] x[2] v[0] v[1] v[2] rh xns phi name\n");
  //   for(int i=0;i<h->ntot;i++) fprintf(fout,"%g %g %g %g %g %g %g %g %g %g %d\n",m[i],x[i][0],x[i][1],x[i][2],v[i][0],v[i][1],v[i][2],rh[i],xns[i],phi[i],n[i]);
  // }

  for (int i=0;i<num;i++) {
    if(!readp6pp(NMAX,data,h,par,fin,true,off1,off2,off3)) perror("Error: NMAX too small!\n");
    if(!writep6pp(data,h,par,fout,false,true)) perror("Error: data empty!\n");
  }
  
  fclose(fin);
  fclose(fout);
  fprintf(stdout,"Finished\n");
}
