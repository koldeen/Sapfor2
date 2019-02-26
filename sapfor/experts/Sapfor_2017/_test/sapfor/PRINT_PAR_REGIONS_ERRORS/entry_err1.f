        subroutine A(i1)
		INTEGER i1
!$SPF PARALLEL_REG reg1
        entry reg(i1)
		   i1 = i1 + 1
!$SPF END PARALLEL_REG 
		END
		
		PROGRAM PAR_REG_TEST
        INTEGER i1
        INTEGER summ
		
		summ = 0
		do i1 = 1, 20
		   call A(summ)
		   call reg(summ)
		enddo
		write(*,*) 'summ = ', summ
		
		summ = 0
		do i1 = 1, 20
		   call A(summ)
		enddo		
        write(*,*) 'summ = ', summ
        END
