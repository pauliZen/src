import numpy as np
import matplotlib.pyplot as plt
import h5py
import math
from matplotlib.colors import BoundaryNorm
from matplotlib.ticker import MaxNLocator

fl = open('snap.lst','r')
path = fl.read()
path = path.splitlines()

rfrac=np.array([0.001,0.003,0.005,0.01,0.03,0.05,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.95,0.99,1.0])
rlagr=np.zeros(rfrac.size)
rslagr=np.zeros(rfrac.size)
rblagr=np.zeros(rfrac.size)
nlagr=np.zeros(rfrac.size)
nslagr=np.zeros(rfrac.size)
nblagr=np.zeros(rfrac.size)
mlagr=np.zeros(rfrac.size)
mslagr=np.zeros(rfrac.size)
mblagr=np.zeros(rfrac.size)
#vlagr=np.zeros(vlagr.size)

#fw = open('lagr.snap','a')

print "Time[NB] ",
for i in range(9):
    for j in range(rfrac.size): 
        print "%.8e " % rfrac[j],
print " "

for i in path:
    f = h5py.File(i,'r')
    s = f['/Step#7']
    b = s['Binaries']
#    m = s['Mergers']
    t = np.array(s['TE'])
    l = np.array(s['L'])
    k = np.array(s['KW'])
    mass = np.array(s['M'])
    n = np.array(s['NAM'])
    x1 = np.array(s['X1'])
    x2 = np.array(s['X2'])
    x3 = np.array(s['X3'])
    bxc1 = np.array(b['XC1'])
    bxc2 = np.array(b['XC2'])
    bxc3 = np.array(b['XC3'])
    ba = np.array(b['A'])
    be = np.array(b['ECC'])
    bp = np.array(b['P'])
    bm1 = np.array(b['M1'])
    bm2= np.array(b['M2'])
#    mm1 = np.array(m['M1'])
#    mm2 = np.array(m['M2'])
#    mm3 = np.array(m['M3'])
#    mxc1 = np.array(m['XC1'])
#    mxc2 = np.array(m['XC2'])
#    mxc3 = np.array(m['XC3'])
    
    tsmass = float(mass.sum())
    tbmass = float(bm1.sum() + bm2.sum())
# + mm1.sum() + mm2.sum() + mm3.sum()
    tmass = tsmass + tbmass
    rmass = tmass*rfrac
    rsmass = tsmass*rfrac
    rbmass = tbmass*rfrac
    
    rs2 = x1*x1 + x2*x2 + x3*x3
    rb2 = bxc1*bxc1 + bxc2*bxc2 + bxc3*bxc3
#    rm2 = mxc1*mxc1 + mxc2*mxc2 + mxc3*mxc3
    r2 = np.append(rs2,rb2)
#    r2 = np.append(ri2,rm2)
    idx = r2.argsort()

    msblagr=np.zeros(rfrac.size)
    nsblagr=np.zeros(rfrac.size)

    kk = 0
    kks = 0
    kkb = 0
    nc = 0
    ncs = 0
    ncb = 0
    cmass = 0
    bmass = 0
    smass = 0
    time = float(s.attrs['Time'])
    N_SINGLE = s.attrs['N_SINGLE']
    N_BINARY = b.attrs['N_BINARY']
#    print time, N_SINGLE,N_BINARY
#    N_MERGER = m.attrs['N_MERGER']
    N_SB = N_SINGLE + N_BINARY
    for j in idx:
        nc += 1
        if (j>=N_SINGLE):
            nc += 1
            ncb += 2
#            if (j>=N_SB):
#                inx = j - N_SB
#                mmb = mm1[inx]+mm2[inx]+mm3[inx]
#                bmass += mmb
#                cmass += mmb
#            else:
            inx = j - N_SINGLE
            mmb = bm1[inx]+bm2[inx]
#            btt=bxc1[inx]*bxc1[inx] + bxc2[inx]*bxc2[inx]+ bxc3[inx]*bxc3[inx]
#            if (btt == r2[j]): 
#                print "Inconsistence: inx=%d, j=%d, r2=%e, r2s=%e, " % (inx,j,btt,r2[j])
            bmass += mmb
            msblagr[kks] += mmb
            nsblagr[kks] += 1
            if (bmass >= rbmass[kkb]):
                rblagr[kkb] = math.sqrt(r2[j])
                nblagr[kkb] = ncb
                kkb += 1
#                if(kkb > rfrac.size - 1): print j , ncb, N_BINARY, bmass, tbmass, rbmass[rfrac.size-1],time
                kkb = min(kkb,rfrac.size-1)
            cmass += mmb
        else:
            ncs += 1
            smass += mass[j]
            if (smass >= rsmass[kks]):
                rslagr[kks] = math.sqrt(r2[j])
                nslagr[kks] = ncs
                kks += 1
                kks = min(kks,rfrac.size-1)
            cmass += mass[j]
        if (cmass >= rmass[kk]):
            rlagr[kk] = math.sqrt(r2[j])
            nlagr[kk] = nc
            kk += 1
            if (kk < rfrac.size-1 ):
                if (nsblagr[kk+1] == 0):
                    msblagr[kk+1] = msblagr[kk]
                    nsblagr[kk+1] = nsblagr[kk]
            kk = min(kk,rfrac.size-1)
    kn = kk - 1
    while (kk < rfrac.size):
        rlagr[kk] = rlagr[kn]
        nlagr[kk] = nlagr[kn]
        nsblagr[kk] = nsblagr[kn]
        msblagr[kk] = msblagr[kn]
        kk += 1
    ksn = kks - 1
    while (kks < rfrac.size):
        rslagr[kks] = rslagr[ksn]
        nslagr[kks] = nslagr[ksn]
        kks += 1
    kbn = kkb - 1
    while (kkb < rfrac.size):
        rblagr[kkb] = rblagr[kbn]
        nblagr[kkb] = nblagr[kbn]
        kkb += 1

    mlagr=rmass/nlagr
    mslagr=rsmass/nslagr
    mblagr=rbmass/nblagr
    
    f.close()
    
    print "%.8e " % time,
    for j in range(rfrac.size): 
        print "%.8e " % rlagr[j],
    for j in range(rfrac.size): 
        print "%.8e " % rslagr[j],
    for j in range(rfrac.size): 
        print "%.8e " % rblagr[j],
    for j in range(rfrac.size): 
        print "%.8e " % mlagr[j],
    for j in range(rfrac.size): 
        print "%.8e " % mslagr[j],
    for j in range(rfrac.size): 
        print "%.8e " % mblagr[j],
    for j in range(rfrac.size): 
        print "%d " % nlagr[j],
    for j in range(rfrac.size): 
        print "%d " % nslagr[j],
    for j in range(rfrac.size): 
        print "%d " % nblagr[j],
    for j in range(rfrac.size): 
        print "%.8e " % msblagr[j],
    for j in range(rfrac.size): 
        print "%d " % nsblagr[j],
    print " " 

#    fw.write(str(rlagr)+str(rslagr)+str(rblagr)+str(mlagr)+str(mslagr)+str(mblagr)+str(nlagr)+str(nslagr)+str(nblagr))
#fw.close()

