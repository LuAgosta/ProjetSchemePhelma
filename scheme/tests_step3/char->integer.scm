; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de la conversion char->integer
;
(char->integer #\t)
(define bob #\7)
(char->integer bob)
bob
(define n (char->integer bob))
(integer? n)
