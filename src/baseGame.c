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

    
      getBaseGame()->tempsActuel = SDL_GetTicks();
      if (getBaseGame()->tempsActuel > getBaseGame()->tempsPrecedent + 1000 ) /* Si 1000 ms soit 1 sec se sont écoulées */
      {    
            --getBaseGame()->time_s;
            printf("%d\n", getBaseGame()->time_s );
            
          if( getBaseGame()->time_s > 100 )
              --getBaseGame()->sec;
          else 
              --getBaseGame()->min;

          getBaseGame()->tempsPrecedent = getBaseGame()->tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
      } 

      // Si le temps du jeux est ingérieur au timer de 1min10 alors c'est la fin du niveau.
      if( getBaseGame()->time_s <= 40 )
      {
        Init_GameOver();
      }
 
    
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
  //Cas ou le jeu n'est pas en pause
  if ( getBaseGame()->state != PAUSE || getBaseGame()->state != INVENTAIRE  )
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
    AfficherHUD(getScores());
    AfficherHUD( getNiveau() );
  }

  //Cas ou le jeu est en pause
  else if ( getBaseGame()->state == PAUSE )
  {
    Dessiner_Menu(getMenuPause(), 2,300, 200,  645, 432 );
  }
  else if ( getBaseGame()->state == INVENTAIRE )
  {
      Dessiner_Menu( getInventaire(),4, 300, 200, 600, 266 );
  }

  //Cas ou on est en train de jouer
  else if ( getBaseGame()->state == IN_GAME )
  { 
    
    if( getBaseGame()->time_s > 100 )
    {
      SetHUD_IntToTexture(getTime(),"1 : ",getBaseGame()->sec ,500, 0 );
    }
    else 
    {
      SetHUD_IntToTexture(getTime(),"0 : ", getBaseGame()->min ,500, 0 );
    }

    // afficher_textures_niveau(0);
    
    SDL_Texture * texture = ChargerTexture("graphics_assets/rect11.png");
    SDL_Texture * itemTex = ChargerTexture("graphics_assets/coin.png");

    //Gestion des affchages des listes, du joueur et du score
    Afficher_ElementsListes( &listEnnemis, texture, ennemi );
    Afficher_ElementsListes( &bullet , itemTex, bull );
    Afficher_ElementsListes( &bullet , itemTex, feu );
    
    AfficherJoueur();

    AfficherHUD(getScores()); 
    AfficherHUD(getTime());
    Afficher_ElementsListes( &items, itemTex, item ); 
    

    // afficher_textures_niveau(1);

    Debug_AfficherCollider();
  }

  //Cas ou on a perdu
  else if (getBaseGame()->state == GAMEOVER )
  {
    Dessiner_Menu(getMenu_Over(), 4, 0, 0 , 1280, 720 );
    AfficherHUD(getScores());
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

