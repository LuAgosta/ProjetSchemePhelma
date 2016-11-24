; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de la primitive quotient
;
(quotient 11 3)
(quotient 3 11)
(quotient 150 10 3 2)
(quotient 21 4 2)
(quotient 11 '3)
(quotient '11 '4)
(define a 8)
(define b 3)
(quotient a b)
'(quotient 11 3)
