function allocateUsingFunction()
  integer AllocateStatus, DeAllocateStatus
  real, dimension(:), allocatable :: arr
  real allocateUsingFunction
  parameter (nx = 10, nx1 = nx + 1)
  
  allocate(arr(0:nx1), STAT = AllocateStatus)
  IF (AllocateStatus /= 0) STOP "*** Not enough memory ***"
  do i = 0, nx1
    arr(i) = 1
  enddo
  allocateUsingFunction = arr(0)
  deallocate (arr, STAT = DeAllocateStatus)
  RETURN
end function allocateUsingFunction
  
program allocatablesmoketest
  real funcResult
  real, dimension(:), allocatable :: rra
  
  funcResult = allocateUsingFunction()
  print*, "Result", funcResult 
end