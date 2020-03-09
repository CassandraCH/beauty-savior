/**
 * \file baseGame.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les différents comportements du jeu en fonction de l'état
 */
#include "baseGame.h"
#include "commun.h"


Base_Game game; /**< */


int last_frame_time = 0;
float dt = 0.0f;

Base_Game* getBaseGame()
{
  return &game;
}



extern void Update(float dt)
{ 

    if ( game.state == MENU_PRINCIPAL )
    {
        if( !Mix_PlayingMusic() )
          Mix_PlayMusic(getMenu()->bgm, -1);
    }
    else if ( game.state == IN_GAME )
    {   
       
        getBaseGame()->time++;
        setTimerBullet(0);

        attaqueEnnemis();

        Update_Listes();
        UpdateJoueur(dt);
        UpdateBullets(joueur, ennemi);
        UpdateEnnemis();
    
        collision_tir();

        CollisionItems(); 
        collisionDetection();
        
    }
      
}
    

extern void Rendu_Jeux() 
{
      
    SDL_SetRenderDrawColor(getRenderer(), 0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear( getRenderer() );
    

  
    if ( getBaseGame()->state == MENU_PRINCIPAL )
    {
      
      Dessiner_MenuPrincipal();

      
    }
    else if ( getBaseGame()->state == IN_GAME )
    
    {

      Affichage_Niveau();
      Debug_AfficherCollider();
      SDL_Texture * texture = ChargerTexture("graphics_assets/rect11.png");
      SDL_Texture * itemTex = ChargerTexture("graphics_assets/coin.png");


      Afficher_ElementsListes( &listEnnemis, texture, ennemi );
      Afficher_ElementsListes( &bullet , itemTex, bull );
      Afficher_ElementsListes( &bullet , itemTex, feu );
      
      AfficherScores();
      
      Afficher_ElementsListes( &items, itemTex, item ); 

      AfficherJoueur();

    
    }
    else if ( getBaseGame()->state == PAUSE )
    {
      // A définir 
    }

    



  SDL_RenderPresent( getRenderer() );


}
/***
 * Met à jour les listes en supprimant si besoin
 */ 
extern void Update_Listes()
{
  supprimeCible(getBullets(), true);
  supprimeCible(getEnnemis(), true);
}

