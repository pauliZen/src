      SUBROUTINE KSINIT
*
*
*       Initialization of KS regularization.
*       ------------------------------------
*
      INCLUDE 'common2.h'
      REAL*8  Q(3),RDOT(3),UI(4),A1(3,4)
*
*
*       Initialize number of KS pairs, first star and new c.m. particle.
      NPAIRS = 1
      IFIRST = 2*NPAIRS + 1
      NTOT = N + NPAIRS
*
*       Set new global indices of the components and current pair index.
      ICOMP = 2*NPAIRS - 1
      JCOMP = ICOMP + 1
      IPAIR = NPAIRS
*
*       Specify mass for new c.m.
      BODY(NTOT) = BODY(ICOMP) + BODY(JCOMP)
*
*       Define c.m. coordinates & velocities and set XDOT for components.
      DO 10 K = 1,3
          X(K,NTOT) = (BODY(ICOMP)*X(K,ICOMP) + BODY(JCOMP)*X(K,JCOMP))/
     &                                                        BODY(NTOT)
          X0DOT(K,NTOT) = (BODY(ICOMP)*X0DOT(K,ICOMP) + BODY(JCOMP)*
     &                                        X0DOT(K,JCOMP))/BODY(NTOT)
          XDOT(K,NTOT) = X0DOT(K,NTOT)
          XDOT(K,ICOMP) = X0DOT(K,ICOMP)
          XDOT(K,JCOMP) = X0DOT(K,JCOMP)
   10 CONTINUE
*
*       Initialize neighbour list.
**    CALL NBLIST(NTOT,RSMIN)
      LIST(1,NTOT) = 0
*
*       Obtain force polynomials & steps for c.m. (treated as point-mass).
**    CALL FPOLY1(NTOT,NTOT)
**    CALL STEPS(NTOT,NTOT)
*
*       Define relative coordinates and velocities in physical units.
      DO 20 K = 1,3
          Q(K) = X(K,ICOMP) - X(K,JCOMP)
          RDOT(K) = X0DOT(K,ICOMP) - X0DOT(K,JCOMP)
   20 CONTINUE
*
*       Introduce regularized variables using definition of 1985 paper.
      R(IPAIR) = SQRT(Q(1)**2 + Q(2)**2 + Q(3)**2)
*
*       Initialize the regularized coordinates according to sign of Q(1).
      IF (Q(1).LE.0.0D0) THEN
          U(3,IPAIR) = 0.0D0
          U(2,IPAIR) = SQRT(0.5D0*(R(IPAIR) - Q(1)))
          U(1,IPAIR) = 0.5D0*Q(2)/U(2,IPAIR)
          U(4,IPAIR) = 0.5D0*Q(3)/U(2,IPAIR)
      ELSE
          U(4,IPAIR) = 0.0D0
          U(1,IPAIR) = SQRT(0.5D0*(R(IPAIR) + Q(1)))
          U(2,IPAIR) = 0.5D0*Q(2)/U(1,IPAIR)
          U(3,IPAIR) = 0.5D0*Q(3)/U(1,IPAIR)
      END IF
*
*       Set current transformation matrix.
      DO 25 K = 1,4
          UI(K) = U(K,IPAIR)
   25 CONTINUE
      CALL MATRIX(UI,A1)
*
*       Form regularized velocity and set initial KS coordinates.
      DO 30 K = 1,4
          UDOT(K,IPAIR) = 0.50D0*(A1(1,K)*RDOT(1) + A1(2,K)*RDOT(2) +
     &                                                  A1(3,K)*RDOT(3))
*       Note that A1(J,K) is the transpose of A1(K,J).
          U0(K,IPAIR) = U(K,IPAIR)
   30 CONTINUE
*
*       Evaluate initial binding energy per unit mass.
      H(IPAIR) = (2.0D0*(UDOT(1,IPAIR)**2 + UDOT(2,IPAIR)**2 +
     &                   UDOT(3,IPAIR)**2 + UDOT(4,IPAIR)**2) -
     &                                              BODY(NTOT))/R(IPAIR)
*
*       Initialize perturber list, c.m. step and index for slow KS.
**    CALL KSLIST(IPAIR)
      LIST(1,1) = 0
      STEP(NTOT) = 100.0
      KSLOW(IPAIR) = 1
*
*       Obtain polynomials for perturbed KS motion (standard case).
      CALL KSPOLY(IPAIR,1)
*
      WRITE (6,40)  TIME, DTAU(IPAIR), R(IPAIR), GAMMA(IPAIR),
     &              STEP(NTOT), LIST(1,ICOMP)
   40 FORMAT (/,' NEW KSREG    TIME =',F7.2,1P,4E9.1,0P,I4,/)
*
*       Prescribe large step for second component to avoid selection.
      STEP(JCOMP) = 1.0E+06
*
      RETURN
*
      END
