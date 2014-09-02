      SUBROUTINE KSPERT(I1,NNB0,XI,VI,FP,FD)
*
*
*       Perturbation on KS pair.
*       ------------------------
*
      INCLUDE 'common2.h'
      REAL*8  XI(6),VI(6),FP(6),FD(6)
*
*
*       Initialize the perturbing force & first derivative.
      DO 10 K = 1,6
          FP(K) = 0.0D0
          FD(K) = 0.0D0
   10 CONTINUE
*
*       Obtain the perturbation from single particles.
      DO 20 L = 2,NNB0+1
          K = LIST(L,I1)
          A1 = X(1,K) - XI(1)
          A2 = X(2,K) - XI(2)
          A3 = X(3,K) - XI(3)
          RIJ2 = A1*A1 + A2*A2 + A3*A3
          A6 = BODY(K)/(RIJ2*SQRT(RIJ2))
          FP(1) = FP(1) + A1*A6
          FP(2) = FP(2) + A2*A6
          FP(3) = FP(3) + A3*A6
          V1 = XDOT(1,K) - VI(1)
          V2 = XDOT(2,K) - VI(2)
          V3 = XDOT(3,K) - VI(3)
          A9 = 3.0D0*(A1*V1 + A2*V2 + A3*V3)/RIJ2
          FD(1) = FD(1) + (V1 - A1*A9)*A6
          FD(2) = FD(2) + (V2 - A2*A9)*A6
          FD(3) = FD(3) + (V3 - A3*A9)*A6
*       Perturbation on first component.
*
          A1 = X(1,K) - XI(4)
          A2 = X(2,K) - XI(5)
          A3 = X(3,K) - XI(6)
          RIJ2 = A1*A1 + A2*A2 + A3*A3
          A6 = BODY(K)/(RIJ2*SQRT(RIJ2))
          FP(4) = FP(4) + A1*A6
          FP(5) = FP(5) + A2*A6
          FP(6) = FP(6) + A3*A6
          V1 = XDOT(1,K) - VI(4)
          V2 = XDOT(2,K) - VI(5)
          V3 = XDOT(3,K) - VI(6)
          A9 = 3.0D0*(A1*V1 + A2*V2 + A3*V3)/RIJ2
          FD(4) = FD(4) + (V1 - A1*A9)*A6
          FD(5) = FD(5) + (V2 - A2*A9)*A6
          FD(6) = FD(6) + (V3 - A3*A9)*A6
*       Perturbation on second component.
   20 CONTINUE
*
*       Form the relative perturbing force and first derivative.
      DO 30 K = 1,3
          FP(K) = FP(K) - FP(K+3)
          FD(K) = FD(K) - FD(K+3)
   30 CONTINUE
*
      RETURN
*
      END
