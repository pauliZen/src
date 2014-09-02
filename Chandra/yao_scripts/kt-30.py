#!/usr/bin/env python
import numpy
import scipy
import math
import sys

z=float(open('zda.txt','r').readlines()[0].split()[1])
da=float(open('zda.txt','r').readlines()[1].split()[1])
ptr=.492*4.848*10**(-3)*da

ff=open('kt-para.txt','r').readlines()
qq=[]
for i in ff:
	qq.append(float(i.split()[1]))
ktpara=scipy.array(qq)
t0,rcool,acool,tmin,rt,a,c,b=ktpara

mm=open('spc/ans30.reg','r').readlines()
qq=[0]
for i in range(1,len(mm)):
	qq.append(float(mm[i].split(',')[3][:-2]))
rlist=scipy.array(qq)
rmidlist=(rlist[0:len(rlist)-1]+rlist[1:len(rlist)])/2*ptr
f=open('kt-30.qdp','w')
for r in rmidlist:
	kt=t0*pow(r/rt,-a)/pow((1+pow(r/rt,b)),c/b)*(pow(r/rcool,acool)+tmin/t0)/(pow(r/rcool,acool)+1)
   	f.write(`r`+' '+`kt`+'\n')
   	print r,kt
f.close()
