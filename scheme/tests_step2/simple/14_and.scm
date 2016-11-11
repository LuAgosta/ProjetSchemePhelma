; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test define evolved
;


(and (< 4 5) (> 4 5))
(and (= "o" "o") (< 4 7 ))
(and (> 4 5) (< 4 5))
(and (and (< 4 5) (< 5 6) (< 6 7) ) (and (< 7 9 ) (< 8 9)))
(and (< 4 5 ) (< 5 6 ) (< 6 7) (< 7 8) (< 8 9))
