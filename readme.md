# Snake

Premier projet C solo, en 2007, juste après le Sokoban du site du zéro ! (souvenirs)

En reprenant ce projet après de longues années, plusieurs adaptations ont dû être faites, notamment le passage à SDL2.
La gestion des threads avec SDL_Timer était aussi assez catastrophiques, et ce qui se comportait à peu près bien sur une machine de 2007 ne se comportait pas bien du tout sur une machine de 2015 en 2024 (dislocation du serpent, car l'un des threads de timer manipulait les mêmes variables que le thread principal, sans processus de lock ou équivalent).

Je mets donc ce projet ici en souvenirs de mes débuts en C. D'autres jeux viendront ensuite, je remonte chronologiquement.

## Installation

Il est nécessaire d'installer SDL2 pour faire compiler ce code, et de placer les dll suivants avec l'exécutable : SDL2.dll, SDL2_image.dll et SDL2_ttf.dll.
Le .vscode considère que lib\SDL2 est présent dans le répertoire principal du projet.

A la base il y avait du son avec FMOD mais j'ai supprimé tout ça du code, car aujourd'hui FMOD est devenu quelque chose de bien plus gros, plein de licenses, et le code a changé, je n'ai pas voulu me repencher sur le son dans cette version du jeu.

## Copyright

Il doit y avoir un peu d'infringment dans les fichiers joints, notamment les écrans "gagné" et "perdu", et l'écran titre, peut-être les polices. Je ne me suis pas penchée sur la question.
Seul le fichier "chateau.jpg" a été remplacé à la dernière minute par le banc d'arguin dans une tentative de démarche d'épuration des fichiers tiers, mais bon...
