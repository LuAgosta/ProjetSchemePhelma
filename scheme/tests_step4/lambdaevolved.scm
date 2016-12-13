; TEST_RETURN_CODE=PASS
; TEST_COMMENT= lambdaevolved 
;

(define fact (lambda (n) (if (= n 0) 1 ( * n (fact (- n 1))))))
fact
(fact 5)
(fact 12)

(define count         ; Notion de fermeture
	((lambda (total) 
		(lambda (inc)
		   (set! total (+ total inc))
			total))
	0))
count
(count 3)
(count 5)

(define (mult_2 x) (* x 2))
(define (map proc items)
	(if (null? items)
		'()
		(cons (proc (car items))
			(map proc (cdr items)))))
(map mult_2 '(0 1 2 3))

