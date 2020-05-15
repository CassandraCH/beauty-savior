/**
 * \file level.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les niveaux : affichage et destruction des niveaux
 */
#include "level.h"
#include "constantes.h"

#include "baseGame.h"

Level level; /**< Structure d'un niveau */

/**
 * \fn extern Level* Get_Level()
 * \brief Fonction qui permet d'accéder à la structure d'un niveau
 * \return Un pointeur sur une structure de données de type Level
*/
extern Level* Get_Level()
{
   return &level;
}

/**
 * \fn extern void Set_Level(int niveau) 
 * \brief Fonction qui permet de mettre à jour le niveau du joueur
 * \brief
 * \param niveau numero du niveau
 * \return pas de valeur de retour (void)
*/
extern void Set_Level(int niveau) 
{
   getPlayer()->niveau = niveau;
}

/**
 * \fn extern void Level_Load()
 * \brief Fonction qui permet de charger un niveau
 * \brief Initialisation des listes (ennemis, bullets,items et colliders)
 * \return pas de valeur de retour (void)
*/
extern void Level_Load()
{
   printf("Chargement Niveau\n");
   
   //Initialisation des listes
   List_Init(&listEnnemis);
   List_Init(&bullet);
   List_Init(&items);
   List_Init(&listCollider);
      
   //Chargement du niveau 1
   if(  getPlayer()->niveau == 1 )
   {
      //Chargement de toutes les entites (sauf joueur)
      LoadAndCreate_PNJ(getCollider(),"files_assets/niveau1.txt") ;

      //Chargement des ennemis
      LoadEnemies("files_assets/ennemi_1.txt");

      Update_TextureEnemi();

      //Chargement des textures
      SDL_Texture * itemTex = Texture_Load("graphics_assets/coin.png");
      LoadItems("files_assets/items_1.txt", itemTex);

      printf("Chargement niveau 1\n");
      TextureManager_Load( &level.levelTextures[0], "graphics_assets/level1.png");
   }  

   //Chargement du niveau 2
   else if(  getPlayer()->niveau == 2 )
   {  
      //Destruction du niveau precedent
      Level_Destroy();

      //Chargement de toutes les entites (sauf joueur)
      LoadAndCreate_PNJ(getCollider(),"files_assets/niveau2.txt") ;
      LoadEnemies("files_assets/ennemi_2.txt");

      Update_TextureEnemi();

      //Chargement des textures
      SDL_Texture * itemTex = Texture_Load("graphics_assets/coin.png");

      //Suppression de la liste d'item precedente
      Delete_List(getItems()); 

      LoadItems("files_assets/items_2.txt", itemTex);

      printf("Chargement niveau 2\n");
      TextureManager_Load( &level.levelTextures[0], "graphics_assets/level2.png");
   }

   //Chargement du niveau 3
   else if(  getPlayer()->niveau == 3 )
   {  
         //Destruction du niveau precedent
         Level_Destroy();

         //Chargement de toutes les entites (sauf joueur)
         LoadAndCreate_PNJ(getCollider(),"files_assets/niveau3.txt") ;
         LoadEnemies("files_assets/ennemi_3.txt");

         Update_TextureEnemi();

         //Chargement des textures
         SDL_Texture * itemTex = Texture_Load("graphics_assets/coin.png");

         //Suppression de la liste d'item precedente
         Delete_List(getItems()); 

         LoadItems("files_assets/items_3.txt", itemTex);

         printf("Chargement niveau 3\n");
         TextureManager_Load( &level.levelTextures[0], "graphics_assets/level3.png");  
   }

   //Chargement du niveau 4
   else if(  getPlayer()->niveau == 4 )
   {  
         //Destruction du niveau precedent
         Level_Destroy();

         //Chargement de toutes les entites (sauf joueur)
         LoadAndCreate_PNJ(getCollider(),"files_assets/niveau4.txt") ;
         
         LoadEnemies("files_assets/ennemi_4.txt");

         Update_TextureEnemi();
         
         //Chargement des textures
          SDL_Texture *itemTex = Texture_Load("graphics_assets/coin.png");

         //Suppression de la liste d'item precedente
         Delete_List(getItems()); 

         LoadItems("files_assets/items_4.txt", itemTex);

         printf("Chargement niveau 4\n");
         TextureManager_Load( &level.levelTextures[0], "graphics_assets/level4.png");
   }
   printf("Fin chargement niveau\n");
}

/**
 * \fn extern void NiveauSuivant()
 * \brief Fonction qui permet de charger un niveau next
 * \brief Appel de la fonction Level_Load()
 * \return pas de valeur de retour (void)
*/
extern void NiveauSuivant()
{
   Level_Load();
}

/**
 * \fn extern void Debug_AfficherCollider() 
 * \brief Fonction de debug qui permet d'afficher les blocs de collision par dessus le decor
 * \brief Cette fonction permet de savoir si les blocs de collisions sont bien positionnés
 * \brief Cette fonction permet de verifier que le joueur entre bien en collision avec les colliders
 * \return pas de valeur de retour (void)
*/
extern void Debug_AfficherCollider() 
{
   SDL_Rect rect;
   SDL_Texture * texColider = Texture_Load("graphics_assets/rect10.png");
   
   //Parcours de la liste des colliders
   for(Node* pt = getCollider()->head ; pt != NULL ; pt = pt->next )
   {
      rect = (SDL_Rect) {  pt->_rect.x- camera.x ,pt->_rect.y-  camera.y ,pt->_rect.w,pt->_rect.h };

      //Affichage des colliders
      SDL_RenderCopy(getRenderer(), texColider , NULL, &rect);
   }
}

/**
 * \fn extern void Level_Textures_Render(int niveau)
 * \brief Fonction qui permet d'afficher les textures du niveau passé en paramètre
 * \param niveau numero du niveau a afficher
 * \return pas de valeur de retour (void)
*/
extern void Level_Textures_Render(int niveau)
{
   SDL_Rect renderQuad = {0, 0, camera.w ,  camera.h };
   SDL_RenderCopy( getRenderer() , Get_Level()->levelTextures[niveau].texture,&camera, &renderQuad);
}

/**
 * \fn extern void Level_Render()
 * \brief Fonction qui permet d'afficher un niveau
 * \return pas de valeur de retour (void)
*/
extern void Level_Render()
{  
   //Cas du niveau 1
   if(  getPlayer()->niveau == 1 )
   {
      Level_Textures_Render(0);
      Player_Render();
      Level_Textures_Render(1);
   }  

   //Cas du niveau 2
   else if(  getPlayer()->niveau == 2 )
   {  
      Level_Textures_Render(1);
   }
}

/**
 * \fn extern void Level_Destroy()
 * \brief Fonction qui permet de gérer la destruction des niveaux et la libération des ressources qui ont été utilisées
 * \return pas de valeur de retour (void)
*/
extern void Level_Destroy()
{
   printf("Destruction Niveau\n");
   
   TexManager_DestroyRessources( &Get_Level()->levelTextures[0] );
   TexManager_DestroyRessources( &Get_Level()->levelTextures[1] );

   printf("Fin Destruction Niveau\n");
}