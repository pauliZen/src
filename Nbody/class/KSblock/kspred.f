      SUBROUTINE KSPRED(IPAIR,I1,I,BODYIN,UI,UIDOT,XI,VI)
*
*
*       Prediction for KS regularization.
*       ---------------------------------
*
      INCLUDE 'common2.h'
      COMMON/ESTAB/  STAB
      REAL*8  UI(4),UIDOT(4),XI(6),VI(6),RDOT(3),A1(3,4)
      PARAMETER (ONE24=1.0/24.0D0,ONE120=1.0/120.0D0)
*
*
*       Add body #I to the perturber list for prediction.
**    NNB2 = LIST(1,I1) + 2
      NNB2 = LIST(1,I1) + 1
**    LIST(NNB2,I1) = I
*
*       Predict coordinates & velocities of perturbers & c.m. to order FDOT.
      DO 10 L = 2,NNB2
          J = LIST(L,I1)
          S = TIME - T0(J)
          S1 = 1.5*S
          S2 = 2.0*S
          X(1,J) = ((FDOT(1,J)*S + F(1,J))*S + X0DOT(1,J))*S + X0(1,J)
          X(2,J) = ((FDOT(2,J)*S + F(2,J))*S + X0DOT(2,J))*S + X0(2,J)
          X(3,J) = ((FDOT(3,J)*S + F(3,J))*S + X0DOT(3,J))*S + X0(3,J)
	  XDOT(1,J) = (FDOT(1,J)*S1 + F(1,J))*S2 + X0DOT(1,J)
	  XDOT(2,J) = (FDOT(2,J)*S1 + F(2,J))*S2 + X0DOT(2,J)
	  XDOT(3,J) = (FDOT(3,J)*S1 + F(3,J))*S2 + X0DOT(3,J)
   10 CONTINUE
*
*       Start prediction of regularized motion.
      DTU = DTAU(IPAIR)
*
*       Check for stabilization of binaries (skip #28 = 0 or GAMMA > GMAX).
      IF (KZ(28).GT.0.AND.GAMMA(IPAIR).LT.GMAX) THEN
          A2 = 2.0D0*(UDOT(1,IPAIR)**2 + UDOT(2,IPAIR)**2 +
     &                UDOT(3,IPAIR)**2 + UDOT(4,IPAIR)**2) -
     &                BODY(I) - H(IPAIR)*R(IPAIR)
*       Include the stabilization term in the predicted force only.
          STAB = 0.2D0*A2*BODYIN/DTU
      ELSE
          STAB = 0.0D0
      END IF
*
      DT = STEP(2*IPAIR-1)
      DO 20 K = 1,9
          UKSP(K,IPAIR) = ((ONE6*UKSD3(K,IPAIR)*DT +
     &                      0.5*UKSD2(K,IPAIR))*DT + UKSD(K,IPAIR))*DT
     &                      + UKS(K,IPAIR)
   20 CONTINUE
      DO 22 K = 1,4
          UI(K) = UKSP(K,IPAIR)
          UIDOT(K) = UKSP(K+4,IPAIR)
   22 CONTINUE
*       Predict U, UDOT & R to order FUDOT3 (set U5, U4 = 0 for lower order).
*     DO 20 K = 1,4
*         FSTAB = FU(K,IPAIR) - STAB*UDOT(K,IPAIR)
*         U4 = ONE24*FUDOT2(K,IPAIR)
*         U5 = ONE120*FUDOT3(K,IPAIR)
*         U4 = 0.0
*         U5 = 0.0
*         UI(K) = ((((U5*DTU + U4)*DTU + FUDOT(K,IPAIR))*DTU +
*    &                FSTAB)*DTU + UDOT(K,IPAIR))*DTU + U0(K,IPAIR)
*         UIDOT(K) = (((5.0*U5*DTU + 4.0*U4)*DTU +
*    &          3.0*FUDOT(K,IPAIR))*DTU + 2.0*FSTAB)*DTU + UDOT(K,IPAIR)
*  20 CONTINUE
      R(IPAIR) = UI(1)**2 + UI(2)**2 + UI(3)**2 + UI(4)**2
*
*       Form relative coordinates obtained from explicit KS transformation.
      Q1 = UI(1)**2 - UI(2)**2 - UI(3)**2 + UI(4)**2
      Q2 = UI(1)*UI(2) - UI(3)*UI(4)
      Q3 = UI(1)*UI(3) + UI(2)*UI(4)
      Q2 = Q2 + Q2
      Q3 = Q3 + Q3
*
*       Assign global coordinates of regularized components.
      A2 = BODY(I1+1)*BODYIN
      XI(1) = X(1,I) + A2*Q1
      XI(2) = X(2,I) + A2*Q2
      XI(3) = X(3,I) + A2*Q3
      XI(4) = XI(1) - Q1
      XI(5) = XI(2) - Q2
      XI(6) = XI(3) - Q3
*
*       Set current transformation matrix.
      CALL MATRIX(UI,A1)
*
*       Obtain relative velocities from KS transformation.
      RINV = 2.0D0/R(IPAIR)
      DO 30 L = 1,3
          RDOT(L) = 0.0D0
          DO 25 K = 1,4
              RDOT(L) = RDOT(L) + A1(L,K)*UIDOT(K)
   25     CONTINUE
          RDOT(L) = RDOT(L)*RINV
   30 CONTINUE
*
*       Set global velocities of KS components.
      VI(1) = XDOT(1,I) + A2*RDOT(1)
      VI(2) = XDOT(2,I) + A2*RDOT(2)
      VI(3) = XDOT(3,I) + A2*RDOT(3)
      VI(4) = VI(1) - RDOT(1)
      VI(5) = VI(2) - RDOT(2)
      VI(6) = VI(3) - RDOT(3)
*
      RETURN
*
      END
