; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de la forme if, or et and
;
(if (or (= 5 5) (< 5 4)) (quote oui) (quote non))
(if (or (= 4 5) (< 5 4)) (quote oui) (quote non))
(if (or (= 5 5) (> 5 4)) (quote oui) (quote non))
(if (and (= 5 5) (> 5 4)) (quote oui) (quote non))
(if (and (= 4 5) (> 5 4)) (quote oui) (quote non))
(if (and (= 4 5) (< 5 4)) (quote oui) (quote non))
(if (and (or (= 5 5) (= 5 4)) (and (!= 4 5) (= 7 7))) (quote oui) (quote non))
(if (and (or (= 5 5) (= 5 4)) (and (!= 4 5) (= 7 8))) (quote oui) (quote non))
(if (or (or (= 5 5) (= 5 4)) (and (!= 4 5) (= 7 8))) (quote oui) (quote non))
