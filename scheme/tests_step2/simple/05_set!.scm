; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de set! 
;

(define a 9)
(set! a 10)
a
(set! a "toto")
a
(define b 11)
b
(set! b a)
b
(set! a 12)
a
b             ; b NE doit PAS prendre la nouvelle valeur de a 
(set! a 56)
a
b             ; b NE doit PAS prendre la nouvelle valeur de a 
(set! c 1)    ; c n'étant pas préalablement définie, l'interpréteur retourne () 
