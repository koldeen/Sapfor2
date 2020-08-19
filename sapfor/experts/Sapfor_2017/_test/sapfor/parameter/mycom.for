
! ----------------------------------------------------------------------
!     My common library. Modified 03/09/2017.
! ----------------------------------------------------------------------
!     Modified DEGREE function:
! ----------------------------------------------------------------------
      FUNCTION DEGREE (A, B) 

!     
      IMPLICIT REAL*8  (A-H,O-Z)
      IMPLICIT INTEGER*4  (I-N)

!     
      IF (A .GE. 1D-15) THEN
         DEGREE = A** B
      ELSE  
         DEGREE = 0D0
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Modified SQRT function:
! ----------------------------------------------------------------------
      FUNCTION DSQRTM (A) 

!     
      IMPLICIT REAL*8  (A-H,O-Z)
      IMPLICIT INTEGER*4  (I-N)

!     
      IF (A .GE. 1D-15) THEN
         DSQRTM = DSQRT (A)
      ELSE  
         DSQRTM = 0D0
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Modified exponent function:
! ----------------------------------------------------------------------
      FUNCTION DEXPM (X) 

!     
      IMPLICIT REAL*8  (A-H,O-Z)
      IMPLICIT INTEGER*4  (I-N)

!     
      IF (X .LE. (-(308D0))) THEN
         DEXPM = 0D0
      ELSE  
         DEXPM = DEXP (X)
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Modified sin:
! ----------------------------------------------------------------------
      REAL*8  FUNCTION DSINM (X) 

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      Y = DSIN (X)

!     
      IF (DABS (Y) .GT. 1D-15) THEN
         DSINM = Y
      ELSE  
         DSINM = 0D0
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Modified cosin:
! ----------------------------------------------------------------------
      REAL*8  FUNCTION DCOSM (X) 

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      Y = DCOS (X)

!     
      IF (DABS (Y) .GT. 1D-15) THEN
         DCOSM = Y
      ELSE  
         DCOSM = 0D0
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Output function DZERO:
! ----------------------------------------------------------------------
      FUNCTION DZERO (A) 

!     
      IMPLICIT REAL*8  (A-H,O-Z)
      IMPLICIT INTEGER*4  (I-N)

!     
      B = DABS (A)

!     
      IF (B .GE. 1D-99) THEN
         DZERO = A
      ELSE  
         DZERO = 0D0
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Output function DZERO2:
! ----------------------------------------------------------------------
      FUNCTION DZERO2 (A, EPS) 

!     
      IMPLICIT REAL*8  (A-H,O-Z)
      IMPLICIT INTEGER*4  (I-N)

!     
      B = DABS (A)

!     
      IF (B .GE. EPS) THEN
         DZERO2 = A
      ELSE  
         DZERO2 = 0D0
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Angle of point (x,y), angle in [0,2pi)
! ----------------------------------------------------------------------
      FUNCTION DANGLE (X, Y) 
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      C_PI = 4D0 * DATAN (1D0)

!     
      IF (X .EQ. 0D0) THEN
         IF (Y .EQ. 0D0) THEN

!- x = 0, y = 0
            A = 0D0
         ELSE IF (Y .GT. 0D0) THEN  

!- x = 0, y > 0
            A = .5D0 * C_PI
         ELSE  

!- x = 0, y < 0
            A = 1.5D0 * C_PI
         ENDIF  
      ELSE IF (Y .EQ. 0D0) THEN  
         IF (X .GT. 0D0) THEN

!- x > 0, y = 0
            A = 0D0
         ELSE  

!- x < 0, y = 0
            A = C_PI
         ENDIF  

!- x <> 0, y <> 0
      ELSE  
         AX = DABS (X)
         AY = DABS (Y)

!- |x| = |y|
         IF (AX .EQ. AY) THEN
            IF (X .GT. 0D0) THEN
               IF (Y .GT. 0D0) THEN

!- x > 0, y > 0 
                  A = 0.25D0 * C_PI
               ELSE  

!- x > 0, y < 0
                  A = 1.75D0 * C_PI
               ENDIF  
            ELSE  
               IF (Y .GT. 0D0) THEN

!- x < 0, y > 0
                  A = 0.75D0 * C_PI
               ELSE  

!- x < 0, y < 0
                  A = 1.25D0 * C_PI
               ENDIF  
            ENDIF  
         ELSE  
            IF (AX .GT. AY) THEN

!- |x| > |y|
               A = DATAN (AY / AX)
            ELSE  

!- |x| < |y|
               A = .5D0 * C_PI - DATAN (AX / AY)
            ENDIF  
            IF (X .LT. 0D0) THEN
               IF (Y .LT. 0D0) THEN

!- x < 0, y < 0
                  A = C_PI + A
               ELSE  

!- x < 0, y > 0
                  A = C_PI - A
               ENDIF  
            ELSE  
               IF (Y .LT. 0D0) THEN

!- x > 0, y < 0
                  A = 2D0 * C_PI - A
               ENDIF  
            ENDIF  
         ENDIF  
      ENDIF  

!     
      DANGLE = A

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     My Entier:
! ----------------------------------------------------------------------
      INTEGER*4  FUNCTION MYROUND (X) 

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      I = IDINT (X)
      Z = X - 1D0 * I

!     
      IF (Z .LE. 0.5D0) THEN
         MYROUND = I
      ELSE  
         MYROUND = I + 1
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     f(x) is set by three points: (x1,f1), (x2,f2), (x3,f3)
!     
!     P2(x) = f2 + c1*(x-x2) + c2*(x-x2)*(x-x2) - approximation
! ----------------------------------------------------------------------
      FUNCTION FP2 (X1, X2, X3, F1, F2, F3, X) 

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      DX12 = X1 - X2
      DX32 = X3 - X2

!     
      DFDX12 = (F1 - F2) / DX12
      DFDX32 = (F3 - F2) / DX32

!     
      C2 = (DFDX32 - DFDX12) / (DX32 - DX12)
      C1 = DFDX12 - C2 * DX12

!     
      FP2 = F2 + C1 * (X - X2) + C2 * (X - X2) * (X - X2)

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     P2'(x) = c1 + 2*c2*(x-x2)
! ----------------------------------------------------------------------
      FUNCTION FP2P1 (X1, X2, X3, F1, F2, F3, X) 

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      DX12 = X1 - X2
      DX32 = X3 - X2

!     
      DFDX12 = (F1 - F2) / DX12
      DFDX32 = (F3 - F2) / DX32

!     
      C2 = (DFDX32 - DFDX12) / (DX32 - DX12)
      C1 = DFDX12 - C2 * DX12

!     
      FP2P1 = C1 + 2D0 * C2 * (X - X2)

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     In integer range:
! ----------------------------------------------------------------------
      INTEGER*4  FUNCTION IN_RANGE_I (I1, I2, I) 

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      IF (I1 .LE. I .AND. I .LE. I2) THEN
         IN_RANGE_I = 0
      ELSE  
         IN_RANGE_I = 1
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     In real range:
! ----------------------------------------------------------------------
      INTEGER*4  FUNCTION IN_RANGE_D (A, B, X) 

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      IF (A .LE. X .AND. X .LE. B) THEN
         IN_RANGE_D = 0
      ELSE  
         IF (X .LT. A) THEN
            IN_RANGE_D = 1
         ELSE  
            IN_RANGE_D = 2
         ENDIF  
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Compare of edges & faces:
! ----------------------------------------------------------------------
      FUNCTION ICMP2 (I1, I2, I3, I4) 
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      IF (I1 .LE. I2) THEN
         K1 = I1
         K2 = I2
      ELSE  
         K1 = I2
         K2 = I1
      ENDIF  

!     
      IF (I3 .LE. I4) THEN
         K3 = I3
         K4 = I4
      ELSE  
         K3 = I4
         K4 = I3
      ENDIF  

!     
      IF (K1 .EQ. K3 .AND. K2 .EQ. K4) THEN
         ICMP2 = 1
      ELSE  
         ICMP2 = 0
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Section procedure:
! ----------------------------------------------------------------------
      SUBROUTINE SECT1D (NP, MP, IB, IE, I1, I2)

!     
      IMPLICIT REAL*8  (A-H,O-Z)
      IMPLICIT INTEGER*4  (I-N)

!     
      IF (NP .EQ. 1) THEN
         I1 = IB
         I2 = IE
      ELSE  
         NC = IE - IB + 1
         NI = NC / NP
         MI = NC - NI * NP

!     
         IF (MP + 1 .LE. MI) THEN
            I1 = IB + MP * (NI + 1)
            I2 = I1 + NI
         ELSE  
            I1 = IB + MI * (NI + 1) + (MP - MI) * NI
            I2 = I1 + NI - 1
         ENDIF  
      ENDIF  

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Length of string.
! ----------------------------------------------------------------------
      INTEGER  FUNCTION LENSTR (S) 
      CHARACTER*(*) ::  S
      L = LEN (S)
1     IF (S(L:L) .EQ. ' ') THEN
         L = L - 1
         IF (L .GT. 0)  GOTO 1
      ENDIF  
      LENSTR = L
      RETURN 
      END


! ----------------------------------------------------------------------
!     Read string:
! ----------------------------------------------------------------------
      SUBROUTINE READSTR (ICH, STR, IER)

!     
      CHARACTER*(*) ::  STR

!     
      IER = (-(1))

!     
      N = MIN0 (1024,LEN (STR))

!     
      IF (N .LT. 1)  GOTO 10

!     
      IER = (-(2))

!     
      DO  I = 1,N
         STR(I:I) = ' '
      ENDDO  

!     
      K = 0

!     
      DO WHILE (.NOT.(EOF (ICH)) .AND. K .EQ. 0)
         READ (UNIT = ICH,FMT = '(1024(a1))',END = 5,ERR = 10) (STR(I:I)
     &, I = 1,1024)
5        IF (STR(1:1) .NE. '#')  K = 1
      ENDDO  

!     
      IER = 0

!     
10    RETURN 
      END


! ----------------------------------------------------------------------
!     Tecplot 2D, integer*4
! ----------------------------------------------------------------------
      SUBROUTINE TPL2D_REC_I (ICH, FNAME, TNAME, VNAME, N1, N2, X1, X2, 
     &X3)

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      CHARACTER*(*) ::  FNAME,TNAME,VNAME

!     
      REAL*8 ::  X1(N1),X2(N2)
      INTEGER*4 ::  X3(N1,N2)

!     
      OPEN (UNIT = ICH,FILE = FNAME)

!     
      WRITE (UNIT = ICH,FMT = *) TNAME
      WRITE (UNIT = ICH,FMT = *) VNAME
      WRITE (UNIT = ICH,FMT = *) 'ZONE T="BIG" I=',N1,' J=',N2,' F=POINT
     &'

!     
      DO  J = 1,N2
         V2 = X2(J)
         DO  I = 1,N1
            V1 = X1(I)
            V3 = 1D0 * X3(I,J)
            WRITE (UNIT = ICH,FMT = '(3(1x,1pe15.8))') V1,V2,V3
         ENDDO  
      ENDDO  

!     
      CLOSE (UNIT = ICH)

!     
      RETURN 
      END


! ----------------------------------------------------------------------
!     Tecplot 2D, real*8 
! ----------------------------------------------------------------------
      SUBROUTINE TPL2D_REC_D (ICH, FNAME, TNAME, VNAME, N1, N2, X1, X2, 
     &X3)

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      CHARACTER*(*) ::  FNAME,TNAME,VNAME

!     
      REAL*8 ::  X1(N1),X2(N2)
      REAL*8 ::  X3(N1,N2)

!     
      OPEN (UNIT = ICH,FILE = FNAME)

!     
      WRITE (UNIT = ICH,FMT = *) TNAME
      WRITE (UNIT = ICH,FMT = *) VNAME
      WRITE (UNIT = ICH,FMT = *) 'ZONE T="BIG" I=',N1,' J=',N2,' F=POINT
     &'

!     
      DO  J = 1,N2
         V2 = X2(J)
         DO  I = 1,N1
            V1 = X1(I)
            V3 = X3(I,J)
            WRITE (UNIT = ICH,FMT = '(3(1x,1pe15.8))') V1,V2,V3
         ENDDO  
      ENDDO  

!     
      CLOSE (UNIT = ICH)

!     
      RETURN 
      END

