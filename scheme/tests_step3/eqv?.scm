; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test de eqv?
;
(eqv? #t #t)
(eqv? 45 45)
(eqv? #\t #\t)
(eqv? () ())
(eqv? #t #f)
(eqv? 45 4)
(eqv? #\t #\f)
(eqv? () 75)
(eqv? (cons 1 2) (cons 1 2))
(define a '(4 5))
(define b a)
(eqv? a b)
(eqv? "er" "er")
(define c "er")
(define d c)
(eqv? c d)
