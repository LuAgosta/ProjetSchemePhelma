; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test define evolved
;

(define a 9)
a
(define b a)
b
(set! a "Robert")
b			; b doit prendre la nouvelle valeur de a


(define c 10)
c
(define d 45)
d
(set! c 45)
c
d			; d doit prendre la nouvelle valeur de c


(define e "coucou")
e
(define f e)
f
(set! f "hello")
e			; e NE doit PAS prendre la valeur de f (?)

(define g 12)
g
(define h 65)
h
(set! h g)
h
(set! g 45)
h        ; h NE doit PAS prendre la nouvelle valeur de g
(set! h "hello")
g        ; g NE doit PAS prendre la nouvelle valeur de h 
