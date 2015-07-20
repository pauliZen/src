import numpy as np
import sys
import matplotlib
import matplotlib.pyplot as plt

xmin=4
xmax=1000
bvmin=-0.5
bvmax=1.5
vimin=-0.5
vimax=1.5

flist='sbclst'

##        Black   Blue    Cyan    Green   Lime    Olive   Red     Maroon  Magenta Purple 
colors=('#000000', '#0000FF', '#00FFFF', '#008000', '#00FF00', '#808000', '#FF0000', '#800000', '#FF00FF', '#800080')
markers=("o", "v", "^", "<", ">", "1", "2", "3", "4", "8", "s")

modellist=['R7_IMF93','R7_IMF01','R7_ROT','R3_IMF01']
path=['R7_IMF93/t9','R7_IMF2001/t7','R7_ROT/t7','R3_IMF2001/t4']

#fig = plt.figure(figsize=(6,10))
fig, axes = plt.subplots(nrows=2, ncols=2)
plots = axes.flat

#size of image
figcf = plt.gcf()
figcf.set_size_inches(6,6)
#figcf.tight_layout()

plots[2].set_xlabel('r [arcsec]')
plots[3].set_xlabel('r [arcsec]')
plots[0].set_title(r'B-V [$mag/arcsec^2$]')
plots[1].set_title(r'V-I [$mag/arcsec^2$]')

for n in range(2):
    i=2*n
    plots[i].set_ylim(bvmin,bvmax)
    plots[i+1].set_ylim(vimin,vimax)
    
    for j in range(2):
        plots[i+j].set_xlim(xmin,xmax)
        plots[i+j].set_xscale('log')
#    plots[i].set_ylabel(r'$\mu$ [mag/arcmin$^2$]')
    ff=open(path[n]+'/'+flist,'r')
    files=ff.readlines()
    k=0
    for j in files:
        fname=j.split()
        r,bv,vi=np.loadtxt(path[n]+'/'+fname[0],usecols=(1,5,6),skiprows=1,unpack=True)
        plots[i].plot(r,bv,markers[k],label=fname[1]+' Myr',color=colors[k])
        plots[i].plot(r,bv,color=colors[k])
        plots[i+1].plot(r,vi,markers[k],label=fname[1]+' Myr',color=colors[k])
        plots[i+1].plot(r,vi,color=colors[k])
        k +=1
    plots[i].text(300,1.3,modellist[n])
    plots[i+1].text(300,1.3,modellist[n])
plots[0].legend(bbox_to_anchor=(0., 1.05, 2.1, .102),loc=3,ncol=5,mode="expand",borderaxespad=0.,frameon=False)

fig.savefig('color.eps')

