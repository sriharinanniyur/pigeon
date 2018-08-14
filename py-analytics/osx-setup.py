# FOR OSX

import os

# install brew, the amazing Mac package manager
os.system("/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"")

# make sure python3 is installed
os.system("brew reinstall gtk3")

# installs the gui interface
os.system("brew reinstall gtk3")

# installs the sbcl lisp compiler
os.system("brew reinstall sbcl")

# install python packages
os.system("pip3 install summarizer nltk wordcloud matplotlib")
