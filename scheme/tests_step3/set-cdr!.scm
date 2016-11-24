; TEST_RETURN_CODE=PASS
; TEST_COMMENT= set-cdr!
;
(set-cdr! (cons 1 (cons 2())) 77)
(set-cdr! (cons"toto" (cons 5 (cons 6()))) "titi" )
(set-cdr! '(2 #\a) #\0)
(define a '(4 5 6))
(set-cdr! a 58)
a
(set-cdr! (quote (8)) 77); on regarde si () est modifié
() 
