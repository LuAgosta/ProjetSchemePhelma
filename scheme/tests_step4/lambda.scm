; TEST_RETURN_CODE=PASS
; TEST_COMMENT= lambda
;
lambda
(lambda (x) (+ x x))
(lambda (x y) (+ x y))
((lambda (x) (+ x x)) 6)
((lambda (x y) ( + x y )) 9 7) 
((lambda (x y z) (set! x 2) (set! y 9) (set! z 10) (* x y z )) 1 1 1)
(define x 5)
((lambda (x) (set! x 8) x ) x)  
x
(define carre (lambda  (x) (* x x)))
(carre 2)
