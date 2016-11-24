; TEST_RETURN_CODE=PASS
; TEST_COMMENT= sup
;
(> 5 6)
(> 6 5)
(define a 6)
(> (if (> a 7) a 7) 7)
