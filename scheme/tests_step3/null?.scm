; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test du prédicat null?
;
(null? ())
(null? '())
(define a ())
(null? a)
(define b "nil")
(null? b)
(null? 4521)
