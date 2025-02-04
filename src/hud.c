/**
 * \file hud.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le compteur de temps, le compteur de vie et le score à afficher
 * \brief Affichage et mise à jour graphique des éléments
 */

#include "basegame.h"

/**
 * \fn extern void Init_HUD(HUD * hud, SDL_Color color, const char * text, int x,  int y)
 * \brief Fonction qui permet d'initialiser un hud
 * \brief Un hud correspond à toutes les informations concernant le joueur tels que le score ou le nombre de vie par exemple
 * \param hud pointeur sur une structure de type HUD 
 * \param color enumération SDL_Color correspondant à la couleur de la police 
 * \param text chaîne de caractère qui correspond au nom de la texture
 * \param x position en x du hud
 * \param y position en y du hud
 * \return pas de valeur de retour (void)
*/
extern void Init_HUD(HUD * hud,SDL_Color color,  const char * text, int x,  int y)
{
    //Transformation du texte en une surface
   
    hud->surface = TTF_RenderText_Solid(hud->police, text, color );

    
    //Transformation de la texture en surface
    hud->tex = SDL_CreateTextureFromSurface( getRenderer(), hud->surface );
    
    int width, height;
    SDL_QueryTexture(hud->tex, NULL, NULL, &width, &height);

    hud->_rect.x = x; //Position en x du hud
    hud->_rect.y = y; //Position en y du hud
    hud->_rect.w = width; //Largeur du hud
    hud->_rect.h = height; //Hauteur du hud
}

/**
 * \fn extern void SetHUD_IntToTexture(HUD * hud, SDL_Color color, const char * nom, int valeur, int posX, int posY)
 * \brief Fonction qui permet de creer la texture d'un hud
 * \param hud pointeur sur une structure de type HUD 
 * \param color enumération SDL_Color correspondant à la couleur de la police 
 * \param nom chaîne de caractère de ce qu'on veut afficher
 * \param valeur valeur numérique à afficher dans le hud
 * \param posX position en x du hud
 * \param posY position en y du hud
 * \return pas de valeur de retour (void)
*/
extern void SetHUD_IntToTexture(HUD * hud,SDL_Color color, const char * nom, int valeur, int posX, int posY)
{
    //Création d'une texture pour le hud
    SDL_Texture * tex = hud->tex;

    //Verifie que la texture a été créé correctement
    if( tex != NULL )
    {
        //Libération de la mémoire et destruction de la texture
        SDL_FreeSurface(hud->surface);
        SDL_DestroyTexture(hud->tex);
    }

    char sc[30];

    sprintf( sc, "%s %d" , nom, valeur ); 
    
 
    hud->surface = TTF_RenderText_Solid(hud->police, sc, color );
   
    //Transformation de la surface en texture
    hud->tex = SDL_CreateTextureFromSurface( getRenderer() , hud->surface );

    int width, height;
    SDL_QueryTexture(hud->tex, NULL, NULL, &width, &height);

    hud->_rect.w = width; //Largeur du hud
    hud->_rect.h = height;//Hauteur du hud
    hud->_rect.x = posX;  //Position en x du hud
    hud->_rect.y = posY;  //Position en y du hud
}


/**
 * \fn extern void Render_HUD(HUD * hud)
 * \brief Fonction qui permet d'afficher un hud
 * \param hud pointeur sur le hud à afficher
 * \return pas de valeur de retour (void)
*/
extern void Render_HUD(HUD * hud)
{
    SDL_Rect scor = {hud->_rect.x - camera.x  ,hud->_rect.y - camera.y, hud->_rect.w ,hud->_rect.h };
    SDL_RenderCopy(getRenderer(), hud->tex, NULL, &hud->_rect);
}

/**
 * \fn extern void Clean_HUD(HUD * hud)
 * \brief Fonction qui detruit un hud
 * \brief 
 * \param hud pointeur sur le hud à supprimer
 * \return pas de valeur de retour (void)
*/
extern void Clean_HUD(HUD * hud)
{
    //Vérifie que la texture a été correctement créé
    if(hud->tex != NULL)
    {
        printf("Nettoyer HUD\n");

        //Libération de la mémoire
        SDL_FreeSurface(hud->surface);

        //Destruction de la texture du hud
        SDL_DestroyTexture(hud->tex);
    }
    
}