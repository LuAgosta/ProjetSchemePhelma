; TEST_RETURN_CODE=PASS
; TEST_COMMENT= car
;
(car (cons 1 (cons 2 ())))
(car (quote (1 2)))
(car (cons #\a 2))
(car (cons (+ 4 5) ( cons 2 ())))
(car (quote (+ 4 5)))
(car (quote ((+ 4 5) "hello")))
