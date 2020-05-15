/**
 * \file baseGame.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les différents comportements du jeu en fonction de l'état
 * \brief Etat possible : en cours de partie, en pause...
 */
#include "baseGame.h"
#include "commun.h"


Base_Game game; /**< Structure qui gère l'état du jeu */


int last_frame_time = 0; /**< Temps écoulé depuis la dernière image*/
float dt = 0.0f; /**< Delta-time = temps écoulé entre l'affichage de chaque image*/

/**
 * \fn Base_Game* getBaseGame()
 * \brief Fonction qui permet d'accéder à la structure qui gère l'état du jeu
 * \return Un pointeur sur une structure de données de type Base_Game
*/
Base_Game* getBaseGame()
{
  return &game;
}

/**
 * \fn extern void Update(float dt)
 * \brief Fonction qui permet gérer les comportements des entités si on se Find dans une partie et gérer le son si on se Find sur le menu principal
 * \brief Etat du jeu possible : menu principal ou en partie
 * \param dt valeur du delta-time
 * \return pas de valeur de retour (void)
*/
extern void Update(float dt)
{ 
  //Si la partie n'est pas gagnée 
  if( getBaseGame()->state != GAMEWIN )
  {
    //Cas ou on se Find dans le menu principal
    if ( game.state == MENU_PRINCIPAL )
    {
        //Gestion de la musique du menu principal
        if( !Mix_PlayingMusic() )
          Mix_PlayMusic(getGameObject()->bgm, -1);
    }

    //Cas ou on est en train de jouer
    else if ( game.state == IN_GAME )
    { 
      //Gestion du timer
      getBaseGame()->time++;
    
    
      getBaseGame()->tempsActuel = SDL_GetTicks();
      if (getBaseGame()->tempsActuel > getBaseGame()->tempsPrecedent + 1000 ) /* Si 1000 ms soit 1 sec se sont écoulées */
      {              
        --getBaseGame()->min;
        printf("%d\n", getBaseGame()->min );

        getBaseGame()->tempsPrecedent = getBaseGame()->tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
      } 

      // Si le temps du jeux est ingérieur au timer de 1min10 alors c'est la fin du niveau.
      if( getBaseGame()->min <= 0 )
      {
        GameOver_Load();
      }

      //Gestion des attaques
      Enemy_Attack();

      //Mise à jour des entités
      List_Update();
      Enemy_Update();
      Bullets_Update(joueur, ennemi);
      Player_Update();
  
      //Gestion des collisions
      Shoot_Collision();
      CollisionItems(); 
      Collision_Detection();
    }
  }
}

/**
 * \fn extern void Game_Render()
 * \brief Fonction qui permet de gérer le rendu 
 * \brief Affichage en fonction de l'etat dans lequel se Find le jeu
 * \return pas de valeur de retour (void)
*/
extern void Game_Render() 
{
  //Cas où le jeu n'est pas en pause, n'est pas sur l'inventaire, 
  // le jeu n'est pas terminé ni sur l'affichage de l'aide
  if ( getBaseGame()->state != PAUSE && getBaseGame()->state != INVENTAIRE 
    && getBaseGame()->state != GAMEWIN && getBaseGame()->state != HELP  )
  {
    SDL_SetRenderDrawColor(getRenderer(), 0xFF,0xFF,0xFF,0);
    SDL_RenderClear( getRenderer() );
  }

  //Cas où on est sur le menu principal
  if ( getBaseGame()->state == MENU_PRINCIPAL )
  {    
    GameObject_Render(getGameObject(), 4, 0, 0, 1280, 720 );
  
  }

  //Cas où on on charge une partie
  else if ( getBaseGame()->state == LOADING )
  {
    GameObject_Render(getMenuLoad(), 2, 0,0 , 1280, 720) ;
    Render_HUD(getScores());
    Render_HUD( getNiveau() );
  }

  //Cas où un niveau est terminé
  else if ( getBaseGame()->state == LEVEL_COMPLETED )
  {
    GameObject_Render(getMenuCon(), 1,0, 0, 1280, 720);
    Render_HUD(  getScores() );
    Render_HUD( getNiveau() );
  }

  //Cas où le jeu est en pause
  else if ( getBaseGame()->state == PAUSE )
  {
    GameObject_Render(getMenuPause(), 2,300, 200,  645, 432 );
  }

  //Cas où on affiche l'inventaire
  else if ( getBaseGame()->state == INVENTAIRE )
  {
      GameObject_Render( getInventaire(),3, 300, 200, 607, 269 );
      Render_HUD(getItem(0)); 
      Render_HUD(getItem(1));
      Render_HUD(getItem(2));
  }

  //Cas où le jeu est terminé = tous les niveaux sont terminés
  else if ( getBaseGame()->state == GAMEWIN )
  {
    GameObject_Render( getMenu_Win() ,2, 413, 74,433, 478  );
    Render_HUD( getNombreVie() );
    Render_HUD( getScores()  );

  }
  // Cas où le joueur affiche l'aide 
  else if ( getBaseGame()->state == HELP )
  {
    GameObject_Render( getHelp() ,0, 322, 150, 637, 363  );
    
  }

  //Cas où on est en train de jouer
  else if ( getBaseGame()->state == IN_GAME )
  { 
    Level_Textures_Render(0);
    Interface_Render();
    //Gestion des affchages des listes, du joueur et du score
    List_RenderElements( &listEnnemis, texture, ennemi, 50, 50 );
    

    // Liste des élements attaques
    List_RenderElements( &bullet , itemTex, feu , 41, 47 );
    List_RenderElements( &bullet , rockTex, rock, 37, 35 );
    List_RenderElements( &bullet , treeTex, tree , 31, 49 );
    
    Player_Render();

    // Liste de l'inventaire
    List_RenderElements( &items, osTex, os, 36, 51 ); 
    List_RenderElements( &items, rockTex, rock ,37, 35 ); 
    List_RenderElements( &items, treeTex, tree, 31, 49 );  
    
    // Afficher Passport
    List_RenderElements( &items, passportTex, passport, 43, 56 );  

    
  }

  //Cas où on a perdu
  else if (getBaseGame()->state == GAMEOVER )
  {
    GameObject_Render(getMenu_Over(), 4, 0, 0 , 1280, 720 );
    
  }

  SDL_RenderPresent(getRenderer());

  // Délai pour laisser respirer le processeur
  SDL_Delay(1);
}

/**
 * \fn extern void List_Update()
 * \brief Fonction qui met à jour les listes des bullets et des ennemis
 * \brief Suppression des listes si nécessaire
 * \return pas de valeur de retour (void)
*/
extern void List_Update()
{
  Delete_Target(getBullets(), true);
  Delete_Target(getEnnemis(), true);
}


/**
 * \fn extern delay(unsigned int frameLimit)
 * \brief Fonction qui permet de gérer le délai du jeu
 * \brief Gestion d'un délai lors de la mise à jour du jeu, afin de laisser respirer le processeur
 * \return pas de valeur de retour (void)
*/
extern void delay(unsigned int frameLimit)
{
	// Gestion des 60 fps (images/stories/seconde)
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}

	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}

	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}




