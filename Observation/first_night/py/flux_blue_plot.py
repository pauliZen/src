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

# d ------------------------------------------------
id,x,y,mag_aper_d,mag_aper_err,mag_auto,mag_auto_err,flux_radius,flags= np.loadtxt('d.cat',usecols=(0,1,2,3,4,5,6,7,8), unpack=True, comments='#') 

mag_aper_i,mag_aper_err_i,flux_radius_i= np.loadtxt('d-i.cat',usecols=(3,4,7), unpack=True, comments='#') 

mag_aper_m,mag_aper_err_m,flux_radius_m= np.loadtxt('d-m.cat',usecols=(3,4,7), unpack=True, comments='#') 

select = (flux_radius> 1.25) & (flux_radius < 2.0) & (mag_auto > 13) & (mag_auto < 21) & (mag_aper_err < 30) & (mag_aper_err_i < 30) & (mag_aper_err_m < 30)
di = mag_aper_d[select]-mag_aper_i[select]
im = mag_aper_i[select]-mag_aper_m[select]

# number plot----------------------------------------
histbin=20
fig = plt.figure(1)
histcount=plt.hist(mag_auto[select],bins=histbin,range=[13.0,21])[0]
histmag=plt.hist(mag_auto[select],bins=histbin,range=[13.0,21])[1]
for i in range(histmag.size-1):
    histmag[i]=(histmag[i]+histmag[i+1])/2
histmag=histmag[0:histbin]
plt.clf()
ax=fig.add_subplot(111)
ax.set_xlabel(r'Magnitude(mag)',fontsize=16)
ax.set_ylabel(r'Number/(mag.deg^2)',fontsize=16)
plt.semilogy(histmag,histcount)
plt.title('d band number counts per magnitude per degree square')
plt.xlim(14,18)
plt.savefig('plot/hist-num_d.pdf')

# d-i histogram---------------------------------------
fig = plt.figure(2)
plt.clf()
ax=fig.add_subplot(111)
ax.set_xlabel(r'd-i',fontsize=16)
ax.set_ylabel(r'Number counts',fontsize=16)
plt.hist(di,bins=55,range=[0,6])
plt.title('d-i Color distrution based on d-selected')
plt.xlim(0, 6)
plt.ylim(0, 500)
plt.savefig('plot/hist-di_d.pdf')

# d-i vs i-m diagram ---------------------------------
fig = plt.figure(3)
plt.clf()
ax=fig.add_subplot(111)
ax.set_xlabel(r'd-i',fontsize=16)
ax.set_ylabel(r'i-m',fontsize=16)
plt.scatter(di, im, 10)
plt.title('Color-Color diagram based on d-selected')
plt.xlim(1, 5)
plt.ylim(-1, 3)
plt.savefig('plot/di-im_d.pdf')

# flux radius diagram --------------------------------
fig = plt.figure(4)
plt.clf()
ax=fig.add_subplot(111)
ax.set_xlabel(r'Magnitude(mag)',fontsize=16)
ax.set_ylabel(r'Flux Radius',fontsize=16)
plt.scatter(mag_auto, flux_radius, 1)
plt.title('d band flux-radius vs magnitude')
plt.xlim(10, 20)
plt.ylim(0, 10)
plt.savefig('plot/flux_d.pdf')

# fig = plt.figure(4)
# ax=fig.add_subplot(111)
# plt.hist(im,bins=50,range=[-2,1])
# plt.title('i-m Color distrution')
# plt.xlim(-2, 1)
# plt.ylim(0, 350)
# plt.savefig('plot/hist-im_d.pdf')

fig = plt.figure(6)
plt.clf()
ax=fig.add_subplot(111)
ax.set_xlabel(r'Magnitude(mag)',fontsize=16)
ax.set_ylabel(r'Number/(mag.deg^2)',fontsize=16)
plt.hist(mag_auto,bins=100,range=[10,22])
plt.title('d band')
plt.xlim(10, 22)
plt.savefig('plot/hist_d.pdf')
