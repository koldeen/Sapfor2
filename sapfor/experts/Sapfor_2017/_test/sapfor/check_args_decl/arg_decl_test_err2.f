        subroutine A(i1)
		   i1 = i1 + 1
		END
		
		PROGRAM PAR_REG_TEST
        INTEGER i1
        INTEGER summ
		
		summ = 0
!$SPF PARALLEL_REG reg1
		do i1 = 1, 20
		   call A(summ)
		enddo
!$SPF END PARALLEL_REG 
        
		write(*,*) 'summ = ', summ
		
		summ = 0
!$SPF PARALLEL_REG reg2
		do i1 = 1, 20
		   call A(summ)
		enddo		
!$SPF END PARALLEL_REG
        write(*,*) 'summ = ', summ
        END
