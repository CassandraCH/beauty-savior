/**
 * \file baseGame.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les différents comportements du jeu en fonction de l'état
 */
#include "baseGame.h"
#include "commun.h"


Base_Game game; /**< Structure qui gère l'état du jeu*/


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
 * \brief Fonction qui permet gerer les comportements des entités si on se trouve dans une partie et gerer le son si on se trouve sur le menu principal
 * \details Etat du jeu possible : menu principal ou en partie
 * \param dt valeur du delta-time
 * \return pas de valeur de retour (void)
*/
extern void Update(float dt)
{ 
  //Cas ou on se trouve dans le menu principal
  if ( game.state == MENU_PRINCIPAL )
  {
      //Gestion de la musique du menu principal
      if( !Mix_PlayingMusic() )
        Mix_PlayMusic(getMenu()->bgm, -1);
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
        Init_GameOver();
      }
 
    
        //Gestion des attaques
        attaqueEnnemis();

        //Mise à jour des entités
        Update_Listes();
        UpdateEnnemis();
        UpdateBullets(joueur, ennemi);
        UpdateJoueur();
    
        //Gestion des collisions
        collision_tir();
        CollisionItems(); 
        collisionDetection();

  }
}

/**
 * \fn extern void Rendu_Jeux()
 * \brief Fonction qui permet de gérer le rendu 
 * \details Affichage en fonction de l'etat dans lequel se trouve le jeu
 * \return pas de valeur de retour (void)
*/
extern void Rendu_Jeux() 
{
  //Cas ou le jeu n'est pas en pause
  if ( getBaseGame()->state != PAUSE && getBaseGame()->state != INVENTAIRE && getBaseGame()->state != GAMEWIN )
  {
    SDL_SetRenderDrawColor(getRenderer(), 0xFF,0xFF,0xFF,0);
    SDL_RenderClear( getRenderer() );
  }
  
  
  //Cas ou on est sur le menu principal
  if ( getBaseGame()->state == MENU_PRINCIPAL )
  {    
    Dessiner_Menu(getMenu(), 4, 0, 0, 1280, 720 );
    
  }

  //Cas ou on on charge une partie
  else if ( getBaseGame()->state == LOADING )
  {
    Dessiner_Menu(getMenuLoad(), 2, 0,0 , 1280, 720) ;
    AfficherHUD(getScores());
    AfficherHUD( getNiveau() );
  }

  //Cas ou un niveau a ete termine
  else if ( getBaseGame()->state == LEVEL_COMPLETED )
  {
    Dessiner_Menu(getMenuCon(), 1,0, 0, 1280, 720);
    AfficherHUD(  getScores() );
    AfficherHUD( getNiveau() );
  }

  //Cas ou le jeu est en pause
  else if ( getBaseGame()->state == PAUSE )
  {
    Dessiner_Menu(getMenuPause(), 2,300, 200,  645, 432 );
  }
  else if ( getBaseGame()->state == INVENTAIRE )
  {
      Dessiner_Menu( getInventaire(),3, 300, 200, 607, 269 );
      AfficherHUD(getItem(0)); 
      AfficherHUD(getItem(1));
      AfficherHUD(getItem(2));
  }

  else if ( getBaseGame()->state == GAMEWIN )
  {
    Dessiner_Menu( getMenu_Win() ,2, 413, 74,433, 478  );
   AfficherHUD(getNombreVie());
    AfficherHUD( getScores() );

  }

  //Cas ou on est en train de jouer
  else if ( getBaseGame()->state == IN_GAME )
  { 
    
    
    
    SDL_Texture * texture = ChargerTexture("graphics_assets/enemi.png");

    SDL_Texture * itemTex = ChargerTexture("graphics_assets/coin.png");
    SDL_Texture * rockTex = ChargerTexture("graphics_assets/tex_rock.png");
    SDL_Texture * treeTex = ChargerTexture("graphics_assets/tex_tree.png");
    SDL_Texture * osTex = ChargerTexture("graphics_assets/tex_os.png");
    
    afficher_textures_niveau(0);
    AfficherInterface();
    //Gestion des affchages des listes, du joueur et du score
    Afficher_ElementsListes( &listEnnemis, texture, ennemi, 50, 50 );
    
    // Liste des élements attaques
    Afficher_ElementsListes( &bullet , itemTex, feu , 41, 47 );
    Afficher_ElementsListes( &bullet , rockTex, rock, 37, 35 );
    Afficher_ElementsListes( &bullet , treeTex, tree , 31, 49 );
    
    AfficherJoueur();

    // Liste de l'inventaire
    Afficher_ElementsListes( &items, osTex, os, 36, 51 ); 
    Afficher_ElementsListes( &items, rockTex, rock ,37, 35 ); 
    Afficher_ElementsListes( &items, treeTex, tree, 31, 49 ); 

    
    
    
  }

  //Cas ou on a perdu
  else if (getBaseGame()->state == GAMEOVER )
  {
    Dessiner_Menu(getMenu_Over(), 4, 0, 0 , 1280, 720 );
    AfficherHUD(getScores());
  }

  SDL_RenderPresent(getRenderer());

  // Délai pour laisser respirer le processeur
    SDL_Delay(1);
}

/**
 * \fn extern void Update_Listes()
 * \brief Fonction qui met a jour les listes de bullets et ennemis
 * \details Suppression des listes si nécessaire
 * \return pas de valeur de retour (void)
*/
extern void Update_Listes()
{
  supprimeCible(getBullets(), true);
  supprimeCible(getEnnemis(), true);
}


/**
 * \fn extern delay(unsigned int frameLimit)
 * \brief Fonction qui permet de gérer le délai du jeu
 * \details Gestion d'un délai lors de la mise à jour du jeu, afin de laisser respirer le processeur
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




