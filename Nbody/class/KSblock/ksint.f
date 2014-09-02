      SUBROUTINE KSINT(I1)
*
*
*       Regularized integration.
*       ------------------------
*
      INCLUDE 'common2.h'
      COMMON/SLOW/  RANGE,ISLOW(10)
      REAL*8  UI(4),UIDOT(4),XI(6),VI(6),FP(6),FD(6)
      REAL*8  EI0(3),EI(3)
      SAVE  EI0
      DATA  EI0 /3*0/
*
*
*       Set second component (= 2), pair index (= 1) & c.m. index.
      I2 = 2
      IPAIR = 1
      I = N + IPAIR
*
*       Define perturber membership & inverse c.m. mass.
      NNB0 = LIST(1,I1)
      BODYIN = 1.0/BODY(I)
*
*       Check for further unperturbed motion (enforced skip in toy code).
**    IF (NNB0.EQ.0) THEN
      IF (NNB0.LT.0) THEN
          KPERT = 0
          CALL UNPERT(IPAIR,KPERT)
*       Note KPERT = -1 or +1 for unperturbed or perturbed motion.
*
*       Form perturber list and restart KS motion if KPERT > 0.
          IF (KPERT.GE.0) THEN
              CALL KSLIST(IPAIR)
              IF (LIST(1,I1).GT.0) THEN
*        Resolve current coordinates & velocities and form new polynomial.
                  CALL KSRES(IPAIR,I1,I2,2,0.0D0)
                  CALL KSPOLY(IPAIR,1)
              END IF
          END IF
          GO TO 100
      END IF
*
*       Perform KS prediction of U, UDOT & H.
      CALL KSPRED(IPAIR,I1,I,BODYIN,UI,UIDOT,XI,VI)
*
*       Obtain the perturbing force & derivative.
      CALL KSPERT(I1,NNB0,XI,VI,FP,FD)
*
*       Save old radial velocity & relative perturbation and set new GAMMA.
      RDOT = TDOT2(IPAIR)
*     G0 = GAMMA(IPAIR)
      GI = SQRT(FP(1)**2 + FP(2)**2 + FP(3)**2)*R(IPAIR)**2*BODYIN
      GAMMA(IPAIR) = GI
*
*       Apply the Hermite corrector.
      CALL KSCORR(IPAIR,UI,UIDOT,FP,FD,TD2,TDOT4,TDOT5)
*
*       Increase regularization time-step counter and update the time.
      NSTEPU = NSTEPU + 1
      T0(I1) = TIME
*
*       Define useful scalars.
      RI = R(IPAIR)
      HI = H(IPAIR)
*
*       Include perturbation factor in predicted step.
      W1 = 0.5/ABS(HI)
      IF (GI.LT.0.0005) THEN
*       Use second-order expansion of cube root for small perturbations.
          W3 = 333.3*GI
          W2 = SQRT(W1)/(1.0 + W3*(1.0 - W3))
      ELSE
          W3 = 1.0 + 1000.0*GI
          W2 = SQRT(W1)/W3**0.3333
      END IF
*
*       Set new regularized step and convert to physical time units.
      DTU = ETAU*W2
      STEP(I1) = ((((0.2D0*TDOT5*DTU + 0.5D0*TDOT4)*DTU +
     &                       TDOT3(IPAIR))*ONE6*DTU + TD2)*DTU + RI)*DTU
      DTAU(IPAIR) = DTU
*
*       See whether the KS slow-down procedure is activated.
      IMOD = KSLOW(IPAIR)
      IF (IMOD.GT.1) THEN
          ZMOD = FLOAT(ISLOW(IMOD))
          STEP(I1) = ZMOD*STEP(I1)
      END IF
*
*       Check diagnostic print option.
      IF (KZ(12).GT.0) THEN
          WRITE (6,10)  IPAIR, TIME, H(IPAIR), RI, DTAU(IPAIR), GI,
     &                  IMOD
   10     FORMAT (3X,'KS MOTION',I3,2F10.4,F8.4,F7.3,1P,E9.1,0P,I4)
      END IF
*
*       Check optional output of periapse angle on unit #12.
      IF (KZ(30).EQ.0) GO TO 40
*
*       Evaluate Runge-Lenz eccentricity vector from physical variables.
      CALL KSRES(IPAIR,I1,I2,2,0.0D0)
      VI2 = 0.0
      RD = 0.0
      RR = 0.0
      DO 15 K = 1,3
          XI(K) = X(K,ICOMP) - X(K,JCOMP)
          VI(K) = XDOT(K,ICOMP) - XDOT(K,JCOMP)
          RR = RR + XI(K)**2
          VI2 = VI2 + VI(K)**2
          RD = RD + XI(K)*VI(K)
   15 CONTINUE
      RR = SQRT(RR)
      EI2 = 0.0
      DO 20 K = 1,3
          EI(K) = (VI2*XI(K) - RD*VI(K))/BODY(NTOT) - XI(K)/RR
          EI2 = EI2 + EI(K)**2
   20 CONTINUE
*       Save initial values for error plot.
      IF (EI0(1).EQ.0.0D0) THEN
          DO 25 K = 1,3
              EI0(K) = EI(K)
   25     CONTINUE
      ELSE
*       Construct cross product to yield deviation (in degrees).
          ERR = (EI(1)*EI0(2) - EI(2)*EI0(1))/EI2
          ERR = 360.0*ASIN(ERR)/TWOPI
          WRITE (12,30)  TIME/TWOPI, ERR
   30     FORMAT (' ',F12.6,1P,E12.4)
      END IF
*
*       Determine new perturbers for binary at apocentre turning point.
   40 IF (RDOT*TD2.GE.0.0D0) GO TO 100
      IF (RDOT.LT.0.0) GO TO 100
*
*       Set approximate value of next period.
      SEMI = -0.5D0*BODY(I)/HI
      TK = TWOPI*SEMI*SQRT(SEMI*BODYIN)
      IF (IMOD.GT.1) THEN
          TK = ZMOD*TK
      END IF
*
*       Use old perturber list if next apocentre is before the c.m. step.
      IF (TIME + TK.LT.T0(I) + STEP(I)) GO TO 100
*
*       Select new perturbers (adopt unperturbed period if none found).
**    CALL KSLIST(IPAIR)
*
  100 RETURN
*
      END
