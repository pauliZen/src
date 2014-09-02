      SUBROUTINE KSCORR(IPAIR,UI,UIDOT,FP,FD,TD2,TDOT4,TDOT5)
*
*
*       Corrector for KS motion.
*       -----------------------
*
      INCLUDE 'common2.h'
      COMMON/SLOW/  RANGE,ISLOW(10)
      COMMON/ESTAB/  STAB
      REAL*8  UI(4),UIDOT(4),FP(6),FD(6),FREG(4),FRD(4),A1(3,4),A(8),
     &        U2(4),U3(4),U4(4),U5(4)
      PARAMETER (ONE24=1.0/24.0D0)
*
*
*       Form new transformation matrix.
      CALL MATRIX(UI,A1)
*
*       Convert from physical to regularized derivative using T' = R.
      RI = R(IPAIR)
      DO 1 K = 1,3
          FD(K) = RI*FD(K)
    1 CONTINUE
*
*       Include KS slow-down factor in the perturbation if ZMOD > 1.
      IF (KZ(26).GT.0) THEN
          IMOD = KSLOW(IPAIR)
          IF (IMOD.GT.1) THEN
              ZMOD = FLOAT(ISLOW(IMOD))
              DO 5 K = 1,3
                  FP(K) = ZMOD*FP(K)
                  FD(K) = ZMOD*FD(K)
    5         CONTINUE
          END IF
      END IF
*
*       Predict H to order HDOT2.
      DTU = DTAU(IPAIR)
      HPRED = (0.5*HDOT2(IPAIR)*DTU + HDOT(IPAIR))*DTU + H(IPAIR)
*
*       Form twice regularized force and half first derivative of H.
      HD = 0.0D0
      TD2 = 0.0D0
      DO 10 K = 1,4
          A(K) = A1(1,K)*FP(1) + A1(2,K)*FP(2) + A1(3,K)*FP(3)
          A(K+4) = A1(1,K)*FD(1) + A1(2,K)*FD(2) + A1(3,K)*FD(3)
          FREG(K) = HPRED*UI(K) + RI*A(K)
          HD = HD + UIDOT(K)*A(K)
          TD2 = TD2 + UI(K)*UIDOT(K)
   10 CONTINUE
*
*       Set regularized velocity matrix (Levi-Civita matrix not required).
      CALL MATRIX(UIDOT,A1)
*
*       Include the whole (L*F)' term in explicit derivatives of FU & H.
      HD2 = 0.0D0
      DO 20 K = 1,4
          AK4 = A(K+4) + A1(1,K)*FP(1) + A1(2,K)*FP(2) + A1(3,K)*FP(3)
          HD2 = HD2 + FREG(K)*A(K) + 2.0D0*UIDOT(K)*AK4
          FRD(K) = HD*UI(K) + 0.5D0*(HPRED*UIDOT(K) + RI*AK4) + TD2*A(K)
*       Set half the regularized force.
          FREG(K) = 0.25D0*FREG(K)
   20 CONTINUE
*
*       Specify time-step factors.
      DTSQ = DTU**2
      DT6 = 6.0/(DTU*DTSQ)
      DT2 = 2.0/DTSQ
      DT13 = ONE3*DTU
      DTSQ12 = ONE12*DTSQ
      DT3 = ONE6*DTU
      DT4 = ONE24*DTU
      DT5 = 0.2D0*DTU
*
*       Form higher derivatives for U & UDOT (2*DF saves one multiply).
      DO 25 K = 1,4
	  DF = 4.0D0*(FU(K,IPAIR) - FREG(K))
          FD6 = 6.0D0*FUDOT(K,IPAIR)
	  SUM = FD6 + FRD(K)
	  SUM2 = SUM + FD6
	  AT3 = DF + DTU*SUM
	  BT2 = -1.5D0*DF - DTU*SUM2
*
*       Include the corrector (old formulation).
*         UI(K) = UI(K) + (0.6D0*AT3 + BT2)*DTSQ12
*         UIDOT(K) = UIDOT(K) + (0.75D0*AT3 + BT2)*DT13
*         U0(K,IPAIR) = UI(K)
*         U(K,IPAIR) = UI(K)
*         UDOT(K,IPAIR) = UIDOT(K)
*
*       Copy Taylor series derivatives (with stabilizer) at start of step.
          U2(K) = FU(K,IPAIR) - STAB*UDOT(K,IPAIR)
          U3(K) = FUDOT(K,IPAIR)
          U4(K) = BT2*DT2
          U5(K) = AT3*DT6
*
*       Save 1/2 force and 1/6 first derivative, also FUDOT2 & FUDOT3.
          FU(K,IPAIR) = FREG(K)
          FUDOT(K,IPAIR) = ONE6*FRD(K)
	  FUDOT2(K,IPAIR) = (3.0D0*AT3 + BT2)*DT2
	  FUDOT3(K,IPAIR) = AT3*DT6
*       NOTE: These are real derivatives!
   25 CONTINUE
*
*       Construct the complete solution of U and UDOT.
      DO 30 K = 1,4
          UI(K) = ((((U5(K)*DT5 + U4(K))*DT4 + U3(K))*DTU +
     &                U2(K))*DTU + UDOT(K,IPAIR))*DTU + U0(K,IPAIR)
          UIDOT(K) = (((0.25D0*U5(K)*DTU + U4(K))*DT3 +
     &                  3.0*U3(K))*DTU + 2.0*U2(K))*DTU + UDOT(K,IPAIR)
          U(K,IPAIR) = UI(K)
          U0(K,IPAIR) = UI(K)
          UDOT(K,IPAIR) = UIDOT(K)
   30 CONTINUE
*
*       Include standard corrector for the energy and save derivatives.
      HD = 2.0D0*HD
      DHD = HDOT(IPAIR) - HD
      SUM = HDOT2(IPAIR) + HD2
      SUM2 = SUM + HDOT2(IPAIR)
      AT3 = 2.0D0*DHD + SUM*DTU
      BT2 = -3.0D0*DHD - SUM2*DTU
*  
      H(IPAIR) = HPRED + (0.75D0*AT3 + BT2)*DT13
      HDOT(IPAIR) = HD
      HDOT2(IPAIR) = HD2
      HDOT3(IPAIR) = (3.0D0*AT3 + BT2)*DT2
      HDOT4(IPAIR) = AT3*DT6
*     WRITE (6,35)  H(IPAIR), HD, HD2, HDOT3(IPAIR), FP(1), FD(1)
*  35 FORMAT (' KSCORR:   H HD HD2 HD3 FP FD ',F10.4,F7.3,1P,4E9.1)
*
*       Form scalar terms for time derivatives (1/2 of TDOT4 & 1/4 of TDOT5).
      TD3 = 0.0D0
      TDOT4 = 0.0D0
      TDOT5 = 0.0D0
      DO 40 K = 1,4
          TD3 = TD3 + UIDOT(K)**2 + 2.0D0*UI(K)*FREG(K)
          TDOT4 = TDOT4 + UI(K)*FRD(K) + 6.0D0*UIDOT(K)*FREG(K)
          TDOT5 = TDOT5 + 0.5D0*FUDOT2(K,IPAIR)*UI(K) +
     &                          2.0D0*FRD(K)*UIDOT(K) + 6.0D0*FREG(K)**2
   40 CONTINUE
*
*       Save R and second & third time derivatives.
      R(IPAIR) = UI(1)**2 + UI(2)**2 + UI(3)**2 + UI(4)**2
      TDOT2(IPAIR) = 2.0D0*TD2
      TDOT3(IPAIR) = 2.0D0*TD3
*
      RETURN
*
      END
