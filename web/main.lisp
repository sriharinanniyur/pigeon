; Written by Srihari Nanniyur.

(defpackage :actionable (:use :common-lisp))
(in-package :actionable)
(load "~/quicklisp/setup.lisp")
(ql:quickload :cl-ppcre :silent t)
(defvar *info-db* (make-hash-table :test #'equal))
(defvar *total-positives* 0)
(defvar *total-negatives* 0)

(defparameter *max-negative-score* .4)
(defparameter *min-positive-score* .6)

(defun result (text)
  (classify (score (get-info text))))

(defclass word-info ()
  ((word
    :initarg :word
    :accessor word
    :initform (error "must supply :word"))
   (positive-count
    :initarg :positive-count
    :accessor positive-count
    :initform 0)
   (negative-count
    :initarg :negative-count
    :accessor negative-count
    :initform 0)))

(defun intern-info (word)
  (or (gethash word *info-db*)
      (setf (gethash word *info-db*)
            (make-instance 'word-info :word word))))

(defun get-words (text)
  (delete-duplicates
   (cl-ppcre:all-matches-as-strings "[a-za-z]{3,}" text)
   :test #'string=))

(defun get-info (text)
  (mapcar #'intern-info (get-words text)))

(defun train (text type)
  (dolist (feature (get-info text))
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
   *info-db* (make-hash-table :test #'equal)
   *total-positives* 0
   *total-negatives* 0))

(defun positive-probability (feature)
  (with-slots (positive-count negative-count) feature
    (let ((pfreq (/ positive-count (max 1 *total-positives*)))
          (negative-frequency (/ negative-count (max 1 *total-negatives*))))
      (/ pfreq (+ pfreq negative-frequency)))))

(defun bayesian (feature &optional
                         (assumed-probability 1/2)
                         (weight 1))
  (let ((basic-probability (positive-probability feature))
        (dat-pts (+ (positive-count feature) (negative-count feature))))
    (/ (+ (* weight assumed-probability)
          (* dat-pts basic-probability))
       (+ weight dat-pts))))

(defun score (features)
  (let ((positive-probs ()) (negative-probs ()) (num-probs 0))
    (dolist (feature features)
      (unless (untrained-p feature)
        (let ((positive-prob (float (bayesian feature) 0.0d0)))
          (push positive-prob positive-probs)
          (push (- 1.0d0 positive-prob) negative-probs)
          (incf num-probs))))
    (let ((h (- 1 (fisher positive-probs num-probs)))
          (s (- 1 (fisher negative-probs num-probs))))
      (/ (+ (- 1 h) s) 2.0d0))))

(defun untrained-p (feature)
  (with-slots (positive-count negative-count) feature
    (and (zerop positive-count) (zerop negative-count))))

(defun fisher (probs num-probs)
  (inverse-chi-square 
   (* -2 (reduce #'+ probs :key #'log))
   (* 2 num-probs)))

(defun inverse-chi-square (value degfree)
  (assert (evenp degfree))
  (min 
   (loop with m = (/ value 2)
      for i below (/ degfree 2)
      for prob = (exp (- m)) then (* prob (/ m i))
      summing prob)
   1.0))

(defun classify (score)
  (values
   (cond
     ((<= score *max-negative-score*) 'not-action-item)
     ((>= score *min-positive-score*) 'action-item)
     (t 'unsure))
   score))

(with-open-file (positive-stream "training/POSITIVES")
  (loop for line = (read-line positive-stream nil)
        while line do
        (train line 'positive)))
(with-open-file (negative-stream "training/NEGATIVES")
  (loop for line = (read-line negative-stream nil)
        while line do
        (train line 'negative)))
(with-open-file (input-stream "data/DATA")
  (with-open-file (output-stream "data/RESULTS" :direction :output :if-exists :supersede)
    (loop for line = (read-line input-stream nil)
          while line do
          (when (equal (result line) 'action-item)
            (format output-stream "~s ~s~%" (result line) line)))))
