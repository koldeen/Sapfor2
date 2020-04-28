program CHECKPOINT
  call check
end

module testA
  real modA
end

module testB
  use testA, modB=>modA
end

module testC
  use testB, modC=>modB
end

module constants
implicit none
   real, parameter,private :: pi = 3.1415926536
   real, parameter, private :: e = 2.7182818285
contains
   subroutine show_consts()
      print*, "Pi = ", pi
      print*, "e = ", e
   end subroutine show_consts
end module constants

module test
implicit none
  use constants, only: pi
end

subroutine check
  !use constants, only: P=>pi,P1=>pi
  use test
  use testC
  parameter( N = 6,M=8,K=8,L=6, PN = 2,NL=1000)

!$SPF CHECKPOINT(INTERVAL(TIME,10),VARLIST(A,B),EXCEPT(AA,D),VARLIST(C))
!$SPF CHECKPOINT(VARLIST(A,B,C),EXCEPT(AA,D))
  integer  A(N,M,K,L), B(N,M,K,L), C(N,M,K,L), D(N,M,K,L)
  integer  AA(N,M,K)
  integer nloopi,nloopj,nloopii,nloopjj,ttt,ttt1 
  character*9 tname
  
!$SPF CHECKPOINT(INTERVAL(TIME,10),FILES_COUNT(4),VARLIST(A,B,C),TYPE(ASYNC),EXCEPT(AA,D))
!$SPF CHECKPOINT(INTERVAL(TIME,10),FILES_COUNT(a),VARLIST(A,B,C),TYPE(ASYNC,FLEXIBLE),EXCEPT(AA,D,TEMP))
!$SPF CHECKPOINT(INTERVAL(TIME,10),VARLIST(A,B),EXCEPT(AA,D,pi),VARLIST(C,e,modB))
  tname='check'
  NNL=NL    
  call serial4(C,N,M,K,L,NNL)
  nloopi=NL
  nloopj=NL
  nloopii=NL
  nloopjj=NL
! $SPF CHECKPOINT(INTERVAL(TIME,ITER),FILES_COUNT(4,5),VARLIST(A,B,C),TYPE(ASYNC),EXCEPT(AA,D))
! $SPF CHECKPOINT(INTERVAL(ITER,TIME),FILES_COUNT(),VARLIST(A,B,C),TYPE(ASYNC),EXCEPT(AA,D))
! $SPF CHECKPOINT(INTERVAL(ITER,TIME),FILES_COUNT,VARLIST(A,B,C),TYPE(ASYNC),EXCEPT(AA,D))
!$SPF CHECKPOINT(INTERVAL(ITER,-1),FILES_COUNT(555),VARLIST(i,j,ii),TYPE(ASYNC),EXCEPT(AA,jj))
!$SPF CHECKPOINT(INTERVAL(TIME,0),FILES_COUNT(4),VARLIST(A),TYPE(ASYNC))
  do i=1,N
    do j=1,M
      do ii=1,K
        do jj=1,L
          A(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo
! $SPF CHECKPOINT(INTERVAL(ITER),FILES_COUNT(555),VARLIST(A,B,C),TYPE(ASYNC),EXCEPT(AA,D))
! $SPF CHECKPOINT(INTERVAL(-1),FILES_COUNT(555),VARLIST(A,B,C),TYPE(ASYNC),EXCEPT(AA,D))
! $SPF CHECKPOINT(INTERVAL(),FILES_COUNT(555),VARLIST(A,B,C),TYPE(ASYNC),EXCEPT(AA,D))
! $SPF CHECKPOINT(INTERVAL,FILES_COUNT(555),VARLIST(A,B,C),TYPE(ASYNC),EXCEPT(AA,D))
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