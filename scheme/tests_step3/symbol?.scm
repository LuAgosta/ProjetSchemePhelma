; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test du predicat symbol?
;
(symbol? 'a)
(symbol? #\a)
(define b 'c)
(symbol? b)
(define d 45)
(symbol? d)
