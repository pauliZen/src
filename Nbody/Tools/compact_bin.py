import numpy as np
import h5py

fl = open('snap.lst','r')
path = fl.read()
path = path.splitlines()

fidwd = open('bindat/wd_binary.lst','w+')
fidns = open('bindat/ns_binary.lst','w+')
fidbh = open('bindat/bh_binary.lst','w+')

for j in path:
    f = h5py.File(j,'r')
    tots = len(f.items())

    kj = 0
    while (kj<tots):
        
        s = f.items()[kj][1]
        kj += 1

        time = float(s.attrs['Time'])

        if ('Binaries' in map(lambda x:x[0], s.items())) :
            b = s['Binaries']
            N_BINARY = b.attrs['N_BINARY']

            if(N_BINARY>0):
                bxc1 = np.array(b['XC1'])
                bxc2 = np.array(b['XC2'])
                bxc3 = np.array(b['XC3'])
                bvc1 = np.array(b['VC1'])
                bvc2 = np.array(b['VC2'])
                bvc3 = np.array(b['VC3'])
                ba = np.array(b['A'])
                be = np.array(b['ECC'])
                bp = np.array(b['P'])
                bm1 = np.array(b['M1'])
                bm2= np.array(b['M2'])
                bk1 = np.array(b['KW1'])
                bk2 = np.array(b['KW2'])
                bn1 = np.array(b['NAM1'])
                bn2 = np.array(b['NAM2'])
                bl1 = np.array(b['L1'])
                bl2 = np.array(b['L2'])                
                bt1 = np.array(b['TE1'])
                bt2 = np.array(b['TE2'])
                brs1 = np.array(b['RS1'])
                brs2 = np.array(b['RS2'])
         
                idxb = np.arange(N_BINARY)
                wdidxb = idxb[((bk1>=10) & (bk1<=12)) | ((bk2>=10) & (bk2<=12))]
                nsidxb = idxb[((bk1==13) | (bk2==13))]
                bhidxb = idxb[((bk1==14) | (bk2==14))]

                if (wdidxb.size>0):
                    title = 'wd_binary.%.8f' % time
                    fidwd.write(title+'\n')
                    fout = open('bindat/'+title, 'w')
                    for i in wdidxb:
                        # m1,m2,xc,vc,a,e,p,k1,k2,l1,l2,te1,te2,rs1,rs2
                        fout.write('%d %d %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %d %d %.8e %.8e %.8e %.8e %.8e %.8e\n' % (bn1[i], bn2[i], bm1[i], bm2[i], bxc1[i], bxc2[i], bxc3[i], bvc1[i], bvc2[i], bvc3[i], ba[i], be[i], bp[i], bk1[i], bk2[i], bl1[i], bl2[i], bt1[i], bt2[i], brs1[i], brs2[i]))
                    fout.close()

                if (nsidxb.size>0):
                    title = 'ns_binary.%.8f' % time
                    fidns.write(title+'\n')
                    fout = open('bindat/'+title, 'w')
                    for i in nsidxb:
                        # m1,m2,xc,vc,a,e,p,k1,k2,l1,l2,te1,te2,rs1,rs2
                        fout.write('%d %d %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %d %d %.8e %.8e %.8e %.8e %.8e %.8e\n' % (bn1[i], bn2[i], bm1[i], bm2[i], bxc1[i], bxc2[i], bxc3[i], bvc1[i], bvc2[i], bvc3[i], ba[i], be[i], bp[i], bk1[i], bk2[i], bl1[i], bl2[i], bt1[i], bt2[i], brs1[i], brs2[i]))
                    fout.close()

                if (bhidxb.size>0):
                    title = 'bh_binary.%.8f' % time
                    fidbh.write(title+'\n')
                    fout = open('bindat/'+title, 'w')
                    for i in bhidxb:
                        # m1,m2,xc,vc,a,e,p,k1,k2,l1,l2,te1,te2,rs1,rs2
                        fout.write('%d %d %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %d %d %.8e %.8e %.8e %.8e %.8e %.8e\n' % (bn1[i], bn2[i], bm1[i], bm2[i], bxc1[i], bxc2[i], bxc3[i], bvc1[i], bvc2[i], bvc3[i], ba[i], be[i], bp[i], bk1[i], bk2[i], bl1[i], bl2[i], bt1[i], bt2[i], brs1[i], brs2[i]))
                    fout.close()
                
fidwd.close()
fidns.close()
fidbh.close()
