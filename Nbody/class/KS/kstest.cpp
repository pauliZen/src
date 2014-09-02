#include <cstdio>
#include <cstdlib>
#include "ksvec.h"
#include "ksbin.h"

#define BLOCK_STEP

static double time_pericenter(
		const double t,
		const double e,
		const KSVec &upos)
{
	// assume a=1, M=1, w0=pi
	const double pi = 4. * atan(1.0);
	const KSVec ppos = upos.trasN(upos);
	const double x = ppos.u1;
	const double y = ppos.u2;
	const double r = sqrt(x*x + y*y);
	const double w = pi; // arg of pericenter
	const double f = atan2(y, x) - w;
	const double cosu = e + r*cos(f);
	const double sinu = r*sin(f) / sqrt(1.0 - e*e);
	const double u = atan2(sinu, cosu);

	double t0 = fmod(t, 2.*pi) - (u - e*sinu);
	t0 -= pi;
	t0 = fmod(t0+pi, 2.*pi) - pi;
	return t0;
}

static void kstest(
		const double mtot,
		const double e,
		const double tcrit)
{
	const double x  = 1.0 + e;
	const double y  = 0.0;
	const double z  = 0.0;
	const double vx = 0.0;
	const double vy = sqrt((1.0 - e) / (1.0 + e));
	const double vz = 0.0;

	KSBinary bin;
	bin.init(x, y, z, vx, vy, vz, mtot);
	const double h0 = bin.energy();
	const double dtau0 = 0.1 * sqrt(1.0 / fabs(2.0*h0));
	fprintf(stderr, "e = %e, h = %e\n", e, h0);
	bin.initderiv1_unperturbed();
	bin.initderiv2();

	const int NITER = 4;
#ifndef BLOCK_STEP
	for(int istep=0; istep<100000; istep++){
		const double derel = (bin.energy() - h0) / h0;
		if(fabs(derel) > 1.e-4) break;
		bin.nextstep_noblock(dtau0);
		const double tperi = time_pericenter(bin.time, e, bin.upos);
		// fprintf(stdout, "%4d %e %e %e\n", istep, bin.time, derel, bin.tnext-bin.time);
		fprintf(stdout, "%4d %e %e %e\n", istep, bin.time, derel, tperi);
		if(bin.time >tcrit) break;

		KSPred pred;
		pred.predict(bin, dtau0);
		for(int iter=0; iter<NITER; iter++){
			KSForce force;
			force.force_unperturbed(pred);
			KSBinary bnew = KSCorr(dtau0, bin, force);
			if(iter < NITER-1){
				pred.upos = bnew.upos;
				pred.uvel = bnew.uvel;
				pred.h    = bnew.h   ;
			}else{
				bnew.time = bin.correct_time(dtau0, bnew);
				bin = bnew;
			}
		}
	}
#else // BLOCK_STEP
	double tsys = 0.0;
	for(int istep=0; istep<100000; istep++){
		const double derel = (bin.energy() - h0) / h0;
		const double descale = bin.ph_r() * derel;
		if(fabs(derel) > 1.e-4) break;
		double dt, dtau;
		bin.nextstep_block(2.0*dtau0, tsys, 1.0, dt, dtau);
		if(dtau != dtau) break;
		// const double terr = tsys - bin.time;
		const double tperi = time_pericenter(bin.time, e, bin.upos);
		fprintf(stdout, "%4d %e %e, %e %e %e %e\n", istep, tsys, derel, descale, dt, dtau, tperi);
		if(tsys >tcrit) break;

		KSPred pred;
		// bin.initderiv2();
		pred.predict(bin, dtau);
		for(int iter=0; iter<NITER; iter++){
			KSForce force;
			force.force_unperturbed(pred);
			KSBinary bnew = KSCorr(dtau, bin, force);
			if(iter < NITER-1){
				pred.upos = bnew.upos;
				pred.uvel = bnew.uvel;
				pred.h    = bnew.h   ;
				continue;
			}else{
				bnew.time = bin.correct_time(dtau, bnew);
				bin = bnew;
				tsys += dt;
				break;
			}
		}
	}
#endif
}

int main(const int ac, const char **av){
	// const int seed = ac>1 ? atoi(av[1]) : (unsigned long)main;
	// srand48(seed);

	kstest(1.0, 0.9999, 628.3);

	return 0;
}
