#!/usr/bin/env python
import numpy as np
import scipy
import os,sys
import os.path
import matplotlib

#atplotlib.use('pdf')
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from optparse import OptionParser
from matplotlib import cm
import scipy.interpolate as interp
# do stellar locus interpolation

id,x,y,mag_aper_m,mag_aper_err,mag_auto,mag_auto_err,flux_radius,flags= np.loadtxt('m.cat',usecols=(0,1,2,3,4,5,6,7,8), unpack=True, comments='#') 


mag_aper_i,mag_aper_err_i,flux_radius_i= np.loadtxt('m-i.cat',usecols=(3,4,7), unpack=True, comments='#') 


mag_aper_d,mag_aper_err_d,flux_radius_d= np.loadtxt('m-d.cat',usecols=(3,4,7), unpack=True, comments='#') 

select = (flux_radius> 1.25) & (flux_radius_i < 2.0) & (mag_auto > 14) & (mag_auto < 18)
di = mag_aper_d[select]-mag_aper_i[select]
im = mag_aper_i[select]-mag_aper_m[select]


fig = plt.figure(1)
ax=fig.add_subplot(111)
ax.set_xlabel(r'RA',fontsize=16)
ax.set_ylabel(r'DEC',fontsize=16)
plt.scatter(mag_auto[select], flux_radius_i[select], 10, mag_auto[select])
plt.title('FWHM')
plt.xlim(10, 20)
plt.ylim(0, 10)

plt.savefig('fluxrad.pdf')


fig = plt.figure(2)
ax=fig.add_subplot(111)
ax.set_xlabel(r'RA',fontsize=16)
ax.set_ylabel(r'DEC',fontsize=16)
plt.scatter(di, im, 10)
plt.title('FWHM')
plt.xlim(-1, 5)
plt.ylim(-1, 5)
plt.savefig('diim.pdf')

