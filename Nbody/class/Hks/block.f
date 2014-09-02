      BLOCK DATA BLOCK
*
*
*       Run time initializations.
*       -------------------------
*
      REAL*8  RANGE
      COMMON/ICPU0/  ICPU
      COMMON/SLOW/  RANGE,ISLOW(10)
      COMMON/COUNTS/  NCOUNT(80)
*
*
*       Initialize COMMON indices & B-S data array.
      DATA  ICPU  /0/
      DATA  RANGE  /50.0D0/
      DATA  ISLOW  /1,2,4,8,16,32,64,128,256,512/
      DATA  NCOUNT  /80*0/
*
      END
