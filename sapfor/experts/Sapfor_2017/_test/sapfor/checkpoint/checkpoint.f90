program CHECKPOINT
  call check
end

module testA
  real modA
  real fixA
end

module testB
  use testA, modB=>modA
  !real fixA
end

module testC 
  use testB, modC=>modB
  !fixA
end

module constants
implicit none
   real, parameter:: pi = 3.1415926536
   real, parameter:: e = 2.7182818285
contains 
   subroutine show_consts()
      print*, "Pi = ", pi
      print*, "e = ", e
   end subroutine show_consts
end module constants

module test

  use constants, only: pi
end

subroutine check
use test
  use testC !, only: modC
implicit none
 
  
  integer n,m,k,l,pn,nl,i,j,ii,jj,nnl
  parameter( N = 6,M=8,K=8,L=6, PN = 2,NL=1000)
  integer  A(N,M,K,L), B(N,M,K,L), C(N,M,K,L), D(N,M,K,L)
  integer  AA(N,M,K)
  integer nloopi,nloopj,nloopii,nloopjj,ttt,ttt1 
  character*9 tname
  !  use constants
  
  
  write(*,*) modC
!$SPF CHECKPOINT(INTERVAL(TIME,10),FILES_COUNT(4),VARLIST(A,B,C),TYPE(ASYNC),EXCEPT(AA,D))
!$SPF CHECKPOINT(INTERVAL(TIME,10),FILES_COUNT(a),VARLIST(A,B,C),TYPE(ASYNC,FLEXIBLE),EXCEPT(AA,D,TEMP))
!$SPF CHECKPOINT(INTERVAL(TIME,10),VARLIST(A,B),EXCEPT(AA,D,pi),VARLIST(C,e,modB,modA))
  tname='check'
  NNL=NL    
  call serial4(C,N,M,K,L,NNL)
  nloopi=NL
  nloopj=NL
  nloopii=NL
  nloopjj=NL

  do i=1,N
    do j=1,M
      do ii=1,K
        do jj=1,L
          A(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo

  do  i=1,N
    do  j=1,M
      do ii=1,K
        ttt = ttt
        do jj=1,L
          ttt = A(i,j,ii,1)+A(i,j,ii,2)
          ttt1=AA(i,j,ii)
        enddo
        ttt=ttt
      enddo
    enddo
  enddo
  
  do  i=1,N
    do  j=1,M
      do  ii=1,K
        do  jj=1,L
          if (B(i,j,ii,jj).ne.(C(i,j,ii,1)+C(i,j,ii,2))) then
            nloopi=min(nloopi,i)
            nloopj=min(nloopj,j)
            nloopii=min(nloopii,ii)
            nloopjj=min(nloopjj,jj)
          endif
        enddo
        ttt = ttt
      enddo
    enddo
  enddo

  if (nloopi .eq.NL) then     
    call ansyes(tname)
  else
    call ansno(tname)
  endif

end


subroutine serial4(AR,N,M,K,L,NL)     
  integer AR(N,M,K,L)
  integer NL 

  do i=1,N
    do j=1,M
      do ii=1,K
        do jj=1,L
10        AR(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo

end


subroutine ansyes(name)
  character*9 name
  print *,name,'  -  complete'
end

subroutine ansno(name)
  character*7 name
  print *,name,'  -  ***error'
end
