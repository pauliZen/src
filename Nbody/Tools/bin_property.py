import numpy as np
import matplotlib.pyplot as plt
import math
from matplotlib.colors import BoundaryNorm
from matplotlib.ticker import MaxNLocator

bm1,bm2,be,bp,ba = np.loadtxt('bdat',unpack=True,usecols=(2,3,5,6,7),skiprows=4)

#n_bins = 30
norm=np.array([True,False])
for kk in norm:
    fig, axes = plt.subplots(nrows=2, ncols=2)
    ax0, ax1, ax2, ax3 = axes.flat

#size of image
    figcf = plt.gcf()
    figcf.set_size_inches(14,8)

    # semi
    binwidth=0.1
    bin=np.arange(np.log10(min(ba)), np.log10(max(ba)) + binwidth, binwidth)
    ax0.hist(np.log10(ba),                        bins=bin, histtype='bar', color='red',  label='All' , normed=kk)
    ax0.hist(np.log10(ba[((bm1<5) & (bm2<5))]),   bins=bin, histtype='bar', color='green',label='M<5' , normed=kk)
    ax0.hist(np.log10(ba[((bm1>=5) | (bm2>=5))]), bins=bin, histtype='bar', color='blue', label='M>=5', normed=kk)
    ax0.legend(prop={'size': 10})
    ax0.set_xlabel('log(Semi[AU])')
     
    # eccentricity
    binwidth=0.05
    bin=np.arange(min(be), max(be) + binwidth, binwidth)
    ax1.hist(be,                        bins=bin, histtype='bar', color='red',  label='All' , normed=kk)
    ax1.hist(be[((bm1<5) & (bm2<5))],   bins=bin, histtype='bar', color='green',label='M<5' , normed=kk)
    ax1.hist(be[((bm1>=5) | (bm2>=5))], bins=bin, histtype='bar', color='blue', label='M>=5', normed=kk)
    ax1.legend(prop={'size': 10})
    ax1.set_xlabel('Ecc')
     
    # Period
    binwidth=0.1
    bin=np.arange(np.log10(min(bp)), np.log10(max(bp)) + binwidth, binwidth)
    ax2.hist(np.log10(bp),                       bins=bin, histtype='bar', color='red',  label='All' , normed=kk)
    ax2.hist(np.log10(bp[((bm1<5) & (bm2<5))]),  bins=bin, histtype='bar', color='green',label='M<5' , normed=kk)
    ax2.hist(np.log10(bp[((bm1>=5) | (bm2>=5))]),bins=bin, histtype='bar', color='blue', label='M>=5', normed=kk)
    ax2.legend(prop={'size': 10})
    ax2.set_xlabel('log(Period[days])')
     
    # M2/M1
    q=np.array(map(lambda x,y: min(x/y,y/x), bm1, bm2))
    binwidth=0.05
    bin=np.arange(min(q), max(q) + binwidth, binwidth)
    ax3.hist(q,                       bins=bin, histtype='bar', color='red',  label='All' , normed=kk)
    ax3.hist(q[((bm1<5) & (bm2<5))],  bins=bin, histtype='bar', color='green',label='M<5' , normed=kk)
    ax3.hist(q[((bm1>=5) | (bm2>=5))],bins=bin, histtype='bar', color='blue', label='M>=5', normed=kk)
    ax3.legend(prop={'size': 10})
    ax3.set_xlabel('M2/M1 (M2<=M1)')
     
        
    plt.tight_layout()
    title = 'bin'
    if (kk): title=title+'_normal'
    plt.savefig(title+'.eps')
    plt.close(fig)
