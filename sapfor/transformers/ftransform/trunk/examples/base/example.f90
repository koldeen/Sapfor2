        program example
        double precision a,b,c
        implicit double precision (a-h,o-z)
        parameter (nx = 200, ny = 200, nx1 = nx + 1, ny1 = ny + 1)
        dimension a(0:nx1, 0:ny1), b(0:nx1, 0:ny1), c(0:nx1, 0:ny1)
        alpha = 0.5d0
        beta = 0.9d0

!PRG flow 0 1 distance=0
!PRG flow 0 2 distance=0
!PRG flow 0 3 distance=0
!PRG flow 1 4 distance=0
!PRG flow 1 5 distance=0
!PRG output 3 2 distance=1
!PRG output 5 4 distance=1
!PRG private zed, zed2
        do j = 1, ny
          do i = 1, nx
            zed = alpha * ((ci,j) - beta)
            zed2 = zed * zed
            a(i,j) = a(i,j) * zed
            a(i, j+1) = a(i, j+1) - zed
            b(i,j) = b(i,j) * zed2
            b(i, j+1) = b(i, j+1) - zed2
          enddo
        enddo
        end