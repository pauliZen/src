#!/usr/bin/env python

import numpy
import scipy
import math

z=float(open('zda.txt','r').readlines()[0].split()[1])
da=float(open('zda.txt','r').readlines()[1].split()[1])
#pixel to real
ptr=.492*4.848E-3*da

mm=open('spc/ans6.reg','r').readlines()
qq=[0]
for i in range(1,len(mm)):
	qq.append(float(mm[i].split(',')[3][:-2]))
rlist=scipy.array(qq)
rmidlist_pxl=(rlist[0:len(rlist)-1]+rlist[1:len(rlist)])/2
rlist_pxl=rlist
left=rlist_pxl[:-1]-rmidlist_pxl
rmidlist=rmidlist_pxl/121.951
rlist=rlist/121.951


ff=open('spc/flux-err.txt','r').readlines()
flux=[]
fdown=[]
fup=[]
for i in range(0,len(ff)):
	flux.append(float(ff[i].split()[0]))
	fdown.append(float(ff[i].split()[1]))
	fup.append(float(ff[i].split()[2]))
flux=scipy.array(flux)
fdown=scipy.array(fdown)
fup=scipy.array(fup)

fminus=fdown[0:len(fdown)]-flux[0:len(flux)]
fplus=fup[0:len(fup)]-flux[0:len(flux)]

sur=flux/(math.pi*(rlist[1:len(rlist)]**2-rlist[0:len(rlist)-1]**2))
sminus=fminus/(math.pi*(rlist[1:len(rlist)]**2-rlist[0:len(rlist)-1]**2))
splus=fplus/(math.pi*(rlist[1:len(rlist)]**2-rlist[0:len(rlist)-1]**2))
#enlarge the value so that convince the fitting
sur_11=sur*1e11
sminus_11=sminus*1e11
splus_11=splus*1e11

fluxfile=open('sur.qdp','w')
for i in range(0,len(mm)-1):
	fluxfile.write(`rmidlist_pxl[i]*ptr`+' '+`left[i]*ptr`+' '+`-left[i]*ptr`+' ')
	#fluxfile.write(`sur_11[i]`+' '+`sminus_11[i]`+' '+`splus_11[i]`+'\n')
	fluxfile.write(`sur_11[i]`+' -0.01 0.01\n')
	print rmidlist_pxl[i]*ptr,sur_11[i]
fluxfile.close()
