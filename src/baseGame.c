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
      setTimerBullet(0); 

      //Gestion des attaques
      attaqueEnnemis();

      //Mise à jour des entités
      Update_Listes();
      UpdateJoueur(dt);
      UpdateBullets(joueur, ennemi);
      UpdateEnnemis();
  
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
  // 
  if ( getBaseGame()->state != PAUSE )
  {
    SDL_SetRenderDrawColor(getRenderer(), 0xFF,0xFF,0xFF,0);
    SDL_RenderClear( getRenderer() );
  }

  //Affichage du menu principal
  if ( getBaseGame()->state == MENU_PRINCIPAL )
  {
    Dessiner_MenuPrincipal();
  }

  //Affichage du menu pause
  else if ( getBaseGame()->state == PAUSE )
  {
    Dessiner_MenuPause();
  }
  //Affichage du jeu lors d'une partie
  else if ( getBaseGame()->state == IN_GAME )
  {

    Affichage_Niveau();
    // Debug_AfficherCollider();
    SDL_Texture * texture = ChargerTexture("graphics_assets/rect11.png");
    SDL_Texture * itemTex = ChargerTexture("graphics_assets/coin.png");


    Afficher_ElementsListes( &listEnnemis, texture, ennemi );
    Afficher_ElementsListes( &bullet , itemTex, bull );
    Afficher_ElementsListes( &bullet , itemTex, feu );
    
    AfficherScores();
    
    Afficher_ElementsListes( &items, itemTex, item ); 

    AfficherJoueur();
  }
  
  //Affichage du menu game over
  else if (getBaseGame()->state == GAMEOVER )
  {
    Dessiner_MenuGameOver();
    AfficherScores();
  }

  SDL_RenderPresent(getRenderer());
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

