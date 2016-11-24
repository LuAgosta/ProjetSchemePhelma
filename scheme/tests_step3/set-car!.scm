; TEST_RETURN_CODE=PASS
; TEST_COMMENT= set-car!
;
(set-car! (cons 1 (cons 2())) 77)
(set-car! (cons (+ 4 6) (cons "toto" ())) "titi")
(set-car! '(#\a 2) #\0)
(define a '(4 5 6))
(set-car! a 58)
a
(set-car! (quote (() 5) ) 8) .; on regarde si () est modifié
() 


