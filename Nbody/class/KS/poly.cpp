#include <cstdio>
#include <cmath>

static inline double poly(
		const int i, 
		const int n, 
		const double x,
		const double c[])
{
	if(i >= n){
		return 0.0;
	}else{
		return c[i] + ((1.0/(i+1)) * x) * poly(i+1, n, x, c);
	}
}

template<int i, int n_minus_i>
struct Poly{
	static inline double poly(const double x, const double c[]){
		// const int n = n_minus_i + i;
		return c[i] + ((1.0/(i+1)) * x) * Poly<i+1, n_minus_i-1>::poly(x, c);
	}
};

template<int i>
struct Poly<i, 0> {
	static inline double poly(const double x, const double c[]){
		return 0;
	}
};

template<int N, int MAX_ITER>
static double solv_poly(
	// solve equation
	//   0 = \sum_{n=0}^N \frac{c_n x^n}{n!}
		const double c[N+1], 
		const double x0, 
		const double xeps)
{
	double x = x0;
	for(int i=0; i<MAX_ITER; i++){
		const double fn = Poly<0, N+1>::poly(x, c);
		const double dn = Poly<0, N  >::poly(x, c+1);
		const double dx = fn / dn;
		fprintf(stderr, "iter=%d, x=%e, f(x)=%e, dx=%e\n", i, x, fn, -dx);
		x -= dx;
		if(fabs(dx) < xeps) return x;
	}
	return __builtin_nan("0x1");
}

#if 0
extern double poly6(const double x, const double c[]){
	return Poly<0, 7>::poly(x, c);
}
#endif

int main(){
	double c[5] = {-3., -3., -2.*2., 1.*6., 1.*24.}; 
	// solve x^4 + x^3 - 2x^2 - 3x - 3 = 0
#if 0
	for(double x=0.0; x<2.0; x+=0.1){
		const double fx = Poly<0,5>::poly(x, c);
		printf("%f %f\n", x, fx);
	}
#endif
	solv_poly<4, 10> (c, 2.0, 1.0e-12);

	return 0;
}

int main0(){
	enum { NMAX = 10 };
	double c[NMAX];
	for(int n=0; n<NMAX; n++) c[n] = 1.0;
	for(int n=0; n<NMAX; n++){
		const double fn = poly(0, n, 1.0, c);
		printf("%d, %f\n", n, fn);
	}
	puts("");
	printf("%d, %f\n", 1, Poly<0, 1>::poly(1.0, c));
	printf("%d, %f\n", 2, Poly<0, 2>::poly(1.0, c));
	printf("%d, %f\n", 3, Poly<0, 3>::poly(1.0, c));
	printf("%d, %f\n", 4, Poly<0, 4>::poly(1.0, c));
	printf("%d, %f\n", 5, Poly<0, 5>::poly(1.0, c));
	printf("%d, %f\n", 6, Poly<0, 6>::poly(1.0, c));
	printf("%d, %f\n", 7, Poly<0, 7>::poly(1.0, c));
	printf("%d, %f\n", 8, Poly<0, 8>::poly(1.0, c));
	printf("%d, %f\n", 9, Poly<0, 9>::poly(1.0, c));

	return 0;
}
