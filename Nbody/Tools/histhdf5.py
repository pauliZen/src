import numpy as np
import math
import matplotlib as mpl
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import h5py

filename = 'snap.40_0.h5part'
step = '/Step#0'

f = h5py.File(filename,'r')

s = f[step]

b = s['Binaries']

# binary information: Semi-major axis
a = b['A']
p = b['P']
e = b['ECC']

fig, axes = plt.subplots(nrows=2,ncols=2)
ax0, ax1, ax2, ax3 = axes.flat

ax0.hist(map(math.log10,a),100,histtype='bar')
ax0.set_title('Log(semi[AU])')

ax1.hist(map(math.log10,p),100,histtype='bar')
ax1.set_title('Log(P[days])')

ax2.hist(e,100,histtype='bar')
ax2.set_title('Ecc')

plt.tight_layout()

plt.show()
