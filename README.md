# i-score-metabot

[Stage : i-score et metabot au SCRIME] (http://i-score.org/)

Contient des scripts pour transformer les fichiers issus du site internet http://blocks.metabot.fr/ en fichier assembleur RHOCK et xml qui seront lisible par i-score, un logiciel séquenceur.

Pour cela, il faut installer libxml2 : 
	sudo apt get install libxml2-utils

Pour lancer et passer de .metablocks à des commandes envoyer au metabot.
	./lancement.sh fichier.metablocks

Ce dossier contient un fichier danse_FOB.metablocks qui contient une chorégraphie possible effectuée via le site internet blocks.metabot.fr.

Pour la lancer sur le robot, il faut mettre à jour le firmware du metabot vers la version 1.1.

Installer robotManager (avec QtCreator sur Ubuntu ou directement via le site metabot.fr) et brancher le metabot par usb à un ordinateur.

Pour mettre à jour le metabot:

	- soit être connecté sur robotManager (usb) et mettre à jour le firmware.
	- soit avec un firmware custom dans le dossier.
		python robotis-loader.py /dev/ttyACM0 metabot.bin
	- soit ./prepare.sh // make // make install
Pour récupérer le dossier firmware du metabot:
A l'heure actuelle, les fonctions rhocks ne sont pas fournit dans le dossier  git clone https:// gitHub.com/Rhoban/Metabot.git.


Il manque donc deux dossiers, pour cela, dans le dossier /firmware/src/ faire ./prepare.sh.

Si ce script échoue: dans le dossier /src mkdir rhock 
./prepare.sh ou directement git clone https:// gitHub.com/Rhoban/Rhock. 

Enlever les -Wall du Makefile
Si le Makefile ne trouve pas la bibliothèque libstdc++.a, il faut remplacer la ligne LDFLAGS par  
	LDFLAGS = $(TARGET_LDFLAGS) $(TOOLCHAIN\_LDFLAGS) 
		-mcpu=cortex-m3 -mthumb \ -Xlinker 
		--gc-sections \ -Xassembler
		--march=armv7-m \ 
		-L./RobotsWar/BinutilsArm/arm-none-eabi/lib/armv6-m/ -lstdc++

Pour compiler une chorégraphie dans le metabot:
	- se connecter sur le site blocks.metabot.fr
	- importer le fichier danse_FOB.metablocks
	- compiler vers le metabot
	- 
Il est possible de lancer cette danse sur un smartphone via l'application Android metabot https://play.google.com/store/apps/details?id=fr.metabot.mobile

Ou via un terminal avec run [id].

Commande à connaître:
id étant le slot ou ce trouve le programme. Pour le connaître: store.

Pour arrêter un programme kill [id] plusieurs kill all. Pour supprimer un programme erase [id] ou erase all.

