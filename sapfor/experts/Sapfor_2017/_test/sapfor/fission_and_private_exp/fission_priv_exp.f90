program SRSA4
  call srsa43
end

subroutine srsa43     
  parameter( N = 6,M=8,K=8,L=6, PN = 2,NL=1000)

  integer  A(N,M,K,L), B(N,M,K,L), C(N,M,K,L), D(N,M,K,L)
  integer  AA(N,M,K)
  integer nloopi,nloopj,nloopii,nloopjj,ttt,ttt1 
  character*9 tname
                 
  tname='srsa43'
!$SPF TRANSFORM (FISSION (NNL))
  NNL=NL    
  call serial4(C,N,M,K,L,NNL)
  nloopi=NL
  nloopj=NL
!$SPF TRANSFORM (PRIVATES_EXPANSION (nloopii,NL))
  nloopii=NL
  nloopjj=NL
  
!$SPF TRANSFORM (FISSION (i, j, ii, jj))
!$SPF TRANSFORM (FISSION (i, j, ii))
  do i=1,N
	do j=1,M
	  do ii=1,K
		do jj=1,L
		  A(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo

!$SPF TRANSFORM (FISSION (i, j, ii, jj), FISSION (i, j, ii))
  do i=1,N
	do j=1,M
	  do ii=1,K
		do jj=1,L
		  A(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo

!$SPF TRANSFORM (PRIVATES_EXPANSION (i))
!$SPF TRANSFORM (PRIVATES_EXPANSION)  
  do i=1,N
	do j=1,M
	  do ii=1,K
		do jj=1,L
		  A(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo

!$SPF TRANSFORM (FISSION (i, j, ii, jj))
!$SPF TRANSFORM (PRIVATES_EXPANSION)
  do i=1,N
	do j=1,M
	  do ii=1,K
		do jj=1,L
		  A(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo

!$SPF TRANSFORM (FISSION (i, j, ii, jj), PRIVATES_EXPANSION)
  do i=1,N
	do j=1,M
	  do ii=1,K
		do jj=1,L
		  A(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo

!$SPF TRANSFORM (PRIVATES_EXPANSION (i), PRIVATES_EXPANSION)
  do i=1,N
	do j=1,M
	  do ii=1,K
		do jj=1,L
		  A(i,j,ii,jj) = NL+i+j+ii+jj
        enddo
      enddo
    enddo
  enddo

!$SPF TRANSFORM (PRIVATES_EXPANSION)
  do i=1,N
	do j=1,M
	  do ii=1,K
		do jj=1,L
		  A(i,j,ii,jj) = NL+i+j+ii+jj
		enddo
      enddo
    enddo
  enddo

!$SPF TRANSFORM (FISSION (i, j, ii))
  do i=1,N
	do j=1,M
	  do ii=1,K
		do jj=1,L
		  A(i,j,ii,jj) = NL+i+j+ii+jj
		enddo
      enddo
    enddo
  enddo

!$SPF TRANSFORM (FISSION (i, j, jj))
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
	  
!$SPF TRANSFORM (FISSION (i, j, ii))
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

!$SPF TRANSFORM (PRIVATES_EXPANSION (i, j))
  do  i=1,N
    do  j=1,M
	  do ii=1,K
	    ttt = ttt
        do jj=1,L
          ttt = A(i,j,ii,1)+A(i,j,ii,2)
          ttt1=AA(i,j,ii)
        enddo
      enddo
      ttt=ttt
    enddo
  enddo

!$SPF TRANSFORM (FISSION (i, j, ii, jj, kk))
!$SPF TRANSFORM (PRIVATES_EXPANSION (i, j, ii, jj))
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
