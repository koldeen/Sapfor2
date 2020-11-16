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
      integer sum_
      sub_ = a - b
      if (1 .eq. 1) then
        return
      endif
      sub_ = sum_(a, -b)
      end
      
      integer function one()
      one = 1
      end
      
	  integer function array_sum(a, b, n)
	  integer n
      integer a(-1:8), b(N)
	  integer i
	  array_sum = 0
	  do i = 1, n
	    array_sum = array_sum + a(i-2) + b(i)
	  enddo
      end
	  
      subroutine print_(a)
      integer a
      write(*,*)a
      end
      
      program main
      implicit none
      integer a, b, res, i, s
      integer sum_, sub_, mul_, one, array_sum
	  integer array1(10), array2(10)
	  do i = 1, 10
	    array1(i) = i
		array2(i) = i
	  enddo
	  s = array_sum(array1, array2, 10)
	  call print_(s)
	  call print_(array_sum(array1, array2, 10))
      a = 1
      b = a + 1
      res = sum_(sum_(one(), b), mul_(1, sub_(a,b)))
      if (1 .eq. one()) call print_(1)
      do i = 1, one() * 5
        call print_(i + one() * one())
      enddo
      call print_(res)
      end
