        program example
        double precision a,b,c, h, alpha, beta
        parameter (nx = 10, ny = 10, nz = 10, nx1 = nx + 1, ny1 = ny + 1, nz1 = nz + 1)
        dimension a(0:nx1, 0:ny1), b(0:nx1, 0:ny1), h(0:nx1, 0:ny1, 0:nz1)
        alpha = 0.5d0
        beta = 0.9d0

        do i = 0, nx1
            do j = 0, ny1
                a(i, j) = 1
                b(i, j) = 2
            enddo
        enddo

!PRG dimension access
        do i = 1, nx
            invariant = alpha * beta
            do j = 1, ny
                a(i,j) = a(i,j) * invariant
                b(i,j) = b(i,j) * beta
            enddo
        enddo

!PRG dimension access
        do i = 1, nx
            invariant = alpha * beta
            do j = 1, ny
                invariant2 = alpha / beta
                do k = 1, nz
                    h(i,j,k) = h(i,j,k - 1) * invariant / invariant2;
                enddo
            enddo
        enddo

        do i = 0, nx1
            write(unit = *,fmt = '(100g15.5)') ( a(i,j), j=0, ny1 )
            write(unit = *,fmt = '(100g15.5)') ( b(i,j), j=0, ny1 )
        enddo
        end