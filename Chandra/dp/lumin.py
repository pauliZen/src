#!/usr/bin/env python

import scipy
import math
import sys
s0=float(open('sur-para.txt','r').readlines()[0].split()[1])*1e-11
rc=float(open('sur-para.txt','r').readlines()[1].split()[1])
beta=float(open('sur-para.txt','r').readlines()[2].split()[1])

z=float(open('zda.txt','r').readlines()[0].split()[1])
da=float(open('zda.txt','r').readlines()[1].split()[1])
dl=float(open('zda.txt','r').readlines()[2].split()[1])

DL=dl*10**6*3.0857E18
DL_kpc=dl*10**3
DA_kpc=da*10**3
l=0
ff=open('lumin.qdp','w')
flux=0
for i in range(1,2000):

	s=s0*(1+(i/rc)**2)**(.5-3*beta)
	#radius: kpc to arcmin
	dflux=s*2*math.pi*(i/DA_kpc/math.pi*180*60)*(1/DA_kpc/math.pi*180*60)
	flux+=dflux
print flux*4*math.pi*DL**2
ff.write(`flux*4*math.pi*DL**2`)
ff.close()

