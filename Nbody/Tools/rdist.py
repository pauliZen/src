import numpy as np
import h5py
import math

fl = open('snap.lst','r')
path = fl.read()
path = path.splitlines()

timeresolution = 0.125
timecount = 0
timeflag = 0.0

class dataset:
    
    def __init__(self):
        self.ri = 0.0
        self.mainlow = 0.0 
        self.mainmid = 0.0 
        self.mainhigh= 0.0 
        self.rg      = 0.0 
        self.fagb    = 0.0 
        self.sagb    = 0.0 
        self.agb     = 0.0 
        self.wd      = 0.0 
        self.ns      = 0.0 
        self.bh      = 0.0 

        self.nmainlow = 0 
        self.nmainmid = 0 
        self.nmainhigh= 0 
        self.nrg      = 0 
        self.nfagb    = 0 
        self.nsagb    = 0 
        self.nagb     = 0 
        self.nwd      = 0 
        self.nns      = 0 
        self.nbh      = 0 


def fillfun( kw, mass, distance, data ):
    data.ri = distance
    mflag = True
    if (kw == 0):
        if (mass < 0.4): 
            data.nmainlow += 1
            data.mainlow += mass
        else:
            data.nmainmid += 1
            data.mainmid += mass
    elif (kw == 1):
        data.nmainhigh += 1
        data.mainhigh += mass
    elif (kw == 3):
        data.nrg += 1
        data.rg += mass
    elif (kw == 5):
        data.nagb += 1
        data.agb += mass
        data.nfagb += 1
        data.fagb += mass
    elif (kw == 6):
        data.nagb += 1
        data.agb += mass
        data.nsagb += 1
        data.sagb += mass
    elif ((kw >= 10) & (kw <= 12)):
        data.nwd += 1
        data.wd += mass
    elif (kw == 13):
        data.nns += 1
        data.ns += mass
    elif (kw == 14):
        data.nbh += 1
        data.bh += mass
    else:
        mflag = False
    return mflag

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

            k = np.array(s['KW'])
            mass = np.array(s['M'])
            n = np.array(s['NAM'])
            x1 = np.array(s['X1'])
            x2 = np.array(s['X2'])
            x3 = np.array(s['X3'])

            N_SINGLE = s.attrs['N_SINGLE']
     
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
                if (N_BINARY > 0):
                    bk1 = np.array(b['KW1'])
                    bk2 = np.array(b['KW2'])
                    bxc1 = np.array(b['XC1'])
                    bxc2 = np.array(b['XC2'])
                    bxc3 = np.array(b['XC3'])
                    bm1 = np.array(b['M1'])
                    bm2= np.array(b['M2'])
             
                else:
                    bflag = False
     
            if (mflag) :
                m = s['Mergers']
                N_MERGER = m.attrs['N_MERGER']
                if (N_MERGER > 0):
                    mk1 = np.array(m['KW1'])
                    mk2 = np.array(m['KW2'])
                    mk3 = np.array(m['KW3'])
                    mm1 = np.array(m['M1'])
                    mm2 = np.array(m['M2'])
                    mm3 = np.array(m['M3'])
                    mxc1 = np.array(m['XC1'])
                    mxc2 = np.array(m['XC2'])
                    mxc3 = np.array(m['XC3'])
             
                else:
                    mflag = False

            print "Sorting..."

            r2 = x1*x1 + x2*x2 + x3*x3
            if (bflag) : 
                rb2 = bxc1*bxc1 + bxc2*bxc2 + bxc3*bxc3
                r2 = np.append(r2,rb2)
        
            if (mflag) :
                rm2 = mxc1*mxc1 + mxc2*mxc2 + mxc3*mxc3
                r2 = np.append(r2,rm2)
     
            idx = r2.argsort()
            
            N_SB = N_SINGLE + N_BINARY

            nc = 0

            titlem = '%.8f' % time
            fw = open('rdist_'+titlem,'w')

            dat = dataset()

            for j in idx:
                if (j>=N_SB):
                    nc += 3
                    inx = j - N_SB
                    w1flag = fillfun(mk1[inx], mm1[inx], math.sqrt(r2[j]), dat)
                    w2flag = fillfun(mk2[inx], mm2[inx], math.sqrt(r2[j]), dat)
                    w3flag = fillfun(mk3[inx], mm3[inx], math.sqrt(r2[j]), dat)
                    # r, main(low,mid,high), red giant, First RGB, Secound RGB, RGB, WD, NS, BH
                    if (w1flag | w2flag | w3flag):
                        fw.write('%.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e\n' % ( dat.ri, dat.nmainlow, dat.mainlow, dat.nmainmid, dat.mainmid, dat.nmainhigh, dat.mainhigh, dat.nrg, dat.rg, dat.nfagb, dat.fagb, dat.nsagb, dat.sagb, dat.nagb, dat.agb, dat.nwd, dat.wd, dat.nns, dat.ns, dat.nbh, dat.bh))
                elif (j>=N_SINGLE):
                    nc += 2
                    inx = j - N_SINGLE
                    w1flag = fillfun(bk1[inx], bm1[inx], math.sqrt(r2[j]), dat)
                    w2flag = fillfun(bk2[inx], bm2[inx], math.sqrt(r2[j]), dat)
                    if (w1flag | w2flag):
                        fw.write('%.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e\n' % ( dat.ri, dat.nmainlow, dat.mainlow, dat.nmainmid, dat.mainmid, dat.nmainhigh, dat.mainhigh, dat.nrg, dat.rg, dat.nfagb, dat.fagb, dat.nsagb, dat.sagb, dat.nagb, dat.agb, dat.nwd, dat.wd, dat.nns, dat.ns, dat.nbh, dat.bh))
                else:
                    nc += 1
                    wflag = fillfun(k[j], mass[j], math.sqrt(r2[j]), dat)
                    if (wflag):
                        fw.write('%.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e %d %.8e\n' % ( dat.ri, dat.nmainlow, dat.mainlow, dat.nmainmid, dat.mainmid, dat.nmainhigh, dat.mainhigh, dat.nrg, dat.rg, dat.nfagb, dat.fagb, dat.nsagb, dat.sagb, dat.nagb, dat.agb, dat.nwd, dat.wd, dat.nns, dat.ns, dat.nbh, dat.bh))
                    
            fw.close()
    
