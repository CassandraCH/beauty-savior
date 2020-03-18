#ifndef HUD_H
#define HUD_H

typedef struct hud_s
{
    TTF_Font* police;
	SDL_Surface* surface;
    SDL_Texture *tex;
	SDL_Rect rect;

}HUD;



extern void Init_HUD(const char * text, int x,  int y);
extern void NettoyerHUD()

#endif