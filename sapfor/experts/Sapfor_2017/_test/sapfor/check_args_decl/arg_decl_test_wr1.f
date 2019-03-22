        subroutine A(i1)
		INTEGER i1
		   i1 = i1 + 1
		END

        subroutine B(i1)
		   i1 = i1 + 1
		END
		
		PROGRAM PAR_REG_TEST
        INTEGER i1
        INTEGER summ
		
		summ = 0
		do i1 = 1, 20
		   call A(summ)
		enddo
		write(*,*) 'summ = ', summ
		
		summ = 0
		do i1 = 1, 20
		   call B(summ)
		enddo		
        write(*,*) 'summ = ', summ
        END
