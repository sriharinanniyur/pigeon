#!/bin/bash

# written by Aadit Trivedi
# requires this "sudo chmod +x osx-install.sh" to be executable through "./osx-install.sh"

read -r -p "Would you like to install pigeon? ___ GB will be added. [Y/n] " input

case $input in
    [yY][eE][sS]|[yY])
		/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
  brew reinstall python3
  brew reinstall gtk3
  brew reinstall sbcl
  pip3 install summarizer nltk wordcloud matplotlib --user

  # Fun animation

  echo " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&,@@@"
  sleep 0.2
  echo " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,,,,,@@@@"
  sleep 0.2
  echo " @@@@@@@@@@@@@@@%((*@@@@@@@@,,,,,,,,@@@@"
  sleep 0.2
  echo " @@@@@@@@@@@@@@(((((@@@@@&.,,,,,,,,,@@@@"
  sleep 0.2
  echo " @@@@@@@@@@@@@((((((/@@*****.,,,,,,,,@@@"
  sleep 0.2
  echo " @@@@@@@@@@@@((((((((*******..,,,,,,,,@@"
  sleep 0.2
  echo " @@@@@@@@@@@%((((((*******,....,,,,,@@@@"
  sleep 0.2
  echo " @@@@@@@@@@@(((((*********......,,,@@@@@"
  sleep 0.2
  echo " @@@@@@@@@@((((((*******.........,,@@@@@"
  sleep 0.2
  echo " @,,,,,@@@(((((((******...........@@@@@@"
  sleep 0.2
  echo " (**%****@(((((((*****   ........@@@@@@@"
  sleep 0.2
  echo " @@#%///////(,********    .....#@@@@@@@@"
  sleep 0.2
  echo " @@@@((((((*************(((( . @@@@@@@@@"
  sleep 0.2
  echo " @@@@@%(((*************/((((@@@@@@@@@@@@"
  sleep 0.2
  echo " @@@@@@@(********//********@@@@@@@@@@@@@"
  sleep 0.2
  echo " @@@@@@@@*********************.@@@@@@@@@"
  sleep 0.2
  echo " @@@@@@@@@***********************...*@@@"
  sleep 0.2
  echo " @@@@@@@@@@@,***********************(((@"
  sleep 0.2
  echo " @@@@@@@,,,,..,.....@@@@@@@@@@@@@@@@@@@@"
  sleep 0.2
  echo " @@@@@@@*,/,,,......@@@@@@@@@@@@@@@@@@@@"
  sleep 0.2
  echo " @@@@@@@***,*/,,....@@@@@@@@@@@@@@@@@@@@"
  sleep 0.2
  echo " @@@@@@@****,,,,,...@@@@@@@@@@@@@@@@@@@@"
  sleep 1

  echo "Pigeon v1.0 Installed!"

    [nN][oO]|[nN])
		echo "Okay, please close this window to cancel the installation."
       		;;

    *)
	echo "Invalid input..."
	exit 1
	;;
esac

