; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test du predicat pair?
;
(pair? '(4 5))
(pair? '(4 5 6))
(pair? '(quote 4))
(pair? '7)
(pair? ())
(pair? '(4 '(7 78)))
