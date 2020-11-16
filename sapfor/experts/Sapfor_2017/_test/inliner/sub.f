      integer function sum_(a, b)
      integer a, b
      sum_ = a + b
      return
      entry mul_(a, b)
      mul_ = a * b
      return
      end

      integer function sub_(a, b)
      integer a, b
      sub_ = a - b
      if (1 .eq. 1) then
        return
      endif
      end
	  
	  integer function sub2_(a, b)
      integer a, b
	  integer sum_
      sub_ = sum_(a, -b)
      end

      subroutine print_(a)
      integer a
      write(*,*)a
      end
      
      subroutine test()
      integer a, b, res, i
      integer sum_, sub_, sub2_, mul_, one
      a = 1
      b = a + 1
	  call print_(a)
	  call print_(b)
      res = sum_(sub_(a,b), sub2_(a,b))
      call print_(res)
      end

      program main
      implicit none
      call test
      end
