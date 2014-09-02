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

  for (int i=0;i<num;i++){
    if(!readp6pp(NMAX,data,h,par,fin,true,off1,off2,off3)) perror("Error: NMAX too small!\n");
    if(!writep6pp(h,par,data,fout,false,true)) perror("Error: data empty!\n");
  }

  fclose(fin);
  fclose(fout);
  fprintf(stdout,"Finished\n");
}
