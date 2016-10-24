; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de set! 
;

(define a 9)
(set! a 10)
a
(set! a "toto")
a
(define b a)
b
(set! a 3)
b
(set! b 12)
a
