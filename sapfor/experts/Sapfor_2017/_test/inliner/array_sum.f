      integer function sum_(a, b)
      integer a, b
      sum_ = a + b
      return
      entry mul_(a, b)
      mul_ = a * b
      return
      end
      
	  integer function array_sum(a, b, n)
	  integer n
      integer a(n), b(n)
	  integer i
	  array_sum = 0
	  do i = 1, n
	    array_sum = array_sum + a(i) + b(i)
	  enddo
      end
	  
	  integer function array_sum2(a, b, n)
	  integer n
      integer a(-1:8), b(n)
	  integer i
	  array_sum2 = 0
	  do i = 1, n
	    array_sum2 = array_sum2 + a(i-2) + b(i)
	  enddo
      end
	  
	  integer function array_sum3(a, b, n)
	  integer i, n, sum_
      integer a(-1:8), b(n)
	  array_sum3 = 0
	  do i = 1, n
	    array_sum3 = array_sum3 + sum_(a(i-2), b(i))
	  enddo
      end
	  
      subroutine print_(a)
      integer a
      write(*,*)a
      end
	  
      subroutine print_array(a, n)
	  integer i, n
      integer a(n)
	  do i = 1, n
        write(*,*)a(i)
      enddo
      end
      
      program main
      implicit none
      integer sum_, mul_, array_sum, array_sum2, array_sum3
      integer i, s
	  integer array1(10), array2(10)
	  do i = 1, 10
	    array1(i) = i
		array2(i) = i
	  enddo
	  call print_array(array1, 10)
	  call print_array(array2, 10)
	  s = array_sum(array1, array2, 10)
	  call print_(s)
	  s = array_sum2(array1, array2, 10)
	  call print_(s)
	  s = array_sum3(array1, array2, 10)
	  call print_(s)
      end
