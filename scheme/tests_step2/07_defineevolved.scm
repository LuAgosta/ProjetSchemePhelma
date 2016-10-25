; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test define evolved
;

(define a 9)
a
(define a "toto")
a
(define b a) 
b
(set! a "Robert")
b			; b doit prendre la nouvelle valeur de a
(define a "Julie")
b			; b doit prendre la nouvelle valeur de a



(define c 10)
c
(define d 45)
d
(define d c)
d
(set! c 45)
c
d			; d doit prendre la nouvelle valeur de c 
(define c 952)
c
d			; d doit prendre la nouvelle valeur de c		



(define e "coucou")
e
(define f e)
f
(set! f "hello")
e			; e NE doit PAS prendre la valeur de f (?)
