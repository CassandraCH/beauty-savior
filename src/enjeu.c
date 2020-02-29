#include "enjeu.h"
#include "baseGame.h"

SDL_Rect camera = {0,0,LARGEUR_FENETRE, HAUTEUR_FENETRE}; 

extern void Input_InGame(SDL_Event *event)
{

    bool isKeyPressed = false;
  
       
    while( SDL_PollEvent(event) )
    {
        if( event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE )
        {
            getBaseGame()->estActif = false;
            return;
        }
        
        if(event->key.keysym.sym == SDLK_a && event->type == SDL_KEYDOWN )
        {
            
            if( getPlayer()->nb_lancer < 1 && !isKeyPressed )
            {
                lancerObjet();
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

