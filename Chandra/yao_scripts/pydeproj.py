import numpy
import math
import random


def gRandFilename(type):  
    fname = ''  
    for i in range(16):  
        fname = fname + chr(random.randint(65,90))  
        fname = fname + chr(random.randint(48,57))  
        return fname + '.' + type  


xcm_name="/tmp/"+gRandFilename("xcm");
output_name="/tmp/"+gRandFilename("txt");

def get_apec_em(nH,kT,A):
    import os
    z=0
    fxcm=open(xcm_name,"w")
    fxcm.write("statistic chi\n")
    fxcm.write("method leven 10 0.01\n")
    fxcm.write("abund grsa\n")
    fxcm.write("xsect bcmc\n")
    fxcm.write("cosmo 73 0.3 0.73\n")
    fxcm.write("model  wabs*apec &  %f & %f & %f & %f & 1\n"%(nH,kT,A,z))
    fxcm.write("flux .7 7.\n")
    fxcm.write("tclout flux\n")
    fxcm.write("puts $xspec_tclout\n")
    fxcm.write("set a [split $xspec_tclout]\n")
    fxcm.write("set a [lindex $a 4]\n")
    fxcm.write("set f [open %s w]\n"%(output_name))
    fxcm.write("puts $f $a\n")
    fxcm.write("tclexit\n")
    fxcm.close()
    os.system("xspec %s >/dev/null"%(xcm_name))
    ff=open(output_name,"r")
    for i in ff:
        return float(i)
pass


#def get_apec_em(nH,kT,A):
#    return math.sqrt(kT)
#pass



class deproj_v_calc:
    def __init__(self):
        self.rlist=None
        self.kTlist=None
        
    def __init__(self,rlist,kTlist,Alist=None,nH=0):
        self.rlist=rlist
        self.kTlist=kTlist
        self.Alist=Alist
        self.nH=0


    def calc_v(self,nsph,nrad):
        rlist=self.rlist
        if nsph<nrad:
            return None
        if nsph is nrad:
            return 4./3*math.pi*(rlist[nsph]**2-rlist[nsph-1]**2)**1.5
        
        return 2*math.pi*(-1./3.*(rlist[nsph-1]**2-rlist[nrad-1]**2)**1.5+1./3.*(rlist[nsph]**2-rlist[nrad-1]**2)**1.5+1./3.*(rlist[nsph-1]**2-rlist[nrad]**2)**1.5-1./3.*(rlist[nsph]**2-rlist[nrad]**2)**1.5)

    def form_matrix(self):
        result=numpy.zeros([len(self.kTlist),len(self.kTlist)])
        size=len(self.kTlist)
        for i in range(0,size):
            for j in range(i,size):
                #result[i,j]=self.calc_v(j+1,i+1)*math.sqrt(self.kTlist[j])
                if self.Alist!=None:
                    result[i,j]=self.calc_v(j+1,i+1)*get_apec_em(self.nH,self.kTlist[j],self.Alist[j])
                else:
                    result[i,j]=self.calc_v(j+1,i+1)*get_apec_em(self.nH,self.kTlist[j],0.5)
        return result
pass
