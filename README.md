# Beauty Savior

Projet développé dans le cadre de la 2ème année licence Informatique.

![Image du Logo Beauty Savior](graphics_assets/logo.png)

## Qu'est-ce que c'est ? 
Beauty Savior est un jeu original développé en langage C avec pour appui la bibliothèque SDL2.

Ce projet a été réalisé dans le cadre de la deuxième année de Licence informatique à l'Université du Mans.

Son concept repose sur celui d'un plateformer.

L'idée est très simple, le but est de finir un niveau dans un temps imparti. 
À cela s'ajoute une contrainte qui est, de récupérer le passeport nécessaire à l'accès du niveau next.

Chaque niveau possède un nombre d'ennemis différents, ainsi que divers objets à récupérer.

L'équipe fut composée de :
  - Calvados Cindy
  - Chelli Celia
  - Chaumulon Cassandra
  - Ousmanova Karina

Les éléments de décor ainsi que le sprite du joueur utilisés dans le cadre de ce jeu sont tirés du pack : Platformer Art Deluxe conçu par Kenney proposé en (Licence CCO 1.0 Universal).

Les autres ressources graphiques telles que : 
- Logo,Ennemis,Items,Interface,Boutons,Menus,Inventaire,Menu aide/win, etc sont des ressources créés par moi-même, Calvados Cindy.

## Comment jouer ?

- Pour se déplacer, utilisez les flèches `Gauche` - `Droite`.
- Pour effectuer un saut, utilisez la touche `haut`.
- Pour mettre le jeu en pause, appuyer sur la touche `p`.
- Pour récupérer un objet, il suffit de le toucher.
- Pour accéder à l'inventaire, appuyez sur la touche `i`.
- Pour lancer une attaque, appuyez sur la touche `espace`.
- La sauvegarde se fait automatiquement à la fin d'un niveau.
- Pour quitter le jeu, appuyez sur `esc` ou cliquer sur la `croix`.
- Vous pouvez accéder à un rappel des commandes en appuyant sur `h`.

## Sous quelle plateforme est disponible le jeu ? 

Actuellement le jeu est disponible sous Windows et Linux.

Deux exécutables sont fournis:
- win_prog  => Environnement Windows.
- linux_prog  => Environnement Linux.

Pour lancer un exécutable il suffit d'entrée en ligne de commande : make <run_plateforme> .
- Exemple : make run_linux | make run_win 


/!\ __NE PAS ESSAYEZ DE RECOMPILER LE DOXYGEN__
- Le doxygen ayant été personnalisé manuellement avec du html et css, une recompilation causerait des erreurs.

/!\ __POUR RECOMPILER LE PROJET AVEC make . VEILLEZ A AVOIR UNE VERSION 32BITS DE gcc.__
- Veillez à bien indiquer la bonne plateforme à compiler, dans le fichier Makefile.compilation 
=> Exemple : ARCH=win | ARCH=linux


