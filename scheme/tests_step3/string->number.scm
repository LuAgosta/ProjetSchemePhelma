; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de la conversion string->number
;
(string->number "4521")
(string->number "45ef21")
(string->number '"4521")
(define s "145")
(string->number s)
(string? s)
