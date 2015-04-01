import numpy as np
import math

def sdot(x1,x2,x3):
    return math.sqrt(x1*x1+x2*x2+x3*x3)

gtnb,gt,grh,grc,grcmtmp,grcn = np.loadtxt('global.30.all',usecols=(0,1,5,8,11,29),unpack=True, comments='#')
#gt,grcnb,grcmnb,grcn = np.loadtxt('rcout',usecols=(19,3,5,4),unpack=True, comments='#')
tscale=0.55062
rscale=9.375
mscale=606362.7
#gtnb=gt/tscale
#grc=grcnb*rscale
grcm=grcmtmp/rscale*mscale
#grcm=grcmnb*mscale


fl = open('bhdata/bh_single.lst','r')
path = fl.read()
path = path.splitlines()

ik = 0

sout = open('bh_score','w')
#print time, rc, mc, nc, bhmc, bhnc, bhm, bhn

for i in path:
    sdata = np.loadtxt('bhdata/'+i)
    num=sdata.size/sdata[0].size
    time=float(i[10:])
    while (gtnb[ik]<time):
        ik +=1
  
    if (sdata[0].size == 1):
        dis = sdot(sdata[2],sdata[3],sdata[4])
        if (dis<grc[ik]):
            sout.write("%.8e %.8e %.8e %d %.8e %d %.8e %d\n" % (time, grc[ik], grcm[ik], grcn[ik], sdata[1],1, sdata[1], 1))
        else:
            sout.write("%.8e %.8e %.8e %d %.8e %d %.8e %d\n" % (time, grc[ik], grcm[ik], grcn[ik], 0.0, 0, sdata[1], 1))
    else:
        ic = 0
        btm = 0.0
        btmc = 0.0
        btnc = 0
        while (ic<num):
            dis = sdot(sdata[ic][2],sdata[ic][3],sdata[ic][4])
            if (dis<grc[ik]):
                btmc += sdata[ic][1]
                btnc += 1
            btm += sdata[ic][1]
            ic +=1
        sout.write("%.8e %.8e %.8e %d %.8e %d %.8e %d\n" % (time, grc[ik], grcm[ik], grcn[ik], btmc, btnc, btm, ic))

sout.close()
fl.close()

# fl = open('bindat/bh_binary.lst','r')
# path = fl.read()
# path = path.splitlines()
#  
# ik = 0
#  
# bout = open('bh_bcore','w')
#  
# for i in path:
#     bdata = np.loadtxt('bindat/'+i)
#     num=bdata.size/bdata[0].size
#     time=float(i[10:])
#     while (gtnb[ik]<time):
#         ik +=1
#     
#     btm = 0.0
#     btmc = 0.0
#     btnc = 0
#     bbtm = 0.0
#     bbtmc = 0.0
#     bbtn = 0
#     bbtnc = 0
#     if (bdata[0].size == 1):
#         dis = sdot(bdata[4],bdata[5],bdata[6])
#         if ((bdata[13]==14) & (bdata[14]==14)): 
#             bbtm += bdata[2]+bdata[3]
#             bbtn += 1
#         if (dis<grc[ik]):
#             if ((bdata[13]==14) & (bdata[14]==14)): 
#                 bbtmc += bdata[2]+bdata[3]
#                 bbtnc += 1
#             btmc += bdata[2]+bdata[3]
#             btnc += 1
#         ic = 1
#         btm = bdata[2]+bdata[3]
#     else:
#         ic = 0
#         while (ic<num):
#             dis = sdot(bdata[ic][4],bdata[ic][5],bdata[ic][6])
#             if (dis<grc[ik]):
#                 btmc += bdata[ic][2] + bdata[ic][3]
#                 btnc += 1
#                 if ((bdata[ic][13]==14) & (bdata[ic][14]==14)): 
#                     bbtmc += bdata[ic][2] + bdata[ic][3]
#                     bbtnc += 1
#             if ((bdata[ic][13]==14) & (bdata[ic][14]==14)): 
#                 bbtm += bdata[ic][2] + bdata[ic][3]
#                 bbtn += 1
#             btm += bdata[ic][2] + bdata[ic][3]
#             ic +=1
#     bout.write("%.8e %.8e %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d\n" % (time, grc[ik], grcm[ik], grcn[ik], btm, ic, btmc, btnc, bbtm, bbtn, bbtmc, bbtnc))
#  
# bout.close()
# fl.close()
