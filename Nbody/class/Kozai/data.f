      SUBROUTINE DATA(ZINC)
*
*
*       Initial conditions.
*       -------------------
*
      IMPLICIT  REAL*8  (A-H,M,O-Z)
      COMMON/AZREG/  Q(8),P(8),R,R1,R2,ENERGY,M(3),X(3,3),XDOT(3,3),
     &               RCOLL,ERROR,C11,C12,C19,C20,C24,C25,NSTEPS,NAME(3)
      COMMON/HIARCH/  MB,MT,A0,A1,E0,E1,P0,P1,P1P0,RATIO,RI,SEMI,SEMI1,
     &                TIME,TPLOT,DTPLOT,RAP,VAP,TWOPI,NEXP
      REAL*8  SUM(7)
*
*
      DO 1 K = 1,7
          SUM(K) = 0.0D0
    1 CONTINUE
      TWOPI = 8.0D0*ATAN(1.0D0)
*
*       Initialize all X & XDOT to zero.
      DO 5 I = 1,3
          DO 4 K = 1,3
              X(K,I) = 0.0
              XDOT(K,I) = 0.0
    4     CONTINUE
    5 CONTINUE
*
*       Specify apocentre velocity of inner and outer orbit.
      MB = M(2) + M(3)
      MT = MB + M(1)
      V0 = SQRT(MB*(1.0 - E0)/(A0*(1.0 + E0)))
      V1 = SQRT(MT*(1.0 - E1)/(A1*(1.0 + E1)))
*
      WRITE (6,66)  A0,A1,V0,V1
   66 FORMAT (' INITIAL:    A0 A1 V0 V1  ',4F9.3)
*       Initialize orbits at apocentre.
      RCM = 0.0
      RA = A0*(1.0 + E0)
      X(1,2) = RCM - RA*M(3)/MB
      X(1,3) = RCM + RA*M(2)/MB
      VCM = 0.0
      XDOT(2,2) = VCM - V0*M(3)/MB
      XDOT(2,3) = VCM + V0*M(2)/MB
      X(2,1) = A1*(1.0 + E1)
      XDOT(1,1) = -V1
      RAP = X(2,1)
      VAP = -V1
*
*       Include optional inclination (ZI > 0).
      IF (ZINC.GE.0.0) THEN
          ZI = TWOPI*ZINC/360.0
          CALL INCLIN(ZI)
      END IF
*
*       Save the periods.
      P0 = TWOPI*A0*SQRT(A0/MB)
      P1 = TWOPI*A1*SQRT(A1/MT)
      P1P0 = P1/P0
      RATIO = P1P0
      WRITE (6,7)  P0, P1, P1P0, A1/A0
    7 FORMAT (' PERIODS:    P0 =',1P,E10.2,'  P1 =',E10.2,
     &                   '  P1/P0 =',0P,F9.3,'  A1/A0 =',F6.2)
*
*       Form total mass & centre of mass terms.
      DO 10 I = 1,3
          SUM(7) = SUM(7) + M(I)
          DO 8 K = 1,3
              SUM(K) = SUM(K) + M(I)*X(K,I)
              SUM(K+3) = SUM(K+3) + M(I)*XDOT(K,I)
    8     CONTINUE
   10 CONTINUE
*
*       Initialize NAME and define X & XDOT with respect to local c.m.
      DO 20 I = 1,3
          NAME(I) = I
          DO 15 K = 1,3
              X(K,I) = X(K,I) - SUM(K)/SUM(7)
              XDOT(K,I) = XDOT(K,I) - SUM(K+3)/SUM(7)
   15     CONTINUE
   20 CONTINUE
*
      RETURN
*
      END
