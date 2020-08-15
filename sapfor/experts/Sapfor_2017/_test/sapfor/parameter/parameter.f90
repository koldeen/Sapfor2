program PARAMTER
  call check
end

module constants
implicit none
   real, parameter::pi = 3.1415926536
   real, parameter::e = 2.7182818285
contains 
  subroutine show_consts()
    print*, "Pi = ", pi
  contains
    subroutine show_e()
	  print*, "e = ", e
	end subroutine show_e
  end subroutine show_consts
end module constants

subroutine check
implicit none
use constants!, only: pi, p=>pi
common /global/ key
  real key
  integer n,m,k,l,pn,nl,i,j,ii,jj,nnl
  parameter(N=6,M=8,K=8,L=6,PN=2,NL=1000)
  integer  A(N,M,K,L)
  character*9 tname

  tname='check'
  NNL=NL
!$SPF ANALYSIS(PARAMETER(N=N))
!$SPF ANALYSIS(PARAMETER(N=6))
!$SPF ANALYSIS(PARAMETER(N=6,M=8))
!$SPF ANALYSIS(PARAMETER(N=M-2))
!$SPF ANALYSIS(PARAMETER(A(i,j,ii,jj)=M-2, i=1))
  do i=1,N
!$SPF ANALYSIS(PARAMETER(M=8))
    do j=1,M
      do ii=1,K
        do jj=1,L
!$SPF ANALYSIS(PARAMETER(NL=9*111+1))
!$SPF ANALYSIS(PARAMETER(A(i,j,ii,jj)=M-2, i=1))
!$SPF ANALYSIS(PARAMETER(A=(M-2)*key))
          A(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo

end
