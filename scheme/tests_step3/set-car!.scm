; TEST_RETURN_CODE=PASS
; TEST_COMMENT= set-car!
;
(define a '(4 5 6))
a
(set-car! a 58)
a
(define b '(() 5))
(set-car! b 8) ;on regarde si () est modifié
()


