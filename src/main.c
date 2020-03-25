/**
 * \file main.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \details Projet réalisé dans le cadre de la formation licence 2 informatiques de l'Université du Mans
 *          Le projet est un jeu de type plateformer, réalisé en langage C avec l'appui de la librairie SDL2.
 * \brief Programme principal du jeu
 */

#include "baseGame.h"

/**
 * \fn int main( int argc, char ** argv )
 * \brief Programme principal du jeu
 * \details 
 * \param argc 
 * \param argv 
 * \return 0
*/
int main( int argc, char ** argv )
{
    //Initialisation de la fenetre 
    Init("Beauty Savior");
	SDL_Event event;
	
    //Initialisation du generateur de nombres aleatoires
    srand( (int) time(NULL));

    //
    int flPreviousTime = 0, flCurrentTime = 0;

    //delta-time
    float dt = 0.0f;

    //Tant que le jeu est actif (le jeu n'a pas ete quitte)
	while( getBaseGame()->estActif )
    {   
        
        flPreviousTime = flCurrentTime;
        flCurrentTime = SDL_GetTicks();

        dt = (flCurrentTime - flPreviousTime) / 1000.0f;

        if( dt > 0.15f )
            dt = 0.15f;

        //Gestion des entrees utilisateur
        ProcessInput(&event);
      
        //Gestion du comportement des entites
        Update(dt);
        
        //Gestion de l'affichage
		Rendu_Jeux( getBaseGame() );
    } 
    
    //Liberation de la memoire 
    LibererRessources_Jeux();

    return 0;
}
