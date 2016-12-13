; TEST_RETURN_CODE=PASS
; TEST_COMMENT= let*
;
let*
(let ((x 2) (y 3)) (let* ((x 7) (z (+ x y))) (* z x)))
(let ((x 2) (y 3)) (let* ((x 7) (z (+ x y))) (let* ((a z) (b x)) (* a b))))
(define x 45)
(define y "hi!")
(let ((x 2) (y 3)) (let* ((x 7) (z (+ x y))) (* z x)))
x
y
