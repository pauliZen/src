      SUBROUTINE PLPERT(ACC)
*
*
*       External perturbations for Plummer model.
*       -----------------------------------------
*
      IMPLICIT  REAL*8  (A-H,M,O-Z)
      COMMON/AZREG/  Q(8),P(8),R,R1,R2,ENERGY,M(3),X(3,3),XDOT(3,3),
     &               RCOLL,ERROR,C11,C12,C19,C20,C24,C25,NSTEPS,NAME(3)
      COMMON/PLUMMER/ ZMP,EPS2
      REAL*8  ACC(9)
*
*
*       Obtain perturbing accelerations for current sequence.
      DO 10 I = 1,3
          IK = 3*(I - 1)
          RI2 = X(1,I)**2 + X(2,I)**2 + X(3,I)**2 + EPS2
          RI3 = RI2*SQRT(RI2)
          DO 5 K = 1,3
              ACC(IK+K) = -ZMP*X(K,I)/RI3
    5     CONTINUE
   10 CONTINUE
*
 	RETURN
 	END
