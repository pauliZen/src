#include <cstdio>
#include <cmath>

int main(){
	const int NITER = 4;
	const double dt = 0.125;
	const double  w = 1.0;

	const double h  = dt;
	const double h2 = (1./2.) * dt;
	const double h3 = (1./3.) * dt;
	const double h4 = (1./4.) * dt;
	const double h5 = (1./5.) * dt;
	const double h6 = (1./6.) * dt;
	const double h12 = (1./12.) * dt;
	
	double pos, vel, acc, jrk, snp, crk;
	pos = 1.0;
	vel = 0.0;
	acc = -w * pos;
	jrk = -w * vel;

	const double e0 = 0.5 * (vel*vel + (w*pos)*(w*pos));

	double t = 0.0;
	for(int i=0; i<10000; i++, t+=dt){
		const double e = 0.5 * (vel*vel + (w*pos)*(w*pos));
		printf("%20.10e%20.10e%20.10e%20.10e%20.10e%20.10e\n", t, pos, vel, pos-cos(w*t), vel + sin(w*t), e-e0);
		if(t > 31.4) break;

		snp = -w * acc;
		crk = -w * jrk;

		double pos1, vel1, acc1, jrk1;
		pos1 = pos + h*(vel + h2*(acc + h3*(jrk + h4*(snp + h5*(crk)))));
		vel1 = vel + h*(acc + h2*(jrk + h3*(snp + h4*(crk))));
		for(int n=0; n<NITER; n++){
			acc1 = -w * pos1;
			jrk1 = -w * vel1;

			vel1 = vel + h2*((acc1 + acc) - h6*(jrk1 - jrk));
#if 0
			pos1 = pos + h2*((vel1 + vel) - h5*((acc1 - acc) - h12*(jrk1 + jrk)));
#else
			pos1 = pos + h2*((vel1 + vel) - h6*(acc1 - acc));
#endif
		}
		pos = pos1;
		vel = vel1;
		acc = acc1;
		jrk = jrk1;
	}
}
