#!/bin/bash

# written by Aadit Trivedi
# requires this "sudo chmod +x osx-install.sh" to be executable through "./osx-install.sh"

/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew reinstall python3
brew reinstall gtk3
brew reinstall sbcl
pip3 install summarizer nltk wordcloud matplotlib

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
