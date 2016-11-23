; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test du predicat boolean?
;
(boolean? #t)
(boolean? '#f)
(boolean? #\f)
(boolean? (or #t #f))
