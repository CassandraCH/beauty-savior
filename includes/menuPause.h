#ifndef _MENU_PAUSE_H
#define _MENU_PAUSE_H


extern void Init_MenuPause();
extern void Dessiner_MenuPause();

extern void Droite(Menu_t* menu);
extern void Gauche(Menu_t* menu);
extern void LoadData_Menu(int numero,int num_image, Menu_t * menu,  char * nomOption,  char * image_on,  char * image_off,
int positionX, int positionY
);
extern void Input_MenuPause(SDL_Event *event);

extern void Nettoyer_MenuPause(Menu_t * menu);

extern void Init_Pause();

#endif