import numpy as np
import h5py
import math

fl = open('snap.lst','r')
path = fl.read()
path = path.splitlines()

timeresolution = 0.125
timecount = 0
timeflag = 0.0


for i in path:
    f = h5py.File(i,'r')
    tots = len(f.items())

    kj = 0
    while (kj<tots):

        s = f.items()[kj][1]
        kj += 1
        
        time = float(s.attrs['Time'])
        
        print "Snapshot time %.8e " % time

        if ((math.fabs(time-timeflag) < timeresolution/2.0) | (time - timeflag >= timeresolution/2.0)):

            print "Initialize... timeflag = %.8e " % timeflag
            
            timecount += 1
            timeflag = math.pow(1000,float(timecount)/20.0)
     
            bflag = 'Binaries' in map(lambda x:x[0], s.items())
            mflag = 'Mergers' in map(lambda x:x[0], s.items())

            b = 0
            m = 0
     
            N_BINARY = 0
            N_MERGER = 0
     
            bm1 = 0
            bm2 = 0
            mm1 = 0
            mm2 = 0
            mm3 = 0
            bxc1 = 0
            bxc2 = 0
            bxc3 = 0
            mxc1 = 0
            mxc2 = 0
            mxc3 = 0
            bk1 = 0
            bk2 = 0
            mk1 = 0
            mk2 = 0
            mk3 = 0
         
            if (bflag) :
                b = s['Binaries']
                N_BINARY = b.attrs['N_BINARY']
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
         
                titleb = 'binary.%.8f' % time
#                fidxb.write(titleb+'\n')
                fout = open('data/'+titleb, 'w')
                i = 0
                while (i<N_BINARY):
                    # m1,m2,xc,vc,a,e,p,k1,k2
                    fout.write('%d %d %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %.8e %d %d\n' % (bn1[i], bn2[i], bm1[i], bm2[i], bxc1[i], bxc2[i], bxc3[i], bvc1[i], bvc2[i], bvc3[i], ba[i], be[i], bp[i], bk1[i], bk2[i]))
                    i += 1
                fout.close()
     
    
