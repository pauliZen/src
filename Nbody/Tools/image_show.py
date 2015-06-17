#Show 7 images in one figure for fits output
#preprocess: fits_trans.sh

import numpy as np

# Set up matplotlib and use a nicer set of plot parameters
import matplotlib
matplotlib.rc_file("matplotlibrc")
import matplotlib.pyplot as plt

import sys

from astropy.io import fits

# Log scale
from astropy.visualization import scale_image

def image_cut(image_r,image_g,image_b,offset_ratio,smooth_ratio):
    isize=image_r.shape
    isize_min=np.min(isize)
    if (isize!=image_b.shape).any() | (isize!=image_g.shape).any():
        print 'Warning: Image size not equal!'
    image_rgba=np.zeros(shape=(isize_min,isize_min,4))
    xshift=(isize[0]-isize_min)/2
    yshift=(isize[1]-isize_min)/2
    image_rgba[:,:,0]=image_r[xshift:xshift+isize_min-1,yshift:yshift+isize_min-1]
    image_rgba[:,:,1]=image_g[xshift:xshift+isize_min-1,yshift:yshift+isize_min-1]
    image_rgba[:,:,2]=image_b[xshift:xshift+isize_min-1,yshift:yshift+isize_min-1]
    inner_ratio=offset_ratio-smooth_ratio
    tmp = linspace(-1,1,isize_min)
    x, y = meshgrid(tmp, tmp)
    r = sqrt(x*x+y*y)
    image_rgba[:,:,3]=(inner_ratio-r)/smooth_ratio
    image_rgba[:,:,3][r>offset_ratio]=0
    image_rgba[:,:,3][r<inner_ratio]=1.0

    return image_rgba

def image_align7(image_c,image1,image2,image3,image4,image5,image6):
    # assume image are all equal size and square
    #  1 2
    # 3 c 4
    #  5 6
    isize=image_c.shape[0]
    xsize=isize*3
    ysize=int(isize*(sqrt(3.0)+1.0)/2.0)
    image_fin=nzeros(shape=(xsize,ysize,4))
    y_top=[0,isize-1]
    y_mid=[(ysize-isize)/2,(ysize-isize)/2+isize-1]
    y_bot=[(ysize+isize)/2,(ysize+isize)/2+isize-1]
    x_tbl=[isize/2,isize/2+isize-1]
    x_tbr=[isize/2+isize,isize/2+2*isize-1]
    x_ml=[0,isize-1]
    x_mc=[isize,2*isize-1]
    x_mr=[2*isize,3*isize-1]
    image_fin[x_tbl[0]:x_tbl[1],y_top[0]:y_top[1]]=image1
    image_fin[x_tbr[0]:x_tbr[1],y_top[0]:y_top[1]]=image2
    image_fin[x_ml[0]:x_ml[1],y_mid[0]:y_mid[1]]=image3
    image_fin[x_mc[0]:x_mc[1],y_mid[0]:y_mid[1]]=image_c
    image_fin[x_mr[0]:x_mr[1],y_mid[0]:y_mid[1]]=image4
    image_fin[x_tbl[0]:x_tbl[1],y_bot[0]:y_bot[1]]=image5
    image_fin[x_tbr[0]:x_tbr[1],y_bot[0]:y_bot[1]]=image6

    return image_fin

flist='flist'

larg=len(sys.argv)-1
if (lagr>=1):
    flist = sys.argv[1]
    if (flist=='-h'):
        print 'arguments: fits_list_prefix[flist]'
        quit()

f = open(flist,'r')
files=f.readline()
files=files.split()

type=('all','ms','rg','agb','bh','wd','bin')

for i in files:
    image=np.zeros(7)
    
    for j in range(7):
        image_file_B = i+'_'+type[j]+'_B.fits'
        image_file_I = i+'_'+type[j]+'_I.fits'
        image_file_V = i+'_'+type[j]+'_V.fits'
        
        image_data_B = fits.getdata(image_file_B)
        image_data_V = fits.getdata(image_file_V)
        image_data_I = fits.getdata(image_file_I)

        image_log_r=scale_image(image_data_I,'log')
        image_log_b=scale_image(image_data_B,'log')
        image_log_g=scale_image(image_data_V,'log')

        image[j]=image_cut(image_log_r,image_log_b,image_log_g)
    image_seven=image_align7(image[0],image[1],image[2],image[3],
                             image[4],image[5],image[6])

    fig = plt.figure()
    plt.imshow(image_seven)
    plt.savefig(i+'.png')
    plt.close(fig)


# To see more color maps
# http://wiki.scipy.org/Cookbook/Matplotlib/Show_colormaps
