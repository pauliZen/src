      SUBROUTINE IBLOCK
*
*
*       Initialization of block steps.
*       -----------------------------
*
      INCLUDE 'common2.h'
*
*
*       Form discrete steps in powers of 2 below SMAX.
      SMAX = 1.0
      DTK(1) = SMAX
      DO 1 K = 2,40
         DTK(K) = 0.5D0*DTK(K-1)
    1 CONTINUE
*
      RETURN
*
      END
