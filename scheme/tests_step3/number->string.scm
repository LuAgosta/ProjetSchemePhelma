; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de la conversion numner->string
;
(number->string 4781)
(number->string '452)
(number->string (+ 4 2))
(define a 78)
(number->string a)
(integer? a)
