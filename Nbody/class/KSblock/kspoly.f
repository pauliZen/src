      SUBROUTINE KSPOLY(IPAIR,IMOD)
*
*
*       Initialization of KS polynomials.
*       ---------------------------------
*
      INCLUDE 'common2.h'
      COMMON/SLOW/  RANGE,ISLOW(10)
      REAL*8  A1(3,4),A(8),FP(4),FPDOT(3),UI(4),UIDOT(4)
*
*
*       Specify indices of c.m. & components and perturber membership (+ 1).
      I = N + IPAIR
      I2 = 2*IPAIR
      I1 = I2 - 1
      NNB1 = LIST(1,I1) + 1
*
*       Initialize variables for accumulating contributions.
      DO 10 K = 1,3
          FP(K) = 0.0D0
          FPDOT(K) = 0.0D0
   10 CONTINUE
*
*       Obtain the perturbation & first derivative.
      DO 40 L = 2,NNB1
          J = LIST(L,I1)
*       Sum over both components (reverse sign for second component).
          II = I1
          DO 30 KCOMP = 1,2
              DO 25 K = 1,3
                  A(K) = X(K,J) - X(K,II)
                  A(K+3) = XDOT(K,J) - XDOT(K,II)
   25         CONTINUE
*       Current velocities are predicted in routines INTGRT, KSMOD, etc.
              RIJ2 = A(1)*A(1) + A(2)*A(2) + A(3)*A(3)
              A8 = BODY(J)/(RIJ2*SQRT(RIJ2))
              A9 = 3.0D0*(A(1)*A(4) + A(2)*A(5) + A(3)*A(6))/RIJ2
              IF (KCOMP.EQ.2) A8 = -A8
*
              DO 28 K = 1,3
                  FP(K) = FP(K) + A(K)*A8
                  FPDOT(K) = FPDOT(K) + (A(K+3) - A(K)*A9)*A8
   28         CONTINUE
              II = I2
   30     CONTINUE
   40 CONTINUE
*
*       Transform to regularized force derivative using T' = R.
      DO 45 K = 1,3
          FPDOT(K) = R(IPAIR)*FPDOT(K)
   45 CONTINUE
*
*       Save the relative perturbation.
      FP(4) = SQRT(FP(1)**2 + FP(2)**2 + FP(3)**2)
      GAMMA(IPAIR) = FP(4)*R(IPAIR)**2/BODY(I)
*
*       Set current transformation matrix.
      DO 48 K = 1,4
          UI(K) = U(K,IPAIR)
          UIDOT(K) = UDOT(K,IPAIR)
   48 CONTINUE
      CALL MATRIX(UI,A1)
*
*       Construct regularized polynomials from explicit derivatives.
      TDOT2(IPAIR) = 0.0D0
      TDOT3(IPAIR) = 0.0D0
      TDOT4 = 0.0D0
      HDOT(IPAIR) = 0.0D0
      HDOT2(IPAIR) = 0.0D0
      HDOT3(IPAIR) = 0.0D0
      HDOT4(IPAIR) = 0.0D0
*
*       Scale perturbing force & first derivative by modification factor.
      IF (IMOD.GT.1) THEN
          ZMOD = FLOAT(ISLOW(IMOD))
          DO 50 K = 1,3
              FP(K) = ZMOD*FP(K)
              FPDOT(K) = ZMOD*FPDOT(K)
   50     CONTINUE
      END IF
*
*       Form regularized force & two derivatives of time & binding energy.
      DO 60 K = 1,4
          A(K) = A1(1,K)*FP(1) + A1(2,K)*FP(2) + A1(3,K)*FP(3)
          A(K+4) = A1(1,K)*FPDOT(1) + A1(2,K)*FPDOT(2) +
     &                                A1(3,K)*FPDOT(3)
          FU(K,IPAIR) = 0.5D0*H(IPAIR)*U(K,IPAIR) + 0.5D0*R(IPAIR)*A(K)
          TDOT2(IPAIR) = TDOT2(IPAIR) + 2.0D0*U(K,IPAIR)*UDOT(K,IPAIR)
          TDOT3(IPAIR) = TDOT3(IPAIR) + 2.0D0*UDOT(K,IPAIR)**2 +
     &                                      2.0D0*U(K,IPAIR)*FU(K,IPAIR)
          HDOT(IPAIR) = HDOT(IPAIR) + 2.0D0*UDOT(K,IPAIR)*A(K)
          HDOT2(IPAIR) = HDOT2(IPAIR) + 2.0D0*FU(K,IPAIR)*A(K)
   60 CONTINUE
*
*       Set regularized velocity matrix (Levi-Civita matrix not required).
      CALL MATRIX(UIDOT,A1)
*
*       Include the whole (L*F)' term in explicit derivatives of FU & H.
      DO 65 K = 1,4
          A(K+4) = A(K+4) + A1(1,K)*FP(1) + A1(2,K)*FP(2) +
     &                                      A1(3,K)*FP(3)
          HDOT2(IPAIR) = HDOT2(IPAIR) + 2.0D0*UDOT(K,IPAIR)*A(K+4)
          FUDOT(K,IPAIR) = 0.5D0*(H(IPAIR)*UDOT(K,IPAIR) + 
     &                            HDOT(IPAIR)*U(K,IPAIR) +
     &                            TDOT2(IPAIR)*A(K) + R(IPAIR)*A(K+4))
          HDOT3(IPAIR) = HDOT3(IPAIR) + 2.0*FUDOT(K,IPAIR)*A(K) +
     &                                            4.0*FU(K,IPAIR)*A(K+4)
          TDOT4 = TDOT4 + 2.0*FUDOT(K,IPAIR)*U(K,IPAIR) +
     &                                     6.0*FU(K,IPAIR)*UDOT(K,IPAIR)
   65 CONTINUE
*
*       Assign a conservative value of the initial step (TD5 not included).
      FAC = 0.8
      IF (IMOD.GT.1) FAC = 1.0
      A2 = 0.5/ABS(H(IPAIR))
      DTU = FAC*ETAU*SQRT(A2)
      DTAU(IPAIR) = DTU
*
*       Convert regularized step to physical units and initialize time T0.
*     STEP(I1) = ((TDOT4/24.0D0*DTU + TDOT3(IPAIR)*ONE6)*DTU +
*    &                            0.5D0*TDOT2(IPAIR))*DTU + R(IPAIR)*DTU
*     IF (IMOD.GT.1) THEN
*         STEP(I1) = ZMOD*STEP(I1)
*     END IF
      STEP(I1) = R(IPAIR)*DTU
      T0(I1) = TIME
*
*       Include factorials in force and first derivative.
      DO 80 K = 1,4
          FU(K,IPAIR) = 0.5D0*FU(K,IPAIR)
          FUDOT(K,IPAIR) = ONE6*FUDOT(K,IPAIR)
          FUDOT2(K,IPAIR) = 0.0
          FUDOT3(K,IPAIR) = 0.0
   80 CONTINUE
*
      RETURN
*
      END
