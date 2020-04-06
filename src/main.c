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
    unsigned int frameLimit = SDL_GetTicks() + 16;
    //
    int flPreviousTime = 0, flCurrentTime = 0;

    //delta-time
    float dt = 0.0f;

    //Tant que le jeu est actif (le jeu n'a pas ete quitte)
	while( getBaseGame()->estActif )
    {   
        //Gestion des entrees utilisateur
        ProcessInput(&event);
      
        //Gestion du comportement des entites
        Update(dt);
        
        //Gestion de l'affichage
		Rendu_Jeux( getBaseGame() );
        
        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16 
        delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
    } 
    
    //Liberation de la memoire 
    LibererRessources_Jeux();

    return 0;
}
