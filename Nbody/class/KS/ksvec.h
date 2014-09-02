#pragma once

#include <cstdio>
#include <cmath>

struct KSVec{
	double u1, u2, u3, u4;

	KSVec() : u1(0.0), u2(0.0), u3(0.0), u4(0.0) {}
	KSVec(const double x, const double y, const double z)
		: u1(x), u2(y), u3(z), u4(0.0) {}
	KSVec(const double x, const double y, const double z, const double w)
		: u1(x), u2(y), u3(z), u4(w) {}

	KSVec operator+(const KSVec &rhs) const {
		return KSVec(u1+rhs.u1, u2+rhs.u2, u3+rhs.u3, u4+rhs.u4);
	}
	KSVec operator-(const KSVec &rhs) const {
		return KSVec(u1-rhs.u1, u2-rhs.u2, u3-rhs.u3, u4-rhs.u4);
	}
	double operator*(const KSVec &rhs) const {
		return u1*rhs.u1 + u2*rhs.u2 + u3*rhs.u3 + u4*rhs.u4;
	}
	friend KSVec operator*(const double s, const KSVec &rhs){
		return KSVec(s*rhs.u1, s*rhs.u2, s*rhs.u3, s*rhs.u4);
	}

	KSVec trasN(const KSVec &v) const {
		return KSVec(
				+u1*v.u1 - u2*v.u2 - u3*v.u3 + u4*v.u4,
				+u2*v.u1 + u1*v.u2 - u4*v.u3 - u3*v.u4,
				+u3*v.u1 + u4*v.u2 + u1*v.u3 + u2*v.u4,
				+u4*v.u1 - u3*v.u2 + u2*v.u3 - u1*v.u4);
	}

	KSVec trasT(const KSVec &v) const {
		return KSVec(
				+u1*v.u1 + u2*v.u2 + u3*v.u3 + u4*v.u4,
				-u2*v.u1 + u1*v.u2 + u4*v.u3 - u3*v.u4,
				-u3*v.u1 - u4*v.u2 + u1*v.u3 + u2*v.u4,
				+u4*v.u1 - u3*v.u2 + u2*v.u3 - u1*v.u4);
	}

	static KSVec init_coord(const double x, const double y, const double z){
		const double r = sqrt(x*x + y*y + z*z);
		if(x > 0.0){
			const double u1 = sqrt(0.5 * (r + x));
			const double u2 = 0.5 * y / u1;
			const double u3 = 0.5 * z / u1;
			const double u4 = 0.0;
			return KSVec(u1, u2, u3, u4);
		}else{
			const double u2 = sqrt(0.5 * (r - x));
			const double u1 = 0.5 * y / u2;
			const double u4 = 0.5 * z / u2;
			const double u3 = 0.0;
			return KSVec(u1, u2, u3, u4);
		}
	}

	void write_back(double &x, double &y, double &z) const {
		x = u1; y = u2; z = u3;
	}

	int print(FILE *fp = stdout, const char *fmt = "[%e, %e, %e, %e]\n") const {
		return fprintf(fp, fmt, u1, u2, u3, u4);
	}
};

