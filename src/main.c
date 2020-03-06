/**
 * \file main.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \details Projet réalisé dans le cadre de la formation licence 2 informatiques de l'Université du Mans
 *          Le projet est un jeu de type plate, réalisé en langage C avec l'appui de la librairie SDL2.
 * \brief Programme principal du jeu
 */

#include "baseGame.h"



int main( int argc, char ** argv )
{

    Init("Beauty Savior");
	SDL_Event event;
	
     srand( (int) time(NULL));

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