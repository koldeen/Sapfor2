	PROGRAM EXPR_WITH_SECTIONS

	REAL A (10), B (9), C(3)

	A(3:6) = B(4:7) + B(3:6)
	A(1:5) = 2 * B(4:8) 
	A(2:4) = C + B(1:3)
	C = B(6:8) * A(1:3)

	END
