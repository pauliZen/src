import numpy as np
import ctypes

def get_test():
    dll = ctypes.CDLL("/u/longw/lib/libarrayprint.so",mode=ctypes.RTLD_GLOBAL)
    func = dll.test
    func.argtypes = [ctypes.c_float, ctypes.c_double, ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_int)]
    return func

__test=get_test()

def test(a,b,c,n,ar,br,cr):
    arp = ar.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
    brp = br.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
    crp = cr.ctypes.data_as(ctypes.POINTER(ctypes.c_int))
    __test(a,b,c,n,arp,brp,crp)
    
a = 1.0
b = 2.0
c = 3
n = 5
ar=np.array([1.0,2.0,3.0,4.0,5.0]).astype(np.float32)
br=np.array([10.0,20.0,30.0,40.0,50.0]).astype(np.double)
cr=np.array([11,22,33,44,55]).astype(np.int32)


test(a,b,c,n,ar,br,cr)
