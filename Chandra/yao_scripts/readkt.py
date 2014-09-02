#!/usr/bin/env python

import numpy
import scipy

z=float(open('zda.txt','r').readlines()[0].split()[1])
da=float(open('zda.txt','r').readlines()[1].split()[1])
#pixel to kpc
ptr=.492*4.848E-3*da

mm=open('spc/ans6.reg','r').readlines()
qq=[0]
for i in range(1,len(mm)):
	qq.append(float(mm[i].split(',')[3][:-2]))
rlist=scipy.array(qq)
rmidlist=(rlist[0:len(rlist)-1]+rlist[1:len(rlist)])/2
left=rlist[:-1]-rmidlist
ff=open('spc/kt-err.txt','r').readlines()
mean=[]
errdown=[]
errup=[]
for i in range(0,len(mm)-1):
	mean.append(float(ff[2*i].split()[0]))
	errdown.append(float(ff[2*i+1].split()[0]))
	errup.append(float(ff[2*i+1].split()[1]))
mean=scipy.array(mean)
errdown=scipy.array(errdown)
errup=scipy.array(errup)

errminus=errdown[0:len(errdown)]-mean[0:len(mean)]
errplus=errup[0:len(errup)]-mean[0:len(mean)]
ktfile=open('kt.qdp','w')
for i in range(0,len(mm)-1):
	ktfile.write(`rmidlist[i]*ptr`+' '+`left[i]*ptr`+' '+`-left[i]*ptr`+' ')
	ktfile.write(`mean[i]`+' '+`errminus[i]`+' '+`errplus[i]`+'\n')

ktfile.close()
