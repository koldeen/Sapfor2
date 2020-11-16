      integer function sum_(a, b)
      integer a, b
      sum_ = a + b
      end

      integer function sub_(a, b)
      integer a, b
      sub_ = a - b
      if (1 .eq. 1) then
        return
      endif
      end

      subroutine print_(a)
      integer a
      write(*,*)a
      end   
      
      program main
      implicit none
      integer a, b, res
      integer sum_, sub_
      a = 1
      b = a + 1
      res = sum_(sum_(a, b), sub_(a,b))
      call print_(res)
      end
