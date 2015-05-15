import numpy as np
import sys
import h5py
import math


filename = 'snap.lst'
# Time interval for calculation (in NB unit)
Tint  = 1.0
# resolution of time interval in NB unit
Tres  = 0.125

fl = open(filename,'r')
path = fl.read()
path = path.splitlines()

toffset = 0.0
ifirst=True
linec=0

for i in path:
    f = 0
    f = h5py.File(i,'r')
    tots = len(f.items())

    kj = 0
    while (kj<tots):
        s = 0
        s = f.items()[kj][1]
        time = float(s.attrs['Time'])
        if (ifirst):
            if (time>0.0):
                toffset=Tint*(int((time-Tres/2.0)/Tint)+1)
            else:
                print "## Time; 100 groups of data; offset %d " % rfrac.size
                print "Time[NB] ",
                for i in range(55):
                    for j in range(rfrac.size): 
                        print "%.2e " % rfrac[j],
                print " "
            ifirst=False

        kj += 1

        if (time-toffset < Tint*linec-Tres/2.0):
            continue
        else:
            linec += 1

        N_SINGLE = s.attrs['N_SINGLE']

        szeros = np.zeros(N_SINGLE)

        t = np.array(s['TE'])
        l = np.array(s['L'])
        k = np.array(s['KW'])
        rs = np.array(s['RS'])
        mass = np.array(s['M'])
        n = np.array(s['NAM'])
        x1 = np.array(s['X1'])
        x2 = np.array(s['X2'])
        x3 = np.array(s['X3'])
        v1 = np.array(s['V1'])
        v2 = np.array(s['V2'])
        v3 = np.array(s['V3'])

        fname = 'data_%.8f' % time
        f_handle = open(fname,'a') 
        np.savetxt(f_handle,
                   np.transpose((x1,x2,x3,v1,v2,v3,
                                 szeros,szeros,szeros,szeros,szeros,szeros,
                                 mass,szeros,np.log10(l),szeros,rs,szeros,k,szeros,
                                 szeros,szeros,x1,x2,x3,v1,v2,v3)),fmt="%e %e %e %e %e %e  %e %e %e %e %e %e  %e %e  %e %e  %e %e  %d %d  %e %e  %e %e %e %e %e %e")
 
        bflag = 'Binaries' in map(lambda x:x[0], s.items())

        if (bflag):
            b = s['Binaries']
            N_BINARY = b.attrs['N_BINARY']

            if (N_BINARY > 0):
                bxc1 = np.array(b['XC1'])
                bxc2 = np.array(b['XC2'])
                bxc3 = np.array(b['XC3'])
                bvc1 = np.array(b['VC1'])
                bvc2 = np.array(b['VC2'])
                bvc3 = np.array(b['VC3'])
                bxr1 = np.array(b['XR1'])
                bxr2 = np.array(b['XR2'])
                bxr3 = np.array(b['XR3'])
                bvr1 = np.array(b['VR1'])
                bvr2 = np.array(b['VR2'])
                bvr3 = np.array(b['VR3'])
                ba = np.array(b['A'])
                be = np.array(b['ECC'])
                bp = np.array(b['P'])
                bm1 = np.array(b['M1'])
                bm2= np.array(b['M2'])
                bn1 = np.array(b['NAM1'])
                bn2 = np.array(b['NAM2'])
                brs1= np.array(b['RS1'])
                brs2= np.array(b['RS2'])
                bl1= np.array(b['L1'])
                bl2= np.array(b['L2'])
                bk1= np.array(b['KW1'])
                bk2= np.array(b['KW2'])

                bm = bm1+bm2
                bmr1 = bm2/bm/206265.0
                bmr2 = bm1/bm/206265.0

                np.savetxt(f_handle,
                           np.transpose((bxc1+bmr1*bxr1,bxc2+bmr1*bxr2,bxc3+bmr1*bxr3,
                                         bvc1+bmr1*bvr1,bvc2+bmr1*bvr2,bvc3+bmr1*bvr3,
                                         bxc1+bmr2*bxr1,bxc2+bmr2*bxr2,bxc3+bmr2*bxr3,
                                         bvc1+bmr2*bvr1,bvc2+bmr2*bvr2,bvc3+bmr2*bvr3,
                                         bm1,bm2,np.log10(bl1),np.log10(bl2),brs1,brs2,bk1,bk2,
                                         ba,be,bxc1,bxc2,bxc3,bvc1,bvc2,bvc3)),fmt="%e %e %e %e %e %e  %e %e %e %e %e %e  %e %e  %e %e  %e %e  %d %d  %e %e  %e %e %e %e %e %e")

            mflag = 'Mergers' in map(lambda x:x[0], s.items())


            if (mflag) :
                m = s['Mergers']
                N_MERGER = m.attrs['N_MERGER']
                if (N_MERGER > 0):
                    mzeros = np.zeros(N_MERGER)
                    mk1 = np.array(m['KW1'])
                    mk2 = np.array(m['KW2'])
                    mk3 = np.array(m['KW3'])
                    mm1 = np.array(m['M1'])
                    mm2 = np.array(m['M2'])
                    mm3 = np.array(m['M3'])
                    mxc1 = np.array(m['XC1'])
                    mxc2 = np.array(m['XC2'])
                    mxc3 = np.array(m['XC3'])
                    mvc1 = np.array(m['VC1'])
                    mvc2 = np.array(m['VC2'])
                    mvc3 = np.array(m['VC3'])
                    mxri1 = np.array(m['XR01'])
                    mxri2 = np.array(m['XR02'])
                    mxri3 = np.array(m['XR03'])
                    mvri1 = np.array(m['VR01'])
                    mvri2 = np.array(m['VR02'])
                    mvri3 = np.array(m['VR03'])
                    mxro1 = np.array(m['XR11'])
                    mxro2 = np.array(m['XR12'])
                    mxro3 = np.array(m['XR13'])
                    mvro1 = np.array(m['VR11'])
                    mvro2 = np.array(m['VR12'])
                    mvro3 = np.array(m['VR13'])
                    ml1  = np.array(m['L1'])
                    ml2  = np.array(m['L2'])
                    ml3  = np.array(m['L3'])
                    mrs1 = np.array(m['RS1'])
                    mrs2 = np.array(m['RS2'])
                    mrs3 = np.array(m['RS3'])
                    ma0  = np.array(m['A0'])
                    mecc0= np.array(m['ECC0'])

                    micm = mm1 + mm2
                    mm = micm + mm3
                    micmr = mm3/mm/206265.0
                    m3r = micm/mm/206265.0
                    mxicm1 = mxc1 + micmr*mxro1
                    mxicm2 = mxc2 + micmr*mxro2
                    mxicm3 = mxc3 + micmr*mxro3
                    mx31   = mxc1 + m3r*mxro1
                    mx32   = mxc2 + m3r*mxro2
                    mx33   = mxc3 + m3r*mxro3
                    mvicm1 = mvc1 + micmr*mvro1
                    mvicm2 = mvc2 + micmr*mvro2
                    mvicm3 = mvc3 + micmr*mvro3
                    mv31   = mvc1 + m3r*mvro1
                    mv32   = mvc2 + m3r*mvro2
                    mv33   = mvc3 + m3r*mvro3
                    mx1r = mm2/micm/206265.0
                    mx2r = mm1/micm/206265.0
                    mx11   = mxicm1 + mx1r*mxri1
                    mx12   = mxicm2 + mx1r*mxri2
                    mx13   = mxicm3 + mx1r*mxri3
                    mx21   = mxicm1 + mx2r*mxri1
                    mx22   = mxicm2 + mx2r*mxri2
                    mx23   = mxicm3 + mx2r*mxri3
                    mv11   = mvicm1 + mx1r*mvri1
                    mv12   = mvicm2 + mx1r*mvri2
                    mv13   = mvicm3 + mx1r*mvri3
                    mv21   = mvicm1 + mx2r*mvri1
                    mv22   = mvicm2 + mx2r*mvri2
                    mv23   = mvicm3 + mx2r*mvri3
                
                    np.savetxt(f_handle,
                               np.transpose((mx11,mx12,mx13,mv11,mv12,mv13,
                                             mx21,mx22,mx23,mv21,mv22,mv23,
                                             mm1,mm2,np.log10(ml1),np.log10(ml2),mrs1,mrs2,mk1,mk2,
                                             ma0,mecc0,mxicm1,mxicm2,mxicm3,mvicm1,mvicm2,mvicm3)),fmt="%e %e %e %e %e %e  %e %e %e %e %e %e  %e %e  %e %e  %e %e  %d %d  %e %e  %e %e %e %e %e %e")

                    np.savetxt(f_handle,
                               np.transpose((mx31,mx32,mx33,mv31,mv32,mv33,
                                             mzeros,mzeros,mzeros,mzeros,mzeros,mzeros,
                                             mm3,mzeros,np.log10(ml3),mzeros,mrs3,mzeros,mk3,mzeros,
                                             mzeros,mzeros,mx31,mx32,mx33,mv31,mv32,mv33)),fmt="%e %e %e %e %e %e  %e %e %e %e %e %e  %e %e  %e %e  %e %e  %d %d  %e %e  %e %e %e %e %e %e")
                
        
                
