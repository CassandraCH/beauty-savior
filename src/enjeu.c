/**
 * \file enjeu.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les entrées utilisateur (touches) et la caméra lorsqu'une partie est en cours
 */
#include "enjeu.h"
#include "baseGame.h"

SDL_Rect camera = {0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE}; /**< Structure qui gère la camera*/

/**
 * \fn extern void Input_InGame(SDL_Event *event)
 * \brief Fonction qui permet gerer les entrees clavier lorsqu'une partie est en cours
 * \details 
 * \details 
 * \param event pointeur sur une structure SDL evenement
 * \return pas de valeur de retour (void)
*/
extern void Input_InGame(SDL_Event *event)
{

    bool isKeyPressed = false; /**< Variable booleenne qui permet de savoir si une touche est pressee ou non*/

    //Tant que qu'il y a un evenement dans la file d'attente
    while( SDL_PollEvent(event) )
    {
        //Si la touche echap est pressee ou si l'utilisateur clique sur la croix
        if( event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE )
        {   
            //Modification de l'etat du jeu => n'est plu actif
            getBaseGame()->estActif = false;
            return;
        }

        //Si la touche  p est presse
        if(event->key.keysym.sym == SDLK_p && event->type == SDL_KEYDOWN )
        {
            //Modification de l'etat du jeu => en pause
            getBaseGame()->state = PAUSE;
            Init_MenuPause();
        }
        
        if(event->key.keysym.sym == SDLK_SPACE && event->type == SDL_KEYDOWN )
        {
            
            if( getPlayer()->nb_lancer < 1 && !isKeyPressed )
            {

                attaqueJoueur();
                isKeyPressed = true;
                return;
            }
            if(event->key.keysym.sym == SDLK_a && event->type == SDL_KEYUP )
            {
                isKeyPressed = false;
            }

        }

    } // fin while (SDL_PollEvent)


        const Uint8 *keystates  = SDL_GetKeyboardState(NULL);
        InputJoueur(event);
        camera.x = ( getPlayer()->x + getPlayer()->tex.w / 2 ) - LARGEUR_FENETRE / 2;
        camera.y = ( getPlayer()->y+  getPlayer()->tex.h / 2 ) - HAUTEUR_FENETRE / 2;
        
        if( camera.x < 0 )
        { 
        camera.x = 0;
        }
        if(camera.y < 0 )
        {
            
            camera.y = 0;
        }
        if( camera.x + camera.w >= LARGEUR_NIVEAU )
        {
            camera.x = LARGEUR_NIVEAU - LARGEUR_FENETRE;
        }
        if( camera.y + camera.h >= HAUTEUR_NIVEAU)
        {
            camera.y = HAUTEUR_NIVEAU - HAUTEUR_FENETRE;

        }

   
   
}

