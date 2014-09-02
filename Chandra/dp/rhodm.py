#!/usr/bin/env python

import scipy
import math
import sys

mp=1.67262*pow(10,-27)
gc=6.673*pow(10,-11)
solar=1.98892E30

ff=open('kt-para.txt','r').readlines()
qq=[]
for i in ff:
	qq.append(float(i.split()[1]))
ktpara=scipy.array(qq)
t0,rcool,acool,tmin,rt,a,c,b=ktpara

n0=float(open('ne-para.txt','r').readlines()[0].split()[1])
rc=float(open('ne-30-beforenorm-para.txt','r').readlines()[1].split()[1])
beta=float(open('ne-30-beforenorm-para.txt','r').readlines()[2].split()[1])

z=float(open('zda.txt','r').readlines()[0].split()[1])
da=float(open('zda.txt','r').readlines()[1].split()[1])

#pixel to kpc
ptr=.492*4.848E-3*da

rr=open('spc/ans6.reg','r').readlines()
rout=float(rr[len(rr)-1].split(',')[3][:-2])
rout_kpc=rout*ptr

f=open('rhodm.qdp','w')
for i in range(1,rout_kpc):
    kti=t0*pow(i/rt,-a)/pow((1+pow(i/rt,b)),c/b)*(pow(i/rcool,acool)+tmin/t0)/(pow(i/rcool,acool)+1)*1.6*pow(10,-16)
    nei=n0*pow(1+pow(i/rc,2),-1.5*beta)*pow(10,6)
    pi=kti*nei*1.92

    j=i+1
    ktj=t0*pow(j/rt,-a)/pow((1+pow(j/rt,b)),c/b)*(pow(j/rcool,acool)+tmin/t0)/(pow(j/rcool,acool)+1)*1.6*pow(10,-16)
    nej=n0*pow(1+pow(j/rc,2),-1.5*beta)*pow(10,6)
    pj=ktj*nej*1.92

    k=i+2
    ktk=t0*pow(k/rt,-a)/pow((1+pow(k/rt,b)),c/b)*(pow(k/rcool,acool)+tmin/t0)/(pow(k/rcool,acool)+1)*1.6*pow(10,-16)
    nek=n0*pow(1+pow(k/rc,2),-1.5*beta)*pow(10,6)
    pk=ktk*nek*1.92

    detp1=pj-pi
    rowi=1.2*nei*mp
    totms1=-i*i*3.0857e19/gc/rowi*detp1/solar

    detp2=pk-pj
    rowj=1.2*nej*mp
    totms2=-j*j*3.0857e19/gc/rowj*detp2/solar

    dm=totms2-totms1
    rho=dm/(4*3.14159*i**2)
    rhodm=rho-rowi

    f.write(`i`+' -.5 .5 '+`rhodm/100`+' '+`-rhodm/1000`+' '+`rhodm/1000`+'\n')
    print i,rhodm/100
f.close()
