; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de la conversion integer->char
;
(integer->char 43)
(define bob 48)
(integer->char bob)
bob
(define c (integer->char bob))
(char? c)
