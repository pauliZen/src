      subroutine fun1(i1)
      integer i1

      i1 = i1 + 1
      end
      
      subroutine fun(i1)
      integer i1

      call fun1(i1)

      end

      program func

      integer i(100)

      do k=1,100
         i(k)=0
         call fun(i(k))
      end do

      do k=1,10
         print*,i(k*10-9:k*10)
      end do
      
      end
