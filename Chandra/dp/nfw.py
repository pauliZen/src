#!/usr/bin/env python

import scipy
import math
import sys

#open NFW fitting parameter
rho0=float(open('nfw-para.txt','r').readlines()[0].split()[1])
rs=float(open('nfw-para.txt','r').readlines()[1].split()[1])
#open Electron Density fitting parameter
n0=float(open('ne-para.txt','r').readlines()[0].split()[1])
rc=float(open('ne-30-beforenorm-para.txt','r').readlines()[1].split()[1])
beta=float(open('ne-30-beforenorm-para.txt','r').readlines()[2].split()[1])

z=float(open('zda.txt','r').readlines()[0].split()[1])
da=float(open('zda.txt','r').readlines()[1].split()[1])


mp=1.67262E-27
gc=6.673E-11
solar=1.98892E30

tm=0

f=open('totalmass.qdp','w')
for i in range(1,2000):
    rho_ng=n0*pow(1+pow(i/rc,2),-1.5*beta)*pow(10,6)*1.2*mp
    rho_dm=rho0/(i/rs*pow((1+i/rs),2))*100
    rho_tot=rho_ng+rho_dm
    tm+=rho_tot*4*3.14159*i**2
    f.write(`i`+' '+`tm`+'\n')
    print i,tm
f.close()
