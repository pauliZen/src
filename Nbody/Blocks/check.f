      SUBROUTINE CHECK(IPAIR)
*
*
*       Accuracy check.
*       ---------------
*
      INCLUDE 'common2.h'
      COMMON/POSTN/  CLIGHT,RZ,GAM,DEGR,IPN
      SAVE
      DATA ITIME /0/
*
*
*       Perform accuracy check.
      V2 = 0.0
      DO 10 K = 1,4
          V2 = V2 + UDOT(K,IPAIR)**2
   10 CONTINUE
*       Form specific energy from regularized expression.
      HT = (2.0*V2 - BODY(N+IPAIR))/R(IPAIR)
      SEMI = -0.5*BODY(N+IPAIR)/HT
      ECC2 = (1.0 - R(IPAIR)/SEMI)**2 +
     &        TDOT2(IPAIR)**2/(BODY(N+IPAIR)*SEMI)
      ECC = SQRT(ECC2)
*
      EBIN = -0.5*BODY(1)*BODY(2)/SEMI
      ETOT = EBIN - DEGR
*       Delay saving initing value by one step for improved accuracy.
      IF (ITIME.LE.1) THEN
          SEMI0 = SEMI
          ECC0 = ECC
          EBIN0 = EBIN
          ITIME = ITIME + 1
          TK = TWOPI*SEMI0*SQRT(SEMI0/BODY(N+IPAIR))
          GO TO 30
      END IF
*
*       Print relevant information (note DA/A and DE).
      ERR = (ETOT - EBIN0)/EBIN0
      DA = (SEMI - SEMI0)/SEMI0
      DE = ECC - ECC0
      IF (MOD(NSTEPU,100000).EQ.0) THEN
      WRITE (7,20)  TIME, IPAIR, NSTEPU, SEMI, R(IPAIR), DA, DE, ERR
   20 FORMAT (' T IP # A R DA/A DE DE/E ',1P,E10.2,0P,I3,I10,1P,5E9.1)
      CALL FLUSH(7)
      END IF
*     I1 = 2*IPAIR - 1
*     WRITE (8,25)  TIME, DTAU(IPAIR), STEP(I1), R(IPAIR)
*  25 FORMAT (' ',1P,E12.4,3E10.2)
*
      IF (SEMI.LT.RZ) THEN
          WRITE (6,25)  NSTEPU, ECC, SEMI, ERR, DEGR, TIME
   25     FORMAT (' GR COAL    #U E A DE/E EGR T  ',I9,F7.3,1P,4E10.2)
          STOP
      END IF
*
   30 RETURN
*
      END
