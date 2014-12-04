#include "ptime.h"
#include <initial.h>
#include "smmintrin.h"
#include "emmintrin.h"

//typedef double v4df __attribute__ ((vector_size(32)));
typedef __m128i v4si;

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
  int a[4]={1,1,1,1};
  v4si b,c;
  _mm_stream_si128(&b,*((v4si*)a));
  _mm_stream_si128(&c,*((v4si*)a));

  tavx.set();
  for (int i=0;i<n;i++) b = _mm_add_epi32(b, c);
  tavx.add();

  int *d=(int*)&b;
  printf("AVX: %d %d %d %d\n", d[0],d[1],d[2],d[3]);
  
  tnow.set();
  for (int i=0;i<n;i++)
    {
      a[0] +=1;
      a[1] +=1;
      a[2] +=1;
      a[3] +=1;
    }
  tnow.add();
  printf("Normal: %d %d %d %d\n",a[0],a[1],a[2],a[3]);

  tlist.print();
  return 0;
}
