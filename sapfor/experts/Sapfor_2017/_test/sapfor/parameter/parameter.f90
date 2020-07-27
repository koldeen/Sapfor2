program PARAMTER
  call check
end

subroutine check
implicit none
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
  do i=1,N
!$SPF ANALYSIS(PARAMETER(M=8))
    do j=1,M
      do ii=1,K
        do jj=1,L
!$SPF ANALYSIS(PARAMETER(NL=9*111+1))
          A(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo

end
