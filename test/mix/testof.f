      Program test
      Integer add
      Real*8 count
      Integer i,j
      j=2
      i=0
      count=0
      Do 1 k=1,100000000
         i=add(i,j)
 1    continue
      write (6,*) 'count:', i
      end
      
      function add(i,j)
      Integer i,j,add
      add=i+j
      end
