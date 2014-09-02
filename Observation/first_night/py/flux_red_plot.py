#!/usr/bin/env python
import numpy as np
import scipy
import os,sys
import os.path
import matplotlib
import pylab

matplotlib.use('pdf')
#matplotlib.use('Agg')
import matplotlib.pyplot as plt

from optparse import OptionParser
from matplotlib import cm
import scipy.interpolate as interp
# do stellar locus interpolation

# m ------------------------------------------------
id,x,y,mag_aper_m,mag_aper_err,mag_auto,mag_auto_err,flux_radius,flags= np.loadtxt('m.cat',usecols=(0,1,2,3,4,5,6,7,8), unpack=True, comments='#') 

mag_aper_i,mag_aper_err_i,flux_radius_i= np.loadtxt('m-i.cat',usecols=(3,4,7), unpack=True, comments='#') 

mag_aper_d,mag_aper_err_d,flux_radius_d= np.loadtxt('m-d.cat',usecols=(3,4,7), unpack=True, comments='#') 

id2,x2,y2,mag_aper_m2,mag_aper_err2,mag_auto2,mag_auto_err2,flux_radius2,flags2= np.loadtxt('m2.cat',usecols=(0,1,2,3,4,5,6,7,8), unpack=True, comments='#') 

mag_aper_i2,mag_aper_err_i2,flux_radius_i2= np.loadtxt('m2-i.cat',usecols=(3,4,7), unpack=True, comments='#') 

mag_aper_d2,mag_aper_err_d2,flux_radius_d2= np.loadtxt('m2-d.cat',usecols=(3,4,7), unpack=True, comments='#') 

select = (flux_radius> 1.3) & (flux_radius < 1.8) & (mag_auto > 12) & (mag_auto < 19) & (mag_aper_err < 30) & (mag_aper_err_i < 30) & (mag_aper_err_d < 30)
select2 = (flux_radius2> 1.2) & (flux_radius2 < 1.7) & (mag_auto2 > 12) & (mag_auto2 < 19) & (mag_aper_err2 < 30) & (mag_aper_err_i2 < 30) & (mag_aper_err_d2 < 30)

di = mag_aper_d[select]-mag_aper_i[select]
im = mag_aper_i[select]-mag_aper_m[select]

di2 = mag_aper_d2[select2]-mag_aper_i2[select2]
im2 = mag_aper_i2[select2]-mag_aper_m2[select2]

# number plot----------------------------------------
histbin=20
fig = plt.figure(1)
histcount=plt.hist(mag_auto[select],bins=histbin,range=[12.0,19])[0]
histmag=plt.hist(mag_auto[select],bins=histbin,range=[12.0,19])[1]
for i in range(histmag.size-1):
    histmag[i]=(histmag[i]+histmag[i+1])/2
histmag=histmag[0:histbin]
histcount2=plt.hist(mag_auto2[select2],bins=histbin,range=[12.0,18])[0]
histmag2=plt.hist(mag_auto2[select2],bins=histbin,range=[12.0,19])[1]
for i in range(histmag2.size-1):
    histmag2[i]=(histmag2[i]+histmag2[i+1])/2
histmag2=histmag2[0:histbin]
plt.clf()
ax=fig.add_subplot(111)
ax.set_xlabel(r'Magnitude(mag)',fontsize=16)
ax.set_ylabel(r'Number/(mag.deg^2)',fontsize=16)
plt.semilogy(histmag,histcount)
plt.semilogy(histmag2,histcount2)
plt.title('m band number counts per magnitude per degree square')
plt.xlim(12,19)
plt.savefig('plot/hist-num_m.pdf')

# d-i histogram---------------------------------------
fig = plt.figure(2)
plt.clf()
ax=fig.add_subplot(111)
ax.set_xlabel(r'd-i',fontsize=16)
ax.set_ylabel(r'Number counts',fontsize=16)
plt.hist(di,bins=55,range=[0,6])
plt.title('m-selected')
plt.xlim(0, 6)
plt.ylim(0, 500)
plt.savefig('plot/hist-di_m.pdf')

# d-i vs i-m diagram ---------------------------------
fig = plt.figure(3)
plt.clf()
ax=fig.add_subplot(111)
ax.set_xlabel(r'd-i',fontsize=16)
ax.set_ylabel(r'i-m',fontsize=16)
plt.scatter(di, im, 1)
plt.title('Color-Color diagram based on m-selected')
plt.xlim(0, 4)
plt.ylim(-0.5, 2)
plt.savefig('plot/di-im_m.pdf')

# flux radius diagram --------------------------------
fig = plt.figure(4)
plt.clf()
ax=fig.add_subplot(111)
ax.set_xlabel(r'Mag',fontsize=16)
ax.set_ylabel(r'Flux_radius',fontsize=16)
plt.scatter(mag_auto, flux_radius, 1)
plt.title('m-selected stars')
plt.xlim(10, 20)
plt.ylim(0, 10)
plt.savefig('plot/flux_m.pdf')

fig = plt.figure(5)
plt.clf()
ax.set_xlabel(r'Magnitude(mag)',fontsize=16)
ax.set_ylabel(r'Flux Radius',fontsize=16)
plt.scatter(mag_auto2, flux_radius2, 1)
plt.title('m band flux-radius vs magnitude')
plt.xlim(10, 20)
plt.ylim(0, 10)
plt.savefig('plot/flux_m2.pdf')

fig = plt.figure(6)
plt.clf()
ax=fig.add_subplot(111)
ax.set_xlabel(r'Magnitude(mag)',fo ntsize=16)
ax.set_ylabel(r'Number/(mag.deg^2)',fontsize=16)
plt.hist(mag_auto,bins=100,range=[10,22])
plt.title('m band')
plt.xlim(10, 22)
plt.savefig('plot/hist_m.pdf')
