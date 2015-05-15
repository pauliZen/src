import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import h5py
import math

#f = h5py.File('/home/lwang/data/GC_100/snap/snap.40_999.h5part','r')
#f = h5py.File('/home/lwang/extradata/GC/B100_king/ns2/snap.40_1172.h5part','r')
f = h5py.File('snap.40_11669.h5part','r')
#f = h5py.File('/home/lwang/hdata/snap.40_329.h5part','r')
s = f['/Step#0']
b = s['Binaries']
#m = s['Mergers']

t      = np.array(s['TE'])
l      = np.array(s['L'])
rs     = np.array(s['RS'])
k      = np.array(s['KW'])
mass   = np.array(s['M'])
n      = np.array(s['NAM'])
x1     = np.array(s['X1'])
x2     = np.array(s['X2'])
x3     = np.array(s['X3'])
v1     = np.array(s['V1'])
v2     = np.array(s['V2'])
v3     = np.array(s['V3'])
bt1    = np.array(b['TE1'])
bt2    = np.array(b['TE2'])
bl1    = np.array(b['L1'])
bl2    = np.array(b['L2'])
brs1   = np.array(b['RS1'])
brs2   = np.array(b['RS2'])
bk1    = np.array(b['KW1'])
bk2    = np.array(b['KW2'])
bkc    = np.array(b['KWC'])
bmass1 = np.array(b['M1'])
bmass2 = np.array(b['M2'])
bn1    = np.array(b['NAM1'])
bn2    = np.array(b['NAM2'])
bnc    = np.array(b['NAMC'])
bxc1   = np.array(b['XC1'])
bxc2   = np.array(b['XC2'])
bxc3   = np.array(b['XC3'])
bvc1   = np.array(b['VC1'])
bvc2   = np.array(b['VC2'])
bvc3   = np.array(b['VC3'])
bxr1   = np.array(b['XR1'])
bxr2   = np.array(b['XR2'])
bxr3   = np.array(b['XR3'])
bvr1   = np.array(b['VR1'])
bvr2   = np.array(b['VR2'])
bvr3   = np.array(b['VR3'])

colors=('b',    'g',  'g', 'r', 'r',  'c',  'c',   'm',   'm',  'm', 'y',    'y',   'y',    'k',  'w')
title=('MS<0.7','MS','HG','RG','CHB','FAGB','SAGB','HMS','HHG','HGB','H-WD','CO-WD','ON-WD','NS','BH')

fig = plt.figure(figsize=(8,6),dpi=300)
plt.title('HR diagram')
plt.xlabel('Log(Teff[K])')
plt.ylabel('Log(L[L*])')
plt.xlim(5.5,3.0)
plt.ylim(-5.0,8.0)
#plt.plot(log10(t),log10(l),'.',log10(bt1),log10(bl1),'.',log10(bt2),log10(bl2),'.')
#plt.plot(log10(t),log10(l),'.',log10((bt1+bt2)/2),log10(bl1+bl2),'.')
for i in range(15):
    plt.plot(np.log10(t[k==i]),np.log10(l[k==i]),'.',color=colors[i],label=title[i])
    plt.plot(np.log10(bt1[bk1==i]),np.log10(bl1[bk1==i]),'.',color=colors[i],label='')
    plt.plot(np.log10(bt2[bk2==i]),np.log10(bl2[bk2==i]),'.',color=colors[i],label='')
    plt.legend(framealpha=0.7,loc='upper left')
plt.savefig('hr.png')
plt.close(fig)
