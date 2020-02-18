#include "level.h"
#include "constantes.h"

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
      init_List(&listEnnemies);
      init_List(&bullet);
      Chargement_CreationPNJ("niveau1.txt") ;
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