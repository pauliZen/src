      SUBROUTINE PNPERT(M1,M2,X,V,ACC,DER,DT)
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
      COMMON/POSTN/  CLIGHT,RZ,GAM,DEGR,IPN
      PARAMETER (ONE12=1.0/12.0D0)
      REAL*8  ACC(3),DER(3),VDOT(3),X(3),V(3)
      SAVE
      REAL*8  ACC0(3),DER0(3)
      DATA ACC0,DER0 /6*0.0D0/
      DATA IC /0/
      DATA ED0,ED20 /2*0.0D0/
*
*
*       Save inverse powers of CLIGHT.
      IF (IC.EQ.0) THEN
          CL2 = 1.0/CLIGHT**2
          CL3 = 1.0/CLIGHT**3
          IC = IC + 1
      END IF
*
*       Set total mass and reduced mass parameter.
      M = M1 + M2
      ETA = M1*M2/M**2
      ZMU = M*ETA
*
*       Form useful scalars.
      R2 = X(1)**2 + X(2)**2 + X(3)**2
      R = SQRT(R2)
      MR = M/R
      V2 = V(1)**2 + V(2)**2 + V(3)**2
      RD = (X(1)*V(1) + X(2)*V(2) + X(3)*V(3))/R
*
      A1 = 2*(2+ETA)*MR - (1+3*ETA)*V2 + 1.5*ETA*RD**2
      B1 = 2*(2-ETA)*RD
      A1 = 0.0
      B1 = 0.0
*
*       Define unscaled PN2.5 (positive sign convention).
      A25 = 8.0/5.0*ETA*MR*RD*(17.0/3.0*MR + 3.0*V2)
      A = (A1 + A25*CL3)*CL2
*
      B25 = -8.0/5.0*ETA*MR*(3.0*MR + V2)
      B = (B1 + B25*CL3)*CL2
*
*       Set the standard PN2.5 perturbing acceleration for VDOT.
      DO 5 K = 1,3
          ACC(K) = M/R2*(A*X(K)/R + B*V(K))
    5 CONTINUE
*
*       Note ACC scaled by M/R**2/C**5 for actual perturbing force.
      RVD = 0.0
      VVDOT = 0.0
      DO 10 K = 1,3
          VDOT(K) = ACC(K) - MR*X(K)/R2
          RVD = RVD + X(K)*VDOT(K)
          VVDOT = VVDOT + V(K)*VDOT(K)
   10 CONTINUE
*       Form d2R/dt**2 from dR/dt & d(R*V)/dt and omit 1/R (set later).
      RD2 = V2 + RVD - RD**2
*
      AD1 = -2*(2+ETA)*MR*RD/R - 2*(1+3*ETA)*VVDOT + 3*ETA*RD*RD2/R
      BD1 = 2*(2-ETA)*RD2/R
      AD1 = 0.0
      BD1 = 0.0
*
*       Adopt Peter Berczik's A & B derivatives (these have correct sign!).
      ADOT = (17.0/3.0*MR + 3.0*V2)*(RD2 - RD**2)*M/R2 +
     &       MR*RD*(-17.0/3.0*M*RD/R2 + 6.0*VVDOT)
      BDOT = MR*((3.0*MR + V2)*RD/R + 3.0*M*RD/R2 - 2.0*VVDOT)
      ADOT = 1.6*ETA*ADOT
      BDOT = 1.6*ETA*BDOT
*
      ADOT = (AD1 + ADOT*CL3)*CL2
      BDOT = (BD1 + BDOT*CL3)*CL2
*
*       Use equation of motion dV/dt = M/R2*((-1 + A/C**5)*X/R + B*V/C**5).
      DO 20 K = 1,3
*       Note that M/R2 is omitted in all terms (see final scaling).
          DER(K) = -2.0*RD/R*(A*X(K)/R + B*V(K)) + ADOT*X(K)/R -
     &              A*RD*X(K)/R2 + A*V(K)/R + BDOT*V(K) + B*VDOT(K)
   20 CONTINUE
*
*       Scale the acceleration and derivative by the leading term M/R**2.
      GMC = M/R2
      GAM = 0.0
      DO 30 K = 1,3
          DER(K) = GMC*DER(K)
          GAM = GAM + ACC(K)**2
   30 CONTINUE
*
*       Employ Hermite 4th-order integration for the energy equation.
      ED = 0.0
      ED2 = 0.0
*       Form the first and second energy derivative.
      DO 40 K = 1,3
          ED = ED + ACC(K)*V(K)
          ED2 = ED2 + ACC(K)*VDOT(K) + DER(K)*V(K)
   40 CONTINUE
*
*       Construct standard Hermite third and fourth-order derivatives.
***   ED3 = 2.0*(-3.0*(ED0 - ED) - (2.0*ED20 + ED2)*DT)/DT**2
***   ED4 = 6.0*(2.0*(ED0 - ED) + (ED20 + ED2)*DT)/DT**3
*
*       Get final result from Keigo's Hermite corrector.
      DE = 0.5*(ED0 + ED)*DT + ONE12*(ED20 - ED2)*DT**2
      DEGR = DEGR + ZMU*DE
*
*       Save the two derivatives for next step.
      ED0 = ED
      ED20 = ED2
      IC = IC + 1
*
      RETURN
*
      END
