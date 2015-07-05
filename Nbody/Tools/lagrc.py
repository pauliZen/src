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
# 13. lagrlib  liblagr.so path

import numpy as np
import h5py
import math
import ctypes
import sys
from ctypes import *

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
Tint  = 0.125
# resolution of time interval in NB unit
Tres  = 0.125
# liblagr path
lagrlib = "/home/lwang/lib/liblagr.so"

larg=len(sys.argv)
if (larg==14):
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
    lagrlib= sys.argv[13]

fl = open(filename,'r')
path = fl.read()
path = path.splitlines()

#rfrac=np.array([0.001,0.003,0.005,0.01,0.03,0.05,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.95,0.99,1.0])
# More useful fraction:
rfrac=np.array([0.001,0.01,0.1,0.3,0.5,0.7,0.9,1.0]).astype('float')

# Safe x/y function:
fxovery = lambda x,y: 0.0 if float(y)==0.0 else x/y

linec = 0
ifirst = True
toffset = 0.0

# Whether average from center to shell or between shells
# flag_s = False
def get_lagr():
    dll = ctypes.CDLL(lagrlib,mode=ctypes.RTLD_GLOBAL)
    func = dll.lagr
    func.argtypes = [c_float, c_int, c_int, c_int, c_bool, c_bool,
                     POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float),
                     POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_int), POINTER(c_int),
                     POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float),POINTER(c_float), POINTER(c_float)]
    return func

__c_lagr=get_lagr()

def c_lagr(t,ns,nb,nm,fs,fb,m,x1,x2,x3,v1,v2,v3,bm1,bm2,bx1,bx2,bx3,bv1,bv2,bv3,bn1,bn2,mm1,mm2,mm3,mx1,mx2,mx3,mv1,mv2,mv3):
    mc = m.ctypes.data_as(POINTER(c_float))
    x1c = x1.ctypes.data_as(POINTER(c_float))
    x2c = x2.ctypes.data_as(POINTER(c_float))
    x3c = x3.ctypes.data_as(POINTER(c_float))
    v1c = v1.ctypes.data_as(POINTER(c_float))
    v2c = v2.ctypes.data_as(POINTER(c_float))
    v3c = v3.ctypes.data_as(POINTER(c_float))
    bm1c = bm1.ctypes.data_as(POINTER(c_float))
    bm2c = bm2.ctypes.data_as(POINTER(c_float))
    bx1c = bx1.ctypes.data_as(POINTER(c_float))
    bx2c = bx2.ctypes.data_as(POINTER(c_float))
    bx3c = bx3.ctypes.data_as(POINTER(c_float))
    bv1c = bv1.ctypes.data_as(POINTER(c_float))
    bv2c = bv2.ctypes.data_as(POINTER(c_float))
    bv3c = bv3.ctypes.data_as(POINTER(c_float))
    bn1c = bn1.ctypes.data_as(POINTER(c_int))
    bn2c = bn2.ctypes.data_as(POINTER(c_int))
    mm1c = mm1.ctypes.data_as(POINTER(c_float))
    mm2c = mm2.ctypes.data_as(POINTER(c_float))
    mm3c = mm3.ctypes.data_as(POINTER(c_float))
    mx1c = mx1.ctypes.data_as(POINTER(c_float))
    mx2c = mx2.ctypes.data_as(POINTER(c_float))
    mx3c = mx3.ctypes.data_as(POINTER(c_float))
    mv1c = mv1.ctypes.data_as(POINTER(c_float))
    mv2c = mv2.ctypes.data_as(POINTER(c_float))
    mv3c = mv3.ctypes.data_as(POINTER(c_float))
    __c_lagr(t,ns,nb,nm,fs,fb,mc,x1c,x2c,x3c,v1c,v2c,v3c,bm1c,bm2c,bx1c,bx2c,bx3c,bv1c,bv2c,bv3c,bn1c,bn2c,mm1c,mm2c,mm3c,mx1c,mx2c,mx3c,mv1c,mv2c,mv3c)

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

        mm1  = np.array([])
        mm2  = np.array([])
        mm3  = np.array([])
        mxc1 = np.array([])
        mxc2 = np.array([])
        mxc3 = np.array([])
        mvc1 = np.array([])
        mvc2 = np.array([])
        mvc3 = np.array([])
        mk1  = np.array([])
        mk2  = np.array([])
        mk3  = np.array([])

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
        mass = mass.astype(np.float32)
        x1 = x1.astype(np.float32)
        x2 = x2.astype(np.float32)
        x3 = x3.astype(np.float32)
        v1 = v1.astype(np.float32)
        v2 = v2.astype(np.float32)
        v3 = v3.astype(np.float32)
        bm1 = bm1.astype(np.float32)
        bm2 = bm2.astype(np.float32)
        bxc1 = bxc1.astype(np.float32)
        bxc2 = bxc2.astype(np.float32)
        bxc3 = bxc3.astype(np.float32)
        bvc1 = bvc1.astype(np.float32)
        bvc2 = bvc2.astype(np.float32)
        bvc3 = bvc3.astype(np.float32)
        bn1 = bn1.astype(np.int)
        bn2 = bn2.astype(np.int)
        mm1 = mm1.astype(np.float32)
        mm2 = mm2.astype(np.float32)
        mm3 = mm3.astype(np.float32)
        mxc1 = mxc1.astype(np.float32)
        mxc2 = mxc2.astype(np.float32)
        mxc3 = mxc3.astype(np.float32)
        mvc1 = mvc1.astype(np.float32)
        mvc2 = mvc2.astype(np.float32)
        mvc3 = mvc3.astype(np.float32)
###        print x1[0],x2[0],x3[0],x1[N_SINGLE-1],x2[N_SINGLE-1],x3[N_SINGLE-1],N_SINGLE,bn2[N_BINARY-1]
        c_lagr(time,N_SINGLE,N_BINARY,N_MERGER,fshell,fbres,mass,x1,x2,x3,v1,v2,v3,bm1,bm2,bxc1,bxc2,bxc3,bvc1,bvc2,bvc3,bn1,bn2,mm1,mm2,mm3,mxc1,mxc2,mxc3,mvc1,mvc2,mvc3)
#   Close current snapshot
    if (hdflag): f.close()

#    fw.write(str(rlagr)+str(rslagr)+str(rblagr)+str(mlagr)+str(mslagr)+str(mblagr)+str(nlagr)+str(nslagr)+str(nblagr))
#fw.close()

