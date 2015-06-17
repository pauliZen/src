import numpy as np

import sys
filename='sb.data'
time=0.0

narg=len(sys.argv)
if (narg>=2):
    filename=sys.argv[1]
    if (filename == '-h'):
        print 'arguments: datafile[sb.data] Time[0.0]'
        quit()
if (narg>=3):
    time=float(sys.argv[2])


rshell, rden, rm =np.loadtxt(filename,unpack=True,usecols=(0,1,5),skiprows=1)
for j in range(rden.size):
    if (rden[j]<0.5*rden[0]):
        a=rden[j-1]/rden[0]
        b=rden[j]/rden[0]
        rcl=((0.5-b)*rshell[j-1]+(a-0.5)*rshell[j])/(a-b)
        break
for j in range(rm.size):
    if (rm[j]<0.5*rm[0]):
        a=rm[j-1]/rm[0]
        b=rm[j]/rm[0]
        rcm=((0.5-b)*rshell[j-1]+(a-0.5)*rshell[j])/(a-b)
        break

print "%f %f %f" % (time,rcl,rcm)
