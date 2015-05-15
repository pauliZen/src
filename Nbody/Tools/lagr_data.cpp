//plot Largrangian radii for 'fit' snapshot, require name i1/i2 at last columns
// reading:
//   number of snapshots
//   snapshot list (two columns, first is time, second is number of data in snapshot)
//   prefix of snapshot name: (prefix)(time)
//   output file name
//   fshell
//   fbres

#include <cstdio>
#include <fstream>
#include <initial.h>
#include <string>
#include <uftools.h>
#include <lagr.h>

const int NFRAC=8;
const float rfrac[NFRAC]={0.001,0.01,0.1,0.3,0.5,0.7,0.9,1.0};

int main (int argc, char **argv){
  pars_initial init(".lagr_data_config");
  init.add("num","number of snapshot",(int)1);
  init.add("list","snapshot list (one column show time of snapshot)","snap.lst");
  init.add("prefix","prefix of snapshot filename: [prefix][time]","data_");
  init.add("NSmax","Maximum number of single stars",(int)1500000);
  init.add("NBmax","Maximum number of binary stars",(int)100000);
  init.add("out","output file name","lagr.snap");
  init.add("fshell","1: do all calculation between R_Lagr shells; 0: do calculation from center to R_lagr ",(int)1);
  init.add("fbres","whether resolve binaries for average mass calculation (1: Yes; 0: No)",(int)0);
  init.initial(argc,argv,false);

  // FILE *flst;
  // if ( (flst = fopen(init.gets("list").c_str(),"r")) == NULL) {
  //   fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("list").c_str());
  //   return 0;
  // }
  std::ifstream flst(init.gets("list").c_str());
  if (!flst.is_open())  {
    fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("list").c_str());
    return 0;
  }

  int nlst=init.geti("num");
  if (nlst<=0) {
    fprintf(stderr,"Error: number of snapshots %d <=0.\n",nlst);
    return 0;
  }
  //  float *tlst=new float[nlst];
  //  int *ndata=new int[nlst];
  std::string prefix=init.gets("prefix");
  int NSMAX=init.geti("NSmax");
  int NBMAX=init.geti("NBmax");
  bool fshell=static_cast<bool>(init.geti("fshell"));
  bool fbres=static_cast<bool>(init.geti("fbres"));

  float* mass=new float[NSMAX];
  float* x1  =new float[NSMAX];
  float* x2  =new float[NSMAX];
  float* x3  =new float[NSMAX];
  float* v1  =new float[NSMAX];
  float* v2  =new float[NSMAX];
  float* v3  =new float[NSMAX];
  float* bm1 =new float[NBMAX];
  float* bm2 =new float[NBMAX];
  float* bxc1=new float[NBMAX];
  float* bxc2=new float[NBMAX];
  float* bxc3=new float[NBMAX];
  float* bvc1=new float[NBMAX];
  float* bvc2=new float[NBMAX];
  float* bvc3=new float[NBMAX];
  int*   bn1 =new int[NBMAX];
  int*   bn2 =new int[NBMAX];
  
  for (int i=0;i<nlst;i++) {
    std::string tstr;
    flst>>tstr;
    
    FILE *fdata;
    if ( (fdata = fopen((prefix+tstr).c_str(),"r")) == NULL) {
      fprintf(stderr,"Error: Cannot open input file %s.\n",init.gets("list").c_str());
      return 0;
    }

    float time=to<float>(tstr);
    int N_SINGLE=0,N_BINARY=0,N_MERGER=0;

    if (time==0.0) {
      printf("## Time; 100 groups of data; offset %d\n", NFRAC);
      printf("Time[NB] ");
      for (int k=0; k<55; k++) {
        for (int j=0;j<NFRAC;j++) {
          printf("%.2e ", rfrac[j]);
        }
      }
      printf("\n");
    }
    
    while(true) {
      double v1[3],v2[3],r1[3],r2[3],m1,m2,l1,l2,rs1,rs2,a,e,xc[3],vc[3];
      int k1,k2,n1,n2;
      fscanf(fdata,"%lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %d %d %lg %lg %lg %lg %lg %lg %lg %lg %d %d",&r1[0],&r1[1],&r1[2],&v1[0],&v1[1],&v1[2],&r2[0],&r2[1],&r2[2],&v2[0],&v2[1],&v2[2],&m1,&m2,&l1,&l2,&rs1,&rs2,&k1,&k2,&a,&e,&xc[0],&xc[1],&xc[2],&vc[0],&vc[1],&vc[2],&n1,&n2);
      if (feof(fdata)) break;
      if (m2>0.0) {
        bm1[N_BINARY] = m1;
        bm2[N_BINARY] = m2;
        bxc1[N_BINARY]= xc[0];
        bxc2[N_BINARY]= xc[1];
        bxc3[N_BINARY]= xc[2];
        bvc1[N_BINARY]= vc[0];
        bvc2[N_BINARY]= vc[1];
        bvc3[N_BINARY]= vc[2];
        bn1[N_BINARY] = n1;
        bn2[N_BINARY] = n2;
        N_BINARY++;
      } else {
        mass[N_SINGLE] = m1;
        x1[N_SINGLE]= xc[0];
        x2[N_SINGLE]= xc[1];
        x3[N_SINGLE]= xc[2];
        v1[N_SINGLE]= vc[0];
        v2[N_SINGLE]= vc[1];
        v3[N_SINGLE]= vc[2];
        N_SINGLE++;
      }
    }

    //    printf("%d %d\n",N_SINGLE,N_BINARY);
    lagr(time,N_SINGLE,N_BINARY,N_MERGER,fshell,fbres,mass,x1,x2,x3,v1,v2,v3,bm1,bm2,bxc1,bxc2,bxc3,bvc1,bvc2,bvc3,bn1,bn2);

    fclose(fdata);

  }

  flst.close();

  delete mass; 
  delete x1  ; 
  delete x2  ; 
  delete x3  ; 
  delete v1  ; 
  delete v2  ; 
  delete v3  ; 
  delete bm1 ; 
  delete bm2 ; 
  delete bxc1; 
  delete bxc2; 
  delete bxc3; 
  delete bvc1; 
  delete bvc2; 
  delete bvc3; 
  delete bn1 ; 
  delete bn2 ; 

  return 0;
}

