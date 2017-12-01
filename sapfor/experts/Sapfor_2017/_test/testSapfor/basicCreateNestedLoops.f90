program BasicCreateNestedLoops
  parameter (nx = 10, ny = 10)
  integer a(nx, ny), b(nx, ny)
  integer i, j, inv


  do j = 1, ny
    do i = 1, nx
      a(i, j) = 1
      b(i, j) = 2
    enddo
  enddo

  do j = 1, ny
    inv = nx * ny
    do i = 1, nx
      a(i, j) = 1 + b(i, j) * inv
    enddo
  enddo

  print*, "Result", a(1, 1), a(nx, 1)
end