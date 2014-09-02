#include <cstdio>
#include <cstdlib>
#include <ctime>

struct float2{
  float x,y;
};

static float2 float2_split(double x){
	const int shift = 20;
	float2 ret;
	x *= (1<<shift);
	double xi = (int)x;
	double xf = x - xi;
	ret.x = xi * (1./(1<<shift));
	ret.y = xf * (1./(1<<shift));
    printf("x %.15lf\nxi %.15lf\nxf %.15lf\nret.x %.8le\nret.y %.8le\n",x,xi,xf,ret.x,ret.y);
    return ret;
}
float2 float2_accum(float2 acc, float x){
	float tmp = acc.x + x;
	acc.y -= (tmp - acc.x) - x;
	acc.x = tmp;
    printf("tmp %.8le\nacc.x %.8le\nacc.y %.8lf\n",tmp,acc.x,acc.y);
	return acc;
}

float2 float2_regularize(float2 acc){
	float tmp = acc.x + acc.y;
	acc.y = acc.y -(tmp - acc.x);
	acc.x = tmp;
	return acc;
}

int main() {
  srand(time(NULL));
  double a=(double)rand()/(double)RAND_MAX*(1<<20);
  float b=(double)rand()/(double)RAND_MAX*(1<<20);
  printf("a %.15lf b %.8lf\n",a,b);
  float2 c=float2_split(a);
  float2_accum(c,b);
  return 0;
}
