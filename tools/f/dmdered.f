	IMPLICIT NONE
	REAL WAVE(800000),WAVE1,WAVE2,DWAVE,FLUX(800000),FLAM(800000)
	REAL R,C,EBV
	INTEGER*4 NPNTS,I,MODE

	WRITE(*,*) 'Input minimum and maximum wavelength and step'
	READ(*,*) WAVE1,WAVE2,DWAVE

	NPNTS = (WAVE2-WAVE1)/DWAVE + 1

	DO I = 1, NPNTS
	  WAVE(I) = WAVE1 + DWAVE * (I-1)
	  FLUX(I) = 1.
	ENDDO

C	R=3.1
	WRITE(*,*) 'INPUT R'
	READ (*,*) R

	WRITE(*,*) 'Which extinction law?'
	WRITE(*,*) '0: < 3640 A Seaton Gal.'
	WRITE(*,*) '   > 3640 A Howarth Gal. (X(Hb)=R+0.53)'
	WRITE(*,*) '1: < 2700 A Fitzpatrick Gal. (X(Hb)=R+1.20)'
	WRITE(*,*) '   > 2700 same as Mode=0 (X(Hb)=R+0.53)'
	WRITE(*,*) '2: Prevot SMC (X(Hb)=R+0.142)'
	WRITE(*,*) '3: Howarth LMC (X(Hb)=R+0.47)'
	WRITE(*,*) '4: < 3700 A Fitzpatrick mean LMC (X(Hb)=R+1.177)'
	WRITE(*,*) '   > 3700 A same as Mode=3 (X(Hb)=R+0.47)'	
	WRITE(*,*) '5: Fitzpatrick 30 Dor LMC'
	WRITE(*,*) '   (within 1 degree of 30 Dor and (X(Hb)=R+0.691)'
	WRITE(*,*) '6: Cardelli, Clayton & Mathis R-dependent law'
      WRITE(*,*) '   X(Hb)=1.015452R + 0.461000)'
	READ(*,*) MODE

	WRITE(*,*) 'INPUT C = 0.4X(Hb)E(B-V)'
	READ (*,*) C

	IF (MODE.EQ.0) THEN
	  EBV=2.5*C/(R+0.53)
	ELSEIF (MODE.EQ.1) THEN
	  EBV=2.5*C/(R+0.53)
	ELSEIF (MODE.EQ.2) THEN
	  EBV=2.5*C/(R+0.142)
	ELSEIF (MODE.EQ.3) THEN
	  EBV=2.5*C/(R+0.47)
	ELSEIF (MODE.EQ.4) THEN
	  EBV=2.5*C/(R+1.177)
	ELSEif (MODE.EQ.5) then
	  EBV=2.5*C/(R+0.691)
	ELSE
	  EBV=2.5*C/(1.015452*R + 0.461000)
	ENDIF

	CALL DMDERED (EBV, R, MODE, WAVE, FLUX, FLAM, NPNTS)

	OPEN (UNIT=11,STATUS='NEW',FORM='FORMATTED',FILE='dmdered.ext')
	OPEN (UNIT=12,STATUS='NEW',FORM='FORMATTED',FILE='dmdered.flam')

	WRITE(11,10) (WAVE(I),FLUX(I),I=1,NPNTS)
	WRITE(12,10) (WAVE(I),FLAM(I),I=1,NPNTS)
10	format (1x,2e15.6)
	CLOSE (UNIT=11)
	CLOSE (UNIT=12)

	STOP
	END


	
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
!
!
!   SUBROUTINE DMDERED
!
!   IMPORTS:
!     EBV      (REAL) E(B-V)
!     R        (REAL) RATIO OF Av/E(B-V)
!     MODE
!     WAVE     (REAL) ARRAY OF WAVELENGTHS (Angstroms)
!*    FLUX     (REAL) ARRAY OF FLUXES
!     NPNTS    (INTEGER)  SIZE OF WAVE, FLUX ARRAYS
!
!   EXPORTS:
!     (UPDATES IMPORTS MARKED '*')
!
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
       SUBROUTINE DMDERED (EBV, R, MODE, WAVE, FLUX, FLAM, NPNTS)
!
!
!   DECLARATIONS
!
!
       IMPLICIT NONE
!
!
       INTEGER NPNTS
       INTEGER I
       INTEGER XRANGE
       INTEGER MODE
!
!
       REAL WAVE(NPNTS), FLUX(NPNTS), FLAM(NPNTS)
       REAL EBV, R
       REAL INVW, BIGX
	 real acardelli, bcardelli, ycardelli, facardelli, fbcardelli 
!
!
       DOUBLE PRECISION WORKFLUX
!
!
!   CALCULATE X(x) [=BIGX] AT EACH POINT, & DEREDDEN
!
!
       XRANGE = 0
       DO I = 1, NPNTS
           INVW = 1.0 / (WAVE(I)*1.E-4)
C---OUT OF RANGE?
           IF (INVW.GT.10.0 .OR. INVW.LT.0.0) THEN
               XRANGE = XRANGE + 1
           ENDIF
C
C          CALLS FOR GALACTIC, SMC, AND LMC 
C                BLUE AND UV EXTINCTION LAWS
C
           IF (INVW.GE.1.83) THEN
C
C              FOR LAMBDA < 5460 ANG
C
               IF (MODE.EQ.0) THEN           
                   CALL GALRED(INVW, BIGX, R)
                   GOTO 400
               ENDIF
               IF (MODE.EQ.1) THEN           
                   CALL GALFITZRED(INVW, BIGX, R)
                   GOTO 400
               ENDIF
               IF (MODE.EQ.2) THEN
                   CALL SMCRED(INVW, BIGX, R)
                   GOTO 400
               ENDIF
               IF (MODE.EQ.3) THEN
                   CALL LMCIDHRED(INVW, BIGX, R)
                   GOTO 400
               ENDIF
               IF (MODE.EQ.4) THEN
                   CALL LMCFITZRED(INVW, BIGX, R)
                   GOTO 400
               ENDIF
               IF (MODE.EQ.5) THEN           
                   CALL DORFITZRED(INVW, BIGX, R)
                   GOTO 400
               ENDIF
C
C--(COMMON) IR LAW
C
           ELSEIF (INVW.GE.0.0) THEN
C
C          FOR LAMBDA > 5460 ANG
C
               BIGX = ((1.86 - 0.48*INVW)*INVW - 0.1)*INVW
               BIGX = BIGX * R / 3.1
           ENDIF
C
C	Cardelli, Clayton and Mathis (1989, AJ, 345, 245) R-dependent law:
	if (MODE.EQ.6) then
	  if (invw.gt.0.0.and.invw.lt.1.1) then
	    acardelli = 0.574 * invw ** 1.61
	    bcardelli = -0.527 * invw ** 1.61
	  elseif (invw.ge.1.1.and.invw.lt.3.3) then
 	    ycardelli = invw - 1.82
	    acardelli = 1. + 0.17699 * ycardelli
     + 		       - 0.50447 * ycardelli **2
     + 		       - 0.02427 * ycardelli **3
     +		 	 + 0.72085 * ycardelli **4
     +			 + 0.01979 * ycardelli **5
     +			 - 0.77530 * ycardelli **6
     +      		 + 0.32999 * ycardelli **7
	    bcardelli = 0. + 1.41338 * ycardelli 
     +		       + 2.28305 * ycardelli **2
     +    	             + 1.07233 * ycardelli **3
     +    		       - 5.38434 * ycardelli **4
     +    		       - 0.62251 * ycardelli **5
     +    		       + 5.30260 * ycardelli **6
     +  		       - 2.09002 * ycardelli **7
        elseif (invw.ge.3.3.and.invw.lt.8.0) then
	    if (invw.lt.5.9) then
	      facardelli = 0.
	      fbcardelli = 0.
	    else
	      facardelli = -0.04473 * (invw - 5.9)**2 
     +                   -0.009779 * (invw - 5.9)**3
	      fbcardelli = 0.2130 * (invw - 5.9)**2
     +                   +0.1207 * (invw - 5.9)**3
	    endif
	    acardelli = 1.752 - 0.316 * invw -
     +      0.104/((invw-4.67)**2 + 0.341) + facardelli
	    bcardelli = -3.090 + 1.825 * invw +
     +      1.206/((invw-4.62)**2 + 0.263) + fbcardelli
	  elseif (invw.ge.8.0.and.invw.lt.10.0) then
	    acardelli = -1.073 - 0.628 * (invw - 8.0) +
     +      0.137 * (invw - 8.0)**2 - 0.070 * (invw - 8.0)**3
	    bcardelli = 13.670 + 4.257 * (invw - 8.0) -
     +      0.420 * (invw - 8.0)**2 + 0.374 * (invw - 8.0)**3
	  endif
	  bigx = acardelli * R + bcardelli
	endif
C
C
C---GET DEREDDENED FLUX
C
C
 400       WORKFLUX = ABS(FLUX(I))
           WORKFLUX = LOG10(WORKFLUX)
           WORKFLUX = WORKFLUX + 0.4*BIGX*EBV
           WORKFLUX = 10.0**WORKFLUX
           FLUX(I) = SIGN(REAL(WORKFLUX),FLUX(I))
C
C---GET f(LAMBDA) FROM BIGX
C
c  ** 15-jul-1991 - added in case to compute flam for the SMC (mode=2)
c  ** 16-aug-1993 - added in case to compute flam for the 30 Dor (mode=5) XWL
c
           IF (MODE.EQ.0.or.MODE.EQ.1) THEN
               FLAM(I)=(BIGX/(R+0.53))-1
           ELSEif (mode.eq.2) then
               flam(i)=(bigx/(R+0.142))-1
           elseif (MODE.EQ.3.or.MODE.EQ.4) then
               FLAM(I)=(BIGX/(R+0.47))-1
           ELSEif (mode.eq.5) then
               flam(i)=(bigx/(R+0.691))-1
           ELSEif (mode.eq.6) then
               flam(i)=(bigx/(1.015452*R+0.461000))-1
           ENDIF
!
C---END OF FLUX VALUE DO LOOP
!
 500   ENDDO
!
!
       IF (XRANGE.GT.0) THEN
           WRITE (*,
     +     '('' '',I5,'' points out of range of fits'')') XRANGE
       ENDIF
!
!
       RETURN
       END
!
!
!
!
!
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
!
!
!   SUBROUTINE GALRED
!
!   DEREDDENS FLUX CALIBRATED DATA
!   USING SEATON (UV) AND HOWARTH (OPTICAL/IR) FITS
!
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
       SUBROUTINE GALRED (INVW, BIGX, R)
!
!
!   DECLARATIONS
!
!
       IMPLICIT NONE
!
!
       REAL INVW, BIGX, R
!
!
       IF (INVW.GT.7.14) THEN
           BIGX =
     +    ((0.2975*INVW - 3.2)*INVW) + 16.17
           BIGX = BIGX + R - 3.2
       ELSEIF (INVW.GT.3.65) THEN
           BIGX = (INVW - 4.60)**2 + 0.28
           BIGX = 2.29 + 0.848*INVW + 1.01/BIGX
           BIGX = BIGX + R - 3.2
       ELSEIF (INVW.GT.2.75) THEN
           BIGX = (INVW - 4.60)**2 + 0.28
           BIGX = 1.56 + 1.048*INVW + 1.01/BIGX
           BIGX = BIGX + R - 3.2
       ELSE
           BIGX = INVW - 1.83
           BIGX = R + (2.56 - 0.993*BIGX)*BIGX
       ENDIF
       RETURN
       END
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
!
!
!   SUBROUTINE SMCRED 
!
!   DEREDDENS FLUX CALIBRATED DATA
!   USING LINEAR FITS TO PREVOT et al 1985 DATA (Astron Atroph 132,389)
!         FIRST BETWEEN 1.83 < INVW < 6.72
!         AND A SECOND BETWEEN  6.72 < INVW < 7.84 
!         NOTE: !! EXTRAPOLATION OF SECOND FIT TO 10.0 !!
!
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
       SUBROUTINE SMCRED (INVW, BIGX, R)
!
!
!   DECLARATIONS
!
!
       IMPLICIT NONE
!
!
       REAL INVW, BIGX, R
!
!
       IF (INVW.LE.6.72) THEN
           BIGX= R + ((2.067*INVW) - 4.110)
       ELSEIF (INVW.GT.6.72) THEN
           BIGX= R + ((3.184*INVW) - 11.45)
       ENDIF
       RETURN
       END
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
!
!
!   SUBROUTINE LMCIDHRED
!
!   DEREDDENS FLUX CALIBRATED DATA
!   USING SEATON (UV) AND HOWARTH (OPTICAL/IR) FITS
!
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
       SUBROUTINE LMCIDHRED (INVW, BIGX, R)
!
!
!   DECLARATIONS
!
!
       IMPLICIT NONE
!
!
       REAL INVW, BIGX, R
!
!
       IF (INVW.GE.2.75) THEN
           BIGX = (INVW - 4.557)**2 + 0.293
           BIGX = (0.105*INVW + 0.462)*INVW + 0.454/BIGX
           BIGX = R - 0.236 + BIGX
       ELSE
           BIGX = INVW - 1.83
           BIGX = R + (0.094*BIGX + 2.04)*BIGX
       ENDIF
!
!
       RETURN
       END
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
!
!
!   SUBROUTINE LMCFITZRED
!
!   DEREDDENS FLUX CALIBRATED DATA
!   USING FITZPATRIC LMC MEAN LAW
!
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
       SUBROUTINE LMCFITZRED (INVW, BIGX, R)
!
!
!   DECLARATIONS
!
!
       IMPLICIT NONE
!
!
       REAL INVW, BIGX, R
       REAL C1,C2,C3,C4,C3DENOM,C4NUM,INVW0,GAMMA
!
!
!      FIT POOR FOR LAMBDA > 3700 ANGSTROMS
!      USE IDH LMC CURVE BELOW THIS
!
!
       IF (INVW.GT.2.7) THEN
C
       C1= -0.69
       C2=  0.89
       C3=  2.55
       C3DENOM=((INVW-((INVW0**2.0)/INVW))**2.0) + (GAMMA**2.0)
       IF (INVW.GT.5.9) THEN
           C4= 0.50
       C4NUM=(0.539*((INVW-5.9)**2.0)) + (0.0564*((INVW-5.9)**3.0))
       ELSE
           C4= 0.00
           C4NUM= 0.00
       ENDIF
       INVW0= 4.608
       GAMMA= 0.994
!
!
       BIGX= R + C1 + (C2*INVW) + (C3/C3DENOM) + (C4*C4NUM)
!
!
       ELSE
C
       CALL LMCIDHRED(INVW, BIGX, R)
C
       ENDIF
C
       RETURN
       END
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
!
!
!   SUBROUTINE DORFITZRED
!
!   DEREDDENS FLUX CALIBRATED DATA
!   USING FITZPATRIC LMC 30 DORADUS LAW
!
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
       SUBROUTINE DORFITZRED (INVW, BIGX, R)
!
!
!   DECLARATIONS
!
!
       IMPLICIT NONE
!
!
       REAL INVW, BIGX, R
       REAL C1,C2,C3,C4,C3DENOM,C4NUM,INVW0,GAMMA
!
!
       C1= -2.19
       C2=  1.39
       C3=  1.49
       C3DENOM=((INVW-((INVW0**2.0)/INVW))**2.0) + (GAMMA**2.0)
       IF (INVW.GT.5.9) THEN
           C4= 0.43
       C4NUM=(0.539*((INVW-5.9)**2.0)) + (0.0564*((INVW-5.9)**3.0))
       ELSE
           C4= 0.00
           C4NUM= 0.00
       ENDIF
       INVW0= 4.606
       GAMMA= 0.894
!
!
       BIGX= R + C1 + (C2*INVW) + (C3/C3DENOM) + (C4*C4NUM)
!
!
       RETURN
       END
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
!
!
!   SUBROUTINE GALFITZRED
!
!   DEREDDENS FLUX CALIBRATED DATA
!   USING FITZPATRIC VERSION OF THE SEATON GAL LAW
!
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
       SUBROUTINE GALFITZRED (INVW, BIGX, R)
!
!
!   DECLARATIONS
!
!
       IMPLICIT NONE
!
!
       REAL INVW, BIGX, R
       REAL C1,C2,C3,C4,C3DENOM,C4NUM,INVW0,GAMMA
!
!
!      FIT POOR FOR LAMBDA > 2700 ANGSTROMS
!      USE SEATONS LAW INSTEAD
!
       IF (INVW.GE.3.7) THEN
C
       C1= -0.38
       C2=  0.74
       C3=  3.96
       C3DENOM=((INVW-((INVW0**2.0)/INVW))**2.0) + (GAMMA**2.0)
       IF (INVW.GT.5.9) THEN
           C4= 0.26
       C4NUM=(0.539*((INVW-5.9)**2.0)) + (0.0564*((INVW-5.9)**3.0))
       ELSE
           C4= 0.00
           C4NUM= 0.00
       ENDIF
       INVW0= 4.595
       GAMMA= 1.051
!
!
       BIGX= R + C1 + (C2*INVW) + (C3/C3DENOM) + (C4*C4NUM)
!
!
       ELSE
C
       CALL GALRED(INVW, BIGX, R)
C
       ENDIF
C
       RETURN
       END
