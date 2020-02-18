#include "level.h"
#include "constants.h"

#include "baseGame.h"

Level level;
LinkedList listEnnemies;
LinkedList bullet;


extern Level* getLevel()
{
   return &level;
}

extern void ChargerNiveau()
{
   printf("Chargement Niveau\n");
   
   if(  getPlayer()->niveau == 1 )
   {
      initList(listEnnemies);
      initList(bullet);
      Load_And_CreatePNJ("niveau1.txt") ;
      ChargerEnnemis("ennemy.txt");
      level.levelTextures[0].texture = LoadTexture("assets/savior1-1.png");
   }  
   else if(  getPlayer()->niveau == 2 )
   {  
         // Load_And_CreatePNJ("niveau2.txt",ennemy) ;
         chargerImage(&getLevel()->levelTextures[1], "assets/niveau2.png");
   }
  printf("Fin chargement niveau\n");
}



extern void Affichage_Niveau ()
{  

   // printf("Affichage Niveau\n");
   
   if(  getPlayer()->niveau == 1 )
   {
      
      // dessiner(&getLevel()->levelTextures[0], 0,0, getBaseGame()->camera.w ,getBaseGame()->camera.h,SDL_FLIP_NONE);
      //SDL_SetRenderDrawColor(getRenderer(), 25,0 ,0, 0);
      // dessinerFullImage(&getLevel()->levelTextures[0],0,0 );
   }  
   else if(  getPlayer()->niveau == 2 )
   {  
         dessinerFullImage(&getLevel()->levelTextures[1],0,0 );
   }
   
   // printf("Fin Affichage Niveau\n");
   // if (  getBaseGame()->state == IN_GAME )
   // {
   //    if(  getPlayer()->niveau == 1 )
   //    {
         
       
   //    }
   //    else if(  getPlayer()->niveau == 2 )
   //    {
   //       dessinerFullImage(&getLevel()->levelTextures[1],0,0 );
        
   //    }
   // }
   // printf("Fin affichage Niveau\n");
   // dessinerFullImage(&getLevel()->levelTextures[0],0,0 );
   // if( getPlayer()->niveau == STATUS_STATE_LIVES )
   // {
   //   level.Render = draw_statud_live;
   // }
   // else if ( getPlayer()->niveau == STATUS_STATE_GAMEOVER )
   // {
   //     level.Render = init_status_lives;
   // }
   // else if ( getPlayer()->niveau == STATUS_STATE_WIN )
   // {
   //    level.Render = draw_game_win;
   // }
   // else  if ( getPlayer()->niveau == STATUS_STATE_PAUSE )
   // {
   //    level.Render = draw_game_pause;
   // }
    
}

extern void DestructionNiveau()
{
   printf("Destruction Niveau\n");
   
   if(  getPlayer()->niveau == 1 )
   {
      LibererRessources(&getLevel()->levelTextures[0]);
   }  
   else if(  getPlayer()->niveau == 2 )
   {  
      LibererRessources(&getLevel()->levelTextures[1]);
         
   }
   
   printf("Fin Destruction Niveau\n");
}