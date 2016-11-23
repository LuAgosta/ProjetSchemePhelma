; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de la conversion string->symbol
;
(string->symbol "sonny")
(define a "terry")
(string->symbol a)
(string? a)
(symbol? (string->symbol a))
