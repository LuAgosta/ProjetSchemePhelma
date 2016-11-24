; TEST_RETURN_CODE=PASS
; TEST_COMMENT= cdr
;
(cdr (cons 1 (cons 2 ())))
(cdr (quote (1 2)))
(cdr (cons 2 #\a))
(cdr (cons 2( cons (+ 4 5) ())))
(cdr (quote (+ 4 5)))
(cdr (quote ((+ 4 5) "hello" (< 5 6))))
(define a 1)
(define b 2)
(define c 3)
(cdr (cons a (cons b ( cons c ()))))
