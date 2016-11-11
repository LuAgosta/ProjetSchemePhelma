; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de l'influence de define et de set! sur l'ensemble des environnements
;
(define bob 2)
(define a 7)
addenv
(define bob 45)
(define b 89)
(set! bob 111)
(set! a 777)
