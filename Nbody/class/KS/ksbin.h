#pragma once

#include <cassert>
#include "ksvec.h"

struct Tprimes{
	double d1t, d2t, d3t, d4t, d5t, d6t;
	Tprimes(
			const KSVec &d0u,
			const KSVec &d1u,
			const KSVec &d2u, // acc
			const KSVec &d3u, // jrk
			const KSVec &d4u, // snp
			const KSVec &d5u) // crk
	{
		d1t = d0u*d0u;
		d2t = 2.0 * (d0u*d1u);
		d3t = 2.0 * (d0u*d2u + d1u*d1u);
		d4t = 2.0 * (d0u*d3u) + 6.0 * (d1u*d2u);
		d5t = 2.0 * (d0u*d4u) + 8.0 * (d1u*d3u) + 6.0 * (d2u*d2u);
		d6t = 2.0 * (d0u*d5u) + 10. * (d1u*d4u) + 20. * (d2u*d3u);
	}
	Tprimes(){}

	double calc_dt(const double dtau) const {
		const double h  = dtau;
		const double h2 = (1./2.) * dtau;
		const double h3 = (1./3.) * dtau;
		const double h4 = (1./4.) * dtau;
		const double h5 = (1./5.) * dtau;
		const double h6 = (1./6.) * dtau;

		// fprintf(stderr, "[%e, %e, %e, %e, %e, %e]\n", d1t, d2t, d3t, d4t, d5t, d6t);
		return h*(d1t + h2*(d2t + h3*(d3t + h4*(d4t + h5*(d5t + h6*d6t)))));
	}

	double poly(const double dt, const double x) const{
			const double x2 = (1./2.) * x;
			const double x3 = (1./3.) * x;
			const double x4 = (1./4.) * x;
			const double x5 = (1./5.) * x;
			const double x6 = (1./6.) * x;
			const double fn = -dt + x*(d1t + x2*(d2t + x3*(d3t + x4*(d4t + x5*(d5t + x6*d6t)))));
			return fn;
	}

	void polydump(const double dt, const char *file, const double xmax) const {
		FILE *fp = fopen(file, "w");
		for(int i=0; i<100; i++){
			double x = i * xmax / 100;
			double y = poly(dt, x);
			fprintf(fp, "%e %e\n", x, y);
		}
		fclose(fp);
		exit(0);
	}

	double guess_dtau(const double dt) const {
		const double ri = 1.0 / d1t;
		const double ri2 = ri * ri;
		const double ri3 = ri * ri2;
		const double ri5 = ri2 * ri3;
		const double dot1 = ri;
		const double dot2 = -d2t * ri3;
		const double dot3 = (3.0*d2t*d2t - d1t*d3t) * ri5;

		const double dt2 = (1./2.) * dt;
		const double dt3 = (1./3.) * dt;

		const double x =  dt*(dot1 + dt2*(dot2 + dt3*dot3));
		return x;
	}

	double guess_dtau2(const double dt, const double dtau0) const {
		const double dx = 0.25*dtau0;
		const double y0 = -dt;
		const double y1 = poly(dt, 0.25*dtau0);
		if(y1 > 0.0){
			return -y0*dx/(y1-y0);
		}
		const double y2 = poly(dt, 0.50*dtau0);
		if(y2 > 0.0){
			return 0.25*dtau0 - y1*dx/(y2-y1);
		}
		const double y3 = poly(dt, 0.75*dtau0);
		if(y3 > 0.0){
			return 0.50*dtau0 - y2*dx/(y3-y2);
		}
		const double y4 = poly(dt, dtau0);
		assert(y4 > 0.0);
		{
			return 0.75*dtau0 - y3*dx/(y4-y3);
		}
	}

	double solve_dtau(
			const double dt,
			const double dtau0,
			const double eps = 1.e-10,
			const int MAX_ITER = 10) const
	{
		// double x = guess_dtau(dt);
		double x = guess_dtau2(dt, dtau0);
		// double x = dt / d1t;
		// double x = dt * dtau0 / poly(0.0, dtau0);
		const double xtol = dtau0 * eps; // relative crit
		for(int i=0; i<MAX_ITER; i++){
			if(x > dtau0) x = dtau0;
			const double x2 = (1./2.) * x;
			const double x3 = (1./3.) * x;
			const double x4 = (1./4.) * x;
			const double x5 = (1./5.) * x;
			const double x6 = (1./6.) * x;
			const double fn = -dt + x*(d1t + x2*(d2t + x3*(d3t + x4*(d4t + x5*(d5t + x6*d6t)))));
			const double dn = d1t + x*(d2t + x2*(d3t + x3*(d4t + x4*(d5t + x5*(d6t)))));
			const double dx = fn / dn;

			if(i >=5) {
				fprintf(stderr, "iter=%d, x=%e, f(x)=%e, dx=%e, r=%e\n", 
						i, x/dtau0, fn, -dx, d1t);
				// polydump(dt, "poly.dat", dtau0);
			}
			x -= dx;
			if(fabs(dx) < xtol){
				printf("!NR %e %d\n", d1t, i+1);
				return x;
			}
		}
		return __builtin_nan("0x1");
	}
};

struct KSBinary{
	KSVec upos, uvel;
	KSVec uacc, ujrk; 
	KSVec usnp, ucrk; // for prediction
	double h, d1h, d2h, d3h, d4h;
	double mass, time, tnext;

	double energy() const {
		return (2.0*(uvel*uvel) - mass) / (upos*upos);
	}

	void init(
			const double x, 
			const double y, 
			const double z,
			const double vx, 
			const double vy, 
			const double vz,
			const double mtot)
	{
		upos = KSVec::init_coord(x, y, z);
		uvel = 0.5 * upos.trasT(KSVec(vx, vy, vz));

		mass = mtot;
		h    = energy();
		time = 0.0;
	}

	void initderiv1_unperturbed(){
		uacc = (0.5 * h) * upos;
		ujrk = (0.5 * h) * uvel;
	}

	void initderiv2(){
		usnp = (0.5 * h) * uacc;
		ucrk = (0.5 * h) * ujrk;
	}

	void write_back(
			double &x,  double &y,  double &z,
			double &vx, double &vy, double &vz,
			double &tout) const
	{
		ph_pos().write_back(x, y, z);
		ph_vel().write_back(vx, vy, vz);
		tout = time;
	}

	double ph_r() const {
		return (upos * upos);
	}
	KSVec ph_pos() const {
		return upos.trasN(upos);
	}
	KSVec ph_vel() const {
		return (2.0 / ph_r()) * upos.trasN(uvel);
	}

	void nextstep_noblock(const double dtau){
		const Tprimes tp(upos, uvel, uacc, ujrk, usnp, ucrk);
		const double dt = tp.calc_dt(dtau);
		tnext = time + dt;
		// fprintf(stderr, "! %e = %e + %e\n", tnext, time, dt);
	}
	void nextstep_block(
			const double dtau0, 
			const double tsys,
			const double dtmax,
			double &dtout,
			double &dtauout)
	{
		const Tprimes tp(upos, uvel, uacc, ujrk, usnp, ucrk);
		const double dt0 = tp.calc_dt(dtau0);
		double dt = dtmax;
		while(dt > dt0) dt *= 0.5;
		while(fmod(tsys, dt) > 0.0) dt *= 0.5;
		assert(dt > 1.e-15);

		const double dtau = tp.solve_dtau((tsys + dt) - time, dtau0);
		const double dtp = tp.calc_dt(dtau);
		tnext = time + dtp;
		// fprintf(stdout, "# %22.16e\n", dtp);

		dtout   = dt;
		dtauout = dtau;
	}

	double correct_time(const double dtau, const KSBinary &p) const {
		const double a0 = upos*upos;
		const double j0 = 2.0 * (upos*uvel);
		const double s0 = 2.0 * (upos*uacc + uvel*uvel);
		const double c0 = 2.0 * (upos*ujrk) + 6.0 * (uvel*uacc);
		const double a1 = p.upos*p.upos;
		const double j1 = 2.0 * (p.upos*p.uvel);
		const double s1 = 2.0 * (p.upos*p.uacc + p.uvel*p.uvel);
		const double c1 = 2.0 * (p.upos*p.ujrk) + 6.0 * (p.uvel*p.uacc);

		const double h2  = (1./2.)  * dtau;
		const double h3  = (1./3.)  * dtau;
		const double h5  = (1./5.)  * dtau;
		const double h6  = (1./6.)  * dtau;
		const double h12 = (1./12.) * dtau;
		const double h14 = (1./14.) * dtau;
		const double h20 = (1./20.) * dtau;

		const double dt_4th = h2*((a1+a0) - h6*(j1-j0));
		const double dt_6th = h2*((a1+a0) - h5*((j1-j0) - h12*(s1+s0)));
		const double dt_8th = h2*((a1+a0) - h14*(3.0*(j1-j0) - h3*((s1+s0) - h20*(c1-c0))));
		// fprintf(stdout, "# %22.16e %22.16e %22.16e %22.16e\n", tnext-time, dt_4th, dt_6th, dt_8th);

		return tnext;
		return time + dt_8th;
		return time + dt_6th;
		return time + dt_4th;
	}

};

struct KSPred{
	KSVec upos, uvel;
	double h;

	void predict(const KSBinary &p, const double dtau){
		const double s1 = dtau;
		const double s2 = (1./2.) * dtau;
		const double s3 = (1./3.) * dtau;
		const double s4 = (1./4.) * dtau;
		const double s5 = (1./5.) * dtau;

		upos = p.upos + s1*(p.uvel + s2*(p.uacc + s3*(p.ujrk + s4*(p.usnp + s5*(p.ucrk)))));
		uvel = p.uvel + s1*(p.uacc + s2*(p.ujrk + s3*(p.usnp + s4*(p.ucrk))));
		h = p.h + s1*(p.d1h + s2*(p.d2h + s3*(p.d3h * s4*(p.d4h))));
	}
};

struct KSForce{
	KSVec uacc, ujrk;
	double d1h, d2h;

	void force_unperturbed(const KSPred &pred){
		const double h2 = 0.5 * pred.h;
		uacc =  h2 * pred.upos;
		ujrk =  h2 * pred.uvel;
		d1h = d2h = 0.0;
	}

	void force_perturbed(
			const KSPred &pred, 
			const KSVec  &ph_acc,
			const KSVec  &ph_jrk)
	{
		const KSVec upos = pred.upos;
		const KSVec uvel = pred.uvel;
		const double h = pred.h;
		const double R = upos * upos;
		const double Rpr = 2.0 *(upos * uvel);
		const KSVec Q = upos.trasT(ph_acc);
		const KSVec Qpr = uvel.trasT(ph_acc) + R * upos.trasT(ph_jrk);

		uacc = 0.5 * (h*upos + R*Q);
		d1h  = 2.0 * (uvel*Q);
		ujrk = 0.5 * (d1h*upos + h*uvel + Rpr*Q + R*Qpr);
		d2h  = 2.0 * (uacc*Q + uvel*Qpr);
	}

};

template <typename T>
struct H4Corr{
	T x1, v1; // position, velocity at tnew
	T s1, c1; // snap, crackle at tnew
	typedef const T CT;
	H4Corr(const double dt, CT x0, CT v0, CT a0, CT j0, CT a1, CT j1){
		const double h = 0.5*dt, hi = 2.0/dt;
		CT Ap = (a1 + a0);
		CT Am = (a1 - a0);
		CT Jp = h *(j1 + j0);
		CT Jm = h *(j1 - j0);
		v1 = v0 + h*(Ap - (1./3.)*Jm);
#if 1
		x1 = x0 + h*((v1 + v0) - ((1./3.)*h) * Am);
#else
		x1 = x0 + h*((v1 + v0) + h*(-0.4*Am + (1./15.)*Jp));
#endif
		
		// derivatives at middle point
		CT snp = (0.5*hi*hi) * Jm;
		CT crk = (1.5*hi*hi*hi) * (Jp - Am);

		s1 = snp + h * crk; // shift forward
		c1 = crk;
	}
};

static inline KSBinary KSCorr(
		const double dtau,
		const KSBinary &p,
		const KSForce  &fo)
{
	H4Corr<KSVec> ucorr(dtau, p.upos, p.uvel, p.uacc, p.ujrk, fo.uacc, fo.ujrk);
	H4Corr<double> hcorr(dtau, 0.0, p.h, p.d1h, p.d2h, fo.d1h, fo.d2h);
	KSBinary pnew;
	pnew.upos = ucorr.x1;
	pnew.uvel = ucorr.v1;
	pnew.uacc = fo.uacc;
	pnew.ujrk = fo.ujrk;
	pnew.usnp = ucorr.s1;
	pnew.ucrk = ucorr.c1;
	pnew.h    = hcorr.v1;
	pnew.d1h  = fo.d1h;
	pnew.d2h  = fo.d2h;
	pnew.d3h  = hcorr.s1;
	pnew.d4h  = hcorr.c1;
	pnew.mass = p.mass;
	pnew.time = p.tnext;

	return pnew;
}
