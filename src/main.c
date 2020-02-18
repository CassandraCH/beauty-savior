
#include "baseGame.h"


/**
*\file main.c
*\brief Jeux de plateforme 2D
*\details Projet réalisé dans le cadre de la formation licence 2 informatiques de l'Université du Mans
*         Le projet est un jeu, réalisé en langage C avec l'appui de la librairie SDL2.
*\author Calvados Cindy, Karina Ousmanovah, Cassandra Chaumullon, Celia Chelli
*\version 0.1
*\date janvier 2020
*/

int main( int argc, char ** argv )
{
    Init("Beauty Savior");
	SDL_Event event;
	
    float flPreviousTime, flCurrentTime;

	while( getBaseGame()->estActif )
    {   

        flPreviousTime = flCurrentTime;
        flCurrentTime = SDL_GetTicks();

        float dt = flCurrentTime - flPreviousTime;

        if( dt > 0.15f )
            dt = 0.15f;
            
        ProcessInput(&event);
	
        Update(dt);
       
		Rendu_Jeux( getBaseGame() );

    } 

    
    
    Quitter_Jeux();

    return 0;
}