      SUBROUTINE LENZ(GM,XI,VI,EVEC)
*
*
*       Longitude of periapse.
*       ----------------------
*
      IMPLICIT REAL*8  (A-H,O-Z)
      REAL*8  XI(3),VI(3)
      REAL*8  HI(3),XREL(3),VREL(3),EVEC(3)
*     SAVE IT
*     DATA IT /0/
*
*
      H2 = 0.0
      RI2 = 0.0
      DO 5 K = 1,3
          K1 = K + 1
          IF (K1.GT.3) K1 = 1
          K2 = K1 + 1
          IF (K2.GT.3) K2 = 1
          HI(K) = XI(K1)*VI(K2) - XI(K2)*VI(K1)
          H2 = H2 + HI(K)**2
          XREL(K) = XI(K)
          RI2 = RI2 + XREL(K)**2
          VREL(K) = VI(K)
    5 CONTINUE
*
      RI = SQRT(RI2)
      DO 10 K = 1,3
          K1 = K + 1
          IF (K1.GT.3) K1 = 1
          K2 = K1 + 1
          IF (K2.GT.3) K2 = 1
          EVEC(K) = (VREL(K1)*HI(K2) - VREL(K2)*HI(K1))/GM - XREL(K)/RI
   10 CONTINUE
*
      RETURN
      END
