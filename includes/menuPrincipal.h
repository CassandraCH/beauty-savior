#ifndef _MENU_PRINCIPAL_H
#define _MENU_PRINCIPAL_H

#include "texture.h"

#define MAX_NUMBER 3


/**
 *\struct option
 *\details Structure gérant les caractéristiques liées à une option
 */
typedef struct option
{   
    int largeur, hauteur;
    const char * nomOption;
    SDL_Texture *texture;
    SDL_Color couleur;
    int x, y;
    char * filename[4];

}Options_t;

/**
 *\struct menu
 *\details Structure 
 */
typedef struct menu Menu_t;

struct menu
{
    int selectedOption;
    Options_t menu[4];
    Mix_Chunk *son;
    TTF_Font * police;
    SDL_Texture * bg;
    Mix_Music * bgm;

};



extern void UpdateOption(Options_t * menut, int etat);
extern int getTouchePresse(Menu_t *menu);

extern void ToucheHaut(Menu_t * menu);
extern void ToucheBas(Menu_t *menu);
extern void Droite(Menu_t *menu);
extern void Gauche(Menu_t *menu);
extern void Dessiner_Menu(Menu_t* menu, int nombresOptions, int posX, int posY , int largeurBG, int hauteurBG);
extern void Init_MenuPrincipal();
extern void Input_MenuPrincipal(SDL_Event* event);

extern void ChargerData_Menu(int numero,int num_image, Menu_t * menu,  char * nomOption,  char * image_on,  char * image_off,
int positionX, int positionY
);

extern void Nettoyer_Menu(Menu_t * menu, int nombreOptions);




#endif