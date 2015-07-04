import numpy as np

import sys
flist='sbp.lst'
fout='sbp_ave'
filter='V'
msun=4.83

narg=len(sys.argv)
if (narg>=2):
    flist=sys.argv[1]
    if (flist == '-h'):
        print 'arguments: datalist[sbp.lst] dataout[sbp_ave] filter[V]'
        quit()
if (narg>=3):
    fout=sys.argv[2]
if (narg>=4):
    filter=sys.argv[3]

if (filter=='I'):
    msun=4.08
if (filter=='B'):
    msun=5.48

fl = open(flist,'r')
path = fl.read()
path = path.splitlines()

rpc=np.array([])
sbl=np.array([])
ra=np.array([])
nc=np.array([])
m=np.array([])

icc=0

for i in path:
    rshell, rden, rarc, ncount, rm=np.loadtxt(i,unpack=True,usecols=(0,1,2,4,5),skiprows=1)
    if(icc==0):
        rpc=rshell
        sbl=np.array([rden])
        ra=rarc
        nc=np.array([ncount])
        m=np.array([rm])
    else:
        if (rpc!=rshell).all():
            print 'Warning! rshell not equal'
        sbl=np.append(sbl,[rden],axis=0)
        nc=np.append(nc,[ncount],axis=0)
        m=np.append(m,[rm],axis=0)
    icc +=1
sbave=sbl.mean(axis=0)
sbstd=sbl.std(axis=0)
sbmid=np.median(sbl,axis=0)
ncave=nc.mean(axis=0)
ncstd=nc.std(axis=0)
ncmid=np.median(nc,axis=0)
mave=m.mean(axis=0)
mstd=m.std(axis=0)
mmid=np.median(m,axis=0)

sbmave=msun+21.572-2.5*np.log10(sbave)
sbmmid=msun+21.572-2.5*np.log10(sbmid)
sbmlow=msun+21.572-2.5*np.log10(sbave-sbstd)
sbmup=msun+21.572-2.5*np.log10(sbave+sbstd)

fhandle=open(fout,'w')
np.savetxt(fhandle,
           np.transpose((rpc,sbave,sbmid,sbstd,ra,sbmave,sbmmid,sbmlow,sbmup,ncave,ncmid,ncstd,mave,mmid,mstd)),
           fmt="%f %f %f %f %f %f %f %f %f %d %d %d %f %f %f",
           header="r[pc] surface_brightness[L_{sun}/pc^2](average) surface_brightness[L_{sun}/pc^2](median) std[L_{sun}/pc^2] r[arcsec] surface_brigtness[mag/arcsec^2](average) surface_brigtness[mag/arcsec^2](median) low[mag/arcsec^2] up[mag/arcsec^2] surface_number_density[1/pc^2](average) surface_number_density[1/pc^2](median) std[1/pc^2] surface_mass_density[M_sun/pc^2](average) surface_mass_density[M_sun/pc^2](median) std[M_sun/pc^2]", 
           comments='')
