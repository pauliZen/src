import numpy as np
import math
import random as ran

data = np.loadtxt('data_multi')
kk = 0
while (kk < data.size/data[1].size):
    for j in range(18):
        print "%lg " % data[kk,j],
    for j in range(2):
        print "%d " % data[kk,j+18],
    for j in range(8):
        print "%lg " % data[kk,j+20],
    print ""
    kk += 1 
