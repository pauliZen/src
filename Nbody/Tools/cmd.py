import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from mpl_toolkits.mplot3d import Axes3D
import h5py
import math
import sys

file='data.prj'
lum='V'
lums=('B','V','I')
color='B-V'
colors=('B-V','V-I','B-I')
dout='cmd'
format='png'
cmin=-0.5
cmax=3.0
mmin=20.0
mmax=-8.0
msize=4.0

narg=len(sys.argv)
if (narg>=2):
    file=sys.argv[1]
    if (file == '-h'):
        print 'arguments: data[data.prj] lum[V] color[B-V] dataout[cmd] format[png] mmin[20.0] mmax[-8.0] cmin[-0.5] cmax[2.0] markersize[4.0]'
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
if (narg>=7):
    mmin=float(sys.argv[6])
if (narg>=8):
    mmax=float(sys.argv[7])
if (narg>=9):
    cmin=float(sys.argv[8])
if (narg>=10):
    cmax=float(sys.argv[9])
if (narg>=11):
    msize=float(sys.argv[10])


IB,K1,K2,V,B,I = np.loadtxt(file,usecols=(0,7,8,17,19,20),unpack=True)

M = V
if lum == 'I':  M = B
if lum == 'B':  M = I

C = np.array([])
if color == 'B-V': C = B-V
if color == 'V-I': C = V-I
if color == 'B-I': C = B-I

colors=('#0000A0', '#0000FF', '#00FFFF', '#FF0000','#FF00FF', '#A52A2A', '#800000', '#FFFF00', '#FFA500', '#808000', '#808080')
colors_b=('#1569C7','#736AFF','#616D7E','#667C26','#254117','#7F38EC','#7D1B7E','#F6358A','#E56E94','#C12267','#0C090A')
#     darkblue, blue, cyan, red, magenta, Brown, Maroon, Yellow, orange, Olive, Grey
title=(r'MS$<0.7M_{\odot}$',r'MS$\geq 0.7M_{\odot}$','HG','RG','CHB','FAGB','SAGB','HMS','HHG','HGB','WD')
title_b=(r'MS-B$<0.7M_{\odot}$',r'MS-B$\geq 0.7M_{\odot}$','HG-B','RG-B','CHB-B','FAGB-B','SAGB-B','HMS-B','HHG-B','HGB-B','WD-B')

fig = plt.figure(figsize=(24,18))
fsize=32
#lsize=1
plt.grid('off')
plt.title('')
plt.xlabel(color,fontsize=fsize)
#plt.xlabel(color)
plt.ylabel(lum,fontsize=fsize)
#plt.ylabel(lum)
plt.xlim(cmin,cmax)
plt.ylim(mmin,mmax)
#plt.plot(log10(t),log10(l),'.',log10(bt1),log10(bl1),'.',log10(bt2),log10(bl2),'.')
#plt.plot(log10(t),log10(l),'.',log10((bt1+bt2)/2),log10(bl1+bl2),'.')

SM = M[IB==0]
SC = C[IB==0]
SK = K1[IB==0]
BM = M[IB==1]
BC = C[IB==1]
BK1 = K1[IB==1]
BK2 = K2[IB==1]
BKB = np.array(map(lambda x,y: max(x,y), BK1,BK2))

patchs=[]

for i in range(10):
    X=SC[SK==i]
    if X.size>0:
#        if X.size<5E4:
        plt.plot(X,SM[SK==i],'.',color=colors[i],label=title[i],markersize=msize)
#        else:
#            plt.plot(X[::int(X.size/5E4)],SM[SK==i][::int(X.size/5E4)],'.',color=colors[i],label=title[i],markersize=msize)
        patch = mpatches.Patch(color=colors[i], label=title[i])
        patchs.append(patch)
#        else:
#            plt.plot(X[0:X.size/50],SM[SK==i][0:X.size/50],'.',color=colors[i],label=title[i],markersize=0.1)
    X=BC[BKB==i]
    if X.size>0: 
#        if X.size<1E5:
        plt.plot(X,BM[BKB==i],'.',color=colors_b[i],label=title_b[i],markersize=msize)
        patch = mpatches.Patch(color=colors_b[i], label=title_b[i])
        patchs.append(patch)
#        else:
#            plt.plot(X[0:X.size/3],BM[BKB==i][0:X.size/3],'.',color=colors_b[i],label=title_b[i],markersize=0.1)
X=SC[(SK>=10) & (SK<=12)]
if X.size>0:
    plt.plot(X,SM[(SK>=10) & (SK<=12)],'.',color=colors[10],label=title[10],markersize=msize)
    patch = mpatches.Patch(color=colors[10], label=title[10])
    patchs.append(patch)

X=BC[(BKB>=10) & (BKB<=12)]
if X.size>0: 
    plt.plot(X,BM[(BKB>=10) & (BKB<=12)],'.',color=colors_b[10],label=title_b[10],markersize=msize)
    patch = mpatches.Patch(color=colors_b[10], label=title_b[10])
    patchs.append(patch)

plt.legend(handles=patchs,framealpha=0.7,loc='upper right',fontsize=fsize)
#plt.legend(handles=patchs,framealpha=0.7,loc='upper right')
plt.yticks(fontsize=fsize)
plt.xticks(fontsize=fsize)
#paxis = plt.axis()
#plt.tick_params(width=lsize)
#plt.axis(linewidth=100.0)
plt.savefig(dout+'.'+format)
plt.close(fig)

