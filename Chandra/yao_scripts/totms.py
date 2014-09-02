#!/usr/bin/env python


import math
import sys

beta=float(sys.argv[1])
n0=float(sys.argv[2])
rc=float(sys.argv[3])
a=float(sys.argv[4])
b=float(sys.argv[5])

mp=1.67262*pow(10,-27)
gc=6.673*pow(10,-11)
solar=1.98892*pow(10,30)

f=open('totms.qdp','w')
for i in range(1,1000):
    kti=a*pow(i,b)*1.6*pow(10,-16)
    nei=n0*pow(1+pow(i/rc,2),-1.5*beta)*pow(10,6)
    pi=kti*nei*1.92
    j=i+1
    ktj=a*pow(j,b)*1.6*pow(10,-16)
    nej=n0*pow(1+pow(j/rc,2),-1.5*beta)*pow(10,6)
    pj=ktj*nej*1.92
    detp=pj-pi
    row=1.2*nei*mp
    
    totms=-i*i*3.0857*pow(10,19)/gc/row*detp/solar
    
    f.write(`i`+' '+`totms`+'\n')
    print i,nei,kti,totms
f.close()
