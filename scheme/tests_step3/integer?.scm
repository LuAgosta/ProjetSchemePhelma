; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test du predicat integer?
;
(integer? 45)
(integer? '4)
(integer? (+ 4 5))
(define a 789)
(integer? a)
(define b "er")
(integer? b)
(integer? #\4)
