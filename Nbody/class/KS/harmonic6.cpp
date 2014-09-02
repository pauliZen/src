#include <cstdio>
#include <cmath>

int main(){
	const int NITER = 3;
	const double dt = 0.25;
	const double  w = 1.0;

	const double h  = dt;
	const double h2 = (1./2.) * dt;
	const double h3 = (1./3.) * dt;
	const double h4 = (1./4.) * dt;
	const double h5 = (1./5.) * dt;
	const double h6 = (1./6.) * dt;
	const double h7 = (1./7.) * dt;
	const double h12 = (1./12.) * dt;
	
	double pos, vel, acc, jrk, snp, crk, d1c, d2c;
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
		d1c = -w * snp;
		d2c = -w * crk;

		double pos1, vel1, acc1, jrk1, snp1;
		pos1 = pos + h*(vel + h2*(acc + h3*(jrk + h4*(snp + h5*(crk + h6*(d1c + h7*(d2c)))))));
		vel1 = vel + h*(acc + h2*(jrk + h3*(snp + h4*(crk + h5*(d1c + h6*(d2c))))));
		for(int n=0; n<NITER; n++){
			acc1 = -w * pos1;
			jrk1 = -w * vel1;
			snp1 = -w * acc1;

			vel1 = vel + h2*((acc1 + acc) - h5*((jrk1 - jrk) - h12*(snp1 + snp)));
			pos1 = pos + h2*((vel1 + vel) - h5*((acc1 - acc) - h12*(jrk1 + jrk)));
		}
		pos = pos1;
		vel = vel1;
		acc = acc1;
		jrk = jrk1;
	}
}
