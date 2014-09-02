      program test

      parameter (NMAX=20,ILIST=10)
      INTEGER NXTLST_MPI(NMAX),NXTLST(NMAX),NXTLEN,ISIZE,NPIECE

      ISIZE = 3
      NPIECE = NMAX / ISIZE + 1
      NXTLST_MPI(1:NMAX) = -1

      NXTLEN = 0
      DO J = 1, ILIST
         NXTLEN = NXTLEN + 1
         NXTLST(NXTLEN) = J
         NXTLST_MPI(MOD(NXTLEN-1,isize)*NPIECE + 
     *        (NXTLEN-1)/ISIZE +1) = J
      END DO

      print*,'NST',nxtlst(1:ILIST)
      print*,'MPI',nxtlst_mpi(1:NMAX)

      END
