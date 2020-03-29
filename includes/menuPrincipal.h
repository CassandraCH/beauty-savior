/**
 * \file menuPrincipal.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere le menu  pricipal du  jeu.
 */

#ifndef _MENU_PRINCIPAL_H
/**< \def _MENU_PRINCIPAL_H*/
#define _MENU_PRINCIPAL_H

#include "texture.h"

/** @brief  Nombre maximum d'options disponibles dans un menu */
#define MAX_NUMBER 3 


/**
 *\struct option
 *\details Structure gérant les caractéristiques liées à une option
 */
typedef struct option
{
    int largeur, hauteur;/**< la largeur, hauteur de l'option*/
    const char * nomOption;/**<le nom de l'option*/
    SDL_Texture *texture;/**< le texture de l'option*/
    SDL_Color couleur;/**<la couleur de l'option*/
    int x, y;/**<la position en x et y de l'option*/
    char * filename[4];/**<le fichiers contenant la texture de l'option*/

}Options_t;
/**< This is the documentation for the preceding typedef */

typedef struct menu Menu_t;
/**< This is the documentation for the preceding typedef */

/**
 *\struct menu
 *\details Structure
 */
struct menu
{
    int selectedOption;/**<selection de l'option*/
    Options_t menu[4];/**< le menu*/
    Mix_Chunk *son;/**< le son du menu*/
    TTF_Font * police;/**< la police utilise pour le menu*/
    SDL_Texture * bg;
    Mix_Music * bgm;

};



extern void UpdateOption(Options_t * menut, int etat);/**< fonction d'etat du menu*/
extern int getTouchePresse(Menu_t *menu);/**< fonction sur les touches du menu*/
extern void ToucheHaut(Menu_t * menu);/**< fonction pour la touche haut du menu*/
extern void ToucheBas(Menu_t *menu);/**<touche bas*/
extern void Droite(Menu_t *menu);/**< pour aller a droite*/
extern void Gauche(Menu_t *menu);/**< pour aller a gauche*/
extern void Dessiner_Menu(Menu_t* menu, int nombresOptions, int posX, int posY , int largeurBG, int hauteurBG);
extern void Init_MenuPrincipal();/**<initialise le menu*/
extern void Input_MenuPrincipal(SDL_Event* event);

extern void ChargerData_Menu(int numero,int num_image, Menu_t * menu,  char * nomOption,  char * image_on,  char * image_off,
int positionX, int positionY
);/**<rechargement du menu*/

extern void Nettoyer_Menu(Menu_t * menu, int nombreOptions);/**<fonction nettoyer le menu remmetre a zero*/




#endif
