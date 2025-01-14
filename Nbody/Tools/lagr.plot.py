#input:
#argument 3:
#   lagr filename
#   global.30.all filename
#   output format
#argument 6:
#   tscale
#   mscale
#   rscale
#argument 8:
#   tmin
#   tmax
#argument 10:
#   rmin
#   rmax
#argument 12:
#   nmin
#   nmax
#argument 14:
#   vmin
#   vmax
#argument 16:
#   mmin
#   mmax
#argument 18:
#   smin
#   smax
#argment 24:
#   mmmin
#   mmmax
#   nnmin
#   nnmax
#   bbmin
#   bbmax

import numpy as np
import matplotlib.pyplot as plt
import math
import sys

filename='lagr.snap'
glfilename='global.30.all'
outformat='.eps'

tscale=1.0
mscale=1.0
rscale=1.0

tmin=0.0
tmax=150.0

rmin=0.0
rmax=20.0

nmin=0
nmax=10000

vmin=-5.0
vmax=5.0

mmin=0.0
mmax=40.0

smin=0.0
smax=5.0

mmmin=0.0
mmmax=1.0

nnmin=0.0
nnmax=1.0

bbmin=0.0
bbmax=1.0

nmin=0
nmax=1000000

vmin=-5.0
vmax=5.0

mmin=0.0
mmax=40.0

smin=0.0
smax=5.0

mmmin=0.0
mmmax=1.0

nnmin=0.0
nnmax=1.0

bbmin=0.0
bbmax=1.0

hdflag=True

larg=len(sys.argv)-1

if (larg>=3):
    filename   = sys.argv[1]
    glfilename = sys.argv[2]
    outformat  = '.'+sys.argv[3]
if (larg>=6):
    tscale = float(sys.argv[4])
    rscale = float(sys.argv[5])
    mscale = float(sys.argv[6])
if (larg>=8):
    tmin   = float(sys.argv[7])
    tmax   = float(sys.argv[8])
if (larg>=10):   
    rmin   = float(sys.argv[9])
    rmax   = float(sys.argv[10])
if (larg>=12):
    nmin   = int(sys.argv[11])
    nmax   = int(sys.argv[12])
if (larg>=14):
    vmin   = float(sys.argv[13])
    vmax   = float(sys.argv[14])
if (larg>=16):
    mmin   = float(sys.argv[15])
    mmax   = float(sys.argv[16])
if (larg>=18):    
    smin   = float(sys.argv[17])
    smax   = float(sys.argv[18])
if (larg>=24):    
    mmmin  = float(sys.argv[19])
    mmmax  = float(sys.argv[20])
    nnmin  = float(sys.argv[21])
    nnmax  = float(sys.argv[22])
    bbmin  = float(sys.argv[23])
    bbmax  = float(sys.argv[24])
if (larg>=25):
    hdflag = int(sys.argv[25])
    
f = open(filename,'r')
title=f.readline()
title=f.readline()
title=title.split()
f.close()
#time,r,rs,rb,m,ms,mb,n,ns,nb,mm,nn,v,vs,vb,vx,vxs,vxb,vy,vys,vyb,vz,vzs,vzb,vr,vrs,vrb,vt,vts,vtb,s,ss,sb,sx,sxs,sxb,sy,sys,syb,sz,szs,szb,sr,srs,srb,st,sts,stb,vrot,vrots,vrotb,srot,srots,srotb=np.loadtxt(filename,skiprows=2,unpack=True)
data=np.loadtxt(filename,skiprows=2,unpack=False)

gt  =np.array([])
grc =np.array([]) 
grcn=np.array([]) 
grcm=np.array([]) 

if (hdflag):
    gt,grc,grcmtmp,grcn = np.loadtxt('global.30.all',skiprows=1,usecols=(1,8,11,29),unpack=True, comments='#')
    grcm=grcmtmp/rscale*mscale
else :
    gt,grcnb,grcmnb,grcn = np.loadtxt('rcout',usecols=(19,3,5,4),unpack=True)
    grc=grcnb*rscale
    grcm=grcmnb*mscale


# full output
#ntot =18
#nfrac=18
#colors     = ('b', 'g', 'r', 'c', 'm', 'y', 'k', 'b', 'g', 'r', 'c', 'm', 'y', 'k', 'b', 'g', 'r', 'c')
#linestyles = ('_', '_', '_', '_', '_', '_', '_', '-', '-', '-', '-', '-', '-', '-', '--', '--', '--', '--')
#masks=np.array(range(18))+1
# Only mark 7 to make clear plot
ntot=8
nfrac=7
colors         = ('b', 'g', 'r', 'c', 'm', 'y', 'k')
linestyles     = ('-', '-', '-', '-', '-', '-', '-')
#masks = np.array([  1,   4,   7,   9,  11,  13,  15])
masks = np.array([  1,   2,   3,   4,   5,   6,   7])
# Label
tlabel=(r'$R_{lagr}$',r'$R_{lagr,s}$',r'$R_{lagr,b}$',
        r'$\langle M \rangle$',r'$\langle M \rangle_{s}$',r'$\langle M \rangle_{b}$',
        r'$N$',r'$N_s$',r'$N_b$',
        r'$M_{bin}/M$',r'$N_{bin}/N$',
        r'$\langle v \rangle$',r'$\langle v \rangle_{s}$',r'$\langle v \rangle_{b}$',
        r'$\langle v_x \rangle$',r'$\langle v_x \rangle_{s}$',r'$\langle v_x \rangle_{b}$',
        r'$\langle v_y \rangle$',r'$\langle v_y \rangle_{s}$',r'$\langle v_y \rangle_{b}$',
        r'$\langle v_z \rangle$',r'$\langle v_z \rangle_{s}$',r'$\langle v_z \rangle_{b}$',
        r'$\langle v_r \rangle$',r'$\langle v_r \rangle_{s}$',r'$\langle v_r \rangle_{b}$',
        r'$\langle v_t \rangle$',r'$\langle v_t \rangle_{s}$',r'$\langle v_t \rangle_{b}$',
        r'$\langle \sigma \rangle$',r'$\langle \sigma \rangle_{s}$',r'$\langle \sigma \rangle_{b}$',
        r'$\langle \sigma_x \rangle$',r'$\langle \sigma_x \rangle_{s}$',r'$\langle \sigma_x \rangle_{b}$',
        r'$\langle \sigma_y \rangle$',r'$\langle \sigma_y \rangle_{s}$',r'$\langle \sigma_y \rangle_{b}$',
        r'$\langle \sigma_z \rangle$',r'$\langle \sigma_z \rangle_{s}$',r'$\langle \sigma_z \rangle_{b}$',
        r'$\langle \sigma_r \rangle$',r'$\langle \sigma_r \rangle_{s}$',r'$\langle \sigma_r \rangle_{b}$',
        r'$\langle \sigma_t \rangle$',r'$\langle \sigma_t \rangle_{s}$',r'$\langle \sigma_t \rangle_{b}$',
        r'$\langle v_{rot} \rangle$',r'$\langle v_{rot} \rangle_{s}$',r'$\langle v_{rot} \rangle_{b}$',
        r'$\langle \sigma_{rot} \rangle$',r'$\langle \sigma_{rot} \rangle_{s}$',r'$\langle \sigma_{rot} \rangle_{b}$',
        r'$M_{p,bin}/M$',r'$N_{p,bin}/N$',r'$M_{p,bin}/M_{bin}$',r'$N_{p,bin}/N_{bin}$')

fname=('R_lagr','R_lagrs','R_lagrb',
        'M','M_s','M_b',
        'N','N_s','N_b',
        'M_bin_M','N_bin_N',
        'v','v_s','v_b',
        'v_x','v_x_s','v_x_b',
        'v_y','v_y_s','v_y_b',
        'v_z','v_z_s','v_z_b',
        'v_r','v_r_s','v_r_b',
        'v_t','v_t_s','v_t_b',
        's','s_s','s_b',
        's_x','s_x_s','s_x_b',
        's_y','s_y_s','s_y_b',
        's_z','s_z_s','s_z_b',
        's_r','s_r_s','s_r_b',
        's_t','s_t_s','s_t_b',
        'v_rot','v_rot_s','v_rot_b',
        's_rot','s_rot_s','s_rot_b',
        'PM_bin_M','PN_bin_N',
        'PMb_Mb','PNb_Nb')


# direct ouput
for k in np.append(np.append(np.array(range(9)),np.array(range(18))+11),np.array([47,48,49])):
    shift = k*ntot
    fig = plt.figure(figsize=(8,6),dpi=300)
    plt.xlabel('Time[Myr]')
    plt.ylabel(tlabel[k])
    plt.xlim(tmin,tmax)
    if(k<3): plt.ylim(rmin,rmax)
    elif(k<6): plt.ylim(mmin,mmax)
    elif(k<9): plt.ylim(nmin,nmax)
    elif(k>=14)&(k<23)|(k>=47): plt.ylim(vmin,vmax)
    else: plt.ylim(0,vmax)
    for i in range(nfrac):
        plt.plot(data[:,0]*tscale,data[:,masks[i]+shift],linestyles[i],label=title[masks[i]+shift],color=colors[i],markersize=1)
    if ((k<6) & (k>=3)):
        plt.yscale('log')
    else:
        plt.yscale('linear')
    # R_lagr
    if(k==0): plt.plot(gt,grc,'--',label=r'$R_{c}$',color=u'grey',markersize=1)
    if(k==3): plt.plot(gt,grcm/grcn,'--',label=r'$R_{c}$',color=u'grey',markersize=1)
    if(k==6): plt.plot(gt,grcn,'--',label=r'$R_{c}$',color=u'grey',markersize=1)
    plt.legend(framealpha=0.7)
    plt.savefig(fname[k]+outformat)
    plt.close(fig)
    
# Mb/M
for k in np.array([9,53]):
    shift = k*ntot
    fig = plt.figure(figsize=(8,6),dpi=300)
    plt.xlabel('Time[Myr]')
    plt.ylabel(tlabel[k])
    plt.xlim(tmin,tmax)
    plt.ylim(mmmin,mmmax)
    for i in range(nfrac):
        plt.plot(data[:,0]*tscale,data[:,masks[i]+shift]/(data[:,masks[i]+3*ntot]*data[:,masks[i]+6*ntot]),linestyles[i],label=title[masks[i]+shift],color=colors[i],markersize=1)
    plt.legend(framealpha=0.7)
    plt.savefig(fname[k]+outformat)
    plt.close(fig)


# Nb/N
for k in np.array([10,54]):
    shift = k*ntot
    fig = plt.figure(figsize=(8,6),dpi=300)
    plt.xlabel('Time[Myr]')
    plt.ylabel(tlabel[k])
    plt.xlim(tmin,tmax)
    plt.ylim(nnmin,nnmax)
    for i in range(nfrac):
        plt.plot(data[:,0]*tscale,data[:,masks[i]+shift]/data[:,masks[i]+6*ntot],linestyles[i],label=title[masks[i]+shift],color=colors[i],markersize=1)
    plt.legend(framealpha=0.7)
    plt.savefig(fname[k]+outformat)
    plt.close(fig)

# PMb/Mb, PNb/Nb
for k in np.array([53,54]):
    shift = k*ntot
    s2 = (k-44)*ntot
    fig = plt.figure(figsize=(8,6),dpi=300)
    plt.xlabel('Time[Myr]')
    plt.ylabel(tlabel[k+2])
    plt.xlim(tmin,tmax)
    plt.ylim(bbmin,bbmax)
    for i in range(nfrac):
        plt.plot(data[:,0]*tscale,data[:,masks[i]+shift]/data[:,masks[i]+s2],linestyles[i],label=title[masks[i]+shift],color=colors[i],markersize=1)
    plt.legend(framealpha=0.7)
    plt.savefig(fname[k+2]+outformat)
    plt.close(fig)
    
# sqrt output
for k in np.append(np.array(range(18))+29,np.array([50,51,52])):
    shift = k*ntot
    fig = plt.figure(figsize=(8,6),dpi=300)
    #plt.title('')
    plt.xlabel('Time[Myr]')
    plt.ylabel(tlabel[k])
    plt.xlim(tmin,tmax)
    plt.ylim(smin,smax)
    for i in range(nfrac):
        plt.plot(data[:,0]*tscale,map(math.sqrt,data[:,masks[i]+shift]),linestyles[i],label=title[masks[i]+shift],color=colors[i],markersize=1)
    plt.legend(framealpha=0.7)
    plt.savefig(fname[k]+outformat)
    plt.close(fig)
    
