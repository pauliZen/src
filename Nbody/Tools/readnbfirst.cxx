#include <nb6out3.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *f;
  if( (f = fopen("conf.3","r")) == NULL ) {
    fprintf(stderr,"Error: Cannot open input file conf.3.\n");
    return 0;
  }

  int NMAX=300000;

  particle6pp *data=new particle6pp[NMAX];
  header *h=new header;
  pars6pp *p =new pars6pp;
  
  readp6pp(NMAX,data,h,p,f,true,2);

  printf("RC %lf VC %lf",p->rc,p->vc);

  return 0;
}

    
