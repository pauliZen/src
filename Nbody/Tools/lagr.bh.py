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
    k = np.array(s['KW'])
    mass = np.array(s['M'])
    n = np.array(s['NAM'])
    x1 = np.array(s['X1'])
    x2 = np.array(s['X2'])
    x3 = np.array(s['X3'])

    tsmass = mass.sum()
    bsmass = mass[k==14].sum()

    time = float(s.attrs['Time'])

    N_SINGLE = s.attrs['N_SINGLE']

    bflag = 'Binaries' in map(lambda x:x[0], s.items())
    mflag = 'Mergers' in map(lambda x:x[0], s.items())

    tbmass = 0.0
    bbmass = 0.0
    tmmass = 0.0
    bmmass = 0.0

    b = 0
    m = 0

    N_BINARY = 0
    N_MERGER = 0

    bm1 = 0
    bm2 = 0
    mm1 = 0
    mm2 = 0
    mm3 = 0
    bxc1 = 0
    bxc2 = 0
    bxc3 = 0
    mxc1 = 0
    mxc2 = 0
    mxc3 = 0
    bk1 = 0
    bk2 = 0
    mk1 = 0
    mk2 = 0
    mk3 = 0

    if (bflag) :
        b = s['Binaries']
        N_BINARY = b.attrs['N_BINARY']
        if (N_BINARY > 0):
            bk1 = np.array(b['KW1'])
            bk2 = np.array(b['KW2'])
            bxc1 = np.array(b['XC1'])
            bxc2 = np.array(b['XC2'])
            bxc3 = np.array(b['XC3'])
            bm1 = np.array(b['M1'])
            bm2= np.array(b['M2'])
     
            tbmass = bm1.sum() + bm2.sum()
            bbmass = bm1[bk1==14].sum() + bm2[bk2==14].sum()
        else:
            bflag = False

    if (mflag) :
        m = s['Mergers']
        N_MERGER = m.attrs['N_MERGER']
        if (N_MERGER > 0):
            mk1 = np.array(m['KW1'])
            mk2 = np.array(m['KW2'])
            mk3 = np.array(m['KW3'])
            mm1 = np.array(m['M1'])
            mm2 = np.array(m['M2'])
            mm3 = np.array(m['M3'])
            mxc1 = np.array(m['XC1'])
            mxc2 = np.array(m['XC2'])
            mxc3 = np.array(m['XC3'])
     
            tmmass = mm1.sum() + mm2.sum() + mm3.sum()
            bmmass = mm1[mk1==14].sum() + mm2[mk2==14].sum() + mm3[mk3==14].sum()
        else:
            mflag = False

    tmass = tsmass + tbmass + tmmass
    bmass = bsmass + bbmass + bmmass
    smass = tmass - bmass
    rmass = tmass*rfrac
#    rsmass = tsmass*rfrac
#    rbmass = tbmass*rfrac
    rstarm = smass*rfrac
    rbhm = bmass*rfrac

    r2 = x1*x1 + x2*x2 + x3*x3
    if (bflag) : 
        rb2 = bxc1*bxc1 + bxc2*bxc2 + bxc3*bxc3
        r2 = np.append(r2,rb2)
    
    if (mflag) :
        rm2 = mxc1*mxc1 + mxc2*mxc2 + mxc3*mxc3
        r2 = np.append(r2,rm2)

    idx = r2.argsort()

    kk = 0
    kks = 0
    kkb = 0
    nc = 0
    ncs = 0
    ncb = 0
    cmass = 0
    csmass = 0
    cbmass = 0

    kl = 0
    kls = 0
    klb = 0
    nl = 0
    nls = 0
    nlb = 0

    N_SB = N_SINGLE + N_BINARY

    for j in idx:
        if (j>=N_SB):
            nc += 3
            inx = j - N_SB
            mmb = 0.0
            mms = 0.0
#            print mk1,inx, N_SB, j, N_SINGLE, N_BINARY, N_MERGER, mflag
            if (mk1[inx]==14): 
                mmb = mmb + mm1[inx]
                ncb += 1
            else:
                mms = mms + mm1[inx]
                ncs += 1
            if (mk2[inx]==14): 
                mmb = mmb + mm2[inx]
                ncb += 1
            else :
                mms = mms + mm2[inx]
                ncs += 1
            if (mk3[inx]==14):
                mmb = mmb + mm3[inx]
                ncb += 1
            else :
                mms = mms + mm3[inx]
                ncs += 1
            cmass += mm1[inx] + mm2[inx] + mm3[inx]
            csmass += mms
            cbmass += mmb
            if (mmb > 0):
                klb = j
                nlb = ncb
            if (mms > 0):
                kls = j
                nls = ncs
            kl = j
            nl = nc
        else:
            if (j>=N_SINGLE):
                nc += 2
                inx = j - N_SINGLE
                cmass += bm1[inx] + bm2[inx]
                bmb = 0.0
                bms = 0.0
                if (bk1[inx]==14): 
                    bmb += bm1[inx]
                    ncb += 1
                else:
                    bms += bm1[inx]
                    ncs += 1
                if (bk2[inx]==14): 
                    bmb += bm2[inx]
                    ncb += 1
                else:
                    bms += bm2[inx]
                    ncs += 1
                csmass += bms
                cbmass += bmb
                if (bmb > 0):
                    klb = j
                    nlb = ncb
                if (bms > 0):
                    kls = j
                    nls = ncs
                kl = j
                nl = nc
            else:
                nc += 1
                cmass += mass[j]
                if (k[j]==14): 
                    cbmass += mass[j]
                    ncb += 1
                    klb = j
                    nlb = ncb
                else:
                    csmass += mass[j]
                    ncs += 1
                    kls = j
                    nls = ncs
                kl = j
                nl = nc

        if (csmass >= rstarm[kks]):
            rslagr[kks] = math.sqrt(r2[j])
            nslagr[kks] = ncs
            kks += 1
            kks = min(kks,rfrac.size-1)
        if (cbmass >= rbhm[kkb]):
            rblagr[kkb] = math.sqrt(r2[j])
            nblagr[kkb] = ncb
            kkb += 1
            kkb = min(kkb,rfrac.size-1)
        if (cmass >= rmass[kk]):
            rlagr[kk] = math.sqrt(r2[j])
            nlagr[kk] = nc
            kk += 1
            kk = min(kk,rfrac.size-1)
    kn = kk - 1
    while (kk < rfrac.size):
        rlagr[kk] = rlagr[kn]
        nlagr[kk] = nlagr[kn]
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
    mslagr=rstarm/nslagr
    if(nblagr[nblagr.size-1]>0): 
        mblagr=rbhm/nblagr
    
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
    print " " 

#    fw.write(str(rlagr)+str(rslagr)+str(rblagr)+str(mlagr)+str(mslagr)+str(mblagr)+str(nlagr)+str(nslagr)+str(nblagr))
#fw.close()

