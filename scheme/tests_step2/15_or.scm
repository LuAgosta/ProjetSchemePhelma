; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test define evolved
;

(or (< 4 5) (> 4 5))
(or (!= "o" "o") (> 4 7 ))
(or (> 4 5) (< 4 5))
(or (or (> 4 5) (> 5 6) (> 6 7) ) (or (> 7 9 ) (< 8 9)))
(or (> 4 5 ) (> 5 6 ) (> 6 7) (> 7 8) (< 8 9))
