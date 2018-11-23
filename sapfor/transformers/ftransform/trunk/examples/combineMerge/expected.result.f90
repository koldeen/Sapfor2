        program example
        double precision a,b,c, alpha, beta
        parameter (nx = 10, ny = 10, nx1 = nx + 1, ny1 = ny + 1)
        dimension a(0:nx1, 0:ny1), b(0:nx1, 0:ny1)
        alpha = 0.5d0
        beta = 0.9d0

        do i = 0, nx1
            do j = 0, ny1
                a(i, j) = 1
                b(i, j) = 2
            enddo
        enddo

        do i = 1, nx
            do j = 1, ny
                a(i,j) = a(i,j) * alpha
                a(i, j+1) = a(i, j+1) - alpha
                b(i,j) = b(i,j) * beta
                b(i, j+1) = b(i, j+1) - beta
            enddo
        enddo

        do i = 0, nx1
            write(unit = *,fmt = '(100g15.5)') ( a(i,j), j=0, ny1 )
            write(unit = *,fmt = '(100g15.5)') ( b(i,j), j=0, ny1 )
        enddo
        end