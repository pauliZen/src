#!/usr/bin/env python

import pydeproj
import numpy
import pylab
import scipy

da=float(open('zda.txt','r').readlines()[1].split()[1])
ptr=.492*4.848E-3*da

sf=open('sbp/sur_flux.qdp','r').readlines()
sur=[]
for i in range(0,len(sf)):
	sur.append(float(sf[i].split()[2]))
sbp_mean=scipy.array(sur)
print sbp_mean

mm=open('spc/ans30.reg','r').readlines()
qq=[0]
for i in range(1,len(mm)):
	qq.append(float(mm[i].split(',')[3][:-2]))
rlist=scipy.array(qq)
rmidlist=(rlist[0:len(rlist)-1]+rlist[1:len(rlist)])/2
print rmidlist

kk=open('kt-30.qdp','r').readlines()
tt=[]
for i in kk:
	tt.append(float(i.split()[1]))
kTlist_mean=scipy.array(tt)
print kTlist_mean

Alist_mean=numpy.ones(len(kTlist_mean))*.5

mat=pydeproj.deproj_v_calc(rlist,kTlist_mean,Alist_mean).form_matrix();
print mat
nlist=numpy.sqrt(numpy.linalg.solve(mat,sbp_mean));
zz=open('ne-30-beforenorm.qdp','w')
for i in range(0,len(rmidlist)):
    print rmidlist[i]*ptr,nlist[i]*1000
    zz.write(`rmidlist[i]*ptr`+' 0 0 '+`nlist[i]*1000`+' '+`-.1*nlist[i]*1000`+' '+`.1*nlist[i]*1000`+'\n')
zz.close()

