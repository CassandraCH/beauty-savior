/**
 * \file enjeu.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les entrées utilisateur (touches) et la caméra lorsqu'une partie est en cours
 */

#include "baseGame.h"

SDL_Rect camera = {0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE}; /**< Structure qui gère la camera*/

/**
 * \fn extern void Input_InGame(SDL_Event *event)
 * \brief Fonction qui permet gérer les entr"es clavier et la camera lorsqu'une partie est en cours 
 * \brief Gestion des entrées de l'utilisateur
 * \param event pointeur sur une structure SDL evenement
 * \return pas de valeur de retour (void)
*/
extern void Input_InGame(SDL_Event *event)
{
    bool isKeyPressed = false; 
    
    /* Gestion des entrees clavier de l'utilisateur */

    //Tant que qu'il y a un evenement dans la file d'attente
    while( SDL_PollEvent(event) )
    {
        //Si la touche echap est pressée ou si l'utilisateur clique sur la croix
        if( event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE )
        {   
            //Modification de l'etat du jeu => n'est plus actif
            getBaseGame()->estActif = false;
            return;
        }

        //Si la touche p est pressée
        if(event->key.keysym.sym == SDLK_p && event->type == SDL_KEYDOWN )
        {
            //Gestion du menu de pause
            Pause_Init();
            //Modification de l'etat du jeu => en pause
            getBaseGame()->state = PAUSE;
        }

        //Si la touche i est pressée
        if(event->key.keysym.sym == SDLK_i && event->type == SDL_KEYDOWN )
        {
            
            //Gestion du menu de pause
            Inventaire_Init();
            //Modification de l'état du jeu => sur le menu de l'inventaire
            getBaseGame()->state = INVENTAIRE;
        }

        if( event->key.keysym.sym == SDLK_h && event->type == SDL_KEYDOWN )
        {
            
            //Gestion du menu de pause
            Help_Init();
            
            getBaseGame()->state = HELP;
        }


        //Si la touche espace est pressee
        if(event->key.keysym.sym == SDLK_SPACE && event->type == SDL_KEYDOWN )
        {
            //Vérification que le joueur a au moins un objet à lancer
            if( getPlayer()->nb_lancer < 1 && !isKeyPressed )
            {
                //Gestion de l'attaque
                Player_Attack();
                //Changement de l'état de la touche => pressée
                isKeyPressed = true;
                return;
            }

            //Si la touche a est pressée
            if(event->key.keysym.sym == SDLK_a && event->type == SDL_KEYUP )
            {
                //Changement de l'etat de la touche => pas pressee
                isKeyPressed = false;
            }
        }

    } // fin while (SDL_PollEvent)


    /* Gestion de la camera */

    const Uint8 *keystates = SDL_GetKeyboardState(NULL); //Variable qui permet de savoir si une touche est pressée ou non

    //Gestion des entrées claver de l'utilisateur
    Player_Input(event);
    
    //Initialisation de la position en x et en y de la camera
    camera.x = ( getPlayer()->x + getPlayer()->tex.w / 2 ) - LARGEUR_FENETRE / 2;
    camera.y = ( getPlayer()->y+  getPlayer()->tex.h / 2 ) - HAUTEUR_FENETRE / 2;
    
    //Gestion de la position en x : si le x est en dehors de la fenêtre, la repositionner
    if( camera.x < 0 )
    { 
        camera.x = 0;
    }

    //Gestion de la position en y : si le y est en dehors de la fenêtre, la repositionner
    if(camera.y < 0 )
    {
        camera.y = 0;
    }

    //Gestion de l'affichage en largeur de la camera
    if( camera.x + camera.w >= LARGEUR_NIVEAU )
    {
        camera.x = LARGEUR_NIVEAU - LARGEUR_FENETRE;
    }

    //Gestion de l'affichage en hauteur de la camera
    if( camera.y + camera.h >= HAUTEUR_NIVEAU)
    {
        camera.y = HAUTEUR_NIVEAU - HAUTEUR_FENETRE;

    }
}

