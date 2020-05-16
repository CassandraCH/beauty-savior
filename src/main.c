/**
 * \file main.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Projet réalisé dans le cadre de la formation licence 2 informatiques de l'Université du Mans
 *          Le projet est un jeu de type plate-forme, réalisé en langage C avec l'appui de la librairie SDL2.
 * \brief Programme principal du jeu
 */

#include "baseGame.h"

/**
 * \fn int main( int argc, char ** argv )
 * \brief Programme principal du jeu
 * \brief 
 * \param argc nombre de paramètres
 * \param argv les arguments
 * \return 0
*/
int main( int argc, char ** argv )
{
    
	SDL_Event event;
    
    //Initialisation du generateur de nombres aleatoires
    srand( (int) time(NULL));

    unsigned int frameLimit = SDL_GetTicks() + 16;
    //
    int flPreviousTime = 0, flCurrentTime = 0;

    //Initialisation des données du jeu
    Init("Beauty Savior");
    
    //Tant que le jeu est actif (le jeu n'a pas ete quitte)
	while( getBaseGame()->estActif ) {   
        //Gestion des entrees utilisateurs
        ProcessInput(&event);
      
        //Mis à jour des composants
        Update();
        
        // Gestion de l'affichage des éléments graphiques du jeu
		Game_Render( getBaseGame() );
        
        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16)
        delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
    } 
    
    //Liberation de la memoire 
    Game_DestroyRessources();

    return 0;
}
