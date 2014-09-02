(define (getxyz r)
  (let ((anglez (random 3.1415926))
	(anglex (random (* 2 3.1415926))))
    (let ((z (* r (cos anglez))))
      (let ((phi (sqrt (- (square r) (square z)))))
	(let ((x (* phi (sin anglex)))
	      (y (* phi (cos anglex))))
	  (list x y z))))))

(define (scale M_s M_bh xyz)
  (let ((r (sqrt (/ M_s M_bh))))
    (map (lambda(x) (* x r)) xyz)))

(Scale 0.54 1000.0 (append (getxyz 0.183916) (getxyz 0.880171)))
