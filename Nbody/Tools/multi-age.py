import numpy as np
import math
import random as ran

fl = open('data.lst','r')
lst = fl.read()
lst = np.array(lst.splitlines())

tnum=1000000
pnum=tnum/lst.size
print 'Total number = %d, Total snapshot = %d, Data per snap. = %d ' % (tnum,lst.size,pnum)

ns = 0
nb = 0

for i in lst:
    data = np.loadtxt(i)
    kk = 0
    while (kk < pnum):
        kk += 1
        ind=ran.randrange(0,data.size/data[1].size,1)
        if (data[ind,13] > 0 ): nb += 1
        else: ns += 1
        for j in data[ind]:
            print j,
        print ""

print "Ns = %d, Nb = %d" % (ns,nb)
