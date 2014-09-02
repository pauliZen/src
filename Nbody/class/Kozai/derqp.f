      SUBROUTINE DERQP(Q,P,CMX,CMV,ENERGY,TIME,QPR,PPR,DX,DV,EPR,TPR)
*
*
*       Equations of motion (version 9/9/01).
*       -------------------------------------
*
      IMPLICIT REAL*8  (A-H,M,O-Z)
      COMMON/AZREG/  V(8),W(8),R,R1,R2,EDUM,M(3),X(3,3),XDOT(3,3),
     &               RCOLL,ERROR,C11,C12,C19,C20,C24,C25,NSTEPS,NAME(3)
*       Note COMMON locations of Q & P are replaced by dummy variables.
      COMMON/CLOSE/  RIJ(3,3),ICALL,NFN
      COMMON/PLUMMER/  ZMP,EPS2
      COMMON/POSTN/  CLIGHT,RZ,GDUM,IPN,ISPIN
      COMMON/BSSAVE/  EP(4),STEPC,TFAC,ITFAC,JC,NHALF2,IPERT
      REAL*8  Q(8),P(8),QPR(8),PPR(8),RK(2),QP(6),P2(2),R12(3),
     &        SIGN(4),QQP(8),PQP(8),QR(8),Q1(8),Q2(9),
     &        ACC(9),DRDQ(8),QF(8),CMX(3),CMV(3),DX(3),DV(3),FCM(3)
      REAL*8  XX(3),VV(3),P1(9),VELOC(9),GR(3)
      REAL*8  SPIN(3),DV3(3),DSPIN(3)
      DATA  SIGN /1.0D0,-1.0D0,-1.0D0,1.0D0/
*
      SPIN(1) = 0.0
      SPIN(2) = 0.7
      SPIN(3) = 0.7
      DSPIN(1) = 0.0
      DSPIN(2) = 0.0
      DSPIN(3) = 0.0
*
*       Increase function evaluation counter and initialize vectors.
      NFN = NFN + 1
      DO 1 K = 1,6
         QP(K) = 0.0
         IF (K.LE.3) R12(K) = 0.0
    1 CONTINUE
*
*       Construct scalar distances and vector product Q*P (note old refs).
      DO 3 K = 1,2
          KS = 4*(K-1)
          KS1 = KS + 1
          KS2 = KS + 2
          RK(K) = 0.0
          P2(K) = 0.0
          SS = 1.0
          LS = 2
          DO 2 L = 1,4
              RK(K) = RK(K) + Q(KS+L)**2
              P2(K) = P2(K) + P(KS+L)**2                         !C9 & C10
              QP(K) = QP(K) + SIGN(L)*Q(KS+L)*P(KS+L)            !C3 & C4
              QP(K+2) = QP(K+2) + SS*SIGN(L)*Q(KS+LS)*P(KS+L)    !C5 & C6
              IF (KS2 + L.GT.KS + 4) KS2 = KS - 2
              QP(K+4) = QP(K+4) + Q(KS2+L)*P(KS+L)               !C7 & C8
              LS = LS - 1
              IF (LS.EQ.0) LS = 4
*       Reverse sign factor to obtain correct expression.
              SS = -SS
              QQP(KS+L) = 0.0
              PQP(KS+L) = 0.0
              QR(KS+L) = 0.0
    2     CONTINUE
    3 CONTINUE
*
*       Obtain the distance vector R1 - R2 and scalar value..
      R1 = RK(1)
      R2 = RK(2)
      KS = 0
      SS = 1.0
      DO 4 L = 1,4
          LS = L
          IF (L.GE.3) LS = L + 2
          R12(1) = R12(1) + SIGN(L)*(Q(L)**2 - Q(L+4)**2)        !C21
          R12(2) = R12(2) + 2.0D0*SIGN(L)*Q(KS+1)*Q(KS+2)        !C22
          R12(3) = R12(3) + 2.0D0*SS*SIGN(L)*Q(LS)*Q(LS+2)       !C23
          KS = KS + 2
          SS = -SS
    4 CONTINUE
      RR = R12(1)**2 + R12(2)**2 + R12(3)**2
      R = SQRT(RR)
      A = C25/R
*
*       Set first derivative of the physical time (standard transformation).
      TPR = R1*R2
      B = A*TPR/RR
      ZM = M(1) + M(2) + M(3)
*
*       Combine vectorial components with relevant coefficients.
      DO 6 K = 1,2
          KS = 4*(K-1)
          K7 = 7 - K
          LS = 2
          SS = 1.0
          DO 5 L = 1,4
              LK = KS + 2 + L
              IF (LK.GT.KS+4) LK = KS + L - 2
              QQP(KS+L) = QQP(KS+L) + SIGN(L)*Q(KS+L)*QP(K7-4) +
     &                    SS*Q(KS+LS)*QP(K7-2) + Q(LK)*QP(K7)    !S2
              PQP(KS+L) = PQP(KS+L) + SIGN(L)*P(KS+L)*QP(K7-4) +
     &                    SS*P(KS+LS)*QP(K7-2) + P(LK)*QP(K7)    !S5
*       Note opposite sign for second component.
              IF (K.EQ.1) THEN
                  QR(KS+L) = QR(KS+L) + SIGN(L)*Q(KS+L)*R12(1) +
     &                       SS*Q(KS+LS)*R12(2) + Q(LK)*R12(3)   !S8
              ELSE
                  QR(KS+L) = QR(KS+L) - SIGN(L)*Q(KS+L)*R12(1) -
     &                       SS*Q(KS+LS)*R12(2) - Q(LK)*R12(3)   !S8
              END IF
              LS = LS - 1
*       Start the third index at 4 and reverse sign factor.
              IF (LS.EQ.0) THEN
                  LS = 4
                  SS = -1.0
              END IF
    5     CONTINUE
    6 CONTINUE
*
*       Include optional Plummer force.
      IF (ZMP.GT.0.0D0) THEN
          DO 7 K = 1,8
              V(K) = Q(K)
              W(K) = P(K)
    7     CONTINUE
          CALL TRANSF(3)
          DO 9 I = 1,3
              DO 8 K = 1,3
                  X(K,I) = X(K,I) + CMX(K)
    8         CONTINUE
    9     CONTINUE
          CALL PLPERT(ACC)
      ELSE
          DO 10 K = 1,9
              ACC(K) = 0.0
   10     CONTINUE
      END IF
*
*       Check GR perturber option which also requires DX and DV.
      IF (IPERT.GT.0) THEN
*       Transform dominant KS pair M1,M2 to physical variables.
          M1 = M(IPERT)
          M2 = M(3)
          K = 4*(IPERT-1)
*
*       Obtain relative coordinates (eqn (52) of AZ).
          XX(1) = Q(K+1)**2 - Q(K+2)**2 - Q(K+3)**2 + Q(K+4)**2
          XX(2) = 2.0D0*(Q(K+1)*Q(K+2) - Q(K+3)*Q(K+4))
          XX(3) = 2.0D0*(Q(K+1)*Q(K+3) + Q(K+2)*Q(K+4))
*
          DO 11 KCOMP = 1,2
              K = 4*(KCOMP - 1)
*       Form product of half Levi-Civita matrix & regularized momenta.
              P1(K+1) = Q(K+1)*P(K+1) - Q(K+2)*P(K+2) - Q(K+3)*P(K+3)
     &                                                + Q(K+4)*P(K+4)
              P1(K+2) = Q(K+2)*P(K+1) + Q(K+1)*P(K+2) - Q(K+4)*P(K+3)
     &                                                - Q(K+3)*P(K+4)
              P1(K+3) = Q(K+3)*P(K+1) + Q(K+4)*P(K+2) + Q(K+1)*P(K+3)
     &                                                + Q(K+2)*P(K+4)
*
*       Evaluate scalar distance.
              RK1 = Q(K+1)**2 + Q(K+2)**2 + Q(K+3)**2 + Q(K+4)**2
              IF (KCOMP.EQ.IPERT) RR = RK1
*
*       Set absolute momenta for M(1) & M(2) in P1(1-3) & P1(5-7) (eqn (53)).
              P1(K+1) = 0.5D0*P1(K+1)/RK1
              P1(K+2) = 0.5D0*P1(K+2)/RK1
              P1(K+3) = 0.5D0*P1(K+3)/RK1
   11     CONTINUE
*
*       Form relative velocity of M(IPERT) wrt reference body.
          DO 12 K = 1,3
              K1 = 3*(IPERT - 1)
              VELOC(K) = P1(K)/M(1)
              VELOC(K+3) = P1(K+4)/M(2)
              VELOC(K+6) = -(P1(K) + P1(K+4))/M(3)
              VV(K) = (VELOC(K1+K) - VELOC(K+6))
   12     CONTINUE
*
*       Obtain the external post-Newtonian force (up to PN3 for IPN <= 3).
          CALL XTPERT(M1,M2,XX,VV,GR)
*
*       Check optional GR spin for maximum mass.
          IF (IPN.GT.0.AND.ISPIN.GT.0) THEN
              MX = MAX(M1,M2)
              MY = MIN(M1,M2)
              CALL gopu_SpinTerms(XX,VV,rr,MX,MY,clight,spin,dv3,dspin)
              DO K = 1,3
                  GR(K) = GR(K) + DV3(K)
              END DO
          END IF
*
*       ======================================================
*       Include coalescence termination inside 3 Schwarzschild radii.
*         IF (MIN(R1,R2).LT.RZ) THEN
*       NB! premature termination may occur for intermediate tolerance.
*             WRITE (6,13)  R1, R2
*  13         FORMAT (' COALESCENCE!    R1 R2 ',1P,2E10.2)
*             DO 14 K = 1,8
*                 V(K) = Q(K)
*                 W(K) = P(K)
*  14         CONTINUE
*             WRITE (6,15)  NSTEPS, TIME, RZ
*  15         FORMAT (' NSTEPS TIME RZ  ',I6,F8.2,1P,E10.2)
*             STOP
*       Note that termination test may be needed inside the BS step (or NAN).
*         END IF
*       ======================================================
*
*       Form the c.m. acceleration.
      DO 16 K = 1,3
          FCM(K) = 0.0
   16 CONTINUE
      DO 20 I = 1,3
          IK = 3*(I - 1)
          DO 18 K = 1,3
              FCM(K) = FCM(K) + M(I)*ACC(IK+K)/ZM
   18     CONTINUE
   20 CONTINUE
*
*       Convert to regularized derivatives for c.m. integration.
      DO 25 K = 1,3
          DX(K) = CMV(K)*TPR
          DV(K) = FCM(K)*TPR
   25 CONTINUE
*
*       Add the perturbation to possible Plummer acceleration.
      K1 = 3*(IPERT - 1)
      DO 23 K = 1,3
*       Split the PN part by mass ratio to preserve relative amount.
          ACC(K+K1) = ACC(K+K1) + M(3)/(M1 + M(3))*GR(K)
          ACC(K+6) = ACC(K+6) - M1/(M1 + M(3))*GR(K)
   23 CONTINUE
*
*       Construct the mass-weighted relative perturbing force.
      DO 30 KCOMP = 1,2
          K1 = 3*(KCOMP - 1)
          K2 = KCOMP - 1 
          K12 = K1 + K2
          L = 3 - KCOMP
          L3 = 3*(L - 1)
          DO 28 K = 1,3
*       Adopt simplified expression (original book Eq.(5.35) suppressed).
              DRDQ(K+K12) = - M(KCOMP)*(M(L)*(ACC(K+K1) - ACC(L3+K))
     &                      + M(3)*(ACC(K+K1) - ACC(K+6)))/ZM
*             DRDQ(K+K12) = - (M(1)*M(2)*(ACC(K+3) - ACC(K))*(-1)**KCOMP
*    &                      + M(KCOMP)*M(3)*(ACC(K+K1) - ACC(K+6)))/ZM
   28     CONTINUE
          DRDQ(4+K12) = 0.0
   30 CONTINUE
*
*       Form product of Q and perturbing force (cf. QFORCE in chain code).
      DO 40 KCOMP = 1,2
          KS = 4*(KCOMP - 1)
          QF(KS+1) =  Q(KS+1)*DRDQ(KS+1) + Q(KS+2)*DRDQ(KS+2) +
     &                                     Q(KS+3)*DRDQ(KS+3)
          QF(KS+2) = -Q(KS+2)*DRDQ(KS+1) + Q(KS+1)*DRDQ(KS+2) +
     &                                     Q(KS+4)*DRDQ(KS+3)
          QF(KS+3) = -Q(KS+3)*DRDQ(KS+1) - Q(KS+4)*DRDQ(KS+2) +
     &                                     Q(KS+1)*DRDQ(KS+3)
          QF(KS+4) =  Q(KS+4)*DRDQ(KS+1) - Q(KS+3)*DRDQ(KS+2) +
     &                                     Q(KS+2)*DRDQ(KS+3)
   40 CONTINUE
*
*       Include factor 2 in transpose Levi-Civita matrix A_k.
      DO 45 I = 1,8
          QF(I) = 2.0*QF(I)
   45 CONTINUE
*
      ELSE
*       Specify zero c.m. derivatives in isolated case.
          DO 26 K = 1,3
              DX(K) = 0.0
              DV(K) = 0.0
   26     CONTINUE
      END IF
*
*       Form derivatives for standard equations of motion.
      RL = R2
      QFAC = C11*RL
      PFAC = RL*ENERGY - C12*P2(2) + C19 + A*RL
      DO 50 I = 1,8
          QPR(I) = QFAC*P(I) + C24*QQP(I)
          PPR(I) = PFAC*Q(I) - C24*PQP(I) - B*QR(I)
          IF (I.EQ.4) THEN
              RL = R1
              QFAC = C12*RL
              PFAC = RL*ENERGY - C11*P2(1) + C20 + A*RL
          END IF
   50 CONTINUE
*
*       Include energy and momentum derivatives for GR case (TPR = R1*R2).
      EPR = 0.0
      IF (IPERT.GT.0) THEN
          DO 55 I = 1,8
              EPR = EPR - QPR(I)*QF(I)
              PPR(I) = PPR(I) - TPR*QF(I)
   55     CONTINUE
*       Use twice E' since ENERGY is 2*E.
          EPR = 2.0*EPR
      END IF
*
*       Check tolerance scaling TFAC = TPR*U (unless using t' = 1/U).
      IF (ITFAC.GT.0) THEN
*       Note Seppo's comment in DIFSY1 re use of different TPR.
          TFAC = M(3)*(M(1)*R2 + M(2)*R1)
*         ITFAC = -1
      END IF
*
*       -------------------------------------
*       Use standard formulation (extra part has been tested OK).
      IF (KS.GT.0) RETURN
*       NB! Replace DO 55 loop by DO 65 for extra stabilization.
*       --------------------------------------
*
*       Adopt stabilization with DT/DTAU = 1/U (Cortina paper 1976).
      GAMMA = 0.5D0*(-R1*R2*ENERGY + R2*C11*P2(1) + R1*C12*P2(2) -
     &        C20*R2 - C19*R1 - A*TPR) +
     &        C24*(QP(1)*QP(2) + QP(3)*QP(4) + QP(5)*QP(6))
      U = M(1)*M(3)*R2 + M(2)*M(3)*R1 + 0.5D0*A*TPR
      G2 = 1.0/U
*     G2 = 1.0/SQRT(R1 + R2)
      TPR = TPR*G2
*
*     IF (ITFAC.NE.0) THEN
          TFAC = TFAC*G2
*         ITFAC = 0
*     END IF
*
*       Include stabilization terms due to modified time transformation.
      GAMMA = G2*GAMMA
*     GAMMA = 0.0
*     S6 = C19 + A*R2
      DO 60 I = 1,8
          QPR(I) = G2*QPR(I)
          PPR(I) = G2*(PPR(I) + GAMMA*Q(I))
*         PPR(I) = G2*(PPR(I) + GAMMA*(S6*Q(I) - B*QR(I)))
*         IF (I.EQ.4) S6 = C20 + A*R1
   60 CONTINUE
*
*       NB! Replace DO 55 loop if used with G2 stabilization.
*     EPR = 0.0
*     DO 65 I = 1,8
*         EPR = EPR - QPR(I)*QF(I)
*         PPR(I) = PPR(I) - TPR*QF(I)
*  65 CONTINUE
*     EPR = 2.0*EPR        !Use twice E' since ENERGY is 2*E.
*
      IF (IPERT.GT.0) THEN
          DO 66 K = 1,3
              DX(K) = G2*DX(K)
              DV(K) = G2*DV(K)
   66     CONTINUE
      END IF
*
*       Check minimum two-body separation (first call only!).
   70 IF (ICALL.EQ.0) RETURN
*
*       Set minimum configuration index & separation.
      IF (R1.LT.R2) THEN
          IM = 1
          RI = R1
      ELSE
          IM = 2
          RI = R2
      END IF
*
*       Determine the osculating pericentre by Mikkola's algorithm.
      K = 1 + 4*(IM - 1)
      CALL PERI(Q(K),QPR(K),TPR,M(IM),M(3),QPERI)
*
*       Define relative perturbation on the close pair.
      GI = 2.0*M(3-IM)*(RI/R)**3/(M(IM) + M(3))
*
*       Identify the close bodies and check mutual distances.
      IF (GI.LT.0.005) THEN
          I = NAME(IM)
          J = NAME(3)
          RIJ(I,J) = MIN(RIJ(I,J),QPERI)
          RIJ(J,I) = MIN(RIJ(J,I),QPERI)
      END IF
*
*       Ckeck minimum two-body distance and switch off indicator.
      IF (GI.LT.0.005) RCOLL = MIN(RCOLL,QPERI)
      ICALL = 0
*
      RETURN
*
      END
