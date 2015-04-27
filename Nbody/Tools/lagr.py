# Lagrangian radii, average mass, number, velocity, radial/tangential velocity, velocity dispersion, radial/tangential velocity dispersion, x/y/z velocity dispersion, rotational velocity
# Parameters are calculated from center to R_lagr
# For average mass, binaries/mergers are resolved
# For velocity and dispersion, binaries/mergers are not resolved.

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

# Whether average from center to shell or between shells
# flag_s = False

print "## Time; 100 groups of data; offset %d " % rfrac.size

print "Time[NB] ",
for i in range(53):
    for j in range(rfrac.size): 
        print "%.2e " % rfrac[j],
print " "

for i in path:
    f = h5py.File(i,'r')
    tots = len(f.items())

    kj = 0
    while (kj<tots):

        s = f.items()[kj][1]
        kj += 1

        time = float(s.attrs['Time'])

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
            else:
                bflag = False

        mflag = 'Mergers' in map(lambda x:x[0], s.items())

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

#  Binary mass/number inside different R_lagr
        msblagr=np.zeros(rfrac.size)
        nsblagr=np.zeros(rfrac.size)

# counter for different R_lagr bins
        kk = 0
        kks = 0
        kkb = 0

#   Number counter
        nc = 0
        ncs = 0
        ncb = 0

#   Mass counter
        cmass = 0
        bmass = 0
        smass = 0

#  Get time
        time = float(s.attrs['Time'])

#  Single and binary number
        N_SB = N_SINGLE + N_BINARY

#  Initialize the velocity vectors
        N_TOT = N_SB + N_MERGER
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
                # increase total counter by one in binary case
                nc += 1
                # increase binary counter by two 
                ncb += 2
#   Merger case
                
                if (j>=N_SB):
                    # increase total counter by one in merger case
                    nc += 1
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

                #  average velocity
                vxblagr[kkb] += mmb[j]*vx[j] 
                vyblagr[kkb] += mmb[j]*vy[j] 
                vzblagr[kkb] += mmb[j]*vz[j] 
                vrblagr[kkb] += mmb[j]*vr[j] 
                vtbave[kkb] += mmb[j]*vt[j] 
                vrotblagr[kkb] += mmb[j]*vrot[j]


                # increase mass/number counter for binaries in R_lagr
                msblagr[kk] += mmb[j]
                nsblagr[kk] += 2

                # Go to next bin if mass reach the R_Lagr limit
                if (bmass >= rbmass[kkb]):
                    # update mass
                    rbmass[kkb] = bmass
                    # Get R_lagr for binary
                    rblagr[kkb] = ri
                    # Get number for binary
                    nblagr[kkb] = ncb
                    # Increase bin index
                    kkb += 1
                    # initial next bins
                    if (kkb < rfrac.size):
                        if(nblagr[kkb] == 0):
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
                    kkb = min(kkb,rfrac.size-1)
            else:
                # Add mass
                smass += mmb[j]

                #  average velocity
                vxslagr[kks] += mmb[j]*vx[j] 
                vyslagr[kks] += mmb[j]*vy[j] 
                vzslagr[kks] += mmb[j]*vz[j] 
                vrslagr[kks] += mmb[j]*vr[j] 
                vtsave[kks] += mmb[j]*vt[j] 
                vrotslagr[kks] += mmb[j]*vrot[j]

                # Go to next bin if mass reach the R_lagr limit
                if (smass >= rsmass[kks]):
                    # update mass
                    rsmass[kks] = smass
                    # Get R_lagr for single
                    rslagr[kks] = ri
                    # Get number for single
                    nslagr[kks] = ncs
                    # increase bin index
                    kks += 1
                    # initial next bins
                    if (kks < rfrac.size):
                        if(nslagr[kks] == 0):
                            vxslagr[kks] = vxslagr[kks-1]
                            vyslagr[kks] = vyslagr[kks-1]
                            vzslagr[kks] = vzslagr[kks-1]
                            vrslagr[kks] = vrslagr[kks-1]
                            vtsave[kks] = vtsave[kks-1]
                            vrotslagr[kks] = vrotslagr[kks-1]
                    # Avoid overflow of bin index
                    kks = min(kks,rfrac.size-1)
            
#   Go to next R_lagr if mass reach limit
            cmass += mmb[j]
            #  average velocity
            vxlagr[kk] += mmb[j]*vx[j] 
            vylagr[kk] += mmb[j]*vy[j] 
            vzlagr[kk] += mmb[j]*vz[j] 
            vrlagr[kk] += mmb[j]*vr[j] 
            vtave[kk] += mmb[j]*vt[j] 
            vrotlagr[kk] += mmb[j]*vrot[j]


            if (cmass >= rmass[kk]):
                # update mass
                rmass[kk] = cmass
                # Get R_lagr 
                rlagr[kk] = ri
                # Get number
                nlagr[kk] = nc
                # increase bin index
                kk += 1
                # Get initial value for next bin 
                if (kk < rfrac.size ):
                    # binary counter
                    if (nsblagr[kk] == 0):
                        msblagr[kk] = msblagr[kk-1]
                        nsblagr[kk] = nsblagr[kk-1]
                    # total counter
                    if (nlagr[kk] == 0):
                        vxlagr[kk] = vxlagr[kk-1]
                        vylagr[kk] = vylagr[kk-1]
                        vzlagr[kk] = vzlagr[kk-1]
                        vrlagr[kk] = vrlagr[kk-1]
                        vtave[kk] = vtave[kk-1]
                        vrotlagr[kk] = vrotlagr[kk-1]
                # Avoid overflow of bin index
                kk = min(kk,rfrac.size-1)

#   Fill empty bins with neighbor bin values
#   Total
        kn = kk - 1
        while (kk < rfrac.size):
            rlagr[kk] = rlagr[kn]
            nlagr[kk] = nlagr[kn]
            nsblagr[kk] = nsblagr[kn]
            msblagr[kk] = msblagr[kn]
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
        mlagr  = rmass/nlagr
        mslagr = rsmass/nslagr
        mblagr = rbmass/nblagr
#   Average velocity
        # total
        vxlagr  = vxlagr/rmass
        vylagr  = vylagr/rmass
        vzlagr  = vzlagr/rmass
        vlagr   = map(math.sqrt,vxlagr*vxlagr + vylagr*vylagr + vzlagr*vzlagr)
        vrlagr  = vrlagr/rmass
        vtave   = map(lambda x,y:x/y,vtave,rmass)
        vtlagr  = map(lambda x: math.sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]), vtave)
        vrotlagr= vrotlagr/rmass
        #single
        vxslagr  = vxslagr  /rsmass
        vyslagr  = vyslagr  /rsmass
        vzslagr  = vzslagr  /rsmass
        vslagr   = map(math.sqrt,vxslagr*vxslagr + vyslagr*vyslagr + vzslagr*vzslagr)
        vrslagr  = vrslagr  /rsmass
        vtsave   = map(lambda x,y:x/y,vtsave,rsmass)
        vtslagr  = map(lambda x: math.sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]), vtsave)
        vrotslagr= vrotslagr/rsmass
        #binary/merger
        if(bflag):
            vxblagr  = vxblagr  /rbmass
            vyblagr  = vyblagr  /rbmass
            vzblagr  = vzblagr  /rbmass
            vblagr   = map(math.sqrt,vxblagr*vxblagr + vyblagr*vyblagr + vzblagr*vzblagr)
            vrblagr  = vrblagr  /rbmass
            vtbave   = map(lambda x,y:x/y,vtbave,rbmass)
            vtblagr  = map(lambda x: math.sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]), vtbave)
            vrotblagr= vrotblagr/rbmass
    
#   Loop again to get velocity dispersion
#   counter for different R_lagr bins
        kk = 0
        kks = 0
        kkb = 0
#   Number counter
        nc = 0
        ncs = 0
        ncb = 0
#
        for j in idx:
            #  increase total counter
            nc += 1
#   Binary/merger case
            if (j>=N_SINGLE):
                # increase total counter by one in binary case
                nc += 1
                # increase binary counter by two 
                ncb += 2
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
                if (ncb==nblagr[kkb]):
                    kkb += 1
                    if (kkb < rfrac.size):
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
                if (ncs==nslagr[kks]):
                    kks += 1
                    if (kks < rfrac.size):
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
            if (nc==nlagr[kk]):
                kk += 1
                if (kk < rfrac.size):
                    sigxlagr[kk] = sigxlagr[kk-1]
                    sigylagr[kk] = sigylagr[kk-1]
                    sigzlagr[kk] = sigzlagr[kk-1]
                    sigrlagr[kk] = sigrlagr[kk-1]
                    sigtlagr[kk] = sigtlagr[kk-1]
                    sigrotlagr[kk] = sigrotlagr[kk-1]
        
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
        sigxlagr  = sigxlagr  /rmass
        sigylagr  = sigylagr  /rmass
        sigzlagr  = sigzlagr  /rmass
        siglagr   = sigxlagr + sigylagr + sigzlagr
        sigrlagr  = sigrlagr  /rmass
        sigtlagr  = sigtlagr  /rmass
        sigrotlagr= sigrotlagr/rmass
        #single
#        sigslagr   = sigslagr   /(rsmass*3.0)
        sigxslagr  = sigxslagr  /rsmass
        sigyslagr  = sigyslagr  /rsmass
        sigzslagr  = sigzslagr  /rsmass
        sigslagr   = sigxslagr + sigyslagr + sigzslagr
        sigrslagr  = sigrslagr  /rsmass
        sigtslagr  = sigtslagr  /rsmass
        sigrotslagr= sigrotslagr/rsmass
        #binary/merger
#        sigblagr   = sigblagr   /(rbmass*3.0)
        if(bflag):
            sigxblagr  = sigxblagr  /rbmass
            sigyblagr  = sigyblagr  /rbmass
            sigzblagr  = sigzblagr  /rbmass
            sigblagr   = sigxblagr + sigyblagr + sigzblagr
            sigrblagr  = sigrblagr  /rbmass
            sigtblagr  = sigtblagr  /rbmass
            sigrotblagr= sigrotblagr/rbmass


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
        print " " 

#   Close current snapshot
    f.close()

#    fw.write(str(rlagr)+str(rslagr)+str(rblagr)+str(mlagr)+str(mslagr)+str(mblagr)+str(nlagr)+str(nslagr)+str(nblagr))
#fw.close()

