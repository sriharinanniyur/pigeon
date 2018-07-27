(load "~/quicklisp/setup.lisp")
(ql:quickload :cl-ppcre)

(defparameter *max-negative-score* .4)
(defparameter *min-positive-score* .6)

(defun classify (score)
  (values
    (cond ((<= score *max-negative-score*) 'negative)
          ((>= score *min-positive-score*) 'positive)
          (t 'unclear))
    score))

(defclass word-feature ()
  ((word-name
     :initarg :word-name
     :accessor word-name
     :initform (error "unspecified :word argument"))
   (positive-count
     :initarg :positive-count
     :accessor positive-count
     :initform 0)
   (negative-count
     :initarg :negative-count
     :accessor negative-count
     :initform 0)))

(defvar *total-positive* 0)
(defvar *total-negative* 0)

(defvar *feature-db* (make-hash-table :test #'equal))
(defun clear-db ()
  (setf *feature-db* (make-hash-table :test #'equal))
  (setf *total-positive* 0)
  (setf *total-negative* 0))

(defun intern-feature (wrd)
  (or (gethash wrd *feature-db*)
      (setf (gethash wrd *feature-db*)
	    (make-instance 'word-feature :word-name wrd))))
(defun get-words (text)
  (delete-duplicates
   (cl-ppcre:all-matches-as-strings "[a-zA-Z]{3,}" text)
   :test #'string=))
(defun get-features (text)
  (mapcar #'intern-feature (get-words text)))

(defun train (text typeid)
  (dolist (feature (get-features text))
    (incf-count feature typeid))
  (incf-total-count typeid))

(defun incf-count (feature typeid)
  (ecase typeid
    (positive (incf (positive-count feature)))
    (negative (incf (negative-count feature)))))
(defun incf-total-count (type)
  (ecase type
    (positive (incf *total-positive*))
    (negative (incf *total-negative*))))

(defun probability (feature)
  (with-slots (positive-count negative-count) feature
    (let ((positive-frequency (/ positive-count (max 1 *total-positive*)))
          (negative-frequency (/ positive-count (max 1 *total-negative*))))
      (/ positive-frequency (+ positive-frequency negative-frequency)))))

(defun bayesian-probability (feature &optional
                                     (assumed-probability 1/2)
                                     (weight 1))
  (let ((basic-probability (probability feature))
        (data-points (+ (positive-count feature) (negative-count feature))))
    (/ (+ (* weight assumed-probability)
          (* data-points basic-probability))
       (+ weight data-points))))

(defun untrained-p (feature)
  (with-slots (positive-count negative-count) feature
    (and (zerop positive-count) (zerop negative-count))))

(defun score (features)
  (let ((positive-probs ()) (negative-probs ()) (number-of-probs 0))
    (dolist (feature features)
      (unless (untrained-p feature)
        (let ((positive-prob (float (bayesian-probability feature) 0.0d0)))
          (push positive-prob positive-probs)
          (push (- 1.0d0 positive-prob) negative-probs)
          (incf number-of-probs))))
    (let ((h (- 1 (fisher positive-probs number-of-probs)))
          (s (- 1 (fisher negative-probs number-of-probs))))
      (/ (+ (- 1 h) s) 2.0d0))))

(defun fisher (probs number-of-probs)
  (inverse-chi-square (* -2 (log (reduce #'* probs))) (* 2 number-of-probs)))

(defun inverse-chi-square (value degrees-of-freedom)
  (assert (evenp degrees-of-freedom))
  (min (loop with m = (/ value 2)
             for i below (/ degrees-of-freedom 2)
             for prob = (exp (- m)) then (* prob (/ m i))
             summing prob)
       1.0))

(defun result (text)
  (classify (score (get-features text))))
