import numpy as np
import matplotlib.pyplot as plt
import h5py
import math
import ctypes
import sys
from ctypes import *

def sdot(x1,x2,x3):
    return math.sqrt(x1*x1+x2*x2+x3*x3)

fl = open('snap.lst','r')
path = fl.read()
path = path.splitlines()

for i in path:
    f = h5py.File(i,'r')
    tots = len(f.items())

    kj = 0
    while (kj<tots):

        s = f.items()[kj][1]

        kj += 1

        time = float(s.attrs['Time'])
     
        print 'snapshot: time = ',time
        sys.stdout.flush()

        kw = np.array(s['KW'])
        mass = np.array(s['M'])
        n = np.array(s['NAM'])
        x1 = np.array(s['X1'])
        x2 = np.array(s['X2'])
        x3 = np.array(s['X3'])
     
#        tsmass = mass.sum()
#        bsmass = mass[k==14].sum()
     
        N_SINGLE = s.attrs['N_SINGLE']
     
        bflag = 'Binaries' in map(lambda x:x[0], s.items())
        mflag = 'Mergers' in map(lambda x:x[0], s.items())
     
#        tbmass = 0.0
#        bbmass = 0.0
#        tmmass = 0.0
#        bmmass = 0.0
     
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
                bn1 = np.array(b['NAM1'])
                bn2 = np.array(b['NAM2'])
                bnc = np.array(b['NAMC'])
                bxc1 = np.array(b['XC1'])
                bxc2 = np.array(b['XC2'])
                bxc3 = np.array(b['XC3'])
                bm1 = np.array(b['M1'])
                bm2 = np.array(b['M2'])
                bxr1   = np.array(b['XR1'])
                bxr2   = np.array(b['XR2'])
                bxr3   = np.array(b['XR3']) 
                ba = np.array(b['A'])
                be = np.array(b['ECC'])
                bp = np.array(b['P'])
 #               tbmass = bm1.sum() + bm2.sum()
#                bbmass = bm1[bk1==14].sum() + bm2[bk2==14].sum()
            else:
                bflag = False
     
        if (mflag) :
            m = s['Mergers']
            N_MERGER = m.attrs['N_MERGER']
            if (N_MERGER > 0):
                mk1 = np.array(m['KW1'])
                mk2 = np.array(m['KW2'])
                mk3 = np.array(m['KW3'])
                mn1 = np.array(m['NAM1'])
                mn2 = np.array(m['NAM2'])
                mn3 = np.array(m['NAM3'])
                mnc = np.array(m['NAMC'])
                mm1 = np.array(m['M1'])
                mm2 = np.array(m['M2'])
                mm3 = np.array(m['M3'])
                mxc1 = np.array(m['XC1'])
                mxc2 = np.array(m['XC2'])
                mxc3 = np.array(m['XC3'])
                mxro1 = np.array(m['XR11'])
                mxro2 = np.array(m['XR12'])
                mxro3 = np.array(m['XR13'])
                mxri1 = np.array(m['XR01'])
                mxri2 = np.array(m['XR02'])
                mxri3 = np.array(m['XR03'])
                meo = np.array(m['ECC1'])
                mei = np.array(m['ECC0'])
                mao = np.array(m['A1'])
                mai = np.array(m['A0'])
                mpo = np.array(m['P1'])
                mpi = np.array(m['P0'])
         
#                tmmass = mm1.sum() + mm2.sum() + mm3.sum()
#                bmmass = mm1[mk1==14].sum() + mm2[mk2==14].sum() + mm3[mk3==14].sum()
            else:
                mflag = False
                
        title = '.%.8f' % time
        phif = open('pot_data'+title,'r')
        nn = phif.readline()
        nn = nn.split()

        nc = int(nn[1])
        ncs = int(nn[2])
        ncsb = int(nn[3])
        
        print 'NC NCS NCSB', nc, ncs, ncsb

        inxi,phi = np.loadtxt('pot_data'+title,usecols=(0,1),unpack=True,comments='#')

        k=0
        minphi = 0
        ikm = 0
        inxm = 0
        xm1 = 0
        xm2 = 0
        xm3 = 0
        while (k<nc):
            if (minphi<phi[k]):
                minphi = phi[k]
                inxm = inxi[k]
                ikm = k
            k +=1
        print 'Minphi %f k %d inx %d' % (minphi,ikm,inxm)
        if (ikm<ncs):
            xm1 = x1[inxm]
            xm2 = x2[inxm]
            xm3 = x3[inxm]
        else:
            if (ikm<ncsb):
                ik = inxm - N_SINGLE
                xm1 = bxc1[ik]
                xm2 = bxc2[ik]
                xm3 = bxc3[ik]
            else:
                ik = inxm - N_SINGLE - N_BINARY
                xm1 = mxc1[ik]
                xm2 = mxc2[ik]
                xm3 = mxc3[ik]

        xr = np.zeros(nc)
        k=0
        while (k<ncs):
            ik = inxi[k]
            xr[k] = sdot(x1[ik]-xm1,x2[ik]-xm2,x3[ik]-xm3)
            k += 1
        while (k<ncsb):
            ik = inxi[k] - N_SINGLE
            xr[k] = sdot(bxc1[ik]-xm1,bxc2[ik]-xm2,bxc3[ik]-xm3)
            k += 1
        while (k<nc):
            ik = inxi[k] - N_SINGLE - N_BINARY
            xr[k] = sdot(mxc1[ik]-xm1,mxc2[ik]-xm2,mxc3[ik]-xm3)
            k += 1

        # distance referred to potential center sorted array index
        idx = xr.argsort()

        print 'Write to pots',title
        sout = open('pots'+title,'w')
        k=0
        ks = 0
        kb = 0
        # name, kw(-1:binary; -2:merger), m, x1, x2, x3, pot, r, order
        while (k<nc):
            isk = idx[k]
            if(isk<ncs):
                ik = inxi[isk]
                if (kw[ik]==14):
                    kb += 1
                    kk = kb
                else:
                    ks -= 1
                    kk = ks
                sout.write("%d %d %.8e %.8e %.8e %.8e %.8e %.8e %d\n" % (n[ik], kw[ik], mass[ik], x1[ik], x2[ik], x3[ik], phi[isk], xr[isk],kk))
            else:
                if(isk<ncsb):
                    ik = inxi[isk]-N_SINGLE
                    label = -1
                    if (bk1[ik]==14) | (bk2[ik]==14): 
                        label = -10
                    if (bk1[ik]==14) & (bk2[ik]==14):
                        label = -11
                    if (label == -1):
                        ks -= 1
                        kk = ks
                    else:
                        kb += 1
                        kk = kb
                    sout.write("%d %d %.8e %.8e %.8e %.8e %.8e %.8e %d\n" % (bn1[ik]+bn2[ik], label, bm1[ik]+bm2[ik], bxc1[ik], bxc2[ik], bxc3[ik], phi[isk], xr[isk],kk))
                else:
                    ik = inxi[isk]-N_SINGLE-N_BINARY
                    label = -2
                    if (mk1[ik]==14) | (mk2[ik]==14) | (mk3[ik]==14): 
                        label = -100
                    if ((mk1[ik]==14) & (mk2[ik]==14) | (mk1[ik]==14) & (mk3[ik]==14) | (mk3[ik]==14) & (mk2[ik]==14)):
                        label = -110
                    if (mk1[ik]==14) & (mk2[ik]==14) & (mk3[ik]==14):
                        label = -111
                    if (label == -2):
                        ks -= 1
                        kk = ks
                    else:
                        kb += 1
                        kk = kb
                    sout.write("%d %d %.8e %.8e %.8e %.8e %.8e %.8e %d\n" % (mn1[ik]+mn2[ik]+mn3[ik], label, mm1[ik]+mm2[ik]+mm3[ik], mxc1[ik], mxc2[ik], mxc3[ik], phi[isk], xr[isk],kk))
            k += 1
        sout.close()

#        print 'Write to pots',title
#        sout = open('pots'+title,'w')
#        k=0
#        while (k<ncs):
#            ik = inxi[k]
#            # name, kw(-1:binary; -2:merger), m, x1, x2, x3, pot
#            sout.write("%d %d %.8e %.8e %.8e %.8e %.8e\n" % (n[ik], kw[ik], mass[ik], x1[ik], x2[ik], x3[ik], phi[k]))
#            k += 1
#        while (k<ncsb):
#            ik = inxi[k]-N_SINGLE
#            # name, kw(-1:binary; -2:merger), m, x1, x2, x3, phi
#            label = -1
#            if (bk1[ik]==14) | (bk2[ik]==14): 
#                label = -10
#            if (bk1[ik]==14) & (bk2[ik]==14):
#                label = -11
#            sout.write("%d %d %.8e %.8e %.8e %.8e %.8e\n" % (bnc[ik], label, bm1[ik]+bm2[ik], bxc1[ik], bxc2[ik], bxc3[ik], phi[k]))
#            k += 1
#        while (k<nc):
#            ik = inxi[k]-N_SINGLE-N_BINARY
#            label = -2
#            if (mk1[ik]==14) | (mk2[ik]==14) | (mk3[ik]==14): 
#                label = -100
#            if ((mk1[ik]==14) & (mk2[ik]==14) | (mk1[ik]==14) & (mk3[ik]==14) | (mk3[ik]==14) & (mk2[ik]==14)):
#                label = -110
#            if (mk1[ik]==14) & (mk2[ik]==14) & (mk3[ik]==14):
#                label = -111
#            # name, kw(-1:binary; -2:merger), m, x1, x2, x3, phi
#            sout.write("%d %d %.8e %.8e %.8e %.8e %.8e\n" % (mnc[ik], label, mm1[ik]+mm2[ik]+mm3[ik], mxc1[ik], mxc2[ik], mxc3[ik], phi[k]))
#            k += 1
#        sout.close()
         
        if(bflag & (ncsb-ncs>0)):
            print 'Write to potb',title
            bout = open('potb'+title,'w')
            k=0
            while (k<ncsb-ncs):
                # n1,n2,k1,k2,m1,m2,xc1,xc2,xc3,xr1,xr2,xr3,a,e,p,pot
                ib=inxi[ncs+k] - N_SINGLE
                bout.write("%d %d %d %d %.8e %.8e  %.8e %.8e %.8e  %.8e %.8e %.8e  %.8e %.8e %.8e %.8e\n" % (bn1[ib], bn2[ib], bk1[ib], bk2[ib], bm1[ib], bm2[ib], bxc1[ib], bxc2[ib], bxc3[ib], bxr1[ib], bxr2[ib], bxr3[ib], ba[ib], be[ib], bp[ib], phi[ncs+k]))
                k += 1
            bout.close()

        if(mflag & (nc-ncsb>0)):
            print 'Write to potm',title
            mout = open('potm'+title,'w')
            k=0
            while (k<nc-ncsb):
                # n1,n2,n3,k1,k2,k3,m1,m2,m3,xc1,xc2,xc3,xro1,xro2,xro3,xri1,xri2,xri3,ao,ai,eo,ei,po,pi,phi
                im=inxi[ncsb+k] - N_SINGLE - N_BINARY
                mout.write("%d %d %d %d %d %d %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e\n" % (mn1[im], mn2[im], mn3[im], mk1[im], mk2[im], mk3[im], mm1[im], mm2[im], mm3[im], mxc1[im], mxc2[im], mxc3[im], mxro1[im], mxro2[im], mxro3[im], mxri1[im], mxri2[im], mxri3[im], mao[im], mai[im], meo[im], mei[im], mpo[im], mpi[im], phi[ncsb+k]))
                k += 1
         
            mout.close()
        
