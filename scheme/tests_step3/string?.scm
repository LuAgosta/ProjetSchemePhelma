; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test du predicat string?
;
(string? "Bonnie & Clyde")
(define bonnie "clyde")
(string? bonnie)
(define clyde 1909)
(string? clyde)
(string? #\t)
