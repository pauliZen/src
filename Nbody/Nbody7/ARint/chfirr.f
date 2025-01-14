      SUBROUTINE CHFIRR(I,IR,XI,XIDOT,FIRR,FD)
*
*
*       Irregular force & derivative on chain c.m.
*       ------------------------------------------
*
      INCLUDE 'common6.h'
      REAL*8  M,MASS,MC
      PARAMETER  (NMX=10,NMX3=3*NMX,NMXm=NMX*(NMX-1)/2)
      COMMON/ARCHAIN/XCH(NMX3),VCH(NMX3),WTTL,M(NMX),
     &           XCDUM(NMX3),WCDUM(NMX3),MC(NMX),
     &           ZI(NMX3),VI(NMX3),MASS,RINV(NMXm),RSUM,INAME(NMX),NN
      COMMON/CHAINC/  XC(3,NCMAX),UC(3,NCMAX),BODYC(NCMAX),ICH,
     &                LISTC(LMAX)
      COMMON/CHREG/  TIMEC,TMAX,RMAXC,CM(10),NAMEC(NMX),NSTEP1,KZ27,KZ30
      COMMON/CPERT/  RGRAV,GPERT,IPERT,NPERT
      REAL*8  XI(3),XIDOT(3),DX(3),DV(3),FIRR(3),FD(3),FP(3*NCMAX),
     &        FPSUM(3),FPD(3*NCMAX),FPDSUM(3)
      SAVE NSKIP
      DATA NSKIP /0/
*
*
*       Update perturber list at frequent intervals.
      IF (IR.GT.0) THEN
          CALL CHLIST(ICH)
      ELSE
          NSKIP = NSKIP + 1
          IF (NSKIP.GE.10) THEN
              CALL CHLIST(ICH)
              NSKIP = 0
          END IF
      END IF
*
*       Subtract all close perturber forces acting on c.m. body #ICH.
      RPERT2 = CMSEP2*(0.5*RSUM)**2
      NPC = LISTC(1) + 1
      JDUM = 0
      DO 30 L = 2,NPC
          J = LISTC(L)
          DX(1) = X(1,J) - XI(1)
          DX(2) = X(2,J) - XI(2)
          DX(3) = X(3,J) - XI(3)
          RIJ2 = DX(1)**2 + DX(2)**2 + DX(3)**2
*       Skip correcting all interactions outside RPERT2.
          IF (RIJ2.GT.RPERT2) GO TO 30
          IF (J.LE.N) GO TO 5
          JP = J - N
          J1 = 2*JP - 1
*       See whether c.m. approximation applies.
          IF (RIJ2.GT.CMSEP2*R(JP)**2.OR.LIST(1,J1).EQ.0) GO TO 5
*       Resolve components of pair #JP.
          CALL KSRES2(JP,J1,J2,RIJ2)
          J = J1
          JDUM = J1
*       Sum over single body or individual KS components.
    5     DR2 = 0.0
          DRDV = 0.0
          DO 10 K = 1,3
              DX(K) = X(K,J) - XI(K)
              DV(K) = XDOT(K,J) - XIDOT(K)
	      DR2 = DR2 + DX(K)**2
	      DRDV = DRDV + DX(K)*DV(K)
   10     CONTINUE
          DR2I = 1.0/DR2
          DR3I = BODY(J)*DR2I*SQRT(DR2I)
	  DRDV = 3.0*DRDV*DR2I
*
*       Subtract force and first derivative.
          DO 20 K = 1,3
              FIRR(K) = FIRR(K) - DX(K)*DR3I
              FD(K) = FD(K) - (DV(K) - DX(K)*DRDV)*DR3I
   20     CONTINUE
          IF (J.EQ.JDUM) THEN
              J = J + 1
              GO TO 5
          END IF
   30 CONTINUE
*
*       Initialize the perturbing force components and vectorial sum.
      DO 35 K = 1,3*NCH
          FP(K) = 0.0D0
          FPD(K) = 0.0D0
   35 CONTINUE
      DO 40 K = 1,3
          FPSUM(K) = 0.0D0
          FPDSUM(K) = 0.0D0
   40 CONTINUE
*
*       Sum each perturber contribution over the chain components.
      KDUM = 0
      IM1 = 0
      DO 70 LL = 2,NPC
          K = LISTC(LL)
          A1 = X(1,K) - XI(1)
          A2 = X(2,K) - XI(2)
          A3 = X(3,K) - XI(3)
          RIJ2 = A1*A1 + A2*A2 + A3*A3
*
*       Skip perturbers consistent with c.m. approximation test above.
          IF (RIJ2.GT.RPERT2) GO TO 70
*       Decide appropriate summation (components or c.m. approximation).
          IF (K.GT.N) THEN
*       Resolve the binary inside 20*R (OK for tidal effect on chain).
              IF (RIJ2.LT.400.0*R(K-N)**2) THEN
                  KDUM = 2*(K - N) - 1
                  K = KDUM
                  GO TO 55
              END IF
          END IF
*
*       Obtain perturbation on each component.
          DO 50 IM = 1,NCH
              IM1 = 3*(IM - 1)
   46         DR2 = 0.0
              DRDV = 0.0
              DO 48 L = 1,3
                  DX(L) = X(L,K) - XC(L,IM)
                  DV(L) = XDOT(L,K) - UC(L,IM)
	          DR2 = DR2 + DX(L)**2
	          DRDV = DRDV + DX(L)*DV(L)
   48         CONTINUE
              DR2I = 1.0/DR2
              DR3I = BODY(K)*DR2I*SQRT(DR2I)
	      DRDV = 3.0*DRDV*DR2I
*
*       Accumulate perturbing force & derivative.
              DO 49 L = 1,3
                  FP(IM1+L) = FP(IM1+L) + DX(L)*DR3I
                  FPD(IM1+L) = FPD(IM1+L) + (DV(L) - DX(L)*DRDV)*DR3I
   49         CONTINUE
*
              IF (K.EQ.KDUM) THEN
                  K = K + 1
                  GO TO 46
              ELSE
                  IF (KDUM.GT.0) K = KDUM
              END IF
   50     CONTINUE
*
*       Reset dummy index after use (otherwise bug with two KS pairs).
          KDUM = 0
          GO TO 70
*
*       Sum over individual components of pair #J using c.m. approximation.
   55     DR2 = 0.0
          DRDV = 0.0
          DO 60 L = 1,3
              DX(L) = X(L,K) - XI(L)
              DV(L) = XDOT(L,K) - XIDOT(L)
	      DR2 = DR2 + DX(L)**2
	      DRDV = DRDV + DX(L)*DV(L)
   60     CONTINUE
          DR2I = 1.0/DR2
          DR3I = BODY(K)*DR2I*SQRT(DR2I)
	  DRDV = 3.0*DRDV*DR2I
*
*       Add force & first derivative.
          DO 65 L = 1,3
              FIRR(L) = FIRR(L) + DX(L)*DR3I
              FD(L) = FD(L) + (DV(L) - DX(L)*DRDV)*DR3I
   65     CONTINUE
          IF (K.EQ.KDUM) THEN
              K = K + 1
              GO TO 55
          END IF
   70 CONTINUE
*
*       Add any perturbations on components to the c.m. force & derivative.
      IF (IM1.GT.0) THEN
*       Sum individual perturbations.
          DO 80 L = 1,NCH
              L1 = 3*(L - 1)
              DO 75 K = 1,3
                  FPSUM(K) = FPSUM(K) + BODYC(L)*FP(L1+K)
                  FPDSUM(K) = FPDSUM(K) + BODYC(L)*FPD(L1+K)
   75         CONTINUE
   80     CONTINUE
*
*       Include mass-weighted contributions.
          BODYIN = 1.0/BODY(I)
          DO 90 K = 1,3
              FIRR(K) = FPSUM(K)*BODYIN + FIRR(K)
              FD(K) = FPDSUM(K)*BODYIN + FD(K)
   90     CONTINUE
      END IF
*
      RETURN
*
      END
