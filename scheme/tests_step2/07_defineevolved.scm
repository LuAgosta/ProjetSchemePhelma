; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test define evolved
;

(define a 9)
a
(define a "toto")
a
(define b a) 
b
(set! a "Robert")
b
(define a "Julie")
b



(define c 10)
c
(define d 45)
d
(define d c)
d
(set! c 45)
c
d
(define c 952)
c
d
