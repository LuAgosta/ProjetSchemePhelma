; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test de la forme if
;
(if (= 5 5) (quote oui) (quote non))
(if (= 5 4) (quote oui) (quote non))
(if (< 4 5) (quote oui) (quote non))
(if (< 5 4) (quote oui) (quote non))
(if (> 4 5) (quote oui) (quote non))
(if (>= 4 5) (quote oui) (quote non))
(if (>= 45 45) (quote oui) (quote non))
(if (<= 45 45) (quote oui) (quote non))
(if (!= 4 45) (quote oui) (quote non))
(if (!= 4 4) (quote oui) (quote non))
