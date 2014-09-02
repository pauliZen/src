      Program test
      real*8 a,b,c,x0,vmax,ranc,res,findroot
      integer seed
      seed=2232

***** --Test 1 M1D-----------------------------------------------------**
      a=2.38411
      b=3.5
      c=0.605927
      x0=-1.3258
      vmax=6.23655

      open (unit=3,status='NEW', file='testout1')
      do 1 i =1, 1000
         ranc=ran2(seed)
         res=findroot(ranc,vmax,a,b,c,x0)
         write(3,*) res
 1    continue

***** --Test 2 M06D----------------------------------------------------**
      a=0.093367
      b=12.5645
      c=0.261283
      x0=-2.46835
      vmax=6.5244

      open (unit=10,status='NEW', file='testout2')
      do 2 i =1, 1000
         ranc=ran2(seed)
         res=findroot(ranc,vmax,a,b,c,x0)
         write(10,*) res
 2    continue

***** --Test 3 M06P----------------------------------------------------**
      a=1.0248
      b=6.31603
      c=0.428713
      x0=-1.39525
      vmax=20.5358

      open (unit=11,status='NEW', file='testout3')
      do 3 i =1, 1000
         ranc=ran2(seed)
         res=findroot(ranc,vmax,a,b,c,x0)
         write(11,*) res
 3    continue

***** --Test 4 M1P----------------------------------------------------**
      a=0.00250775
      b=16.1338
      c=0.244205
      x0=-2.29949
      vmax=43.6983

      open (unit=12,status='NEW', file='testout4')
      do 4 i =1, 1000
         ranc=ran2(seed)
         res=findroot(ranc,vmax,a,b,c,x0)
         write(12,*) res
 4    continue
      
      end
      
