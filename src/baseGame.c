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
		
		if (bullet.nodeCount > 0 || listCollider.nodeCount > 0 || listEnnemies.nodeCount > 0)
		{
		  deleteTarget(&bullet, true);
		  deleteTarget(&listCollider, true);
		  deleteTarget(&listEnnemies, true);
		}
        
        // moveRectangle(&bullet);
        
        UpdateJoueur(dt);
        // collisionDetect();
        collisionDecor((Entite*)getPlayer());
        for( Node * pt =listEnnemies.tete ; pt != NULL; pt=pt->suivant ) 
        {
          deplacement_entiteNJ((Entite*) pt );
		  collisionEntite((Entite*) getPlayer(), (Entite*) pt);
          collisionDecor((Entite*)pt);
        }
    }
      
}
    


extern void Rendu_Jeux() 
{
      SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);
      SDL_RenderClear(getRenderer());

  
    if ( getBaseGame()->state == MENU_PRINCIPAL )
    {
      SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);
      SDL_RenderClear(getRenderer());
      Draw_MenuPrincipal();
    }
    else if ( getBaseGame()->state == IN_GAME )
    
    {
//      clearRect(Listes());

      SDL_Surface* surface = IMG_Load("assets/rect10.png");
      SDL_Surface* surface2 = IMG_Load("assets/rect11.png");
      SDL_Surface* surface3 = IMG_Load("assets/arrow.png");
      SDL_Texture * texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
      SDL_Texture * texture2 = SDL_CreateTextureFromSurface(getRenderer(), surface2);
      SDL_Texture * texture3 = SDL_CreateTextureFromSurface(getRenderer(), surface3);

       if( listCollider.nodeCount > 0)
        {
          for(Node* pt = listCollider.tete ; pt != NULL ; pt = pt->suivant )
          {
            SDL_Rect ledgeRect = {  pt->rect->x- camera.x ,pt->rect->y-  camera.y ,pt->rect->w,pt->rect->h };
            if ( pt->type == platform )
            {
              SDL_RenderCopyEx(getRenderer(), texture , NULL, &ledgeRect, 0, 0, (pt->estTourne == 1) );
            } else if (pt->type == fleche )
            {
              SDL_RenderCopyEx(getRenderer(), texture3 , NULL, &ledgeRect,  0, 0, (pt->estTourne == 1) );
            }
             
          }
        }

      SDL_Rect renderQuad = {0, 0, camera.w ,  camera.h };
      SDL_RenderCopyEx( getRenderer() , getLevel()->levelTextures[0].texture,&camera, &renderQuad, 0.0, NULL, SDL_FLIP_NONE );

      SDL_SetRenderDrawColor( getRenderer(), 0xFF,0,0,0 );
        RenderElements(&listEnnemies, texture2, ennemi );
        RenderElements(&bullet, texture2, ennemi );
        

      
      Affichage_Niveau();
     
      AfficherJoueur();
    }
    else if ( getBaseGame()->state == PAUSE )
    {
      // A définir 
    }


    //  DrawScore();
    

  SDL_RenderPresent( getRenderer() );
  // delay(1);
}


void delay(unsigned int frameLimit)
{
    // Gestion des 60 fps (images/seconde)
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


