      program onelooptransform
      integer  k_6
      integer  k_5
      integer  k_4
      integer  j_3
      integer  i_2
      integer  i_1
      double precision  inv
      parameter (nx = 10,ny = 10,nx1 = nx + 1,ny1 = ny + 1)
      dimension a(0:nx1,0:ny1)
      k = 0
      i = 0
      print *, 'i is 0, see:',i
      do  i_1 = i,i

!LOOP 1
          do  j = 0,ny1
            a(i_1,j) = 0
          enddo
        enddo
        print *, 'i must be still 0, see:',i
        do  i = 1,nx1
          do  j = 0,ny1
            a(i,j) = 1
          enddo
        enddo
        i = 5
        j = 5
        do  j_3 = j,j
          do  i_2 = i,i

!IF 1
            if (a(i_2,j_3) .gt. 0) then
              a(i_2,j_3) = a(i_2,j_3) + i_2 + j_3
            endif
          enddo
        enddo
        do  k_4 = k,k

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
          do  k_5 = k,k
            inv = 10
            do  j = 1,ny
                a(i,j) = a(i,j) * inv
            enddo
          enddo
        enddo

!LOOP 8
        do  i = 1,nx
            inv = 10
            do  k_6 = k,k
              do  j = 1,ny
                a(i,j) = a(i,j) * inv
              enddo
            enddo
        enddo
        do  i = 0,nx1
            write (unit = *,fmt = '(100g15.5)') (a(i,j), j = 0,ny1)
        enddo
        end