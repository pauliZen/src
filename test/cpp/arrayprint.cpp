#include <cstdio>

extern "C" void test (float a, double b, int c, int n, float* ar, double *br, int* cr)
{
  printf("%f %lf %d\n",a,b,c);
  for (int i=0;i<n;i++) printf("%f %lf %d\n",ar[i],br[i],cr[i]);
}

