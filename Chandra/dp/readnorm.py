#!/usr/bin/env python

import numpy
import scipy

z=float(open('zda.txt','r').readlines()[0].split()[1])
da=float(open('zda.txt','r').readlines()[1].split()[1])
#pixel to real
ptr=.492*4.848E-3*da

mm=open('spc/ans6.reg','r').readlines()
qq=[0]
for i in range(1,len(mm)):
	qq.append(float(mm[i].split(',')[3][:-2]))
rlist=scipy.array(qq)
rmidlist=(rlist[0:len(rlist)-1]+rlist[1:len(rlist)])/2
left=rlist[:-1]-rmidlist
detr3=rlist[1:len(rlist)]**3-rlist[0:len(rlist)-1]**3

ff=open('spc/norm-err.txt','r').readlines()

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

ne=(3*10**14*mean*((1+z))**2/((detr3)*(0.492*4.8481368E-6)**3*da*10**6*3.0857E18)/1.2)**.5
errminus=(3*10**14*abs(errdown[0:len(errdown)]-mean[0:len(mean)])*((1+z))**2/((detr3)*(0.492*4.8481368E-6)**3*da*10**6*3.0857E18)/1.2)**.5
errplus=(3*10**14*abs(errup[0:len(errup)]-mean[0:len(mean)])*((1+z))**2/((detr3)*(0.492*4.8481368E-6)**3*da*10**6*3.0857E18)/1.2)**.5

pp=open('ne.qdp','w')
for i in range(0,6):
	pp.write(`rmidlist[i]*ptr`+' '+`left[i]*ptr`+' '+`-left[i]*ptr`+' ')
	pp.write(`ne[i]`+' '+`-errminus[i]`+' '+`errplus[i]`+'\n')

pp.close()
