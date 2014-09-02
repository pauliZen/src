      program test
      parameter (NMAX=1000000)
      LOGICAL A(NMAX),B(NMAX)
      INTEGER D

      DO J=1,67000
         DO I=1,NMAX
            IF (A(I).AND.A(J)) D=D+1
         END DO
      END DO

      PRINT*,D

      END
      
