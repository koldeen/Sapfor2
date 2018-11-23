        program looptransformtightenvalid
        double precision inv
        parameter (nx = 10, ny = 10, nx1 = nx + 1, ny1 = ny + 1)
        dimension a(0:nx1, 0:ny1)

        do i = 0, nx1
            do j = 0, ny1
                a(i, j) = 1
            enddo
        enddo

        do i = 1, nx
            inv = 10
            do j = 1, ny
                a(i,j) = a(i,j) * inv
            enddo
        enddo

        do i = 0, nx1
            write(unit = *,fmt = '(100g15.5)') ( a(i,j), j=0, ny1 )
        enddo
        end