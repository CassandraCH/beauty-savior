# Beauty Savior

Projet développé dans le cadre de la 2ème année licence Informatique.

![Image du Logo Beauty Savior](graphics_assets/logo.png)

## Qu'est-ce que c'est ? 
Beauty Savior est un jeu original développé en langage C avec pour appui la bibliothèque SDL2.

Ce projet a été réalisé dans le cadre de la deuxième année de Licence informatique à l'Université du Mans.

Son concept repose sur celui d'un plateformer.

L'idée est très simple, le but est de finir un niveau dans un temps imparti. 
À cela s'ajoute une contrainte qui est, de récupérer le passeport nécessaire à l'accès du niveau suivant.

Chaque niveau possède un nombre d'ennemis différents, ainsi que divers objets à récupérer.

L'équipe fut composée de :
  - Calvados Cindy
  - Chelli Celia
  - Chaumulon Cassandra
  - Ousmanova Karina


## Comment jouer ?

- Pour se déplacer, utilisez les flèches `gauche` - `droite`.
- Pour effectuer un saut, utilisez la touche `haut`.
- Pour mettre le jeu en pause, appuyer sur la touche `p`.
- Pour récupérer un objet, il suffit de le toucher.
- Pour accéder à l'inventaire, appuyez sur la touche `i`.
- Pour lancer une attaque, appuyez sur la touche `espace`.
- La sauvegarde se fait automatiquement à la fin d'un niveau.
- Pour quitter le jeu, appuyez sur `esc` ou cliquer sur la `croix`.

## Sous quelle plateforme est disponible le jeu ? 

Actuellement le jeu est disponible sous Windows et Linux.

Deux exécutables sont fournis:
- win_prog  => Environnement Windows.
- linux_prog  => Environnement Linux.

Pour lancer un exécutable il suffit d'entrée en ligne de commande : make <run_plateforme> .
- Exemple : make run_linux | make run_win 

/!\ __NE PAS ESSAYEZ DE RECOMPILER LES SOURCES__ 
- Les sources SDL2 étant liées statiquement au programme, une recompilation causerait une erreur.
Si vous souhaitez compiler les sources, assurez-vous d'avoir SDL2 , SDL_Image, SDL_Mixer, SDL_TTF installer sur votre environnement de travail.
- Veillez également à vérifier le makefile et à modifier au besoin les chemins vers les librairies SDL2.
