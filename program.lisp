; ACTIONABLE - Action-itemize e-mail.

(defpackage :actionable (:use :common-lisp))
(in-package :actionable)
(load "~/quicklisp/setup.lisp")
(ql:quickload :cl-ppcre)
(defvar *feature-db* (make-hash-table :test #'equal))
(defvar *total-positives* 0)
(defvar *total-negatives* 0)

(defparameter *max-negative-score* .4)
(defparameter *min-positive-score* .6)

(defun result (text)
  (classify (score (get-features text))))

(defclass word-info ()
  ((word       
    :initarg :word
    :accessor word
    :initform (error "Must supply :word"))
   (positive-count
    :initarg :positive-count
    :accessor positive-count
    :initform 0)
   (negative-count
    :initarg :negative-count
    :accessor negative-count
    :initform 0)))

(defun intern-info (word)
  (or (gethash word *feature-db*)
      (setf (gethash word *feature-db*)
            (make-instance 'word-info :word word))))

(defun get-words (text)
  (delete-duplicates
   (cl-ppcre:all-matches-as-strings "[a-zA-Z]{3,}" text)
   :test #'string=))

(defun get-features (text)
  (mapcar #'intern-info (get-words text)))

(defmethod print-object ((object word-info) stream)
  (print-unreadable-object (object stream :type t)
    (with-slots (word negative-count positive-count) object
      (format stream "~s :negatives ~d :positives ~d" word negative-count positive-count))))

(defun train (text type)
  (dolist (feature (get-features text))
    (incf-count feature type))
  (incf-total-count type))

(defun incf-count (feature type)
  (ecase type
    (negative (incf (negative-count feature)))
    (positive (incf (positive-count feature)))))

(defun incf-total-count (type)
  (ecase type
    (negative (incf *total-negatives*))
    (positive (incf *total-positives*))))

(defun clear-db ()
  (setf
   *feature-db* (make-hash-table :test #'equal)
   *total-positives* 0
   *total-negatives* 0))

(defun positive-probability (feature)
  (with-slots (positive-count negative-count) feature
    (let ((positive-frequency (/ positive-count (max 1 *total-positives*)))
          (negative-frequency (/ negative-count (max 1 *total-negatives*))))
      (/ positive-frequency (+ positive-frequency negative-frequency)))))

(defun bayesian-positive-probability (feature &optional
                                  (assumed-probability 1/2)
                                  (weight 1))
  (let ((basic-probability (positive-probability feature))
        (data-points (+ (positive-count feature) (negative-count feature))))
    (/ (+ (* weight assumed-probability)
          (* data-points basic-probability))
       (+ weight data-points))))

(defun score (features)
  (let ((positive-probs ()) (negative-probs ()) (number-of-probs 0))
    (dolist (feature features)
      (unless (untrained-p feature)
        (let ((positive-prob (float (bayesian-positive-probability feature) 0.0d0)))
          (push positive-prob positive-probs)
          (push (- 1.0d0 positive-prob) negative-probs)
          (incf number-of-probs))))
    (let ((h (- 1 (fisher positive-probs number-of-probs)))
          (s (- 1 (fisher negative-probs number-of-probs))))
      (/ (+ (- 1 h) s) 2.0d0))))

(defun untrained-p (feature)
  (with-slots (positive-count negative-count) feature
    (and (zerop positive-count) (zerop negative-count))))

(defun fisher (probs number-of-probs)
  (inverse-chi-square 
   (* -2 (reduce #'+ probs :key #'log))
   (* 2 number-of-probs)))

(defun inverse-chi-square (value degrees-of-freedom)
  (assert (evenp degrees-of-freedom))
  (min 
   (loop with m = (/ value 2)
      for i below (/ degrees-of-freedom 2)
      for prob = (exp (- m)) then (* prob (/ m i))
      summing prob)
   1.0))

(defun classify (score)
  (list
   (cond
     ((<= score *max-negative-score*) 'not-action-item)
     ((>= score *min-positive-score*) 'action-item)
     (t 'unsure))
   score))

(with-open-file (positive-stream "POSITIVES")
  (loop for line = (read-line positive-stream nil)
        while line do
        (train line 'positive)))
(with-open-file (negative-stream "NEGATIVES")
  (loop for line = (read-line negative-stream nil)
        while line do
        (train line 'negative)))
(format t "WELCOME TO ACTIONABLE. ENTER A SENTENCE TO GET ITS CLASSIFICATION.~%")
(loop for line = (read-line nil)
      while line do
      (format t "~S~%" (result line)))
