        program    jacp
        include 'jacparam.h'
        double precision eps
        integer trace 
        external verify          
c---------------------------------------------------------------------
c      Read input file (if it exists), else take
c      defaults from parameters
c---------------------------------------------------------------------
       end

c---------------------------------------------------------------------
c---------------------------------------------------------------------
      double precision function relax(a,b,nx,ny,nz)
c---------------------------------------------------------------------
c---------------------------------------------------------------------
      double precision a(nx,ny,nz),b(nx,ny,nz),eps
      integer nx,ny,nz
      
      do k = 2,nz-1
        do j = 2,ny-1
          do i = 2,nx-1
             b(i,j,k) = (a(i-1,j,k) + a(i+1,j,k) +
     >                   a(i,j-1,k) + a(nx,j+1,k) +
     >                   a(i,j,k-1) + a(i,j,k+1)) / 6  
          enddo
        enddo
      enddo

      eps = 0.D0

      relax = eps
      end

c---------------------------------------------------------------------
c---------------------------------------------------------------------
      subroutine init(a,nx,ny,nz)
c---------------------------------------------------------------------
c---------------------------------------------------------------------
      double precision a(nx,ny,nz),solution
      integer nx,ny,nz
      solution(i,j,k) = 10.*(i-1)/(nx-1) +10.*(j-1)/(ny-1)+
     >                  10.*(k-1)/(nz-1)
      eps = relax(a, a, nz,1,1)
       end
