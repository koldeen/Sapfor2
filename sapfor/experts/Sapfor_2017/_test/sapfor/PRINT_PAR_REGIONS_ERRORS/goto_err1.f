        subroutine A(i1)
		INTEGER i1
		   i1 = i1 + 1
		END
		
		PROGRAM GOTO_TEST
        INTEGER i1
        INTEGER summ
		
		summ = 0
!$SPF PARALLEL_REG reg1
		do i1 = 1, 20
		   call A(summ)
10		enddo
!$SPF END PARALLEL_REG 
        goto 10
		write(*,*) 'summ = ', summ
		
		summ = 0
		do i1 = 1, 20
		   call A(summ)
		enddo		
        write(*,*) 'summ = ', summ
        END
