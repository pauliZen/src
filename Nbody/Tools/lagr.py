# Lagrangian radii, average mass, number, velocity, radial/tangential velocity, velocity dispersion, radial/tangential velocity dispersion, x/y/z velocity dispersion, rotational velocity
# For velocity and dispersion, binaries/mergers are not resolved.

# if hdflag = false, read snapshot generate from snapshot.f
#  --fsnap  = false, snapshot for MOCCA
#                    the snap.lst should only contain the time
#                    filename for single data should be single_[time]
#                             for binary data should be binary_[time]
#                    bflag and scaling factors should be defined
#  --fsnap  = true,  snapshot for Fit transformation
#                    the snap.lst should only contain the time
#                    filename prefix is defined in fpr, filename 
#                    is [fpr][time]

# Input arguments: 13 (first is script path)
#  1. filename snapshot list filename     
#  2. hdflag   HD5 output flag
#  3. fsnap    Fit snapshot flag
#  4. fpr      prefix of data
#  5. bflag    binary flag
#  6. rscale   distance scaling [pc]
#  7. mscale   mass scaling [M_sun]
#  8. vscale   velocity scaling [km/s]
#  9. fshell   calculation between shells flag
# 10. fbres    resolving binaries during average mass calculation flag
# 11. Tint     Time interval for output
# 12. Tres     Time resolution for snapshots in NB unit

import numpy as np
import sys
import matplotlib.pyplot as plt
import h5py
import math
from matplotlib.colors import BoundaryNorm
from matplotlib.ticker import MaxNLocator

# Custom options
# for HDF5 output
filename = 'snap.lst'
hdflag = True
# for snapshot case: Single snapshot file for Fit transformation
fsnap = True
fpr = 'data_'
# for snaphsot case: MOCCA snapshot
bflag = True
rscale = 1.0
mscale = 1.0
vscale = 1.0
# Whether calculate everything from center or between neighbor shells
fshell = True
# Whether resolve binaries for average mass calculation
fbres = False
# Time interval for calculation (in NB unit)
Tint  = 2.0
# resolution of time interval in NB unit
Tres  = 0.125

larg=len(sys.argv)
if (larg==13):
    filename = sys.argv[1]
    hdflag = int(sys.argv[2])
    fsnap  = int(sys.argv[3])
    fpr    = sys.argv[4]
    bflag  = int(sys.argv[5])
    rscale = float(sys.argv[6])
    mscale = float(sys.argv[7])
    vscale = float(sys.argv[8])
    fshell = int(sys.argv[9])
    fbres  = int(sys.argv[10])
    Tint   = float(sys.argv[11])
    Tres   = float(sys.argv[12])

fl = open(filename,'r')
path = fl.read()
path = path.splitlines()

#rfrac=np.array([0.001,0.003,0.005,0.01,0.03,0.05,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.95,0.99,1.0])
# More useful fraction:
rfrac=np.array([0.001,0.01,0.1,0.3,0.5,0.7,0.9,1.0])

# Safe x/y function:
fxovery = lambda x,y: 0.0 if float(y)==0.0 else x/y

linec = 0
ifirst = True
toffset = 0.0

for i in path:
    f = 0
    if (hdflag):
        f = h5py.File(i,'r')
        tots = len(f.items())
    else:
        tots = 1

    kj = 0
    while (kj<tots):

        s = 0
        if (hdflag):
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
        else:
            time = float(i)

        kj += 1

        if (time-toffset < Tint*linec-Tres/2.0):
            continue
        else:
            linec += 1


        # lagrangian radii
        rlagr=np.zeros(rfrac.size)
        rslagr=np.zeros(rfrac.size)
        rblagr=np.zeros(rfrac.size)

        # numbers
        nlagr=np.zeros(rfrac.size)
        nslagr=np.zeros(rfrac.size)
        nblagr=np.zeros(rfrac.size)
         
        # average mass
        mlagr=np.zeros(rfrac.size)
        mslagr=np.zeros(rfrac.size)
        mblagr=np.zeros(rfrac.size)
         
        # average velocity
        vlagr=np.zeros(rfrac.size)
        vslagr=np.zeros(rfrac.size)
        vblagr=np.zeros(rfrac.size)
         
        # average x velocity
        vxlagr=np.zeros(rfrac.size)
        vxslagr=np.zeros(rfrac.size)
        vxblagr=np.zeros(rfrac.size)
         
        # average y velocity
        vylagr=np.zeros(rfrac.size)
        vyslagr=np.zeros(rfrac.size)
        vyblagr=np.zeros(rfrac.size)

        # average z velocity
        vzlagr=np.zeros(rfrac.size)
        vzslagr=np.zeros(rfrac.size)
        vzblagr=np.zeros(rfrac.size)
         
        # average tangential velocity
        vtlagr=np.zeros(rfrac.size)
        vtslagr=np.zeros(rfrac.size)
        vtblagr=np.zeros(rfrac.size)

        # average radial velocity
        vrlagr=np.zeros(rfrac.size)
        vrslagr=np.zeros(rfrac.size)
        vrblagr=np.zeros(rfrac.size)
         
        # velocity dispersion
        siglagr=np.zeros(rfrac.size)
        sigslagr=np.zeros(rfrac.size)
        sigblagr=np.zeros(rfrac.size)
         
        # radial velocity dispersion
        sigrlagr=np.zeros(rfrac.size)
        sigrslagr=np.zeros(rfrac.size)
        sigrblagr=np.zeros(rfrac.size)
         
        # tangential velocity dispersion
        sigtlagr=np.zeros(rfrac.size)
        sigtslagr=np.zeros(rfrac.size)
        sigtblagr=np.zeros(rfrac.size)
         
        # x velocity dispersion
        sigxlagr=np.zeros(rfrac.size)
        sigxslagr=np.zeros(rfrac.size)
        sigxblagr=np.zeros(rfrac.size)
         
        # y velocity dispersion
        sigylagr=np.zeros(rfrac.size)
        sigyslagr=np.zeros(rfrac.size)
        sigyblagr=np.zeros(rfrac.size)
         
        # z velocity dispersion
        sigzlagr=np.zeros(rfrac.size)
        sigzslagr=np.zeros(rfrac.size)
        sigzblagr=np.zeros(rfrac.size)
         
        # rotational velocity
        vrotlagr=np.zeros(rfrac.size)
        vrotslagr=np.zeros(rfrac.size)
        vrotblagr=np.zeros(rfrac.size)

        # rotational velocity dispersion
        sigrotlagr=np.zeros(rfrac.size)
        sigrotslagr=np.zeros(rfrac.size)
        sigrotblagr=np.zeros(rfrac.size)

        #  Binary mass/number inside different R_lagr
        msblagr=np.zeros(rfrac.size)
        nsblagr=np.zeros(rfrac.size)

        #  Primordial binary mass/number inside different R_lagr
        mspblagr=np.zeros(rfrac.size)
        nspblagr=np.zeros(rfrac.size)

        N_SINGLE = 0

        t = 0
        l = 0
        k = 0
        mass = 0
        n = 0
        x1 = 0
        x2 = 0
        x3 = 0
        v1 = 0
        v2 = 0
        v3 = 0

        N_BINARY = 0
        b = 0

        bm1 = 0
        bm2 = 0
        bxc1 = 0
        bxc2 = 0
        bxc3 = 0
        bvc1 = 0
        bvc2 = 0
        bvc3 = 0
#        bk1 = 0
#        bk2 = 0
        ba = 0
        be = 0
        bp = 0
        bn1 = 0
        bn2 = 0

        mflag = False

        if (hdflag):
            N_SINGLE = s.attrs['N_SINGLE']

            t = np.array(s['TE'])
            l = np.array(s['L'])
            k = np.array(s['KW'])
            mass = np.array(s['M'])
            n = np.array(s['NAM'])
            x1 = np.array(s['X1'])
            x2 = np.array(s['X2'])
            x3 = np.array(s['X3'])
            v1 = np.array(s['V1'])
            v2 = np.array(s['V2'])
            v3 = np.array(s['V3'])
     
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
                    ba = np.array(b['A'])
                    be = np.array(b['ECC'])
                    bp = np.array(b['P'])
                    bm1 = np.array(b['M1'])
                    bm2= np.array(b['M2'])
                    bn1 = np.array(b['NAM1'])
                    bn2 = np.array(b['NAM2'])
                else:
                    bflag = False

            mflag = 'Mergers' in map(lambda x:x[0], s.items())

        else:
            if (fsnap):
                m1,m2,xc1,xc2,xc3,vc1,vc2,vc3,n1,n2 = np.loadtxt(fpr+i,unpack=True,usecols=(12,13,22,23,24,25,26,27,28,29))
                mass = m1[m2==0]
                N_SINGLE = mass.size
                x1 = xc1[m2==0]
                x2 = xc2[m2==0]
                x3 = xc3[m2==0]
                v1 = vc1[m2==0]
                v2 = vc2[m2==0]
                v3 = vc3[m2==0]

                bm1 = m1[m2>0]
                N_BINARY = bm1.size
                if (N_BINARY>0):
                    bflag = True
                    bm2 = m2[m2>0]
                    bxc1 = xc1[m2>0]
                    bxc2 = xc2[m2>0]
                    bxc3 = xc3[m2>0]
                    bvc1 = vc1[m2>0]
                    bvc2 = vc2[m2>0]
                    bvc3 = vc3[m2>0]
                    bn1  = n1[m2>0]
                    bn2  = n2[m2>0]
                else:
                    bflag = False
            else:
                mass,x1,x2,x3,v1,v2,v3 = np.loadtxt(fpr+i+'_single.dat',unpack=True)
                N_SINGLE = mass.size
#                if (mscale!=1.0):
#                    mass = mass*mscale
                if (rscale!=1.0):
                    x1 = x1*rscale
                    x2 = x2*rscale
                    x3 = x3*rscale
                if (vscale!=1.0):
                    v1 = v1*vscale
                    v2 = v2*vscale
                    v3 = v3*vscale
        
                if (bflag):
                    bm1,bm2,bxc1,bxc2,bxc3,bvc1,bvc2,bvc3 = np.loadtxt(fpr+i+'_binary.dat',unpack=True,usecols=(2,3,4,5,6,7,8,9))
                    N_BINARY = bm1.size
                    if (N_BINARY>0):
                        bn1 = np.zeros(rfrac.size)
                        bn2 = np.zeros(rfrac.size)
#                    if (mscale!=1.0):
#                        bm1 = bm1*mscale
#                        bm2 = bm2*mscale
                        if (rscale!=1.0):
                            bxc1 = bxc1*rscale
                            bxc2 = bxc2*rscale
                            bxc3 = bxc3*rscale
                        if (vscale!=1.0):
                            bvc1 = bvc1*vscale
                            bvc2 = bvc2*vscale
                            bvc3 = bvc3*vscale
                    else:
                        bflag=False

        N_MERGER = 0
        m = 0

        mm1 = 0
        mm2 = 0
        mm3 = 0
        mxc1 = 0
        mxc2 = 0
        mxc3 = 0
        mvc1 = 0
        mvc2 = 0
        mvc3 = 0
        mk1 = 0
        mk2 = 0
        mk3 = 0

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
                mvc1 = np.array(m['VC1'])
                mvc2 = np.array(m['VC2'])
                mvc3 = np.array(m['VC3'])
            else:
                mflag = False

        tsmass = float(mass.sum())
        tbmass = 0
        tmmass = 0
        rbmass = 0
        rmmass = 0

        rs2 = x1*x1 + x2*x2 + x3*x3
        rb2 = 0
        r2 = rs2

        if (bflag): 
            tbmass = float(bm1.sum() + bm2.sum())
            rb2 = bxc1*bxc1 + bxc2*bxc2 + bxc3*bxc3
            r2 = np.append(r2,rb2)

        rm2 = 0
        if (mflag):
            tmmass = float(mm1.sum() + mm2.sum() + mm3.sum())
            rm2 = mxc1*mxc1 + mxc2*mxc2 + mxc3*mxc3
            r2 = np.append(r2,rm2)
#        rb2 = np.append(rb2,rm2)

# Total mass
        tmass = tsmass + tbmass + tmmass
# Treat triple as binary
        tbmass = tbmass + tmmass

#  mass limit for different R_lagr
        rmass = tmass*rfrac
        rsmass = tsmass*rfrac
        rbmass = tbmass*rfrac
        
#  Get distance sorting index
        idx = r2.argsort()

# counter for different R_lagr bins
        kk = 0
        kks = 0
        kkb = 0

#   Number counter
        nc = 0
        ncs = 0
        ncb = 0
        #   Previous counter
        ncprev = 0
        ncsprev = 0
        ncbprev = 0

#   Mass counter
        cmass = 0
        bmass = 0
        smass = 0
        #   Previous counter
        mcprev = 0
        mcsprev = 0
        mcbprev = 0

#  Single and binary number
        N_SB = N_SINGLE + N_BINARY
#  binary and merger
        N_BM = N_BINARY + N_MERGER
        # Resolved case
        if (fbres): N_BM = N_BINARY*2 + N_MERGER*3
#  Total number 
        N_TOT = N_SB + N_MERGER
        # For total counter, unresolved and resolved case 
        N_TOTR = N_BM + N_SINGLE
#  Initialize the velocity vectors
        # velocity, x,y,z,r,t,rot
        vx = np.zeros(N_TOT)
        vy = np.zeros(N_TOT)
        vz = np.zeros(N_TOT)
        # The radial velocity uses the spherical coordinate system, thus not a vector
        vr = np.zeros(N_TOT)
        # Notice the tangential velocity is also vector in (x,y,z) coordinate system
        vt = np.zeros((N_TOT,3))
        # Average tangetial velocity
        vtave = np.zeros((rfrac.size,3))
        vtbave = np.zeros((rfrac.size,3))
        vtsave = np.zeros((rfrac.size,3))
        # rotational velocity
        vrot = np.zeros(N_TOT)
#   Initialize mass array
        mmb = np.zeros(N_TOT)

        for j in idx:
#  Initialization
            # position
            rx = 0.0
            ry = 0.0
            rz = 0.0
            ri = math.sqrt(r2[j])

#   Binary/merger case
            if (j>=N_SINGLE):
                # increase binary counter by one
                ncb += 1
                if (fbres):
                    # increase total counter by one in binary case
                    nc += 1
                    # increase binary counter by one for resolved case
                    ncb += 1
#   Merger case
                
                if (j>=N_SB):
                    if (fbres):
                        # increase total counter by one in merger case
                        nc += 1
                        # increase binary counter by one for resolved case
                        ncb += 1
                    inx = j - N_SB
                    mmb[j] = mm1[inx]+mm2[inx]+mm3[inx]
                    vx[j] = mvc1[inx]
                    vy[j] = mvc2[inx]
                    vz[j] = mvc3[inx]
                    rx    = mxc1[inx]
                    ry    = mxc2[inx]
                    rz    = mxc3[inx]
#   Binary case
                else:
                    inx = j - N_SINGLE
                    mmb[j] = bm1[inx]+bm2[inx]
                    vx[j] = bvc1[inx]
                    vy[j] = bvc2[inx]
                    vz[j] = bvc3[inx]
                    rx    = bxc1[inx]
                    ry    = bxc2[inx]
                    rz    = bxc3[inx]

#########--debug-------------------------
###            btt=bxc1[inx]*bxc1[inx] + bxc2[inx]*bxc2[inx]+ bxc3[inx]*bxc3[inx]
###            if (btt == r2[j]): 
###                print "Inconsistence: inx=%d, j=%d, r2=%e, r2s=%e, " % (inx,j,btt,r2[j])
#########--debug-------------------------

#   Single case
            else:
                # increase number counter
                ncs += 1
                mmb[j] = mass[j]
                rx     = x1[j]
                ry     = x2[j]
                rz     = x3[j]
                vx[j]  = v1[j]
                vy[j]  = v2[j]
                vz[j]  = v3[j]

            #  increase total counter
            nc += 1

#   Get velocity information
            # x-y plane radial velocity * rxy
            rvxy = rx*vx[j] + ry*vy[j]
            # radial velocity value
            vr[j] = (rvxy + rz*vz[j])/ri
            # tangential velocity vector
            vt[j,0] = vx[j] - vr[j]*rx/ri
            vt[j,1] = vy[j] - vr[j]*ry/ri
            vt[j,2] = vz[j] - vr[j]*rz/ri
            # x-y plane radial position square
            rxy2 = rx*rx + ry*ry
            # rotational velocity
            vrot1 = vx[j] - rvxy*rx/rxy2
            vrot2 = vy[j] - rvxy*ry/rxy2
            vrot[j] = math.sqrt(vrot1*vrot1+vrot2*vrot2)
            # rotational direction sign
            vrotd = vrot1*ry - vrot2*rx
            if (vrotd<0.0): vrot[j] = -vrot[j]

#   Check whether need to reach next bin
            if (j>=N_SINGLE):
                #  Add mass
                bmass += mmb[j]

                # increase mass/number counter for binaries in R_lagr
                if (kk < rfrac.size):
                    msblagr[kk] += mmb[j]
                    nsblagr[kk] += 1
                    if (fbres): nsblagr[kk] += 1

                    # primordial binareis
                    if (j<N_SB):
                        if (abs(bn1[j-N_SINGLE]-bn2[j-N_SINGLE])==1):
                            mspblagr[kk] += mmb[j]
                            nspblagr[kk] += 1
                            if (fbres): nspblagr[kk] += 1

                if (kkb < rfrac.size):
                    #  average velocity
                    vxblagr[kkb] += mmb[j]*vx[j] 
                    vyblagr[kkb] += mmb[j]*vy[j] 
                    vzblagr[kkb] += mmb[j]*vz[j] 
                    vrblagr[kkb] += mmb[j]*vr[j] 
                    vtbave[kkb] += mmb[j]*vt[j] 
                    vrotblagr[kkb] += mmb[j]*vrot[j]

                    # Go to next bin if mass reach the R_Lagr limit
                    if ((bmass >= rbmass[kkb]) | ((kkb == rfrac.size-1) & (ncb == N_BM))):
                        # update mass
                        rbmass[kkb] = bmass
                        # Get R_lagr for binary
                        rblagr[kkb] = ri
                        # Get number for binary
                        nblagr[kkb] = ncb
                        # For shell cases:
                        if ((fshell) & (kkb>0)):
                            rbmass[kkb] -= mcbprev
                            nblagr[kkb] -= ncbprev
                        mcbprev = bmass
                        ncbprev = ncb
                        # Increase bin index
                        kkb += 1
                        # initial next bins
                        if (kkb < rfrac.size):
                            if ((not fshell) & (nblagr[kkb] == 0)):
                                vxblagr[kkb] = vxblagr[kkb-1]
                                vyblagr[kkb] = vyblagr[kkb-1]
                                vzblagr[kkb] = vzblagr[kkb-1]
                                vrblagr[kkb] = vrblagr[kkb-1]
                                vtbave[kkb] = vtbave[kkb-1]
                                vrotblagr[kkb] = vrotblagr[kkb-1]
###########---debug--------------
#                if(kkb > rfrac.size - 1): print j , ncb, N_BINARY, bmass, tbmass, rbmass[rfrac.size-1],time
###########---debug--------------
                        # Avoid overflow of bin index
                        # kkb = min(kkb,rfrac.size-1)
            else:
                # Add mass
                smass += mmb[j]

                if (kks < rfrac.size):
                    #  average velocity
                    vxslagr[kks] += mmb[j]*vx[j] 
                    vyslagr[kks] += mmb[j]*vy[j] 
                    vzslagr[kks] += mmb[j]*vz[j] 
                    vrslagr[kks] += mmb[j]*vr[j] 
                    vtsave[kks] += mmb[j]*vt[j] 
                    vrotslagr[kks] += mmb[j]*vrot[j]

                    # Go to next bin if mass reach the R_lagr limit
                    if ((smass >= rsmass[kks]) | ((kks == rfrac.size-1) & (ncs == N_SINGLE))):
                        # update mass
                        rsmass[kks] = smass
                        # Get R_lagr for single
                        rslagr[kks] = ri
                        # Get number for single
                        nslagr[kks] = ncs
                        # For shell cases:
                        if ((fshell) & (kks>0)):
                            rsmass[kks] -= mcsprev 
                            nslagr[kks] -= ncsprev
                        mcsprev = smass
                        ncsprev = ncs
                        # increase bin index
                        kks += 1
                        # initial next bins
                        if (kks < rfrac.size):
                            if((not fshell) & (nslagr[kks] == 0)):
                                vxslagr[kks] = vxslagr[kks-1]
                                vyslagr[kks] = vyslagr[kks-1]
                                vzslagr[kks] = vzslagr[kks-1]
                                vrslagr[kks] = vrslagr[kks-1]
                                vtsave[kks] = vtsave[kks-1]
                                vrotslagr[kks] = vrotslagr[kks-1]
                        # Avoid overflow of bin index
                        # kks = min(kks,rfrac.size-1)
            
#   Go to next R_lagr if mass reach limit
            cmass += mmb[j]

            if (kk < rfrac.size):
                #  average velocity
                vxlagr[kk] += mmb[j]*vx[j] 
                vylagr[kk] += mmb[j]*vy[j] 
                vzlagr[kk] += mmb[j]*vz[j] 
                vrlagr[kk] += mmb[j]*vr[j] 
                vtave[kk] += mmb[j]*vt[j] 
                vrotlagr[kk] += mmb[j]*vrot[j]

                if ((cmass >= rmass[kk]) | ((kk == rfrac.size-1) & (nc == N_TOTR))):
                    # update mass
                    rmass[kk] = cmass
                    # Get R_lagr 
                    rlagr[kk] = ri
                    # Get number
                    nlagr[kk] = nc
                    # For shell cases:
                    if ((fshell) & (kk>0)):
                        rmass[kk] -= mcprev
                        nlagr[kk] -= ncprev
                    mcprev = cmass
                    ncprev = nc
                    # increase bin index
                    kk += 1
                    # Get initial value for next bin 
                    if (kk < rfrac.size ):
                        if (not fshell):
                            # binary counter
                            if (nsblagr[kk] == 0):
                                msblagr[kk] = msblagr[kk-1]
                                nsblagr[kk] = nsblagr[kk-1]
                            if (nspblagr[kk] == 0):
                                mspblagr[kk] = mspblagr[kk-1]
                                nspblagr[kk] = nspblagr[kk-1]
                            # total counter
                            if (nlagr[kk] == 0):
                                vxlagr[kk] = vxlagr[kk-1]
                                vylagr[kk] = vylagr[kk-1]
                                vzlagr[kk] = vzlagr[kk-1]
                                vrlagr[kk] = vrlagr[kk-1]
                                vtave[kk] = vtave[kk-1]
                                vrotlagr[kk] = vrotlagr[kk-1]
                    # Avoid overflow of bin index
                    # kk = min(kk,rfrac.size-1)

#   Fill empty bins with neighbor bin values
        if (not fshell):
            #   Total
            kn = kk - 1
            while (kk < rfrac.size):
                rlagr[kk] = rlagr[kn]
                nlagr[kk] = nlagr[kn]
                nsblagr[kk] = nsblagr[kn]
                msblagr[kk] = msblagr[kn]
                nspblagr[kk] = nspblagr[kn]
                mspblagr[kk] = mspblagr[kn]
                vxlagr[kk] = vxlagr[kn]
                vylagr[kk] = vylagr[kn]
                vzlagr[kk] = vzlagr[kn]
                vrlagr[kk] = vrlagr[kn]
                vtave[kk] = vtave[kn]
                vrotlagr[kk] = vrotlagr[kn]
                kk += 1
            #   Single
            ksn = kks - 1
            while (kks < rfrac.size):
                rslagr[kks] = rslagr[ksn]
                nslagr[kks] = nslagr[ksn]
                vxslagr[kks] = vxslagr[ksn]
                vyslagr[kks] = vyslagr[ksn]
                vzslagr[kks] = vzslagr[ksn]
                vrslagr[kks] = vrslagr[ksn]
                vtsave[kks] = vtsave[ksn]
                vrotslagr[kks] = vrotslagr[ksn]
                kks += 1
            #   Binary + Merger
            kbn = kkb - 1
            while (kkb < rfrac.size):
                rblagr[kkb] = rblagr[kbn]
                nblagr[kkb] = nblagr[kbn]
                vxblagr[kkb] = vxblagr[kbn]
                vyblagr[kkb] = vyblagr[kbn]
                vzblagr[kkb] = vzblagr[kbn]
                vrblagr[kkb] = vrblagr[kbn]
                vtbave[kkb] = vtbave[kbn]
                vrotblagr[kkb] = vrotblagr[kbn]
                kkb += 1

#   Average mass
        mlagr  = np.array(map(fxovery,rmass,nlagr)  ) 
        mslagr = np.array(map(fxovery,rsmass,nslagr)) 
        mblagr = np.array(map(fxovery,rbmass,nblagr)) 
#   Average velocity
        # total
        vxlagr  = np.array(map(fxovery,vxlagr  ,rmass)) 
        vylagr  = np.array(map(fxovery,vylagr  ,rmass)) 
        vzlagr  = np.array(map(fxovery,vzlagr  ,rmass)) 
        vrlagr  = np.array(map(fxovery,vrlagr  ,rmass)) 
        vtave   = np.array(map(fxovery,vtave   ,rmass)) 
        vrotlagr= np.array(map(fxovery,vrotlagr,rmass)) 
        vlagr   = np.sqrt(vxlagr*vxlagr + vylagr*vylagr + vzlagr*vzlagr)
        vtlagr  = np.array(map(lambda x: math.sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]), vtave))
        #single
        vxslagr  = np.array(map(fxovery,vxslagr  ,rsmass)) 
        vyslagr  = np.array(map(fxovery,vyslagr  ,rsmass)) 
        vzslagr  = np.array(map(fxovery,vzslagr  ,rsmass)) 
        vrslagr  = np.array(map(fxovery,vrslagr  ,rsmass)) 
        vtsave   = np.array(map(fxovery,vtsave   ,rsmass)) 
        vrotslagr= np.array(map(fxovery,vrotslagr,rsmass)) 
        vslagr   = np.sqrt(vxslagr*vxslagr + vyslagr*vyslagr + vzslagr*vzslagr)
        vtslagr  = np.array(map(lambda x: math.sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]), vtsave))
        #binary/merger
        if(bflag):
            vxblagr  = np.array(map(fxovery,vxblagr  ,rbmass)) 
            vyblagr  = np.array(map(fxovery,vyblagr  ,rbmass)) 
            vzblagr  = np.array(map(fxovery,vzblagr  ,rbmass)) 
            vrblagr  = np.array(map(fxovery,vrblagr  ,rbmass)) 
            vtbave   = np.array(map(fxovery,vtbave   ,rbmass)) 
            vrotblagr= np.array(map(fxovery,vrotblagr,rbmass)) 
            vblagr   = np.sqrt(vxblagr*vxblagr + vyblagr*vyblagr + vzblagr*vzblagr)
            vtblagr  = np.array(map(lambda x: math.sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]), vtbave))
    
#   Loop again to get velocity dispersion
#   counter for different R_lagr bins
        kk = 0
        kks = 0
        kkb = 0
#   Number counter
        nc = 0
        ncs = 0
        ncb = 0
        #   Previous counter
        ncprev = 0
        ncsprev = 0
        ncbprev = 0
#
        for j in idx:
            #  increase total counter
            nc += 1
#   Binary/merger case
            if (j>=N_SINGLE):
                # increase binary counter by two 
                ncb += 1
                if (fbres):
                    # increase total counter by one in binary case
                    nc += 1
                    # increase binary counter by one for resolved case
                    ncb += 1
                    if (j>=N_SB):
                        # For merger case
                        nc  += 1
                        ncb += 1
                # x,y,z
                dx = vx[j] - vxblagr[kkb]
                dy = vy[j] - vyblagr[kkb]
                dz = vz[j] - vzblagr[kkb]
                dr = vr[j] - vrblagr[kkb]
                dt = vt[j] - vtbave[kkb]
                drot = vrot[j] - vrotblagr[kkb]
                # mass weighted square
                dx2 = mmb[j]*dx*dx
                dy2 = mmb[j]*dy*dy
                dz2 = mmb[j]*dz*dz
                dr2 = mmb[j]*dr*dr
                dt2 = mmb[j]*(dt[0]*dt[0] + dt[1]*dt[1] + dt[2]*dt[2])
                drot2= mmb[j]*drot*drot
                # velocity value
#                dv2 = dx2 + dy2 + dz2
                # dispersion
                sigxblagr[kkb] += dx2
                sigyblagr[kkb] += dy2
                sigzblagr[kkb] += dz2
#                sigblagr[kkb] += dv2
                sigrblagr[kkb] += dr2
                sigtblagr[kkb] += dt2
                sigrotblagr[kkb] += drot2

                # check whether need to increase kkb
                if (ncb-ncbprev==nblagr[kkb]):
                    if (fshell): ncbprev += nblagr[kkb]
                    kkb += 1
                    if ((not fshell) & (kkb < rfrac.size)):
                        sigxblagr[kkb] = sigxblagr[kkb-1]
                        sigyblagr[kkb] = sigyblagr[kkb-1]
                        sigzblagr[kkb] = sigzblagr[kkb-1]
                        sigrblagr[kkb] = sigrblagr[kkb-1]
                        sigtblagr[kkb] = sigtblagr[kkb-1]
                        sigrotblagr[kkb] = sigrotblagr[kkb-1]
                
#   Single case
            else:
                # increase number counter
                ncs += 1
                # x,y,z
                dx = vx[j] - vxslagr[kks]
                dy = vy[j] - vyslagr[kks]
                dz = vz[j] - vzslagr[kks]
                dr = vr[j] - vrslagr[kks]
                dt = vt[j] - vtsave[kks]
                drot = vrot[j] - vrotslagr[kks]
                # mass weighted square
                dx2 = mmb[j]*dx*dx
                dy2 = mmb[j]*dy*dy
                dz2 = mmb[j]*dz*dz
                dr2 = mmb[j]*dr*dr
                dt2 = mmb[j]*(dt[0]*dt[0] + dt[1]*dt[1] + dt[2]*dt[2])
                drot2= mmb[j]*drot*drot
                # velocity value
#                dv2 = dx2 + dy2 + dz2
                # dispersion
                sigxslagr[kks] += dx2
                sigyslagr[kks] += dy2
                sigzslagr[kks] += dz2
#                sigslagr[kks] += dv2
                sigrslagr[kks] += dr2
                sigtslagr[kks] += dt2
                sigrotslagr[kks] += drot2

                # check whether need to increase kks
                if (ncs-ncsprev==nslagr[kks]):
                    if (fshell): ncsprev += nslagr[kks]
                    kks += 1
                    if ((not fshell) & (kks < rfrac.size)):
                        sigxslagr[kks] = sigxslagr[kks-1]
                        sigyslagr[kks] = sigyslagr[kks-1]
                        sigzslagr[kks] = sigzslagr[kks-1]
                        sigrslagr[kks] = sigrslagr[kks-1]
                        sigtslagr[kks] = sigtslagr[kks-1]
                        sigrotslagr[kks] = sigrotslagr[kks-1]

#   Total                 
            # x,y,z
            dx = vx[j] - vxlagr[kk]
            dy = vy[j] - vylagr[kk]
            dz = vz[j] - vzlagr[kk]
            dr = vr[j] - vrlagr[kk]
            dt = vt[j] - vtave[kk]
            drot = vrot[j] - vrotlagr[kk]
            # mass weighted square
            dx2 = mmb[j]*dx*dx
            dy2 = mmb[j]*dy*dy
            dz2 = mmb[j]*dz*dz
            dr2 = mmb[j]*dr*dr
            dt2 = mmb[j]*(dt[0]*dt[0] + dt[1]*dt[1] + dt[2]*dt[2])
            drot2= mmb[j]*drot*drot
            # velocity value
 #           dv2 = dx2 + dy2 + dz2
            # dispersion
            sigxlagr[kk] += dx2
            sigylagr[kk] += dy2
            sigzlagr[kk] += dz2
#            siglagr[kk] += dv2
            sigrlagr[kk] += dr2
            sigtlagr[kk] += dt2
            sigrotlagr[kk] += drot2

            # check whether need to increase kk
            if (nc-ncprev==nlagr[kk]):
                if (fshell): ncprev += nlagr[kk]
                kk += 1
                if ((not fshell) & (kk < rfrac.size)):
                    sigxlagr[kk] = sigxlagr[kk-1]
                    sigylagr[kk] = sigylagr[kk-1]
                    sigzlagr[kk] = sigzlagr[kk-1]
                    sigrlagr[kk] = sigrlagr[kk-1]
                    sigtlagr[kk] = sigtlagr[kk-1]
                    sigrotlagr[kk] = sigrotlagr[kk-1]

        if (not fshell):
            kn = kk - 1
            while (kk < rfrac.size):
                sigxlagr[kk] = sigxlagr[kn]
                sigylagr[kk] = sigylagr[kn]
                sigzlagr[kk] = sigzlagr[kn]
                sigrlagr[kk] = sigrlagr[kn]
                sigtlagr[kk] = sigtlagr[kn]
                sigrotlagr[kk] = sigrotlagr[kn]
                kk += 1
            ksn = kks - 1
            while (kks < rfrac.size):
                sigxslagr[kks] = sigxslagr[ksn]
                sigyslagr[kks] = sigyslagr[ksn]
                sigzslagr[kks] = sigzslagr[ksn]
                sigrslagr[kks] = sigrslagr[ksn]
                sigtslagr[kks] = sigtslagr[ksn]
                sigrotslagr[kks] = sigrotslagr[ksn]
                kks += 1
            kbn = kkb - 1
            while (kkb < rfrac.size):
                sigxblagr[kkb] = sigxblagr[kbn]
                sigyblagr[kkb] = sigyblagr[kbn]
                sigzblagr[kkb] = sigzblagr[kbn]
                sigrblagr[kkb] = sigrblagr[kbn]
                sigtblagr[kkb] = sigtblagr[kbn]
                sigrotblagr[kkb] = sigrotblagr[kbn]
                kkb += 1

# Divide mass
        # total
#        siglagr   = siglagr   /(rmass*3.0)
        sigxlagr  = np.array(map(fxovery,sigxlagr  ,rmass)) 
        sigylagr  = np.array(map(fxovery,sigylagr  ,rmass)) 
        sigzlagr  = np.array(map(fxovery,sigzlagr  ,rmass)) 
        sigrlagr  = np.array(map(fxovery,sigrlagr  ,rmass)) 
        sigtlagr  = np.array(map(fxovery,sigtlagr  ,rmass)) 
        sigrotlagr= np.array(map(fxovery,sigrotlagr,rmass))
        siglagr   = sigxlagr + sigylagr + sigzlagr
        #single
#        sigslagr   = sigslagr   /(rsmass*3.0)
        sigxslagr  = np.array(map(fxovery,sigxslagr  ,rsmass)) 
        sigyslagr  = np.array(map(fxovery,sigyslagr  ,rsmass)) 
        sigzslagr  = np.array(map(fxovery,sigzslagr  ,rsmass)) 
        sigrslagr  = np.array(map(fxovery,sigrslagr  ,rsmass)) 
        sigtslagr  = np.array(map(fxovery,sigtslagr  ,rsmass)) 
        sigrotslagr= np.array(map(fxovery,sigrotslagr,rsmass)) 
        sigslagr   = sigxslagr + sigyslagr + sigzslagr
        #binary/merger
#        sigblagr   = sigblagr   /(rbmass*3.0)
        if(bflag):
            sigxblagr  = np.array(map(fxovery,sigxblagr  ,rbmass)) 
            sigyblagr  = np.array(map(fxovery,sigyblagr  ,rbmass)) 
            sigzblagr  = np.array(map(fxovery,sigzblagr  ,rbmass)) 
            sigrblagr  = np.array(map(fxovery,sigrblagr  ,rbmass)) 
            sigtblagr  = np.array(map(fxovery,sigtblagr  ,rbmass)) 
            sigrotblagr= np.array(map(fxovery,sigrotblagr,rbmass)) 
            sigblagr   = sigxblagr + sigyblagr + sigzblagr


#   Print data 
        print "%.8e " % time,
        # R_Lagr
        for j in range(rfrac.size): 
            print "%.8e " % rlagr[j],
        for j in range(rfrac.size): 
            print "%.8e " % rslagr[j],
        for j in range(rfrac.size): 
            print "%.8e " % rblagr[j],
        # <M>
        for j in range(rfrac.size): 
            print "%.8e " % mlagr[j],
        for j in range(rfrac.size): 
            print "%.8e " % mslagr[j],
        for j in range(rfrac.size): 
            print "%.8e " % mblagr[j],
        # N
        for j in range(rfrac.size): 
            print "%d " % nlagr[j],
        for j in range(rfrac.size): 
            print "%d " % nslagr[j],
        for j in range(rfrac.size): 
            print "%d " % nblagr[j],
        # Mb in R_lagr
        for j in range(rfrac.size): 
            print "%.8e " % msblagr[j],
        # Nb in R_lagr
        for j in range(rfrac.size): 
            print "%d " % nsblagr[j],
        # <V>
        for j in range(rfrac.size):
            print "%.8e " % vlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vblagr[j],
        # <V_x>
        for j in range(rfrac.size):
            print "%.8e " % vxlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vxslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vxblagr[j],
        # <V_y>
        for j in range(rfrac.size):
            print "%.8e " % vylagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vyslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vyblagr[j],
        # <V_z>
        for j in range(rfrac.size):
            print "%.8e " % vzlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vzslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vzblagr[j],
        # <V_r>
        for j in range(rfrac.size):
            print "%.8e " % vrlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vrslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vrblagr[j],
        # <V_t>
        for j in range(rfrac.size):
            print "%.8e " % vtlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vtslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vtblagr[j],
        # Sigma^2
        for j in range(rfrac.size):
            print "%.8e " % siglagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigblagr[j],
        # Sigma_x^2
        for j in range(rfrac.size):
            print "%.8e " % sigxlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigxslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigxblagr[j],
        # Sigma_y^2
        for j in range(rfrac.size):
            print "%.8e " % sigylagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigyslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigyblagr[j],
        # Sigma_z^2
        for j in range(rfrac.size):
            print "%.8e " % sigzlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigzslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigzblagr[j],
        # Sigma_r^2
        for j in range(rfrac.size):
            print "%.8e " % sigrlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigrslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigrblagr[j],
        # Sigma_t^2
        for j in range(rfrac.size):
            print "%.8e " % sigtlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigtslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigtblagr[j],
        # v_rot
        for j in range(rfrac.size):
            print "%.8e " % vrotlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vrotslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % vrotblagr[j],
        # Sigma_rot^2
        for j in range(rfrac.size):
            print "%.8e " % sigrotlagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigrotslagr[j],
        for j in range(rfrac.size):
            print "%.8e " % sigrotblagr[j],
        # Primordial Mb in R_lagr
        for j in range(rfrac.size): 
            print "%.8e " % mspblagr[j],
        # Primrodial Nb in R_lagr
        for j in range(rfrac.size): 
            print "%d " % nspblagr[j],
        print " " 

#   Close current snapshot
    if (hdflag): f.close()

#    fw.write(str(rlagr)+str(rslagr)+str(rblagr)+str(mlagr)+str(mslagr)+str(mblagr)+str(nlagr)+str(nslagr)+str(nblagr))
#fw.close()

