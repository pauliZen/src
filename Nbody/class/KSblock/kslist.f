      SUBROUTINE KSLIST(IPAIR)
*
*
*       KS perturber selection.
*       -----------------------
*
      INCLUDE 'common2.h'
      REAL*4  W1,W2,W3,RSEP2,RCRIT2
*
*
*       Set first KS component and c.m. index.
      I1 = 2*IPAIR - 1
      I = N + IPAIR
*
*       Prepare standard perturber selection assuming apocentre. 
      RCRIT2 = CMSEP2*R(IPAIR)**2
*
*       Select new perturbers from c.m. neighbour list.
      NNB1 = 1
      NNB2 = LIST(1,I) + 1
      DO 10 L = 2,NNB2
          J = LIST(L,I)
          W1 = X(1,J) - X(1,I)
          W2 = X(2,J) - X(2,I)
          W3 = X(3,J) - X(3,I)
          RSEP2 = W1*W1 + W2*W2 + W3*W3
          IF (RSEP2.LT.RCRIT2) THEN
              NNB1 = NNB1 + 1
              LIST(NNB1,I1) = J
          END IF
   10 CONTINUE
*
*       Specify one unperturbed Kepler period if no perturbers.
      IF (NNB1.EQ.1) THEN
          SEMI = -0.5*BODY(I)/H(IPAIR)
          STEP(I1) = TWOPI*SEMI*SQRT(SEMI/BODY(I))
      END IF
*
*       Save perturber membership (zero is OK).
      LIST(1,I1) = NNB1 - 1
*
      RETURN
*
      END
