      program onelooptransform
      double precision  inv
      parameter (nx = 10,ny = 10,nx1 = nx + 1,ny1 = ny + 1)
      dimension a(0:nx1,0:ny1)
      k = 0
      i = 0
        do  i = i,i

!LOOP 1
          do  j = 0,ny1
            a(i,j) = 0
          enddo
        enddo
        do  i = 1,nx1
          do  j = 0,ny1
            a(i,j) = 1
          enddo
        enddo
        i = 5
        j = 5
        do  j = j,j
          do  i = i,i

!IF 1
            if (a(i,j) .gt. 0) then
              a(i,j) = a(i,j) + i + j
            endif
          enddo
        enddo
        do  k = k,k

!LOOP 4
          do  i = 1,nx
              inv = 10
              do  j = 1,ny
                  a(i,j) = a(i,j) * inv
              enddo
          enddo
        enddo

!LOOP 6
        do  i = 1,nx
          do  k = k,k
            inv = 10
            do  j = 1,ny
                a(i,j) = a(i,j) * inv
            enddo
          enddo
        enddo

!LOOP 8
        do  i = 1,nx
            inv = 10
            do  k = k,k
              do  j = 1,ny
                a(i,j) = a(i,j) * inv
              enddo
            enddo
        enddo
        do  i = 0,nx1
            write (unit = *,fmt = '(100g15.5)') (a(i,j), j = 0,ny1)
        enddo
        end