import numpy as np

import sys
filename='sbp'
fout='sbp_color'

narg=len(sys.argv)
if (narg>=2):
    filename=sys.argv[1]
    if (filename == '-h'):
        print 'arguments: datalist[sbp] dataout[sbp_ave]'
        quit()
if (narg>=3):
    fout=sys.argv[2]

rpc, rarcv, rmagv, rmagvm, rmlowv, rmupv=np.loadtxt(filename+'.V',unpack=True,usecols=(0,4,5,6,7,8),skiprows=1)
rarci, rmagi, rmagim, rmlowi, rmupi=np.loadtxt(filename+'.I',unpack=True,usecols=(4,5,6,7,8),skiprows=1)
rarcb, rmagb, rmagbm, rmlowb, rmupb=np.loadtxt(filename+'.B',unpack=True,usecols=(4,5,6,7,8),skiprows=1)

if (rarcv!=rarci).all(): print 'Warning! R[arc] did not match for V and I'
if (rarcv!=rarcb).all(): print 'Warning! R[arc] did not match for V and B'

rbv=rmagb-rmagv
rbvm=rmagbm-rmagvm
rbvlow=rbv+np.sqrt((rmagb-rmlowb)**2+(rmagv-rmlowv)**2)
rbvup=rbv-np.sqrt((rmagb-rmupb)**2+(rmagv-rmupv)**2)
rvi=rmagv-rmagi
rvim=rmagvm-rmagim
rvilow=rvi+np.sqrt((rmagv-rmlowv)**2+(rmagi-rmlowi)**2)
rviup=rvi-np.sqrt((rmagv-rmupv)**2+(rmagi-rmupi)**2)

fhandle=open(fout,'w')
np.savetxt(fhandle,
           np.transpose((rpc,rarcv,rbv,rbvm,rbvlow,rbvup,rvi,rvim,rvilow,rviup)),
           fmt="%f %f %f %f %f %f %f %f %f %f",
           header="r[pc] r[arcsec] B-V[mag/arcsec^2](average) B-V[mag/arcsec^2](median) low[mag/arcsec^2] up[mag/arcsec^2] V-I[mag/arcsec^2](average) V-I[mag/arcsec^2](median) low[mag/arcsec^2] up[mag/arcsec^2]",
           comments='')
