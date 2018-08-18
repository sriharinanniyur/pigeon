#!/bin/bash

# written by Aadit Trivedi

read -r -p "Would you like to install pigeon? ___ GB will be added. [Y/n] " input

case $input in
    [yY][eE][sS]|[yY])
    	/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	echo "Waking up Python3..."
	brew reinstall python3
	echo "Calling gtk3..."
	brew reinstall gtk3
	echo "Bringing on sbcl..."
	brew reinstall sbcl
	echo "Assembling Python libraries..."
	pip3 install summarizer nltk wordcloud matplotlib --user
	echo "Pigeon v1.0 Installed!"
    [nN][oO]|[nN])
		echo "Okay, please close this window to cancel the installation."
       		;;
    *)
	echo "Invalid input..."
	exit 1
	;;
esac
