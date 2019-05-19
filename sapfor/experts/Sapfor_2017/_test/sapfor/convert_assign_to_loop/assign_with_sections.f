	PROGRAM ASSIGN_WITH_SECTIONS

	REAL A (10), B (9), C(3)

	A(3:6) = B(4:7)
	A(1:5) = B(4:8)
	A(2:4) = C
	C = B(6:8)

	END
