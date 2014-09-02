#!/usr/bin/env python

import scipy
import math
import sys


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


mp=1.67262*pow(10,-27)
gc=6.673*pow(10,-11)
solar=1.98892*pow(10,30)

f=open('totms8.qdp','w')
g=open('pressure.qdp','w')
for i in range(1,3000):
    kti=t0*pow(i/rt,-a)/pow((1+pow(i/rt,b)),c/b)*(pow(i/rcool,acool)+tmin/t0)/(pow(i/rcool,acool)+1)*1.6*pow(10,-16)
    nei=n0*pow(1+pow(i/rc,2),-1.5*beta)*pow(10,6)
    pi=kti*nei*1.92
    g.write(`i`+' ' +`pi`+'\n')

    j=i+1
    ktj=t0*pow(j/rt,-a)/pow((1+pow(j/rt,b)),c/b)*(pow(j/rcool,acool)+tmin/t0)/(pow(j/rcool,acool)+1)*1.6*pow(10,-16)
    nej=n0*pow(1+pow(j/rc,2),-1.5*beta)*pow(10,6)
    pj=ktj*nej*1.92

    detp=pj-pi
    row=1.2*nei*mp
    totms=-i*i*3.0857*pow(10,19)/gc/row*detp/solar
    
    f.write(`i`+' '+`totms`+'\n')
    print i,totms
f.close()
