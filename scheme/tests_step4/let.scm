; TEST_RETURN_CODE=PASS
; TEST_COMMENT= let
;
(let ((x 2) (y 3)) (* x y))
(let ((x 2) (y 3)) (let ((x 7) (z (+ x y))) (* z x)))
(define a (lambda (x y) (+ y x)))
(define b 3)
(let ((x 2) (y 3)) (+ b (a x y)) )
(define x 45)
(let ((x 2) (y 3)) (* x y))
x
