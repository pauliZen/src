;;----Ex 1.16----;;
;;identify even number
(define (even? n)
  (= (remainder n 2) 0))
;;iterative exponentiation process with logarithmic steps
(define (fast-expt base n)
  (define (iter res base n)
    (cond ((= n 0 ) res)
	  ((even? n) (iter res (* base base) (/ n 2)))
	  (else (iter (* res base) base (- n 1)))))
  (iter 1 base n))

;;----Ex 1.19----;;
;;First trans.:
;;  a' = b q + a (p + q)
;;  b' = b p + a q
;;Second trans.:
;;  a'' = b q' + a (p' + q') = b (2pq + q^2) + a (2pq + 2q^2 + p^2)
;;  b'' = b p' + a q' = b (p^2 + q^2) + a (2pq + q^2)
;;=>
;;  p' = p^2 + q^2
;;  q' = 2pq + q^2

;;----Ex 1.22----;;
;;smallest divisor function
(define (square a)
  (* a a))
(define (divides? a b)
  (= (remainder b a) 0))
(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
	((divides? test-divisor n) test-divisor)
	(else (find-divisor n (+ test-divisor 1)))))
(define (smallest-divisor n)
  (find-divisor n 2))

;;----Ex 1.23----;;
;;time measure of identify prime n
(define (timed-prime-test n)
  (newline)
  (display n)
  (start-prime-test n (runtime)))
(define (start-prime-test n start-time)
  (if (prime? n)
      (report-prime (- (runtime) start-time))))
(define (report-prime elapsed-time)
  (display " *** ")
  (display elapsed-time))
(define (prime? n)
  (= (smallest-divisor n) n))
;;loop
(define (timed-prime-display a b)
  (timed-prime-test a)
  (if (< a b)
      ((timed-prime-display (+ a 1) b))))


;;----Ex 1.25----;;
;;expmod in book actually do remainder every time called expmod,
;;It calculated (remainder b^n-cn*n (where cn make it less than n) n)

;;----Ex 1.28----;;
;;Miller-Rabin test
(define (expmod-MRtest base exp m)
  (define (iter res base exp last-even last-base)
    (cond ((= exp 0) res)
	  ((and (= base 1) last-even (< last-base (- m 1)) (> last-base 1)) 0)
	  ((even? exp)
	   (iter res (remainder (square base) m) (/ exp 2) true base))
	  (else
	   (iter (remainder (* res base) m) base (- exp 1) false base))))
  (iter 1 base exp false base))

(define (MR-test n)
  (define (try-it a)
    (= (expmod-MRtest a (- n 1) n) 1))
  (try-it (+ 1 (random (- n 1)))))

(define (fast-prime? n times)
  (cond ((= times 0) true)
	((= n 1) true)
        ((MR-test n) (fast-prime? n (- times 1)))
        (else false)))

;;----Ex 1.29----;;
;;sum pattern
(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a)
         (sum term (next a) next b))))
;;Simpson's integral
(define (integral f a b n)
  (define (s-int f a b h)
    (define (add-dx x) (+ x (* 2 h)))
    (* (+ (* (sum f (+ a h) add-dx (- b h)) 4)
	  (* (sum f (add-dx a) add-dx (- b (* 2 h))) 2)
	  (f a) (f b))
       (/ h 3)))
  (if (even? n)
      (s-int f a b (/ (- b a) n))
      (display "n is not even")))
;;cube
(define (cube x)
  (* x x x))

;;----Ex 1.30----;;
;;iterative sum pattern
(define (sum term a next b)
  (define (iter a result)
    (if (> a b)
	result
	(iter (next a) (+ result (term a)))))
  (iter a 0))

;;----Ex 1.31----;;
;;recursive product pattern
(define (product term a next b)
  (if (> a b)
      1
      (* (term a)
	 (product term (next a) next b))))
;;iterative product pattern
(define (product term a next b)
  (define (iter a result)
    (if (> a b)
	result
	(iter (next a) (* result (term a)))))
  (iter a 1))
;;factorial
(define (! n)
  (define (f n) n)
  (define (add-one x) (+ x 1))
  (product f 1 add-one n))
;;pi/4 approx.
(define (get-pi n)
  (define (f i)
    (if (even? i)
	(/ i (+ i 1))
	(/ (+ i 1) i)))
  (define (add-one i) (+ i 1))
  (product f 2 add-one (+ n 1)))

;;----Ex 1.32----;;
;;recursive accumulate pattern
(define (accumulate combiner null-value term a next b)
  (if (> a b)
      null-value
      (combiner (term a)
		(accumulate combiner null-value term (next a) next b))))
;;iterative accumulate pattern
(define (accumulate combiner null-value term a next b)
  (define (iter a result)
    (if (> a b)
	result
	(iter (next a) (combiner result (term a)))))
  (iter a null-value))
;;sum using accumulate
(define (sum term a next b)
  (accumulate + 0 term a next b))
;;product using accumulate
(define (product term a next b)
  (accumulate * 1 term a next b))

;;----Ex 1.33----;;
;;filtered accumulate pattern (iterative)
(define (filtered-accumulate combiner null-value term a next b filter)
  (define (iter a result)
    (cond ((> a b) result)
	  ((filter a) (iter (next a) (combiner result (term a))))
	  (else (iter (next a) result))))
  (iter a null-value))
;;filtered sum pattern
(define (filtered-sum term a next b filter)
  (filtered-accumulate + 0 term a next b filter))
;;filtered product pattern
(define (filtered-product term a next b filter)
  (filtered-accumulate * 1 term a next b filter))
;;sum square of prime numbers
(define (sum-prime-square a b)
  (define (add-one x) (+ x 1))
  (define (prime? n)
    (fast-prime? n (if (< n 10) n 10)))
  (filtered-sum square a add-one b prime?))
;;GCD algorithm
(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))
;;product of all positive intergers less than n and are relatively prime to n
(define (product-prime-to-n n)
  (define (f x) x)
  (define (add-one x) (+ x 1))
  (define (prime? x) (= (gcd x n) 1))
  (filtered-product f 1 add-one (- n 1) prime?))

;;----Ex 1.35----;;
;;fixed-point
(define (fixed-point f first-guess tolerance)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
          next
          (try next))))
  (try first-guess))

(define (average x y)
  (/ (+ x y) 2))

(define (golden-ratio tolerance)
  (fixed-point (lambda (x) (average x (+ 1.0 (/ 1.0 x)))) 1.0 tolerance))

;;----Ex 1.36----;;
;;fixed-point with display
(define (fixed-point-display f first-guess tolerance)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (newline)
    (display guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
	  next
          (try next))))
  (try first-guess))

(define (x^x value tolerance)
  (fixed-point-display (lambda (x) (average x (/ (log value) (log x)))) 2.0 tolerance))

;;----Ex 1.37----;;
;;recursive cont-frac
(define (cont-frac n d k)
  (define (frac i)
    (if (= i k)
	(/ (n i) (d i))
	(/ (n i) (+ (d i) (frac (+ i 1))))))
  (frac 1))
(define (phi k)
  (/ 1 (cont-frac (lambda (i) 1.0) (lambda (i) 1.0) k)))

;;iterative cont-frac
(define (cont-frac n d k)
  (define (frac i res)
    (if (= i 0)
	res
	(frac (- i 1) (/ (n i) (+ (d i) res)))))
  (frac k 0))

;;----Ex 1.38----;;
;;natural logarithms using Euler's method
(define (get-e k)
  (+ 2 (cont-frac (lambda (i) 1.0)
		  (lambda (i) (let ((r (remainder i 3)))
				(if (< r 2)
				    1
				    (* (/ (+ i 1) 3) 2))))
		  k)))

;;----Ex 1.39----;;
;;minus cont-frac
(define (cont-frac-minus n d k)
  (define (frac i res)
    (if (= i 0)
	res
	(frac (- i 1) (/ (n i) (- (d i) res)))))
  (frac k 0))
;;tan x by using Lambert's formula
(define (tan-cf x k)
  (cont-frac-minus (lambda (i)
	       (if (= i 1) x (square x)))
	     (lambda (i) (- (* i 2) 1))
	     k))

;;----Ex 1.40----;;
;;From book
(define (deriv g dx)
  (lambda (x)
    (/ (- (g (+ x dx)) (g x))
       dx)))
(define (newton-transform g dx)
  (lambda (x)
    (- x (/ (g x) ((deriv g dx) x)))))
(define (newtons-method g guess tolerance)
  (fixed-point (newton-transform g 0.00001) guess tolerance))
;; general cubic
(define (cubic a b c)
  (lambda (x) (+ (cube x) (* a (square x)) (* b x) c)))

;;----Ex 1.41----;;
;;apply g twice
(define (double g)
  (lambda (x) (g (g x))))

;;----Ex 1.42----;;
;;f(g(x))
(define (compose f g)
  (lambda (x) (f (g x))))

;;----Ex 1.43----;;
(define (repeated g n)
  (if (= n 1)
      g
      (double (repeated g (- n 1)))))

;;----Ex 1.44----;;
;;smooth procedure
(define (smooth g dx)
  (lambda (x) (/ (+ (g (- x dx)) (g x) (g (+ x dx))) 3)))

(define (n-fold-smooth g n dx)
  (define (smooth-dx g) (smooth g dx))
  ((repeated smooth-dx n) g))

;;----Ex 1.45----;;
(define (average-damp f)
  (lambda (x) (average x (f x))))

(define (nth-root x exp ndamp tolerance)
  (fixed-point ((repeated average-damp ndamp) (lambda (y) (/ x (fast-expt y (- exp 1))))) 2.0 tolerance))
;;The n-th root need log2(n) times average-damp

;;----Ex 1.55----;;
;;iterative-improve pattern
(define (iterative-improve good? improve)
  (lambda (first-guess)
    (define (try guess)
      (let ((next (improve guess)))
	(if (good? guess next)
	    next
	    (try next))))
    (try first-guess)))
;;fixed-point using iterative-improve
(define (fixed-point f first-guess tolerance)
  ((iterative-improve (lambda (a b) (< (abs (- a b)) tolerance)) f) first-guess))
;;sqrt using iterative-improve
(define (sqrt-iter x tolerance)
  ((iterative-improve (lambda (a guess) (< (abs (- (square guess) x)) tolerance))
		      (lambda (guess) ((average-damp (lambda (y) (/ x y))) guess)))
   0.1))
   
;;----Ex 2.1----;;
(define (make-rat n d)
  (let ((a (abs n))
	(b (abs d))
	(sign (if (or (and (< n 0) (< d 0)) (and (> n 0) (> d 0)))
		  false
		  true))
	(g (gcd n d)))
    (if sign
	(cons (- (/ a g)) (/ b g))
	(cons (/ a g) (/ b g)))))

;;----Ex 2.2----;;
;;constructor & selector of segment
(define (make-segment a b)
  (cons a b))
(define (start-segment a)
  (car a))
(define (end-segment a)
  (cdr a))
;;constructor & selector of point
(define (make-point a b)
  (cons a b))
(define (x-point a)
  (car a))
(define (y-point a)
  (cdr a))
;;----------------------------------
;;application of segment
(define (midpoint-segment a)
  (let ((start (start-segment a))
	(end (end-segment a)))
    (make-point (average (x-point start) (x-point end))
	  (average (y-point start) (y-point end)))))
(define (print-point p)
  (newline)
  (display "(")
  (display (x-point p))
  (display ",")
  (display (y-point p))
  (display ")"))

;;----Ex 2.3----;;
;;constructor & selector of vector
(define (make-vector a b)
  (cons a b))
(define (x-vector a)
  (car a))
(define (y-vector a)
  (cdr a))
(define (vector-segment a)
  (let ((end (end-segment a))
	(start (start-segment a)))
    (make-vector (- (x-point end) (x-point start))
	  (- (y-point end) (y-point start)))))
;;constructor & selector of rectangles
(define (make-rectangle a b c)
  (let ((vec1 (vector-segment (make-segment a b)))
	(vec2 (vector-segment (make-segment a c))))
    (if (= (+ (* (x-vector vec1) (x-vector vec2))
	      (* (y-vector vec1) (y-vector vec2)))
	   0)
	(cons (make-segment a b) c))))
(define (first-edge-rectangle rect)
  (car rect))
(define (second-edge-rectangle rect)
  (make-segment (start-segment (car rect)) (cdr rect)))
;;--------------------------	   
;;properties of rectangles
(define (area-rectangle rect)
  (let ((vec1 (vector-segment (first-edge-rectangle rect)))
	(vec2 (vector-segment (second-edge-rectangle rect))))
    (abs (- (* (x-vector vec1) (y-vector vec2))
	    (* (y-vector vec1) (x-vector vec2))))))
(define (perimeter-rectangle rect)
  (let ((vec1 (vector-segment (first-edge-rectangle rect)))
	(vec2 (vector-segment (second-edge-rectangle rect))))
    (let ((length1 (sqrt (+ (square (x-vector vec1)) (square (y-vector vec1)))))
	  (length2 (sqrt (+ (square (x-vector vec2)) (square (y-vector vec2))))))
      (* 2 (+ length1 length2)))))

;;----Ex 2.4----;;
(define (cdr z)
  (z (lambda (p q) q)))

;;----Ex 2.5----;;
(define (cons-e a b)
  (* (fast-expt 2 a) (fast-expt 3 b)))

(define (car-e x)
  (define (iter a x)
    (if (= (remainder x 2) 0)
	(iter (+ a 1) (/ x 2))
	a))
  (iter 0 x))

(define (cdr-e x)
  (define (iter a x)
    (if (= (remainder x 3) 0)
	(iter (+ a 1) (/ x 3))
	a))
  (iter 0 x))

;;----Ex 2.6----;;
;;from book
(define zero (lambda (f) (lambda (x) x)))

(define (add-1 n)
  (lambda (f) (lambda (x) (f ((n f) x)))))

;; (add-1 zero)
;(lambda (f) (lambda (x) (f (((lambda(ff) (lambda(x) x)) f) x))))
;(lambda (f) (lambda (x) (f ((lambda(x) x) x))))
;(lambda (f) (lambda (x) (f x)))

;; (add-1 (add-1 zero))
;(lambda (f) (lambda (x) (f (((lambda(ff) (lambda(x) (ff x))) f) x))))
;(lambda (f) (lambda (x) (f ((lambda(x) (f x)) x))))
;(lambda (f) (lambda (x) (f (f x))))

(define one
  (lambda (f)
    (lambda (x) (f x))))
(define two
  (lambda (f)
    (lambda (x) (f (f x)))))
(define (plus a b)
  (lambda (f)
    (lambda (x) (((a f) ((b f) x))))))

;; (plus one two)
;(lambda(f) (lambda (x) (((lambda(x) (f x)) ((lambda(x) (f (f x))) x)))))
;(lambda(f) (lambda (x) ((lambda(x) (f x)) (f (f x)))))
;(lambda(f) (lambda (x) (f (f (f x)))))

;;----Ex 2.7----;;
(define (make-interval a b)
  (cons a b))

(define (upper-bound x)
  (cdr x))

(define (lower-bound x)
  (car x))

;;----Ex 2.8----;;
(define (sub-interval a b)
  (let ((p1 (- (lower-bound a) (upper-bound b)))
	(p2 (- (upper-bound a) (lower-bound b))))
    (cond ((and (< p1 0) (<= p2 0)) (make-interval (- p2) (- p1)))
	  ((and (>= p1 0) (> p2 0)) (make-interval p1 p2))
	  ((and (< p1 0) (> p2 0)) (make-interval 0 (max (- p1) p2)))
	  (else (make-interval 0 (max p1 (- p2)))))))

;;----Ex 2.9----;;
(define (div-interval x y)
  (let ((u (upper-bound y))
	(l (lower-bound y)))
    (cond ((= u 0) (display "Error: Divided by zero (upper-bound)"))
	  ((= l 0) (display "Error: Divided by zero (lower-bound)"))
	  (else (mul-interval x 
			      (make-interval (/ 1.0 u)
					     (/ 1.0 l)))))))

;;----Ex 2.10----;;
(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))

;;----Ex 2.12----;;
(define (make-center-percent c p)
  (let ((w (/ (* c p) 2)))
    (make-interval (- c w) (+ c w))))

(define (center i)
  (/ (+ (lower-bound i) (upper-bound i)) 2))

(define (percent i)
  (/ (- (upper-bound i) (lower-bound i)) (center i)))

;;----Ex 2.13----;;
;;p(a*b)=(a*b*p(b)+b*a*p(a))/(a*b)=p(a)+p(b)
;;a(1+-pa)*b(1+-pb)=a*b(1+-pa*pb+-pa+-pb)
;;approx. pa+pb

;;----Ex 2.14----;;
(define (add-interval x y)
  (make-interval (+ (lower-bound x) (lower-bound y))
                 (+ (upper-bound x) (upper-bound y))))
;; parallel resistors
(define (par1 r1 r2)
  (div-interval (mul-interval r1 r2)
                (add-interval r1 r2)))

(define (par2 r1 r2)
  (let ((one (make-interval 1 1))) 
    (div-interval one
                  (add-interval (div-interval one r1)
                                (div-interval one r2)))))

;;p(a/b)=((1/b)*a*p(a)+(a/b*b)*b*p(b))/(a/b)=p(a)+p(b)

;;the new center value calculated by mul-interval and div-interval is not same as directly mul. and div. of center values 

;;----Ex 2.16----;;
(define (make-interval c p)
  (cons c p))

(define (center x)
  (car x))

(define (percent x)
  (cdr x))

(define (par2 r1 r2)
  (let ((one (make-interval 1 0))) 
    (div-interval one
                  (add-interval (div-interval one r1)
                                (div-interval one r2)))))

(define (add-interval x y)
  (let ((cx (center x))
	(px (percent x))
	(cy (center y))
	(py (percent y)))
    (make-interval (+ cx cy) (/ (+ (* px cx) (* py cy)) (+ cx cy)))))

(define (mul-interval x y)
  (let ((cx (center x))
	(px (percent x))
	(cy (center y))
	(py (percent y)))
    (make-interval (* cx cy) (+ px py))))

(define (div-interval x y)
  (let ((cx (center x))
	(px (percent x))
	(cy (center y))
	(py (percent y)))
    (make-interval (/ cx cy) (+ px py))))

(define (parallel-interval x y)
  (let ((cx (center x))
	(px (percent x))
	(cy (center y))
	(py (percent y)))
    (make-interval (/ 1 (+ (/ 1 cx) (/ 1 cy))) (/ (+ (* py cx) (* px cy)) (+ cx cy)))))

;;The test of parallel-interval show that the par2 give the consistent value. Ex 2.15 give the correct answer, the repeated uncertainty will enlarge the error.

;;----Ex 2.17----;;
(define (last-pair x)
  (define (iter a x)
    (if (null? x)
	a
	(iter (car x) (cdr x))))
  (iter () x))

;;----Ex 2.18----;;
(define (reverse x)
  (define (iter a x)
    (if (null? x)
	a
	(iter (cons (car x) a) (cdr x))))
  (iter () x))

;;----Ex 2.19----;;
;;from book
(define us-coins (list 50 25 10 5 1))

(define uk-coins (list 100 50 20 10 5 2 1 0.5))

(define (cc amount coin-values)
  (cond ((= amount 0) 1)
        ((or (< amount 0) (no-more? coin-values)) 0)
        (else
         (+ (cc amount
                (except-first-denomination coin-values))
            (cc (- amount
                   (first-denomination coin-values))
                coin-values)))))

(define (first-denomination coin-values)
  (car coin-values))
(define (except-first-denomination coin-values)
  (cdr coin-values))
(define (no-more? coin-values)
  (if (null? coin-values)
      true
      false))

;;----Ex 2.20----;;
(define (same-parity . x)
  (define (rec l)
    (if (or (null? (cdr l)) (null? (cdr (cdr l))))
	(cons (car l) ())
	(cons (car l) (rec (cdr (cdr l))))))
  (rec x))

;;----Ex 2.21----;;
(define (square-list items)
  (if (null? items)
      ()
      (cons (square (car items)) (square-list (cdr items)))))
(define (square-list items)
  (map square items))

;;----Ex 2.23----;;
(define (for-each-my f items)
  (if (null? items)
      true
      ((lambda ()
	(f (car items))
	(for-each-my f (cdr items))))))

;;----Ex 2.27----;;
(define (deep-reverse lst)
  (define (iter a x)
    (cond ((null? x) a)
	  ((pair? (car x)) (iter (cons (iter () (car x)) a) (cdr x)))
	  (else (iter (cons (car x) a) (cdr x)))))
  (iter () lst))

;;----Ex 2.28----;;
(define (append list1 list2)
  (if (null? list1)
      list2
      (cons (car list1) (append (cdr list1) list2))))

;;----Ex 2.29----;;
;;recursive + append method
(define (fringe tr)
  (cond ((null? tr) ())
	((pair? (car tr)) (append (fringe (car tr)) (fringe (cdr tr))))
	(else (cons (car tr) (fringe (cdr tr))))))
;;iterative + reverse method
(define (fringe tr)
  (define (iter a x)
    (cond ((null? x) a)
	  ((pair? (car x)) (iter (iter a (car x)) (cdr x)))
	  (else (iter (cons (car x) a) (cdr x)))))
  (reverse (iter () tr)))


;;----Ex 2.30----;;
;;from book
(define (make-mobile left right)
  (list left right))

(define (make-branch length structure)
  (list length structure))
;;a
(define (left-branch x)
  (car x))
(define (right-branch x)
  (car (cdr x)))
(define (branch-length x)
  (car x))
(define (branch-structure x)
  (car (cdr x)))
;;b
(define (total-weight x)
  (define (check-mobile m)
    (+ (check-branch (left-branch m))
       (check-branch (right-branch m))))
  (define (check-branch b)
    (if (pair? (branch-structure b))
	(check-mobile (branch-structure b))
	(branch-structure b)))
  (check-mobile x))
;;c
(define (balance-test x)
  (define (get-torque b)
    (if (pair? (branch-structure b))
	(cons (branch-length b) (test-mobile (branch-structure b)))
	(cons (branch-length b) (branch-structure b))))
  (define (test-mobile m)
    (let ((lp (get-torque (left-branch m)))
	  (rp (get-torque (right-branch m))))
      (let ((lw (cdr lp))
	    (rw (cdr rp)))
	(if (or (= lw 0) (= rw 0) (not (= (* (car lp) lw) (* (car rp) rw))))
	    0
	    (+ rw lw)))))
  (if (= (test-mobile x) 0)
      false
      true))
;;d
;;only change branch-structure and right-branch is enough

;;----Ex 2.30----;;
(define (square-tree tr)
  (cond ((null? tr) ())
	((pair? tr) (cons (square-tree (car tr)) (square-tree (cdr tr))))
	(else (square tr))))
(define (square-tree tr)
  (map (lambda(sub-tr)
	 (if (pair? sub-tr)
	     (square-tree sub-tr)
	     (square sub-tr)))
       tr))

;;----Ex 2.31----;;
;;high order procedure
(define (tree-map f tr)
  (map (lambda(sub-tr)
	 (if (pair? sub-tr)
	     (tree-map f sub-tr)
	     (f sub-tr)))
       tr))
;;new square-tree
(define (square-tree tr)
  (tree-map square tr))

;;----Ex 2.32----;;
;;The method: subsets of list (first, others) can be divided to two parts: sets with first memberand others and sets without first members and others. This process can be recursively executed until reach end of list to get all subsets.
(define (subsets s)
  (if (null? s)
      (list ())
      (let ((rest (subsets (cdr s))))
        (append rest (map (lambda(x) (append (list (car s)) x)) rest))))))

;;----Ex 2.33----;;
;;from book
(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))
;;basic
(define (map-my p sequence)
  (accumulate (lambda (x y) (cons (p x) y)) () sequence))

(define (append-my seq1 seq2)
  (accumulate cons seq2 seq1))

(define (length-my sequence)
  (accumulate (lambda(x y) (+ 1 y)) 0 sequence))

;;----Ex 2.34----;;
(define (horner-eval x coefficient-sequence)
  (accumulate (lambda (this-coeff higher-terms) (+ this-coeff (* x higher-terms)))
              0
              coefficient-sequence))

;;----Ex 2.35----;;
(define (count-leaves t)
  (accumulate (lambda(x y) (+ x y)) 0
	      (map (lambda (x) (if (pair? x)
				   (count-leaves x)
				   1))
		   t)))

;;----Ex 2.36----;;
(define (accumulate-n op init seqs)
  (if (null? (car seqs))
      ()
      (cons (accumulate op init (map car seqs))
            (accumulate-n op init (map cdr seqs)))))

;;----Ex 2.37----;;
;;from book
(define (dot-product v w)
  (accumulate + 0 (map * v w)))
;;
(define (matrix-*-vector m v)
  (map (lambda (x) (dot-product x v)) m))
(define (transpose mat)
  (accumulate-n cons () mat))
(define (matrix-*-matrix m n)
  (let ((cols (transpose n)))
    (map (lambda(x) (matrix-*-vector cols x)) m)))

;;----Ex 2.38----;;
(define (fold-left op initial sequence)
  (define (iter result rest)
    (if (null? rest)
        result
        (iter (op result (car rest))
              (cdr rest))))
  (iter initial sequence))
(define fold-right accumulate)
;;if the two arguments of op exchange positions, the result is same, then fold-left and fold-right give same result

;;----Ex 2.39----;;
(define (reverse sequence)
  (fold-right (lambda (x y) (append y (list x))) () sequence))
(define (reverse sequence)
  (fold-left (lambda (x y) (cons y x)) () sequence))

;;----Ex 2.40----;;
;;from book
(define (flatmap proc seq)
  (accumulate append () (map proc seq)))
(define (enumerate-interval low high)
  (if (> low high)
      ()
      (cons low (enumerate-interval (+ low 1) high))))
(define (prime-sum? pair)
  (prime? (+ (car pair) (cadr pair))))
(define (make-pair-sum pair)
  (list (car pair) (cadr pair) (+ (car pair) (cadr pair))))
;;
(define (unique-pairs n)
  (flatmap
   (lambda (i)
     (map (lambda (j) (list i j))
	  (enumerate-interval 1 (- i 1))))
   (enumerate-interval 1 (- n 1))))

(define (prime-sum-pairs n)
  (map make-pair-sum
       (filter prime-sum? (unique-pairs n))))

;;----Ex 2.41----;;
(define (triple-pairs n)
  (flatmap
   (lambda (i)
     (map (lambda (j) (append (list i) j))
	  (unique-pairs (- i 1))))
   (enumerate-interval 1 n)))

(define (equal-s-sum pair s)
  (= s (+ (car pair) (cadr pair) (caddr pair))))

(define (equal-s-sum-triple n s)
  (filter (lambda(x) (equal-s-sum x s)) (triple-pairs n)))

;;----Ex 2.42----;;
(define (adjoin-position new-row k rest-of-queens)
  (cons (cons new-row k) rest-of-queens))
(define (safe? k positions)
  (define (ischecked p1 p2)
    (let ((dif (- (cdr p2) k)))
      (or (= (car p1) (car p2))
	  (= (+ (car p1) dif) (car p2))
	  (= (- (car p1) dif) (car p2)))))
  (define (check p c)
    (cond ((null? c) true)
	  ((ischecked p (car c)) false)
	  (else (check p (cdr c)))))
  (let ((p (car positions)))
    (check p (cdr positions))))
(define (queens board-size)
  (define (queen-cols k)
    (if (= k 0)
	(list ())
        (filter
         (lambda (positions) (safe? k positions))
         (flatmap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (enumerate-interval 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))

;;----Ex 2.43----;;
;;the 2.43 queen-cols are called n*n times and 2.42 only called n times.

;;----Ex 2.54----;;
(define (equal?-my a b)
  (cond ((and (pair? a) (pair? b)) (and (eq? (car a) (car b)) (equal?-my (cdr a) (cdr b))))
	((and (not (pair? a)) (not (pair? b))) (eq? a b))
	(else false)))

;;----Ex 2.56----;;
;;from book
(define (variable? x) (symbol? x))

(define (same-variable? v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2)))

(define (sum? x)
  (and (pair? x) (eq? (car x) '+)))

(define (addend s) (cadr s))

(define (augend s) (caddr s))

(define (product? x)
  (and (pair? x) (eq? (car x) '*)))

(define (multiplier p) (cadr p))

(define (multiplicand p) (caddr p))

(define (make-sum a1 a2)
  (cond ((=number? a1 0) a2)
        ((=number? a2 0) a1)
        ((and (number? a1) (number? a2)) (+ a1 a2))
        (else (list '+ a1 a2))))

(define (=number? exp num)
  (and (number? exp) (= exp num)))

(define (make-product m1 m2)
  (cond ((or (=number? m1 0) (=number? m2 0)) 0)
        ((=number? m1 1) m2)
        ((=number? m2 1) m1)
        ((and (number? m1) (number? m2)) (* m1 m2))
        (else (list '* m1 m2))))

;;for exponentiation
(define (exponentiation? x)
  (and (pair? x) (eq? (car x) '**)))

(define (base s) (cadr s))

(define (exponent s) (caddr s))

(define (make-exponentiation a1 a2)
  (cond ((=number? a1 0) 0)
	((=number? a1 1) 1)
	((=number? a2 0) 1)
	((=number? a2 1) a1)
	((and (number? a1) (number? a2)) (expt a1 a2))
	(else (list '** a1 a2))))

(define (deriv exp var)
  (cond ((number? exp) 0)
        ((variable? exp) (if (same-variable? exp var) 1 0))
        ((sum? exp)
         (make-sum (deriv (addend exp) var)
                   (deriv (augend exp) var)))
        ((product? exp)
         (make-sum
           (make-product (multiplier exp)
                         (deriv (multiplicand exp) var))
           (make-product (deriv (multiplier exp) var)
                         (multiplicand exp))))
	((exponentiation? exp)
	 (make-product
	  (make-product 
	   (exponent exp)
	   (make-exponentiation (base exp) (make-sum (exponent exp) -1)))
	  (deriv (base exp) var)))
        (else (error "unknown expression type -- DERIV" exp))))

;;----Ex 2.57----;;
(define (augend s)
  (if (null? (cdddr s))
      (caddr s)
      (cons '+ (cddr s))))

(define (multiplicand p)
  (if (null? (cdddr p))
      (caddr p)
      (cons '* (cddr p))))

(define (make-sum a1 a2)
  (cond ((=number? a1 0) a2)
        ((=number? a2 0) a1)
        ((and (number? a1) (number? a2)) (+ a1 a2))
	((and (not (sum? a1)) (number? a2) (list '+ a2 a1)))
	((sum? a1)
	 (cond ((number? a2)
		(if (number? (addend a1))
		    (append (list '+ (+ (addend a1) a2)) (cddr a1))
		    (append (list '+ a2) (cdr a1))))
	       ((sum? a2)
		(cond ((and (number? (addend a1)) (number? (addend a2)))
		       (append (append (list '+ (+ (addend a1) (addend a2)))
			       (cddr a1)) (cddr a2)))
		      ((number? (addend a2))
		       (append (append (list '+) (cdr a2)) (cdr a1)))
		      (else (append (append (list '+) (cdr a1)) (cdr a2)))))
	       (else (append a1 (list a2)))))
	((sum? a2)
	 (if (number? a1)
	     (if (number? (addend a2))
		 (append (list '+ (+ (addend a2) a1)) (cddr a2))
		 (append (list '+ a1) (cdr a2)))
	     (append a2 (list a1))))
        (else (list '+ a1 a2))))


(define (make-product m1 m2)
  (cond ((or (=number? m1 0) (=number? m2 0)) 0)
        ((=number? m1 1) m2)
        ((=number? m2 1) m1)
        ((and (number? m1) (number? m2)) (* m1 m2))
	((and (not (product? m1)) (number? m2) (list '* m2 m1)))
	((product? m1)
	 (cond ((number? m2)
		(if (number? (multiplier m1))
		    (append (list '* (* (multiplier m1) m2)) (cddr m1))
		    (append (list '* m2) (cdr m1))))
	       ((product? m2)
		(cond ((and (number? (multiplier m1)) (number? (multiplier m2)))
		       (append (append (list '* (* (multiplier m1) (multiplier m2)))
			       (cddr m1)) (cddr m2)))
		      ((number? (multiplier m2))
		       (append (append (list '*) (cdr m2)) (cdr m1)))
		      (else (append (append (list '*) (cdr m1)) (cdr m2)))))
	       (else (append m1 (list m2)))))
	((product? m2)
	 (if (number? m1)
	     (if (number? (multiplier m2))
		 (append (list '* (* (multiplier m2) m1)) (cddr m2))
		 (append (list '* m1) (cdr m2)))
	     (append m2 (list m1))))
        (else (list '* m1 m2))))

;;----Ex 2.58----;;
;;a
(define (sum? x)
  (and (pair? x) (eq? (cadr x) '+)))

(define (addend s) (car s))

(define (augend s) (caddr s))

(define (product? x)
  (and (pair? x) (eq? (cadr x) '*)))

(define (multiplier p) (car p))

(define (multiplicand p) (caddr p))

(define (make-sum a1 a2)
  (cond ((=number? a1 0) a2)
        ((=number? a2 0) a1)
        ((and (number? a1) (number? a2)) (+ a1 a2))
        (else (list a1 '+ a2))))

(define (make-product m1 m2)
  (cond ((or (=number? m1 0) (=number? m2 0)) 0)
        ((=number? m1 1) m2)
        ((=number? m2 1) m1)
        ((and (number? m1) (number? m2)) (* m1 m2))
        (else (list m1 '* m2))))

(define (exponentiation? x)
  (and (pair? x) (eq? (cadr x) '**)))

(define (base s) (car s))

(define (exponent s) (caddr s))

(define (make-exponentiation a1 a2)
  (cond ((=number? a1 0) 0)
	((=number? a1 1) 1)
	((=number? a2 0) 1)
	((=number? a2 1) a1)
	((and (number? a1) (number? a2)) (expt a1 a2))
	(else (list a1 '** a2))))

;;b
(define (member? item x)
  (cond ((null? x) false)
        ((eq? item (car x)) true)
        (else (member? item (cdr x)))))

(define (sum? x)
  (and (pair? x) (member? '+ x)))

(define (product? x)
  (and (pair? x) (not (member? '+ x)) (eq? (cadr x) '*)))

(define (addend s)
  (if (eq? (cadr s) '+)
      (car s)
      (let ((x (addend (cddr s))))
	(if (pair? x)
	    (append (list (car s) (cadr s)) x)
	    (list (car s) (cadr s) x)))))

(define (augend s)
  (if (eq? (cadr s) '+)
      (if (null? (cdddr s)) 
	  (caddr s)
	  (cddr s))
      (augend (cddr s))))

(define (multiplicand p)
  (if (null? (cdddr p))
      (caddr p)
      (cddr p)))

(define (make-sum a1 a2)
  (cond ((=number? a1 0) a2)
        ((=number? a2 0) a1)
        ((and (number? a1) (number? a2)) (+ a1 a2))
	((and (not (sum? a1)) (number? a2) (list a2 '+ a1)))
	((sum? a1)
	 (cond ((number? a2)
		(if (number? (addend a1))
		    (make-sum (+ (addend a1) a2) (augend a1))
		    (append (list a2 '+) a1)))
	       ((sum? a2)
		(cond ((and (number? (addend a1)) (number? (addend a2)))
		       (make-sum (+ (addend a1) (addend a2)) (make-sum
			       (augend a1) (augend a2))))
		      ((number? (addend a2))
		       (append a2 (list '+) a1))
		      (else (append a1 (list '+) a2))))
	       (else (append a1 (list '+ a2)))))
	((sum? a2)
	 (if (number? a1)
	     (if (number? (addend a2))
		 (make-sum (+ (addend a2) a1) (augend a2))
		 (append (list a1 '+) a2))
	     (append a2 (list '+ a1))))
        (else (list a1 '+ a2))))


(define (make-product m1 m2)
  (cond ((or (=number? m1 0) (=number? m2 0)) 0)
        ((=number? m1 1) m2)
        ((=number? m2 1) m1)
        ((and (number? m1) (number? m2)) (* m1 m2))
	((and (not (product? m1)) (number? m2) (list m2 '* m1)))
	((product? m1)
	 (cond ((number? m2)
		(if (number? (multiplier m1))
		    (append (list (* (multiplier m1) m2) '*) (cddr m1))
		    (append (list  m2 '*) m1)))
	       ((product? m2)
		(cond ((and (number? (multiplier m1)) (number? (multiplier m2)))
		       (append (list (* (multiplier m1) (multiplier m2)) '*)
			       (cddr m1) (list '*) (cddr m2)))
		      ((number? (multiplier m2))
		       (append m2 (list '*) m1))
		      (else (append m1 (list '*) m2))))
	       (else (append m1 (list '* m2)))))
	((product? m2)
	 (if (number? m1)
	     (if (number? (multiplier m2))
		 (append (list (* (multiplier m2) m1) '*) (cddr m2))
		 (append (list m1 '*) m2))
	     (append m2 (list '* m1))))
        (else (list m1 '* m2))))

;;----Ex 2.59----;;
;;from book
(define (element-of-set? x set)
  (cond ((null? set) false)
        ((equal? x (car set)) true)
        (else (element-of-set? x (cdr set)))))

(define (adjoin-set x set)
  (if (element-of-set? x set)
      set
      (cons x set)))

(define (intersection-set set1 set2)
  (cond ((or (null? set1) (null? set2)) '())
        ((element-of-set? (car set1) set2)
         (cons (car set1)
               (intersection-set (cdr set1) set2)))
        (else (intersection-set (cdr set1) set2))))
;;
(define (union-set set1 set2)
  (cond ((null? set1) set2)
	((null? set2) set1)
	((element-of-set? (car set1) set2) (union-set (cdr set1) set2))
	(else (cons (car set1) (union-set (cdr set1) set2)))))

;;----Ex 2.60----;;
;;for duplicate, element-of-set? intersection-set are same
(define (adjoin-set x set)
  (if (null? set)
      (list x)
      (cons x set)))

(define (union-set set1 set2)
  (cond ((null? set1) set2)
	((null? set2) set1)
	(else (append set1 set2))))

;;----Ex 2.61----;;
(define (adjoin-set x set)
  (if (null? set)
      (list x)
      (let ((cpy (car set)))
	(cond ((< x cpy) (cons x set))
	      ((= x cpy) set)
	      (else (cons cpy (adjoin-set x (cdr set))))))))

;;----Ex 2.62----;;
(define (union-set set1 set2)
  (cond ((null? set1) set2)
	((null? set2) set1)
	(else (let ((a1 (car set1))
		    (a2 (car set2)))
		(cond ((= a1 a2) (cons a1 (union-set (cdr set1) (cdr set2))))
		      ((< a1 a2) (cons a1 (union-set (cdr set1) set2)))
		      (else (cons a2 (union-set set1 (cdr set2)))))))))

;;----Ex 2.63----;;
(define (entry tree) (car tree))

(define (left-branch tree) (cadr tree))

(define (right-branch tree) (caddr tree))

(define (make-tree entry left right)
  (list entry left right))

(define (tree->list-1 tree)
  (if (null? tree)
      '()
      (append (tree->list-1 (left-branch tree))
              (cons (entry tree)
                    (tree->list-1 (right-branch tree))))))

(define (tree->list-2 tree)
  (define (copy-to-list tree result-list)
    (if (null? tree)
        result-list
        (copy-to-list (left-branch tree)
                      (cons (entry tree)
                            (copy-to-list (right-branch tree)
                                          result-list)))))
  (copy-to-list tree '()))
;; Both give correct results, the first one is more slowly since it always append the left brance to right brance at the same level, which will be very cost at top level.

;;----Ex 2.64----;;
(define (list->tree elements)
  (car (partial-tree elements (length elements))))

(define (partial-tree elts n)
  (if (= n 0)
;;if size is 0, just return empty tree and input set as remaining set.
      (cons '() elts)
;;divide set to two almost equal parts, get size for the left part      
      (let ((left-size (quotient (- n 1) 2)))
;;recursize to get left tree and remaining set	
        (let ((left-result (partial-tree elts left-size)))
          (let ((left-tree (car left-result))
                (non-left-elts (cdr left-result))
;;get size of remaining set - 1
                (right-size (- n (+ left-size 1))))
;;the first element of remaining set is the entry of subtree	    
            (let ((this-entry (car non-left-elts))
;;recursize to get right tree and remaining set		  
                  (right-result (partial-tree (cdr non-left-elts)
                                              right-size)))
              (let ((right-tree (car right-result))
                    (remaining-elts (cdr right-result)))
;;make subtree based on entry and left-tree and right-tree obtained above and also return remaining set
                (cons (make-tree this-entry left-tree right-tree)
                      remaining-elts))))))))

;;----Ex 2.65----;;

;; (define (union-set set1 set2)
;;   (cond ((null? set1) set2)
;; 	((null? set2) set1)
;; 	(else (let ((e2 (entry set2))
;; 		    (e1 (entry set1)))
;; 		(cond ((= e1 e2)
;; 		       (make-tree e1
;; 			    (union-set (left-branch set1) (left-branch set2))
;; 			    (union-set (right-branch set1) (right-branch set2))))
;; 		      ((< e1 e2)
;; 		       (if (null? (right-branch set1))
;; 			   (make-tree e2
;; 				      (union-set set1 (left-branch set2))
;; 				      (right-branch set2))
;; 			   (let ((r1 (entry (right-branch set1))))
;; 			     (cond ((= r1 e2)
;; 				    (make-tree
;; 				     e2
;; 				     (union-set  (make-tree e1
;; 							    (left-branch set1)
;; 							    (left-branch (right-branch set1)))
;; 						 (left-branch set2))
;; 				     (union-set (right-branch (right-branch set1))
;; 						(right-branch set2))))
;; 				   ((< r1 e2)
;; 				    (union-set (make-tree
;; 						 r1
;; 						 (make-tree
;; 						  e1
;; 						  (left-branch set1)
;; 						  (left-branch (right-branch set1)))
;; 						 (right-branch (right-branch set1)))
;; 					       set2))
;; 				   (else
;; 				    (make-tree
;; 				     e2
;; 				     (union-set (make-tree e1 (left-branch set1) '())
;; 						(left-branch set2))
;; 				     (union-set (right-branch set1) (right-branch set2))))))))
;; 		      (else (union-set set2 set1)))))))

;; (define (union-set set1 set2)
;;   (cond ((null? set1) (tree->list-2 set2))
;; 	((null? set2) (tree->list-2 set1))
;; 	((= (entry set1) (entry set2))
;; 	 (append (union-set (left-branch set1) (left-branch set2))
;; 		 (cons (entry set1) (union-set (right-branch set1) (right-branch set2)))))
;; 	((< (entry set1) (entry set2))
;; 	 (append (union-set set1 (left-branch set2))
;; 		 (tree->list-2 (right-branch set2))))
;; 	(else (append (union-set (left-branch set1) set2)
;; 		      (tree->list-2 (right-branch set1))))))

(define (union-set set1 set2)
  (define (list-union-set set1 set2)
    (cond ((null? set1) set2)
	  ((null? set2) set1)
	  (else (let ((a1 (car set1))
		      (a2 (car set2)))
		  (cond ((= a1 a2) (cons a1 (list-union-set (cdr set1) (cdr set2))))
			((< a1 a2) (cons a1 (list-union-set (cdr set1) set2)))
			(else (cons a2 (list-union-set set1 (cdr set2)))))))))
  (list->tree (list-union-set (tree->list-2 set1) (tree->list-2 set2))))

(define (intersection-set set1 set2)
  (define (list-intersection-set set1 set2)
    (if (or (null? set1) (null? set2))
	'()
	(let ((x1 (car set1)) (x2 (car set2)))
	  (cond ((= x1 x2)
		 (cons x1
		       (list-intersection-set (cdr set1)
					      (cdr set2))))
		((< x1 x2)
		 (list-intersection-set (cdr set1) set2))
		((< x2 x1)
		 (list-intersection-set set1 (cdr set2)))))))
  (list->tree (list-intersection-set (tree->list-2 set1) (tree->list-2 set2))))

;;----Ex 2.66----;;
(define (tree-lookup n binary-tree)
  (if (null? binary-tree)
      false
      (let ((e (entry binary-tree)))
	(cond ((= n e) binary-tree)
	      ((< n e) (tree-lookup n (left-branch binary-tree)))
	      (else (tree-lookup n (right-branch binary-tree)))))))

;;----Ex 2.67----;;
;;from book
;;representing

(define (make-leaf symbol weight)
  (list 'leaf symbol weight))

(define (leaf? object)
  (eq? (car object) 'leaf))

(define (symbol-leaf x) (cadr x))

(define (weight-leaf x) (caddr x))

(define (make-code-tree left right)
  (list left
        right
        (append (symbols left) (symbols right))
        (+ (weight left) (weight right))))

(define (left-branch tree) (car tree))

(define (right-branch tree) (cadr tree))

(define (symbols tree)
  (if (leaf? tree)
      (list (symbol-leaf tree))
      (caddr tree)))

(define (weight tree)
  (if (leaf? tree)
      (weight-leaf tree)
      (cadddr tree)))

;; decoding
(define (decode bits tree)
  (define (decode-1 bits current-branch)
    (if (null? bits)
        '()
        (let ((next-branch
               (choose-branch (car bits) current-branch)))
          (if (leaf? next-branch)
              (cons (symbol-leaf next-branch)
                    (decode-1 (cdr bits) tree))
              (decode-1 (cdr bits) next-branch)))))
  (decode-1 bits tree))

(define (choose-branch bit branch)
  (cond ((= bit 0) (left-branch branch))
        ((= bit 1) (right-branch branch))
        (else (error "bad bit -- CHOOSE-BRANCH" bit))))

;; sets

(define (adjoin-set x set)
  (cond ((null? set) (list x))
        ((< (weight x) (weight (car set))) (cons x set))
        (else (cons (car set)
                    (adjoin-set x (cdr set))))))

(define (make-leaf-set pairs)
  (if (null? pairs)
      '()
      (let ((pair (car pairs)))
        (adjoin-set (make-leaf (car pair)
                               (cadr pair))
                    (make-leaf-set (cdr pairs))))))

;;sample
 (define sample-tree
   (make-code-tree (make-leaf 'A 4)
                   (make-code-tree
                    (make-leaf 'B 2)
                    (make-code-tree (make-leaf 'D 1)
                                    (make-leaf 'C 1)))))

 (define sample-message '(0 1 1 0 0 1 0 1 0 1 1 1 0))

;;(decode sample-message sample-tree)

;;----Ex 2.68----;;
;;from book
(define (encode message tree)
  (if (null? message)
      '()
      (append (encode-symbol (car message) tree)
              (encode (cdr message) tree))))

;;encode method
(define (encode-symbol symbol tree)
  (cond ((null? tree) (error "No such symbol" symbol))
	((leaf? tree) '())
	((check-leaf symbol (left-branch tree)) (cons '0 (encode-symbol symbol (left-branch tree))))
	((check-leaf symbol (right-branch tree)) (cons '1 (encode-symbol symbol (right-branch tree))))
	(else (error "No such symbol" symbol))))
(define (check-leaf symbol tr)
  (if (leaf? tr)
      (equal? (symbol-leaf tr) symbol)
      (member? symbol (symbols tr))))

;;----Ex 2.69----;;
;; (define (make-frequent-set-pair symbol freq)
;;   (cons symbol freq))
;; (define (symbol-pair s)
;;   (car s))
;; (define (frequent-pair s)
;;   (cdr s))
;; (define (Make-leaf-set pairs)
;;   (sort pairs (lambda (x y) (< (frequent-pair x) (frequent-pair y)))))
(define (generate-huffman-tree pairs)
  (successive-merge (make-leaf-set pairs)))
(define (successive-merge leaves)
  (if (null? (cdr leaves))
      (car leaves)
      (successive-merge (adjoin-set (make-code-tree (car leaves) (cadr leaves)) (cddr leaves)))))

;;----Ex 2.70----;;
(define lyrics-code (generate-huffman-tree '((A 2) (NA 16) (BOOM 1) (SHA 3) (GET 2) (YIP 9) (JOB 2) (WAH 1))))
(define lyrics '((Get a job) (Sha na na na na na na na na) (Get a job) (Sha na na na na na na na na) (Wah yip yip yip yip yip yip yip yip yip) (Sha boom)))
(map (lambda (x) (encode x lyrics-code)) lyrics)

;;----Ex 2.71----;;
;; The sum of frequent from 1 to n-1 is (frequent of n) - 1, thus the tree is linearly, the bottom level is least frequent 1 and next least frequent 2, upper level increase as (symbol index +1)
;; The most frequent only need 1 bit, the least frequent need n - 1

;;----Ex 2.72----;;
;; Most frequent need n
;; Least frequent need
;; max: (n + (n - 1) + (n - 2) + ... + 1) = n(n+1)/2
;; min: (n + n/2 + n/4 + ... + 1) = 2n -1

;;----Ex 2.73----;;
;;a. Because the dispatch pattern need identify operator and operands, but number? and same-variable? need input that is not pair.

;;b. 
;;from book
(define (deriv exp var)
   (cond ((number? exp) 0)
         ((variable? exp) (if (same-variable? exp var) 1 0))
         (else ((get 'deriv (operator exp)) (operands exp)
                                            var))))
(define (operator exp) (car exp))
(define (operands exp) (cdr exp))
;;sum
(define (install-sum-package)
  (define (sum? x)
    (and (pair? x) (eq? (car x) '+)))
  (define (operands exp) (cdr exp))
  (define (=number? exp num)
    (and (number? exp) (= exp num)))
  (define (addend s) (cadr s))
  (define (augend s)
    (if (null? (cdddr s))
	(caddr s)
	(cons '+ (cddr s))))
  (define (make-sum a1 a2)
    (cond ((=number? a1 0) a2)
	  ((=number? a2 0) a1)
	  ((and (number? a1) (number? a2)) (+ a1 a2))
	  ((and (not (sum? a1)) (number? a2) (list '+ a2 a1)))
	  ((sum? a1)
	   (cond ((number? a2)
		  (if (number? (addend a1))
		      (make-sum (+ (addend a1) a2) (augend a1))
		      (make-sum a2 a1)))
		 ((sum? a2)
		  (cond ((and (number? (addend a1)) (number? (addend a2)))
			 (make-sum (make-sum (+ (addend a1) (addend a2))
					     (augend a1))
				   (augend a2)))
			((number? (addend a2))
			 (append (list '+) (operands a2) (operands a1)))
			(else (append (list '+) (operands a1) (operands a2)))))
		 (else (append a1 (list a2)))))
	  ((sum? a2)
	   (if (number? a1)
	       (if (number? (addend a2))
		   (make-sum (+ (addend a2) a1) (augend a2))
		   (append (list '+ a1) (operands a2)))
	       (append a2 (list a1))))
	  (else (list '+ a1 a2))))
  ;;interface
  (put 'deriv '+ (lambda(x y) (make-sum (deriv (car x) y)
					  (deriv (augend (cons '+ x)) y)))))

(define (install-product-package)
  (define (product? x)
    (and (pair? x) (eq? (car x) '*)))
  (define (multiplier p) (cadr p))
  (define (multiplicand p) (caddr p))
  (define (make-product m1 m2)
    (cond ((or (=number? m1 0) (=number? m2 0)) 0)
	  ((=number? m1 1) m2)
	  ((=number? m2 1) m1)
	  ((and (number? m1) (number? m2)) (* m1 m2))
	  ((and (not (product? m1)) (number? m2) (list '* m2 m1)))
	  ((product? m1)
	   (cond ((number? m2)
		  (if (number? (multiplier m1))
		      (append (list '* (* (multiplier m1) m2)) (cddr m1))
		      (append (list '* m2) (cdr m1))))
		 ((product? m2)
		  (cond ((and (number? (multiplier m1)) (number? (multiplier m2)))
			 (append (append (list '* (* (multiplier m1) (multiplier m2)))
					 (cddr m1)) (cddr m2)))
			((number? (multiplier m2))
			 (append (append (list '*) (cdr m2)) (cdr m1)))
			(else (append (append (list '*) (cdr m1)) (cdr m2)))))
		 (else (append m1 (list m2)))))
	  ((product? m2)
	   (if (number? m1)
	       (if (number? (multiplier m2))
		   (append (list '* (* (multiplier m2) m1)) (cddr m2))
		   (append (list '* m1) (cdr m2)))
	       (append m2 (list m1))))
	  (else (list '* m1 m2))))
  ;;interface (need make-sum)
  (put 'deriv '* (lambda(x y)
		   (let ((exp (cons '* x)))
		     (make-sum
		      (make-product (car x) (deriv (multiplicand exp) y))
		      (make-product (deriv (car x) y) (multiplicand exp)))))))

;;c
;;for exponentiation
(define (install-exponentiation-package)
  (define (exponentiation? x)
    (and (pair? x) (eq? (car x) '**)))
  (define (base s) (cadr s))
  (define (exponent s) (caddr s))
  (define (make-exponentiation a1 a2)
    (cond ((=number? a1 0) 0)
	  ((=number? a1 1) 1)
	  ((=number? a2 0) 1)
	  ((=number? a2 1) a1)
	  ((and (number? a1) (number? a2)) (expt a1 a2))
	  (else (list '** a1 a2))))
  ;;interface
  (put 'deriv '** (lambda(x y)
		    (make-product (make-product (cadr x)
						(make-exponentiation (car x)
								     (make-sum (cadr x) -1)))
				  (deriv (car x) var)))))

;;----Ex 2.74----;;
;;a
;;use get-record method from specified division
(define (get-record name division)
  ((get 'record (type-tags division)) name division))

;;b
(define (get-salary name record)
  ((get 'salary (type-tags record)) name record))

;;c
(define (find-employee-record name divisions)
  (map (lambda(x) (get-record name x)) divisions))

;;d
;; should install new method of get record and the specific entries of set for new division

;;----Ex 2.75----;;
(define (make-from-mag-ang x y)
  (define (dispatch op)
    (cond ((eq? op 'magnitude) x)
	  ((eq? op 'angle) y)
	  ((eq? op 'real-part) (* x (cos y)))
	  ((eq? op 'imag-part) (* x (sin y)))
	  (else
	   (error "Unknown op -- MAKE-FROM-MAG-ANG" op))))
  dispatch)

;;----Ex 2.76----;;
;; when new types and operators added,
;; explicit dispatch is the worst case, all codes using the operators need to be changed.
;; data-directed dispatch install new package, message passing need define new type procedure.
;;
;; Message passing is the best for adding new type
;; data-directed dispatch is the best for adding new operations

;;----Ex 2.78----;;
(define (attach-tag type-tag contents)
  (if (eq? type-tag 'scheme-number)
      contents
      (cons type-tag contents)))

((define (type-tag datum)
  (cond ((pair? datum) (car datum))
	((number? datum) 'scheme-number)
	(error "Bad tagged datum -- TYPE-TAG" datum))))

;;----Ex 2.79----;;
(define (install-zero-package)
  (put 'equ? '(complex complex) (lambda(x y) (and (eq? (real-part x) (real-part y) (eq? (imag-part x) (imag-part y))))))
  (put 'equ? '(rational rational) (lambda(x y) (eq? (/ (numer x) (denom x)) (/ (numer y) (denom y)))))
  (put 'equ? '(scheme-number scheme-number) (lambda(x y) (eq? x y))))

;;----Ex 2.80----;;
(define (install-zero-package)
  (put '=zero? '(complex) (lambda(x) (and (eq? (real-part x) 0) (eq? (imag-part x) 0))))
  (put '=zero? '(rational) (lambda(x) (and (eq? (numer x) 0) (not (eq? (denom x) 0)))))
  (put '=zero? '(scheme-number) (lambda(x) (eq? x 0))))

;;----Ex 2.81----;;
;;a: wrong, the apply-generic will go infinit iterative loop when the operator is not defined
;;b: apply-generic can do it correctly, it first transform two arguments to top level and then find there is no operator thus return error
;;c:

(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
          (apply proc (map contents args))
          (if (= (length args) 2)
              (let ((type1 (car type-tags))
                    (type2 (cadr type-tags))
                    (a1 (car args))
                    (a2 (cadr args)))
		(if (eq? type1 type2)
		    (error "No method for these types"
                                (list op type-tags))
		    (let ((t1->t2 (get-coercion type1 type2))
			  (t2->t1 (get-coercion type2 type1)))
		      (cond (t1->t2
			     (apply-generic op (t1->t2 a1) a2))
			    (t2->t1
			     (apply-generic op a1 (t2->t1 a2)))
			    (else
			     (error "No method for these types"
				    (list op type-tags)))))))
	      (error "No method for these types"
		     (list op type-tags)))))))

;;----Ex 2.83----;;
(define (install-raise-package)
  (put 'raise 'integer (lambda(x) (make-rational x 1)))
  (put 'raise 'rational (lambda(x) (make-real (/ (numer x) (denom x)))))
  (put 'raise 'real (lambda(x) (make-complex-from-real-imag x 0))))

;;----Ex 2.84----;;
(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
          (apply proc (map contents args))
          (if (= (length args) 2)
              (let ((type1 (car type-tags))
                    (type2 (cadr type-tags))
                    (a1 (car args))
                    (a2 (cadr args)))
		(cond ((eq? type1 type2) (error "No method for these types"
                                (list op type-tags)))
		      ((higher? type1 type2) (apply-generic op a1 ((get 'raise type2) a2)))
		      (else (apply-generic op ((get 'raise type1) a1) a2))))
	      (error "No method for these types"
		     (list op type-tags)))))))

(define (higher? x1 x2)
  (> (get 'order x1) (get 'order x2)))

(define (install-order-package)
  (put 'order 'integer (lambda(x) 0))
  (put 'order 'rational (lambda(x) 5))
  (put 'order 'real (lambda(x) 10))
  (put 'order 'complex (lambda(x) 15)))

;;----Ex 2.85----;;
(define (install-project-package)
  (put 'drop 'complex (lambda(x)
			(let ((im (imag-part x))
			      (re (real-part x)))
			  (if (eq? im 0)
			      (if (integer? re)
				  (make-integer re)
				  (make-real re))
			      x))))
  (put 'drop 'real (lambda(x)
		     (if (integer? x)
			 (make-integer x)
			 x)))
  (put 'drop 'rational (lambda(x)
			 (if (eq? (denom x) 1)
			     (make-integer x)
			     x))))

(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
          (let ((res (apply proc (map contents args))))
	    ((get 'drop (type-tag res)) res))
          (if (= (length args) 2)
              (let ((type1 (car type-tags))
                    (type2 (cadr type-tags))
                    (a1 (car args))
                    (a2 (cadr args)))
		(cond ((eq? type1 type2) (error "No method for these types"
                                (list op type-tags)))
		      ((higher? type1 type2) (apply-generic op a1 ((get 'raise type2) a2)))
		      (else (apply-generic op ((get 'raise type1) a1) a2))))
	      (error "No method for these types"
		     (list op type-tags)))))))

;;----Ex 2.86----;;
(define (install-rectangular-package)
  ;; internal procedures
  (define (real-part z) (car z))
  (define (imag-part z) (cdr z))
  (define (make-from-real-imag x y) (cons x y))
  (define (magnitude z)
    (apply-generic 'sqrt (apply-generic 'sub (apply-generic 'square (real-part z)))
             (apply-generic 'square (imag-part z))))))
  (define (angle z)
    (atan (contents (imag-part z)) (contents (real-part z))))
  (define (make-from-mag-ang r a)
    (cons (apply-generic 'mul r (apply-generic 'cos a))) (apply-generic 'mul r (apply-generic 'sin a)))

  ;; interface to the rest of the system
  (define (tag x) (attach-tag 'rectangular x))
  (put 'real-part '(rectangular) real-part)
  (put 'imag-part '(rectangular) imag-part)
  (put 'magnitude '(rectangular) magnitude)
  (put 'angle '(rectangular) angle)
  (put 'make-from-real-imag 'rectangular
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'rectangular
       (lambda (r a) (tag (make-from-mag-ang r a))))
  'done)

(define (install-polar-package)
  ;; internal procedures
  (define (magnitude z) (car z))
  (define (angle z) (cdr z))
  (define (make-from-mag-ang r a) (cons r a))
  (define (real-part z)
    (apply-generic 'mul (magnitude z) (apply-generic 'cos (angle z))))
  (define (imag-part z)
    (apply-generic 'mul (magnitude z) (apply-generic 'sin (angle z))))
  (define (make-from-real-imag x y) 
    (cons (apply-generic 'sqrt (apply-generic 'sub (apply-generic 'square x) (apply-generic 'squre y)))
          (apply-generic 'atan y x)))

  ;; interface to the rest of the system
  (define (tag x) (attach-tag 'polar x))
  (put 'real-part '(polar) real-part)
  (put 'imag-part '(polar) imag-part)
  (put 'magnitude '(polar) magnitude)
  (put 'angle '(polar) angle)
  (put 'make-from-real-imag 'polar
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'polar
       (lambda (r a) (tag (make-from-mag-ang r a))))
  'done)

(define (install-extended-operators)
  (put 'sin '(scheme-number) (lambda(x) (sin x)))
  (put 'sin '(rational) (lambda(x) (sin (/ (numer x) (denom x)))))
  (put 'cos '(scheme-number) (lambda(x) (cos x)))
  (put 'cos '(rational) (lambda(x) (cos (/ (numer x) (denom x)))))
  (put 'square '(scheme-number) (lambda(x) (square x)))
  (put 'square '(rational) (lambda(x) (square (/ (numer x) (denom x)))))
  (put 'atan '(rational rational) (lambda(x y) (atan (* (numer x) (denom y)) (* (numer y) (denom x)))))
  (put 'atan '(scheme-number scheme-number) (lambda (x y) (atan x y)))
  (put 'sqrt (scheme-number) (lambda(x) (sqrt x)))
  (put 'sqrt '(rational) (lambda(x) (sqrt (/ (numer x) (denom x))))))

;;----Ex 3.1----;;
(define (make-accumulator init)
  (define (sum amount)
    (begin (set! init (+ init amount))
	   init))
  sum)

;;----Ex 3.2----;;
(define (make-monitored f)
  (define (monitor count)
    (lambda (input)
      (cond ((eq? input 'how-many-calls?) count)
	    ((eq? input 'reset-count) (set! count 0))
	    (else (begin (set! count (+ count 1)) (f input))))))
  (monitor 0))

;;----Ex 3.3----;;
(define (make-account balance password)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (dispatch pass m)
    (if (eq? pass password)
	(cond ((eq? m 'withdraw) withdraw)
	      ((eq? m 'deposit) deposit)
	      (else (error "Unknown request -- MAKE-ACCOUNT"
                       m)))
	(error "Incorrect password")))	
  dispatch)

;;----Ex 3.4----;;
(define (make-account balance password)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (password-protect times)
    (define (dispatch pass m)
      (cond ((eq? pass password)
	     (cond ((eq? m 'withdraw) withdraw)
		   ((eq? m 'deposit) deposit)
		   (else (error "Unknown request -- MAKE-ACCOUNT"
				m))))
	    ((< times 7) (begin (set! times (+ times 1)) (error "Incorrect password")))
	    (else (call-the-cops))))
    dispatch)
  (password-protect 0))

;;----Ex 3.5----;;
(define (random-in-range low high)
  (let ((range (- high low)))
    (+ low (random range))))

(define (monte-carlo trials experiment)
  (define (iter trials-remaining trials-passed)
    (cond ((= trials-remaining 0)
           (/ trials-passed trials))
          ((experiment)
           (iter (- trials-remaining 1) (+ trials-passed 1)))
          (else
           (iter (- trials-remaining 1) trials-passed))))
  (iter trials 0))

(define (estimate-integral P x1 x2 y1 y2 times)
  (define (p-test) (P (random-in-range x1 x2) (random-in-range y1 y2)))
  (* (monte-carlo times p-test) (* (- x2 x1) (- y2 y1))))

;;----Ex 3.6----;;
(define (rand opt)
  (define (rand-o init)
    (define (reset input)
      (set! init input))
    (cond ((eq? opt 'generate) (begin (set! init (rand-update init)) init))
	  ((eq? opt 'reset) reset)
	  (else (error "Incorrect input"))))
  (rand-o 7))

;;----Ex 3.7----;;
(define (make-joint account password new-password)
  (define (access new-ps m)
    (if (eq? new-ps new-password)
	(account password m)
	(error "Incorrect password")))
  access)

;;----Ex 3.8----;;
(define f
  (let ((init '*))
    (lambda(x)
      (cond ((eq? init '*) (begin (set! init x) init))
	    ((> x init) 0)
	    (else x)))))

;;----Ex 3.17----;;
;;O(n^2)!
(define (count-pairs x)
  (define not-checked (check-loop))
  (define (iter a)
    (cond ((not (pair? a)) 0)
	  ((not-checked a) (+ (iter (car a))
			    (iter (cdr a))
			    1))
	  (else 0)))
  (iter x))

;;insufficient check-loop, O(n)!
(define (check-loop)
  (let ((check-list '()))
    (lambda(m)
      (define (loop m l)
	(cond ((eq? m 'show) check-list)
	      ((null? l) (begin (set! check-list (cons m check-list)) true))
	      ((eq? m (car l)) false)
	      (else (loop m (cdr l)))))
      (loop m check-list))))

;;----Ex 3.18----;;
;;use extra space, cannot detect list without non-pair element
(define (check-cycle x)
  (define (recover a)
    (cond ((not (pair? a)) '())
	  ((not (pair? (car a))) '())
	  ((and (not (pair? (cdar a))) (number? (caar a)))
	   (begin (set-car! a (cdar a))
		  (recover (cdr a))))
	  (else (begin (recover (car a))
		       (recover (cdr a))))))
  (define (check a n)
    (cond ((not (pair? a)) false)
	  ((not (pair? (car a)))
	   (begin (set-car! a (cons n (car a)))
		  (or (check (cdr a) (+ n 1))
		      false)))
	  ((and (not (pair? (cdar a))) (number? (caar a))) (> n (caar a)))
	  (else (or (check (car a) (+ n 1))
		    (check (cdr a) (+ n 1))))))
  (let ((res (check x 0)))
    (recover x)
    res)))

;;----Ex 3.19----;;
;; unknwon

;;----Ex 3.21----;;
(define (print-queue queue)
  (front-ptr queue))

;;----Ex 3.22----;;
(define (front-ptr queue) (car queue))
(define (rear-ptr queue) (cdr queue))
(define (set-front-ptr! queue item) (set-car! queue item))
(define (set-rear-ptr! queue item) (set-cdr! queue item))

(define (empty-deque? queue) (or (null? (front-ptr queue))) (null? (rear-ptr queue)))
(define (make-deque) (cons '() '()))

(define (front-deque queue)
  (if (empty-deque? queue)
      (error "FRONT called with an empty queue" queue)
      (car (front-ptr queue))))

(define (rear-deque queue)
  (if (empty-deque? queue)
      (error "FRONT called with an empty queue" queue)
      (car (rear-ptr queue))))

(define (front-insert-deque! queue item)
  (let ((new-pair (cons item (cons '() (front-ptr queue)))))
    (cond ((empty-deque? queue)
           (set-front-ptr! queue new-pair)
           (set-rear-ptr! queue new-pair)
           (print-deque queue))
          (else
	   (set-car! (cdr (front-ptr queue)) new-pair)
           (set-front-ptr! queue new-pair)
           (print-deque queue)))))

(define (front-delete-deque! queue)
  (cond ((empty-deque? queue)
         (error "DELETE! called with an empty queue" queue))
        (else
         (set-front-ptr! queue (cddr (front-ptr queue)))
	 (cond ((empty-deque? queue)
		(set-rear-ptr! queue '())
		(print-deque queue))
	       (else (set-car! (cdr (front-ptr queue)) '())
		     (print-deque queue))))))

(define (rear-insert-deque! queue item)
  (let ((new-pair (cons item (cons (rear-ptr queue) '()))))
    (cond ((empty-deque? queue)
           (set-front-ptr! queue new-pair)
           (set-rear-ptr! queue new-pair)
           (print-deque queue))
          (else
           (set-cdr! (cdr (rear-ptr queue)) new-pair)
           (set-rear-ptr! queue new-pair)
           (print-deque queue)))))

(define (rear-delete-deque! queue)
  (cond ((empty-deque? queue)
         (error "DELETE! called with an empty queue" queue))
        (else
         (set-rear-ptr! queue (cadr (rear-ptr queue)))
	 (cond ((empty-deque? queue)
		(set-front-ptr! queue '())
		(print-deque queue))
	       (else (set-cdr! (cdr (rear-ptr queue)) '())
		     (print-deque queue))))))

(define (print-deque queue)
  (define (print-now q)
    (let ((next (cddr q)))
      (if (null? next)
	  (list (car q))
	  (cons (car q) (print-now next)))))
  (if (empty-deque? queue)
      '()
      (print-now (front-ptr queue))))

;;----Ex 3.24-----;;
(define (make-table same-key?)
  (let ((local-table (list '*table*)))
    (define (assoc key records)
      (cond ((null? records) false)
	    ((same-key? key (caar records)) (car records))
	    (else (assoc key (cdr records)))))
    (define (lookup key-1 key-2)
      (let ((subtable (assoc key-1 (cdr local-table))))
        (if subtable
            (let ((record (assoc key-2 (cdr subtable))))
              (if record
                  (cdr record)
                  false))
            false)))
    (define (insert! key-1 key-2 value)
      (let ((subtable (assoc key-1 (cdr local-table))))
        (if subtable
            (let ((record (assoc key-2 (cdr subtable))))
              (if record
                  (set-cdr! record value)
                  (set-cdr! subtable
                            (cons (cons key-2 value)
                                  (cdr subtable)))))
            (set-cdr! local-table
                      (cons (list key-1
                                  (cons key-2 value))
                            (cdr local-table)))))
      'ok)    
    (define (dispatch m)
      (cond ((eq? m 'lookup-proc) lookup)
            ((eq? m 'insert-proc!) insert!)
            (else (error "Unknown operation -- TABLE" m))))
    dispatch))

(define operation-table (make-table same-key?))
(define get (operation-table 'lookup-proc))
(define put (operation-table 'insert-proc!))

;;----Ex 3.25-----;;
;;Miss understanding? seems just use originial ones
(define (make-table)
  (let ((local-table (list '*table*)))
    (define (lookup key-1 key-2)
      (let ((subtable (assoc key-1 (cdr local-table))))
        (if subtable
            (let ((record (assoc key-2 (cdr subtable))))
              (if record
                  (cdr record)
                  false))
            false)))
    (define (insert! key-1 key-2 value)
      (let ((subtable (assoc key-1 (cdr local-table))))
        (if subtable
            (let ((record (assoc key-2 (cdr subtable))))
              (if record
                  (set-cdr! record value)
                  (set-cdr! subtable
                            (cons (cons key-2 value)
                                  (cdr subtable)))))
            (set-cdr! local-table
                      (cons (list key-1
                                  (cons key-2 value))
                            (cdr local-table)))))
      'ok)    
    (define (dispatch m)
      (cond ((eq? m 'lookup-proc) lookup)
            ((eq? m 'insert-proc!) insert!)
            (else (error "Unknown operation -- TABLE" m))))
    dispatch))

(define operation-table (make-table))
(define get (operation-table 'lookup-proc))
(define put (operation-table 'insert-proc!))
	
;;----Ex 3.27----;;
;;Gobular------------|
;;| memorize         |
;;| memo-fib         |
;;-------------------|
;;    |          ^
;;    |          |
;;    |     |----------------|
;;    |     | table: *table* |
;;    |     |----------------|
;;    |         ^
;;    |         |
;;    |-> (x) (body with f = (lambda(n)...)
;;              ^
;;              |            ^
;;           |------|        |
;;           | x:3  | ----> (x:2 x:1)
;;           |------|
;; if change memo-fib to (memorize fib), the first call is similar as above,
;; but for the recursive call fib, fib will be the globular one, which will not use memorize


;;----Ex 3.28----;;
(define (or-gate a1 a2 output)
  (define (or-action-procedure)
    (let ((new-value (logical-or (get-signal a1) (get-singal a2))))
      (after-delay or-gate-delay
		   (lambda ()
		     (set-signal! output new-value)))))
  (add-action! a1 or-action-procedure)
  (add-action! a2 or-action-procedure)
  'ok)

;;----Ex 3.29----;;
(define (or-gate a1 a2 output)
  (let ((m1 (make-wire))
	(m2 (make-wire))
	(o (make-wire)))
    (inverter a1 m1)
    (inverter a2 m2)
    (and-gate m1 m2 o)
    (inverter o output)
    'ok))

;;----Ex 3.30----;;
(define (ripple-carry-adder A B C S)
  (define (adder ain bin cin sout)
    (cond ((null? A) 'ok)
	  ((null? (cdr A)) (full-adder (car A) (car B) cin (car S) 0)
	   (else (full-adder (car A) (car B) cin (car S) cout)
		 (adder (cdr A) (cdr B) cout (cdr S) )))))
  (adder A B C S))

;;----Ex 3.31----;;
;;if not run after added, the procedure will be only executed when the wire is set to a differet value.


;;----Ex 3.33----;;
(define (averager a b c)
  (let ((factor (make-connector))
	(sum (make-connector)))
    (adder a b sum)
    (multiplier sum factor c)
    (constant 0.5 factor)
    'ok))

;;----Ex 3.34----;;
;; If set b one value, the multiplier cannot get a since no condition satisfy m1 or m2 and product both have values.

;;----Ex 3.35----;;
(define (squarer a b)
  (define (process-new-value)
    (if (has-value? b)
        (if (< (get-value b) 0)
            (error "square less than 0 -- SQUARER" (get-value b))
	    (set-value! a (sqrt (get-value b)) me))
        (and (has-value? a) (set-value! b (square (get-value a)) me))))
  (define (process-forget-value)
    (forget-value! b me)
    (forget-value! a me)
    (process-new-value))
  (define (me request)
    (cond ((eq? request 'I-have-a-value)
	   (process-new-value))
	  ((eq? request 'I-lost-my-value)
	   (process-forget-value))
	  (else
           (error "Unknown request -- MULTIPLIER" request))))
  (connect a me)
  (connect b me)
  me)

;;----Ex 3.36----;;
;;--Globular----------
;;
;; a
;;--------------------
;; |  
;; |      ------------
;; |      | value: false
;; |      | informant: false
;; |      | constraints: '()
;; |      | P(set-my-value)
;; |      | P(forget-my-value)
;; |      | P(connect)
;; |----->| P(me)
;;        ------------
;;          |
;;        --------  
;;        | request:'set-value! |->  | set-my-value|           -> |for-each-except|
;;        --------                    newval: 10 setter: users     setter: users
;;        

;;----Ex 3.37----;;
(define (c- x y)
  (let ((z (make-connector)))
    (adder z y x)
    z))

(define (c* x y)
    (let ((z (make-connector)))
    (multiplier x y z)
    z))

(define (c/ x y)
    (let ((z (make-connector)))
    (multiplier z y x)
    z))

(define (cv v)
  (let ((x (make-connector)))
    (constant v x)
    x))

;;----Ex 3.39----;;
;;Possible result:
;;121,101
;;100: P1 calculated (* x x), then P2 set x to 11, then P1 set x to 100

;;----Ex 3.40----;;
;;Possible result:
;;1E6 P1 set x to 100, then P2 read x, then set x 1E6
;;    or P2 set x 1E3, then P1 read x, then set x 1E6
;;1E2 P1 execute (* x x), then p2 set x to 1E3, then P1 set x to 1E2
;;1E4 P2 set x to 1E3 between P1 execute (* x x), then p1 set x to 1E4
;;    or P1 set x to 1E2 after P2 read x second times, then P2 execute (* x x x), then P2 set x to 1E4
;;1E3 P2 execute (* x x x), then p1 set x to 1E2, then p2 set x to 1E3
;;IE5 P1 set x to 1E2 after P2 read x first time, then P2 execute (* x x x), then P2 set x to 1E5
;;Only 1E6 remain if set serializer

;;----Ex 3.41----;;
;;The new dispatch can be rewrited as
(lambda (m)
  ((lambda(p) 
     ((lambda(x y)
	(cond ((eq? m 'withdraw) x)
	      ((eq? m 'deposit) y)
	      ((eq? m 'balance) balance)
	      (else (error "Unknown request - Make-Account" m))))
      (p withdraw) (p deposit))))
  (make-serializer))
;;(make-serializer) and (p withdraw) (p deposit) are inside local environments
;;  protected : make-serializer
;;  -------------------------
;;            |
;;  protected-withdraw: (protected withdraw)
;;  protected-deposit: (protected deposit)
;;  ----------------------------------------
;;            |
;;         dispatch

;;then when call (dispatch m), like ((lambda(m) ((lambda(x y) ****) (p-w) (p-d))) m)
;;while the old one is like
((lambda(m) (conds ((eq? m 'withdraw) (p w))
		  ((eq? m 'deposit) (p d))
		  ((eq? m 'balance) (p b)))) m)

;;The result is same

