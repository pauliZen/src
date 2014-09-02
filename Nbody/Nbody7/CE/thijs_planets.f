      SUBROUTINE THIJS_PLANETS
      
      INCLUDE 'common6.h'
      
      REAL*8  RAN2, AAA(12), MPLANET, RPLANET, QPLANET, VMU, VSIG
      REAL*8  XXX,YYY,ZZZ,XXXDOT,YYYDOT,ZZZDOT,MMM
      REAL*8  XXXSDOT,YYYSDOT,ZZZSDOT
      REAL*8  NUMBER1,NUMBER2,WWW,RANDOMNUMBER,MAXWELLVALUE
      REAL*8  SCALEV,SCALEM,SCALEX,SCALEVS
      INTEGER USEPLANET, NPLANET, VDIST
      INTEGER MSEL, PSEL

*     --06/29/12 10:15-lwang-add-notes----------------------------------*
***** Note: For new velocity distribution generator, we use function:--**
*****       a*(Log10[v]-v0)^b*Exp[-(Log10(v)-v0)/c]--------------------**
*****       a, b, c, v0 is fitting parameters, here we use:------------**
      REAL*8 fitvdista,fitvdistb,fitvdistc,fitvdistv0,fitvdistvmax
      REAL*8 findroot
*****       vmax is velocity uplimit-----------------------------------**
*     --06/29/12 10:15-lwang-end-notes----------------------------------*
*
*     VDIST = 0        PLUMMER
*     VDIST = 1        CONSTANT VELOCITY (VMU)
*     VDIST = 2        GAUSSIAN VELOCITIES (VMU,VSIG)
*     VDIST = 3        MAXWELL VELOCITIES (PEAK AT VMU)
*     lwang-add-notes---------------------------------------------------*
***** Note:------------------------------------------------------------**
*     VDIST = 4        Daniel's fly-by runs
*****      MSEL = 1: 1M; 2: 0.6M---------------------------------------**
*****      PSEL = 1: Delay; 2: Prompt-----------------------------------**
*     lwang-end-add-notes-----------------------------------------------*
*     
*     Read in the planet properties
      READ (5,*)  USEPLANET, NPLANET, MPLANET, RPLANET, QPLANET, 
     &            VDIST, VMU, VSIG, MSEL, PSEL
      IF (USEPLANET.EQ.0) GO TO 999
      WRITE (6,*) 'NMRQ_PLANET = ', NPLANET, MPLANET, RPLANET, QPLANET
      WRITE (6,*) 'VDIST VMU VSIG = ', VDIST, VMU, VSIG, MSEL, PSEL

*     --11/12/12 8:35-lwang-add call-----------------------------------*
***** Note: call for bdata store initial------------------------------**
      call bdata_init(N,NPLANET)
*     --11/12/12 8:35-lwang-end-add call-------------------------------*
      
*     lwang-test-closed-------------------------------------------------*
***** Note: Check whether N+ index has been used-----------------------**
*     Save the original data for diagnostics
      WRITE (10,*) 'Pre-planets diagnostics:'
      DO 11 I = 1,N
*      DO 11 I=1,N+NBIN0+100
         WRITE (10,10)  BODY(I),(X(K,I),K=1,3),(XDOT(K,I),K=1,3),-I
 10      FORMAT (1P,7E14.6,I7)
 11   CONTINUE
*     lwang-end-test----------------------------------------------------*
      
*     Move the pairs to higher positions
*     (in reverse order, to avoid overwriting)
      WRITE (6,*) 'TKPL N NBIN0 NTOT NPAIRS NZERO =', 
     &     N, NBIN0, NTOT, NPAIRS, NZERO
*     --11/07/12 1:35-lwang-change-------------------------------------*
***** Note:just remain the data after single N-------------------------**
c$$$  DO 20 III = 1, NBIN0
c$$$         INDEX1 = N+1         - III
c$$$         INDEX2 = N+NPLANET+1 - III
c$$$         BODY(INDEX2) = BODY(INDEX1) 
c$$$*         WRITE (6,*) 'i index1 index2 M',III,INDEX1,INDEX2,BODY(INDEX2)
c$$$         DO 18 KKK = 1,3
c$$$            X(KKK,INDEX2) = X(KKK,INDEX1) 
c$$$            XDOT(KKK,INDEX2) = XDOT(KKK,INDEX1) 
c$$$ 18      CONTINUE
c$$$ 20   CONTINUE
*     --11/07/12 1:35-lwang-end-change---------------------------------*
      
*     Generate initial conditions from Plummer model (A & A 37, 183).

*     Mass and position scaling
      SCALEM = 1./ZMBAR
      SCALEX = 1.5*TWOPI/16.0

      KDUM = IDUM1

*     Loop over planets
      DO 100 III = 1, NPLANET
 
*         Define planet masses
          MMM = MPLANET 

*         Define planet position radii and reject distant particles (Sverre book Eq. 8.7)
   30     AAA(1) = RAN2(KDUM)
          IF (AAA(1).LT.1.0D-10) GO TO 30
          RIII = (AAA(1)**(-0.6666667) - 1.0)**(-0.5)
          IF (RIII.GT.10.0) GO TO 30

*         Define planet XYZ vector (Sverre book Eq. 8.8)
          AAA(2) = RAN2(KDUM)
          AAA(3) = RAN2(KDUM)
          ZZZ = (1.0 - 2.0*AAA(2))*RIII
          XXX = SQRT(RIII**2 - ZZZ**2)*COS(TWOPI*AAA(3))
          YYY = SQRT(RIII**2 - ZZZ**2)*SIN(TWOPI*AAA(3))

*         Define planet velocity distribution
*         Case 0: Plummer model
          IF (VDIST.EQ.0) THEN 
 32          AAA(4) = RAN2(KDUM)
             AAA(5) = RAN2(KDUM)
             AAA(6) = AAA(4)**2*(1.0 - AAA(4)**2)**3.5
             IF (0.1*AAA(5).GT.AAA(6)) GO TO 32
             AAA(8) = AAA(4)*SQRT(2.0)/(1.0 + RIII**2)**0.25
             SCALEV = SQRT(ZMASS/SCALEX) * SQRT(2*QPLANET/RPLANET)
          END IF
*         Case 1: Constant velocities
          IF (VDIST.EQ.1) THEN 
             AAA(8) = VMU
             SCALEV = 1./VSTAR
          END IF
*         Case 2: Gaussian velocity distribution
          IF (VDIST.EQ.2) THEN 
 36          AAA(4) = RAN2(KDUM)
             AAA(5) = RAN2(KDUM)
             NUMBER1 = 2.0 * AAA(4) - 1.0
             NUMBER2 = 2.0 * AAA(5) - 1.0
             WWW = NUMBER1**2 + NUMBER2**2
             IF (WWW.GE.1) GO TO 36
             WWW = sqrt( (-2.0*LOG(WWW)) / WWW )
             RANDOMNUMBER = NUMBER1 * WWW
             AAA(8) = VMU + RANDOMNUMBER*VSIG
             IF (AAA(8).LE.0) GO TO 36
             SCALEV = 1./VSTAR
          END IF
*         Case 3: Maxwellian distribution
          IF (VDIST.EQ.3) THEN 
             MAXWELLCOUNTER = 0
             MAXWELLVALUE = 0.
 40          AAA(4) = RAN2(KDUM)
             AAA(5) = RAN2(KDUM)
             NUMBER1 = 2.0 * AAA(4) - 1.0
             NUMBER2 = 2.0 * AAA(5) - 1.0
             WWW = NUMBER1**2 + NUMBER2**2
             IF (WWW.GE.1) GO TO 40
             WWW = sqrt( (-2.0*LOG(WWW)) / WWW )
             RANDOMNUMBER = NUMBER1 * WWW
             MAXWELLCOUNTER = MAXWELLCOUNTER + 1
             MAXWELLVALUE = MAXWELLVALUE + RANDOMNUMBER**2
             IF (MAXWELLCOUNTER.LT.3) GO TO 40
*            Factor sqrt(2) converts peak to stddev
             AAA(8) = VMU/SQRT(2.0) * SQRT(MAXWELLVALUE)
             SCALEV = 1./VSTAR
          END IF
*     lwang-add---------------------------------------------------------*
***** Note: Daniel's fly-by runs-Velocity distribution generator-------**
***** PS: vmu: 1-1Mstar, 2-0.6Mstar; vsig: 1-delayed, 2-prompt---------**
***** -Plummer model vstar---------------------------------------------**
          if (vdist.EQ.4) then
 43          AAA(9) = RAN2(KDUM)
             AAA(10) = RAN2(KDUM)
             AAA(11) = AAA(9)**2*(1.0 - AAA(9)**2)**3.5
             IF (0.1*AAA(10).GT.AAA(11)) GO TO 43
             AAA(12) = AAA(9)*SQRT(2.0)/(1.0 + RIII**2)**0.25
             SCALEVS = SQRT(ZMASS/SCALEX) * SQRT(2*QPLANET/RPLANET)

             AAA(9) = RAN2(KDUM)
             AAA(10) = RAN2(KDUM)
             ZZZsDOT = (1.0 - 2.0*AAA(9))*AAA(12)
             XXXsDOT = SQRT(AAA(12)**2 - ZZZSDOT**2)*COS(TWOPI*AAA(10))
             YYYsDOT = SQRT(AAA(12)**2 - ZZZSDOT**2)*SIN(TWOPI*AAA(10))

***** --Vplanets-------------------------------------------------------**
             AAA(4)=ran2(kdum)
*     --06/29/12 10:31-lwang-change-random-generator--------------------*
***** Note: Use new generator instead----------------------------------**

***** --M1=1Mstar, delayed---------------------------------------------**
             if (MSEL.EQ.1.AND.PSEL.EQ.1) then
                fitvdista=2.38411
                fitvdistb=3.5
                fitvdistc=0.605927
                fitvdistv0=-1.3258
                fitvdistvmax=6.23655
                
             end if
***** --M1=0.6Mstar, delayed-------------------------------------------**
             if (MSEL.EQ.2.AND.PSEL.EQ.1) then
                fitvdista=0.093367
                fitvdistb=12.5645
                fitvdistc=0.261283
                fitvdistv0=-2.46835
                fitvdistvmax=6.5244

             end if
***** --M1=0.6Mstar, prompt--------------------------------------------**
             if (MSEL.EQ.2.AND.PSEL.EQ.2) then
                fitvdista=1.0248
                fitvdistb=6.31603
                fitvdistc=0.428713
                fitvdistv0=-1.39525
                fitvdistvmax=20.5358

             end if
***** --M1=1Mstar, prompt----------------------------------------------**
             if (MSEL.EQ.1.AND.PSEL.EQ.2) then
                fitvdista=0.00250775
                fitvdistb=16.1338
                fitvdistc=0.244205
                fitvdistv0=-2.29949
                fitvdistvmax=43.6983
                
             end if
***** -----------------------------------------------------------------**
             AAA(8)=findroot(AAA(4),fitvdistvmax,fitvdista,
     &            fitvdistb,fitvdistc,fitvdistv0)
             
*     --06/29/12 10:31-lwang-end-change-random-generator----------------*

***** --Unused now-----------------------------------------------------**
c$$$***** M1=1Mstar, delayed
c$$$             if (MSEL.EQ.1.AND.PSEL.EQ.1) then
c$$$                AAA(8)=10**(-1.13839 + 1.73508*AAA(4))
c$$$             end if
c$$$***** M1=0.6Mstar, delayed
c$$$             if (MSEL.EQ.2.AND.PSEL.EQ.1) then
c$$$                AAA(8)=10**(-0.988601 + 1.51929*AAA(4))
c$$$             end if
c$$$***** M1=1Mstar, prompt
c$$$             if (MSEL.EQ.1.AND.PSEL.EQ.2) then
c$$$                if (AAA(4).LT.0.283736) then
c$$$                   AAA(8)=10**(-0.784764 + 3.87704*AAA(4))
c$$$                end if
c$$$                if (AAA(4).LT.0.904905.AND.AAA(4).GE.0.283736) then
c$$$                   AAA(8)=10**(0.0234888 + 1.02844*AAA(4))
c$$$                end if
c$$$                if (AAA(4).GE.0.904905) then
c$$$                   AAA(8)=10**(-2.55407 + 3.87686*AAA(4))
c$$$                end if
c$$$             end if
c$$$***** M1=0.6Mstar, prompt
c$$$             if (MSEL.EQ.2.AND.PSEL.EQ.2) then
c$$$                if (AAA(4).LT.0.945539) then
c$$$                   AAA(8)=10**(-7.0286 + 8.41887*AAA(4))
c$$$                end if
c$$$                if (AAA(4).GE.0.945539) then
c$$$                   AAA(8)=10**(-0.574254 + 1.59277*AAA(4))
c$$$                end if
c$$$             end if
c$$$***** -----------------------------------------------------------------**
             SCALEV = 1./VSTAR
          END if
*     lwang-end-add-----------------------------------------------------*
          
*         Define planet VXVYVZ vector
          AAA(6) = RAN2(KDUM)
          AAA(7) = RAN2(KDUM)
          ZZZDOT = (1.0 - 2.0*AAA(6))*AAA(8)
          XXXDOT = SQRT(AAA(8)**2 - ZZZDOT**2)*COS(TWOPI*AAA(7))
          YYYDOT = SQRT(AAA(8)**2 - ZZZDOT**2)*SIN(TWOPI*AAA(7))

*     lwang-Add---------------------------------------------------------*
***** Note: -Vstar+Vplanets--------------------------------------------**
          if (vdist.EQ.4) then
             ZZZDOT = ZZZDOT + ZZZSDOT*SCALEVS/SCALEV
             XXXDOT = XXXDOT + XXXSDOT*SCALEVS/SCALEV
             YYYDOT = YYYDOT + YYYSDOT*SCALEVS/SCALEV
          end if
*     lwang-end-Add-----------------------------------------------------*
          
*         Write output to diagnostics file
          WRITE (10,46)  MMM,XXX,YYY,ZZZ,XXXDOT,YYYDOT,ZZZDOT, III
 46       FORMAT (1P,7E14.6,I5)
*          WRITE (6,*)   MMM,XXX,YYY,ZZZ,XXXDOT,YYYDOT,ZZZDOT

*         Add the planets to the database
*     --11/07/12 2:57-lwang-change-------------------------------------*
***** Note:change N-Nbin0+III to N+III---------------------------------**
          INDEX3 = N+III
*     --11/07/12 2:57-lwang-end-change---------------------------------*
          BODY(INDEX3) = MMM * SCALEM
          X(1,INDEX3) = XXX * SCALEX * RPLANET
          X(2,INDEX3) = YYY * SCALEX * RPLANET
          X(3,INDEX3) = ZZZ * SCALEX * RPLANET
          XDOT(1,INDEX3) = XXXDOT * SCALEV
          XDOT(2,INDEX3) = YYYDOT * SCALEV
          XDOT(3,INDEX3) = ZZZDOT * SCALEV

 100   CONTINUE

*      Update the counters
       N = N + NPLANET
       NZERO = N
       NTOT = NTOT + NPLANET
       WRITE (6,*) 'TKPL N NBIN0 NTOT NPAIRS NZERO =', 
     &      N, NBIN0, NTOT, NPAIRS, NZERO
       WRITE (6,*) 'TKPL ZMBAR ZMBAR1 ZMASS = ', ZMBAR,ZMASS,ZMBAR1
       WRITE (6,*) 'TKPL RBAR VSTAR         = ', RBAR,VSTAR

*      Write new database to diagnostics file
       WRITE (10,*) 'Post-planets diagnostics:'
       DO 200 I = 1,N-NBIN0
          WRITE (10,190) BODY(I)*ZMBAR,
     &                   (X(K,I)*RBAR,K=1,3),
     &                   (XDOT(K,I)*VSTAR,K=1,3),
     &                   I
 190      FORMAT ('xxx',1P,7E14.6,I7)
 200   CONTINUE
 
       CALL FLUSH(10)

*      Save random number sequence in COMMON for future use.
       IDUM1 = KDUM
       
*       WRITE (6,*) 'TK: Leaving thijs_planets'

 999   RETURN
       
       END
      
