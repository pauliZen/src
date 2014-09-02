      PROGRAM TEST
      include 'omp_lib.h'

      REAL*8 X(3,1000)
      Integer LOOPN,COUNT(3),TNUM,dic,dlst(1000)

      COUNT(1) = 0
      COUNT(2) = 0
      COUNT(3) = 0
      TNUM = 0

      READ(5,*) LOOPN
      dic=0
      
!$omp parallel if(LOOPN.ge.5) default(none)
!$omp& shared(X,LOOPN,dic,count,TNUM,dlst)
!$omp do      
      DO 1 I = 1, LOOPN
         DO K=1,3
            X(K,I)=K*I
!$omp critical            
            COUNT(K) = COUNT(K) + K
            TNUM = TNUM + K
!$omp end critical            
         END DO
*!$omp critical
         dic = dic + 1
         dlst(dic)=1
*!$omp end critical         
 1    CONTINUE
!$omp end do      
!$omp master
      PRINT*, 'COUNT: ',(COUNT(K),K=1,3),TNUM,dic
!$omp end master
!$omp do      
      DO 2 I = 1, LOOPN
         print*,'X:I',I, X(1,I),X(2,I),X(3,I),dlst(I)
 2    continue
!$omp end do      
!$omp end parallel
      END
