        subroutine A(array, summ, L, idx)
		INTEGER summ, array(L), idx, L
		   summ = summ + array(idx)
		END

        subroutine B(array, summ, L, idx)
		INTEGER summ, array(L), idx, L
		   summ = summ + array(idx)
		END
		
		PROGRAM PAR_REG_TEST
		PARAMETER(L=20)
        INTEGER i1, array(L)
        INTEGER summ
		do i1 = 1, 20
		   array(i1) = 2
		enddo
		
		summ = 0
!$SPF PARALLEL_REG reg1
		do i1 = 1, 20
		   call A(array, summ, L, i1)
		   array(i1) = array(i1) + 1
		enddo
!$SPF END PARALLEL_REG 
        
		write(*,*) 'summ = ', summ
		
		summ = 0
		do i1 = 1, 20
		   call B(array, summ, L, i1)
		   array(i1) = array(i1) + 2
		enddo
        write(*,*) 'summ = ', summ
		
		summ = 0
		do i1 = 1, 20
		   call A(array, summ, L, i1)
		enddo        
		write(*,*) 'summ = ', summ
        END
