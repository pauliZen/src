import numpy as np
import ctypes
import sys

def get_sd():
    dll = ctypes.CDLL("/u/longw/lib/libsurfacedensity.so",mode=ctypes.RTLD_GLOBAL)
    func = dll.surfacedensity
    func.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float),
                     ctypes.c_int, ctypes.c_float, ctypes.c_float,
                     ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_float)]
    return func

__sd=get_sd()

def sd(n,x,y,w,m,nbin,rmax,rmin,rshell,rden,rm,ncount,rarea):
    xp  = x.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    yp  = y.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    wp  = w.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    mp  = m.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    rsp = rshell.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    rdp = rden.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    rmp = rm.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    ncp = ncount.ctypes.data_as(ctypes.POINTER(ctypes.c_int))
    rap = rarea.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    __sd(n,xp,yp,wp,mp,nbin,rmax,rmin,rsp,rdp,rmp,ncp,rap)


larg=len(sys.argv)

filename='data_prj'
fout='sb'
filter='V'
rs=10
rmax=20
rmin=0.05
nbins=15

msun=4.83

if (larg>=2):
    filename=sys.argv[1]
    if (filename == '-h'):
        print 'arguments: filename[data_prj] filter[V] rmax[20pc] nbins[15] rmin[0.05pc] fileout[sb] distance[pc]'
        quit()
if (larg>=3):
    filter=sys.argv[2]
if (larg>=4):
    rmax=float(sys.argv[3])
if (larg>=5):
    nbins=int(sys.argv[4])
if (larg>=6):
    rmin=float(sys.argv[5])
if (larg>=7):
    fout=sys.argv[6]
if (larg>=8):
    rs=float(sys.argv[7])

fcol=18
if (filter=='I'): fcol=21
if (filter=='B'): fcol=20

x,y,m1,m2,mag = np.loadtxt(filename,usecols=(1,2,9,10,fcol-1),unpack=True)

##dm=5.0*np.log10(rs)-5.0

xp=x.astype(np.float32)
yp=y.astype(np.float32)
lp=(10.0**(0.4*(msun-mag))).astype(np.float32)
print 'sum %f' % lp.sum()
mp=(m1+m2).astype(np.float32)

rshell=np.zeros(nbins).astype(np.float32)
rden=np.zeros(nbins).astype(np.float32)
rm=np.zeros(nbins).astype(np.float32)
ncount=np.zeros(nbins).astype(np.int32)
rarea=np.zeros(nbins).astype(np.float32)

sd(mag.size,xp,yp,lp,mp,nbins,rmax,rmin,rshell,rden,rm,ncount,rarea)

rmag=msun+21.572-2.5*np.log10(rden)
rarc=rshell/rs*206264.806

fhandle=open(fout,'w')
np.savetxt(fhandle, np.transpose((rshell,rden,rarc,rmag,ncount,rm,rarea)),fmt="%f %f %f %f %d %f %f",header="r[pc] surface_brightness[L_{sun}/pc^2] r[arcsec] surface_brigtness[mag/arcsec^2] surface_number_density[1/pc^2] surface_mass_density[M_sun/pc^2] area[pc^2]",comments='')
fhandle.close()
