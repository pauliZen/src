## projected cumulative luminosity function of different types of stars
## need projected data 

import numpy as np
import scipy.spatial as sp

import matplotlib
import matplotlib.pyplot as plt

import sys

flist='dlist'
dout='cuml.eps'
filter='V'

# KDTree method to find half value index
def find_half_index(a):
    tree=sp.cKDTree(np.vstack(a))
    dis,index=tree.query([a[-1]/2.0])
    return index

larg=len(sys.argv)-1
if (larg>=1):
    flist = sys.argv[1]
    if (flist=='-h'):
        print 'arguments: projected_data_list[flist] filter[V]'
        quit()
if (larg>=2):
    filter = sys.argv[2]

# filter V
msun=4.83
ml1=22
ml2=26

if filter=='B':
    msun=5.48
    ml1=24
    ml2=28
    
if filter=='I':
    msun=4.08
    ml1=25
    ml2=29

f = open(flist,'r')
files=f.readlines()

def cum_table(t1,t2,r,b,k1,k2,l1,l2):
    select1=True
    select2=True
    if (t1==t2):
        select1 = (k1==t1)
        select2 = ((b==1) & (k2==t1))
    else:
        select1 = ((k1>=t1) & (k1<=t2))
        select2 = ((b==1) & (k2>=t1) & (k2<=t2))
    rr=np.append(r[select1],r[select2])
    ll=np.append(l1[select1],l2[select2])
    rtmp=np.array([])
    ltmp=np.array([])
    if (rr.size>0):
        index=rr.argsort()
        rtmp=rr[index]
        ltmp=ll[index].cumsum()
    return rtmp,ltmp

type=(r'MS($<0.7 M_{\odot}$)',r'MS($\geq0.7 M_{\odot}$)','HG','RG','CHB','AGB','WD','NS','BH')
kwl=(0,1,2,3,4,5,10,13,14)
kwh=(0,1,2,3,4,6,12,13,14)
colors=('#1569C7', '#0000FF', '#00FFFF', '#FF0000','#FF00FF', '#A52A2A', '#FFFF00','#808080','k')

#header
print 'Time[Myr] LV_{LMS} N_{LMS} LV_{HMS} N_{HMS} LV_{HG} N_{HG} LV_{RG} N_{RG} LV_{CHB} N_{CHB} LV_{AGB} N_{AGB} LV_{WD} N_{WD} LV_{NS} N_{NS} LV_{BH} N_{BH} LV_{Bin} N_{Bin}'

for i in files:
    filename=i.split()
    b,x,y,k1,k2,m1,m2=np.loadtxt(filename[0],usecols=(0,1,2,7,8,ml1-1,ml2-1),unpack=True)
    r=np.sqrt(x*x+y*y)
    l1=10.0**(0.4*(msun-m1))
    l2=10.0**(0.4*(msun-m2))

    print filename[1],

    rc=[]
    lc=[]
    nc=[]
    hc=[]
    for j in range(9):
        rj,lj=cum_table(kwl[j],kwh[j],r,b,k1,k2,l1,l2)
        nj=np.array([])
        hpair=[0,0,0]
        if (rj.size>0):
#            nj=np.linspace(0,1,rj.size)
            nj=np.array(range(1,rj.size+1))
            hj=find_half_index(lj)
            hpair=[rj[hj],lj[hj],nj[hj]]
            print lj[-1],rj.size,rj[hj],
            num=rj.size
            if (num>1E3):
                ncut=int(num/1E3)
                rj=np.append(rj[0:200],rj[200::ncut])
                lj=np.append(lj[0:200],lj[200::ncut])
                nj=np.append(nj[0:200],nj[200::ncut])
        else:
            print 0.0,0,0.0,
        rc.append(rj)
        lc.append(lj)
        nc.append(nj)
        hc.append(hpair)

    rbin=r[b==1]
    lbin=l1[b==1]+l2[b==1]
    index=rbin.argsort()
    rsbin=rbin[index]
    lsbin=lbin[index].cumsum()
    nbin=rsbin.size
#    nsbin=np.linspace(0,1,nbin)
    nsbin=np.array(range(1,nbin+1))
    nbhindex=find_half_index(lsbin)
    hbin=[rsbin[nbhindex],lsbin[nbhindex],nsbin[nbhindex]]
    print lsbin[-1],nbin,rsbin[nbhindex]
    if(nbin>1E3):
        ncut = int(nbin/1E3)
        rsbin=np.append(rsbin[0:200],rsbin[200::ncut])
        lsbin=np.append(lsbin[0:200],lsbin[200::ncut])
        nsbin=np.append(nsbin[0:200],nsbin[200::ncut])

    fig = plt.figure()
    plt.xlabel('r[pc]')
    plt.ylabel('Cumulative luminosity distribution')
    plt.xscale('log')
    plt.yscale('log')
    plt.xlim(0.01,100.0)
    plt.ylim(1e-3,1e7)

    for j in range(7):
        if (rc[j].size>0):
            plt.plot(rc[j],lc[j],label=type[j],color=colors[j])
            plt.plot([hc[j][0]],[hc[j][1]],'.',color=colors[j],markersize=10.0)
    if (rsbin.size>0):
        plt.plot(rsbin,lsbin,label='Binary',color='#808000')
        plt.plot([hbin[0]],[hbin[1]],'.',color='#808000',markersize=10.0)
    plt.legend(framealpha=0.7,loc='upper left')
    plt.savefig(filename[0]+'.cuml.eps')
    plt.close(fig)
    
    fig = plt.figure()
    plt.xlabel('r[pc]')
    plt.ylabel('Cumulative number distribution')
    plt.xscale('log')
    plt.yscale('log')
    plt.xlim(0.01,100.0)
    plt.ylim(1,1e6)
    
    for j in range(9):
        if (rc[j].size>0):
            plt.plot(rc[j],nc[j],label=type[j],color=colors[j])
            plt.plot([hc[j][0]],[hc[j][2]],'.',color=colors[j],markersize=10.0)
    if (rsbin.size>0):
        plt.plot(rsbin,nsbin,label='Binary',color='#808000')
        plt.plot([hbin[0]],[hbin[2]],'.',color='#808000',markersize=10.0)
    plt.legend(framealpha=0.7,loc='upper left')
    plt.savefig(filename[0]+'.cumn.eps')
    plt.close(fig)


