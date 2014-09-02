      Program Tiny
      write(unit=*, fmt=*) 'Hello world, % Rate, years'
      Read(*,*) amount, pcrate, nyears
      rate=pcrate/100.0
      repay=rate*amount/(1.0-(1.0+rate)**(-nyears))
      write(*,*) 'annual repayment are', repay
      End
