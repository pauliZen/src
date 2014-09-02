      SUBROUTINE INCLIN(ZI)
*
*
*       Inclination of outer orbit.
*       ---------------------------
*
      IMPLICIT REAL*8  (A-H,M,O-Z)
      COMMON/AZREG/  Q(8),P(8),R,R1,R2,ENERGY,M(3),X(3,3),XDOT(3,3),
     &               RCOLL,ERROR,C11,C12,C19,C20,C24,C25,NSTEPS,NAME(3)
      COMMON/HIARCH/  MB,MT,A0,A1,E0,E1,P0,P1,P1P0,RATIO,RI,SEMI,SEMI1,
     &                TIME,TPLOT,DTPLOT,RAP,VAP,TWOPI,NEXP
      REAL*8  PX(3),QX(3),XORB(2),VORB(2),XREL(3),VREL(3)
      REAL*4  RAN2
      SAVE IDUM1
*
*
*       Initialize random number generator.
      IF (NEXP.EQ.0) THEN
          KDUM = -1
          XR = RAN2(KDUM)
          IDUM1 = KDUM
      END IF
*
*       Randomize perihelion, node & inclination.
      PI = TWOPI*RAN2(IDUM1)
      OMEGA = TWOPI*RAN2(IDUM1)
      PI = 0.0
      OMEGA = 0.0
*
*       Define transformation elements (Brouwer & Clemence p. 35).
      PX(1) = COS(PI)*COS(OMEGA) - SIN(PI)*SIN(OMEGA)*COS(ZI)
      QX(1) =-SIN(PI)*COS(OMEGA) - COS(PI)*SIN(OMEGA)*COS(ZI)
      PX(2) = COS(PI)*SIN(OMEGA) + SIN(PI)*COS(OMEGA)*COS(ZI)
      QX(2) =-SIN(PI)*SIN(OMEGA) + COS(PI)*COS(OMEGA)*COS(ZI)
      PX(3) = SIN(PI)*SIN(ZI)
      QX(3) = COS(PI)*SIN(ZI) 
*
*       Copy relative motion at apocentre.
      XORB(1) = 0.0
      XORB(2) = RAP
      VORB(1) = VAP
      VORB(2) = 0.0
*
*       Transform to relative variables.
      DO 5 K = 1,3
          XREL(K) = PX(K)*XORB(1) + QX(K)*XORB(2)
          VREL(K) = PX(K)*VORB(1) + QX(K)*VORB(2)
    5 CONTINUE
*
*       Set new X & XDOT for the outer body.
      RI2 = 0.0
      VI2 = 0.0
      DO 10 K = 1,3
          X(K,1) = XREL(K)
          XDOT(K,1) = VREL(K)
          RI2 = RI2 + XREL(K)**2
          VI2 = VI2 + VREL(K)**2
   10 CONTINUE
*
*     AI = 2.0/SQRT(RI2) - VI2/MT
*     AI = 1.0/AI
*     PI = TWOPI*AI*SQRT(AI/MT)
*     WRITE (6,20)  PI,(X(K,1),K=1,3), (XDOT(K,1),K=1,3)
*  20 FORMAT (' INCLIN:   P X XD  ',F8.3,1X,3F7.2,2X,3F6.2)
*
      RETURN
*
      END
