; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test define evolved
;
(= 5 5)
(= 5 6)
(define a 6)
(define b 8)
(= a b)
(set! b 6)
(= a b)
(= "hello" "hello")
(= "hello" "jean") 
(= #t #f) 
(= () () ) 
(= #\a #\a) 
(= (+ 4 5 ) (if (< 4 5) (+ 4 5 ) (+ 7 8))) 
