# pigeon

## Dependencies
 - Any UNIX operating system (Linux preferred, OS X will also work). Windows will not work.
 - SBCL and Quicklisp for Lisp code.
 - Any C compiler (GCC or Clang preferred).
 - C libraries: gtk+ 3.0, libcURL 7.30.0 or higher. Install with brew on Mac or the default package manager on your Linux system.
 - Python packages: NLTK, summarizer, WordCloud. Install with PIP3.

## OS X instructions (assuming Homebrew, Python3/PIP3, and a C compiler are installed):
 - Run the shell command "brew install gtk3". This will take a while, so now would be a good time for a coffee break.
 - Run the shell command "brew install sbcl". This installs the SBCL Lisp compiler.
 - libcURL is usually installed by default on OS X, so you don't need to install it.
 - Run the shell command "pip3 install summarizer nltk wordcloud"

