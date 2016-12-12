; TEST_RETURN_CODE=PASS
; TEST_COMMENT= begin
;
(begin (+ 3 4))
(define a "hello") 
(begin "ola" a) 
(begin (set! a 5) (+ a a))
(define b 65)
(begin (set! b (+ b a) ) b)
(begin (define x 6) ( set! x ( - x )) ( set! x ( + x x)) (* -1 x) )
x
