#include "baseGame.h"
#include "commun.h"


Base_Game game;


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
        
    }
    else if ( game.state == IN_GAME )
    {   
       
        getBaseGame()->time++;
        setTimerBullet(0);
        
        UpdateJoueur(dt);
        UpdateBullets();
        UpdateEnnemis();
    
        collision_tir();

        CollisionItems(); 
        collisionDetection();
        

        if( getTimerBullet() < 100 )
        {
          setTimerBullet(getTimerBullet() + 1);
        }
        else 
        {
          suppListe( &bullet );
          setTimerBullet(0);
        }

        
    }
      
}
    

extern void Rendu_Jeux() 
{
      SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);
      SDL_RenderClear(getRenderer());

  
    if ( getBaseGame()->state == MENU_PRINCIPAL )
    {
      
      Dessiner_MenuPrincipal();
    }
    else if ( getBaseGame()->state == IN_GAME )
    
    {

      Affichage_Niveau();
    

      SDL_Texture * texture = ChargerTexture("graphics_assets/rect11.png");
      SDL_Texture * itemTex = ChargerTexture("graphics_assets/coin.png");

      SDL_SetRenderDrawColor( getRenderer(), 0xFF,0,0,0 );

      Afficher_ElementsListes( &listEnnemis, texture, ennemi );
      Afficher_ElementsListes( &bullet , texture, bull );
      
      AfficherJoueur();
      Afficher_ElementsListes( &items, itemTex, item );

      // AfficherScore();
    
    }
    else if ( getBaseGame()->state == PAUSE )
    {
      // A définir 
    }



  SDL_RenderPresent( getRenderer() );

}
