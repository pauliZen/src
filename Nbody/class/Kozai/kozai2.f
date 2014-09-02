*
*             K O Z A I
*             *********
*
*
*       Three-body regularization program with movie, Kozai, PN & spin.
*       ---------------------------------------------------------------
*
*       Method of Aarseth & Zare, Celestial Mechanics 10, 185.
*       ......................................................
*
*       Developed by Sverre Aarseth & Seppo Mikkola.
*       ............................................
*
      PROGRAM KOZAI
*
      IMPLICIT  REAL*8  (A-H,M,O-Z)
      COMMON/AZREG/  Q(8),P(8),R,R1,R2,ENERGY,M(3),X(3,3),XDOT(3,3),
     &               RCOLL,ERROR,C11,C12,C19,C20,C24,C25,NSTEPS,NAME(3)
      COMMON/HIARCH/  MB,MT,A0,A1,E0,E1,P0,P1,P1P0,RATIO,RI,SEMI,SEMI1,
     &                TIME,TPLOT,DTPLOT,RAP,VAP,TWOPI,NEXP
      COMMON/CLOSE/  RIJ(3,3),ICALL,NFN
      COMMON/BSSAVE/  EP(4),STEPC,TFAC,ITFAC,JC,NHALF2,IPERT
      COMMON/ANGLES/  TWOPI2,ALPHA,DEGREE
      COMMON/TBIN0/   RGRAV,SEMI0,ECC0,DB,I10,I20
      COMMON/PLUMMER/  ZMP,EPS2
      COMMON/POSTN/  CLIGHT,RZ,GAMMA,IPN,ISPIN
      COMMON/PNPERT/ GAMMA1,GAMMA2,GAMMA3
      REAL*8  Y(24),RK(3),M0(3),X0(3,3),V0(3,3),XX(3,3),XR(3),VR(3)
      REAL*8  EVEC0(3),EVEC(3),CMX(3),CMV(3),
     &        XN(3,3),VV(3,3),XCM(3),VCM(3)
      SAVE R10,R100,ITIME
      DATA R10,R100,ITIME /0.01D0,0.0D0,0/
*
*
*       COMMON variables
*       ****************
*
*       ------------------------------------------------------------------
*       C11     Inverse mass factor for DERQP (also C12,C19,C20,C24,C25).
*       CLIGHT  Speed of light in scaled units (3.0D+05/SQRT(GM/R)).
*       CMX     Centre of mass coordinates (affected by perturbation).
*       CMV     Centre of mass velocity.
*       ENERGY  Twice the initial total energy (simpler eqns of motion).
*       ERROR   Relative energy error at the end (ignore with T' = 1/U).
*       GAMMA   Relative perturbation due to active post-Newtonian terms.
*       ICALL   Indicator for pericentre check (first function call only).
*       M       Particle mass.
*       NAME    Particle identity (initialized to 1,2,3).
*       NFN     Number of function calls.
*       NSTEPS  Number of DIFSY calls.
*       P       Regularized momenta.
*       Q       Regularized coordinates.
*       R       Distance between M(1) and M(2) (not regularized).
*       R1      Distance between M(1) and M(3).
*       R2      Distance between M(2) and M(3).
*       RCOLL   Minimum two-body separation (osculating pericentre).
*       RIJ     Minimum pairwise separations (osculating pericentre).
*       X       Particle coordinates (X(3,I) is Z-component).
*       XDOT    Velocity components (XDOT(3,I) is Z-component).
*       ZMP     Mass of Plummer model.
*       EPS2    Plummer softening squared.
*       ------------------------------------------------------------------
*
*       Input Parameters
*       ------------------------------------------------------------------
*       TOL     Tolerance for Bulirsch-Stoer integrator.
*       TCRIT0  Maximum time (terminates on escape or TCRIT).
*       ECRIT   Energy error criterion (time reversal only).
*       IREV    Time reversal option (IREV = 0: standard).
*       IMOVE   Movie option (> 0).
*       XMAX    Maximum range (X & Y; movie option).
*       NWAIT   Delay loop (CALL WAIT; depends on CPU speed.
*       NEXP    Number of experiments.
*
*       ZMP     Mass of Plummer model (zero for isolated system).
*       EPS2    Plummer softening (square is saved).
*       CLIGHT  Speed of light (>100000: non-GR; =20: strong GR).
*       IPN     PN option (=1: PN1; =2: PN1 + PN2; =3: PN1->PN3).
*       ISPIN   Spin option (only for Post-Newtonian with IPN > 0).
*
*       E0      Inner eccentricity.
*       E1      Outer eccentricity.
*       A0      Inner semi-major axis.
*       A1      Outer semi-major axis.
*       M(1)    Outer orbit mass (perturber).
*       M(2)    Inner component mass.
*       M(3)    Mass of reference body (inner binary).
*       ZINC    Inclination (in degrees).
*
*       Standard template included (with movie but no Plummer):
*       1.0E-12 1.0D+06 0.001 0 0 160.0 200 0
*       0.0 1.0 60.0 0 0
*       0.90 0.5 10.0 100.0 1.0 8.0 10.0 0.0
*       ------------------------------------
*
*       Read and print main parameters (IREV > 0 for time reversal).
      READ (5,*)  TOL, TCRIT0, ECRIT, IREV, IMOVE, XMAX, NWAIT, NEXP
      WRITE (6,999)  TOL, TCRIT0, ECRIT, IREV, XMAX
  999 FORMAT (//,5X,'TOL =',1P,E9.2,'  TCRIT =',E9.2,'  ECRIT =',E8.1,
     &              '  IREV =',0P,I3,'  XMAX =',F6.1,/)
*
*       Read parameters for Plummer model and PN terms (IPN=0: experimental).
      READ (5,*)  ZMP, EPS2, CLIGHT, IPN, ISPIN
      EPS2 = EPS2**2
*
      TWOPI = 8.0D0*ATAN(1.0D0)
      DEGREE = 360.0D0/TWOPI
      DELTA = 0.0
      ALPHA = 0.0
      PC = 0.0
      SEMI = 0.0
      E = 0.0
      IESC = 0
      IHYP = 0
*
*       Specify the number of first-order equations for the integrator.
      N = 24
      IEXP = 0
*
*       Initialize optional movie (suppress if linking problem).
      IF (IMOVE.GT.0) THEN
          CALL MOVIE0(XMAX)
      END IF
*
      READ (5,*)  E0, E1, A0, A1, M(1), M(2), M(3), ZINC
*
*       Read the basic configuration.
    1 CALL DATA(ZINC)
*
*       Assume inner binary M(2) + M(3) with semi-major axis A0 (Msun & AU).
      VSTAR = 30.0*SQRT((M(2) + M(3))/A0)
      BETA = VSTAR/3.0D+05
      TKOZ = P1**2/P0*(M(2)+M(3))/M(1)*(1.0 - E1**2)**1.5
      TKOZ = 2.0/(3.0*TWOPI)*TKOZ
      WRITE (6,996)  VSTAR, BETA, TKOZ, ISPIN
  996 FORMAT (' INITIAL:    V* BETA TKOZ ISPIN ',1P,3E10.2,0P,I4/)
  900 CONTINUE
      IF (IEXP.GT.0) THEN
          IF (IEXP.GT.NEXP) STOP
          DO 903 I = 1,3
              M(I) = M0(I)
              DO 902 K = 1,3
                  DX = 0.0
                  IF (K.LE.2.AND.I.EQ.3) DX = 1.0D-06*FLOAT(IEXP)
                  X(K,I) = X0(K,I) + DX
                  XDOT(K,I) = V0(K,I)
                  XX(K,I) = X(K,I)
  902         CONTINUE
  903     CONTINUE
          GO TO 5
      END IF
*
*       Save the tolerance, repeat counter & initial condition.
      EPS = TOL
      IERR = 0
      DO 3 I = 1,3
          M0(I) = M(I)
          DO 2 K = 1,3
              X0(K,I) = X(K,I)
              V0(K,I) = XDOT(K,I)
              XX(K,I) = X(K,I)
    2     CONTINUE
    3 CONTINUE
*
    5 PERIM = 100.0
      ZMI1 = 1000.0
      ZMI2 = 1000.0
      ZMI3 = 1000.0
      ZMIN = 1000.0
*
*       Set control indicators.
      IRUN = 0
      ITER = 0
*       Specify step increase factor and initialization index for DIFSY.
      STEPC = 1.1D0
      JC = -1
      ITFAC = 1
*       Reduce step for GR movie (note possible problem with ZFAC = 0.1).
      ZFAC = 0.5
*       Avoid small movie steps for Plummer model.
      IF (ZMP.GT.0.0) ZFAC = 0.5
*
*       Initialize diagnostic variables & counters.
      R12MIN = 100.0
      RMIN = 100.0
      RCOLL = 100.0
      DO 10 J = 1,3
          DO 8 K = 1,3
              RIJ(J,K) = 100.0
    8     CONTINUE
   10 CONTINUE
      NSTEPS = 0
      NFN = 0
      NREG = 0
      ICALL = 0
      TFAC = 1.0
*
*       Initialize local time, regularized time and termination time..
      TIME = 0.0D0
      TAU = 0.0D0
      TCRIT = TCRIT0
*
*       Obtain initial energy and transform to regularized variables.
      IF (IRUN.EQ.0) CALL TRANSF(1)
*
*       Define gravitational radius and pericentre check distance.
      RGRAV = (M(1)*M(2) + M(1)*M(3) + M(2)*M(3))/(0.5D0*ABS(ENERGY))
      RSTAR = 0.5*RGRAV
*
*       Form the two smallest distances (assume sensible reference body).
      R1 = Q(1)**2 + Q(2)**2 + Q(3)**2 + Q(4)**2
      R2 = Q(5)**2 + Q(6)**2 + Q(7)**2 + Q(8)**2
*
      IPERT = 1
      IF (R2.LT.R1) IPERT = 2
*       Set termination distance to maximum of separation and 5*RGRAV (x 2).
      RMAX0 = 2.0*MAX(R1,R2,5.0*RGRAV)
***   IF (CLIGHT.LT.100000.0) RMAX0 = 1.0D+02
*
*       Specify the crossing time (also meaningful if ENERGY > 0).
      TCR = (M(1) + M(2) + M(3))**2.5/ABS(ENERGY)**1.5
*
*       Set step for time transformation DT/DTAU = 1.0/U (ignore M1*M2/R).
*     TPR = R1*R2/(M(1)*M(3)*R2 + M(2)*M(3)*R1)
*       Form basic time derivative (consult DERQP for TPR modification).
      TPR = R1*R2
*     TPR = R1*R2/SQRT(R1 + R2)
      DTAU0 = TCR*EPS**0.1/TPR
*
*       Try alternative expression for initial step (Seppo Mikkola).
      R0 = MAX(R1,R2)
      DTAU = 0.1*(EPS/1.0E-12)**0.1*R0*SQRT(R0/(M(1) + M(2) + M(3)))/TPR
      DTAU = 0.1*DTAU
*       Choose the smallest value (large ENERGY or TCR create problems).
      DTAU = MIN(DTAU0,DTAU)
*
*       Reduce step and switch off TFAC modification for large velocities.
      IF (ENERGY.GT.10.0*M(1)*M(3)/RGRAV) THEN
          ITFAC = 0
      END IF
*
*       Initialize C.M. variables.
      DO 14 K = 1,3
          CMX(K) = 0-.0
          CMV(K) = 0-.0
   14 CONTINUE
*
      IF (IERR.EQ.0) THEN
          WRITE (6,15)  RGRAV, R1, R2, 0.5*ENERGY
   15     FORMAT (5X,'RGRAV =',F7.3,'  R1 =',F7.3,'  R2 =',F7.3,
     &               '  ENERGY =',F12.6,/)
          CALL BINARY(IESC)
      END IF

*       Initialize time constant & input array for the integrator.
*     CONST = 0.0D0
      DO 20 K = 1,8
*         CONST = CONST + Q(K)*P(K)
          Y(K) = Q(K)
          Y(K+8) = P(K)
   20 CONTINUE
      DO 25 K = 1,3
          Y(16+K) = CMX(K)
          Y(19+K) = CMV(K)
   25 CONTINUE
      Y(23) = ENERGY
      Y(24) = 0.0
*
*       Produce initial output.
      IF (IREV.EQ.0) CALL TRANSF(2)
*
*       Advance the equations of motion by Bulirsch-Stoer integrator.
   30 IF (IMOVE.GT.0) DTAU = ZFAC*DTAU
*       Switch off GR perturbation for large CLIGHT.
      IF (CLIGHT.GE.100000.0) IPERT = 0
      CALL DIFSY1(N,EPS,DTAU,TAU,Y)
*
      IF (DTAU.EQ.0.0) THEN
          WRITE(6,*)  ' STEPSIZE = 0!', char(7)
          STOP
      END IF
*
*       Copy regularized coordinates & momenta and obtain physical time.
*     SUMQP = 0.0D0
      DO 35 K = 1,8
          Q(K) = Y(K)
          P(K) = Y(K+8)
*         SUMQP = SUMQP + Q(K)*P(K)
*       Note that the momentum includes factor of 2 in AZ formulation.
   35 CONTINUE
      DO 40 K = 1,3
          CMX(K) = Y(16+K)
          CMV(K) = Y(19+K)
   40 CONTINUE
*
*       Set explicit time (Baumgarte & Stiefel, 1974; Aarseth, 1976).
*     TEXP = (0.5D0*(SUMQP - CONST) - TAU)/ENERGY
      TIME = Y(24)
      ENERGY = Y(23)
*
*       Update relative distances (NB! not quite latest value).
      R1 = Q(1)**2 + Q(2)**2 + Q(3)**2 + Q(4)**2
      R2 = Q(5)**2 + Q(6)**2 + Q(7)**2 + Q(8)**2
*
*       Include test for post-Newtonian terms.
      IF (CLIGHT.LT.100000.0) THEN
*       Define dominant body index for routine DERQP.
          IPERT = 1
          IF (R2.LT.R1) IPERT = 2
          IP = IPERT
*       Define coalescence as 3 Schwarzschild radii.
          RZ = 6.0*(M(IP) + M(3))/CLIGHT**2
*       Transform to physical variables and obtain Newtonian elements.
          CALL TRANSF(3)
          IESC = 0
          CALL BINARY(IESC)
*       Experimental treatment for relevant PN energies (cf. Mora & Will).
          DO 240 K = 1,3
              XR(K) = X(K,IP) - X(K,3)
              VR(K) = XDOT(K,IP) - XDOT(K,3)
  240     CONTINUE
          V2 = VR(1)**2 + VR(2)**2 + VR(3)**2
          BETA = SQRT(V2)/CLIGHT
          SEMI = SEMI0
          IF (R1.LT.R10.AND.R10.GT.R100.AND.R1.GT.SEMI) THEN
          GM = M(IP) + M(3)
          CALL LENZ(GM,XR,VR,EVEC)
          DOM = 3.0*TWOPI*M(N)/(CLIGHT**2*SEMI*(1.0 - ECC0**2))
          DOM = 360.0*DOM/TWOPI
          IF (ITIME.EQ.0) THEN
          DO K = 1,3
              EVEC0(K) = EVEC(K)
          END DO
          END IF
          ITIME = ITIME + 1
          IF (ITIME.GT.1) THEN
          EZ = EVEC(1)*EVEC0(2) - EVEC(2)*EVEC0(1)
          EE0 =SQRT(EVEC(1)**2+EVEC(2)**2)*SQRT(EVEC0(1)**2+EVEC0(2)**2)
          ALPHA = ASIN(EZ/EE0)
          IF (ALPHA.LT.0.0) ALPHA = TWOPI + ALPHA
          ALPHA = 360.0*ALPHA/TWOPI
          IF (MOD(NSTEPS,100).EQ.0) THEN
              WRITE (15,241)  TIME, ALPHA, DOM, SEMI
  241         FORMAT (' ',1P,E12.4,0P,2F11.3,1P,E15.6)
          END IF
          DO K = 1,3
              EVEC0(K) = EVEC(K)
          END DO
          END IF
          DO I = 1,3
          DO K = 1,3
              XN(K,I) = X(K,I)
              VV(K,I) = XDOT(K,I)
          END DO
          END DO
          I1 = 1
          IF (R2.LT.R1) I1 = 2
          I2 = 3
          MB = M(I1) + M(I2)
          DO K = 1,3
              XCM(K) = (M(I1)*X(K,I1) + M(I2)*X(K,I2))/MB
              VCM(K) = (M(I1)*XDOT(K,I1) + M(I2)*XDOT(K,I2))/MB
          END DO
          IF (MOD(NSTEPS,100).EQ.0) THEN
          CALL INC(XN,VV,XCM,VCM,ALPHA)
          ZI = 360.0*ALPHA/TWOPI
          WRITE (11,242)  TIME, ZI, DOM
  242     FORMAT (' ',1P,E12.4,2E10.2)
          END IF
          END IF
          R100 = R10
          R10 = R1
*
*       Distinguish between elliptic and hyperbolic case.
          IF (ECC0.LT.1.0) THEN
*       Obtain specific binding energies for each active two-body term.
          CALL GRBIN(M(IP),M(3),XR,VR,SEMI,ECC,EBIN)
          ECC0 = ECC
          IF (MOD(NSTEPS,100).EQ.0) THEN
              WRITE (8,243)  TIME, SEMI, ECC, EBIN
  243         FORMAT (' ',1P,3E12.4,E15.7)
          END IF
          ECC2 = ECC**2
          FE = 1.0 + (73.0/24.0 + 37.0*ECC2/96.0)*ECC2
          GE = (1.0 - ECC2)**3.5/FE
          RATIO = M(IP)/M(3)
*       Replace physical time-scale by N-body units (cf. Lee 1993).
*         TZ = TAUGR*GE*SEMI**4/(RATIO*(1.0 + RATIO)*M(3)**3)
          TZ = GE*SEMI**4/(RATIO*(1.0 + RATIO)*M(3)**3)
          TZ = 5.0/64.0*CLIGHT**5*TZ
*       Form time-scale for the rate of perihelion advance (TK/PDOT).
          PDOT = 3.0*BETA**2/(1.0 - ECC2)
          TK = TWOPI*SEMI*SQRT(SEMI/(M(IP) + M(3)))
          TP = TK/PDOT
*
*       Include decision-making for adding more PN terms.
          IF (TZ.LT.2.0*TIME.AND.IPN.LT.3) THEN
              IPN = 3
              WRITE (6,245)  IPN, NAME(IP), TIME, BETA, GAMMA, TZ
  245         FORMAT (' PN SWITCH!    IPN NAME T V/C GAMMA TZ ',
     &                                2I3,1X,1P,4E9.1)
          ELSE IF (TZ.LT.5.0*TIME.AND.IPN.LT.2) THEN
              IPN = 2
              WRITE (6,245)  IPN, NAME(IP), TIME, BETA, GAMMA, TZ
          ELSE IF (TZ.LT.10.0*TIME.AND.IPN.LT.1) THEN
              IPN = 1
              WRITE (6,245)  IPN, NAME(IP), TIME, BETA, GAMMA, TZ
          END IF
*
          IF (NSTEPS.EQ.0) THEN
              WRITE (6,255)  RZ, BETA, TZ, TP, IPN
  255         FORMAT (5X,'RELATIVISTIC    RZ =',1P,E8.1,'  V/C =',E9.2,
     &                   '  TZ =',E8.1,'  TK/TP =',E8.1,'  IPN =',0P,I2)
          END IF
*
          ELSE
*       Treat hyperbolic case using BETA instead of TZ.
          IF (IHYP.EQ.0) THEN
              WRITE (6,260)  RZ, BETA, ECC0, IPN
  260         FORMAT (5X,'RELATIVISTIC    RZ =',1P,E8.1,'  V/C =',E8.1,
     &                                 '  ECC =',0P,F6.3,'  IPN =',I2)
              IHYP = 1
          END IF
*
*       Include decision-making for adding more PN terms.
          IF (BETA.GT.0.1.AND.IPN.LT.3) THEN
              IPN = 3
              WRITE (6,270)  IPN, NAME(IP), TIME, BETA, GAMMA, ECC0
  270         FORMAT (' PN SWITCH!    IPN NAME T V/C GAMMA ECC',
     &                                2I3,1X,1P,4E9.1)
          ELSE IF (BETA.GT.0.05.AND.IPN.LT.2) THEN
              IPN = 2
              WRITE (6,270)  IPN, NAME(IP), TIME, BETA, GAMMA, ECC0
          ELSE IF (BETA.GT.0.01.AND.IPN.LT.1) THEN
              IPN = 1
              WRITE (6,270)  IPN, NAME(IP), TIME, BETA, GAMMA, ECC0
          END IF
*
*       Check whether to reduce the number of PN terms (SEMI < 0 only).
          IF (IPN.EQ.3.AND.BETA.LT.0.1) THEN
              IPN = 2
              WRITE (6,270)  IPN, NAME(IP), TIME, BETA, GAMMA, ECC0
          ELSE IF (IPN.EQ.2.AND.BETA.LT.0.05) THEN
              IPN = 1
              WRITE (6,270)  IPN, NAME(IP), TIME, BETA, GAMMA, ECC0
          ELSE IF (IPN.EQ.1.AND.BETA.LT.0.01) THEN
              IPN = 0
              WRITE (6,270)  IPN, NAME(IP), TIME, BETA, GAMMA, ECC0
          END IF
          END IF
*       Include termination test for GR coalescence.
          IF (MIN(R1,R2).LT.RZ) GO TO 90
      ELSE
          CALL TRANSF(3)
          IESC = 0
          CALL BINARY(IESC)
          IF (MOD(NSTEPS,100).EQ.0) THEN
              WRITE (8,242)  TIME, SEMI0, ECC0
          END IF
      END IF
*
*       Check minimum two-body separations and increase step counter.
      RMIN = MIN(RMIN,R)
      RM = MIN(R1,R2)
      R12MIN = MIN(R12MIN,RM)
      RMAX = MAX(R1,R2,R)
      NSTEPS = NSTEPS + 1
*
*       Check minimum two-body separations.
      RK(1) = R1
      RK(2) = R2
      RK(3) = R
*       Consider pairs 1-2, 1-3 & 2-3 with identified names.
      DO 44 K = 1,3
          DO 42 L = K+1,3
              I = NAME(K)
              J = NAME(L)
*       Use cyclic loop index (3,1,2) for distances R, R1 & R2.
              KK = K - 1
              IF (KK.EQ.0) KK = 3
              RIJ(I,J) = MIN(RIJ(I,J),RK(KK))
              RIJ(J,I) = MIN(RIJ(J,I),RK(KK))
   42     CONTINUE
   44 CONTINUE
*
*       Switch on search indicator inside RSTAR (reset in DERQP).
      IF (RM.LT.RSTAR) THEN
          ICALL = 1
      END IF
*
*       Determine pericentre & impact parameter during forward motion.
      IF (IRUN.EQ.0.AND.R1 + R2 + R.LT.PERIM) THEN
          PERIM = R1 + R2 + R
          IF (PERIM.LT.3.0*RGRAV) THEN
              CALL IMPACT(PC)
          END IF
      END IF
*
*       Record minimum moment of inertia during forward integration.
      IF (IRUN.EQ.0) THEN
          ZMI = R1**2 + R2**2 + R**2
          ZMI1 = ZMI2
          ZMI2 = ZMI3
          ZMI3 = ZMI
          IF (ZMI3.GT.ZMI2.AND.ZMI2.LT.ZMI1) THEN
              ZMIN = MIN(ZMI2,ZMIN)
          END IF
      END IF
*
*       Include optional movie (PGPLOT or X11). 
      IF (IMOVE.GT.0) THEN
          DO 45 L = 1,3
              IF (NAME(L).EQ.1) I1 = L
              IF (NAME(L).EQ.2) I2 = L
              IF (NAME(L).EQ.3) I3 = L
   45     CONTINUE
          CALL TRANSF(3)
          DO 48 I = 1,3
*       Add c.m. coordinates in case of external perturbation.
              DO 46 K = 1,3
                  XX(K,I) = X(K,I) + CMX(K)
   46         CONTINUE
   48     CONTINUE
          CALL MOVIE(I1,I2,I3,XX,TIME)
          ZZ = 0.0
          DO 49 KK = 1,NWAIT
              CALL WAIT(KK,ZZ)
   49     CONTINUE
*       Include dummy stop to fool the compiler.
          IF (ZZ.LT.-1.0) STOP
      END IF
*
*       Use actual two-body force to decide on switching.
      F12 = (M(1) + M(2))/R**2
      F13 = (M(1) + M(3))/R1**2
      F23 = (M(2) + M(3))/R2**2
      IF (F12.LT.MAX(F13,F23)) GO TO 70
*
      IMIN = 1
*       Use a simple distance test to determine new reference body IMIN.
      IF (R2.LT.1.00001*R1) IMIN = 2
*
*       Transform to physical variables and rename the exchanged particles.
      CALL TRANSF(3)
*
      DO 50 K = 1,3
          TEMP1 = X(K,3)
          TEMP2 = XDOT(K,3)
          X(K,3) = X(K,IMIN)
          XDOT(K,3) = XDOT(K,IMIN)
          X(K,IMIN) = TEMP1
          XDOT(K,IMIN) = TEMP2
   50 CONTINUE
*
      TEMP1 = M(3)
      M(3) = M(IMIN)
      M(IMIN) = TEMP1
      NAME3 = NAME(3)
      NAME(3) = NAME(IMIN)
      NAME(IMIN) = NAME3
*
*       Transform back to regularized variables and initialize input array.
      CALL TRANSF(4)
      DO 60 K = 1,8
          Y(K) = Q(K)
          Y(K+8) = P(K)
   60 CONTINUE
*
*       Increase regularization counter at the end of switching procedure.
      NREG = NREG + 1
*
*       Update relative distances (NB! New R becomes largest old R1 or R2).
      R = MAX(R1,R2)
      R1 = Q(1)**2 + Q(2)**2 + Q(3)**2 + Q(4)**2
      R2 = Q(5)**2 + Q(6)**2 + Q(7)**2 + Q(8)**2
      IPERT = 1
      IF (R2.LT.R1) IPERT = 2
*
*       Check termination criteria (TIME > TCRIT or RMAX > RMAX0).
   70 CONTINUE
*       Save current step for possible reversal after small step.
      IF (IREV.GT.0.AND.ITER.EQ.0) DTAU0 = DTAU
*       Suppress next line for termination at exact TCRIT with iteration.
      IF (TIME.GT.TCRIT.AND.(IRUN.EQ.0.OR.IREV.EQ.0)) GO TO 90
*
*       Include iteration to exact TCRIT for time reversal.
      IF ((IREV.GT.0.OR.IRUN.EQ.0).AND.
     &    (TIME.GT.TCRIT.OR.ITER.GT.0)) THEN
          IF (ABS(TIME - TCRIT).LT.1.0E-12.AND.IRUN.GT.0) GO TO 120
          IF (ABS(TIME - TCRIT).LT.1.0E-12.AND.IRUN.EQ.0) THEN
              ITER = 0
              GO TO 90
          END IF
*       Begin iteration for termination at TCRIT (NB! use correct TPR).
          DTAU = (TCRIT - TIME)/(R1*R2)
*         DTAU = DTAU*SQRT(R1 + R2)
*       Note extra scaling of STEP to compensate for movie reduction.
          IF (IMOVE.GT.0) DTAU = DTAU/ZFAC
*       ------------------------------------------------------------
*       Include alternative time transformation (N = 24; see DERQP).
*         U = M(1)*M(3)*R2 + M(2)*M(3)*R1 + M(1)*M(2)*R1*R2/R
*         DTAU = DTAU*U
*       ------------------------------------------------------------
          ITER = ITER + 1
          IF (ITER.LE.10) GO TO 30
      END IF
      IF (RMAX.LT.RMAX0.AND.TIME.LT.TCRIT) GO TO 30
*
*       Obtain final output after transforming to physical variables.
   90 CALL TRANSF(2)
*
*       Perform binary analysis.
      IESC = 1
      CALL BINARY(IESC)
*
*       Print diagnostics during forward run.
      IF (IRUN.EQ.0) THEN
          RCOLL = MIN(RCOLL,R12MIN)
          WRITE (6,95)  TIME, RMIN, R12MIN, RCOLL, RMAX, ERROR, NSTEPS,
     &                  NREG
   95     FORMAT  (/,'  TIME =',1P,E9.2,'  MIN(R) =',E8.1,
     &               '  MIN(R1,R2) =',E8.1,'  RCOLL =',E8.1,
     &               '  RMAX =',E8.1,'  DE/E =',E9.1,'  NSTEPS =',I8,
     &               '  NREG =',I3)
          WRITE (6,100)  RIJ(1,2), RIJ(1,3), RIJ(2,3), RCOLL
  100     FORMAT (' RIJ:  1-2 1-3 2-3 RCOLL ',1P,4E10.2)
          IF (MIN(R1,R2).LT.RZ) THEN
              WRITE (6,105)  R1, R2, 0.5*ENERGY
  105         FORMAT (' GR COALESCENCE!    R1 R2 ENERGY  ',1P,3E10.2)
          END IF
      END IF
*
*       Check time reversal indicator.
      IF (IREV.GT.0) THEN
          IF (IRUN.EQ.0) THEN
              TCRIT = TIME
              TAU = 0.0D0
              DTAU = 0.5*DTAU0
              Y(24) = 0.0D0
              NSTEPS = 0
              NREG = 0
              NFN0 = NFN
              NFN = 0
*       Initialize time constant & input array for the integrator.
*             CONST = 0.0D0
              DO 110 K = 1,8
                  P(K) = -P(K)
                  Y(K) = Q(K)
                  Y(K+8) = P(K)
*                 CONST = CONST + Q(K)*P(K)
  110         CONTINUE
              DO 115 K = 1,3
                  CMV(K) = -CMV(K)
                  Y(19+K) = CMV(K)
  115         CONTINUE
              IRUN = IRUN + 1
          END IF
          GO TO 30
      END IF
*
*       Continue with the next experiment.
      IEXP = IEXP + 1
      IF (IMOVE.GT.0) CALL MOVIE1
      IF (IEXP.GT.0) GO TO 900
*
*       Transform to physical variables and evaluate time reversal errors.
  120 CALL TRANSF(3)
      ERRX = 0.0
      ERRV = 0.0
      DO 130 I = 1,3
          L = NAME(I)
          DO 125 K = 1,3
              ERRX = ERRX + (X(K,I) - X0(K,L))**2
              ERRV = ERRV + (XDOT(K,I) + V0(K,L))**2
  125     CONTINUE
  130 CONTINUE
      ERRX = SQRT(ERRX/3.0)
      ERRV = SQRT(ERRV/3.0)
      RCOLL = MIN(RCOLL,R12MIN)
*       Obtain angle of escape in degrees.
      ANGLE = ATAN2(XDOT(2,IESC),XDOT(1,IESC))
      IF (ANGLE.LT.0.0) ANGLE = ANGLE + TWOPI
      ANGLE = DEGREE*ANGLE
*
*       Include final output after possible time iteration.
      IF (IREV.EQ.0.AND.IRUN.EQ.0) THEN
          CALL TRANSF(2)
          WRITE (6,95)  TIME, RMIN, R12MIN, RCOLL, RMAX, ERROR, NSTEPS,
     &                  NREG
          STOP
      END IF
*
      WRITE (10,135)  NSTEPS, NFN0, NFN, ERROR, ERRX, ERRV, EPS, TIME,
     &                SEMI, E
  135 FORMAT (' ',I4,2I7,1P,E9.1,3E9.1,0P,F7.2,2F7.4)
*
*       Print diagnostic (successful run on unit #7, unsuccessful on #8).
      IF (MAX(ERRX,ERRV).LT.ECRIT) THEN
          WRITE (7,140)  IEXP, TIME, DELTA, ALPHA, IESC, PC, ANGLE,
     &                   SEMI, E, RCOLL, PERIM, ZMIN, ERRX, ERRV, EPS
  140     FORMAT (I5,F7.1,F8.4,F8.2,I3,F7.3,F7.1,2F7.3,1P,6E10.2)
      ELSE
          WRITE (8,140)  IEXP, TIME, DELTA, ALPHA, IESC, PC, ANGLE,
     &                   SEMI, E, RCOLL, PERIM, ZMIN, ERRX, ERRV, EPS
*
*       Reduce tolerance by 100 and try again (until limit of 1.0E-15).
          IERR = IERR + 1
          IF (IERR.LT.7.AND.EPS.GT.0.99E-13) THEN
              EPS = 0.01*EPS
              DO 150 I = 1,3
                  M(I) = M0(I)
                  NAME(I) = I
                  DO 145 K = 1,3
                      X(K,I) = X0(K,I)
                      XDOT(K,I) = V0(K,I)
  145             CONTINUE
  150         CONTINUE
              GO TO 5
          END IF
      END IF
*
*       Continue with the next experiment.
      IEXP = IEXP + 1
      CALL MOVIE1
      GO TO 900
*
      END
