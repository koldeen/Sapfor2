		subroutine C(array, summ, L, idx)
		INTEGER summ, array(L), idx
		entry reg(array, summ, L, idx)
		   summ = summ + array(idx)		
		end
		
		subroutine A(array, summ, L, idx)
		INTEGER summ, array(L), idx
!$SPF PARALLEL_REG reg1
		   call C(array, summ, L, idx)
!$SPF END PARALLEL_REG
		END

		PROGRAM ENTRY_TEST
		PARAMETER(L=20)
        INTEGER i1, array(L)
        INTEGER summ

		do i1 = 1, 20
		   array(i1) = 2
		enddo
		
		summ = 0
		do i1 = 1, 20
		   call A(array, summ, L, i1)
		   call reg(array, summ, L, i1)
		   array(i1) = array(i1) + 1
		enddo
		write(*,*) 'summ = ', summ
        END
