; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de set! 
;

(define a 9)
(set! a 10)
a
(set! a "toto")
a
(define b 11)
b
(set! b a)
b
(set! a 12)
a
b
(define a 56)
a
b
(set! c 1)
