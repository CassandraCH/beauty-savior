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
 * \brief Mise à jour 
 * \details On fait appel à la fonction \a somme1(int n) et on multiplie par 2 son résultat
 * \param dt valeur du delta-time
*/
extern void Update(float dt)
{ 

    if ( game.state == MENU_PRINCIPAL )
    {
        
    }
    else if ( game.state == IN_GAME )
    {   
       
        getBaseGame()->time++;
        setTimerBullet(0);

        Update_Listes();

        UpdateJoueur(dt);
        UpdateBullets();
        UpdateEnnemis();
    
        collision_tir();

        CollisionItems(); 
        collisionDetection();
        
    }
      
}
    

extern void Rendu_Jeux() 
{
      
    SDL_SetRenderDrawColor(getRenderer(), 0,0,0,0);
    SDL_RenderClear( getRenderer() );
    

  
    if ( getBaseGame()->state == MENU_PRINCIPAL )
    {
      
      Dessiner_MenuPrincipal();
    }
    else if ( getBaseGame()->state == IN_GAME )
    
    {

      Affichage_Niveau();

      SDL_Texture * texture = ChargerTexture("graphics_assets/rect11.png");
      SDL_Texture * itemTex = ChargerTexture("graphics_assets/coin.png");

      Afficher_ElementsListes( &listEnnemis, texture, ennemi );
      Afficher_ElementsListes( &bullet , itemTex, bull );
      
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