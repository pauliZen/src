      SUBROUTINE KSRES(J,J1,J2,KCASE,RIJ2)
*
*
*       Current coordinates & velocities of KS pair.
*       --------------------------------------------
*
      INCLUDE 'common2.h'
      COMMON/SLOW/  RANGE,ISLOW(10)
      REAL*8  UI(4),RDOT(3),V(4),A1(3,4)
*
*
*       Resolve components of pair #J at curent time.
      J2 = J + J
      J1 = J2 - 1
      A2 = 1.0/R(J)
      A3 = A2*(TIME - T0(J1))
      IF (KSLOW(J).GT.1) THEN
          IMOD = KSLOW(J)
          A3 = A3/FLOAT(ISLOW(IMOD))
      END IF
*
*       Convert physical interval to regularized time (second order).
      DTU = (1.0 - 0.5D0*TDOT2(J)*A2*A3)*A3
*     A4 = 3.0D0*TDOT2(J)**2*A2 - TDOT3(J)
*       Convert physical interval to regularized time (third order).
*     DTU = ((ONE6*A4*A3 - 0.5D0*TDOT2(J))*A2*A3 + 1.0)*A3
*
*       Predict regularized coordinates to order FU (or FUDOT?).
      DO 10 K = 1,4
              UI(K) = (FU(K,J)*DTU + UDOT(K,J))*DTU + U0(K,J)
*             UI(K) = ((FUDOT(K,J)*DTU + FU(K,J))*DTU + UDOT(K,J))*DTU +
*    &                                                           U0(K,J)
   10 CONTINUE
*
*       Employ KS transformation.
      Q1 = UI(1)**2 - UI(2)**2 - UI(3)**2 + UI(4)**2
      Q2 = UI(1)*UI(2) - UI(3)*UI(4)
      Q3 = UI(1)*UI(3) + UI(2)*UI(4)
      Q2 = Q2 + Q2
      Q3 = Q3 + Q3
      J3 = N + J
      A2 = BODY(J2)/BODY(J3)
*
*       Set global coordinates of regularized components.
      X(1,J1) = X(1,J3) + A2*Q1
      X(2,J1) = X(2,J3) + A2*Q2
      X(3,J1) = X(3,J3) + A2*Q3
      X(1,J2) = X(1,J1) - Q1
      X(2,J2) = X(2,J1) - Q2
      X(3,J2) = X(3,J1) - Q3
*
*       See whether velocities are needed.
      IF (KCASE.EQ.1) GO TO 40
*
*       Set current transformation matrix and two-body separation.
      CALL MATRIX(UI,A1)
      RI = UI(1)**2 + UI(2)**2 + UI(3)**2 + UI(4)**2
      RINV = 2.0/RI
*
*       Convert physical interval to regularized time (third order).
*     A4 = 3.0D0*TDOT2(J)**2*A2 - TDOT3(J)
*     DTU = ((ONE6*A4*A3 - 0.5D0*TDOT2(J))*A2*A3 + 1.0)*A3
*     DTU2 = ONE6*DTU
*
*       Predict regularized velocity.
      DO 20 K = 1,4
          V(K) = (3.0*FUDOT(K,J)*DTU + 2.0*FU(K,J))*DTU + UDOT(K,J)
*         V(K) = ((FUDOT2(K,J)*DTU2 + 3.0*FUDOT(K,J))*DTU +
*    &                                2.0*FU(K,J))*DTU + UDOT(K,J)
   20 CONTINUE
*
*       Obtain relative velocities from KS transformation.
      DO 30 L = 1,3
          RDOT(L) = 0.0D0
          DO 25 K = 1,4
              RDOT(L) = RDOT(L) + A1(L,K)*V(K)
   25     CONTINUE
          RDOT(L) = RDOT(L)*RINV
   30 CONTINUE
*
*       Set global velocities of KS components.
      XDOT(1,J1) = XDOT(1,J3) + A2*RDOT(1)
      XDOT(2,J1) = XDOT(2,J3) + A2*RDOT(2)
      XDOT(3,J1) = XDOT(3,J3) + A2*RDOT(3)
      XDOT(1,J2) = XDOT(1,J1) - RDOT(1)
      XDOT(2,J2) = XDOT(2,J1) - RDOT(2)
      XDOT(3,J2) = XDOT(3,J1) - RDOT(3)
*
   40 RETURN
*
      END
