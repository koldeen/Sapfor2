      PROGRAM TEST
      INTEGER I, K, N
      DOUBLE PRECISION A(20, 20), TMP_BR1(7, 14)
      N = 5
!$SPF TRANSFORM(SHRINK(TMP_BR1 (1, 0)))
      DO I = 1,N
        DO K = 1,N
          TMP_BR1(K,I) = I + 7
          A(K,I) = TMP_BR1(K,I) + 12
        ENDDO
      ENDDO
      END
