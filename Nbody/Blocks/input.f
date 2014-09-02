      SUBROUTINE INPUT
*
*
*       Input of KS parameters.
*       -----------------------
*
      INCLUDE 'common2.h'
      COMMON/POSTN/  CLIGHT,RZ,GAM,DEGR,IPN
      DATA KZ /40*0/
*
*
*       Input parameters and options.
*       -----------------------------------------------------------------
*       ETAU    Regularized time-step factor (2*pi/ETAU steps per orbit).
*       GMIN    Unperturbed perturbation limit (not used).
*       DELTAT  Output time interval (Kepler periods).
*       TCRIT   Termination time.
*       KZ(11)  Post-Newtonian effect (reads E, A, KZ(30), CLIGHT).
*       KZ(12)  Diagnostic output after each step.
*       KZ(26)  Slow-down procedure.
*       KZ(28)  Energy stabilization.
*       KZ(30)  Runge--Lenz eccentricity vector.
*       ECC     Eccentricity.
*       SEMI    Semi-major axis.
*       KZ(30)  Option for plotting error of periapse angle.
*       Template: 0.2 1.0D-06 0 0 0 100.0 1000.0
*                 0.9 1.0 0
*       -----------------------------------------------------------------
*
*       Read input parameters & options.
      READ (5,*)  ETAU, GMIN, KZ(11), KZ(12), KZ(26), KZ(28), DELTAT,
     &            TCRIT
      KZ(30) = 0
      WRITE (6,1)  ETAU, DELTAT, TCRIT, KZ(11), KZ(12), KZ(26), KZ(28)
    1 FORMAT (' ETAU =',F5.2,'  DT =',F6.1,'  TCR =',F7.1,
     &            '  #11 =',I3,'  #12 =',I3,'  #26 =',I3,'  #28 =',I3)
*
*       Read initial conditions for binary and copy X0DOT (for KSINIT).
*     DO 5 I = 1,2
*         READ (5,*)  BODY(I),(X(K,I),K=1,3),(XDOT(K,I),K=1,3)
*         DO 4 K = 1,3
*             X0DOT(K,I) = XDOT(K,I)
*   4     CONTINUE
*   5 CONTINUE
*
*       Define masses M1 & M2 and place c.m. body at the centre.
      BODY(1) = 0.5
      BODY(2) = 0.5
      BODY(1) = 7.4471D-03
      BODY(2) = 7.4471D-03
      BODY(3) = BODY(1) + BODY(2)
      DO 20 I = 1,3
          DO 10 K = 1,3
              X(K,I) = 0.0
              XDOT(K,I) = 0.0
              X0DOT(K,I) = 0.0
   10     CONTINUE
   20 CONTINUE
*
*       Read two-body elements and specify binary at apocentre on x-axis.
      IF (KZ(11).NE.0) THEN
          READ (5,*) ECC, SEMI, CLIGHT
          VAP = SQRT(BODY(3)/SEMI*(1.0 - ECC)/(1.0 + ECC))
          XDOT(2,2) = VAP
          X0DOT(2,2) = VAP
          X(1,2) = SEMI*(1.0 + ECC)
          XDOT(3,2) = 1.0D-04
          X0DOT(3,2) = 1.0D-04
          RZ = 6.0*BODY(3)/CLIGHT**2
      ELSE
          CLIGHT = 1.0D+06
          DEGR = 0.0
          RZ = 0.0
      END IF
*
*       Initialize time, counters and parameters.
      IPN = 0
      TIME = 0.0
      NSTEPU = 0
      NKSPER = 0
      NPRECT = 0
      TWOPI = 8.0*ATAN(1.0D0)
      GMAX = 0.001
      ONE3 = 1.0/3.0D0
      ONE6 = 1.0/6.0D0
      ONE12 = 1.0/12.0D0
      CMSEP2 = 1.0/GMIN**0.666667
      DO 30 J = 1,KMAX
          KVEC(2*J-1) = J
          KVEC(2*J) = J
   30 CONTINUE
*
      RETURN
*
      END
