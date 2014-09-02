      Program test
      REAL*8 time,tstore
      time=1.0D
      tstore=time
      DO I=1,1000000
         if (tstore.ne.time) go to 10
         time = time *0.5D
         tstore = time
      END DO

 10   END
      
