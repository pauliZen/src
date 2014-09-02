      SUBROUTINE GRBIN(M1,M2,X,V,E0,E1,E2,E3,EBIN)
*
*
*       Relativistic binary energy.
*       ---------------------------
*
*       L. Blanchet & B. Iyer, Class. Quantum Grav. 20 (2003), 755.
*       T. Mora & Clifford Will, gr-qc/0312082.
*       ---------------------------------------
*
      IMPLICIT REAL*8  (A-H,M,O-Z)
      COMMON/POSTN/  CLIGHT,RZ,GAMMA,IPN,ISPIN
      REAL*8  X(3),V(3)
*
*
*       Set total mass and reduced mass parameter.
      M = M1 + M2
      ETA = M1*M2/M**2
      ETA2 = ETA**2
      ETA3 = ETA2*ETA
      PI = 4.0*ATAN(1.0D0)
      PI2 = PI**2
*
      R2 = X(1)**2 + X(2)**2 + X(3)**2
      R = SQRT(R2)
      MR = M/R
      V2 = V(1)**2 + V(2)**2 + V(3)**2
      RD = (X(1)*V(1) + X(2)*V(2) + X(3)*V(3))/R
*
*       Set Newtonian energy per unit reduced mass.
      E0 = 0.5*V2 - MR
*
*       Form higher-order terms depending on GR indicator.
      IF (IPN.GE.1) THEN
          E1 = 0.5*MR**2 + 3.0/8.0*(1.0 - 3.0*ETA)*V2**2 +
     &         0.5*((3.0 + ETA)*V2 + ETA*RD**2)*MR
          E1 = E1/CLIGHT**2
      ELSE
          E1 = 0.0
      END IF
*
      IF (IPN.GE.2) THEN
          E2 = -0.25*(2.0 + 15.0*ETA)*MR**3 +
     &          5.0/16.0*(1.0 - 7.0*ETA + 13.0*ETA**2)*V2**3 + !5/160 bug 7/07
     &          1.0/8*(14.0 - 55.0*ETA + 4.0*ETA**2)*MR**2*V2 +
     &          1.0/8*(4.0 + 69*ETA + 12.0*ETA**2)*MR**2*RD**2 +
     &          1.0/8*(21.0 - 23.0*ETA - 27.0*ETA**2)*MR*V2**2 +
     &          1.0/4*(1.0 - 15.0*ETA)*MR*V2*RD**2 -
     &          3.0/8*ETA*(1.0 - 3.0*ETA)*MR*RD**4
          E2 = E2/CLIGHT**4
      ELSE
          E2 = 0.0
      END IF
*
      IF (IPN.GE.3) THEN
          E3 = (3./8 + 18469./840*ETA)*MR**4
     &         + (1.25 - (6747./280 - 41./64*PI2)*ETA
     &         - 21./4*ETA2 + 0.5*ETA3)*MR**3*V2
     &         + (1.5 + (2321./280 - 123./64*PI2)*ETA + 51./4*ETA2
     &         + 3.5*ETA3)*MR**3*RD**2
     &         + 1./128*(35 - 413*ETA + 1666*ETA2 - 2261*ETA3)*V2**4
     &         + 1./16*(135 - 194*ETA + 406*ETA2 - 108*ETA3)*MR**2*V2**2
     &         + 1./16*(12 + 248*ETA -815*ETA2 -324*ETA3)*MR**2*V2*RD**2
     &         -1./48*ETA*(731 - 492*ETA - 288*ETA2)*MR**2*RD**4
     &         + 1./16*(55 - 215*ETA + 116*ETA2 + 325*ETA3)*MR*V2**3
     &         + 1./16*ETA*(5 - 25*ETA + 25*ETA2)*MR*RD**6
     &         - 1./16*ETA*(21 + 75*ETA - 375*ETA2)*MR*V2**2*RD**2
     &         - 1./16*ETA*(9 - 84*ETA + 165*ETA2)*MR*V2*RD**4
         E3 = E3/CLIGHT**6
      ELSE
          E3 = 0.0
      END IF
*
*       Set specific binding energy according to the PN indicator.
      EBIN = E0 + E1 + E2 + E3
*
      RETURN
      END
