      Program test
      Integer add
      Real*8 count
      Integer a(4);
      Integer i,j
      j=2
      i=0
      count=0
      Do 1 k=1,1000
         i=add(i,j)
 1    continue
      Do 2 k=1,4
         a(k)=k
 2    continue
      j=mix(a,4)
      write (6,*) 'count:', i
      write (6,*) 'a:',(a(k),k=1,4)
      end
      
