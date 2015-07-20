import numpy as np
import sys
import matplotlib
import matplotlib.pyplot as plt

xmin=4
xmax=1000
sbmin=25
sbmax=10
sdmin=0.001
sdmax=100.0
mlmin=0.001
mlmax=100.0

filter='V'
msun=4.83

dist=5800.0

flist='dlist'
ffit='king-fit-lum-'+filter+'.dat'

m1_rscale=9.375
m1_tscale=0.622

##        Black   Blue    Cyan    Green   Lime    Olive   Red     Maroon  Magenta Purple 
colors=('#000000', '#0000FF', '#00FFFF', '#008000', '#00FF00', '#808000', '#FF0000', '#800000', '#FF00FF', '#800080')
markers=("o", "v", "^", "<", ">", "1", "2", "3", "4", "8", "s")

modellist=['R7_IMF93','R7_IMF01','R7_ROT','R3_IMF01']
path=['R7_IMF93/t9','R7_IMF2001/t7','R7_ROT/t7','R3_IMF2001/t4']

def king(x,k,rc,rt):
    xr=x*dist/206264.806
    return (k*(1.0/(1.0+(xr/rc)**2)**0.5 - 1.0/(1.0+(rt/rc)**2)**0.5)**2)

#fig = plt.figure(figsize=(6,10))
fig, axes = plt.subplots(nrows=4, ncols=3)
plots = axes.flat

#size of image
figcf = plt.gcf()
figcf.set_size_inches(18,18)

plots[9].set_xlabel('r [arcsec]')
plots[10].set_xlabel('r [arcsec]')
plots[11].set_xlabel('r [arcsec]')
plots[0].set_title(r'$\mu$ [$mag/arcsec^2$]')
plots[1].set_title(r'$\rho$ [$M_{\odot}/arcsec^2$]')
plots[2].set_title(r'$M/L$ [$M_{\odot}/L_{\odot}$]')

for n in range(4):
    i=3*n
    plots[i].set_ylim(sbmin,sbmax)
    plots[i+1].set_ylim(sdmin,sdmax)
    plots[i+2].set_ylim(mlmin,mlmax)
    plots[i+1].set_yscale('log')
    plots[i+2].set_yscale('log')    
    
    for j in range(3):
        plots[i+j].set_xlim(xmin,xmax)
        plots[i+j].set_xscale('log')
#    plots[i].set_ylabel(r'$\mu$ [mag/arcmin$^2$]')
    ff=open(path[n]+'/'+flist,'r')
    files=ff.readlines()
    rc,rt,s1,s2=np.loadtxt(path[n]+'/'+ffit,usecols=(1,3,5,7),unpack=True)
    k0=s1/s2/3.1415926/rc**2
    k=0
    for j in files:
        fname=j.split()
        rp,sbp,r,sb,sd=np.loadtxt(path[n]+'/'+fname[0]+'.sb.'+filter,usecols=(0,1,2,3,5),skiprows=1,unpack=True)
        sd=sd*(rp/r)**2
        sbp=sbp*(rp/r)**2
        x=np.linspace(xmin,(rt[k]*0.99)*206264.806/dist,1000)
        y=map(lambda a: msun+21.572-2.5*np.log10(king(a,k0[k],rc[k],rt[k])), x)
        rs=(r*dist/206264.806<0.95*rt[k])
        sbf=map(lambda a: king(a,k0[k],rc[k],rt[k]), r[rs])*(rp[rs]/r[rs])**2
        plots[i].plot(r,sb,markers[k],label=fname[1]+' Myr',color=colors[k])
        plots[i].plot(x,y,color=colors[k])
        plots[i+1].plot(r,sd,markers[k],label=fname[1]+' Myr',color=colors[k])
        plots[i+2].plot(r,sd/sbp,markers[k],label=fname[1]+' Myr',color=colors[k])
        plots[i+2].plot(r[rs],sd[rs]/sbf,color=colors[k])
        k +=1
    plots[i].text(300,12,modellist[n])
    plots[i+1].text(300,20,modellist[n])
    plots[i+2].text(300,20,modellist[n])
plots[0].legend(bbox_to_anchor=(0., 1.1, 3.4, .102),loc=3,ncol=9,mode="expand",borderaxespad=0.,frameon=False)

fig.savefig('sp.eps')

