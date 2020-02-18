#include "ingame.h"

#include "baseGame.h"

SDL_Rect camera = {0,0,LARGEUR_FENETRE, HAUTEUR_FENETRE}; 

extern void Input_InGame(SDL_Event *event)
{
    while( SDL_PollEvent(event) )
    {
        if( event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE )
        {
            getBaseGame()->estActif = false;
            return;
        }

       
        if(event->key.keysym.sym == SDLK_SPACE)
        {
            
            // if ( getPlayer()->lancer < 1 )
            // {
            //      SDL_Rect *rect = malloc(sizeof(SDL_Rect));
            //     rect->w = 20;
            //     rect->h = 20;
            //     rect->y = getPlayerY() - (rect->h/2);
            //     if( getPlayer()->isLeft )
            //         rect->x =  getPlayerX() - (rect->w/2);
            //     else
            //         rect->x =  getPlayerX() + getPlayer()->w ;
               
            //     insertQueue(&bullet, rect, item );
            //     getPlayer()->lancer++;
            // }
            printf("%d - %d \n", getPlayerX() ,  getPlayerY() );
        }
    } // fin while (SDL_PollEvent)

    const Uint8 *keystates  = SDL_GetKeyboardState(NULL);
    InputJoueur(event);

    camera.x = ( getPlayer()->x + getPlayer()->w / 2 ) - LARGEUR_FENETRE / 2;
    camera.y = ( getPlayer()->y+  getPlayer()->h  / 2 ) - HAUTEUR_FENETRE / 2;
	
	 if( camera.x < 0 )
    { 
       camera.x = 0;
    }
    if(camera.y < 0 )
    {
		
        camera.y = 0;
    }
    if( camera.x + camera.w >= LEVEL_WIDTH )
    {
        camera.x = LEVEL_WIDTH - LARGEUR_FENETRE;
    }
    if( camera.y + camera.h >= LEVEL_HEIGHT)
    {
        camera.y = LEVEL_HEIGHT - HAUTEUR_FENETRE;
    }
    
}

extern void UpdateIngame()
{

}

extern void RenderIngame()
{

}