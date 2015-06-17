import numpy as np
import h5py

fl = open('snap.part.lst','r')
path = fl.read()
path = path.splitlines()

fidxs = open('bhdata/bh_single.lst','w+')
fidxb = open('bhdata/bh_binary.lst','w+')
fidxm = open('bhdata/bh_merger.lst','w+')

for j in path:
    f = h5py.File(j,'r')
    tots = len(f.items())

    kj = 0
    while (kj<tots):
        
        s = f.items()[kj][1]
        kj += 1

        time = float(s.attrs['Time'])
     
        N_SINGLE = s.attrs['N_SINGLE']

        t = np.array(s['TE'])
        l = np.array(s['L'])
        k = np.array(s['KW'])
        mass = np.array(s['M'])
        n = np.array(s['NAM'])
        x1 = np.array(s['X1'])
        x2 = np.array(s['X2'])
        x3 = np.array(s['X3'])
        v1 = np.array(s['V1'])
        v2 = np.array(s['V2'])
        v3 = np.array(s['V3'])
     
        idxs = np.arange(N_SINGLE)
        bhidxs = idxs[k==14]
     
        if (bhidxs.size>0):
            titles = 'bh_single.%.8f' % time
            fidxs.write(titles+'\n')
            fout = open('bhdata/'+titles, 'w')
            for i in bhidxs:
            # m,x,v
                fout.write('%d %.8e %.8e %.8e %.8e %.8e %.8e %.8e\n' % (n[i], mass[i], x1[i], x2[i], x3[i], v1[i], v2[i], v3[i]))
            fout.close()
     
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
       
                idxb = np.arange(N_BINARY)
                bhidxb = idxb[((bk1==14) | (bk2==14))]
       
                if (bhidxb.size>0):
                    titleb = 'bh_binary.%.8f' % time
                    fidxb.write(titleb+'\n')
                    fout = open('bhdata/'+titleb, 'w')
                    for i in bhidxb:
                        # m1,m2,xc,vc,a,e,p,k1,k2
                       fout.write('%d %d %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %d %d\n' % (bn1[i], bn2[i], bm1[i], bm2[i], bxc1[i], bxc2[i], bxc3[i], bvc1[i], bvc2[i], bvc3[i], ba[i], be[i], bp[i], bk1[i], bk2[i]))
                    fout.close()
   
        if ('Mergers' in map(lambda x:x[0], s.items())) :
            m = s['Mergers']
            N_MERGER = m.attrs['N_MERGER']

            if (N_MERGER>0):
     
                mm1 = np.array(m['M1'])
                mm2 = np.array(m['M2'])
                mm3 = np.array(m['M3'])
                mxc1 = np.array(m['XC1'])
                mxc2 = np.array(m['XC2'])
                mxc3 = np.array(m['XC3'])
                mvc1 = np.array(m['VC1'])
                mvc2 = np.array(m['VC2'])
                mvc3 = np.array(m['VC3'])
                mk1 = np.array(m['KW1'])
                mk2 = np.array(m['KW2'])
                mk3 = np.array(m['KW3'])
                mn1 = np.array(m['NAM1'])
                mn2 = np.array(m['NAM2'])
                mn3 = np.array(m['NAM3'])
                mp0 = np.array(m['P0'])
                mp1 = np.array(m['P1'])
                me0 = np.array(m['ECC0'])
                me1 = np.array(m['ECC1'])
                ma0 = np.array(m['A0'])
                ma1 = np.array(m['A1'])
                
                idxm = np.arange(N_MERGER)
                bhidxm = idxm[((mk1==14)|(mk2==14)|(mk3==14))]
     
                if (bhidxm.size>0):
                    titlem = 'bh_merge.%.8f' % time
                    fidxm.write(titlem+'\n')
                    fout = open('bhdata/'+titlem, 'w')
                    for i in bhidxm:
                        # m1,m2,m3,xc,vc,a0,a1,e0,e1,p0,p1,k1,k2,k3
                        fout.write('%d %d %d %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %d %d %d\n' % (mn1[i], mn2[i], mn3[i], mm1[i],mm2[i],mm3[i],mxc1[i],mxc2[i],mxc3[i],mvc1[i],mvc2[i],mvc3[i],ma0[i],ma1[i],me0[i],me1[i],mp0[i],mp1[i],mk1[i],mk2[i],mk3[i]))
                    fout.close()

fidxs.close()
#fidxb.close()
fidxm.close()

