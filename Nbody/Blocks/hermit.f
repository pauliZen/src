*
*            H E R M I T 5
*            *************
*
*       Hermite block-step KS & PN toy code.
*       ------------------------------------
*
*       Sverre Aarseth & Keigo Nitadori.
*       ................................
*
      PROGRAM HERMIT5
*
      INCLUDE 'common2.h'
      INTEGER NEXTL(100),LISTKS(100)
*
*
*       Read input parameters and initialize KS block-steps.
      CALL INPUT
      CALL IBLOCK
*
*       Set useful parameters (including many binaries).
      TBLOCK = 0.125/1024.0
      N = 20
      NP = 10
      NP = 1
      NPAIRS = 0
      DX = 1.0D-05
      DX0 = DX
      DZ = 10.0*DX
      ECC = 0.9
      ECC = 0.99
*
*       Include special case of one KS binary with PN.
      IF (KZ(11).NE.0) GO TO 35
*
*       Define multiple binary orbits (X & X0DOT required).
      DO 30 IPAIR = 1,NP
          I1 = 2*IPAIR - 1
          I2 = I1 + 1
          DO 10 K = 1,3
              X(K,I1) = 0.0
              X(K,I2) = 0.0
              X0DOT(K,I1) = 0.0
              X0DOT(K,I2) = 0.0
   10     CONTINUE
          BODY(I1) = 1.0D-04
          BODY(I2) = 1.0D-04
          X(1,I1) =  FLOAT(IPAIR)*DX
          X(1,I2) = -FLOAT(IPAIR)*DX
*       Assign different c.m. positions.
          X(3,I1) = IPAIR*DZ
          X(3,I2) = IPAIR*DZ
          SEMI = ABS(X(1,I1) - X(1,I2))/(1.0 + ECC)
          VREL = SQRT((BODY(I1)+BODY(I2))/SEMI*(1.0 - ECC)/(1.0 + ECC))
          X0DOT(2,I1) =  VREL*BODY(I2)/(BODY(I1) + BODY(I2))
          X0DOT(2,I2) = -VREL*BODY(I1)/(BODY(I1) + BODY(I2))
   30 CONTINUE
*
   35 CONTINUE
*       Initialize KS and set quantized values of STEP.
      DO 40 IP = 1,NP
          CALL KSINIT
          I1 = 2*IP - 1
          DT = STEP(I1)
          CALL STEPK(DT,DTN)
          STEP(I1) = DTN
   40 CONTINUE
*
*       Evaluate initial two-body elements for test purposes.
      SEMI0 = -0.5*BODY(N+1)/H(1)
      TK = TWOPI*SEMI0*SQRT(SEMI0/BODY(N+1))
      ECC2 = (1.0 - R(1)/SEMI0)**2 + TDOT2(1)**2/(BODY(N+1)*SEMI0)
      ECC0 = SQRT(ECC2)
*
      WRITE (6,50)  ECC0, SEMI0, R(1), TDOT2(1), TK
   50 FORMAT (' BINARY    E A R TD2 TK  ',F10.5,1P,4E10.2)
*       Scale output times by Kepler period.
      DELTAT = DELTAT*TK
      TCRIT = TCRIT*TK
      TNEXT = DELTAT
*
*       Determine quantized value of TMIN.
   60 TMIN = TBLOCK
      DO 70 IP = 1,NPAIRS
        I1 = 2*IP - 1
        LISTKS(IP) = I1
        TMIN = MIN(T0(I1) + STEP(I1),TMIN)
   70 CONTINUE
*
*       Form list of binaries due at TMIN.
      LENGTH = 0
      DO 80 L = 1,NPAIRS
        J = LISTKS(L)
        IF (T0(J) + STEP(J).EQ.TMIN) THEN
          LENGTH = LENGTH + 1
          NEXTL(LENGTH) = J
        END IF
   80 CONTINUE
*       Note case of LENGTH = 0 should not occur.
*
*       Begin KS integration loop.
      LI = 1
   90 I1 = NEXTL(LI)
      TIME = T0(I1) + STEP(I1)
      CALL KSINT(I1)
*       Include diagnostic output and decision-making for first binary.
      IP = KVEC(I1)
      IF (IP.EQ.1) THEN
*       Note highest accuracy is after corrector.
          CALL CHECK(IP)
      END IF
*
      LI = LI + 1
      IF (LI.LE.LENGTH) GO TO 90
      IF (TIME.LT.TBLOCK) GO TO 60
*
*       Advance block-step time to represent single stars.
      TBLOCK = TBLOCK + 0.125
      IF (TBLOCK.LT.TCRIT) GO TO 60
*
      STOP
*
      END
