#include <cstdio>
#include <cmath>

int main(){
	const int NITER = 4;
	const double dt = 1./32.;
	const double  w = 1.0;

	const double h  = dt;
	const double h2 = (1./2.) * dt;
	
	double pos, vel, acc;
	pos = 1.0;
	vel = 0.0;
	acc = -w * pos;

	const double e0 = 0.5 * (vel*vel + (w*pos)*(w*pos));

	double t = 0.0;
	for(int i=0; i<10000; i++, t+=dt){
		const double e = 0.5 * (vel*vel + (w*pos)*(w*pos));
		printf("%20.10e%20.10e%20.10e%20.10e%20.10e%20.10e\n", t, pos, vel, pos-cos(w*t), vel + sin(w*t), e-e0);
		if(t > 31.4) break;


		double pos1, vel1, acc1;
		vel1 = vel + h2*acc;
		pos1 = pos + h*vel1;
		for(int n=0; n<NITER; n++){
			acc1 = -w * pos1;
			vel1 = vel + h2*(acc1 + acc);
			pos1 = pos + h2*(vel1 + vel);
		}
		pos = pos1;
		vel = vel1;
		acc = acc1;
	}
}
