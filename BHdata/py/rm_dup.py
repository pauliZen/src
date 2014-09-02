# remove duplicate index in index log file
# usage: rmdup('orign file name','new file name')

def rmdup(rfile,wfile):
    import numpy as np
    mylist=np.loadtxt(rfile,dtype=int)
    mylist=list(set(mylist))
    mylist.sort()
    fw=open(wfile,'w')
    for item in mylist:
        fw.write("%s\n" % item)
    return wfile

    
    
