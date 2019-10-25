      PROGRAM TEST
      INTEGER I, K, N, C(20)
      DOUBLE PRECISION A(20, 20), TMP_BR1(7, 14)
      N = 5
!$SPF TRANSFORM(SHRINK(TMP_BR1 (1, 0), A(0, 1, 2), C, A(1,1)))
!$SPF ANALYSIS(PRIVATE(TMP_BR1, A))
      DO I = 1,N
        DO K = 1,N
          TMP_BR1(K,I) = I + 7
          A(K,I) = TMP_BR1(K,I) + 12
        ENDDO
      ENDDO
      END
