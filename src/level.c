#include "level.h"
#include "constantes.h"

#include "baseGame.h"

Level level;


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
      init_List(&items);

      Chargement_CreationPNJ(getCollider(),"files_assets/niveau1.txt") ;

      ChargementEnnemis("files_assets/ennemi.txt");

      SDL_Texture * itemTex = ChargerTexture("graphics_assets/coin.png");
      ChargementItems("files_assets/coin.txt", itemTex);

      ChargerTextureManager( level.levelTextures, "graphics_assets/decor.png");
   }  
   else if(  getPlayer()->niveau == 2 )
   {  
         // Load_And_CreatePNJ("niveau2.txt",ennemy) ;
         chargerImage(&getLevel()->levelTextures[1], "graphics_assets/niveau2.png");
   }
  printf("Fin chargement niveau\n");
}

extern void Debug_AfficherCollider() 
{
   SDL_Rect rect;
   SDL_Texture * texColider = ChargerTexture("graphics_assets/rect10.png");
   for(Node* pt = getCollider()->tete ; pt != NULL ; pt = pt->suivant )
   {
          rect = (SDL_Rect) {  pt->rect->x- camera.x ,pt->rect->y-  camera.y ,pt->rect->w,pt->rect->h };
         SDL_RenderCopy(getRenderer(), texColider , NULL, &rect);
   }
}

extern void afficher_textures_niveau(int niveau)
{
   SDL_Rect renderQuad = {0, 0, camera.w ,  camera.h };
   SDL_RenderCopy( getRenderer() , getLevel()->levelTextures[niveau].texture,&camera, &renderQuad);

}

extern void Affichage_Niveau ()
{  

   // printf("Affichage Niveau\n");
   
   if(  getPlayer()->niveau == 1 )
   {

      afficher_textures_niveau(0);

   

   }  
   else if(  getPlayer()->niveau == 2 )
   {  
      afficher_textures_niveau(1);
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