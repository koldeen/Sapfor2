      program jac3d
      parameter (l = 384,itmax = 100)
      real  a(l,l,l),eps,maxeps,b(l,l,l)
      double precision  startt,endt,dvtime
      integer  idx(3)
      maxeps = 0.5
      do  k = 1,l
         do  j = 1,l
            do  i = 1,l
               a(i,j,k) = 0.
               if (i .eq. 1 .or. j .eq. 1 .or. k .eq. 1 .or. i .eq. l .or. j .eq. l .or. k .eq. l) then
                  b(i,j,k) = 0.
               else
                  b(i,j,k) = 1. + i + j + k
               endif
            enddo
         enddo
      enddo
      a(:,:,:) = b(:,:,:)
      a(1,1,1) = b(2,2,2)
      a = b
      startt = dvtime ()
      do  it = 1,itmax
         eps = 0.
         do  k = 2,l - 1
            do  j = 2,l - 1
               do  i = 2,l - 1
                  eps = max (eps,abs (b(i,j,k) - a(i,j,k)))
                  a(i,j,k) = b(i,j,k)
               enddo
            enddo
         enddo
         do  k = 2,l - 1
            do  j = 2,l - 1
               do  i = 2,l - 1
                  b(i,j,k) = (a(i,j,k - 1) + a(i,j - 1,k) + a(i - 1,j,k) + a(i + 1,j,k) + a(i,j + 1,k) + a(i,j,k + 1)) / 6.
               enddo
            enddo
         enddo
         print 200, it,eps
200      FORMAT (' IT = ', I4, '   EPS = ', E14.7)
         if (eps .lt. maxeps)          exit
      enddo
      endt = dvtime ()
      print *, 'Jacobi3D Benchmark Completed.'
      print 201, l,l,l
201   FORMAT (' Size            = ', I4, ' x ', I4, ' x ', I4)
      print 202, itmax
202   FORMAT (' Iterations      =       ', I12)
      print 203, endt - startt
203   FORMAT (' Time in seconds =       ', F12.2)
      print *, 'Operation type  =     floating point'
      if (abs (eps - 5.058044) .lt. 1.0e-4) then
         print *, 'Verification    =         SUCCESSFUL'
      else
         print *, 'Verification    =       UNSUCCESSFUL'
      endif
      print *, 'END OF Jacobi3D Benchmark'
      end

