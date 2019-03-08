        PROGRAM GOTO_TEST
		INTEGER I, J, SUMM
		SUMM = 0
		J = 0
		DO I = 1, 10
44		   SUMM = SUMM + I
		   GOTO 55
55		   J = I
           GOTO 44
		   EXIT
		ENDDO
		GOTO 55
		END
