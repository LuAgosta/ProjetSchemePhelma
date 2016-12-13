; TEST_RETURN_CODE=PASS
; TEST_COMMENT= define
;

(define mult_2 (lambda (x) (* x 2)))
(mult_2 2)

(define (add_2 x) (+ x 2)) ; Autre manière de définir une procédure
(add_2 2)

(define (sup x y) (if (< x y) x y))
(sup 3 5)
(sup 5 3)

