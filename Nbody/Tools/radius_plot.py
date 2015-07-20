import numpy as np
import sys
import matplotlib
import matplotlib.pyplot as plt

ffit='king-fit-lum.fin'

m1_rscale=9.375
m1_tscale=0.622

colors=('#0000A0', '#0000FF', '#00FFFF', '#FF0000','#FF00FF', '#A52A2A', '#800000', '#FFFF00', '#FFA500', '#808000', '#808080')

modellist=['R7_IMF93','R7_IMF01','R7_ROT','R3_IMF01']
path=['R7_IMF93','R7_IMF2001','R7_ROT','R3_IMF2001']

psize=1E3

fit_t=[]
fit_rc=[]
fit_rcerr=[]
fit_rhl=[]
for i in path:
    t,rc,rce,rhl=np.loadtxt(i+'/'+ffit,usecols=(0,1,2,8),unpack=True)
    if (t.size>psize):
        step=int(t.size/psize)
        t=t[::step]
        rc=rc[::step]
        rce=rce[::step]
        rhl=rhl[::step]
    fit_t.append(t)
    fit_rc.append(rc)
    fit_rcerr.append(rce)
    fit_rhl.append(rhl)

rc_t=[]
rc_r=[]
rc,t=np.loadtxt(path[0]+'/rcout.new',usecols=(3,19),unpack=True)
if (t.size>psize):
    step=int(t.size/psize)
    t=t[::step]
    rc=rc[::step]
rc=rc*m1_rscale
rc_t.append(t)
rc_r.append(rc)

rh_t=[]
rh_r=[]
t,rh=np.loadtxt(path[0]+'/lagr.snap.all',usecols=(0,5),unpack=True)
if (t.size>psize):
    step=int(t.size/psize)
    t=t[::step]
    rh=rh[::step]
t=t*m1_tscale
rh_t.append(t)
rh_r.append(rh)

for i in path[1:4]:
    t,rh,rc=np.loadtxt(i+'/global.30.all',usecols=(1,5,8),unpack=True,skiprows=1)
    if (t.size>psize):
        step=int(t.size/psize)
        t=t[::step]
        rc=rc[::step]
        rh=rh[::step]
    rc_t.append(t)
    rh_t.append(t)
    rc_r.append(rc)
    rh_r.append(rh)

mc_t=[]
mc_rc=[]
mc_rh=[]
for i in path:
    t,rc,rh=np.loadtxt(i+'/system.dat',usecols=(1,13,16),unpack=True)
    if (t.size>psize):
        step=int(t.size/psize)
        t=t[::step]
        rc=rc[::step]
        rh=rh[::step]
    mc_t.append(t)
    mc_rc.append(rc)
    mc_rh.append(rh)

#fig = plt.figure(figsize=(6,10))
fig, axes = plt.subplots(nrows=4, ncols=1)
ax0, ax1, ax2, ax3 = axes.flat

#size of image
figcf = plt.gcf()
figcf.set_size_inches(6,10)

ax3.set_xlabel('Time [Myr]')

plots=[ax0,ax1,ax2,ax3]
for i in range(4):
    plots[i].set_ylabel('Radius [pc]')
    plots[i].set_xlim(0,10000)
    plots[i].set_ylim(0,20)
    plots[i].plot(fit_t[i],fit_rhl[i],label=r'$R_{hl}$',color=colors[2])
    plots[i].plot(fit_t[i],fit_rc[i],label=r'$R_{cl}$',color=colors[3])
    plots[i].plot(rh_t[i],rh_r[i],label=r'$R_{h}$',color=colors[1])
    plots[i].plot(rc_t[i],rc_r[i],label=r'$R_{c}$',color=colors[4])
    plots[i].plot(mc_t[i],mc_rh[i],'--',label=r'$R_{h}$(MOCCA)',color=colors[5])
    plots[i].plot(mc_t[i],mc_rc[i],'--',label=r'$R_{c}$(MOCCA)',color=colors[6])
    plots[i].text(100,17,modellist[i])

ax0.legend(bbox_to_anchor=(0., 1.02, 1., .102),loc=3,ncol=3,mode="expand",borderaxespad=0.,frameon=False)

fig.savefig('radius.eps')

