#include <cstdio>
#include <cstdlib>
#include "ksvec.h"
#include "ksbin.h"

int main(const int ac, const char **av){
	const int seed = ac>1 ? atoi(av[1]) : (unsigned long)main;
	srand48(seed);

	const double x = drand48() - 0.5;
	const double y = drand48() - 0.5;
	const double z = drand48() - 0.5;
	const KSVec r0(x, y, z);
	const KSVec u = KSVec::init_coord(x, y, z);
	const KSVec r1 = u.trasN(u);

	r0.print();
	u .print();
	r1.print();

	const double vx = drand48() - 0.5;
	const double vy = drand48() - 0.5;
	const double vz = drand48() - 0.5;
	const KSVec v0(vx, vy, vz);
	const KSVec upr = 0.5 * u.trasT(v0);
	const KSVec v1 = (2.0 / (u*u)) * u.trasN(upr);
	v0 .print();
	upr.print();
	v1 .print();

	const double bl = u.u4*upr.u1 - u.u3*upr.u2 + u.u2*upr.u3 - u.u1*upr.u4;
	printf("bilinear : %e\n", bl);

	KSBinary bin;
	bin.init(x, y, z, vx, vy, vz, 1.0);
	bin.ph_pos().print();
	bin.ph_vel().print();

	Tprimes tpr;
	tpr.d1t = 1.0; tpr.d2t = 1.0; tpr.d3t = 1.0;
	tpr.d4t = 1.0; tpr.d5t = 1.0; tpr.d6t = 1.0;
	const double dtau = tpr.solve_dtau(3.0);
	const double dt = tpr.calc_dt(dtau);
	printf("dt = %24.16e, dtau = %24.16e\n", dt, dtau);
	
	return 0;
}
