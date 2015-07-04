## velocity dispersion


import numpy as np
import sys

flist='dlst'
filter='V'
mmax=24
rmin=0.01
rmax=100.0
nbin=50
nlim=50

larg=len(sys.argv)-1
if (larg>=1):
    flist = sys.argv[1]
    if (flist=='-h'):
        print 'arguments: projected_data_list[dlst] magnitude_cut[24] bin_number[50] rmin[0.01] rmax[100.0] number_min_per_bin[100] filter[V]'
        quit()
if (larg>=2):
    mmax=float(sys.argv[2])
if (larg>=3):
    nbin=int(sys.argv[3])
if (larg>=4):
    rmin=float(sys.argv[4])
if (larg>=5):
    rmax=float(sys.argv[5])
if (larg>=6):
    nlim=int(sys.argv[6])
if (larg>=7):
    filter = sys.argv[7]


msun=4.83
mcol=18

if filter=='B':
    msun=5.48
    mcol=20

if filter=='I':
    msun=4.08
    mcol=21
    
f = open(flist,'r')
files=f.readlines()

for i in files:
    filename=i.split()
    x,y,vx,vy,vz,m1,m2,m=np.loadtxt(filename[0],usecols=(1,2,4,5,6,9,10,mcol-1),unpack=True)

    # luminosity cut
    select=(m<mmax)
    xs=x[select]
    ys=y[select]

    rs=np.sqrt(xs*xs+ys*ys)
    ls=10.0**(0.4*(msun-m[select]))
    mass=m1[select]+m2[select]
    vzs=vz[select]

    # sorting distance
    #index=rs.argsort()
    #rss=rs[index]
    #lss=ls[index]
    #vzss=vzs[index]

    lmin=np.log10(rmin)
    scale=float(nbin)/(np.log10(rmax)-lmin)
    rshell=10.0**(np.array(range(1,nbin+1))/scale+lmin)
#    nlr=(0.5*np.log10(x)-lmin)*scale
    
    vzavel=np.zeros(nbin)
    vzavem=np.zeros(nbin)
    vzave=np.zeros(nbin)
    szl=np.zeros(nbin)
    szm=np.zeros(nbin)
    sz=np.zeros(nbin)
    ravel=np.zeros(nbin)
    ravem=np.zeros(nbin)
    rave=np.zeros(nbin)
    ncount=np.zeros(nbin)
    

    lowlim = True
    uplim = True
    k=0
    i=0
    while i<nbin:
        ncount[k]=0
        select=True
        ri=np.array([])
        while (ncount[k]<nlim) & (i<nbin):
            uplim=(rs<=rshell[i])
            select = (lowlim & uplim)
            ri=rs[select]
            ncount[k]=ri.size
            i +=1
        if (ncount[k]<nlim): break
        lowlim=(rs>rshell[i-1])
        li=ls[select]
        massi=mass[select]
        vzi=vzs[select]
        # luminosity weight
        ravel[k]=np.average(ri,weights=li)
        vzavel[k]=np.average(vzi,weights=li)
        szl[k]=np.sqrt(np.average((vzi-vzavel[k])**2,weights=li))
        # mass weight
        ravem[k]=np.average(ri,weights=massi)
        vzavem[k]=np.average(vzi,weights=massi)
        szm[k]=np.sqrt(np.average((vzi-vzavem[k])**2,weights=massi))
        # no weight
        rave[k]=np.average(ri)
        vz[k]=np.average(vzi)
        sz[k]=np.std(vzi)

        k +=1

    print 'File ',filename[0],' Time ',filename[1],' Number ',rs.size, ' Nbins ',k
    fout='vdf_%s_m%.1f_%s' % (filter,mmax,filename[1])
    fhandle=open(fout,'w')
    np.savetxt(fhandle,np.transpose((ravel[0:k],vzavel[0:k],szl[0:k],ravem[0:k],vzavem[0:k],szm[0:k],rave[0:k],vzave[0:k],sz[0:k],ncount[0:k])),fmt="%e %e %e %e %e %e %e %e %e %d",header="<r>[pc](lum) <v>[km/s](lum) <sigma>[km/s](lum) <r>[pc](mass) <v>[km/s](mass) <sigma>[km/s](mass) <r>[pc] <v>[km/s] <sigma>[km/s] N",comments='')
    fhandle.close()
    
