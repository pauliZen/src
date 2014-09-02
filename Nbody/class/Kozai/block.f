      BLOCK DATA BLOCK
*
*
*       Run time initializations.
*       -------------------------
*
      REAL*8  EP,STEPC,TFAC
      COMMON/BSSAVE/  EP(4),STEPC,TFAC,ITFAC,JC,NHALF2,IPERT
      COMMON/RAND/  IY,IFF,IR(97),IRAN0
*
*
*       Initialize Bulirsch-Stoer variables.
      DATA  EP  /0.04D0,0.0016D0,0.64D-4,0.256D-5/
      DATA  STEPC  /1.1D0/
      DATA  ITFAC,JC,NHALF2,IPERT  /0,-1,24,1/
      DATA  IFF,IRAN0  /0,0/
*
      END
