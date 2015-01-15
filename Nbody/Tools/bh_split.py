#split the bh particle data in sorted list by bh_stat.sh
import numpy as np
import sys

#filename=sys.stdin.readlines()
filename='bh_single.1004.00000000'
data = np.loadtxt(filename)
num=data.size/data[0].size
print num

k=0
while (k<num):
    if (k==0): 
        last=data[k][0]
    else:
        if(last!=data[k][0]):
            last=data[k][0]
            print ""
            print ""
        lnum=data[k].size
        j=0
        while (j<lnum):
            print data[k][j],
            j+=1
        print ""
    k +=1

