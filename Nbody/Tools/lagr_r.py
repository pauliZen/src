import numpy as np
import matplotlib.pyplot as plt
import sys

flist='lagr.lst'
ncol=2
outformat='png'

narg=len(sys.argv)
if (narg>=2):
    flist=sys.argv[1]
    if (flist == '-h'):
        print 'arguments: datalist[lagr.lst] column[2] outformat[png]'
        quit()
if (narg>=3):
    ncol=int(sys.argv[2])
if (narg>=4):
    outformat=sys.argv[3]


colors         = ('b', 'g', 'r', 'c', 'm', 'y', 'k')
linestyles     = ('-', '-', '-', '-', '-', '-', '-')

fl = open(flist,'r')
path = fl.read()
path = path.splitlines()

tlabel=(r'$R_{lagr}$',r'$R_{lagr,s}$',r'$R_{lagr,b}$',
        r'$\langle M \rangle$',r'$\langle M \rangle_{s}$',r'$\langle M \rangle_{b}$',
        r'$N$',r'$N_s$',r'$N_b$',
        r'$M_{bin}/M$',r'$N_{bin}/N$',
        r'$\langle v \rangle$',r'$\langle v \rangle_{s}$',r'$\langle v \rangle_{b}$',
        r'$\langle v_x \rangle$',r'$\langle v_x \rangle_{s}$',r'$\langle v_x \rangle_{b}$',
        r'$\langle v_y \rangle$',r'$\langle v_y \rangle_{s}$',r'$\langle v_y \rangle_{b}$',
        r'$\langle v_z \rangle$',r'$\langle v_z \rangle_{s}$',r'$\langle v_z \rangle_{b}$',
        r'$\langle v_r \rangle$',r'$\langle v_r \rangle_{s}$',r'$\langle v_r \rangle_{b}$',
        r'$\langle v_t \rangle$',r'$\langle v_t \rangle_{s}$',r'$\langle v_t \rangle_{b}$',
        r'$\langle \sigma \rangle$',r'$\langle \sigma \rangle_{s}$',r'$\langle \sigma \rangle_{b}$',
        r'$\langle \sigma_x \rangle$',r'$\langle \sigma_x \rangle_{s}$',r'$\langle \sigma_x \rangle_{b}$',
        r'$\langle \sigma_y \rangle$',r'$\langle \sigma_y \rangle_{s}$',r'$\langle \sigma_y \rangle_{b}$',
        r'$\langle \sigma_z \rangle$',r'$\langle \sigma_z \rangle_{s}$',r'$\langle \sigma_z \rangle_{b}$',
        r'$\langle \sigma_r \rangle$',r'$\langle \sigma_r \rangle_{s}$',r'$\langle \sigma_r \rangle_{b}$',
        r'$\langle \sigma_t \rangle$',r'$\langle \sigma_t \rangle_{s}$',r'$\langle \sigma_t \rangle_{b}$',
        r'$\langle v_{rot} \rangle$',r'$\langle v_{rot} \rangle_{s}$',r'$\langle v_{rot} \rangle_{b}$',
        r'$\langle \sigma_{rot} \rangle$',r'$\langle \sigma_{rot} \rangle_{s}$',r'$\langle \sigma_{rot} \rangle_{b}$',
        r'$M_{p,bin}/M$',r'$N_{p,bin}/N$',r'$M_{p,bin}/M_{bin}$',r'$N_{p,bin}/N_{bin}$')

fname=('R_lagr','R_lagrs','R_lagrb',
        'M','M_s','M_b',
        'N','N_s','N_b',
        'M_bin_M','N_bin_N',
        'v','v_s','v_b',
        'v_x','v_x_s','v_x_b',
        'v_y','v_y_s','v_y_b',
        'v_z','v_z_s','v_z_b',
        'v_r','v_r_s','v_r_b',
        'v_t','v_t_s','v_t_b',
        's','s_s','s_b',
        's_x','s_x_s','s_x_b',
        's_y','s_y_s','s_y_b',
        's_z','s_z_s','s_z_b',
        's_r','s_r_s','s_r_b',
        's_t','s_t_s','s_t_b',
        'v_rot','v_rot_s','v_rot_b',
        's_rot','s_rot_s','s_rot_b',
        'PM_bin_M','PN_bin_N',
        'PMb_Mb','PNb_Nb')

fig = plt.figure(figsize=(8,6),dpi=300)
icc=0
plt.xlabel('r [pc]')
plt.xscale('log')
plt.xlim(0.1,100)
plt.ylabel(tlabel[ncol-1])

for i in path:
    data=np.transpose(np.loadtxt(i,unpack=False))
    plt.plot(data[:,0],data[:,ncol-1],linestyles[icc],label=i[5:]+' Myr',color=colors[icc],markersize=1)
    icc +=1
plt.legend(framealpha=0.7)
plt.savefig(fname[ncol-1]+'_t.'+outformat)
plt.close(fig)
