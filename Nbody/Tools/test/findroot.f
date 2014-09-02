      FUNCTION findroot(rand_i,v_max,vdd_a,vdd_b,vdd_c,vdd_e)

*     lwang-add---------------------------------------------------------*
***** Note: find the root for planets velocity distribution function---**
***** --rand_i: rand seed----------------------------------------------**
***** --v_max: velocity uplimit log------------------------------------**
***** --vdd_a/b/c/e: coefficient---------------------------------------**
***** --             a*(v-e)^b*Exp(-(v-e)*c)---------------------------**

      real*8 xxxx,xxxxmin,xxxxmax,findroot
      real*8 v_max,vdd_a,vdd_b,vdd_c,vdd_e,rand_i

      xxxxmax=v_max
      xxxxmin=0

 1    xxxx=xxxxmin+(xxxxmax-xxxxmin)/2
      if ((vdd_a*((log10(xxxx)-vdd_e)**vdd_b)*exp(-(log10(xxxx)-vdd_e)
     &     /vdd_c)).GT.rand_i) then
         xxxxmax=xxxx
      else
         xxxxmin=xxxx
      end if
*      write (6,*) xxxx
      if ((xxxxmax-xxxxmin).GT.0.001) go to 1
      findroot=xxxxmin+(xxxxmax-xxxxmin)/2
*       write(6,*) findroot, xxxx
*     lwang-end-add-----------------------------------------------------*

      return
      end
      
