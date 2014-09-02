#include "ptime.h"
#include <initial.h>

typedef double v4df __attribute__ ((vector_size(32)));

int main(int argc, char *argv[])
{
  ptime tnow("Normal");
  ptime tavx("AVX");

  time_list tlist;
  tlist.add(&tavx);
  tlist.add(&tnow);

  pars_initial init(".test");
  init.add("N","N to add",(int)10000000);
  init.initial(argc,argv);

  int n=init.geti("N");
  double a[4]={1.0,1.0,1.0,1.0};
  v4df b={1.0,1.0,1.0,1.0};
  v4df c={1.0001,1.0001,1.0001,1.0001};

  tavx.set();
  for (int i=0;i<n;i++) b = b + c;
  tavx.add();

  double *d=(double*)&b;
  printf("AVX: %g %g %g %g\n", d[0],d[1],d[2],d[3]);
  
  tnow.set();
  for (int i=0;i<n;i++)
    {
      a[0] +=1.0001;
      a[1] +=1.0001;
      a[2] +=1.0001;
      a[3] +=1.0001;
    }
  tnow.add();
  printf("Normal: %g %g %g %g\n",a[0],a[1],a[2],a[3]);

  tlist.print();
  return 0;
}
