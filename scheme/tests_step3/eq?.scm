; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de eq?
;
(eq? '() ())
(eq? #t #t)
(eq? '#f '#f)
(eq? #t #f)
(eq? 12 12)
(eq? 12 (+ 6 6))
(eq? 'big 'big)
(eq? 'bill 'broonzy)
(define a 2)
(define b 2)
(eq? a b)
(define c b)
(eq? c b)
