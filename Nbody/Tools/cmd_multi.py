import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from mpl_toolkits.mplot3d import Axes3D
import h5py
import math
import sys

file='dlst'
lum='V'
lums=('B','V','I')
color='B-V'
colors=('B-V','V-I')
dout='cmd_multi'
format='png'

narg=len(sys.argv)
if (narg>=2):
    file=sys.argv[1]
    if (file == '-h'):
        print 'arguments: projected_datalist_with_time[dlst] lum[V] color[B-V] dataout[cmd_multi] format[png]'
        quit()
if (narg>=3):
    lum=sys.argv[2]
    if not (lum in lums): 
        print 'No filter ',lum,' support'
        quit()
if (narg>=4):
    color=sys.argv[3]
    if not (color in colors):
        print 'No color ',lum,' support'
        quit()
if (narg>=5):
    dout=sys.argv[4]
if (narg>=6):
    format=sys.argv[5]

f = open(file,'r')
path=f.readlines()

fig = plt.figure(figsize=(24,18))
fsize=32
msize=4.0
plt.grid('off')
plt.title('')
plt.xlabel(color,fontsize=fsize)
plt.ylabel(lum,fontsize=fsize)
plt.xlim(-0.5,2.0)
plt.ylim(20.0,-8.0)

##        Black   Blue    Cyan    Green   Lime    Olive   Red     Maroon  Magenta Purple 
colors=('#000000', '#0000FF', '#00FFFF', '#008000', '#00FF00', '#808000', '#FF0000', '#800000', '#FF00FF', '#800080')
patchs=[]

k=0
for i in path:
    filename=i.split()
    V,B,I = np.loadtxt(filename[0],usecols=(17,19,20),unpack=True)
    
    M = V
    if lum == 'I':  M = B
    if lum == 'B':  M = I

    C = np.array([])
    
    if color == 'B-V': C = B-V
    if color == 'V-I': C = V-I

    plt.plot(C,M,'.',color=colors[k],label=filename[1]+' Myr',markersize=msize)
    patch = mpatches.Patch(color=colors[k], label=filename[1]+' Myr')
    patchs.append(patch)
    
    k +=1

plt.legend(handles=patchs,framealpha=0.7,loc='lower right',fontsize=fsize)
plt.yticks(fontsize=fsize)
plt.xticks(fontsize=fsize)
plt.savefig(dout+'.'+format)
plt.close(fig)

