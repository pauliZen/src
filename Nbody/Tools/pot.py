import numpy as np
import matplotlib.pyplot as plt
import h5py
import math
import ctypes
import sys
from ctypes import *


fl = open('snap.lst','r')
path = fl.read()
path = path.splitlines()

def sdot(x1,x2,x3):
    return math.sqrt(x1*x1+x2*x2+x3*x3)

rc=4.26647367e-01
tscale=0.622
rscale=9.375
mscale=474603

# extract cuda function pointer in the shared object *.so
# def get_gpupot():
#     dll = ctypes.CDLL("/home/lwang/lib/libgpupot.so",mode=ctypes.RTLD_GLOBAL)
#     func = dll.gpupot
#     func.argtypes = [c_int, POINTER(c_int), POINTER(c_double)]
#     return func
#  
# def get_gpupot_send_float():
#     dll = ctypes.CDLL("/home/lwang/lib/libgpupot.so",mode=ctypes.RTLD_GLOBAL)
#     func = dll.gpupot_send_float
#     func.argtypes = [c_int, POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float)]
#     return func
#  
# # create __gpupot function with get_gpupot()
# __gpupot = get_gpupot()
# __gpupot_send = get_gpupot_send_float()
#  
# # convenient python wrapper for __gpupot
# # it does all job with types convertation
# # from python ones to C++ ones 
# def gpupot(ni, lst, pot):
#     lst_p = lst.ctypes.data_as(POINTER(c_int))
#     pot_p = pot.ctypes.data_as(POINTER(c_double))
#     __gpupot(ni, lst_p, pot_p)
#  
# def gpupot_send(n, m, x1, x2, x3):
#     m_p = m.ctypes.data_as(POINTER(c_float))
#     x1_p = x1.ctypes.data_as(POINTER(c_float))
#     x2_p = x2.ctypes.data_as(POINTER(c_float))
#     x3_p = x3.ctypes.data_as(POINTER(c_float))
#     __gpupot_send(n, m_p, x1_p, x2_p, x3_p)
  
#def get_potavx():
#    dll = ctypes.CDLL("/home/lwang/lib/libpot.avx.so",mode=ctypes.RTLD_GLOBAL)
#    func = dll.gpupot
#    func.argtypes = [c_int, POINTER(c_int), c_int,  POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_double)]
#    return func
# 
## create __gpupot function with get_gpupot()
#__potavx = get_potavx()
# 
## convenient python wrapper for __gpupot
## it does all job with types convertation
## from python ones to C++ ones 
#def potavx(ni, lst, n, m, x1, x2, x3, pot):
#    lst_p = lst.ctypes.data_as(POINTER(c_int))
#    m_p  =  m.ctypes.data_as(POINTER(c_float))
#    x1_p = x1.ctypes.data_as(POINTER(c_float)) 
#    x2_p = x2.ctypes.data_as(POINTER(c_float)) 
#    x3_p = x3.ctypes.data_as(POINTER(c_float)) 
#    pot_p = pot.ctypes.data_as(POINTER(c_double))
#    __potavx(ni, lst_p, n, m_p, x1_p, x2_p, x3_p, pot_p)
 
# lst=np.array([10,12,14]).astype('int')
# #x=np.array(map(lambda x,y,z: np.array([x,y,z]), x1,x2,x3))
# pot=np.zeros(x1.size).astype('double')
#  
# print mass[0],x1[0],x2[0],x3[0]
#  
# gpupot_send(x1.size,mass,x1,x2,x3)
# gpupot(3,lst,pot)
#  
# print pot


for i in path:
    f = h5py.File(i,'r')
    tots = len(f.items())
#    st=map(lambda x:x[1], f.items())
    
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
     
        
#        xi1=np.zeros(x1.size/10)
#        xi2=np.zeros(x1.size/10)
#        xi3=np.zeros(x1.size/10)
#        mi=np.zeros(x1.size/10)
#        kwi=np.zeros(x1.size/10)
#        ni=np.zeros(x1.size/10).astype('int')
        inxi=np.zeros(x1.size/10).astype('int')
         
        nc = 0
        ncs = 0
         
        k=0
        while (k<x1.size):
            dis=sdot(x1[k],x2[k],x3[k])
            if (dis<=rc):
#                xi1[nc] = x1[k]
#                xi2[nc] = x2[k]
#                xi3[nc] = x3[k]
#                mi[nc]  = mass[k]
#                kwi[nc] = kw[k]
                inxi[nc] = k
#                ni[nc] = n[k]
                nc += 1
                ncs += 1
            k +=1
         
        ncsb = ncs
         
        if (bflag):
            kb=0
            while (kb<bxc1.size):
                dis=sdot(bxc1[kb],bxc2[kb],bxc3[kb])
                if (dis<=rc):
#                   xi1[nc] = bxc1[kb]
#                   xi2[nc] = bxc2[kb]
#                   xi3[nc] = bxc3[kb]
#                   mi[nc]  = bm1[kb]+bm2[kb]
#                   kwi[nc] = -1
                    inxi[nc] = kb + N_SINGLE
#                    ni[nc] = bnc[kb]
                    nc += 1
                    ncsb += 1
                kb += 1

        if (mflag):    
            km=0
            while (km<mxc1.size):
                dis=sdot(mxc1[km],mxc2[km],mxc3[km])
                if (dis<=rc):
#                    xi1[nc] = mxc1[km]
#                    xi2[nc] = mxc2[km]
#                    xi3[nc] = mxc3[km]
#                    mi[nc]  = mm1[km]+mm2[km]+mm3[km]
#                    kwi[nc] = -2
                    inxi[nc] = km + N_SINGLE + N_BINARY
#                    ni[nc] = mnc[km]
                    nc += 1
                km += 1

        phi=np.zeros(nc).astype('double')
#        xi = map(lambda x,y,z: np.array([x,y,z]), x1,x2,x3)
        if(bflag):
#            xi = np.append(xi,map(lambda x,y,z: np.array([x,y,z]), bxc1,bxc2,bxc3))
            xi1 = np.append(x1,bxc1)/rscale
            xi2 = np.append(x2,bxc2)/rscale
            xi3 = np.append(x3,bxc3)/rscale
            mi = np.append(mass,bm1+bm2)/mscale
        else:
            xi1 = x1/rscale
            xi2 = x2/rscale
            xi3 = x3/rscale
            mi = mass/mscale
        if(mflag):
#            xi = np.append(xi,map(lambda x,y,z: np.array([x,y,z]), mxc1,mxc2,mxc3))
            xi1 = np.append(xi1,mxc1/rscale) 
            xi2 = np.append(xi2,mxc2/rscale) 
            xi3 = np.append(xi3,mxc3/rscale) 
            mi = np.append(mi,(mm1+mm2+mm3)/mscale)
        
        totn = xi1.size

#        print 'Potential AVX, NC = ',nc, 'NCS = ',ncs, 'NCSB = ',ncsb, 'N = ',totn, 'N_SINGLE',N_SINGLE, 'N_BINARY',N_BINARY

        title = '.%.8f' % time

        fout = open('pot_data_in'+title,'w')
        fout.write('%d ' % nc)
        k=0
        while (k<nc):
            fout.write('%d '% (inxi[k]))
            k +=1
        fout.write('\n')
        k=0
        fout.write('%d %d %d %d\n' % (totn,nc,ncs,ncsb))
        while (k<totn):
            fout.write('%.8e %.8e %.8e %.8e\n' % (mi[k],xi1[k],xi2[k],xi3[k]))
            k +=1
        fout.close()
#        print 'm,x',mi[0],xi1[0],xi2[0],xi3[0]
#        print 'm,x',mi[1],xi1[1],xi2[1],xi3[1]
#        print 'm,x',mi[mi.size-1],xi1[mi.size-1],xi2[mi.size-1],xi3[mi.size-1]
#        potavx(nc,inxi,totn,mass,xi1,xi2,xi3,phi)
        
#        k=0
#        while (k<x1.size):
#            ki=0
#            while (ki<nc):
#                if (inxi[ki] != k):
#                    phi[ki] += mass[k]/sdot(x1[k]-xi1[ki],x2[k]-xi2[ki],x3[k]-xi3[ki])
#                ki += 1
#            k += 1
#         
#        if (bflag):
#            kb=0
#            while (kb<bxc1.size):
#                ki=0
#                while (ki<nc):
#                    if (inxi[ki] != kb):
#                        phi[ki] += (bm1[kb]+bm[kb])/sdot(bxc1[kb]-xi1[ki],bxc2[kb]-xi2[ki],bxc3[kb]-xi3[ki])
#                    ki += 1
#                kb += 1
#         
#        if (mflag):
#            km=0
#            while (km<bxc1.size):
#                ki=0
#                while (ki<nc):
#                    if (inxi[ki] != km):
#                        phi[ki] += (mm1[km]+mm2[km]+mm3[km])/sdot(mxc1[km]-xi1[ki],mxc2[km]-xi2[ki],mxc3[km]-xi3[ki])
#                    ki += 1
#                km += 1
                
#        title = '.%.8f' % time
# 
#        print 'Write to pots',title
#        sout = open('pots'+title,'w')
#        k=0
#        while (k<ncs):
#            ik = inxi[k]
#            # name, kw(-1:binary; -2:merger), m, x1, x2, x3, pot
#            sout.write("%d %d %.8e %.8e %.8e %.8e %.8e\n" % (n[ik], kw[ik], mass[ik], x1[ik], x2[ik], x3[ik], phi[k]))
#            k += 1
#        while (k<ncsb):
#            ik = inxi[k]-ncs
#            # name, kw(-1:binary; -2:merger), m, x1, x2, x3, phi
#            sout.write("%d %d %.8e %.8e %.8e %.8e %.8e\n" % (bnc[ik], -1, bm1[ik]+bm2[ik], bxc1[ik], bxc2[ik], bxc3[ik], phi[k]))
#            k += 1
#        while (k<nc):
#            ik = inxi[k]-ncsb
#            # name, kw(-1:binary; -2:merger), m, x1, x2, x3, phi
#            sout.write("%d %d %.8e %.8e %.8e %.8e %.8e\n" % (mnc[ik], -2, mm1[ik]+mm2[ik]+mm3[ik], mxc1[ik], mxc2[ik], mxc3[ik], phi[k]))
#            k += 1
#        sout.close()
#         
#        if(bflag & (ncsb-ncs>0)):
#            print 'Write to potb',title
#            bout = open('potb'+title,'w')
#            k=0
#            while (k<ncsb-ncs):
#                # n1,n2,k1,k2,m1,m2,xc1,xc2,xc3,xr1,xr2,xr3,a,e,p,pot
#                ib=inxi[ncs+k] - ncs
#                bout.write("%d %d %d %d %.8e %.8e  %.8e %.8e %.8e  %.8e %.8e %.8e  %.8e %.8e %.8e %.8e\n" % (bn1[ib], bn2[ib], bk1[ib], bk2[ib], bm1[ib], bm2[ib], bxc1[ib], bxc2[ib], bxc3[ib], bxr1[ib], bxr2[ib], bxr3[ib], ba[ib], be[ib], bp[ib], phi[ncs+k]))
#                k += 1
#            bout.close()
# 
#        if(mflag & (nc-ncsb>0)):
#            print 'Write to potm',title
#            mout = open('potm'+title,'w')
#            k=0
#            while (k<nc-ncsb):
#                # n1,n2,n3,k1,k2,k3,m1,m2,m3,xc1,xc2,xc3,xro1,xro2,xro3,xri1,xri2,xri3,ao,ai,eo,ei,po,pi,phi
#                im=inxi[ncsb+k] - ncsb
#                mout.write("%d %d %d %d %d %d %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e\n" % (mn1[im], mn2[im], mn3[im], mk1[im], mk2[im], mk3[im], mm1[im], mm2[im], mm3[im], mxc1[im], mxc2[im], mxc3[im], mxro1[im], mxro2[im], mxro3[im], mxri1[im], mxri2[im], mxri3[im], mao[im], mai[im], meo[im], mei[im], mpo[im], mpi[im], phi[ncsb+k]))
#                k += 1
#         
#            mout.close()
#        
