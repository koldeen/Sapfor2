      PROGRAM TEST
      INTEGER I, K, N, C(20)
      DOUBLE PRECISION A(20, 20), TMP_BR1(7, 14)
      N = 5
      I = 1
!$SPF TRANSFORM(SHRINK(TMP_BR1 (1, 0), A(0, 0, 2), N, C, A(i,1),
!$SPF&K))
!$SPF ANALYSIS(PRIVATE(TMP_BR1,
!$SPF&A))
      DO I = 1,N
        DO K = 1,N
          TMP_BR1(K,I) = I + 7
          A(K,I) = TMP_BR1(K,I) + 12
        ENDDO
      ENDDO
      END
