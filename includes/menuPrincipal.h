#ifndef _MENU_PRINCIPAL_H
#define _MENU_PRINCIPAL_H

// #include "Texture.h"

#define MAX_NUMBER 3 //nombre d'éléments du menu


typedef struct option
{   
    int largeur, hauteur;
    const char * nomOption;
    SDL_Texture *texture;
    SDL_Color couleur;
    int x, y;

}Options_t;


typedef struct menu
{
    int selectedOption;
    Options menu[3];
    Mix_Chunk *son;
    TTF_Font * police;

}Menu_t;


extern void UpdateOption(Options_t * );
extern int GetKeyPressed();

extern void MoveUp();
extern void MoveDown();

extern void Init_MenuPrincipal();
extern void Draw_MenuPrincipal();

extern void Input_MenuPrincipal(SDL_Event* event);

extern void Nettoyer_MenuPrincipal();



#endif