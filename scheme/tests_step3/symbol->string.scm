; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de la conversion symbol->string
;
(symbol->string 'waters)
(define a 'muddy)
(symbol->string a)
(symbol? a)
(string? (symbol->string a))
