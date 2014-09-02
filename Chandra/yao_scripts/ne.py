#!/usr/bin/env python


import math
import sys

beta=float(sys.argv[1])
n0=float(sys.argv[2])
rc=float(sys.argv[3])
n=open('ne-model.qdp','w')
for r in range(1,1000):
    ne=n0*pow(1+pow(r/rc,2),-1.5*beta)
    n.write(`r`+' '+`ne`+'\n')
    print r,ne
n.close()
