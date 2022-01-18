# pigeon
### Practice project. Smart email client written in C/C++ and Lisp.

## Dependencies
 - Any UNIX operating system (Linux preferred, OS X will also work). Windows will not work.
 - SBCL and Quicklisp for Lisp code.
 - Any C compiler (GCC or Clang preferred).
 - C libraries: gtk+ 3.0, libcURL 7.30.0 or higher. Install with brew on Mac or the default package manager on your Linux system.
 - Python packages: NLTK, summarizer, WordCloud. Install with PIP3.
### OS X instructions:
 - Get Git from https://git-scm.com/downloads
 - If you already have git:
  1. Download the repository: ``$ sudo git clone https://github.com/sriharinanniyur/pigeon/``
  2. Add permission rights to continue installation: ``$ sudo chmod +x install.sh``
  3. Finally, run the installation: ``$ sudo ./install.sh``
 ### -------------OR----------

 - Run the shell command ``brew install gtk3``. This will take a while, so now would be a good time for a coffee break.
 - Run the shell command ``brew install sbcl``. This installs the SBCL Lisp compiler.
 - cd into your Downloads folder and run ``curl -O https://beta.quicklisp.org/quicklisp.lisp`` Then, run ``sbcl --load quicklisp.lisp``. At the prompt, type ``(quicklisp-quickstart:install)``. When the process is finished, exit with Ctrl-D.
 - libcURL is usually installed by default on OS X, so you don't need to install it.
 - Run the shell command ``pip3 install summarizer nltk wordcloud matplotlib``.
