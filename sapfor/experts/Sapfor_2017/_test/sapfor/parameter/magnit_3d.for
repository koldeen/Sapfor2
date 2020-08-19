
! ----------------------------------------------------------------------
!     MAGNIT_3D. 14/06/2020
! ----------------------------------------------------------------------
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

! --- 
!      include 'omp_lib.h'
!     
!      INTEGER(KIND=OMP_LOCK_KIND) ::  LOCK

! --- 
      INTEGER*4 ,ALLOCATABLE:: MAP(:,:)

!     
      REAL*8 ,ALLOCATABLE:: RR(:),PP(:),ZZ(:)
      REAL*8 ,ALLOCATABLE:: RS(:),PS(:),ZS(:)

!     
      REAL*8 ,ALLOCATABLE:: PHI1(:,:,:),PHI2(:,:,:),PHI3(:,:,:)
      REAL*8 ,ALLOCATABLE:: ARX_RZ(:,:),ARY_RZ(:,:),ARZ_RZ(:,:)
      REAL*8 ,ALLOCATABLE:: AR_RZ(:,:),AR_RP(:,:)

!     
      REAL*8 ,ALLOCATABLE:: HX(:,:,:),HY(:,:,:),HZ(:,:,:),HR(:,:,:),HP(:
     &,:,:)

!     
      REAL*8 ,ALLOCATABLE:: BX(:,:,:),BY(:,:,:),BZ(:,:,:),BR(:,:,:),BP(:
     &,:,:)

!     
      CHARACTER*8 ::  SNUM
      CHARACTER*256 ::  VNAME
      CHARACTER*1024 ::  STR

! --- 
      COMMON /BMAIN/DR,DP,DZ,CFR,CFP,CFZ
      COMMON /BMATR/VMUMAT(4,4),VJRM(4),VJZM(4)
      COMMON /BITER/EPS,TAU,RKC,PHI0,ITM,ITP,ITS,K0

! --- 
      CPU_T1 = OMP_GET_WTIME ()

!     
!      CALL OMP_INIT_LOCK(LOCK)

! --- 
      WRITE (UNIT = *,FMT = *) 'command: magnit_3d <vname> [<nthreads> [
     &<lprint>]]'
      WRITE (UNIT = *,FMT = *) 

! --- 
      VNAME = 'magnit_3d'
      MTHR = OMP_GET_MAX_THREADS ()
      NTHR = 1
      LPP = 0

! ->  
      MXARG = IARGC ()

! ->  
      IF (MXARG .GT. 0) THEN
         I = 1
         STR = ' '
         CALL GETARG(I,STR)
         L = MIN0 (256,LENSTR (STR))
         VNAME = STR(1:L)
      ENDIF  

!     
      LVNAME = LENSTR (VNAME)

! ->  
      IF (MXARG .GT. 1) THEN
         I = 2
         STR = ' '
         CALL GETARG(I,STR)
         READ (UNIT = STR,FMT = *) NTHR
      ENDIF  

! ->  
      IF (MXARG .GT. 2) THEN
         I = 3
         STR = ' '
         CALL GETARG(I,STR)
         READ (UNIT = STR,FMT = *) LPP
      ENDIF  

! --- 
      OPEN (UNIT = 2,FILE = VNAME(1:LVNAME)//'.log')

! --- 
      WRITE (UNIT = *,FMT = *) '---> Start'
      WRITE (UNIT = 2,FMT = *) '---> Start'

! --- 
      WRITE (UNIT = *,FMT = *) 'MAGNIT_3D'
      WRITE (UNIT = *,FMT = *) 'vname=',VNAME(1:LVNAME)
      WRITE (UNIT = *,FMT = *) ' nthr=',NTHR
      WRITE (UNIT = *,FMT = *) ' mthr=',MTHR
      WRITE (UNIT = *,FMT = *) '  lpp=',LPP

!     
      WRITE (UNIT = 2,FMT = *) 'MAGNIT_3D'
      WRITE (UNIT = 2,FMT = *) 'vname=',VNAME(1:LVNAME)
      WRITE (UNIT = 2,FMT = *) ' nthr=',NTHR
      WRITE (UNIT = 2,FMT = *) ' mthr=',MTHR
      WRITE (UNIT = 2,FMT = *) '  lpp=',LPP
      WRITE (UNIT = 2,FMT = *) 

! --- 
      WRITE (UNIT = *,FMT = *) '---> Read'
      WRITE (UNIT = 2,FMT = *) '---> Read'

! --- 
      OPEN (UNIT = 1,FILE = VNAME(1:LVNAME)//'.d')

! ->  
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) R11

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) R12

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) Z11

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) Z12

! ->  
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) R21

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) R22

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) Z21

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) Z22

! ->  
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) R31

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) R32

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) Z31

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) Z32

! ->  
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) R41

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) R42

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) Z41

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) Z42

! ->  
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) RN

! ->  
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) VJ0

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) VJX
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) VJY

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) VJZ

! ->  
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) VMU0

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) VMU1

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) VMU2

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) VMU3

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) VMU4

! ->  
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) NR0

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) NP0

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) NZ0

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) NRF

! ->  
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) EPS

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) TAU

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) PHI0

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) RKC

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) ITM

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) ITP

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) ITS

!     
      CALL READSTR(1,STR,IER)
      IF (IER .NE. 0)  GOTO 999
      READ (UNIT = STR,FMT = *) LP

!     
      LP = MAX0 (LP,LPP)

! ->  
      CLOSE (UNIT = 1)

! ->  
      PHI = DANGLE (VJX,VJY)
      RHO = DSQRT (VJX * VJX + VJY * VJY)

!     
      CPH = DCOSM (PHI)
      SPH = DSINM (PHI)

!     
      VJR = (+(CPH)) * VJX + SPH * VJY
      VJP = (-(SPH)) * VJX + CPH * VJY

! ->  
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' R11=',R11
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' R12=',R12
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' Z11=',Z11
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' Z12=',Z12
      WRITE (UNIT = 2,FMT = *) 

! ->  
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' R21=',R21
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' R22=',R22
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' Z21=',Z21
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' Z22=',Z22
      WRITE (UNIT = 2,FMT = *) 

! ->  
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' R31=',R31
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' R32=',R32
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' Z31=',Z31
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' Z32=',Z32
      WRITE (UNIT = 2,FMT = *) 

! ->  
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' R41=',R41
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' R42=',R42
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' Z41=',Z41
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' Z42=',Z42
      WRITE (UNIT = 2,FMT = *) 

! ->  
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') '  Rn=',RN
      WRITE (UNIT = 2,FMT = *) 

!     
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' vJ0=',VJ0
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' vjx=',VJX
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' vjy=',VJY
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' vjz=',VJZ
      WRITE (UNIT = 2,FMT = *) 

!     
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' phi=',PHI
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' rho=',RHO
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' vjr=',VJR
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' vjp=',VJP
      WRITE (UNIT = 2,FMT = *) 

!     
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'vMu0=',VMU0
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'vMu1=',VMU1
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'vMu2=',VMU2
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'vMu3=',VMU3
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'vMu4=',VMU4
      WRITE (UNIT = 2,FMT = *) 

!     
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,i11)') ' nr0=',NR0
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,i11)') ' np0=',NP0
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,i11)') ' nz0=',NZ0
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,i11)') ' nrf=',NRF
      WRITE (UNIT = 2,FMT = *) 

!     
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' eps=',EPS
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' tau=',TAU
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'phi0=',PHI0
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' rkc=',RKC
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,i11)') ' itm=',ITM
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,i11)') ' itp=',ITP
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,i11)') ' its=',ITS
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,i11)') '  lp=',LP
      WRITE (UNIT = 2,FMT = *) 

! --- 
      WRITE (UNIT = *,FMT = *) '---> Normalization'
      WRITE (UNIT = 2,FMT = *) '---> Normalization'

!     
      VJN = VJ0
      VBN = VMU0 * VJ0
      VPN = VJ0 * RN

!     
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' vJn=',VJN
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' vBn=',VBN
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') ' vPn=',VPN
      WRITE (UNIT = 2,FMT = *) 

! ->  
      R11N = R11 / RN
      R12N = R12 / RN
      Z11N = Z11 / RN
      Z12N = Z12 / RN

! ->  
      R21N = R21 / RN
      R22N = R22 / RN
      Z21N = Z21 / RN
      Z22N = Z22 / RN

! ->  
      R31N = R31 / RN
      R32N = R32 / RN
      Z31N = Z31 / RN
      Z32N = Z32 / RN

! ->  
      R41N = R41 / RN
      R42N = R42 / RN
      Z41N = Z41 / RN
      Z42N = Z42 / RN

! ->  
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'R11n=',R11N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'R12n=',R12N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'Z11n=',Z11N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'Z12n=',Z12N
      WRITE (UNIT = 2,FMT = *) 

! ->  
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'R21n=',R21N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'R22n=',R22N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'Z21n=',Z21N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'Z22n=',Z22N
      WRITE (UNIT = 2,FMT = *) 

! ->  
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'R31n=',R31N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'R32n=',R32N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'Z31n=',Z31N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'Z32n=',Z32N
      WRITE (UNIT = 2,FMT = *) 

! ->  
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'R41n=',R41N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'R42n=',R42N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'Z41n=',Z41N
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') 'Z42n=',Z42N
      WRITE (UNIT = 2,FMT = *) 

! ->  
      RA = DMIN1 (R11N,R21N,R31N,R41N)
      RB = DMAX1 (R12N,R22N,R32N,R42N)

!     
      ZA = DMIN1 (Z11N,Z21N,Z31N,Z41N)
      ZB = DMAX1 (Z12N,Z22N,Z32N,Z42N)

! ->  
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') '  RA=',RA
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') '  RB=',RB
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') '  ZA=',ZA
      WRITE (UNIT = 2,FMT = '(1x,a5,1x,1pe15.8)') '  ZB=',ZB
      WRITE (UNIT = 2,FMT = *) 

! ->  
      VMUMAT(1,1) = VMU1
      VMUMAT(1,2) = 2D0 * VMU1 * VMU2 / (VMU1 + VMU2)
      VMUMAT(1,3) = 2D0 * VMU1 * VMU3 / (VMU1 + VMU3)
      VMUMAT(1,4) = 2D0 * VMU1 * VMU4 / (VMU1 + VMU4)

!     
      VMUMAT(2,1) = VMUMAT(1,2)
      VMUMAT(2,2) = VMU2
      VMUMAT(2,3) = 2D0 * VMU2 * VMU3 / (VMU2 + VMU3)
      VMUMAT(2,4) = 2D0 * VMU2 * VMU4 / (VMU2 + VMU4)

!     
      VMUMAT(3,1) = VMUMAT(1,3)
      VMUMAT(3,2) = VMUMAT(2,3)
      VMUMAT(3,3) = VMU3
      VMUMAT(3,4) = 2D0 * VMU3 * VMU4 / (VMU3 + VMU4)

!     
      VMUMAT(4,1) = VMUMAT(1,4)
      VMUMAT(4,2) = VMUMAT(2,4)
      VMUMAT(4,3) = VMUMAT(3,4)
      VMUMAT(4,4) = VMU4

! ->  
      DO  K = 1,4
         DO  I = 1,4
            WRITE (UNIT = 2,FMT = '(1x,a4,2(i2),1x,1pe15.8)') 'vMu:',I,K
     &,VMUMAT(I,K)
         ENDDO  
      ENDDO  
      WRITE (UNIT = 2,FMT = *) 

! ->  
      VJRM(1) = 0D0
      VJRM(2) = (+(VJR))
      VJRM(3) = (-(VJR))
      VJRM(4) = 0D0
! ->  
      VJZM(1) = 0D0
      VJZM(2) = (+(VJZ))
      VJZM(3) = (-(VJZ))
      VJZM(4) = 0D0

! --- 
      WRITE (UNIT = *,FMT = *) '---> Memory'
      WRITE (UNIT = 2,FMT = *) '---> Memory'

! --- 
!$SPF ANALYSIS(PARAMETER(NR0=130,NRF=2))
      NR = NR0 * NRF
!$SPF ANALYSIS(PARAMETER(NP0=60))
      NP = NP0 * NRF
!$SPF ANALYSIS(PARAMETER(NZ0=300))
      NZ = NZ0 * NRF

!     
      WRITE (UNIT = *,FMT = '(1x,a4,3(1x,i8))') 'dim:',NR,NP,NZ
      WRITE (UNIT = 2,FMT = '(1x,a4,3(1x,i8))') 'dim:',NR,NP,NZ
      WRITE (UNIT = 2,FMT = *) 

! --- 
      ALLOCATE(MAP(NR,NZ), STAT = IER)

!     
      ALLOCATE(RR(0:NR),PP(0:NP),ZZ(0:NZ), STAT = IER)

!     
      ALLOCATE(RS(NR),PS(NP),ZS(NZ), STAT = IER)

!     
      ALLOCATE(PHI1(NR,NP,NZ),PHI2(NR,NP,NZ),PHI3(NR,NP,NZ), STAT = IER)

!     
      ALLOCATE(ARX_RZ(NR,NZ),ARY_RZ(NR,NZ),ARZ_RZ(NR,NZ), STAT = IER)

!     
      ALLOCATE(AR_RZ(NR,NZ),AR_RP(NR,NP), STAT = IER)

!     
      ALLOCATE(HX(NR,NP,NZ),HY(NR,NP,NZ),HZ(NR,NP,NZ), STAT = IER)
      ALLOCATE(HR(NR,NP,NZ),HP(NR,NP,NZ), STAT = IER)

!     
      ALLOCATE(BX(NR,NP,NZ),BY(NR,NP,NZ),BZ(NR,NP,NZ), STAT = IER)
      ALLOCATE(BR(NR,NP,NZ),BP(NR,NP,NZ), STAT = IER)

! --- 
      WRITE (UNIT = *,FMT = *) '---> Grid & map'
      WRITE (UNIT = 2,FMT = *) '---> Grid & map'

! ->  
      PI = 4D0 * DATAN (1D0)

!     
      DR = (RB - RA) / NR
      DP = 2D0 * PI / NP
      DZ = (ZB - ZA) / NZ
      DM = DMIN1 (DR,DP,DZ)

! ->  
      WRITE (UNIT = *,FMT = '(1x,a4,4(1x,1pe15.8))') 'stp:',DR,DP,DZ,DM
      WRITE (UNIT = 2,FMT = '(1x,a4,4(1x,1pe15.8))') 'stp:',DR,DP,DZ,DM
      WRITE (UNIT = 2,FMT = *) 

! ->  
      DM2 = DM * DM
      DR2 = DR * DR
      DP2 = DP * DP
      DZ2 = DZ * DZ

!     
      CFR = DM2 / DR2
      CFP = DM2 / DP2
      CFZ = DM2 / DZ2

!     
      WRITE (UNIT = *,FMT = '(1x,a4,3(1x,1pe15.8))') 'cfs:',CFR,CFP,CFZ
      WRITE (UNIT = 2,FMT = '(1x,a4,3(1x,1pe15.8))') 'cfs:',CFR,CFP,CFZ

! ->  
      DO  I = 0,NR
         RR(I) = RA + DR * I
      ENDDO  

!     
      DO  J = 0,NP
         PP(J) = DP * J
      ENDDO  

!     
      DO  K = 0,NZ
         ZZ(K) = ZA + DZ * K
      ENDDO  

! ->  
      DO  I = 1,NR
         RS(I) = 0.5D0 * (RR(I - 1) + RR(I))
      ENDDO  

!     
      DO  J = 1,NP
         PS(J) = 0.5D0 * (PP(J - 1) + PP(J))
      ENDDO  

!     
      DO  K = 1,NZ
         ZS(K) = 0.5D0 * (ZZ(K - 1) + ZZ(K))
      ENDDO  

! ->  
      K0 = NZ / 2

! ->  
      IF (LP .GT. 0) THEN

!     
         WRITE (UNIT = 2,FMT = '(5x,a1,8x,a2)') 'i','rr'
         DO  I = 0,NR
            WRITE (UNIT = 2,FMT = '(1x,i8,1x,1pe15.8)') I,RR(I)
         ENDDO  
         WRITE (UNIT = 2,FMT = *) 

!     
         WRITE (UNIT = 2,FMT = '(5x,a1,8x,a2)') 'j','pp'
         DO  J = 0,NP
            WRITE (UNIT = 2,FMT = '(1x,i8,1x,1pe15.8)') J,PP(J)
         ENDDO  
         WRITE (UNIT = 2,FMT = *) 

!     
         WRITE (UNIT = 2,FMT = '(5x,a1,8x,a2)') 'k','zz'
         DO  K = 0,NZ
            WRITE (UNIT = 2,FMT = '(1x,i8,1x,1pe15.8)') K,ZZ(K)
         ENDDO  
         WRITE (UNIT = 2,FMT = *) 

!     
         WRITE (UNIT = 2,FMT = '(5x,a1,8x,a2)') 'i','rs'
         DO  I = 1,NR
            WRITE (UNIT = 2,FMT = '(1x,i8,1x,1pe15.8)') I,RS(I)
         ENDDO  
         WRITE (UNIT = 2,FMT = *) 

!     
         WRITE (UNIT = 2,FMT = '(5x,a1,8x,a2)') 'j','ps'
         DO  J = 1,NP
            WRITE (UNIT = 2,FMT = '(1x,i8,1x,1pe15.8)') J,PS(J)
         ENDDO  
         WRITE (UNIT = 2,FMT = *) 

!     
         WRITE (UNIT = 2,FMT = '(5x,a1,8x,a2)') 'k','zs'
         DO  K = 1,NZ
            WRITE (UNIT = 2,FMT = '(1x,i8,1x,1pe15.8)') K,ZS(K)
         ENDDO  
         WRITE (UNIT = 2,FMT = *) 

!     
      ENDIF  

! ->  
      DO  K = 1,NZ
         Z = ZS(K)

!     
         DO  I = 1,NR
            R = RS(I)

!     
            M = 4

!     
            IF (IN_RANGE_D (Z11N,Z12N,Z) .EQ. 0) THEN
               IF (IN_RANGE_D (R11N,R12N,R) .EQ. 0) THEN
                  M = 1
                  GOTO 5
               ENDIF  
            ENDIF  

!     
            IF (IN_RANGE_D (Z21N,Z22N,Z) .EQ. 0) THEN
               IF (IN_RANGE_D (R21N,R22N,R) .EQ. 0) THEN
                  M = 2
                  GOTO 5
               ENDIF  
            ENDIF  

!     
            IF (IN_RANGE_D (Z31N,Z32N,Z) .EQ. 0) THEN
               IF (IN_RANGE_D (R31N,R32N,R) .EQ. 0) THEN
                  M = 3
                  GOTO 5
               ENDIF  
            ENDIF  

!     
5           MAP(I,K) = M

!     
         ENDDO  
      ENDDO  

! ->  
      CALL TPL2D_REC_I(10,'magint_3d_map.plt','TITLE = "MAP"','VARIABLES
     & = "R" "Z" "MAP"',NR,NZ,RS,ZS,MAP)

! ->  
      CALL TPL2D_REC_IM(10,'magint_3d_map_xz.plt','TITLE = "MAP"','VARIA
     &BLES = "X" "Z" "MAP"',NR,NZ,RS,ZS,MAP)

! ->  
      DO  K = 1,NZ
         DO  I = 1,NR
            M = MAP(I,K)
            AR_RZ(I,K) = VMUMAT(M,M)
         ENDDO  
      ENDDO  

! ->  
      CALL TPL2D_REC_D(10,'magint_3d_vMu.plt','TITLE = "vMu"','VARIABLES
     & = "R" "Z" "vMu"',NR,NZ,RS,ZS,AR_RZ)

! --- 
      WRITE (UNIT = *,FMT = *) '---> Iterative loop'
      WRITE (UNIT = 2,FMT = *) '---> Iterative loop'

! --- 
      CPU_T2 = OMP_GET_WTIME ()

! --- 
      ZERO = 1D-15

! --- 
      IT = 0

!     
      IT1 = 0
      RK1 = 1D0

! ->  
      DO  K = 1,NZ
         DO  J = 1,NP
            DO  I = 1,NR
               PHI1(I,J,K) = PHI0
               PHI2(I,J,K) = PHI0
               PHI3(I,J,K) = PHI0
            ENDDO  
         ENDDO  
      ENDDO  

! ->  
!_omp parallel num_threads(nthr) private (nth,mth)
!OMP_GET_NUM_THREADS ()     
      NTH = 1 
      MTH = 0
!OMP_GET_THREAD_NUM ()     
      CALL MAIN_CALC(NTH,MTH,NR,NP,NZ,MAP,RR,RS,PHI1,PHI2,PHI3,RK,RK1,IT
     &,IT1,LOCK)

!     
!_omp end parallel
!     
! --- results ---
!     
20    CONTINUE

!     
      WRITE (UNIT = *,FMT = *) 'final result:'
      WRITE (UNIT = 2,FMT = *) 'final result:'

!     
      WRITE (UNIT = *,FMT = '(4h it=,i8,4h rk=,1x,1pe12.5)') IT1,RK1
      WRITE (UNIT = 2,FMT = '(4h it=,i8,4h rk=,1x,1pe12.5)') IT1,RK1

! ->  
      DO  K = 1,NZ
         DO  I = 1,NR
            AR_RZ(I,K) = PHI3(I,1,K)
         ENDDO  
      ENDDO  

!     
      DO  J = 1,NP
         DO  I = 1,NR
            AR_RP(I,J) = PHI3(I,J,K0)
         ENDDO  
      ENDDO  

!     
      CALL TPL2D_REC_D(10,'magint_3d_phi_rz.plt','TITLE = "phi*(r,z)"','
     &VARIABLE = "R" "Z" "PHI"',NR,NZ,RS,ZS,AR_RZ)

!     
      CALL TPL2D_REC_DM(10,'magint_3d_phi_xz.plt','TITLE = "phi*(x,0,z)"
     &','VARIABLE = "X" "Z" "PHI"',NR,NZ,RS,ZS,AR_RZ)

!     
      CALL TPL2D_REC_D(10,'magint_3d_phi_rp.plt','TITLE = "phi*(r,p)"','
     &VARIABLE = "R" "P" "PHI"',NR,NP,RS,PS,AR_RP)

! ->  
      DO  K = 1,NZ
         DO  J = 1,NP
            DO  I = 1,NR

! -   
               IF (I .EQ. 1) THEN
                  A1 = RS(I)
                  A2 = RS(I + 1)
                  A3 = RS(I + 2)
                  V1 = PHI3(I,J,K)
                  V2 = PHI3(I + 1,J,K)
                  V3 = PHI3(I + 2,J,K)
                  VP = FP2P1 (A1,A2,A3,V1,V2,V3,A1)
               ELSE  
                  IF (I .EQ. NR) THEN
                     A1 = RS(I - 2)
                     A2 = RS(I - 1)
                     A3 = RS(I)
                     V1 = PHI3(I - 2,J,K)
                     V2 = PHI3(I - 1,J,K)
                     V3 = PHI3(I,J,K)
                     VP = FP2P1 (A1,A2,A3,V1,V2,V3,A3)
                  ELSE  
                     A1 = RS(I - 1)
                     A2 = RS(I)
                     A3 = RS(I + 1)
                     V1 = PHI3(I - 1,J,K)
                     V2 = PHI3(I,J,K)
                     V3 = PHI3(I + 1,J,K)
                     VP = FP2P1 (A1,A2,A3,V1,V2,V3,A2)
                  ENDIF  
               ENDIF  

!     
               VHR = (-(VP))

! -   
               IF (J .EQ. 1) THEN
                  A1 = PS(NP)
                  V1 = PHI3(I,NP,K)
               ELSE  
                  A1 = PS(J - 1)
                  V1 = PHI3(I,J - 1,K)
               ENDIF  

!     
               A2 = PS(J)
               V2 = PHI3(I,J,K)

!     
               IF (J .EQ. NP) THEN
                  A3 = PS(1)
                  V3 = PHI3(I,1,K)
               ELSE  
                  A3 = PS(J + 1)
                  V3 = PHI3(I,J + 1,K)
               ENDIF  

!     
               VP = FP2P1 (A1,A2,A3,V1,V2,V3,A2)

!     
               VHP = (-(VP)) / RS(J)

! -   
               IF (K .EQ. 1) THEN
                  A1 = ZS(K)
                  A2 = ZS(K + 1)
                  A3 = ZS(K + 2)
                  V1 = PHI3(I,J,K)
                  V2 = PHI3(I,J,K + 1)
                  V3 = PHI3(I,J,K + 2)
                  VP = FP2P1 (A1,A2,A3,V1,V2,V3,A1)
               ELSE  
                  IF (K .EQ. NZ) THEN
                     A1 = ZS(K - 2)
                     A2 = ZS(K - 1)
                     A3 = ZS(K)
                     V1 = PHI3(I,J,K - 2)
                     V2 = PHI3(I,J,K - 1)
                     V3 = PHI3(I,J,K)
                     VP = FP2P1 (A1,A2,A3,V1,V2,V3,A3)
                  ELSE  
                     A1 = ZS(K - 1)
                     A2 = ZS(K)
                     A3 = ZS(K + 1)
                     V1 = PHI3(I,J,K - 1)
                     V2 = PHI3(I,J,K)
                     V3 = PHI3(I,J,K + 1)
                     VP = FP2P1 (A1,A2,A3,V1,V2,V3,A2)
                  ENDIF  
               ENDIF  

!     
               VHZ = (-(VP))

! -   
               CPH = DCOSM (PS(J))
               SPH = DSINM (PS(J))

!     
               VHX = VHR * CPH - VHP * SPH
               VHY = VHR * SPH + VHP * CPH

! -   
               M = MAP(I,K)

! -   
               IF (M .EQ. 2 .OR. M .EQ. 3) THEN
                  VBX = VHX + VJX
                  VBY = VHY + VJY
                  VBZ = VHZ + VJZM(M)
                  VBR = VHR + VJR
                  VBP = VHP + VJP
               ELSE  
                  VMU = VMUMAT(M,M)
                  VBX = VMU * VHX
                  VBY = VMU * VHY
                  VBZ = VMU * VHZ
                  VBR = VMU * VHR
                  VBP = VMU * VHP
               ENDIF  

! -   
               HX(I,J,K) = VHX
               HY(I,J,K) = VHY
               HZ(I,J,K) = VHZ
               HR(I,J,K) = VHR
               HP(I,J,K) = VHP

! -   
               BX(I,J,K) = VBX
               BY(I,J,K) = VBY
               BZ(I,J,K) = VBZ
               BR(I,J,K) = VBR
               BP(I,J,K) = VBP

! -   
               IF (LP .GT. 0) THEN

!     
                  WRITE (UNIT = 2,FMT = '(1x,a4,4(1x,i8))') 'ijkm',I,J,K
     &,M

!     
                  WRITE (UNIT = 2,FMT = '(1x,a4,5(1x,1pe13.6))') ' vH:',
     &VHX,VHY,VHZ,VHR,VHP

!     
                  WRITE (UNIT = 2,FMT = '(1x,a4,5(1x,1pe13.6))') ' vB:',
     &VBX,VBY,VBZ,VBR,VBP

!     
               ENDIF  

! -   
            ENDDO  
         ENDDO  
      ENDDO  

! ->  
      DO  K = 1,NZ
         DO  I = 1,NR
            ARX_RZ(I,K) = HX(I,1,K)
            ARY_RZ(I,K) = HY(I,1,K)
            ARZ_RZ(I,K) = HZ(I,1,K)
         ENDDO  
      ENDDO  

!     
      CALL TPL2D_REC_D(10,'magint_3d_Hz_rz.plt','TITLE = "Hz(r,z)"','VAR
     &IABLE = "R" "Z" "Hz"',NR,NZ,RS,ZS,ARZ_RZ)

!     
      CALL TPL2D_REC_DM3(10,'magint_3d_Hv_xz.plt','TITLE = "Hv(x,0,z)"',
     &'VARIABLE = "X" "Z" "Hx" "Hy" "Hz" "Hm"',NR,NZ,RS,ZS,ARX_RZ,ARY_RZ
     &,ARZ_RZ)

! ->  
      DO  K = 1,NZ
         DO  I = 1,NR
            ARX_RZ(I,K) = BX(I,1,K)
            ARY_RZ(I,K) = BY(I,1,K)
            ARZ_RZ(I,K) = BZ(I,1,K)
         ENDDO  
      ENDDO  

!     
      CALL TPL2D_REC_D(10,'magint_3d_Bz_rz.plt','TITLE = "Bz(r,z)"','VAR
     &IABLE = "R" "Z" "Bz"',NR,NZ,RS,ZS,ARZ_RZ)

!     
      CALL TPL2D_REC_DM3(10,'magint_3d_Bv_xz.plt','TITLE = "Bv(x,0,z)"',
     &'VARIABLE = "X" "Z" "Bx" "By" "Bz" "Bm"',NR,NZ,RS,ZS,ARX_RZ,ARY_RZ
     &,ARZ_RZ)

! --- 
      CPU_T3 = OMP_GET_WTIME ()

!     
      CPU_DT1 = CPU_T2 - CPU_T1
      CPU_DT2 = CPU_T3 - CPU_T2

!     
      WRITE (UNIT = 2,FMT = '(11h cpu_times:,2(1x,f10.3))') CPU_DT1,CPU_
     &DT2
      WRITE (UNIT = *,FMT = '(11h cpu_times:,2(1x,f10.3))') CPU_DT1,CPU_
     &DT2

! --- 
999   CONTINUE

!     
      CLOSE (UNIT = 2)

! --- 
      IF (ALLOCATED (MAP))  DEALLOCATE(MAP)

     
      IF (ALLOCATED (RR))  DEALLOCATE(RR)
      IF (ALLOCATED (PP))  DEALLOCATE(PP)
      IF (ALLOCATED (ZZ))  DEALLOCATE(ZZ)

     
      IF (ALLOCATED (RR))  DEALLOCATE(RS)
      IF (ALLOCATED (PP))  DEALLOCATE(PS)
      IF (ALLOCATED (ZZ))  DEALLOCATE(ZS)

     
      IF (ALLOCATED (PHI1))  DEALLOCATE(PHI1)
      IF (ALLOCATED (PHI2))  DEALLOCATE(PHI2)
      IF (ALLOCATED (PHI3))  DEALLOCATE(PHI3)

     
      IF (ALLOCATED (AR_RZ))  DEALLOCATE(AR_RZ)
      IF (ALLOCATED (AR_RP))  DEALLOCATE(AR_RP)

     
      IF (ALLOCATED (ARX_RZ))  DEALLOCATE(ARX_RZ)
      IF (ALLOCATED (ARY_RZ))  DEALLOCATE(ARY_RZ)
      IF (ALLOCATED (ARZ_RZ))  DEALLOCATE(ARZ_RZ)

     
      IF (ALLOCATED (HX))  DEALLOCATE(HX)
      IF (ALLOCATED (HY))  DEALLOCATE(HY)
      IF (ALLOCATED (HZ))  DEALLOCATE(HZ)
      IF (ALLOCATED (HR))  DEALLOCATE(HR)
      IF (ALLOCATED (HP))  DEALLOCATE(HP)

     
      IF (ALLOCATED (BX))  DEALLOCATE(BX)
      IF (ALLOCATED (BY))  DEALLOCATE(BY)
      IF (ALLOCATED (BZ))  DEALLOCATE(BZ)
      IF (ALLOCATED (BR))  DEALLOCATE(BR)
      IF (ALLOCATED (BP))  DEALLOCATE(BP)

! --- 
      STOP
      END


! ----------------------------------------------------------------------
      SUBROUTINE MAIN_CALC (NTH, MTH, NR, NP, NZ, MAP, RR, RS, PHI1, PHI
     &2, PHI3, RK, RK1, IT, IT1, LOCK)

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
!      include 'omp_lib.h'
!     
!      INTEGER(KIND=OMP_LOCK_KIND) ::  LOCK

!     
      INTEGER*4 ::  MAP(NR,NZ)

!     
      REAL*8 ::  RR(0:NR),RS(NR)
      REAL*8 ::  PHI1(NR,NP,NZ)
      REAL*8 ::  PHI2(NR,NP,NZ)
      REAL*8 ::  PHI3(NR,NP,NZ)

!     
! --- 
      COMMON /BMAIN/DR,DP,DZ,CFR,CFP,CFZ
      COMMON /BMATR/VMUMAT(4,4),VJRM(4),VJZM(4)
      COMMON /BITER/EPS,TAU,RKC,PHI0,ITM,ITP,ITS,K0

! --- 
      CALL SECT1D(NTH,MTH,1,NZ,K1,K2)

!     
!     write(*,*) 'CALC_1:', nth, mth, k1, k2
! --- 
10    CONTINUE

! ->  
      IF (MTH .EQ. 0) THEN
         RK = 0D0
      ENDIF  

! ->  
      RK0 = 0D0

! --- 
!$SPF ANALYSIS(PRIVATE(VMU,VIJMK,VIJPK))
      DO  K = K1,K2
         DO  J = 1,NP
            DO  I = 1,NR

! ->  
               MA_0 = MAP(I,K)

!     
               MA_L = 0
               MA_R = 0
               MA_B = 0
               MA_T = 0

!     
!- left
               IF (I .GT. 1)  MA_L = MAP(I - 1,K)

!- right
               IF (I .LT. NR)  MA_R = MAP(I + 1,K)

!- bottom
               IF (K .GT. 1)  MA_B = MAP(I,K - 1)

!- top
               IF (K .LT. NZ)  MA_T = MAP(I,K + 1)

! ->  
               VIJK = PHI1(I,J,K)

! ->  
               DIAG = 0D0

! ->  
               WRM = 0D0
               WRP = 0D0

!     
               IF (I .GT. 1) THEN

!- Jacobi
                  VIMJK = PHI1(I - 1,J,K)
                  S1 = CFR * RR(I - 1) / RS(I)
                  IF (MA_0 .EQ. MA_L) THEN
                     VMU = VMUMAT(MA_0,MA_0)
                     WRM = S1 * VMU * (VIMJK - VIJK)
                  ELSE  
                     VMU = VMUMAT(MA_L,MA_0)
                     WW1 = 0.5D0 * DR * VJRM(MA_L) / VMUMAT(MA_L,MA_L)
                     WW2 = 0.5D0 * DR * VJRM(MA_0) / VMUMAT(MA_0,MA_0)
                     WWW = WW1 + WW2
                     WRM = S1 * VMU * (VIMJK - VIJK + WWW)
                  ENDIF  
                  DIAG = DIAG + S1 * VMU
               ENDIF  

!     
               IF (I .LT. NR) THEN
                  VIPJK = PHI1(I + 1,J,K)
                  S2 = CFR * RR(I) / RS(I)
                  IF (MA_0 .EQ. MA_R) THEN
                     VMU = VMUMAT(MA_0,MA_0)
                     WRP = S2 * VMU * (VIPJK - VIJK)
                  ELSE  
                     VMU = VMUMAT(MA_0,MA_R)
                     WW1 = 0.5D0 * DR * VJRM(MA_0) / VMUMAT(MA_0,MA_0)
                     WW2 = 0.5D0 * DR * VJRM(MA_R) / VMUMAT(MA_R,MA_R)
                     WWW = WW1 + WW2
                     WRP = S2 * VMU * (VIPJK - VIJK - WWW)
                  ENDIF  
                  DIAG = DIAG + S2 * VMU
               ENDIF  

! ->  
               IF (J .GT. 1) THEN

!- Jacobi
                  VIJMK = PHI1(I,J - 1,K)
               ELSE  
                  VIJMK = PHI1(I,NP,K)
               ENDIF  

!     
               IF (J .LT. NP) THEN
                  VIJPK = PHI1(I,J + 1,K)
               ELSE  
                  VIJPK = PHI1(I,1,K)
               ENDIF  

!     
               RS2 = RS(I) * RS(I)
               VMU = VMUMAT(MA_0,MA_0)
               S3 = CFP / RS2
               WPM = S3 * VMU * (VIJMK - VIJK)
               WPP = S3 * VMU * (VIJPK - VIJK)
               DIAG = DIAG + S3 * VMU

! ->  
               WZM = 0D0
               WZP = 0D0

!     
               IF (K .GT. 1) THEN

!- Jacobi
                  VIJKM = PHI1(I,J,K - 1)
                  IF (MA_0 .EQ. MA_B) THEN
                     VMU = VMUMAT(MA_0,MA_0)
                     WZM = CFZ * VMU * (VIJKM - VIJK)
                  ELSE  
                     VMU = VMUMAT(MA_B,MA_0)
                     WW1 = 0.5D0 * DZ * VJZM(MA_B) / VMUMAT(MA_B,MA_B)
                     WW2 = 0.5D0 * DZ * VJZM(MA_0) / VMUMAT(MA_0,MA_0)
                     WWW = WW1 + WW2
                     WZM = CFZ * VMU * (VIJKM - VIJK + WWW)
                  ENDIF  
                  DIAG = DIAG + CFZ * VMU
               ENDIF  

!     
               IF (K .LT. NZ) THEN
                  VIJKP = PHI1(I,J,K + 1)
                  IF (MA_0 .EQ. MA_T) THEN
                     VMU = VMUMAT(MA_0,MA_0)
                     WZP = CFZ * VMU * (VIJKP - VIJK)
                  ELSE  
                     VMU = VMUMAT(MA_0,MA_T)
                     WW1 = 0.5D0 * DZ * VJZM(MA_0) / VMUMAT(MA_0,MA_0)
                     WW2 = 0.5D0 * DZ * VJZM(MA_T) / VMUMAT(MA_T,MA_T)
                     WWW = WW1 + WW2
                     WZP = CFZ * VMU * (VIJKP - VIJK - WWW)
                     DIAG = DIAG + CFZ * VMU
                  ENDIF  
               ENDIF  

! ->  
               S0 = WRP + WRM + WPP + WPM + WZP + WZM
               RK0 = DMAX1 (RK0,S0)

!     
               PHI2(I,J,K) = VIJK + TAU * (S0 / DIAG)

!     
            ENDDO  
         ENDDO  
      ENDDO  

! ->  
!     write(*,*) 'CALC_2:', mth, rk0
! --- 
!_omp barrier
!      CALL OMP_SET_LOCK(LOCK)
      RK = DMAX1 (RK,RK0)
!      CALL OMP_UNSET_LOCK(LOCK)

!_omp barrier
! --- 
      IF (MTH .EQ. 0) THEN
         IF (MOD (IT,ITP) .EQ. 0 .OR. RK .LE. EPS .OR. IT .EQ. ITM) THEN
            WRITE (UNIT = *,FMT = '(4h it=,i8,4h rk=,1x,1pe12.5,1x,1pe12
     &.5)') IT,RK,RK1
            WRITE (UNIT = 2,FMT = '(4h it=,i8,4h rk=,1x,1pe12.5,1x,1pe12
     &.5)') IT,RK,RK1
         ENDIF  
      ENDIF  

! ->  
      IF (RK .LT. RK1) THEN
         IF (MTH .EQ. 0) THEN
            RK1 = RK
            IT1 = IT
         ENDIF  

!     
         DO  K = K1,K2
            DO  J = 1,NP
               DO  I = 1,NR
                  S1 = PHI1(I,J,K)
                  PHI3(I,J,K) = S1
               ENDDO  
            ENDDO  
         ENDDO  
      ENDIF  

! ->  
      IF (RK .LE. EPS)  GOTO 20
      IF (IT .GE. ITM)  GOTO 20
      IF (RK .GT. RKC * RK1)  GOTO 20

! ->  
      IF (MTH .EQ. 0) THEN
         IT = IT + 1
      ENDIF  

! ->  
      DO  K = K1,K2
         DO  J = 1,NP
            DO  I = 1,NR
               S2 = PHI2(I,J,K)
               PHI1(I,J,K) = S2
            ENDDO  
         ENDDO  
      ENDDO  

! ->  
      IF (MTH .EQ. 0) THEN
         PHI1(1,1,K0) = PHI0
      ENDIF  

! ->  
!_omp barrier
! ->  
      GOTO 10

! ->  
20    CONTINUE

! ->  
!_omp barrier
! --- 
      RETURN 
      END


! ----------------------------------------------------------------------
!     Tecplot 2D, integer*4, (x,z) co-ordinates
! ----------------------------------------------------------------------
      SUBROUTINE TPL2D_REC_IM (ICH, FNAME, TNAME, VNAME, N1, N2, X1, X2,
     & X3)

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
      WRITE (UNIT = ICH,FMT = *) 'ZONE T="BIG" I=',2 * N1,' J=',N2,' F=P
     &OINT'

!     
      DO  J = 1,N2
         V2 = X2(J)
         DO  I = N1,1,(-(1))
            V1 = (-(X1(I)))
            V3 = 1D0 * X3(I,J)
            WRITE (UNIT = ICH,FMT = '(3(1x,1pe15.8))') V1,V2,V3
         ENDDO  
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
!     Tecplot 2D, real*8, (x,z) co-ordinates, output scalar
! ----------------------------------------------------------------------
      SUBROUTINE TPL2D_REC_DM (ICH, FNAME, TNAME, VNAME, N1, N2, X1, X2,
     & X3)

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
      WRITE (UNIT = ICH,FMT = *) 'ZONE T="BIG" I=',2 * N1,' J=',N2,' F=P
     &OINT'

!     
      DO  J = 1,N2
         V2 = X2(J)
         DO  I = N1,1,(-(1))
            V1 = (-(X1(I)))
            V3 = X3(I,J)
            WRITE (UNIT = ICH,FMT = '(3(1x,1pe15.8))') V1,V2,V3
         ENDDO  
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


! ----------------------------------------------------------------------
!     Tecplot 2D, real*8, (x,z) co-ordinates, output of 3D-vector 
! ----------------------------------------------------------------------
      SUBROUTINE TPL2D_REC_DM3 (ICH, FNAME, TNAME, VNAME, N1, N2, X1, X2
     &, X3, X4, X5)

!     
      IMPLICIT INTEGER*4  (I-N)
      IMPLICIT REAL*8  (A-H,O-Z)

!     
      CHARACTER*(*) ::  FNAME,TNAME,VNAME

!     
      REAL*8 ::  X1(N1),X2(N2)
      REAL*8 ::  X3(N1,N2),X4(N1,N2),X5(N1,N2)

!     
      OPEN (UNIT = ICH,FILE = FNAME)

!     
      WRITE (UNIT = ICH,FMT = *) TNAME
      WRITE (UNIT = ICH,FMT = *) VNAME
      WRITE (UNIT = ICH,FMT = *) 'ZONE T="BIG" I=',2 * N1,' J=',N2,' F=P
     &OINT'

!     
      DO  J = 1,N2
         V2 = X2(J)
         DO  I = N1,1,(-(1))
            V1 = (-(X1(I)))
            V3 = (-(X3(I,J)))
            V4 = X4(I,J)
            V5 = X5(I,J)
            V6 = DSQRTM (V3 * V3 + V4 * V4 + V5 * V5)
            IF (V6 .GE. 1E-15) THEN
               V3 = V3 / V6
               V4 = V4 / V6
               V5 = V5 / V6
            ENDIF  
            WRITE (UNIT = ICH,FMT = '(6(1x,1pe15.8))') V1,V2,V3,V4,V5,V6
         ENDDO  
         DO  I = 1,N1
            V1 = X1(I)
            V3 = X3(I,J)
            V4 = X4(I,J)
            V5 = X5(I,J)
            V6 = DSQRTM (V3 * V3 + V4 * V4 + V5 * V5)
            IF (V6 .GE. 1E-15) THEN
               V3 = V3 / V6
               V4 = V4 / V6
               V5 = V5 / V6
            ENDIF  
            WRITE (UNIT = ICH,FMT = '(6(1x,1pe15.8))') V1,V2,V3,V4,V5,V6
         ENDDO  
      ENDDO  

!     
      CLOSE (UNIT = ICH)

!     
      RETURN 
      END

