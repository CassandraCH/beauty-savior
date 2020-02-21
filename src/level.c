#include "level.h"
#include "constantes.h"

#include "baseGame.h"

Level level;
LinkedList listEnnemis;
LinkedList bullet;
LinkedList listCollider;


extern Level* getLevel()
{
   return &level;
}

extern void ChargerNiveau()
{
   printf("Chargement Niveau\n");
   
   if(  getPlayer()->niveau == 1 )
   {
      init_List(&listEnnemis);
      init_List(&bullet);
      Chargement_CreationPNJ("files_assets/niveau1.txt") ;
      ChargementEnnemis("files_assets/ennemi.txt");
      level.levelTextures[0].texture = LoadTexture("graphics_assets/savior1-1.png");
   }  
   else if(  getPlayer()->niveau == 2 )
   {  
         // Load_And_CreatePNJ("files_assets/niveau2.txt",ennemy) ;
         chargerImage(&getLevel()->levelTextures[1], "graphics_assets/niveau2.png");
   }
  printf("Fin chargement niveau\n");
}


extern void Affichage_Niveau ()
{  

   // printf("Affichage Niveau\n");
   
   if(  getPlayer()->niveau == 1 )
   {
      SDL_SetRenderDrawColor(getRenderer(), 25,0 ,0, 0);
   }  
   else if(  getPlayer()->niveau == 2 )
   {  
      dessinerFullImage(&getLevel()->levelTextures[1],0,0 );
   }
   
    
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