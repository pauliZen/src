import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys

tmin=5.5
tmax=3.0
lmin=-5.0
lmax=8.0

filename='data'
larg=len(sys.argv)
if (larg>=2):
    filename=sys.argv[1]
    if (filename == '-h'):
        print 'arguments: filename[data] Tmin[5.5] Tmax[3.0] Lmin[-5.0] Lmax[8.0]'
        quit()
if (larg>=3):
    tmin=float(sys.argv[2])
if (larg>=4):
    tmax=float(sys.argv[3])
if (larg>=5):
    lmin=float(sys.argv[4])
if (larg>=6):
    lmax=float(sys.argv[5])

m1,m2,l1,l2,r1,r2,k1,k2 = np.loadtxt(filename, usecols=(12,13,14,15,16,17,18,19),unpack=True)

select=(r2>0)
l= np.append(l1,l2[select])
r= np.append(r1,r2[select])
k= np.append(k1,k2[select])
m= np.append(m1,m2[select])

t=0.25*(l-2.0*np.log10(r))+3.7
select=((r>0.3) & (k>=10) & (k<=12))
mm = m[select]
r[select] = 0.0155*np.sqrt((1.44/mm)**(2.0/3.0)-(mm/1.44)**(2.0/3.0))
r[(select & (r<1.886956e-5))] = 1.886956e-5
r[(select & (r>0.1))] = 0.1

colors=('b',    'g',  'g', 'r', 'r',  'c',  'c',   'm',   'm',  'm', '#F6358A','#E56E94','#C12267',    'k',  'w')
title=('MS<0.7','MS','HG','RG','CHB','FAGB','SAGB','HMS','HHG','HGB','H-WD','CO-WD','ON-WD','NS','BH')

fig = plt.figure(figsize=(8,6),dpi=300)
plt.title('HR diagram')
plt.xlabel('Log(Teff[K])')
plt.ylabel('Log(L[L*])')
plt.xlim(tmin,tmax)
plt.ylim(lmin,lmax)
#plt.plot(log10(t),log10(l),'.',log10(bt1),log10(bl1),'.',log10(bt2),log10(bl2),'.')
#plt.plot(log10(t),log10(l),'.',log10((bt1+bt2)/2),log10(bl1+bl2),'.')
for i in range(14):
    plt.plot(t[k==i],l[k==i],'.',color=colors[i],label=title[i])
    plt.legend(framealpha=0.7,loc='upper left')
plt.savefig('hr.png')
plt.close(fig)
