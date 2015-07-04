import numpy as np
import matplotlib.pyplot as plt
import math
import sys

filename='sb.data'
rmin=0.0
rmax=100.0
tscale=1.0

narg=len(sys.argv)
if (narg>=2):
    filename=sys.argv[1]
    if (filename == '-h'):
        print 'arguments: datafile[sb.data] rmin[0.0] rmax[100.0] tscale[1.0]'
        quit()
if (narg>=3):
    rmin=float(sys.argv[2])
if (narg>=4):
    rmax=float(sys.argv[3])
if (narg>=5):
    tscale=float(sys.argv[4])

x,y,k,mv=np.loadtxt(filename,unpack=True,usecols=(1,2,7,17))

title=('MS<0.7','MS','HG','RG','CHB','FAGB','SAGB','HMS','HHG','HGB','H-WD','CO-WD','ON-WD','NS','BH')
colors=('b',    '#333300',  '#00FF00', 'r', '#FF00FF',  'c',  '#9900FF',   'm',   '#6600FF',  '#6666CC', '#FF9331',    '#9D9D00',   '#CCFF00',    'k',  'w')

fig = plt.figure()
plt.title('Time[Myr] = %.2f; r[pc] = (%.4f ~ %.4f)' % (tscale*float(filename[5:-5]),rmin,rmax))
plt.xlabel('Log(L[L*])')
plt.ylabel('Number')
#plt.yscale('log')
#plt.ylim(0.1,1000)
r=x*x+y*y
rmax2=rmax*rmax
rmin2=rmin*rmin
select = (r<=rmax2) & (r>rmin2)
rr=r[select]
rdata=mv[select]
ldata=0.4*(4.83-rdata)
rk=k[select]
print 'Number %d' % rdata.size
plt.xlim(-5,np.max(ldata)+1)
for i in range(15):
    data=ldata[rk==i]
    if (data.size>0):
        plt.hist(data,100,histtype='step',label=title[i],color=colors[i],alpha=1.0)
    if (i==3) | (i==4):
        datar=np.sqrt(rr[rk==i])
        print(np.transpose((datar,data)))
plt.legend(framealpha=0.7,loc='upper left')
plt.savefig('lum_dist.png')
plt.close(fig)

