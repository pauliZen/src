#Show 7 images in one figure for fits output
#preprocess: fits_trans.sh

import numpy as np

# Set up matplotlib and use a nicer set of plot parameters
import matplotlib
#from matplotlib import text
matplotlib.rc_file("matplotlibrc")
import matplotlib.pyplot as plt

import sys

from astropy.io import fits

# Log scale
from astropy.visualization import scale_image

def image_cut(image_r,image_g,image_b,offset_ratio,smooth_ratio,invert=False):
    isize=image_r.shape
    isize_min=np.min(isize)
    if (isize!=image_b.shape) | (isize!=image_g.shape):
        print 'Warning: Image size not equal!'
    image_rgba=np.zeros(shape=(isize_min,isize_min,4))
    xshift=(isize[0]-isize_min)/2
    yshift=(isize[1]-isize_min)/2
    if invert:
        image_rgba[:,:,0]=1.0-image_r[xshift:xshift+isize_min,yshift:yshift+isize_min]
        image_rgba[:,:,1]=1.0-image_g[xshift:xshift+isize_min,yshift:yshift+isize_min]
        image_rgba[:,:,2]=1.0-image_b[xshift:xshift+isize_min,yshift:yshift+isize_min]
    else:
        image_rgba[:,:,0]=image_r[xshift:xshift+isize_min,yshift:yshift+isize_min]
        image_rgba[:,:,1]=image_g[xshift:xshift+isize_min,yshift:yshift+isize_min]
        image_rgba[:,:,2]=image_b[xshift:xshift+isize_min,yshift:yshift+isize_min]
    inner_ratio=offset_ratio-smooth_ratio
    tmp = np.linspace(-1,1,isize_min)
    x, y = np.meshgrid(tmp, tmp)
    r = np.sqrt(x*x+y*y)
    image_rgba[:,:,3]=(offset_ratio-r)/smooth_ratio
    image_rgba[:,:,3][r>offset_ratio]=0
    image_rgba[:,:,0][r>offset_ratio]=0
    image_rgba[:,:,1][r>offset_ratio]=0
    image_rgba[:,:,2][r>offset_ratio]=0
    image_rgba[:,:,3][r<inner_ratio]=1.0

    return image_rgba

def image_align7(image_c,image1,image2,image3,image4,image5,image6):
    # assume image are all equal size and square
    #  1 2
    # 3 c 4
    #  5 6
    isize=image_c.shape[0]
    xsize=isize*3
    ysize=int(isize*(np.sqrt(3.0)+1.0))
    image_fin=np.zeros(shape=(ysize,xsize,4))
    y_top=[0,isize]
    y_mid=[(ysize-isize)/2,(ysize-isize)/2+isize]
    y_bot=[ysize-isize,ysize]
    x_tbl=[isize/2,isize/2+isize]
    x_tbr=[isize/2+isize,isize/2+2*isize]
    x_ml=[0,isize]
    x_mc=[isize,2*isize]
    x_mr=[2*isize,3*isize]
    image_fin[y_top[0]:y_top[1],x_tbl[0]:x_tbl[1]] += image1
    image_fin[y_top[0]:y_top[1],x_tbr[0]:x_tbr[1]] += image2
    image_fin[y_mid[0]:y_mid[1],x_ml[0]:x_ml[1]] +=image3
    image_fin[y_mid[0]:y_mid[1],x_mc[0]:x_mc[1]] +=image_c
    image_fin[y_mid[0]:y_mid[1],x_mr[0]:x_mr[1]] +=image4
    image_fin[y_bot[0]:y_bot[1],x_tbl[0]:x_tbl[1]] +=image5
    image_fin[y_bot[0]:y_bot[1],x_tbr[0]:x_tbr[1]] +=image6

    return image_fin

flist='flist'

larg=len(sys.argv)-1
if (larg>=1):
    flist = sys.argv[1]
    if (flist=='-h'):
        print 'arguments: fits_list_prefix[flist]'
        quit()

f = open(flist,'r')
files=f.readline()
files=files.split()

type=('all','ms','rg','agb','bh','wd','bin')
base=np.array([500.0, 500.0, 500.0, 500.0, 50.0, 5.0, 50.0])
lmaxr=base
lmaxg=base
lmaxb=base
#lmr=(99.6,99.5,99.9,99.95,99.5,99.93,99.91)

for i in files:
    image=[]
    
    for j in range(7):
        image_file_B = i+'_'+type[j]+'_B.fits'
        image_file_I = i+'_'+type[j]+'_I.fits'
        image_file_V = i+'_'+type[j]+'_V.fits'
        
        image_data_B = fits.getdata(image_file_B)
        image_data_V = fits.getdata(image_file_V)
        image_data_I = fits.getdata(image_file_I)

        image_log_r=scale_image(image_data_I,'log',max_cut= lmaxr[j])
        image_log_b=scale_image(image_data_B,'log',max_cut= lmaxb[j])
        image_log_g=scale_image(image_data_V,'log',max_cut= lmaxg[j])
#        image_log_r=scale_image(image_data_I,'log',max_percent= lmr[j])
#        image_log_b=scale_image(image_data_B,'log',max_percent= lmr[j])
#        image_log_g=scale_image(image_data_V,'log',max_percent= lmr[j])

        if j==4:
            image.append(image_cut(image_log_r,image_log_g,image_log_b,1.0,0.05,True))
        else:
            image.append(image_cut(image_log_r,image_log_g,image_log_b,1.0,0.05))
    image_seven=image_align7(image[0],image[1],image[2],image[3],
                             image[4],image[5],image[6])

    fig = plt.figure(figsize=(6*3,6*(np.sqrt(3)+1)))
    fontsize=20
    fig.patch.set_visible(False)
    plt.axis('off')
    plt.imshow(image_seven)
    isize=image_seven.shape
    tx_top=isize[0]*(1.0/(np.sqrt(3.0)+1.0)-0.03)
    tx_mid=isize[0]*((np.sqrt(3.0)+2.0)/(2*np.sqrt(3.0)+2.0)-0.03)
    tx_bot=isize[0]*(1.0-0.03)
    tx_h=isize[1]*np.array([1.0/6.0,1.0/3.0,1.0/2.0,2.0/3.0,5.0/6.0])
    plt.text(tx_h[1],tx_top,'MS',ha='center',va='center',size=fontsize,color='w')
    plt.text(tx_h[3],tx_top,'RG',ha='center',va='center',size=fontsize,color='w')
    plt.text(tx_h[0],tx_mid,'AGB',ha='center',va='center',size=fontsize,color='w')
    plt.text(tx_h[4],tx_mid,'BH',ha='center',va='center',size=fontsize)
    plt.text(tx_h[1],tx_bot,'WD',ha='center',va='center',size=fontsize,color='w')
    plt.text(tx_h[3],tx_bot,'Binary',ha='center',va='center',size=fontsize,color='w')

    plt.savefig(i+'.eps')
    plt.close(fig)


# To see more color maps
# http://wiki.scipy.org/Cookbook/Matplotlib/Show_colormaps
