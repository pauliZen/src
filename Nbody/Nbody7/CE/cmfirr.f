      SUBROUTINE CMFIRR(I,IPAIR,XI,XIDOT,FIRR,FD)
*
*
*       Irregular c.m. force & derivative.
*       ----------------------------------
*
      INCLUDE 'common6.h'
***** Note:set radius criterion----------------------------------------**
      COMMON/WL/ WL_RADIUS
      REAL*8  WL_RADIUS, WL_A(3), WL_V(3), WL_LM(4), WL_M, WL_RIJ2
*     --10/25/12 17:37-lwang-end-close encounter------------------------*
      REAL*8  XI(3),XIDOT(3),FIRR(3),FD(3),DX(3),DV(3),FP(6),FPD(6)

*
*
*       Initialize the perturbing force & first derivative.
      DO 1 K = 1,6
          FP(K) = 0.0D0
          FPD(K) = 0.0D0
    1 CONTINUE
*
*       Set individual KS components and indicators for unresolved pair.
      I2 = 2*IPAIR
      I1 = I2 - 1
      KDUM = 0
      IFP = 0
*
*       Specify perturber indices for decision-making.
      NP = LIST(1,I1)
      LP = 2
      JP = LIST(2,I1)
*
*       Perform irregular force loop for perturbed c.m.
      NNB0 = LIST(1,I)
      DO 20 LL = 2,NNB0+1
          K = LIST(LL,I)
*       Advance lower perturber index (includes possible old neighbour).
    2     IF (K.GT.JP.AND.LP.LE.NP) THEN
              LP = LP + 1
              JP = LIST(LP,I1)
*       Include rare case of two consecutive previous neighbours.
              GO TO 2
          END IF
*
*       Distinguish between nearby perturber and more distant neighbour.
          IF (K.NE.JP) THEN
              IF (K.LE.N) GO TO 10
*       Check c.m. approximation (point-mass assumption OK for #I).
              A1 = X(1,K) - XI(1)
              A2 = X(2,K) - XI(2)
              A3 = X(3,K) - XI(3)
              RIJ2 = A1*A1 + A2*A2 + A3*A3
              IF (RIJ2.GT.CMSEP2*R(K-N)**2) GO TO 10
              KDUM = 2*(K - N) - 1
              IF (LIST(1,KDUM).EQ.0) GO TO 10
              K = KDUM
              GO TO 10
*       Consider more carefully the case of identified perturber.
          ELSE
*       Determine next perturber index (if any).
              IF (LP.LE.NP) THEN
                  LP = LP + 1
                  JP = LIST(LP,I1)
              END IF
*       Specify first KS component if #JP is perturbed c.m.
              IF (K.GT.N) THEN
                  KDUM = 2*(K - N) - 1
                  IF (LIST(1,KDUM).GT.0) THEN
                      K = KDUM
                  END IF
              END IF
          END IF
*
*       Evaluate perturbation on first component due to body #K.
          IFP = 1
    4     dr2 = 0.0
          drdv = 0.0
          DO 5 L = 1,3
              dx(L) = X(L,K) - X(L,I1)
              dv(L) = XDOT(L,K) - XDOT(L,I1)
              dr2 = dr2 + dx(L)**2
              drdv = drdv + dx(L)*dv(L)
    5     CONTINUE
*
          dr2i = 1.0/dr2
          dr3i = BODY(K)*dr2i*SQRT(dr2i)
          drdv = 3.0*drdv*dr2i
*
          DO 6 L = 1,3
              FP(L) = FP(L) + dx(L)*dr3i
              FPD(L) = FPD(L) + (dv(L) - dx(L)*drdv)*dr3i
    6     CONTINUE
*
*       Evaluate perturbation on second component due to body #K.
          dr2 = 0.0
          drdv = 0.0
          DO 7 L = 1,3
              dx(L) = X(L,K) - X(L,I2)
              dv(L) = XDOT(L,K) - XDOT(L,I2)
              dr2 = dr2 + dx(L)**2
              drdv = drdv + dx(L)*dv(L)
    7     CONTINUE
*
          dr2i = 1.0/dr2
          dr3i = BODY(K)*dr2i*SQRT(dr2i)
          drdv = 3.0*drdv*dr2i
*
          DO 8 L = 1,3
              FP(L+3) = FP(L+3) + dx(L)*dr3i
              FPD(L+3) = FPD(L+3) + (dv(L) - dx(L)*drdv)*dr3i
    8     CONTINUE
*
          IF (K.GT.KDUM) GO TO 20
          K = K + 1
          GO TO 4
*
*       Sum over components of pair #J or its c.m. using c.m. approximation.
   10     dr2 = 0.0
          drdv = 0.0
          DO 12 L = 1,3
              dx(L) = X(L,K) - XI(L)
              dv(L) = XDOT(L,K) - XIDOT(L)
              dr2 = dr2 + dx(L)**2
              drdv = drdv + dx(L)*dv(L)
   12     CONTINUE
*
          dr2i = 1.0/dr2
          dr3i = BODY(K)*dr2i*SQRT(dr2i)
          drdv = 3.0*drdv*dr2i
*
          DO 14 L = 1,3
              FIRR(L) = FIRR(L) + dx(L)*dr3i
              FD(L) = FD(L) + (dv(L) - dx(L)*drdv)*dr3i
   14     CONTINUE
          IF (K.EQ.KDUM) THEN
              K = K + 1
              GO TO 10
          END IF
   
   20 CONTINUE
*
*       Add mass-weighted perturbations to force & first derivative.
      IF (IFP.GT.0) THEN
          BODYIN = 1.0/BODY(I)
          DO 30 K = 1,3
              FIRR(K) = (BODY(I1)*FP(K) + BODY(I2)*FP(K+3))*BODYIN +
     &                                                           FIRR(K)
              FD(K) = (BODY(I1)*FPD(K) + BODY(I2)*FPD(K+3))*BODYIN +
     &                                                             FD(K)
   30     CONTINUE
      END IF
*
*       Check force correction due to regularized chain.
      IF (NCH.GT.0) THEN
          CALL KCPERT(I,I1,FIRR,FD)
      END IF

*     --10/30/12 14:43-lwang-CE-single-single---------------------------*
***** Note:single particle close encounter-----------------------------**
      DO 200 LL = 2,NNB0+1
          K = LIST(LL,I)
          WL_M=body(I1)+body(I2)
          WL_A(1)=X(1,K)-(body(I1)*X(1,I1)+body(I2)*X(1,I2))/WL_M
          WL_A(2)=X(2,K)-(body(I1)*X(2,I1)+body(I2)*X(2,I2))/WL_M
          WL_A(3)=X(3,K)-(body(I1)*X(3,I1)+body(I2)*X(3,I2))/WL_M
          WL_V(1)=XDOT(1,K)-(body(I1)*XDOT(1,I1)+
     &         body(I2)*XDOT(1,I2))/WL_M
          WL_V(2)=XDOT(2,K)-(body(I1)*XDOT(2,I1)+
     &         body(I2)*XDOT(2,I2))/WL_M
          WL_V(3)=XDOT(3,K)-(body(I1)*XDOT(3,I1)+
     &         body(I2)*XDOT(3,I2))/WL_M
          WL_RIJ2=WL_A(1)*WL_A(1)+WL_A(2)*WL_A(2)+WL_A(3)*WL_A(3)
          if (WL_RIJ2.LT.WL_RADIUS) then
*             write (6,*) 'lW_CE: time in f :', Time
*             call flush(6)
             if (K.GT.N) then
                WL_LM(1)=body(I1)
                WL_LM(2)=body(I2)
                WL_LM(3)=body(2*(k-N)-1)
                WL_LM(4)=body(2*(k-N))
                call storece(name(I1),name(I2),name(2*(k-N)-1),
     &               name(2*(k-N)),WL_LM,WL_A,WL_V,Time)
             else
                WL_LM(1)=body(I1)
                WL_LM(2)=body(I2)
                WL_LM(3)=body(k)
                call storece(name(I1),name(I2),name(K),0,WL_LM,
     &               WL_A,WL_V,Time)
             end if
          end if
 200   continue
*     --10/30/12 14:43-lwang-end-CE-------------------------------------*
*
      RETURN
*
      END
