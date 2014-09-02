      SUBROUTINE XTPERT(M1,M2,X,V,ACC)
*
*
*       Post-Newtonian perturbations.
*       -----------------------------
*
*       L. Blanchet & B. Iyer, Class. Quantum Grav. 20 (2003), 755.
*       T. Mora & Clifford Will, gr-qc/0312082.
*       ---------------------------------------
*
      IMPLICIT REAL*8  (A-H,M,O-Z)
      COMMON/POSTN/  CLIGHT,RZ,GAMMA,IPN,ISPIN
      COMMON/PNPERT/ GAMMA1,GAMMA2,GAMMA3
      REAL*8  ACC(3),X(3),V(3),ACC1(3),ACC2(3),ACC3(3)
      SAVE ITIME,PI2
      DATA ITIME /0/
*
*
*       Set total mass and reduced mass parameter.
      M = M1 + M2
      ETA = M1*M2/M**2
      ETA2 = ETA**2
      ETA3 = ETA2*ETA
      IF (ITIME.EQ.0) THEN
          PI = 4.0*ATAN(1.0D0)
          PI2 = PI**2
          ITIME = 1
      END IF
*
*       Form useful scalars.
      R2 = X(1)**2 + X(2)**2 + X(3)**2
      R = SQRT(R2)
      MR = M/R
      V2 = V(1)**2 + V(2)**2 + V(3)**2
      RD = (X(1)*V(1) + X(2)*V(2) + X(3)*V(3))/R
*
*       Check the post-Newtonian scalar A & B-terms (skip A2/B2 if IPN < 2).
      IF (IPN.GE.1) THEN
          A1 = 2.0*(2.0 + ETA)*MR - (1.0 + 3.0*ETA)*V2 + 1.5*ETA*RD**2
          B1 = 2.0*(2.0 - ETA)*RD
      ELSE
          A1 = 0.0
          B1 = 0.0
      END IF
*
*       Include second-order terms on IPN >= 2.
      IF (IPN.GE.2) THEN
          A2 = - 0.75*(12.0 + 29.0*ETA)*MR**2 - ETA*(3.0-4.0*ETA)*V2**2
     &         - 15.0/8.0*ETA*(1.0 - 3.0*ETA)*RD**4
     &         + 0.5*ETA*(13.0 - 4.0*ETA)*MR*V2
     &         + (2.0 + 25.0*ETA + 2.0*ETA**2)*MR*RD**2
     &         + 1.5*ETA*(3.0 - 4.0*ETA)*V2*RD**2
          B2 = - 0.5*RD*((4.0 + 41.0*ETA + 8.0*ETA**2)*MR
     &         - ETA*(15.0 +4.0*ETA)*V2 + 3.0*ETA*(3.0 + 2.0*ETA)*RD**2)
          A2 = A2/CLIGHT**2
          B2 = B2/CLIGHT**2
      ELSE
          A2 = 0.0
          B2 = 0.0
      END IF
*
*       Add third-order terms on IPN >= 3.
      IF (IPN.GE.3) THEN
          A3 = (16. + (1399./12. - 41./16.*PI2)*ETA + 35.5*ETA2)*MR**3
     &         + ETA*(20827./840. + 123./64.*PI2 - ETA2)*MR**2*V2
     &         - (1. + (22717./168. + 615./64.*PI2)*ETA + 11./8.*ETA2
     &         - 7.*ETA3)*MR**2*RD**2
     &         - 0.25*ETA*(11. - 49.*ETA + 52.*ETA2)*V2**3
     &         + 35./16.*ETA*(1. -5.*ETA + 5.*ETA2)*RD**6
     &         - 0.25*ETA*(75. + 32.*ETA - 40.*ETA2)*MR*V2**2
     &         - 0.5*ETA*(158. - 69.*ETA - 60.*ETA2)*MR*RD**4
     &         + ETA*(121. - 16.*ETA - 20.*ETA2)*MR*V2*RD**2
     &         + 0.375*ETA*(20. - 79.*ETA + 60.*ETA2)*V2**2*RD**2
     &         - 15./8.*ETA*(4. - 18.*ETA + 17.*ETA2)*V2*RD**4
          B3 = (4. + (5849./840. + 123./32.*PI2)*ETA - 25.*ETA2
     &         - 8.*ETA3)*MR**2
     &         + 0.125*ETA*(65. - 152.*ETA - 48.*ETA2)*V2**2
     &         + 15./8.*ETA*(3. - 8.*ETA - 2.*ETA2)*RD**4
     &         + ETA*(15. + 27.*ETA + 10.*ETA2)*MR*V2
     &         - 1./6.*ETA*(329. + 177.*ETA + 108.*ETA2)*MR*RD**2
     &         - 0.75*ETA*(16. - 37.*ETA - 16.*ETA2)*V2*RD**2
          B3 = B3*RD
          A3 = A3/CLIGHT**4
          B3 = B3/CLIGHT**4
      ELSE
          A3 = 0.0
          B3 = 0.0
      END IF
*
*       Include PN2.5 and add all contributions.
      A25 = 8.0/5.0*ETA*MR*RD*(17.0/3.0*MR + 3.0*V2)
      A25 = A25/CLIGHT**3
      A = A1 + A2 + A25 + A3
*
      B25 = -8.0/5.0*ETA*MR*(3.0*MR + V2)
      B25 = B25/CLIGHT**3
      B = B1 + B2 + B25 + B3
*
*       Scale the acceleration by the leading term M/R**2.
      GMC = M/(CLIGHT**2*R2)
      DO 20 K = 1,3
          ACC(K) = GMC*(A*X(K)/R + B*V(K))
          ACC1(K) = GMC*(A1*X(K)/R + B1*V(K))
          ACC2(K) = GMC*(A2*X(K)/R + B2*V(K))
          ACC3(K) = GMC*(A3*X(K)/R + B3*V(K))
   20 CONTINUE
*
*       Obtain the relative perturbations for diagnostics.
      DF = SQRT(ACC(1)**2 + ACC(2)**2 + ACC(3)**2)
      DF1 = SQRT(ACC1(1)**2 + ACC1(2)**2 + ACC1(3)**2)
      DF2 = SQRT(ACC2(1)**2 + ACC2(2)**2 + ACC2(3)**2)
      DF3 = SQRT(ACC3(1)**2 + ACC3(2)**2 + ACC3(3)**2)
      GAMMA = DF*R2/M
      GAMMA1 = DF1*R2/M
      GAMMA2 = DF2*R2/M
      GAMMA3 = DF3*R2/M
*
      RETURN
      END
