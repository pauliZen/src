      IMPLICIT REAL*8 (A-H,M,O-Z)
*
*       Unperturbed GR Two-Body Orbit. (Peters 1964)
*       ==============================
*
      M1 = 8.0
      M2 = 10.0
      SEMI = 10.0
      ECC = 0.99
      CVEL = 200.0
      AMIN = 6.0*(M1 + M2)/CVEL**2
      TIME = 0.0
      IT = 0
    1 E2 = ECC**2
      ADOT =  64.0/5.0*M1*M2*(M1+M2)/(CVEL**5*SEMI**3*(1.0-E2)**3.5)
      ADOT = ADOT*(1.0 + 73.0/24.0*E2 + 37.0/96.0*E2**2)
      EDOT = 304.0/15.0*ECC*M1*M2*(M1+M2)/(CVEL**5*SEMI**4)
      EDOT = EDOT/(1.0-E2)**2.5*(1.0 + 121.0/304.0*E2)
      DT = 0.001*SEMI/ADOT
      SEMI = SEMI - ADOT*DT
      ECC = ECC - EDOT*DT
      TIME = TIME + DT
      IT = IT + 1
      TGR = SEMI/ADOT
      WRITE (6,10)  TIME, ECC, SEMI, EDOT, ADOT, TGR
   10 FORMAT (' T E A ED AD TGR  ',1P,E12.4,0P,F10.6,1P,E12.4,3E10.2)
      IF (SEMI.GT.AMIN.AND.IT.LT.100000) GO TO 1
      STOP
      END
