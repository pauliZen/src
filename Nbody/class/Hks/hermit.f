*
*            K S R E G 2
*            ***********
*
*       Hermite KS toy code (p.56 & 62).
*       --------------------------------
*
*       Coded by Sverre Aarseth, IOA, Cambridge.
*       ........................................
*
      PROGRAM HERMIT
*
      INCLUDE 'common2.h'
*
*
*       Read input parameters and initialize KS polynomials.
      CALL INPUT
      CALL KSINIT
*
*       Evaluate initial two-body elements.
      SEMI0 = -0.5*BODY(3)/H(1)
      TK = TWOPI*SEMI0*SQRT(SEMI0/BODY(3))
      ECC2 = (1.0 - R(1)/SEMI0)**2 + TDOT2(1)**2/(BODY(3)*SEMI0)
      ECC0 = SQRT(ECC2)
*
*       Scale output times by Kepler period.
      DELTAT = DELTAT*TK
      TCRIT = TCRIT*TK
      TNEXT = DELTAT
      I1 = 1
*
*       Advance equations of motion until output time is exceeded.
    5 TIME = TIME + STEP(1)
      CALL KSINT(I1)
      IF (TIME.LT.TNEXT) GO TO 5
*
*       Perform accuracy check.
      V2 = 0.0
      DO 10 K = 1,4
          V2 = V2 + UDOT(K,1)**2
   10 CONTINUE
*       Form specific energy from regularized expression.
      HT = (2.0*V2 - BODY(3))/R(1)
      SEMI = -0.5*BODY(3)/HT
      ECC2 = (1.0 - R(1)/SEMI)**2 + TDOT2(1)**2/(BODY(3)*SEMI)
      ECC = SQRT(ECC2)
*
*       Print relevant information (note DA/A and DE).
      DA = (SEMI - SEMI0)/SEMI0
      DE = ECC - ECC0
      WRITE (6,20)  TIME/TK, NSTEPU, ECC, SEMI, DA, DE
   20 FORMAT (' T/TK # E A TK DA/A DE ',F8.2,I7,F7.3,1P,3E9.1)
*
*       Continue until termination time is exceeded.
      TNEXT = TNEXT + DELTAT
      IF (TIME.LT.TCRIT) GO TO 5
*
      STOP
*
      END
