import numpy as np

import sys
flist='sbp.lst'
fout='sbcore'
tscale=1.0

narg=len(sys.argv)
if (narg>=2):
    flist=sys.argv[1]
    if (flist == '-h'):
        print 'arguments: datalist[sbp.lst] Tscale[1.0]'
        quit()
if (narg>=3):
    tscale=float(sys.argv[2])

fl = open(flist,'r')
path = fl.read()
path = path.splitlines()

t=np.array([])
rc=np.array([])
rcm=np.array([])

for i in path:
    time=float(i[5:-5])*tscale
    t=np.append(t,time)
    rshell, rden, rm =np.loadtxt(i,unpack=True,usecols=(0,1,5),skiprows=1)
    for j in range(rden.size):
        if (rden[j]<0.5*rden[0]):
            a=rden[j-1]/rden[0]
            b=rden[j]/rden[0]
            rcj=((0.5-b)*rshell[j-1]+(a-0.5)*rshell[j])/(a-b)
            rc=np.append(rc,rcj)
            break
    for j in range(rm.size):
        if (rm[j]<0.5*rm[0]):
            a=rm[j-1]/rm[0]
            b=rm[j]/rm[0]
            rcj=((0.5-b)*rshell[j-1]+(a-0.5)*rshell[j])/(a-b)
            rcm=np.append(rcm,rcj)
            break
    

print "%f %f %f %f %f %f %f" % (t.mean(),rc.mean(),np.median(rc),rc.std(),rcm.mean(),np.median(rcm),rcm.std())
